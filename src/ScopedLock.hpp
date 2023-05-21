/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** ScopedLock
*/

#pragma once

#include "Mutex.hpp"

namespace Plazza {
    class ScopedLock {
        public:
            ScopedLock(Mutex &mutex);
            ~ScopedLock();
        private:
            Mutex &_mutex;
    };
}
