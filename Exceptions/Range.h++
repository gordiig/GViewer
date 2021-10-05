//
// Created by 17105727 on 29.09.2021.
//

#ifndef GVIEWER_RANGE_H
#define GVIEWER_RANGE_H

#include <exception>
#include "Exception.h++"

class IndexError: public Exception {
public:
    IndexError(__EXC_ARGS__, const std::out_of_range& exc) noexcept:
        Exception(__EXC_PARAMS__, exc.what()) {}

    ~IndexError() noexcept override = default;
};

class NotFoundInCollectionError: public Exception {
public:
    NotFoundInCollectionError(__EXC_ARGS__) noexcept:
        Exception(__EXC_PARAMS__, "Value is not found in collection") {}

    NotFoundInCollectionError(__EXC_ARGS__, const std::string &msg) noexcept :
        Exception(__EXC_PARAMS__, msg) {}

    ~NotFoundInCollectionError() noexcept override = default;
};

#endif //GVIEWER_RANGE_H
