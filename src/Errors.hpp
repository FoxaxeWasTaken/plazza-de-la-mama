/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** Errors
*/

#pragma once

#include <exception>
#include <string>

namespace Plazza {
    class Error : public std::exception {
        public:
            Error() = default;

        protected:
            std::string _message;
    };

    class SafeQueueError : public Error {
        public:
            SafeQueueError(std::string const &message) {_message = "SafeQueueError: " + message;}
            const char *what() const noexcept override {return _message.c_str();}
    };

    class ArgsError : public Error {
        public:
            ArgsError(std::string const &message) {_message = "ArgsError: " + message;}
            const char *what() const noexcept override {return _message.c_str();}
    };

    class ParseError : public Error {
        public:
            ParseError(std::string const &message) {_message = "ParseError: " + message;}
            const char *what() const noexcept override {return _message.c_str();}
    };

    class NamedPipesError : public Error {
        public:
            NamedPipesError(std::string const &message) {_message = "NamedPipesError: " + message;}
            const char *what() const noexcept override {return _message.c_str();}
    };
}
