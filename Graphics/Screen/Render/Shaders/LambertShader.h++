//
// Created by 17105727 on 19.10.2021.
//

#ifndef GVIEWER_LAMBERTSHADER_H
#define GVIEWER_LAMBERTSHADER_H

#include "IShader.h++"
#include "../../../Geometry/Basics/Point2.h++"
#include "../../../Utils/LineInterpolator.h++"
#include "../../../Utils/Interpolator.h++"


class LambertShader: public IShader {
protected:


public:
    LambertShader() noexcept = default;

    LambertShader(const LambertShader &copy) noexcept = default;
    LambertShader(LambertShader &&move) noexcept = default;

    LambertShader& operator = (const LambertShader &copy) noexcept = default;
    LambertShader& operator = (LambertShader &&move) noexcept = default;

    Screen shade(const DynArray<Vertex> &figure, const DynArray<ScreenVertex> &screenVertex) override {
        return {0, 0, {0, 0}};
    }

    ~LambertShader() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[LambertShader]"; }
};

#endif //GVIEWER_LAMBERTSHADER_H
