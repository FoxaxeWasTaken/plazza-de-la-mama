/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** Cooks
*/

#include "Cook.hpp"

Plazza::Cook::Cook(Plazza::Storage &storage, double timeMultiplier, Plazza::SafeQueue<std::unique_ptr<IPizza>> &toCook, Plazza::SafeQueue<std::unique_ptr<IPizza>> &cooked, std::atomic<bool> &isClosing)
    : _isCooking(false),
      _storage(storage),
      _pizza(nullptr),
      _timeMultiplier(timeMultiplier),
      _toCook(toCook),
      _cooked(cooked),
      _isClosing(isClosing),
      _time(0),
      _thread(&Cook::run, this)
{

}

Plazza::Cook::~Cook()
{
    _thread.join();
}

void Plazza::Cook::run()
{
    std::size_t timeNeeded = 0;

    while (!_isClosing.load()) {
        if (_toCook.size() == 0)
            continue;
        _pizza = _toCook.pop();
        _isCooking = true;
        while (_storage.hasIngredients(_pizza->getIngredients()) == false);
        _storage.takeIngredients(_pizza->getIngredients());
        timeNeeded = _pizza.get()->getCookingTime() * _timeMultiplier;
        while (_time < timeNeeded);
        _cooked.push(_pizza);
        _isCooking = false;
    }
}

bool Plazza::Cook::isCooking() const
{
    return _isCooking.load();
}

std::atomic<std::size_t> &Plazza::Cook::getTime()
{
    return _time;
}

Plazza::Cook::Cook(Cook&& other)
    : _isCooking(other._isCooking.load()),
      _storage(other._storage),
      _pizza(std::move(other._pizza)),
      _timeMultiplier(other._timeMultiplier),
      _toCook(other._toCook),
      _cooked(other._cooked),
      _isClosing(other._isClosing),
      _time(other._time.load()),
      _thread(std::move(other._thread))
{
}