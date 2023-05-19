/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** Storage
*/

#pragma once

#include <array>
#include <vector>

#include "Ingredients.hpp"

namespace Plazza {
    class Storage {
        public:
            Storage();
            ~Storage() = default;

            void addIngredient(Ingredients ingredient);
            void removeIngredient(Ingredients ingredient);
            int getIngredient(Ingredients ingredient) const;
            void setIngredient(Ingredients ingredient, int quantity);
            bool hasIngredients(std::vector<Ingredients> ingredients) const;
            void takeIngredients(std::vector<Ingredients> ingredients);
            void refill();
        private:
            std::array<std::size_t, 9> _ingredients;
    };
}
