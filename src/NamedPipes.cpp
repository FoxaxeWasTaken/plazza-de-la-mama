/*
** EPITECH PROJECT, 2023
** plazza-de-la-mama
** File description:
** NamedPipes
*/

#include "NamedPipes.hpp"

#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>

Plazza::NamedPipes::NamedPipes(std::string inName, std::string outName, bool isParent)
    : _inName(inName), _outName(outName), _inFd(-1), _outFd(-1), _isParent(isParent)
{
    if (_inName.find("/tmp/plazza") != 0 || _outName.find("/tmp/plazza") != 0) {
        throw NamedPipesError("invalid pipe name");
    }
    if (isParent)
        createPipes();
    openPipes();
}

Plazza::NamedPipes::~NamedPipes()
{
    closePipes();
}

void Plazza::NamedPipes::createPipes()
{
    if (mkfifo(_inName.c_str(), 0666) == -1) {
        throw NamedPipesError("mkfifo");
    }
    if (mkfifo(_outName.c_str(), 0666) == -1) {
        throw NamedPipesError("mkfifo");
    }
}

void Plazza::NamedPipes::openPipes()
{
    if (_isParent) {
        _inFd = open(_inName.c_str(), O_WRONLY);
        _outFd = open(_outName.c_str(), O_RDONLY);
    } else {
        _inFd = open(_inName.c_str(), O_RDONLY);
        _outFd = open(_outName.c_str(), O_WRONLY);
    }
    if (_inFd == -1 || _outFd == -1) {
        throw NamedPipesError("open");
    }
    if (fcntl(_inFd, F_SETFL, O_NONBLOCK) == -1 || fcntl(_outFd, F_SETFL, O_NONBLOCK) == -1) {
        throw NamedPipesError("fcntl");
    }
}

void Plazza::NamedPipes::closePipes()
{
    if (_inFd != -1)
        close(_inFd);
    if (_outFd != -1)
        close(_outFd);
    if (_isParent) {
        unlink(_inName.c_str());
        unlink(_outName.c_str());
    }
}

void Plazza::NamedPipes::remove_existing_pipes()
{
    system("rm -f /tmp/plazza*");
}

void Plazza::NamedPipes::operator>>(std::string &str)
{
    char buffer[4096];
    int ret = 0;

    memset(buffer, 0, 4096);
    ret = read(_isParent ? _outFd : _inFd, buffer, 4096);
    if (ret == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            str = "";
            return;
        } else {
            throw NamedPipesError("read");
        }
    }
    if (ret == 0) {
        throw NamedPipesError("pipe closed unexpectedly");
    }
    str = buffer;
}

void Plazza::NamedPipes::operator<<(const std::string &str)
{
    if (write(_isParent ? _inFd : _outFd, str.c_str(), str.size()) == -1) {
        throw NamedPipesError("write");
    }
}
