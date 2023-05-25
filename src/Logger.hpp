/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** Logger
*/

#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace Plazza {
    class Logger {
        public:
            Logger();
            ~Logger();

            static void log(const std::string &message, const std::string &file = "");
            static void log(const std::vector<std::string> &messages, const std::string &file = "");
    };
} 