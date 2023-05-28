/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** Main
*/

#include <iostream>
#include "Args.hpp"
#include "Reception.hpp"

int main(int ac, char **av)
{
    Plazza::Args a;
    try {
        a.checkArg(ac, av);
        Plazza::NamedPipes::remove_existing_pipes();
        Plazza::Reception r(a.getNbCooks(), a.getTimeRefill(), a.getMultiplier());
        r.run();
    } catch (Plazza::ArgsError &e) {
        std::cout << e.what() << std::endl;
        return (84);
    } catch (Plazza::Error &e) {
        std::cout << "Unknown error " << e.what() << std::endl;
        return (84);
    }
    return 0;
}
