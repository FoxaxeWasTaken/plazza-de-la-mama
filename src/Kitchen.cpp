/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Plazza::Kitchen::Kitchen(std::size_t nbCooks, std::size_t timeRestock, double timeMultiplier)
    : _clock(), _storage(), _toCook(), _cooked(), _cooks(), _timeRestock(timeRestock), _isClosing(false)
{
    for (std::size_t i = 0; i < nbCooks; i++)
        _cooks.emplace_back(_storage, timeMultiplier, _toCook, _cooked, _isClosing);
    run();
}

Plazza::Kitchen::~Kitchen()
{
}

void Plazza::Kitchen::run()
{
    double refillTime = 0;
    double closeTime = 0;
    double newTime;

    while (true) {
        newTime = _clock.getElapsedTime();
        _clock.restart();
        refillTime += newTime * 1000;
        closeTime += newTime;
        for (auto &cook : _cooks) {
            cook.getTime().fetch_add(newTime);
        }
        if (refillTime >= static_cast<double>(_timeRestock)) {
            _storage.refill();
            refillTime -= static_cast<double>(_timeRestock);
        }
        if (_toCook.size() > 0 || getCookOccupancy() > 0) {
            closeTime = 0;
        } else if (closeTime >= 5) {
            _isClosing.store(true);
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
