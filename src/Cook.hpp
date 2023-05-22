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
            Cook(Storage &storage, double timeMultiplier, SafeQueue<std::unique_ptr<IPizza>> &toCook, SafeQueue<std::unique_ptr<IPizza>> &cooked, std::atomic<bool> &isClosing);
            Cook(Cook &&other);
            ~Cook();

            void run();
            bool isCooking() const;
            void addTime(const double timeAdd);
        private:
            std::atomic<bool> _isCooking;
            Storage &_storage;
            std::unique_ptr<IPizza> _pizza;
            double _timeMultiplier;
            SafeQueue<std::unique_ptr<IPizza>> &_toCook;
            SafeQueue<std::unique_ptr<IPizza>> &_cooked;
            std::atomic<bool> &_isClosing;
            std::atomic<double> _time;
            Thread _thread;
    };
}
