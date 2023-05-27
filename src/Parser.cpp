/*
** EPITECH PROJECT, 2023
** Parse
** File description:
** Parser
*/

#include "Parser.hpp"
#include <iostream>

bool Plazza::Parser::checkStatus(std::string line)
{
    if (std::regex_match(line, std::regex("\\s*status\\s*"))) {
        return (true);
    }
    return (false);
}

std::vector<std::unique_ptr<Plazza::IPizza>> Plazza::Parser::checkPizza(std::string line)
{
    std::vector<std::unique_ptr<Plazza::IPizza>> pizzas;
    std::regex regexPattern("\\s*([a-zA-Z]+)\\s*(S|M|L|XL|XXL)\\s*(x[1-9][0-9]*)\\s*");

    if (std::regex_match(line, std::regex("^\\s*([a-zA-Z]+)\\s*(S|M|L|XL|XXL)\\s*(x[1-9][0-9]*)\\s*(;\\s*([a-zA-Z]+)\\s*(S|M|L|XL|XXL)\\s*(x[1-9][0-9]*)\\s*)*$"))) {
        std::sregex_iterator iter(line.begin(), line.end(), regexPattern);
        std::sregex_iterator end;

        while (iter != end) {
            std::smatch match = *iter;
            std::string name(match[1]);
            std::transform(name.cbegin(), name.cend(), name.begin(), [](unsigned char c){return (std::tolower(c));});
            size_t nbPizza = std::stoi(std::string(match[3]).substr(1));
            for (size_t count = 0; count < nbPizza; count++) {
                if (pizzaFactory.find(name) == pizzaFactory.end()) {
                    throw (Plazza::ParseError("Invalid pizza name " + std::string(match[1])));
                }
                pizzas.emplace_back(std::move(pizzaFactory.find(name)->second(stringToSize.find(std::string(match[2]))->second)));
            }
            ++iter;
        }
        return (pizzas);
    }
    throw (Plazza::ParseError("Command invalid"));
}
