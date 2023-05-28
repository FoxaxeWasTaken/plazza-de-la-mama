/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

#include <sstream>
#include <iostream>
#include <iomanip>

Plazza::Kitchen::Kitchen(std::size_t nbCooks, std::size_t timeRestock, double timeMultiplier, NamedPipes &pipes)
    : _clock(), _storage(), _toCook(), _cooked(), _cooks(), _timeRestock(timeRestock), _isClosing(false), _pipes(pipes)
{
    for (std::size_t i = 0; i < nbCooks; i++)
        _cooks.push_back(std::make_unique<Cook>(_storage, timeMultiplier, _toCook, _cooked, _isClosing));
    run();
}

void Plazza::Kitchen::run()
{
    double refillTime = 0;
    double closeTime = 0;
    double newTime;

    while (_isClosing.load() == false) {
        _sendPizzaOrders();
        newTime = _clock.getElapsedTime();
        _clock.restart();
        refillTime += newTime * 1000;
        closeTime += newTime;
        for (auto &cook : _cooks) {
            cook->addTime(newTime);
        }
        if (refillTime >= static_cast<double>(_timeRestock)) {
            _storage.refill();
            refillTime -= static_cast<double>(_timeRestock);
        }
        if (_toCook.size() > 0 || _getCookOccupancy() > 0) {
            closeTime = 0;
        } else if (closeTime >= 5) {
            _isClosing.store(true);
            break;
        }
        usleep(10000);
        std::string msg;
        _pipes >> msg;
        if (msg.empty())
            continue;
        _processMessage(msg);
    }
    _sendPizzaOrders();
    _sendQuitMessage();
}

void Plazza::Kitchen::_processMessage(const std::string &msg)
{
    Plazza::MessageType type = Plazza::Message::getTypeFromStr(msg);

    if (type == Plazza::MessageType::Status) {
        std::ostringstream oss;
        oss << "\t" << "Pizzas in queue: " << _toCook.size() << std::endl;
        oss << "\t" << "Pizzas cooking: " << _getCookOccupancy() << std::endl;
        oss << "\t" << "Can cook " << _getAvailability() << " pizzas" << std::endl;
        oss << "\t" << "Ingredients: ";
        int ingredient = 1;
        while (ingredient <= 256) {
            Ingredients casted = static_cast<Ingredients>(ingredient);
            oss << " " << ingredientsMap.at(casted) << ": " << _storage.getIngredient(casted);
            ingredient *= 2;
        }
        Plazza::StatusMessage status(oss.str(), _getAvailability(), Plazza::R_Reception);
        status >> _pipes;
    }
    if (type == Plazza::MessageType::Order) {
        std::unique_ptr<Plazza::OrderMessage> order = Plazza::Message::unpack<Plazza::OrderMessage>(msg);
        std::unique_ptr<IPizza> pizza = std::move(order->getPizza());
        _toCook.push(pizza);
    }
}



std::size_t Plazza::Kitchen::_getCookOccupancy()
{
    std::size_t nbCooks = 0;

    for (auto &cook : _cooks) {
        if (cook->isCooking())
            nbCooks++;
    }
    return nbCooks;
}

std::size_t Plazza::Kitchen::_getAvailability()
{
    int pizzasInQueue = _toCook.size();
    int pizzasCooking = _getCookOccupancy();
    int totalAv = _getCookCount() * 2;

    int result = totalAv - pizzasInQueue - pizzasCooking;
    return result > 0 ? result : 0;
}

std::size_t Plazza::Kitchen::_getCookCount() const
{
    return _cooks.size();
}

void Plazza::Kitchen::_sendQuitMessage()
{
    Plazza::QuitMessage quit(Plazza::R_Reception);
    quit >> _pipes;
}

void Plazza::Kitchen::_sendPizzaOrders()
{
    while (_cooked.size() > 0) {
        try {
            std::unique_ptr<IPizza> pizza = _cooked.pop();
            Plazza::OrderMessage msg = Plazza::OrderMessage(std::move(pizza), Plazza::R_Reception);
            msg >> _pipes;
            usleep(10000);
        } catch (Plazza::SafeQueueError &e) {
            continue;
        }
    }
}
