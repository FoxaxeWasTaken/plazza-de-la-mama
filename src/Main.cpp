/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** Main
*/

#include <iostream>
#include "Args.hpp"

int main(int ac, char **av)
{
    Plazza::Args a;
    try {
        a.checkArg(ac, av);
    } catch (Plazza::ArgsError &e) {
        std::cout << e.what() << std::endl;
        return (84);
    }
    return 0;
}
