/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** Fork
*/

#include "Fork.hpp"

Plazza::Fork::Fork()
{
    _pid = 0;
}

Plazza::Fork::~Fork()
{
}

void Plazza::Fork::fork()
{
    _pid = ::fork();
}

void Plazza::Fork::wait()
{
    int status = 0;

    waitpid(_pid, &status, 0);
}

bool Plazza::Fork::isChild() const
{
    return _pid == 0;
}

bool Plazza::Fork::isParent() const
{
    return _pid != 0;
}

pid_t Plazza::Fork::getPid() const
{
    return _pid;
}
