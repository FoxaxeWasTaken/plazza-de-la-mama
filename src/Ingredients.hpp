/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** Ingredients
*/

#pragma once

#include <map>
#include <string>

namespace Plazza {
    enum Ingredients {
        Doe = 1,
        Tomato = 2,
        Gruyere = 4,
        Ham = 8,
        Mushrooms = 16,
        Steak = 32,
        Eggplant = 64,
        GoatCheese = 128,
        ChiefLove = 256
    };

    static const std::map<Ingredients, std::string> ingredientsMap = {
        {Doe, "Doe"},
        {Tomato, "Tomato"},
        {Gruyere, "Gruyere"},
        {Ham, "Ham"},
        {Mushrooms, "Mushrooms"},
        {Steak, "Steak"},
        {Eggplant, "Eggplant"},
        {GoatCheese, "GoatCheese"},
        {ChiefLove, "ChiefLove"}
    };
}
