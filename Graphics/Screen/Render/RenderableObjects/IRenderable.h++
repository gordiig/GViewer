//
// Created by 17105727 on 11.10.2021.
//

#ifndef GVIEWER_IRENDERABLE_H
#define GVIEWER_IRENDERABLE_H

#include <sstream>
#include <utility>
#include <optional>

#include "../../../../Utils/BaseObject.h++"
#include "../../../../Utils/Containers/DynArray.h++"
#include "../../../../Geometry/Basics/Point2.h++"
#include "../../../Basics/Vertex.h++"
#include "../../../Materials/IMaterial.h++"

class Screen;
class ICamera;

class IRenderable: public BaseObject {
protected:
    const static Screen EMPTY_SCREEN;
    std::shared_ptr<ICamera> camera;

    virtual void transformToCameraSpace() = 0;
    virtual void cutByCameraPyramid() = 0;
    virtual void projectToScreen() = 0;
    virtual void transformToScreenSpace() = 0;
    virtual Screen drawObject() = 0;

public:
    explicit IRenderable(std::shared_ptr<ICamera> camera) noexcept : camera(std::move(camera)) {}

    IRenderable(const IRenderable &copy) = default;
    IRenderable(IRenderable &&move) noexcept = default;

    IRenderable& operator = (const IRenderable &copy) = default;
    IRenderable& operator = (IRenderable &&move) noexcept = default;

    [[nodiscard]] virtual Screen render() = 0;

    ~IRenderable() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[IRenderable]"; }
};

const Screen IRenderable::EMPTY_SCREEN = {0, 0, {0, 0}};

#endif //GVIEWER_IRENDERABLE_H
