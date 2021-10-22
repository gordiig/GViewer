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

public:
    explicit Renderable3DObject(const DynArray<Vertex> &vtxs) :
            IRenderable(), vtxs(vtxs), projectedVtxs(), screenVtxs() {
    }

    Renderable3DObject(const Renderable3DObject &copy) = default;
    Renderable3DObject(Renderable3DObject &&move) noexcept = default;

    Renderable3DObject& operator = (const Renderable3DObject &copy) = default;
    Renderable3DObject& operator = (Renderable3DObject &&move) noexcept = default;

    ~Renderable3DObject() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[Renderable3DObject]"; }
};


#endif //GVIEWER_RENDERABLE3DOBJECT_H
