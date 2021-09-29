//
// Created by 17105727 on 29.09.2021.
//

#ifndef GVIEWER_RANGE_H
#define GVIEWER_RANGE_H

#include <exception>
#include <vector>
#include "Exception.h++"

class IndexError: public Exception {
public:
    IndexError(__EXC_ARGS__, const std::out_of_range& exc) :
        Exception(__EXC_PARAMS__, exc.what()) {}
};

class NotFoundInCollectionError: public Exception {
public:
    NotFoundInCollectionError(__EXC_ARGS__):
        Exception(__EXC_PARAMS__, "Value is not found in collection") {}

    NotFoundInCollectionError(__EXC_ARGS__, const std::string &msg) :
        Exception(__EXC_PARAMS__, msg) {}

};

#endif //GVIEWER_RANGE_H
