//
// Created by 17105727 on 13.10.2021.
//

#ifndef GVIEWER_ISHADER_H
#define GVIEWER_ISHADER_H

#include "../RenderableObjects/Lights/IRenderableLight.h++"
#include "../../Screen.h++"
#include "../../../Utils/Containers/DynArray.h++"
#include "../../../Utils/Containers/Pair.h++"
#include "../../../Utils/Interpolator.h++"
#include "../../../Utils/LineInterpolator.h++"
#include "../../../Graphics/Basics/Vertex.h++"
#include "../../../Geometry/Basics/Point2.h++"
#include "../../../Utils/BaseObject.h++"

class IRenderable;
class ICamera;
class IMaterial;

class IShader: public BaseObject {
protected:
    using VertexLine = Pair<ScreenVertex, ScreenVertex>;

    const static Screen EMPTY_SCREEN;

    DynArray<std::shared_ptr<IRenderableLight>> lights{};

    [[nodiscard]] static LineInterpolator<size_t, double> getTxInterpolator(const VertexLine &line) noexcept {
        const auto& lineStartPos = line.first.pos;
        const auto& lineStartTx = line.first.tx;
        const auto& lineEndPos = line.second.pos;
        const auto& lineEndTx = line.second.tx;

        Point2 lineStart2D = {lineStartPos.x, lineStartPos.y};
        Point2 lineEnd2D = {lineEndPos.x, lineEndPos.y};
        Point2 lineStartTx2D = {lineStartTx.x, lineStartTx.y};
        Point2 lineEndTx2D = {lineEndTx.x, lineEndTx.y};

        LineInterpolator<size_t, double> ans({lineStart2D, lineEnd2D}, {lineStartTx2D, lineEndTx2D});
        return ans;
    }
    [[nodiscard]] static Interpolator getZInterpolatorByY(const VertexLine &line) {
        const auto& lineStartPos = line.first.pos;
        const auto& lineEndPos = line.first.pos;

        auto lineStartY = (double) lineStartPos.y;
        auto lineEndY = (double) lineEndPos.y;

        double lineStartZ = line.first.pos.z;
        double lineEndZ = line.second.pos.z;

        Interpolator ans({lineStartY, lineEndY}, {lineStartZ, lineEndZ});
        return ans;
    }

    [[nodiscard]] static auto sizeRectangleForScreen(const DynArray<ScreenVertex> &screenVtxs) noexcept {
        if (screenVtxs.isEmpty())
            return Pair(Point2<size_t, size_t>{0, 0}, Point2<size_t, size_t>{0, 0});

        const auto& firstScreenVtxPos = screenVtxs[0].pos;
        Point2<size_t, size_t> leftTopPt = {firstScreenVtxPos.x, firstScreenVtxPos.y};
        Point2<size_t, size_t> rightBottomPt = {firstScreenVtxPos.x, firstScreenVtxPos.y};

        for (const auto& screenVtx : screenVtxs) {
            const auto& curPos = screenVtx.pos;

            if (curPos.x > rightBottomPt.x)
                rightBottomPt.x = curPos.x;
            if (curPos.y > rightBottomPt.y)
                rightBottomPt.y = curPos.y;
            if (curPos.x < leftTopPt.x)
                leftTopPt.x = curPos.x;
            if (curPos.y < leftTopPt.y)
                leftTopPt.y = curPos.y;
        }

        return Pair(leftTopPt, rightBottomPt);
    }

    [[nodiscard]] static long findTopScreenCoordIdx(const DynArray<ScreenVertex> &screenVtxs) noexcept {
        // Checking if screenVtxs array is empty
        if (screenVtxs.isEmpty())
            return -1;

        // Initializing variables for later
        long ansIdxY = 0;
        auto topYCoord = screenVtxs[ansIdxY].pos.y;

        for (int i = 1; i < screenVtxs.count(); i++) {
            // Initializing variables for checking top y
            const auto& curY = screenVtxs[i].pos.y;

            // If current y is less than current top y (less == higher)
            if (curY < topYCoord) {
                topYCoord = curY;
                ansIdxY = i;
            }
        }

        return ansIdxY;
    }

    [[nodiscard]] static size_t getXForLine(const ScreenCoordinate& bottomPtPos, const ScreenCoordinate& topPtPos,
                                            const size_t currentY) noexcept {
        size_t ans;

        if (bottomPtPos.y == topPtPos.y)
            ans = bottomPtPos.x;
        else
            ans = bottomPtPos.x + (currentY - topPtPos.y) * (bottomPtPos.x - topPtPos.x) / (bottomPtPos.y - topPtPos.y);

        return ans;
    }

    unsigned short getIntensityForVtx(const Vertex &vtx) {
        unsigned short totalIntensity = 0;
        for (const auto &light : lights)
            totalIntensity += light->getIntensity(vtx);
        return std::min(totalIntensity, IRenderableLight::MAX_INTENSITY);
    }

public:
    virtual Screen shade(const DynArray<Vertex>& figure, const DynArray<ScreenVertex>& screenVtxs,
                         const IMaterial& material) = 0;

    virtual void configure(const DynArray<std::shared_ptr<IRenderableLight>> &lights) {
        this->lights = lights;
    }

    ~IShader() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[IShader]"; }
};

const Screen IShader::EMPTY_SCREEN = {0, 0, {0, 0}};

#endif //GVIEWER_ISHADER_H