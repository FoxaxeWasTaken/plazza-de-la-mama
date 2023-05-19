/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** Thread
*/

#pragma once

#include <pthread.h>
#include <functional>
#include <iostream>
#include <memory>
#include <csignal>

namespace Plazza {
    class Thread {
        public:
            template<typename Function, typename... Args>
            Thread(Function&& f, Args&&... args) {
                auto callable = std::bind(std::forward<Function>(f), std::forward<Args>(args)...);
                auto threadFunc = [](void* arg) -> void* {
                    auto* func = static_cast<decltype(callable)*>(arg);
                    (*func)();
                    delete func;
                    return nullptr;
                };
                auto* func = new decltype(callable)(std::move(callable));
                pthread_create(&_thread, nullptr, threadFunc, func);
            }   
            ~Thread();
            void join();
            void detach();
            bool isJoinable() const;
            bool isDetached() const;
            bool isRunning() const;

        private:
            pthread_t _thread;
            std::function<void(void)> _func;
    };
}
