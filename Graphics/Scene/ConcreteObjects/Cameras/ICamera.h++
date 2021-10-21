//
// Created by 17105727 on 07.10.2021.
//

#ifndef GVIEWER_ICAMERA_H
#define GVIEWER_ICAMERA_H

#include <sstream>
#include <utility>
#include "../../BaseSceneObject.h++"
#include "../../../../Geometry/Basics/Vector.h++"
#include "../../../../Geometry/Basics/Angle.h++"


class ICamera: public BaseSceneObject {
protected:
    double zCameraCoord = -5;
    double zScreenCoord = 0;
    size_t screenWidth;
    size_t screenHeight;

    void setKa(double ka) override { }

public:
    ICamera(size_t screenWidth, size_t screenHeight) noexcept : screenWidth(screenWidth), screenHeight(screenHeight) {}

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

    ~ICamera() noexcept override = default;

    [[nodiscard]] std::string toString() const noexcept override {
        std::stringstream sst;
        sst << "[ICamera id = " << id << ']';
        return sst.str();
    }

};

#endif //GVIEWER_ICAMERA_H
