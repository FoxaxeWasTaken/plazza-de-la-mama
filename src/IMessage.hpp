/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** IMessage
*/

#pragma once

#include "Pizzas.hpp"

#include <memory>

namespace Plazza {
    enum MessageType {
        Order,
        Status,
        Error,
        Quit
    };

    class IMessage {
        public:
            virtual ~IMessage() = default;
            virtual MessageType getType() const = 0;
    };
}
