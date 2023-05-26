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

Plazza::Kitchen::~Kitchen()
{
}

void Plazza::Kitchen::run()
{
    double refillTime = 0;
    double closeTime = 0;
    double newTime;

    while (_isClosing.load() == false) {
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
        if (_toCook.size() > 0 || getCookOccupancy() > 0) {
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
}

void Plazza::Kitchen::_processMessage(const std::string &msg)
{
    Plazza::MessageType type = Plazza::Message::getTypeFromStr(msg);

    if (type == Plazza::MessageType::Status) {
        std::ostringstream oss;
        oss << "\t" << "Pizzas in queue: " << _toCook.size() << std::endl;
        oss << "\t" << "Pizzas cooking: " << getCookOccupancy() << std::endl;
        oss << "\t" << "Can cook " << getAvailability() << " pizzas" << std::endl;
        oss << "\t" << "Ingredients: ";
        int ingredient = 1;
        while (ingredient <= 256) {
            Ingredients casted = static_cast<Ingredients>(ingredient);
            oss << " " << ingredientsMap.at(casted) << ": " << _storage.getIngredient(casted);
            ingredient *= 2;
        }
        Plazza::StatusMessage status(oss.str(), Plazza::R_Reception);
        status >> _pipes;
    }
}



std::size_t Plazza::Kitchen::getCookOccupancy()
{
    std::size_t nbCooks = 0;

    for (auto &cook : _cooks) {
        if (cook->isCooking())
            nbCooks++;
    }
    return nbCooks;
}

std::size_t Plazza::Kitchen::getAvailability()
{
    int pizzasInQueue = _toCook.size();
    int pizzasCooking = getCookOccupancy();
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
