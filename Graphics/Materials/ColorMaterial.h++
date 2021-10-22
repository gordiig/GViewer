//
// Created by 17105727 on 06.10.2021.
//

#ifndef GVIEWER_COLORMATERIAL_H
#define GVIEWER_COLORMATERIAL_H


#include "../Basics/RGBA.h++"
#include "IMaterial.h++"


class ColorMaterial: public IMaterial {
protected:
    RGBA color;

public:
    explicit ColorMaterial(RGBA color) noexcept : color(std::move(color)) {}

    ColorMaterial(const ColorMaterial &copy) noexcept = default;
    ColorMaterial(ColorMaterial &&move) noexcept = default;

    ColorMaterial& operator = (const ColorMaterial &copy) noexcept = default;
    ColorMaterial& operator = (ColorMaterial &&move) noexcept = default;

    [[nodiscard]] RGBA getColor(double x, double y, size_t intensity) const override {
        RGBA ansColor = color.applyIntensity(intensity);
        return color;
    }

    [[nodiscard]] std::shared_ptr<IMaterial> copyShared() const override {
        ColorMaterial copy = *this;
        return std::make_shared<ColorMaterial>(std::move(copy));
    }
    [[nodiscard]] std::unique_ptr<IMaterial> copyUnique() const override {
        ColorMaterial copy = *this;
        return std::make_unique<ColorMaterial>(std::move(copy));
    }

    ~ColorMaterial() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[ColorMaterial rgba = " << color << ']';
        return sst.str();
    }

};

#endif //GVIEWER_COLORMATERIAL_H
