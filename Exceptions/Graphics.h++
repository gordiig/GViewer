//
// Created by 17105727 on 01.10.2021.
//

#ifndef GVIEWER_GRAPHICS_H
#define GVIEWER_GRAPHICS_H

#include <string>
#include "Exception.h++"

class OutOfScreenBounds : public Exception {
public:
    OutOfScreenBounds(__EXC_ARGS__, const std::string &msg) noexcept :
            Exception(__EXC_PARAMS__, msg) {}

    ~OutOfScreenBounds() noexcept override = default;
};

#endif //GVIEWER_GRAPHICS_H
