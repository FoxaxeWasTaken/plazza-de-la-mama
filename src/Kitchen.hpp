/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** Kitchen
*/

#pragma once

#include "Clock.hpp"
#include "Pizzas.hpp"
#include "Storage.hpp"
#include "Thread.hpp"
#include "SafeQueue.hpp"
#include "Fork.hpp"
#include "Cook.hpp"
#include "NamedPipes.hpp"
#include "Messages.hpp"

namespace Plazza {
    class Kitchen {
        public:
            Kitchen(std::size_t nbCooks, std::size_t timeRestock, double timeMultiplier, NamedPipes &pipes);
            ~Kitchen();
            
            void run();
        private:
            Clock _clock;
            Storage _storage;
            SafeQueue<std::unique_ptr<IPizza>> _toCook;
            SafeQueue<std::unique_ptr<IPizza>> _cooked;
            std::vector<std::unique_ptr<Cook>> _cooks;
            std::size_t _timeRestock;
            std::atomic<bool> _isClosing;
            NamedPipes &_pipes;

            std::size_t _getCookCount() const;
            std::size_t _getCookOccupancy();
            std::size_t _getAvailability();
            void _processMessage(const std::string &msg);
            void _sendQuitMessage();
            void _sendPizzaOrders();
    };
}
