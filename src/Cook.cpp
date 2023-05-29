/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** Cooks
*/

#include "Cook.hpp"

Plazza::Cook::Cook(Storage & storage, double timeMultiplier, Plazza::SafeQueue<std::unique_ptr<IPizza>> &toCook, Plazza::SafeQueue<std::unique_ptr<IPizza>> &cooked, std::atomic<bool> &isClosing)
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
    std::size_t startTime = 0;
    sleep(1);

    while (!_isClosing.load()) {
        if (_toCook.size() > 0) {
            try {
                _pizza = _toCook.pop();
            } catch (Plazza::SafeQueueError &e) {
                continue;
            }
        } else {
            usleep(1000);
            continue;
        }
        _isCooking = true;
        while (_storage.takeIngredients(_pizza->getIngredients()) == false) {
            usleep(1000);
        }
        timeNeeded = _pizza.get()->getCookingTime() * _timeMultiplier;
        startTime = _time.load();
        while (_time.load() - startTime < timeNeeded) {
            usleep(1000);
        }
        _cooked.push(_pizza);
        _isCooking = false;
    }
}

bool Plazza::Cook::isCooking() const
{
    return _isCooking.load();
}

void Plazza::Cook::addTime(const double timeAdd)
{
    _time.store(_time.load() + timeAdd);
}
