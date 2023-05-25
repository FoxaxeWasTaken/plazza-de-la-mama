/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** SafeQueue
*/

#pragma once

#include <queue>
#include <iostream>
#include "Errors.hpp"
#include "Mutex.hpp"
#include "ScopedLock.hpp"
#include "ConditionalVariable.hpp"

namespace Plazza {
    template<typename T>
    class SafeQueue {
        public:
            SafeQueue() : _queue(), _mutex() {}
            ~SafeQueue() = default;

            void push(T &element)
            {
                ScopedLock lock(_mutex);
                _queue.push(std::move(element));
            }

            T pop()
            {
                ScopedLock lock(_mutex);
                if (_queue.empty()) {
                    throw Plazza::SafeQueueError("Queue is empty");
                }
                T element = std::move(_queue.front());
                _queue.pop();
                return element;
            }

            bool empty()
            {
                ScopedLock lock(_mutex);
                return _queue.empty();
            }

            size_t size()
            {
                ScopedLock lock(_mutex);
                return _queue.size();
            }

        private:
            std::queue<T> _queue;
            Mutex _mutex;
    };
}
