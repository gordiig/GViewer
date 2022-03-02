//
// Created by 17105727 on 25.10.2021.
//

#ifndef GVIEWER_CAMERA_H
#define GVIEWER_CAMERA_H

#include "ICamera.h++"


class Camera: public ICamera {
public:
    Camera(size_t screenWidth, size_t screenHeight) : ICamera(screenWidth, screenHeight) {

    }

    Camera(const Camera &copy) = default;
    Camera(Camera &&move) noexcept = default;

    Camera& operator = (const Camera &copy) = default;
    Camera& operator = (Camera &&move) noexcept = default;

    [[nodiscard]] double width() const noexcept override { return 0; }
    [[nodiscard]] double height() const noexcept override { return 0; }
    [[nodiscard]] double depth() const noexcept override { return 0; }

    void setToRender() const override { }

    ~Camera() noexcept override = default;

    [[nodiscard]] std::string toString() const noexcept override { return "[Camera]"; }
};

#endif //GVIEWER_CAMERA_H
