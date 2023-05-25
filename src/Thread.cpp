/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** Thread
*/

#include "Thread.hpp"

Plazza::Thread::~Thread()
{
    if (isJoinable())
        pthread_detach(_thread);
}

void Plazza::Thread::join()
{
    pthread_join(_thread, nullptr);
}

void Plazza::Thread::detach()
{
    pthread_detach(_thread);
}

bool Plazza::Thread::isJoinable() const
{
    return pthread_tryjoin_np(_thread, nullptr) == 0;
}

bool Plazza::Thread::isRunning() const
{
    return pthread_kill(_thread, 0) == 0;
}

Plazza::Thread::Thread(Thread&& other)
    : _thread(other._thread)
{
    other._thread = 0;
}

void Plazza::Thread::cancel()
{
    pthread_cancel(_thread);
}
