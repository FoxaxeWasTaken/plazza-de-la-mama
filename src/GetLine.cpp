/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** GetLine
*/

#include "GetLine.hpp"

Plazza::GetLine::GetLine()
    : _commands(), _running(true), _thread(&GetLine::getLine, this)
{
}

Plazza::GetLine::~GetLine()
{
    _running = false;
    _thread.join();
}

void Plazza::GetLine::getLine()
{
    std::string command = "";

    while (_running) {
        std::getline(std::cin, command);
        _commands.push(command);
    }
}

void Plazza::GetLine::stop()
{
    _running = false;
}

std::string Plazza::GetLine::getCommand()
{
    std::string command;

    if (!_commands.empty()) {
        command = _commands.pop();
    }
    return command;
}

bool Plazza::GetLine::isRunning() const
{
    return _running;
}
