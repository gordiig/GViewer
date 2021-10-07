//
// Created by 17105727 on 01.10.2021.
//

#ifndef GVIEWER_POLYGON_H
#define GVIEWER_POLYGON_H


#include <sstream>
#include <utility>
#include "../../Settings/Settings.h++"
#include "../../Utils/BaseObject.h++"
#include "../Scene/BaseSceneObject.h++"
#include "../../Geometry/Basics/Vector.h++"
#include "Vertex.h++"


class Polygon: public BaseSceneObject {
protected:
    Vertex v1;
    Vertex v2;
    Vertex v3;

    double _width;
    double _height;
    double _depth;

    [[nodiscard]] Coordinate maxCoord(const Coordinate &c1, const Coordinate &c2, const Coordinate &c3) const noexcept {
        double tmp = std::max(c1.x, c2.x);
        double maxX = std::max(tmp, c3.x);

        tmp = std::max(c1.y, c2.y);
        double maxY = std::max(tmp, c3.y);

        tmp = std::max(c1.z, c2.z);
        double maxZ = std::max(tmp, c3.z);

        return {maxX, maxY, maxZ};
    }
    [[nodiscard]] Coordinate minCoord(const Coordinate &c1, const Coordinate &c2, const Coordinate &c3) const noexcept {
        double tmp = std::min(c1.x, c2.x);
        double minX = std::min(tmp, c3.x);

        tmp = std::min(c1.y, c2.y);
        double minY = std::min(tmp, c3.y);

        tmp = std::min(c1.z, c2.z);
        double minZ = std::min(tmp, c3.z);

        return {minX, minY, minZ};
    }

public:
    Polygon() = delete;
    Polygon(Vertex v1, Vertex v2, Vertex v3) :
        BaseSceneObject(), v1(std::move(v1)), v2(std::move(v2)), v3(std::move(v3)) {
        origin = turnOrigin = scaleOrigin = (v1.pos + v2.pos + v3.pos) / 3.0;

        Coordinate maxC = maxCoord(v1.pos, v2.pos, v3.pos);
        Coordinate minC = minCoord(v1.pos, v2.pos, v3.pos);

        _width = abs(maxC.x - minC.x);
        _height = abs(maxC.y - minC.y);
        _depth = abs(maxC.z - minC.z);
    }

    Polygon(const Polygon &copy) = default;
    Polygon(Polygon &&move) noexcept = default;

    Polygon& operator = (const Polygon &copy) noexcept = default;
    Polygon& operator = (Polygon &&move) noexcept = default;

    [[nodiscard]] Vertex& getV1() noexcept { return v1; }
    [[nodiscard]] Vertex& getV2() noexcept { return v2; }
    [[nodiscard]] Vertex& getV3() noexcept { return v3; }

    [[nodiscard]] const Vertex& getV1() const noexcept { return v1; }
    [[nodiscard]] const Vertex& getV2() const noexcept { return v2; }
    [[nodiscard]] const Vertex& getV3() const noexcept { return v3; }

    [[nodiscard]] std::unique_ptr<ISceneObject> copyUnique() const override {
        Polygon newPoly = *this;
        return std::make_unique<Polygon>(std::move(newPoly));
    }
    [[nodiscard]] std::shared_ptr<ISceneObject> copyShared() const override {
        Polygon newPoly = *this;
        return std::make_shared<Polygon>(std::move(newPoly));
    }

    [[nodiscard]] Vector norm() const noexcept override {
        Vector ans = (v1.vec + v2.vec + v3.vec) / 3.0;
        return ans;
    }

    [[nodiscard]] double width() const noexcept override { return _width * sf.x; }
    [[nodiscard]] double height() const noexcept override { return _height * sf.y; }
    [[nodiscard]] double depth() const noexcept override { return _depth * sf.z; }

    void setToRender() const override {
        Settings& s = Settings::getInstance();
        IRenderer& renderer = s.getRenderer();

        Polygon newPoly = *this;
        std::unique_ptr<ISceneObject> newP = std::make_unique<Polygon>(std::move(newPoly));
        renderer.addToRender(std::move(newP));
    }

    ~Polygon() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[Polygon v1 = " << v1 << ", v2 = " << v2 << ", v3 = " << v3 << ']';
        return sst.str();
    }

};

#endif //GVIEWER_POLYGON_H
