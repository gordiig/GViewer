//
// Created by 17105727 on 19.10.2021.
//

#ifndef GVIEWER_LAMBERTSHADER_H
#define GVIEWER_LAMBERTSHADER_H

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


class LambertShader: public IShader {
protected:
    [[nodiscard]] static Vertex getAvgVtxForLighting(const DynArray<Vertex> &figure) {
        // Initializing variables for later
        Vector avgNorm(0, 0, 0);
        Coordinate avgPos(0, 0, 0);
        Vertex ansVtx = Vertex::zero();
        double avgKd = 0;
        double avgKa = 0;
        const auto& figureVtxCountDouble = (double) figure.count();

        // Calculating sum of all needed values
        for (const auto& vtx : figure) {
            avgNorm += vtx.vec;
            avgPos += vtx.pos;
            avgKd += vtx.sc.getKd();
            avgKa += vtx.sc.getKa();
        }

        // Divide sums for getting avg values
        avgNorm /= figureVtxCountDouble;
        avgPos /= figureVtxCountDouble;
        avgKd /= figureVtxCountDouble;
        avgKa /= figureVtxCountDouble;

        // Setting avg values to resulting vtx
        ansVtx.pos = avgPos;
        ansVtx.vec = avgNorm;
        ansVtx.sc.setKd(avgKd);
        ansVtx.sc.setKa(avgKa);

        return ansVtx;
    }

public:
    LambertShader() noexcept = default;

    LambertShader(const LambertShader &copy) noexcept = default;
    LambertShader(LambertShader &&move) noexcept = default;

    LambertShader& operator = (const LambertShader &copy) noexcept = default;
    LambertShader& operator = (LambertShader &&move) noexcept = default;

    Screen shade(const DynArray<Vertex> &figure, const DynArray<ScreenVertex> &screenVtxs,
                 const IMaterial& material) override {
        // Checking if figure is empty
        if (figure.count() == 0 || screenVtxs.count() == 0)
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

        // Initializing interpolators
        LineInterpolator line1InterpolatorTx = getTxInterpolator(line1);
        LineInterpolator line2InterpolatorTx = getTxInterpolator(line2);
        Interpolator line1ZInterpolatorByY = getZInterpolatorByY(line1);
        Interpolator line2ZInterpolatorByY = getZInterpolatorByY(line2);

        // Getting light intensity
        const auto& avgVtx = getAvgVtxForLighting(figure);
        const auto& lightIntensity = getIntensityForVtx(avgVtx);

        int zzzzz = 1;

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

            // Getting tx and z from both lines
            Point2 line1Tx = line1InterpolatorTx.interpolate({x1Double, syDouble});
            Point2 line2Tx = line2InterpolatorTx.interpolate({x2Double, syDouble});
            double line1Z = line1ZInterpolatorByY.interpolate(syDouble);
            double line2Z = line2ZInterpolatorByY.interpolate(syDouble);

            // Swap x1 and x2 if needed
            if (x1 > x2) {
                std::swap(x1, x2);
                std::swap(x1Double, x2Double);
                std::swap(line1Tx, line2Tx);
                std::swap(line1Z, line2Z);
            }

            // Initializing tx, ty and z interpolator
            Interpolator txInterpolator({x1Double, x2Double}, {line1Tx.x, line2Tx.x});
            Interpolator tyInterpolator({x1Double, x2Double}, {line1Tx.y, line2Tx.y});
            Interpolator zInterpolator({x1Double, x2Double}, {line1Z, line2Z});

            // Draw line
            double tx, ty, z, xDouble;
            for (size_t x = x1; x <= x2; x++) {
                // Getting interpolated values
                xDouble = (double) x;
                tx = txInterpolator.interpolate(xDouble);
                ty = tyInterpolator.interpolate(xDouble);
                z = zInterpolator.interpolate(xDouble);
                const auto& color = material.getColor(tx, ty, lightIntensity);

                // Subtracting offset because we need to start drawing from (0, 0)
                screen.setPixelColor(x - screenOffset.x, sy - screenOffset.y, color, z);
            }

            // Changing first line and line interpolator if needed
            if (sy == bottomPt1.pos.y) {
                idx1--;
                line1.first = line1.second;
                line1.second = screenVtxs[idx1];
                line1InterpolatorTx = getTxInterpolator(line1);
                line1ZInterpolatorByY = getZInterpolatorByY(line1);
            }

            // Changing second line and line interpolator if needed
            if (sy == bottomPt2.pos.y) {
                idx2 = (idx2 + 1) % screenVtxsCount;
                line2.first = line2.second;
                line2.second = screenVtxs[idx2];
                line2InterpolatorTx = getTxInterpolator(line2);
                line2ZInterpolatorByY = getZInterpolatorByY(line2);
            }

            // Going down
            sy += 1;
            syDouble = (double) sy;  // Do not increment for make float error a bit less
        }

        return screen;
    }

    ~LambertShader() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[LambertShader]"; }
};

#endif //GVIEWER_LAMBERTSHADER_H
