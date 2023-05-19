/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** Mutex
*/

#pragma once

#include <pthread.h>

namespace Plazza {
    class Mutex {
        public:
            Mutex();
            ~Mutex();

            void lock();
            void unlock();
            bool trylock();
        private:
            pthread_mutex_t _mutex;
    };
}
