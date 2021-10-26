//
// Created by 17105727 on 01.10.2021.
//

#ifndef GVIEWER_SCREEN_H
#define GVIEWER_SCREEN_H

#include "../Basics/RGBA.h++"
#include "../../Utils/BaseObject.h++"
#include "../../Utils/Containers/Matrix.h++"
#include "../../Utils/Containers/Pair.h++"
#include "../../Geometry/Basics/Point2.h++"


class Screen: public BaseObject {
protected:
    using BitmabWithDepth = Matrix<Pair<RGBA, double>>;

    BitmabWithDepth bitmapWithDepth;
    Point2<size_t, size_t> offset;

public:
    Screen(size_t width,
           size_t height,
           const Point2<size_t, size_t>& offset,
           const RGBA &fillColor = RGBA::transparent()) noexcept :
           bitmapWithDepth(height, width,  {fillColor, 0}), offset(offset) {
    }

    Screen(const Screen &copy) noexcept = default;
    Screen(Screen &&move) noexcept = default;

    Screen& operator = (const Screen &copy) noexcept = default;
    Screen& operator = (Screen &&move) noexcept = default;

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
    [[nodiscard]] const Point2<size_t, size_t>& getOffset() const noexcept { return offset; }

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

    void apply(const Screen &rhs) noexcept {
        // Getting rhs width, height and offset for later
        size_t rhsWidth = rhs.width();
        size_t rhsHeight = rhs.height();
        const auto& rhsOffset = rhs.offset;

        // Getting this width and height
        size_t thisWidth = width();
        size_t thisHeight = height();

        // Calculating rhs minX, minY, maxX, maxY
        size_t rhsMinX = rhsOffset.x;
        size_t rhsMinY = rhsOffset.y;
        size_t rhsMaxX = rhsWidth + rhsMinX;
        size_t rhsMaxY = rhsHeight + rhsMinY;

        // Calculating this minX, minY, maxX, maxY
        size_t thisMinX = offset.x;
        size_t thisMinY = offset.y;
        size_t thisMaxX = thisWidth + thisMinX;
        size_t thisMaxY = thisHeight + thisMinY;

        // Calculating both minX, minY, maxX, maxY
        size_t bothMinX = std::min(rhsMinX, thisMinX);
        size_t bothMinY = std::min(rhsMinY, thisMinY);
        size_t bothMaxX = std::max(rhsMaxX, thisMaxX);
        size_t bothMaxY = std::max(rhsMaxY, thisMaxY);

        // If rhs is not fully inside this screen
        if ((bothMinX != thisMinX) || (bothMinY != thisMinY) || (bothMaxX != thisMaxX) || (bothMaxY != thisMaxY)) {
            // Initializing new bitmap matrix
            BitmabWithDepth newBitmap(bothMaxY, bothMaxX, {RGBA::transparent(), 0.0});

            // Copying this bitmap to the new bitmap
            for (size_t y = thisMinY; y < thisMaxY; y++) {
                for (size_t x = thisMinX; x < thisMaxX; x++) {
                    newBitmap[(long) y][(long) x] = bitmapWithDepth[(long) y][(long) x];
                }
            }

            // Changing this offset and bitmap
            offset.x = bothMinX;
            offset.y = bothMinY;
            bitmapWithDepth = newBitmap;
        }

        // Adding rhs to this screen
        for (size_t y = 0; y < rhsHeight; y++) {
            for (size_t x = 0; x < rhsWidth; x++) {
                const auto& rhsColor = rhs.getPixedColor(x, y);
                const auto& rhsZIndex = rhs.getZIndex(x, y);
                setPixelColor(x + rhsOffset.x, y + rhsOffset.y, rhsColor, rhsZIndex);
            }
        }
    }

    [[nodiscard]] Pair<size_t, size_t> getSize() const noexcept {
        return {width(), height()};
    }
    [[nodiscard]] size_t width() const noexcept { return bitmapWithDepth.columns(); }
    [[nodiscard]] size_t height() const noexcept { return bitmapWithDepth.rows(); }

    ~Screen() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[Screen width = " << bitmapWithDepth.rows() << ", height = " << bitmapWithDepth.columns() << ']';
        return sst.str();
    }
};

#endif //GVIEWER_SCREEN_H
