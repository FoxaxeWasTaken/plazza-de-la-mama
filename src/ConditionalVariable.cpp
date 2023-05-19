/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** ConditionalVariable
*/

#include "ConditionalVariable.hpp"

Plazza::ConditionalVariable::ConditionalVariable()
{
    pthread_cond_init(&_cond, nullptr);
    pthread_mutex_init(&_mutex, nullptr);
}

Plazza::ConditionalVariable::~ConditionalVariable()
{
    pthread_cond_destroy(&_cond);
    pthread_mutex_destroy(&_mutex);
}

void Plazza::ConditionalVariable::wait()
{
    pthread_cond_wait(&_cond, &_mutex);
}

void Plazza::ConditionalVariable::signal()
{
    pthread_cond_signal(&_cond);
}

void Plazza::ConditionalVariable::broadcast()
{
    pthread_cond_broadcast(&_cond);
}
