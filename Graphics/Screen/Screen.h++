//
// Created by 17105727 on 01.10.2021.
//

#ifndef GVIEWER_SCREEN_H
#define GVIEWER_SCREEN_H


#include <sstream>
#include "../../Utils/BaseObject.h++"
#include "../Basics/RGBA.h++"
#include "../../Utils/Containers/Matrix.h++"
#include "../../Utils/Containers/Pair.h++"
#include "../../Geometry/Basics/Point2.h++"
#include "../../Exceptions/Graphics.h++"

class Screen: public BaseObject {
protected:
    Matrix<Pair<RGBA, double>> bitmapWithDepth;

public:
    Screen(size_t width, size_t height, const RGBA &fillColor = RGBA::transparent()) noexcept :
        bitmapWithDepth(height, width, {fillColor, 0}) {}

    ~Screen() noexcept override = default;

    [[nodiscard]] RGBA& getPixedColor(size_t x, size_t y) {
        long longX = (long) x;
        long longY = (long) y;
        return bitmapWithDepth[longY][longX].first;
    }
    [[nodiscard]] const RGBA& getPixedColor(size_t x, size_t y) const {
        long longX = (long) x;
        long longY = (long) y;
        return bitmapWithDepth[longY][longX].first;
    }
    [[nodiscard]] double getZIndex(size_t x, size_t y) const {
        long longX = (long) x;
        long longY = (long) y;
        return bitmapWithDepth[longY][longX].second;
    }

    RGBA setPixelColor(size_t x, size_t y, const RGBA &color, double zIndex) {
        long longX = (long) x;
        long longY = (long) y;
        auto& curColor = bitmapWithDepth[longY][longX];

        RGBA resultColor = zIndex < curColor.second
                ? color.blendThisAbove(curColor.first)
                : color.blendThisBelow(curColor.first);
        bitmapWithDepth[longY][longX].first = resultColor;
        return resultColor;
    }

    void apply(const Screen &rhs, const Point2<size_t, size_t> &leftTop) {
        size_t maxX = leftTop.x + rhs.width();
        size_t maxY = leftTop.y + rhs.height();

        if (maxX >= width())
            throw OutOfScreenBounds(EXC_PARAMS, "Width overflow on applying one screen on another");
        if (maxY >= height())
            throw OutOfScreenBounds(EXC_PARAMS, "Height overflow on applying one screen on another");

        for (size_t x = leftTop.x; x < maxX; x++) {
            for (size_t y = leftTop.y; y < maxY; y++) {
                auto& rhsColor = rhs.getPixedColor(x, y);
                auto rhsZIndex = rhs.getZIndex(x, y);
                this->setPixelColor(x, y, rhsColor, rhsZIndex);
            }
        }
    }

    [[nodiscard]] auto getSize() const noexcept {
        return std::pair(bitmapWithDepth.columns(), bitmapWithDepth.rows());
    }
    [[nodiscard]] size_t width() const noexcept { return bitmapWithDepth.columns(); }
    [[nodiscard]] size_t height() const noexcept { return bitmapWithDepth.rows(); }

    [[nodiscard]] std::string toString() const noexcept override {
        std::stringstream sst;
        sst << "bitmapWithDepth[" << bitmapWithDepth.rows() << ", " << bitmapWithDepth.columns() << ']';
        return BaseObject::toString();
    }
};

#endif //GVIEWER_SCREEN_H
