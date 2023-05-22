/*
** EPITECH PROJECT, 2023
** Args
** File description:
** Args
*/

#ifndef ARGS_HPP_
    #define ARGS_HPP_

    #include "Errors.hpp"

namespace Plazza {

    enum typeArg{
        Double,
        Int
    };

    class Args {
        public:
            Args() = default;
            ~Args() = default;

            void checkArg(int ac, char **av);

            void setNbCooks(std::string arg);
            size_t getNbCooks() const;
            void setTimeRefill(std::string arg);
            size_t getTimeRefill() const;
            void setMultiplier(std::string arg);
            double getMultiplier() const;

        private:
            int _nbCooks;
            int _timeRefill;
            double _multiplier;
    };
}

#endif /* !ARGS_HPP_ */
