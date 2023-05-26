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
    if (_thread.isJoinable()) {
        _thread.join();
    } else {
        _thread.cancel();
    }
}

void Plazza::GetLine::getLine()
{
    std::string command;

    while (_running) {
        std::getline(std::cin, command);
        if (std::cin.eof() || command == "exit") {
            command = "exit";
            _running = false;
        }
        _commands.push(command);
        usleep(10000);
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
