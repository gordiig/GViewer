//
// Created by 17105727 on 19.10.2021.
//

#ifndef GVIEWER_GOURAUDSHADER_H
#define GVIEWER_GOURAUDSHADER_H

#include "IShader.h++"
#include "../../../Basics/Vertex.h++"
#include "../../../Materials/IMaterial.h++"
#include "../../../../Geometry/Basics/Point2.h++"
#include "../../../../Geometry/Basics/Point3.h++"
#include "../../../../Geometry/Basics/Vector.h++"
#include "../../../../Utils/Containers/DynArray.h++"
#include "../../../../Utils/Containers/Pair.h++"
#include "../../../../Utils/LineInterpolator.h++"
#include "../../../../Utils/Interpolator.h++"

class GouraudShader: public IShader {
protected:
    [[nodiscard]] static Interpolator getIntensityInterpolatorByY(const VertexLine &line,
                                                                  const size_t intensityStart,
                                                                  const size_t intensityEnd) {
        const auto& lineStartY = (double) line.first.pos.y;
        const auto& lineEndY = (double) line.second.pos.y;
        const auto intensityStartDouble = (double) intensityStart;
        const auto intensityEndDouble = (double) intensityEnd;

        Interpolator ans({lineStartY, lineEndY}, {intensityStartDouble, intensityEndDouble});
        return ans;
    }

public:
    GouraudShader() noexcept = default;

    GouraudShader(const GouraudShader &copy) noexcept = default;
    GouraudShader(GouraudShader &&move) noexcept = default;

    GouraudShader& operator = (const GouraudShader &copy) noexcept = default;
    GouraudShader& operator = (GouraudShader &&move) noexcept = default;

    Screen shade(const DynArray<Vertex> &figure, const DynArray<ScreenVertex> &screenVtxs,
                 const IMaterial& material) override {
        // Checking if figure is empty
        if (figure.count() == 0)
            return EMPTY_SCREEN;

        // Getting screen size
        const auto [leftTopPt, rightBottomPt] = sizeRectangleForScreen(screenVtxs);
        size_t screenWidth = rightBottomPt.x - leftTopPt.x;
        size_t screenHeight = rightBottomPt.y - leftTopPt.y;
        if (screenWidth == 0 || screenHeight == 0)
            return {0, 0, {0, 0}};

        // Getting top vtx idx and top and bottom y
        const auto& topYCoordIdx = findTopScreenCoordIdx(screenVtxs);
        const auto& topYVtx = screenVtxs[topYCoordIdx];
        const size_t bottomY = rightBottomPt.y;
        size_t sy = topYVtx.pos.y;
        auto syDouble = (double) sy;

        // Initializing screen with offset of left and top coord
        const Point2<size_t, size_t> screenOffset{leftTopPt.x, leftTopPt.y};
        Screen screen(screenWidth, screenHeight, screenOffset);

        // Getting vtxs count
        const long screenVtxsCount = (long) screenVtxs.count();

        // Calculating indexes for first 2 lines
        long idx1 = topYCoordIdx - 1;
        long idx2 = (topYCoordIdx + 1) % screenVtxsCount;

        // Initializing pairs for first and second lines
        VertexLine line1{screenVtxs[topYCoordIdx], screenVtxs[idx1]};
        VertexLine line2{screenVtxs[topYCoordIdx], screenVtxs[idx2]};

        // Getting light intensity for all verticies in lines
        size_t line1StartIntensity = getIntensityForVtx(figure[topYCoordIdx]);
        size_t line1EndIntensity = getIntensityForVtx(figure[idx1]);
        size_t line2StartIntensity = line1StartIntensity;
        size_t line2EndIntensity = getIntensityForVtx(figure[idx2]);

        // Initializing interpolators
        LineInterpolator line1InterpolatorTx = getTxInterpolator(line1);
        LineInterpolator line2InterpolatorTx = getTxInterpolator(line2);
        Interpolator line1ZInterpolatorByY = getZInterpolatorByY(line1);
        Interpolator line2ZInterpolatorByY = getZInterpolatorByY(line2);
        Interpolator line1IntensityInterpolatorByY = getIntensityInterpolatorByY(line1,
                                                                                 line1StartIntensity,
                                                                                 line1EndIntensity);
        Interpolator line2IntensityInterpolatorByY = getIntensityInterpolatorByY(line2,
                                                                                 line2StartIntensity,
                                                                                 line2EndIntensity);

        // Main loop
        size_t x1, x2;
        double x1Double, x2Double;
        while (sy <= bottomY) {
            // For readability
            const auto& topPt1 = line1.first;
            const auto& topPt1Pos = topPt1.pos;
            const auto& topPt2 = line2.first;
            const auto& topPt2Pos = topPt2.pos;
            const auto& bottomPt1 = line1.second;
            const auto& bottomPt1Pos = bottomPt1.pos;
            const auto& bottomPt2 = line2.second;
            const auto& bottomPt2Pos = bottomPt2.pos;

            // Calculating current x for first and second line
            x1 = getXForLine(bottomPt1Pos, topPt1Pos, sy);
            x1Double = (double) x1;
            x2 = getXForLine(bottomPt2Pos, topPt2Pos, sy);
            x2Double = (double) x2;

            // Getting tx, z and intensities from both lines
            Point2 line1Tx = line1InterpolatorTx.interpolate({x1Double, syDouble});
            Point2 line2Tx = line2InterpolatorTx.interpolate({x2Double, syDouble});
            double line1Z = line1ZInterpolatorByY.interpolate(syDouble);
            double line2Z = line2ZInterpolatorByY.interpolate(syDouble);
            double line1Intensity = line1IntensityInterpolatorByY.interpolate(syDouble);
            double line2Intensity = line2IntensityInterpolatorByY.interpolate(syDouble);

            // Swap x1 and x2 if needed
            if (x1 > x2) {
                std::swap(x1, x2);
                std::swap(x1Double, x2Double);
                std::swap(line1Tx, line2Tx);
                std::swap(line1Z, line2Z);
                std::swap(line1Intensity, line2Intensity);
            }

            // Initializing tx, ty, z and intensity interpolator
            Interpolator txInterpolator({x1Double, x2Double}, {line1Tx.x, line2Tx.x});
            Interpolator tyInterpolator({x1Double, x2Double}, {line1Tx.y, line2Tx.y});
            Interpolator zInterpolator({x1Double, x2Double}, {line1Z, line2Z});
            Interpolator intensityInterpolator({x1Double, x2Double}, {line1Intensity, line2Intensity});

            // Draw line
            double tx, ty, z, xDouble, intensity;
            for (size_t x = x1; x <= x2; x++) {
                // Getting interpolated values
                xDouble = (double) x;
                tx = txInterpolator.interpolate(xDouble);
                ty = tyInterpolator.interpolate(xDouble);
                z = zInterpolator.interpolate(xDouble);
                intensity = intensityInterpolator.interpolate(xDouble);

                // Subtracting width and height because we already have screen offset,
                // so we need to start drawing from (0, 0)
                screen.setPixelColor(x - screenWidth, sy - screenHeight, material.getColor(tx, ty, (size_t) intensity), z);
            }

            // Changing first line and line interpolator if needed
            if (sy == bottomPt1.pos.y) {
                // Changing vertixes in line
                idx1--;
                line1.first = line1.second;
                line1.second = screenVtxs[idx1];

                // Recalculating intensities
                line1StartIntensity = line1EndIntensity;
                line1EndIntensity = getIntensityForVtx(figure[idx1]);

                // Changing interpolators
                line1InterpolatorTx = getTxInterpolator(line1);
                line1ZInterpolatorByY = getZInterpolatorByY(line1);
                line1IntensityInterpolatorByY = getIntensityInterpolatorByY(line1,
                                                                            line1StartIntensity,
                                                                            line1EndIntensity);
            }

            // Changing second line and line interpolator if needed
            if (sy == bottomPt2.pos.y) {
                // Changing vertixes in line
                idx2 = (idx2 + 1) % screenVtxsCount;
                line2.first = line2.second;
                line2.second = screenVtxs[idx2];

                // Recalculating intensities
                line2StartIntensity = line2EndIntensity;
                line2EndIntensity = getIntensityForVtx(figure[idx2]);

                // Changing interpolators
                line2InterpolatorTx = getTxInterpolator(line2);
                line2ZInterpolatorByY = getZInterpolatorByY(line2);
                line2IntensityInterpolatorByY = getIntensityInterpolatorByY(line2,
                                                                            line2StartIntensity,
                                                                            line2EndIntensity);
            }

            // Going down
            sy += 1;
            syDouble = (double) sy;
        }

        return screen;
    }

    ~GouraudShader() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[GouraudShader]"; }
};

#endif //GVIEWER_GOURAUDSHADER_H
