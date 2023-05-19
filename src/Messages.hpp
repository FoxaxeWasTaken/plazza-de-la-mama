/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** Messages
*/

#pragma once

#include "IMessage.hpp"

namespace Plazza {
    enum Recipient {
        Kitchen,
        Reception
    };

    class OrderMessage : public IMessage {
        public:
            OrderMessage(std::reference_wrapper<IPizza> pizza, Recipient recipient);
            ~OrderMessage() = default;

            MessageType getType() const override;
            IPizza &getPizza() const;
            Recipient getRecipient() const;
        private:
            std::reference_wrapper<IPizza> _pizza;
            Recipient _recipient;
    };

    class StatusMessage : public IMessage {
        public:
            StatusMessage(std::string status);
            ~StatusMessage() = default;

            MessageType getType() const override;
            std::string getStatus() const;
        private:
            std::string _status;
    };

    class ErrorMessage : public IMessage {
        public:
            ErrorMessage(std::string error, std::vector<std::reference_wrapper<IPizza>> pizzas);
            ~ErrorMessage() = default;

            MessageType getType() const override;
            std::string getError() const;
            std::vector<std::reference_wrapper<IPizza>> getPizzas() const;
        private:
            std::string _error;
            std::vector<std::reference_wrapper<IPizza>> _pizzas;
    };

    class QuitMessage : public IMessage {
        public:
            QuitMessage() = default;
            ~QuitMessage() = default;

            MessageType getType() const override;
    };
}
