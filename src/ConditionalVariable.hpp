/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** ConditionalVariable
*/

#pragma once

#include <pthread.h>

namespace Plazza {
    class ConditionalVariable {
        public:
            ConditionalVariable();
            ~ConditionalVariable();

            void wait();
            void signal();
            void broadcast();
        private:
            pthread_cond_t _cond;
            pthread_mutex_t _mutex;
    };
}
