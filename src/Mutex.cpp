/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** Mutex
*/

#include "Mutex.hpp"

Plazza::Mutex::Mutex()
{
    pthread_mutex_init(&_mutex, nullptr);
}

Plazza::Mutex::~Mutex()
{
    pthread_mutex_destroy(&_mutex);
}

void Plazza::Mutex::lock()
{
    pthread_mutex_lock(&_mutex);
}

void Plazza::Mutex::unlock()
{
    pthread_mutex_unlock(&_mutex);
}

bool Plazza::Mutex::trylock()
{
    return pthread_mutex_trylock(&_mutex) == 0;
}
