//
// Created by 17105727 on 11.10.2021.
//

#ifndef GVIEWER_IRENDERABLE_H
#define GVIEWER_IRENDERABLE_H

#include "../../Screen.h++"
#include "../../../Basics/Vertex.h++"
#include "../../../Materials/IMaterial.h++"
#include "../../../../Utils/BaseObject.h++"
#include "../../../../Utils/Containers/DynArray.h++"
#include "../../../../Geometry/Basics/Point2.h++"
#include "../../../../Settings/Settings.h++"

class ICamera;
class IShader;

class IRenderable: public BaseObject {
protected:
    const static Screen EMPTY_SCREEN;
    std::shared_ptr<ICamera> camera;
    std::shared_ptr<IShader> shader;

    virtual void transformToCameraSpace() = 0;
    virtual void cutByCameraPyramid() = 0;
    virtual void projectToScreen() = 0;
    virtual void transformToScreenSpace() = 0;
    virtual Screen drawObject() = 0;

    [[nodiscard]] virtual bool testFigure() const noexcept = 0;

public:
    IRenderable() noexcept {
        const auto& settings = Settings::getInstance();
        camera = settings.getCameraPtr();
        shader = settings.getShaderPtr();
    }

    IRenderable(const IRenderable &copy) = default;
    IRenderable(IRenderable &&move) noexcept = default;

    IRenderable& operator = (const IRenderable &copy) = default;
    IRenderable& operator = (IRenderable &&move) noexcept = default;

    [[nodiscard]] virtual Screen render() = 0;

    ~IRenderable() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[IRenderable]"; }
};

#endif //GVIEWER_IRENDERABLE_H
