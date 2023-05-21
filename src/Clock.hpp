/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** Clock
*/

#pragma once

#include <chrono>

namespace Plazza {
    class Clock {
        public:
            Clock();
            ~Clock();
            double getElapsedTime() const;
            void restart();
        private:
            std::chrono::time_point<std::chrono::system_clock> _start;
    };
}
