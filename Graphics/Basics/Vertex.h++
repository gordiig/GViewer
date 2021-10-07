//
// Created by 17105727 on 30.09.2021.
//

#ifndef GVIEWER_VERTEX_H
#define GVIEWER_VERTEX_H

#include <sstream>
#include <utility>
#include "ShadingCoefficients.h++"
#include "../Scene/ISceneObject.h++"
#include "../../Geometry/Basics/Point2.h++"
#include "../../Geometry/Basics/Point3.h++"
#include "../../Geometry/Basics/Vector.h++"
#include "../../Utils/BaseObject.h++"


struct Vertex: public BaseObject {
    Coordinate pos;
    TextureCoordinate tx;
    Vector vec;
    ShadingCoefficients sc;

    Vertex(Coordinate pos, TextureCoordinate tx, Vector vec, ShadingCoefficients sc) :
        pos(std::move(pos)), tx(std::move(tx)), vec(std::move(vec)), sc(std::move(sc)) {}

    Vertex(const Vertex &copy) noexcept = default;
    Vertex(Vertex &&move) noexcept = default;

    Vertex& operator = (const Vertex &copy) noexcept = default;
    Vertex& operator = (Vertex &&move) noexcept = default;

    ~Vertex() noexcept override = default;

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


#endif //GVIEWER_VERTEX_H
