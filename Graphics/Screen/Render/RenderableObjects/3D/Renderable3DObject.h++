//
// Created by 17105727 on 20.10.2021.
//

#ifndef GVIEWER_RENDERABLE3DOBJECT_H
#define GVIEWER_RENDERABLE3DOBJECT_H

#include <utility>

#include "../IRenderable.h++"
#include "../../Shaders/IShader.h++"
#include "../../../Graphics/Basics/Vertex.h++"
#include "../../../Utils/Containers/DynArray.h++"


class Renderable3DObject: public IRenderable {
protected:
    DynArray<Vertex> vtxs;
    DynArray<Vertex> vtxsInCameraSpace;
    DynArray<Vertex> vtxsCuttedByCameraPyramid;
    DynArray<Vertex> projectedVtxs;
    DynArray<ScreenVertex> screenVtxs;

    [[nodiscard]] inline bool testFigure() const noexcept override { return shader->testFigure(vtxs); }

public:
    explicit Renderable3DObject(const DynArray<Vertex> &vtxs) :
            IRenderable(), vtxs(vtxs), vtxsInCameraSpace(), vtxsCuttedByCameraPyramid(), projectedVtxs(), screenVtxs() {
    }

    Renderable3DObject(const Renderable3DObject &copy) = default;
    Renderable3DObject(Renderable3DObject &&move) noexcept = default;

    Renderable3DObject& operator = (const Renderable3DObject &copy) = default;
    Renderable3DObject& operator = (Renderable3DObject &&move) noexcept = default;

    ~Renderable3DObject() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[Renderable3DObject]"; }
};


#endif //GVIEWER_RENDERABLE3DOBJECT_H
