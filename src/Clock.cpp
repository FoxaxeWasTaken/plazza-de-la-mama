/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** Clock
*/

#include "Clock.hpp"

Plazza::Clock::Clock()
    : _start(std::chrono::system_clock::now())
{
}

Plazza::Clock::~Clock()
{
}

double Plazza::Clock::getElapsedTime() const
{
    std::chrono::time_point<std::chrono::system_clock> end;
    std::chrono::duration<double> elapsed_seconds;

    end = std::chrono::system_clock::now();
    elapsed_seconds = end - _start;

    return elapsed_seconds.count();
}

void Plazza::Clock::restart()
{
    _start = std::chrono::system_clock::now();
}
