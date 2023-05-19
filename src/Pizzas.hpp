/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** Pizzas
*/

#pragma once

#include <string>
#include <vector>

#include "Ingredients.hpp"

namespace Plazza {
    enum PizzaType {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };

    enum PizzaSize {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    class IPizza {
        public:
            virtual std::vector<Ingredients> getIngredients() const = 0;
            virtual PizzaType getType() const = 0;
            virtual PizzaSize getSize() const = 0;

            virtual ~IPizza() = default;
    };

    class APizza : public IPizza {
        public:
            APizza(PizzaType type, PizzaSize size);
            ~APizza() = default;

            virtual std::vector<Ingredients> getIngredients() const = 0;
            PizzaType getType() const;
            void setType(PizzaType type);
            PizzaSize getSize() const;
            void setSize(PizzaSize size);
        protected:
            PizzaType _type;
            PizzaSize _size;
    };

    class PizzaMargarita : public APizza {
        public:
            PizzaMargarita(PizzaSize size);
            ~PizzaMargarita() = default;

            std::vector<Ingredients> getIngredients() const override;
        private:
            std::vector<Ingredients> _ingredients;
    };

    class PizzaRegina : public APizza {
        public:
            PizzaRegina(PizzaSize size);
            ~PizzaRegina() = default;

            std::vector<Ingredients> getIngredients() const override;
        private:
            std::vector<Ingredients> _ingredients;
    };

    class PizzaAmericana : public APizza {
        public:
            PizzaAmericana(PizzaSize size);
            ~PizzaAmericana() = default;

            std::vector<Ingredients> getIngredients() const override;
        private:
            std::vector<Ingredients> _ingredients;
    };

    class PizzaFantasia : public APizza {
        public:
            PizzaFantasia(PizzaSize size);
            ~PizzaFantasia() = default;

            std::vector<Ingredients> getIngredients() const override;
        private:
            std::vector<Ingredients> _ingredients;
    };
}
