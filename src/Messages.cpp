/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** Messages
*/

#include "Messages.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>

Plazza::OrderMessage::OrderMessage(std::unique_ptr<IPizza> pizza, Recipient recipient)
    : Message(Plazza::MessageType::Order), _pizza(std::move(pizza)), _recipient(recipient)
{
}

const std::unique_ptr<Plazza::IPizza> &Plazza::OrderMessage::getPizza() const
{
    return _pizza;
}

std::string Plazza::OrderMessage::pack() const
{
    std::ostringstream oss;

    oss << std::setw(2) << std::setfill('0') << _type << ";";
    oss << std::setw(2) << std::setfill('0') << _recipient << ";";
    oss << std::setw(2) << std::setfill('0') << _pizza->getType() << ";";
    oss << std::setw(2) << std::setfill('0') << _pizza->getSize();
    return oss.str();
}

std::unique_ptr<Plazza::OrderMessage> Plazza::OrderMessage::unpack(const std::string &str)
{
    std::istringstream iss(str);
    std::string type;
    std::string recipientStr;
    std::string pizzaTypeStr;
    std::string size;
    
    std::getline(iss, type, ';');
    std::getline(iss, recipientStr, ';');
    std::getline(iss, pizzaTypeStr, ';');
    std::getline(iss, size, ';');
    Plazza::PizzaType pizzaType = static_cast<Plazza::PizzaType>(std::stoi(pizzaTypeStr));
    Plazza::Recipient recipient = static_cast<Plazza::Recipient>(std::stoi(recipientStr));
    Plazza::PizzaSize pizzaSize = static_cast<Plazza::PizzaSize>(std::stoi(size));
    std::unique_ptr<Plazza::IPizza> pizza = nullptr;
    switch (pizzaType) {
        case Plazza::PizzaType::Regina:
            pizza = std::make_unique<Plazza::PizzaRegina>(pizzaSize);
            break;
        case Plazza::PizzaType::Margarita:
            pizza = std::make_unique<Plazza::PizzaMargarita>(pizzaSize);
            break;
        case Plazza::PizzaType::Americana:
            pizza = std::make_unique<Plazza::PizzaAmericana>(pizzaSize);
            break;
        case Plazza::PizzaType::Fantasia:
            pizza = std::make_unique<Plazza::PizzaFantasia>(pizzaSize);
            break;
        default:
            break;
    }
    std::unique_ptr<Plazza::OrderMessage> msg = std::make_unique<Plazza::OrderMessage>(std::move(pizza), recipient);
    return msg;
}

Plazza::Recipient Plazza::OrderMessage::getRecipient() const
{
    return _recipient;
}

Plazza::StatusMessage::StatusMessage(std::string status)
    : Message(Plazza::MessageType::Status), _status(status)
{
}

std::string Plazza::StatusMessage::getStatus() const
{
    return _status;
}

std::string Plazza::StatusMessage::pack() const
{
    std::ostringstream oss;

    oss << std::setw(2) << std::setfill('0') << _type << ";" << _status << ";";
    return oss.str();
}

std::unique_ptr<Plazza::StatusMessage> Plazza::StatusMessage::unpack(const std::string &str)
{
    std::istringstream iss(str);
    std::string type;
    std::string status;

    std::getline(iss, type, ';');
    std::getline(iss, status, ';');
    std::unique_ptr<Plazza::StatusMessage> msg = std::make_unique<Plazza::StatusMessage>(status);
    return msg;
}

Plazza::ErrorMessage::ErrorMessage(std::string error, const std::vector<std::shared_ptr<IPizza>> &pizzas)
    : Message(Plazza::MessageType::Error), _error(error), _pizzas(pizzas)
{
}

std::string Plazza::ErrorMessage::getError() const
{
    return _error;
}

std::string Plazza::ErrorMessage::pack() const
{
    std::ostringstream oss;

    oss << std::setw(2) << std::setfill('0') << _type << ";";
    oss << _error << ";";
    oss << std::setw(2) << std::setfill('0') << _pizzas.size() << ";";
    for (auto &pizza : _pizzas) {
        oss << std::setw(2) << std::setfill('0') << pizza->getType() << ";";
        oss << std::setw(4) << std::setfill('0') << pizza->getSize() << ";";
    }
    return oss.str();
}

std::unique_ptr<Plazza::ErrorMessage> Plazza::ErrorMessage::unpack(const std::string &str)
{
    std::istringstream iss(str);
    std::string type;
    std::string error;
    std::string nbPizzas;

    std::getline(iss, type, ';');
    std::getline(iss, error, ';');
    std::getline(iss, nbPizzas, ';');
    std::vector<std::shared_ptr<Plazza::IPizza>> pizzas;
    for (size_t i = 0; i < std::stoul(nbPizzas); i++) {
        std::string pizzaType;
        std::string pizzaSize;

        std::getline(iss, pizzaType, ';');
        std::getline(iss, pizzaSize, ';');
        std::shared_ptr<Plazza::IPizza> pizza = nullptr;
        switch (std::stoi(pizzaType)) {
            case Plazza::PizzaType::Regina:
                pizza = std::make_shared<Plazza::PizzaRegina>(static_cast<Plazza::PizzaSize>(std::stoi(pizzaSize)));
                break;
            case Plazza::PizzaType::Margarita:
                pizza = std::make_shared<Plazza::PizzaMargarita>(static_cast<Plazza::PizzaSize>(std::stoi(pizzaSize)));
                break;
            case Plazza::PizzaType::Americana:
                pizza = std::make_shared<Plazza::PizzaAmericana>(static_cast<Plazza::PizzaSize>(std::stoi(pizzaSize)));
                break;
            case Plazza::PizzaType::Fantasia:
                pizza = std::make_shared<Plazza::PizzaFantasia>(static_cast<Plazza::PizzaSize>(std::stoi(pizzaSize)));
                break;
            default:
                break;
        }
        pizzas.push_back(pizza);
    }
    std::unique_ptr<Plazza::ErrorMessage> msg = std::make_unique<Plazza::ErrorMessage>(error, pizzas);
    return msg;
}

const std::vector<std::shared_ptr<Plazza::IPizza>> &Plazza::ErrorMessage::getPizzas() const
{
    return _pizzas;
}

Plazza::QuitMessage::QuitMessage()
    : Message(Plazza::MessageType::Quit)
{
}

std::string Plazza::QuitMessage::pack() const
{
    std::ostringstream oss;

    oss << std::setw(2) << std::setfill('0') << _type << ";";
    return oss.str();
}
