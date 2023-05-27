/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** Reception
*/

#include "Reception.hpp"

#include <iostream>

Plazza::Reception::Reception(std::size_t nbCooks, std::size_t timeRestock, double timeMultiplier)
    : _nbCooks(nbCooks), _timeRestock(timeRestock), _timeMultiplier(timeMultiplier), _getLine()
{
}

Plazza::Reception::~Reception()
{
    _getLine.stop();
    for (auto &kitchen : _kitchens) {
        Plazza::Fork &fork = *std::get<0>(kitchen);
        fork.kill();
    }
}

void Plazza::Reception::printKitchenStatuses()
{
    std::cout << "There is " << _kitchens.size() << " kitchens running" << std::endl;
    std::size_t i = 1;
    for (auto &kitchen : _kitchens) {
        Plazza::NamedPipes &pipes = *std::get<1>(kitchen);
        Plazza::StatusMessage msg(Plazza::R_Kitchen);
        msg >> pipes;
        std::string answer;
        while (answer.empty()) {
            pipes >> answer;
            usleep(1000);
        }
        if (Plazza::Message::getTypeFromStr(answer) != Plazza::Status) {
            std::cout << "Got wrong message type, the kitchen closed before getting the status" << std::endl;
            continue;
        }
        std::unique_ptr<Plazza::StatusMessage> status = Plazza::Message::unpack<Plazza::StatusMessage>(answer);
        std::cout << "Kitchen " << i++ << ": " << std::endl;
        std::cout << status->getStatus() << std::endl; 
    }
}

void Plazza::Reception::cookPizzas(std::vector<std::unique_ptr<IPizza>> &pizzas)
{
    std::vector<std::pair<std::size_t, std::size_t>> availability;

    for (std::size_t i = 0; i < _kitchens.size(); i++) {
        auto &kitchen = _kitchens[i];
        Plazza::NamedPipes &pipes = *std::get<1>(kitchen);
        Plazza::StatusMessage msg(Plazza::R_Kitchen);
        msg >> pipes;
        std::string answer;
        while (answer.empty()) {
            pipes >> answer;
            usleep(1000);
        }
        if (Plazza::Message::getTypeFromStr(answer) != Plazza::Status) {
            std::cout << "Got wrong message type, the kitchen closed before getting the status" << std::endl;
            continue;
        }
        std::unique_ptr<Plazza::StatusMessage> status = Plazza::Message::unpack<Plazza::StatusMessage>(answer);
        availability.push_back(std::make_pair(i, status->getAvailability()));
    }

    std::size_t availabilitySum = 0;
    for (auto &pair : availability)
        availabilitySum += pair.second;
    while (availabilitySum < pizzas.size())  {
        if (createKitchen())
            while (1);
        availabilitySum += _nbCooks * 2;
        availability.push_back(std::make_pair(_kitchens.size() - 1, _nbCooks * 2));
    }

    for (auto &pizza : pizzas) {
        std::size_t kitchenIndex = 0;
        for (std::size_t i = 1; i < availability.size(); i++) {
            if (availability[i].second > availability[kitchenIndex].second) {
                kitchenIndex = i;
            }
        }
        auto &kitchen = _kitchens[availability[kitchenIndex].first];
        Plazza::NamedPipes &pipes = *std::get<1>(kitchen);
        Plazza::OrderMessage msg(std::move(pizza), R_Kitchen);
        msg >> pipes;
        availability[kitchenIndex].second--;
        usleep(10000);
    }
    usleep(10000);
}

void Plazza::Reception::processKitchenMessage(std::size_t kitchenIndex, const std::string &msg, std::vector<std::size_t> &toDelete)
{
    Plazza::MessageType type = Plazza::Message::getTypeFromStr(msg);

    switch (type) {
        case Plazza::Quit:
            std::cout << "Kitchen " << kitchenIndex + 1 << " quitted gracefully" << std::endl;
            toDelete.push_back(kitchenIndex);
            break;
        case Plazza::Error:
            {
                std::unique_ptr<Plazza::ErrorMessage> errormsg = Plazza::Message::unpack<Plazza::ErrorMessage>(msg);
                std::cout << "Kitchen " << kitchenIndex + 1 << " encountered an error: " << errormsg->getError() << std::endl;
            }
            break;
        case Plazza::Order:
            {
                std::unique_ptr<Plazza::OrderMessage> order = Plazza::Message::unpack<Plazza::OrderMessage>(msg);
                const std::unique_ptr<Plazza::IPizza> &pizza = order->getPizza();
                std::cout << "Kitchen " << kitchenIndex + 1 << " cooked a " << sizeToString.at(pizza->getSize()) << " "
                << pizzaTypeToString.at(pizza->getType()) << " pizza" << std::endl;
            }
            break;
        default:
            break;
    }
}

void Plazza::Reception::run()
{
    std::string command;

    while (_getLine.isRunning()) {
        std::string incoming;
        std::vector<std::size_t> toDelete;
        for (std::size_t i = 0; i < _kitchens.size(); i++) {
            auto &kitchen = _kitchens[i];
            Plazza::NamedPipes &pipes = *std::get<1>(kitchen);
            pipes >> incoming;
            if (!incoming.empty()) {
                processKitchenMessage(i, incoming, toDelete);
            }
        }
        for (size_t i = toDelete.size(); i > 0; i--) {
            auto maxElement = std::max_element(toDelete.begin(), toDelete.end());
            toDelete.erase(maxElement);
            std::get<0>(_kitchens[*maxElement])->kill();
            std::get<1>(_kitchens[*maxElement]).reset();
            _kitchens.erase(_kitchens.begin() + *maxElement);
        }
        try {
            Parser parser;
            command = _getLine.getCommand();
            if (command.empty()) {
                usleep(10000);
                continue;
            }
            if (parser.checkStatus(command)) {
                printKitchenStatuses();
            } else {
                std::vector<std::unique_ptr<IPizza>> pizzas = parser.checkPizza(command);
                cookPizzas(pizzas);
            }
            usleep(10000);
        } catch (const Plazza::ParseError &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

bool Plazza::Reception::createKitchen()
{
    std::unique_ptr<Fork> fork = std::make_unique<Fork>();
    std::string name = "/tmp/plazza_kitchen_" + std::to_string(_kitchens.size());
    std::string name_in = name + "_in";
    std::string name_out = name + "_out";

    if (fork->isChild()) {
        NamedPipes pipes(name_in, name_out, false);
        std::unique_ptr<Kitchen> kitchen = std::make_unique<Kitchen>(_nbCooks, _timeRestock, _timeMultiplier, pipes);
        return (true);
    } else {
        std::unique_ptr<NamedPipes> pipes = std::make_unique<NamedPipes>(name_in, name_out);
        _kitchens.push_back(std::make_tuple(std::move(fork), std::move(pipes)));
    }
    return (false);
}
