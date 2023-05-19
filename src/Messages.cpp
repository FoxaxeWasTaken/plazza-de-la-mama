/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** Messages
*/

#include "Messages.hpp"

Plazza::OrderMessage::OrderMessage(std::reference_wrapper<IPizza> pizza, Recipient recipient)
    : _pizza(pizza), _recipient(recipient)
{
}

Plazza::MessageType Plazza::OrderMessage::getType() const
{
    return MessageType::Order;
}

Plazza::IPizza &Plazza::OrderMessage::getPizza() const
{
    return _pizza.get();
}

Plazza::Recipient Plazza::OrderMessage::getRecipient() const
{
    return _recipient;
}

Plazza::StatusMessage::StatusMessage(std::string status)
    : _status(status)
{
}

Plazza::MessageType Plazza::StatusMessage::getType() const
{
    return MessageType::Status;
}

std::string Plazza::StatusMessage::getStatus() const
{
    return _status;
}

Plazza::ErrorMessage::ErrorMessage(std::string error, std::vector<std::reference_wrapper<IPizza>> pizzas)
    : _error(error), _pizzas(pizzas)
{
}

Plazza::MessageType Plazza::ErrorMessage::getType() const
{
    return MessageType::Error;
}

std::string Plazza::ErrorMessage::getError() const
{
    return _error;
}

std::vector<std::reference_wrapper<Plazza::IPizza>> Plazza::ErrorMessage::getPizzas() const
{
    return _pizzas;
}

Plazza::MessageType Plazza::QuitMessage::getType() const
{
    return MessageType::Quit;
}

