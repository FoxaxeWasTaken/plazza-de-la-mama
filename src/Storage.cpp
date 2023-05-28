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
    _ingredients.insert(std::make_pair(Plazza::Doe, maxIngredients));
    _ingredients.insert(std::make_pair(Plazza::Tomato, maxIngredients));
    _ingredients.insert(std::make_pair(Plazza::Gruyere, maxIngredients));
    _ingredients.insert(std::make_pair(Plazza::Ham, maxIngredients));
    _ingredients.insert(std::make_pair(Plazza::Mushrooms, maxIngredients));
    _ingredients.insert(std::make_pair(Plazza::Steak, maxIngredients));
    _ingredients.insert(std::make_pair(Plazza::Eggplant, maxIngredients));
    _ingredients.insert(std::make_pair(Plazza::GoatCheese, maxIngredients));
    _ingredients.insert(std::make_pair(Plazza::ChiefLove, maxIngredients));
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
    return _ingredients.at(ingredient).load();
}

void Plazza::Storage::setIngredient(Ingredients ingredient, int quantity)
{
    _ingredients[ingredient].store(quantity);
}

bool Plazza::Storage::hasIngredients(std::vector<Ingredients> ingredients) const
{
    for (auto ingredient : ingredients) {
        if (_ingredients.at(ingredient).load() <= 0)
            return false;
    }
    return true;
}

bool Plazza::Storage::takeIngredients(std::vector<Ingredients> ingredients)
{
    size_t count = 0;

    for (auto ingredient : ingredients) {
        _ingredients.at(ingredient).fetch_sub(1);
        if (_ingredients.at(ingredient).load() < 0) {
            break;
        }
        count++;
    }
    if (count != ingredients.size()) {
        for (auto ingredient : ingredients) {
            _ingredients.at(ingredient).fetch_add(1);
            if (count == 0) {
                return (false);
            }
            count--;
        }
    }
    return (true);
}

void Plazza::Storage::refill(std::size_t nbIngredients)
{
    for (auto &ingredient : _ingredients) {
        ingredient.second.fetch_add(nbIngredients);
    }
}
