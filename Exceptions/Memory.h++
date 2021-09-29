//
// Created by 17105727 on 29.09.2021.
//

#ifndef GVIEWER_MEMORY_H
#define GVIEWER_MEMORY_H

#include <exception>
#include "Exception.h++"

class BadAllocException: public Exception {
public:
    explicit BadAllocException(__EXC_ARGS__, const std::bad_alloc &allocException) :
        Exception(__EXC_PARAMS__, allocException.what()) {}
};

#endif //GVIEWER_MEMORY_H
