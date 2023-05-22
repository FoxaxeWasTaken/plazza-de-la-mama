/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** Message
*/

#pragma once

#include "Pizzas.hpp"
#include "NamedPipes.hpp"

#include <memory>
#include <string>

namespace Plazza {
    enum MessageType {
        None = -1,
        Order,
        Status,
        Error,
        Quit
    };

    class NamedPipes;

    class Message {
        public:
            Message(MessageType type)
                : _type(type)
            {
            }

            ~Message() = default;

            MessageType getType() const
            {
                return _type;
            }

            static MessageType getTypeFromStr(const std::string &str)
            {
                return static_cast<MessageType>(std::stoi(str.substr(0, str.find(';'))));
            }

            virtual std::string pack() const = 0;

            template<typename T>
            static std::unique_ptr<T> unpack(const std::string &str)
            {
                return T::unpack(str);
            }

            void operator>>(NamedPipes &pipes)
            {
                pipes << pack();
            }

        protected:
            MessageType _type;
    };
}
