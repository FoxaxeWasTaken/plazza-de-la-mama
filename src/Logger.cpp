/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama [WSL: Ubuntu]
** File description:
** Logger
*/

#include "Logger.hpp"

static const std::string LOG_FILE = "plazza.log";

Plazza::Logger::Logger()
{
}

Plazza::Logger::~Logger()
{
}

void Plazza::Logger::log(const std::string &message, const std::string &file)
{
    std::ofstream logFile;
    std::string usedFile = file.empty() ? LOG_FILE : file;

    logFile.open(usedFile, std::ios_base::app);
    if (logFile.is_open()) {
        logFile << message << std::endl;
        logFile.close();
    }
}

void Plazza::Logger::log(const std::vector<std::string> &messages, const std::string &file)
{
    std::ofstream logFile;
    std::string usedFile = file.empty() ? LOG_FILE : file;

    logFile.open(usedFile, std::ios_base::app);
    if (logFile.is_open()) {
        for (const auto &message : messages)
            logFile << message << std::endl;
        logFile.close();
    }
}