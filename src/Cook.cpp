/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** Cooks
*/

#include "Cook.hpp"

Plazza::Cook::Cook(Plazza::Storage &storage, std::size_t timeMultiplier, Plazza::SafeQueue<std::unique_ptr<IPizza>> &toCook, Plazza::SafeQueue<std::unique_ptr<IPizza>> &cooked)
    : _isCooking(false), _storage(storage), _pizza(nullptr), _timeMultiplier(timeMultiplier), _toCook(toCook), _cooked(cooked), _isClosing(false)
{
    _thread = Thread(run, std::ref(*this));
}

static void run(Plazza::Cook &cook)
{
    cook.run();
}

Plazza::Cook::~Cook()
{
    _isClosing = true;
    _thread.join();
}

void Plazza::Cook::run()
{
    std::size_t timeNeeded = 0;

    while (!_isClosing) {
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
    return _isCooking;
}

std::atomic<std::size_t> &Plazza::Cook::getTime()
{
    return _time;
}
