/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** Pizzas
*/

#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>

#include "Ingredients.hpp"

namespace Plazza {

    enum PizzaType {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };

    const std::map<PizzaType, std::string> pizzaTypeToString = {
        {Plazza::Regina, "Regina"},
        {Plazza::Margarita, "Margarita"},
        {Plazza::Americana, "Americana"},
        {Plazza::Fantasia, "Fantasia"}
    };

    const std::map<Plazza::PizzaType, std::size_t> cookingTime = {
        {Plazza::Regina, 2},
        {Plazza::Margarita, 1},
        {Plazza::Americana, 2},
        {Plazza::Fantasia, 4}
    };

    enum PizzaSize {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    const std::map<std::string , PizzaSize> stringToSize = {
        {"S", PizzaSize::S},
        {"M", PizzaSize::M},
        {"L", PizzaSize::L},
        {"XL", PizzaSize::XL},
        {"XXL", PizzaSize::XXL}
    };

    const std::map<PizzaSize, std::string> sizeToString = {
        {PizzaSize::S, "S"},
        {PizzaSize::M, "M"},
        {PizzaSize::L, "L"},
        {PizzaSize::XL, "XL"},
        {PizzaSize::XXL, "XXL"}
    };

    class IPizza {
        public:
            virtual std::vector<Ingredients> getIngredients() const = 0;
            virtual PizzaType getType() const = 0;
            virtual PizzaSize getSize() const = 0;
            virtual std::size_t getCookingTime() const = 0;

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
            std::size_t getCookingTime() const;
        protected:
            PizzaType _type;
            PizzaSize _size;
            std::size_t _cookingTime;
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

    const std::map<std::string, std::function<std::unique_ptr<Plazza::IPizza >(PizzaSize)>> pizzaFactory = {
        {"regina", [](PizzaSize size) {return (std::make_unique<Plazza::PizzaRegina>(size));}},
        {"margarita", [](PizzaSize size) {return (std::make_unique<Plazza::PizzaMargarita>(size));}},
        {"americana", [](PizzaSize size) {return (std::make_unique<Plazza::PizzaAmericana>(size));}},
        {"fantasia", [](PizzaSize size) {return (std::make_unique<Plazza::PizzaFantasia>(size));}}
    };
}
