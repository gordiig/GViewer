//
// Created by 17105727 on 05.10.2021.
//

#ifndef GVIEWER_IRENDERER_H
#define GVIEWER_IRENDERER_H

#include "../../Basics/RGBA.h++"
#include "../../../Utils/BaseObject.h++"
#include "../../../Utils/Containers/DynArray.h++"

// For reduction of circular includes
class IRenderable;
class IRenderableLight;
class Screen;


class IRenderer: public BaseObject {
protected:
    RGBA backgroundColor;
    DynArray<std::shared_ptr<IRenderable>> objectsToRender;
    DynArray<std::shared_ptr<IRenderableLight>> lights;

public:
    IRenderer() noexcept = default;

    IRenderer(const IRenderer &copy) noexcept = default;
    IRenderer(IRenderer &&move) noexcept = default;

    IRenderer& operator = (const IRenderer &copy) noexcept = default;
    IRenderer& operator = (IRenderer &&move) noexcept = default;

    virtual void addToRender(std::shared_ptr<IRenderable> &&obj) { objectsToRender.append(std::move(obj)); }
    virtual void addToRender(std::shared_ptr<IRenderableLight> &&light) { lights.append(std::move(light)); }

    virtual void setBackgroundColor(const RGBA &bgColor) { backgroundColor = bgColor; }

    virtual Screen render() = 0;

    virtual void clear() noexcept {
        objectsToRender.clear();
        lights.clear();
    }

    ~IRenderer() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[IRenderer]"; }

};

#endif //GVIEWER_IRENDERER_H
