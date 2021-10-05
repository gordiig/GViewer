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


class Vertex: public BaseObject {
protected:
    Coordinate pos;
    TextureCoordinate tx;
    Vector vec;
    ShadingCoefficients sc;

public:
    Vertex(Coordinate pos, TextureCoordinate tx, Vector vec, ShadingCoefficients sc) :
        pos(std::move(pos)), tx(std::move(tx)), vec(std::move(vec)), sc(std::move(sc)) {}

    Vertex(const Vertex &copy) noexcept {
        if (this == &copy)
            return;
        *this = copy;
    }
    Vertex(Vertex &&move) noexcept { *this = move; }

    Vertex& operator = (const Vertex &copy) noexcept {
        pos = copy.pos;
        tx = copy.tx;
        vec = copy.vec;
        sc = copy.sc;
        return *this;
    }
    Vertex& operator = (Vertex &&move) noexcept {
        pos = move.pos;
        tx = move.tx;
        vec = move.vec;
        sc = move.sc;
        return *this;
    }

    [[nodiscard]] const Coordinate& getPos() const noexcept { return pos; }
    [[nodiscard]] const TextureCoordinate& getTx() const noexcept { return tx; }
    [[nodiscard]] const Vector& getVec() const noexcept { return vec; }
    [[nodiscard]] const ShadingCoefficients& getSc() const noexcept { return sc; }

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
