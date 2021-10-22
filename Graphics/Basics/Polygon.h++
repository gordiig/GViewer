//
// Created by 17105727 on 01.10.2021.
//

#ifndef GVIEWER_POLYGON_H
#define GVIEWER_POLYGON_H

#include "Vertex.h++"
#include "../Screen/Render/IRenderer.h++"
#include "../Scene/BaseSceneObject.h++"
#include "../../Settings/Settings.h++"


class Polygon: public BaseSceneObject {
protected:
    Vertex v1;
    Vertex v2;
    Vertex v3;

    [[nodiscard]] Coordinate maxCoord() const noexcept {
        const auto& c1 = v1.pos;
        const auto& c2 = v2.pos;
        const auto& c3 = v3.pos;

        double tmp = std::max(c1.x, c2.x);
        double maxX = std::max(tmp, c3.x);

        tmp = std::max(c1.y, c2.y);
        double maxY = std::max(tmp, c3.y);

        tmp = std::max(c1.z, c2.z);
        double maxZ = std::max(tmp, c3.z);

        return {maxX, maxY, maxZ};
    }
    [[nodiscard]] Coordinate minCoord() const noexcept {
        const auto& c1 = v1.pos;
        const auto& c2 = v2.pos;
        const auto& c3 = v3.pos;

        double tmp = std::min(c1.x, c2.x);
        double minX = std::min(tmp, c3.x);

        tmp = std::min(c1.y, c2.y);
        double minY = std::min(tmp, c3.y);

        tmp = std::min(c1.z, c2.z);
        double minZ = std::min(tmp, c3.z);

        return {minX, minY, minZ};
    }

    void setKa(double ka) override {
        v1.sc.setKa(ka);
        v2.sc.setKa(ka);
        v3.sc.setKa(ka);
    }

public:
    Polygon() = delete;

    Polygon(Vertex v1, Vertex v2, Vertex v3) :
            BaseSceneObject(), v1(std::move(v1)), v2(std::move(v2)), v3(std::move(v3)) {
        origin = turnOrigin = scaleOrigin = (v1.pos + v2.pos + v3.pos) / 3.0;
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

    [[nodiscard]] double width() const noexcept override { return abs(maxCoord().x - minCoord().x) * sf.x; }
    [[nodiscard]] double height() const noexcept override { return abs(maxCoord().y - minCoord().y) * sf.y; }
    [[nodiscard]] double depth() const noexcept override { return abs(maxCoord().z - minCoord().z) * sf.z; }

    void setToRender() const override;

    ~Polygon() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[Polygon v1 = " << v1 << ", v2 = " << v2 << ", v3 = " << v3 << ']';
        return sst.str();
    }

};

#endif //GVIEWER_POLYGON_H
