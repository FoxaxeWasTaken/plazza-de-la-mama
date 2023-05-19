/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** Storage
*/

#include "Storage.hpp"

Plazza::Storage::Storage()
{
    _ingredients.fill(5);
}

void Plazza::Storage::addIngredient(Ingredients ingredient)
{
    _ingredients[ingredient] += 1;
}

void Plazza::Storage::removeIngredient(Ingredients ingredient)
{
    _ingredients[ingredient] -= 1;
}

int Plazza::Storage::getIngredient(Ingredients ingredient) const
{
    return _ingredients[ingredient];
}

void Plazza::Storage::setIngredient(Ingredients ingredient, int quantity)
{
    _ingredients[ingredient] = quantity;
}

bool Plazza::Storage::hasIngredients(std::vector<Ingredients> ingredients) const
{
    for (auto ingredient : ingredients) {
        if (_ingredients[ingredient] == 0)
            return false;
    }
    return true;
}

void Plazza::Storage::takeIngredients(std::vector<Ingredients> ingredients)
{
    for (auto ingredient : ingredients) {
        _ingredients[ingredient] -= 1;
    }
}

void Plazza::Storage::refill()
{
    for (auto &ingredient : _ingredients) {
        if (ingredient < 5)
            ingredient += 1;
    }
}
