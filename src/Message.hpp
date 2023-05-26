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
    enum Recipient {
        R_Kitchen,
        R_Reception
    };

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
            Message(MessageType type, Recipient recipient)
                : _type(type), _recipient(recipient)
            {
            }

            ~Message() = default;

            MessageType getType() const
            {
                return _type;
            }

            Recipient getRecipient() const
            {
                return _recipient;
            }

            static MessageType getTypeFromStr(const std::string &str)
            {
                return static_cast<MessageType>(std::stoi(str.substr(0, str.find(';'))));
            }

            static Recipient getRecipientFromStr(const std::string &str)
            {
                return static_cast<Recipient>(std::stoi(str.substr(str.find(';') + 2)));
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
            Recipient _recipient;
    };
}
