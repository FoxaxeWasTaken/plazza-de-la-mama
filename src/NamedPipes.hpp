/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** NamedPipes
*/

#pragma once

#include <string>

#include "Errors.hpp"

namespace Plazza {
    class NamedPipes {
        private:
            std::string _inName;
            std::string _outName;
            int _inFd;
            int _outFd;
            bool _isParent;

            /**
             * @brief Create the pipes
            */
            void createPipes();

            /**
             * @brief Open the pipes according to the process
            */
            void openPipes();

            /**
             * @brief Close the pipes
            */
            void closePipes();
        
        public:
            NamedPipes(std::string inName, std::string outName, bool isParent = true);
            ~NamedPipes();

            void operator>>(std::string &str);
            void operator<<(const std::string &str);
    };
}
