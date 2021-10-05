//
// Created by 17105727 on 30.09.2021.
//

#ifndef GVIEWER_MATH_H
#define GVIEWER_MATH_H

#include <string>
#include "Exception.h++"


class DivideByZeroError : public Exception {
public:
    DivideByZeroError(__EXC_ARGS__) noexcept :
            Exception(__EXC_PARAMS__, "Trying to divide by zero!") {}

    DivideByZeroError(__EXC_ARGS__, const std::string &msg) noexcept :
        Exception(__EXC_PARAMS__, msg) {}

    ~DivideByZeroError() noexcept override = default;
};


class CotangensOfZeroError : public Exception {
public:
    CotangensOfZeroError(__EXC_ARGS__) noexcept :
            Exception(__EXC_PARAMS__, "Trying to get cot(0)!") {}

    CotangensOfZeroError(__EXC_ARGS__, const std::string &msg) noexcept :
            Exception(__EXC_PARAMS__, msg) {}

    ~CotangensOfZeroError() noexcept override = default;
};

#endif //GVIEWER_MATH_H
