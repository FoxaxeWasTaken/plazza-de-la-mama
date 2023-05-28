/*
** EPITECH PROJECT, 2023
** Args
** File description:
** Args
*/

#include "Args.hpp"

void Plazza::Args::checkArg(int ac, char **av)
{
    if (ac != 4) {
        throw (Plazza::ArgsError("invalid number of arguments"));
    }
    setMultiplier(av[1]);
    setNbCooks(av[2]);
    setTimeRefill(av[3]);
}

void Plazza::Args::setNbCooks(std::string arg)
{
    std::size_t pos = 0;

    try {
        _nbCooks = std::stoi(arg, &pos);
    } catch (std::exception &e) {
        throw (Plazza::ArgsError("argument (NbCooks) is not a number"));
    }
    if (arg.length() != pos)
        throw (Plazza::ArgsError("argument (NbCooks) is not a number"));
    if (_nbCooks <= 0)
        throw (Plazza::ArgsError("number (NbCooks) is negativ or null"));
}

size_t Plazza::Args::getNbCooks() const
{
    return (_nbCooks);
}

void Plazza::Args::setTimeRefill(std::string arg)
{
    std::size_t pos = 0;

    try {
        _timeRefill = std::stoi(arg, &pos);
    } catch (std::exception &e) {
        throw (Plazza::ArgsError("argument (TimeRefill) is not a number"));
    }
    if (arg.length() != pos)
        throw (Plazza::ArgsError("argument (TimeRefill) is not a number"));
    if (_timeRefill <= 0)
        throw (Plazza::ArgsError("number (TimeRefill) is negativ or null"));
}

size_t Plazza::Args::getTimeRefill() const
{
    return (_timeRefill);
}

void Plazza::Args::setMultiplier(std::string arg)
{
    std::size_t pos = 0;

    try {
        _multiplier = std::stod(arg, &pos);
    } catch (std::exception &e) {
        throw (Plazza::ArgsError("argument (multiplier) is not a number"));
    }
    if (arg.length() != pos)
        throw (Plazza::ArgsError("argument (multiplier) is not a number"));
    if (_multiplier <= 0)
        throw (Plazza::ArgsError("number (multiplier) is negativ or null"));
}

double Plazza::Args::getMultiplier() const
{
    return (_multiplier);
}
