/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** Storage
*/

#include "Storage.hpp"

Plazza::Storage::Storage(std::size_t maxIngredients)
    : _ingredients(), _maxIngredients(maxIngredients)
{
    refill(maxIngredients);
}

void Plazza::Storage::addIngredient(Ingredients ingredient)
{
    _ingredients[ingredient].fetch_add(1);
}

void Plazza::Storage::removeIngredient(Ingredients ingredient)
{
    _ingredients[ingredient].fetch_sub(1);
}

int Plazza::Storage::getIngredient(Ingredients ingredient) const
{
    return _ingredients[ingredient].load();
}

void Plazza::Storage::setIngredient(Ingredients ingredient, int quantity)
{
    _ingredients[ingredient].store(quantity);
}

bool Plazza::Storage::hasIngredients(std::vector<Ingredients> ingredients) const
{
    for (auto ingredient : ingredients) {
        if (_ingredients[ingredient].load() == 0)
            return false;
    }
    return true;
}

void Plazza::Storage::takeIngredients(std::vector<Ingredients> ingredients)
{
    for (auto ingredient : ingredients) {
        _ingredients[ingredient].fetch_sub(1);
    }
}

void Plazza::Storage::refill(std::size_t nbIngredients)
{
    for (auto &ingredient : _ingredients) {
        if (ingredient.load() < _maxIngredients)
            ingredient.fetch_add(nbIngredients);
    }
}
