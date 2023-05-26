/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** Reception
*/

#pragma once

#include "Kitchen.hpp"
#include "GetLine.hpp"
#include "Parser.hpp"

#include <vector>

namespace Plazza {
    class Reception {
        private:
            std::size_t _nbCooks;
            std::size_t _timeRestock;
            double _timeMultiplier;
            GetLine _getLine;
            std::vector<std::tuple<std::unique_ptr<Fork>, std::unique_ptr<NamedPipes>>> _kitchens;

            /**
             * @brief Prints all of the kitchen statuses
            */
            void printKitchenStatuses();

            /**
             * @brief Cooks the pizzas
             * @param pizzas The pizzas to cook
            */
            void cookPizzas(std::vector<std::unique_ptr<IPizza>> &pizzas);

            /**
             * @brief Process messages from the kitchens
             * @param msg The message to process
            */
            void processKitchenMessage(std::size_t kitchenIndex, const std::string &msg, std::vector<std::size_t> &toDelete);

        public:
            /**
             * @brief Construct a new Reception object
             * @param nbCooks The number of cooks in the kitchen
             * @param timeRestock The time it takes to restock the ingredients
             * @param timeMultiplier The time multiplier for the pizzas
            */
            Reception(std::size_t nbCooks, std::size_t timeRestock, double timeMultiplier);

            /**
             * @brief Destroy the Reception object
            */
            ~Reception();

            /**
             * @brief Runs the reception
            */
            void run();

            /**
             * @brief Creates a new kitchen
             */
            void createKitchen();
    };
}