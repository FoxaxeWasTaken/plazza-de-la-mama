/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** Pizzas
*/

#include "Pizzas.hpp"

Plazza::APizza::APizza(Plazza::PizzaType type, Plazza::PizzaSize size)
{
    _type = type;
    _size = size;
}

Plazza::PizzaType Plazza::APizza::getType() const
{
    return _type;
}

void Plazza::APizza::setType(Plazza::PizzaType type)
{
    _type = type;
}

Plazza::PizzaSize Plazza::APizza::getSize() const
{
    return _size;
}

void Plazza::APizza::setSize(Plazza::PizzaSize size)
{
    _size = size;
}

std::size_t Plazza::APizza::getCookingTime() const
{
    return _cookingTime;
}

Plazza::PizzaMargarita::PizzaMargarita(Plazza::PizzaSize size)
    : APizza(Plazza::Margarita, size)
{
    _ingredients.push_back(Plazza::Doe);
    _ingredients.push_back(Plazza::Tomato);
    _ingredients.push_back(Plazza::Gruyere);
    _cookingTime = cookingTime.at(_type);
}

std::vector<Plazza::Ingredients> Plazza::PizzaMargarita::getIngredients() const
{
    return _ingredients;
}

Plazza::PizzaRegina::PizzaRegina(Plazza::PizzaSize size)
    : APizza(Plazza::Regina, size)
{
    _ingredients.push_back(Plazza::Doe);
    _ingredients.push_back(Plazza::Tomato);
    _ingredients.push_back(Plazza::Gruyere);
    _ingredients.push_back(Plazza::Ham);
    _ingredients.push_back(Plazza::Mushrooms);
    _cookingTime = cookingTime.at(_type);
}

std::vector<Plazza::Ingredients> Plazza::PizzaRegina::getIngredients() const
{
    return _ingredients;
}

Plazza::PizzaAmericana::PizzaAmericana(Plazza::PizzaSize size)
    : APizza(Plazza::Americana, size)
{
    _ingredients.push_back(Plazza::Doe);
    _ingredients.push_back(Plazza::Tomato);
    _ingredients.push_back(Plazza::Gruyere);
    _ingredients.push_back(Plazza::Steak);
    _cookingTime = cookingTime.at(_type);
}

std::vector<Plazza::Ingredients> Plazza::PizzaAmericana::getIngredients() const
{
    return _ingredients;
}

Plazza::PizzaFantasia::PizzaFantasia(Plazza::PizzaSize size)
    : APizza(Plazza::Fantasia, size)
{
    _ingredients.push_back(Plazza::Doe);
    _ingredients.push_back(Plazza::Tomato);
    _ingredients.push_back(Plazza::Eggplant);
    _ingredients.push_back(Plazza::GoatCheese);
    _ingredients.push_back(Plazza::ChiefLove);
    _cookingTime = cookingTime.at(_type);
}

std::vector<Plazza::Ingredients> Plazza::PizzaFantasia::getIngredients() const
{
    return _ingredients;
}
