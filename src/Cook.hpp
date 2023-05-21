/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** Cooks
*/

#pragma once

#include "Clock.hpp"
#include "Pizzas.hpp"
#include "Storage.hpp"
#include "Thread.hpp"
#include "SafeQueue.hpp"

namespace Plazza {
    class Cook {
        public:
            Cook(Storage &storage, std::size_t timeMultiplier, SafeQueue<std::unique_ptr<IPizza>> &toCook, SafeQueue<std::unique_ptr<IPizza>> &cooked);
            ~Cook();

            void run();
            bool isCooking() const;
            std::atomic<std::size_t> &getTime();
        private:
            bool _isCooking;
            Storage &_storage;
            std::unique_ptr<IPizza> _pizza;
            Thread _thread;
            std::size_t _timeMultiplier;
            SafeQueue<std::unique_ptr<IPizza>> &_toCook;
            SafeQueue<std::unique_ptr<IPizza>> &_cooked;
            bool _isClosing;
            std::atomic<std::size_t> _time;
    };
}
