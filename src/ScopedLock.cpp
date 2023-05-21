/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** ScopedLock
*/

#include "ScopedLock.hpp"

Plazza::ScopedLock::ScopedLock(Mutex &mutex) : _mutex(mutex)
{
    _mutex.lock();
}

Plazza::ScopedLock::~ScopedLock()
{
    _mutex.unlock();
}
