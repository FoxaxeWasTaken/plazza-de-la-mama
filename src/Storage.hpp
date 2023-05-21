/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** Storage
*/

#pragma once

#include <array>
#include <vector>
#include <atomic>

#include "Ingredients.hpp"

namespace Plazza {
    class Storage {
        public:
            Storage(std::size_t maxIngredients = 5);
            ~Storage() = default;

            void addIngredient(Ingredients ingredient);
            void removeIngredient(Ingredients ingredient);
            int getIngredient(Ingredients ingredient) const;
            void setIngredient(Ingredients ingredient, int quantity);
            bool hasIngredients(std::vector<Ingredients> ingredients) const;
            void takeIngredients(std::vector<Ingredients> ingredients);
            void refill(std::size_t nbIngredients = 1);
        private:
            std::array<std::atomic<std::size_t>, 9> _ingredients;
            std::size_t _maxIngredients;
    };
}
