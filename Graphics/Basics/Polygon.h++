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
#include "Vertex.h++"


class Polygon: public BaseSceneObject {
protected:
    Vertex v1;
    Vertex v2;
    Vertex v3;

public:
    Polygon() = delete;
    Polygon(Vertex v1, Vertex v2, Vertex v3) :
        BaseSceneObject(), v1(std::move(v1)), v2(std::move(v2)), v3(std::move(v3)) { }

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

    [[nodiscard]] std::unique_ptr<ISceneObject> copy() const override {
        Polygon newPoly = *this;
        return std::make_unique<Polygon>(std::move(newPoly));
    }

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
