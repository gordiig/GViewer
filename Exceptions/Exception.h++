//
// Created by 17105727 on 29.09.2021.
//

#ifndef GVIEWER_EXCEPTION_H
#define GVIEWER_EXCEPTION_H

#include <exception>
#include <string>
#include <utility>
#include "../Utils/BaseObject.h++"

#define __EXC_ARGS__ const char *file, size_t line
#define __EXC_PARAMS__ file, line
#define EXC_PARAMS __FILE__, __LINE__

class Exception: public std::exception, public BaseObject{
protected:
    std::string file;
    size_t line;
    std::string message;
    std::string fullMessage;

    [[nodiscard]] std::string getFullMessage() const {
        std::stringstream sst;
        sst << message << std::endl << "Line " << line << "in" << file << std::endl;
        return sst.str();
    }

public:
    Exception() = delete;

    Exception(__EXC_ARGS__) noexcept :
        file(file), line(line), message("Exception"), fullMessage(getFullMessage()) {}

    Exception(__EXC_ARGS__, std::string msg) noexcept :
        file(file), line(line), message(std::move(msg)), fullMessage(getFullMessage()) {}

    ~Exception() noexcept override = default;

    [[nodiscard]] const char *what() const noexcept override { return fullMessage.c_str(); }
};

#endif //GVIEWER_EXCEPTION_H
