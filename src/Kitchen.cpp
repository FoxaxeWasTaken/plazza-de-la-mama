/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Plazza::Kitchen::Kitchen(std::size_t nbCooks, std::size_t timeRestock, std::size_t timeMultiplier)
    : _clock(), _storage(), _toCook(), _cooked(), _cooks(), _timeRestock(timeRestock)
{
    for (std::size_t i = 0; i < nbCooks; i++)
        _cooks.push_back(Cook(_storage, timeMultiplier, _toCook, _cooked));
    run();
}

Plazza::Kitchen::~Kitchen()
{
}

void Plazza::Kitchen::run()
{
    std::size_t refillTime = 0;
    std::size_t closeTime = 0;
    std::size_t newTime = 0;

    while (true) {
        newTime = _clock.getElapsedTime();
        _clock.restart();
        refillTime += newTime;
        closeTime += newTime;
        for (auto &cook : _cooks) {
            cook.getTime().fetch_add(newTime);
        }
        if (refillTime >= _timeRestock) {
            _storage.refill();
            refillTime -= _timeRestock;
        }
        if (_toCook.size() > 0 || getCookOccupancy() > 0) {
            closeTime = 0;
        } else if (closeTime >= 5) {
            break;
        }
    }
}

std::size_t Plazza::Kitchen::getCookOccupancy()
{
    std::size_t nbCooks = 0;

    for (auto &cook : _cooks) {
        if (cook.isCooking())
            nbCooks++;
    }
    return nbCooks;
}
