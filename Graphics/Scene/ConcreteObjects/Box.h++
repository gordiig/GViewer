//
// Created by 17105727 on 06.10.2021.
//

#ifndef GVIEWER_BOX_H
#define GVIEWER_BOX_H

#include <sstream>
#include "../CompositeSceneObject.h++"
#include "../../Materials/IMaterial.h++"
#include "../../../Geometry/Basics/Point3.h++"
#include "../../../Geometry/Basics/Vector.h++"
#include "SingleSidePlane.h++"


class Box: public CompositeSceneObject {
private:
    using TX = TextureCoordinate;

    double _width;
    double _height;
    double _depth;

public:
    Box(const Coordinate &leftTopClosest, double width, double height, double depth) noexcept : CompositeSceneObject() {
        const double oneThird = 1.0 / 3.0;
        const double twoThirds = 2.0 / 3.0;

        _width = width;
        _height = height;
        _depth = depth;

        origin = turnOrigin = scaleOrigin = Coordinate(
                (leftTopClosest.x + width) / 2.0,
                (leftTopClosest.y - height) / 2.0,
                (leftTopClosest.z + depth) / 2.0);

        SingleSidePlane oXYClosestPlane = SingleSidePlane::oXY(
                leftTopClosest,
                width,
                height,
                false);
        SingleSidePlane oXYDeepestPlane = SingleSidePlane::oXY(
                Coordinate(leftTopClosest.x, leftTopClosest.y, leftTopClosest.z + depth),
                width,
                height,
                true);
        SingleSidePlane oXZTopPlane = SingleSidePlane::oXZ(
                Coordinate(leftTopClosest.x, leftTopClosest.y, leftTopClosest.z + depth),
                width,
                depth,
                true);
        SingleSidePlane oXZBottomPlane = SingleSidePlane::oXZ(
                Coordinate(leftTopClosest.x, leftTopClosest.y - height, leftTopClosest.z + depth),
                width,
                depth,
                false);
        SingleSidePlane oYZLeftPlane = SingleSidePlane::oYZ(
                leftTopClosest,
                depth,
                height,
                false);
        SingleSidePlane oYZRightPlane = SingleSidePlane::oYZ(
                Coordinate(leftTopClosest.x + width, leftTopClosest.y, leftTopClosest.z),
                depth,
                height,
                true);

        oXYClosestPlane.setTextureCoordinates(
                TX(0.25, oneThird),
                TX(0, oneThird),
                TX(0, twoThirds),
                TX(0.25, twoThirds));
        oXZTopPlane.setTextureCoordinates(
                TX(0.5, oneThird),
                TX(0.25, oneThird),
                TX(0.25, twoThirds),
                TX(0.5, twoThirds));
        oXYDeepestPlane.setTextureCoordinates(
                TX(0.75, oneThird),
                TX(0.5, oneThird),
                TX(0.5, twoThirds),
                TX(0.75, twoThirds));
        oXZBottomPlane.setTextureCoordinates(
                TX(0.75, oneThird),
                TX(1, oneThird),
                TX(1, twoThirds),
                TX(0.75, twoThirds));
        oYZLeftPlane.setTextureCoordinates(
                TX(0.25, oneThird),
                TX(0.25, 0),
                TX(0.5, 0),
                TX(0.5, oneThird));
        oYZRightPlane.setTextureCoordinates(
                TX(0.25, twoThirds),
                TX(0.25, 1),
                TX(0.5, 1),
                TX(0.5, twoThirds));

        subObjects.append(std::make_unique<SingleSidePlane>(std::move(oXYClosestPlane)));
        subObjects.append(std::make_unique<SingleSidePlane>(std::move(oXYDeepestPlane)));
        subObjects.append(std::make_unique<SingleSidePlane>(std::move(oXZTopPlane)));
        subObjects.append(std::make_unique<SingleSidePlane>(std::move(oXZBottomPlane)));
        subObjects.append(std::make_unique<SingleSidePlane>(std::move(oYZLeftPlane)));
        subObjects.append(std::make_unique<SingleSidePlane>(std::move(oYZRightPlane)));
    }

    Box(const Box &copy) noexcept = default;
    Box(Box &&copy) noexcept = default;

    Box& operator = (const Box &copy) noexcept = default;
    Box& operator = (Box &&copy) noexcept = default;

    [[nodiscard]] double width() const noexcept override { return _width * sf.x; }
    [[nodiscard]] double height() const noexcept override { return _height * sf.y; }
    [[nodiscard]] double depth() const noexcept override { return _depth * sf.z; }

    [[nodiscard]] std::unique_ptr<ISceneObject> copyUnique() const override {
        Box copy(*this);
        return std::make_unique<Box>(std::move(copy));
    }
    [[nodiscard]] std::shared_ptr<ISceneObject> copyShared() const override {
        Box copy(*this);
        return std::make_shared<Box>(std::move(copy));
    }

    ~Box() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[Box id = " << id << ']';
        return sst.str();
    }

};

#endif //GVIEWER_BOX_H
