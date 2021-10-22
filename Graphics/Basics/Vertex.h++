//
// Created by 17105727 on 30.09.2021.
//

#ifndef GVIEWER_VERTEX_H
#define GVIEWER_VERTEX_H

#include "ShadingCoefficients.h++"
#include "../Scene/ISceneObject.h++"
#include "../../Geometry/Basics/Point2.h++"
#include "../../Geometry/Basics/Point3.h++"
#include "../../Geometry/Basics/Vector.h++"
#include "../../Utils/BaseObject.h++"


template <typename T>
struct Vertex_: public BaseObject {
    T pos;
    TextureCoordinate tx;
    Vector vec;
    ShadingCoefficients sc;

    Vertex_(T pos, TextureCoordinate tx, Vector vec, ShadingCoefficients sc) :
        pos(std::move(pos)), tx(std::move(tx)), vec(std::move(vec)), sc(std::move(sc)) {}

    static Vertex_ zero() noexcept {
        return {
            T(0, 0, 0),
            TextureCoordinate(0, 0),
            Vector(0, 0, 0),
            ShadingCoefficients(0, 0)
        };
    }

    Vertex_(const Vertex_ &copy) noexcept = default;
    Vertex_(Vertex_ &&move) noexcept = default;

    Vertex_& operator = (const Vertex_ &copy) noexcept = default;
    Vertex_& operator = (Vertex_ &&move) noexcept = default;

    ~Vertex_() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst
            << "vertex[pos = " << pos
            << ", tx = " << tx
            << ", vector = " << vec
            << ", sc = " << sc << ']';
        return sst.str();
    }
};

using Vertex = Vertex_<Coordinate>;
using ScreenVertex = Vertex_<ScreenCoordinate>;


#endif //GVIEWER_VERTEX_H
