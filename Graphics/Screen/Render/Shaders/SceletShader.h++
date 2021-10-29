//
// Created by 17105727 on 26.10.2021.
//

#ifndef GVIEWER_SCELETSHADER_H
#define GVIEWER_SCELETSHADER_H

#include "IShader.h++"
#include "../../../Basics/Vertex.h++"
#include "../../../../Geometry/Basics/Point2.h++"
#include "../../../../Geometry/Basics/Point3.h++"
#include "../../../../Geometry/Basics/Vector.h++"
#include "../../../../Utils/Containers/DynArray.h++"
#include "../../../../Utils/Containers/Pair.h++"


class SceletShader: public IShader {
protected:
    using Line = DynArray<ScreenCoordinate>;

    static Line brezLine(const ScreenCoordinate &p1, const ScreenCoordinate &p2) {
        // Initializing answer
        Line ans;

        // If points are equal, returning one of them
        if (p1 == p2)
            return {p1};

        // Initializing start point
        ScreenCoordinate workingPoint{p1.x, p1.y, 0};

        // Initializing dx and dy
        long dx = std::abs((long) p2.x - (long) p1.x);
        long dy = std::abs((long) p2.y - (long) p1.y);

        // Initializing signs
        short signX = p1.x < p2.x ? 1 : -1;
        short signY = p1.y < p2.y ? 1 : -1;

        // Initializing error
        long e = dx - dy;
        long e2;

        while (workingPoint.x != p2.x || workingPoint.y != p2.y) {
            // Adding point to the line
            ans.append(workingPoint);
            e2 = e * 2;

            if (e2 > -dy) {
                e -= dy;
                workingPoint.x += signX;
            }
            if (e2 < dx) {
                e += dx;
                workingPoint.y += signY;
            }
        }

        return ans;
    }

public:
    Screen shade(const DynArray<Vertex> &figure, const DynArray<ScreenVertex> &screenVtxs,
                 const IMaterial &material) override {
        // Checking if figure is empty
        if (figure.count() == 0)
            return EMPTY_SCREEN;

        // Getting screen size
        const auto sizeRectForScreen = sizeRectangleForScreen(screenVtxs);
        const auto& leftTopPt = sizeRectForScreen.first;
        const auto& rightBottomPt = sizeRectForScreen.second;
        size_t screenWidth = rightBottomPt.x - leftTopPt.x + 1;
        size_t screenHeight = rightBottomPt.y - leftTopPt.y + 1;
        if (screenWidth == 0 || screenHeight == 0)
            return {0, 0, {0, 0}};

        // Getting top vtx idx and top and bottom y
        const auto& topYCoordIdx = findTopScreenCoordIdx(screenVtxs);
        const auto& topYVtx = screenVtxs[topYCoordIdx];

        // Initializing screen with offset of left and top coord
        const Point2<size_t, size_t> screenOffset{leftTopPt.x, leftTopPt.y};
        Screen screen(screenWidth, screenHeight, screenOffset);

        // Getting vtxs count
        const long screenVtxsCount = (long) screenVtxs.count();

        long idx1, idx2;
        for (long i = 0; i < screenVtxsCount; i++) {
            // Calculating indexes for line corners
            idx1 = i;
            idx2 = (i + 1) % screenVtxsCount;

            // Getting vertixes for line
            const auto& v1 = screenVtxs[idx1];
            const auto& v2 = screenVtxs[idx2];

            // Calculating line
            Line line = brezLine(v1.pos, v2.pos);

            // Adding line to the screen
            for (const auto& point : line) {
                screen.setPixelColor(point.x - screenOffset.x, point.y - screenOffset.y, RGBA::white(), 0);
            }
        }

        return screen;
    }

    ~SceletShader() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[SceletShader]"; }
};


#endif //GVIEWER_SCELETSHADER_H
