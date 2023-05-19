/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** Fork
*/

#pragma once

#include <unistd.h>
#include <sys/wait.h>

namespace Plazza {
    class Fork {
        public:
            Fork();
            ~Fork();
            void fork();
            void wait();
            bool isChild() const;
            bool isParent() const;
            pid_t getPid() const;

        private:
            pid_t _pid;
    };
}
