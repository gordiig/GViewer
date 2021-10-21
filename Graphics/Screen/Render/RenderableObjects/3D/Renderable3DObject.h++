//
// Created by 17105727 on 20.10.2021.
//

#ifndef GVIEWER_RENDERABLE3DOBJECT_H
#define GVIEWER_RENDERABLE3DOBJECT_H

#include <utility>

#include "../IRenderable.h++"
#include "../../../Graphics/Basics/Vertex.h++"
#include "../../../Utils/Containers/DynArray.h++"

class ICamera;

class Renderable3DObject: public IRenderable {
protected:
    using VertexLine = Pair<ScreenVertex, ScreenVertex>;

    DynArray<Vertex> vtxs;
    DynArray<Vertex> projectedVtxs;
    DynArray<ScreenVertex> screenVtxs;

    [[nodiscard]] auto sizeRectangleForScreen() const noexcept {
        if (screenVtxs.isEmpty())
            return Pair(Point2<size_t, size_t>{0, 0}, Point2<size_t, size_t>{0, 0});

        const auto& firstScreenVtxPos = screenVtxs[0].pos;
        Point2<size_t, size_t> minPt = {firstScreenVtxPos.x, firstScreenVtxPos.y};
        Point2<size_t, size_t> maxPt = {firstScreenVtxPos.x, firstScreenVtxPos.y};

        for (const auto& screenVtx : screenVtxs) {
            const auto& curPos = screenVtx.pos;

            if (curPos.x > maxPt.x)
                maxPt.x = curPos.x;
            if (curPos.y > maxPt.y)
                maxPt.y = curPos.y;
            if (curPos.x < minPt.x)
                minPt.x = curPos.x;
            if (curPos.y < minPt.y)
                minPt.y = curPos.y;
        }

        return Pair(minPt, maxPt);
    }

    [[nodiscard]] Pair<size_t, size_t> getScreenSize() const noexcept {
        if (screenVtxs.isEmpty())
            return {0, 0};

        auto [minCoord, maxCoord] = sizeRectangleForScreen();
        size_t width = maxCoord.x - minCoord.x;
        size_t height = maxCoord.y - minCoord.y;

        return {width, height};
    }

    [[nodiscard]] long findTopScreenCoordIdx() const noexcept {
        if (screenVtxs.isEmpty())
            return -1;

        long ansIdx = 0;
        auto topYCoord = screenVtxs[ansIdx].pos.y;

        for (int i = 1; i < screenVtxs.count(); i++) {
            const auto curY = screenVtxs[i].pos.y;
            if (curY < topYCoord) {
                topYCoord = curY;
                ansIdx = i;
            }
        }

        return ansIdx;
    }

public:
    Renderable3DObject(const DynArray<Vertex> &vtxs, const std::shared_ptr<ICamera>& camera) :
            IRenderable(camera), vtxs(vtxs), projectedVtxs(), screenVtxs() {
    }

    Renderable3DObject(const Renderable3DObject &copy) = default;
    Renderable3DObject(Renderable3DObject &&move) noexcept = default;

    Renderable3DObject& operator = (const Renderable3DObject &copy) = default;
    Renderable3DObject& operator = (Renderable3DObject &&move) noexcept = default;

    ~Renderable3DObject() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[Renderable3DObject]"; }
};


#endif //GVIEWER_RENDERABLE3DOBJECT_H
