/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** Messages
*/

#pragma once

#include "Message.hpp"

namespace Plazza {
    enum Recipient {
        Kitchen,
        Reception
    };

    class OrderMessage : public Message {
        public:
            OrderMessage(std::unique_ptr<IPizza> pizza, Recipient recipient);
            ~OrderMessage() = default;

            const std::unique_ptr<IPizza> &getPizza() const;
            Recipient getRecipient() const;
            std::string pack() const;
            static std::unique_ptr<OrderMessage> unpack(const std::string &str);
        private:
            std::unique_ptr<IPizza> _pizza;
            Recipient _recipient;
    };
    

    class StatusMessage : public Message {
        public:
            StatusMessage(std::string status);
            ~StatusMessage() = default;

            std::string getStatus() const;
            std::string pack() const;
            static std::unique_ptr<StatusMessage> unpack(const std::string &str);
        private:
            std::string _status;
    };

    class ErrorMessage : public Message {
        public:
            ErrorMessage(std::string error, const std::vector<std::shared_ptr<IPizza>> &pizzas);
            ~ErrorMessage() = default;

            std::string getError() const;
            const std::vector<std::shared_ptr<IPizza>> &getPizzas() const;
            std::string pack() const;
            static std::unique_ptr<ErrorMessage> unpack(const std::string &str);
        private:
            std::string _error;
            std::vector<std::shared_ptr<IPizza>> _pizzas;
    };

    class QuitMessage : public Message {
        public:
            QuitMessage();
            ~QuitMessage() = default;

            std::string pack() const;
            static std::unique_ptr<QuitMessage> unpack(const std::string &str);
    };
}
