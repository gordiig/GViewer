//
// Created by 17105727 on 05.10.2021.
//

#ifndef GVIEWER_SINGLESIDEPLANE_H
#define GVIEWER_SINGLESIDEPLANE_H

#include "../CompositeSceneObject.h++"
#include "../../Basics/Polygon.h++"
#include "../../../Geometry/Basics/Point2.h++"
#include "../../Basics/Vertex.h++"
#include "../../Materials/IMaterial.h++"
#include "../../Materials/ColorMaterial.h++"


class SingleSidePlane: public CompositeSceneObject {
protected:
    double _width;
    double _height;
    double _depth;

    static SingleSidePlane constructWithCoords(Coordinate leftTop, Coordinate leftBottom, Coordinate rightBottom,
                                               Coordinate rightTop, const Vector& norm) {
        ShadingCoefficients sc = ShadingCoefficients(0.5, 0.5);

        Vertex leftTopV = Vertex( std::move(leftTop), TextureCoordinate(0, 0),norm,sc);
        Vertex leftBottomV = Vertex(std::move(leftBottom), TextureCoordinate(0, 1), norm, sc);
        Vertex rightBottomV = Vertex(std::move(rightBottom), TextureCoordinate(1, 1), norm, sc);
        Vertex rightTopV = Vertex(std::move(rightTop), TextureCoordinate(1, 0), norm, sc);

        Polygon p1 = Polygon(leftTopV, leftBottomV, rightTopV);
        Polygon p2 = Polygon(rightTopV, rightBottomV, leftBottomV);

        return {p1, p2};
    }

public:
    SingleSidePlane(const Polygon &p1, const Polygon &p2) : CompositeSceneObject() {
        origin = turnOrigin = scaleOrigin = (p1.getOrigin() + p2.getOrigin()) / 2.0;

        _width = p1.width() + p2.width();
        _height = p1.height() + p2.height();
        _depth = p1.depth() + p2.depth();

        subObjects.append(std::make_shared<Polygon>(p1));
        subObjects.append(std::make_shared<Polygon>(p2));
    }

    static SingleSidePlane oXY(const Coordinate &leftTop_, double width, double height, bool positiveNorm = true) noexcept {
        Coordinate leftTop = leftTop_;
        Coordinate leftBottom = Coordinate(leftTop.x, leftTop.y - height, leftTop.z);
        Coordinate rightBottom = Coordinate(leftTop.x + width, leftTop.y - height, leftTop.z);
        Coordinate rightTop = Coordinate(leftTop.x + width, leftTop.y, leftTop.z);
        Vector norm = Vector(0, 0, positiveNorm ? 1 : -1);

        return constructWithCoords(leftTop, leftBottom, rightBottom, rightTop, norm);
    }
    static SingleSidePlane oXZ(const Coordinate &leftTop_, double width, double height, bool positiveNorm = true) noexcept {
        Coordinate leftTop = leftTop_;
        Coordinate leftBottom = Coordinate(leftTop.x, leftTop.y, leftTop.z - height);
        Coordinate rightBottom = Coordinate(leftTop.x + width, leftTop.y, leftTop.z - height);
        Coordinate rightTop = Coordinate(leftTop.x + width, leftTop.y, leftTop.z);
        Vector norm = Vector(0, positiveNorm ? 1 : -1, 0);

        return constructWithCoords(leftTop, leftBottom, rightBottom, rightTop, norm);
    }
    static SingleSidePlane oYZ(const Coordinate &leftTop_, double width, double height, bool positiveNorm = true) noexcept {
        Coordinate leftTop = leftTop_;
        Coordinate leftBottom = Coordinate(leftTop.x, leftTop.y - height, leftTop.z);
        Coordinate rightBottom = Coordinate(leftTop.x, leftTop.y - height, leftTop.z + width);
        Coordinate rightTop = Coordinate(leftTop.x, leftTop.y, leftTop.z + width);
        Vector norm = Vector(positiveNorm ? 1 : -1, 0, 0);

        return constructWithCoords(leftTop, leftBottom, rightBottom, rightTop, norm);
    }

    SingleSidePlane(const SingleSidePlane &copy) = default;
    SingleSidePlane(SingleSidePlane &&move) noexcept = default;

    SingleSidePlane& operator = (const SingleSidePlane &copy) = default;
    SingleSidePlane& operator = (SingleSidePlane &&move) noexcept = default;

    Polygon& firstPolygon() { return dynamic_cast<Polygon&>(*(subObjects[0])); }
    Polygon& secondPolygon() { return dynamic_cast<Polygon&>(*(subObjects[1])); }

    void setTextureCoordinates(
            const TextureCoordinate &leftTopTx,
            const TextureCoordinate &leftBottomTx,
            const TextureCoordinate &rightBottomTx,
            const TextureCoordinate &rightTopTx) {
        Polygon& fst = firstPolygon();
        Polygon& scd = secondPolygon();

        fst.getV1().tx = leftTopTx;
        fst.getV2().tx = leftBottomTx;
        fst.getV3().tx = rightTopTx;

        scd.getV1().tx = rightTopTx;
        scd.getV2().tx = rightBottomTx;
        scd.getV3().tx = leftBottomTx;
    }

    [[nodiscard]] double width() const noexcept override { return _width * sf.x; }
    [[nodiscard]] double height() const noexcept override { return _height * sf.y; }
    [[nodiscard]] double depth() const noexcept override { return _depth * sf.z; }

    ~SingleSidePlane() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[SingleSidePlane id = " << id << ']';
        return sst.str();
    }

};

#endif //GVIEWER_SINGLESIDEPLANE_H
