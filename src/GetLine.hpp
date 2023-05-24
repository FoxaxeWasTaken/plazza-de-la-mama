/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** GetLine
*/

#pragma once

#include <iostream>
#include <atomic>
#include "SafeQueue.hpp"
#include "Mutex.hpp"
#include "Thread.hpp"

namespace Plazza
{
    class GetLine {
        public:
            GetLine();
            ~GetLine();
            void getLine();
            void stop();
            std::string getCommand();
            bool isRunning() const;
        private:
            SafeQueue<std::string> _commands;
            std::atomic<bool> _running;
            Thread _thread;
    };
}
