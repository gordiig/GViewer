//
// Created by 17105727 on 01.10.2021.
//

#ifndef GVIEWER_ANGLESYSTEM_H
#define GVIEWER_ANGLESYSTEM_H


#include <sstream>
#include <utility>
#include "../../Utils/BaseObject.h++"
#include "../Basics/Angle.h++"

struct AngleSystem: public BaseObject {
    Angle xAxis;
    Angle yAxis;
    Angle zAxis;

    AngleSystem() noexcept = default;

    AngleSystem(Angle xAxis, Angle yAxis, Angle zAxis) noexcept :
        xAxis(std::move(xAxis)), yAxis(std::move(yAxis)), zAxis(std::move(zAxis)) { }

    AngleSystem(const AngleSystem &copy) noexcept {
        if (this == &copy)
            return;
        *this = copy;
    }
    AngleSystem(AngleSystem &&copy) noexcept { *this = copy; }

    AngleSystem& operator = (const AngleSystem &copy) noexcept {
        xAxis = copy.xAxis;
        yAxis = copy.yAxis;
        zAxis = copy.zAxis;
        return *this;
    }
    AngleSystem& operator = (AngleSystem &&copy) noexcept {
        xAxis = copy.xAxis;
        yAxis = copy.yAxis;
        zAxis = copy.zAxis;
        return *this;
    }

    ~AngleSystem() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "angSys [x] = " << xAxis << " [y] = " << yAxis << " [z] = " << zAxis;
        return sst.str();
    }
};

#endif //GVIEWER_ANGLESYSTEM_H
