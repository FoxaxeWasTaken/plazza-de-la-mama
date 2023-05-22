/*
** EPITECH PROJECT, 2023
** Parser
** File description:
** Parser
*/

#ifndef PARSER_HPP_
    #define PARSER_HPP_

    #include <string>
    #include <regex>
    #include <algorithm>

    #include "Pizzas.hpp"
    #include "Errors.hpp"

namespace Plazza {
    class Parser {
        public:
            Parser() = default;
            ~Parser() = default;

            static bool checkStatus(std::string line);
            static std::vector<std::unique_ptr<Plazza::IPizza>> checkPizza(std::string line);

        private:

    };
}

#endif /* !PARSER_HPP_ */
