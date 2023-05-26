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
    createKitchen();
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
    std::cout << "There is " << _kitchens.size() << " kitchens" << std::endl;
    std::cout << "Asking them for status" << std::endl;
    for (auto &kitchen : _kitchens) {
        Plazza::NamedPipes &pipes = *std::get<1>(kitchen);
        Plazza::StatusMessage msg("", Plazza::R_Kitchen);
        msg >> pipes;
        std::string answer;
        while (answer.empty()) {
            pipes >> answer;
            usleep(1000);
        }
        std::unique_ptr<Plazza::StatusMessage> status = Plazza::Message::unpack<Plazza::StatusMessage>(answer);
        std::cout << status->getStatus() << std::endl; 
    }
}

void Plazza::Reception::cookPizzas(std::vector<std::unique_ptr<IPizza>> &pizzas)
{
    std::cout << "need to cook " << pizzas.size() << " pizzas" << std::endl;
}

void Plazza::Reception::run()
{
    std::string command;

    while (_getLine.isRunning()) {
        try {
            usleep(10000);
            Parser parser;
            command = _getLine.getCommand();
            if (command.empty()) {
                continue;
            }
            if (parser.checkStatus(command)) {
                printKitchenStatuses();
            } else {
                std::vector<std::unique_ptr<IPizza>> pizzas = parser.checkPizza(command);
                cookPizzas(pizzas);
            }
        } catch (const Plazza::ParseError &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

void Plazza::Reception::createKitchen()
{
    std::unique_ptr<Fork> fork = std::make_unique<Fork>();
    std::string name = "/tmp/plazza_kitchen_" + std::to_string(_kitchens.size());
    std::string name_in = name + "_in";
    std::string name_out = name + "_out";

    if (fork->isChild()) {
        NamedPipes pipes(name_in, name_out, false);
        std::unique_ptr<Kitchen> kitchen = std::make_unique<Kitchen>(_nbCooks, _timeRestock, _timeMultiplier, pipes);
    } else {
        std::unique_ptr<NamedPipes> pipes = std::make_unique<NamedPipes>(name_in, name_out);
        _kitchens.push_back(std::make_tuple(std::move(fork), std::move(pipes)));
    }
}
