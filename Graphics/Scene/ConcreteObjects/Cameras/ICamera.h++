//
// Created by 17105727 on 07.10.2021.
//

#ifndef GVIEWER_ICAMERA_H
#define GVIEWER_ICAMERA_H


#include "../../BaseSceneObject.h++"
#include "../../../../Geometry/Basics/Vector.h++"
#include "../../../../Geometry/Basics/Angle.h++"
#include "../../../../Geometry/Transform/PointTransformer.h++"


class ICamera: public BaseSceneObject {
protected:
    double zCameraCoord = -5;
    double zScreenCoord = 0;
    size_t screenWidth;
    size_t screenHeight;

public:
    ICamera(size_t screenWidth, size_t screenHeight) noexcept : screenWidth(screenWidth - 1), screenHeight(screenHeight - 1) {}

    ICamera(const ICamera &copy) noexcept = default;
    ICamera(ICamera &&move) noexcept = default;

    ICamera& operator = (const ICamera &copy) noexcept = default;
    ICamera& operator = (ICamera &&move) noexcept = default;

    [[nodiscard]] double getZCameraCoord() const noexcept { return zCameraCoord; }
    [[nodiscard]] double getZScreenCoord() const noexcept { return zScreenCoord; }
    [[nodiscard]] double getScreenDistanceFromCamera() const noexcept { return abs(zScreenCoord - zCameraCoord); }

    [[nodiscard]] Angle getFovX() const noexcept {
        double tgX = (double) screenWidth / 2 / getScreenDistanceFromCamera();
        Angle ans = Angle::initAtan(tgX);
        return ans;
    }
    [[nodiscard]] Angle getFovY() const noexcept {
        double tgY = (double) screenHeight / 2 / getScreenDistanceFromCamera();
        Angle ans = Angle::initAtan(tgY);
        return ans;
    }

    [[nodiscard]] size_t getScreenWidth() const noexcept { return screenWidth; }
    [[nodiscard]] size_t getScreenHeight() const noexcept { return screenHeight; }

    [[nodiscard]] Vector getSightVector() const noexcept {
        // Initializing default sight vector for camera
        Vector defaultSightVector{0, 0, 1};

        // Transforming it to current camera position in global space
        PointTransformer::move(defaultSightVector, getOrigin());
        PointTransformer::turn(defaultSightVector, getAngles(), getTurnOrigin());

        return defaultSightVector;
    }

    ~ICamera() noexcept override = default;

    [[nodiscard]] std::string toString() const noexcept override {
        std::stringstream sst;
        sst << "[ICamera id = " << id << ']';
        return sst.str();
    }

};

#endif //GVIEWER_ICAMERA_H
