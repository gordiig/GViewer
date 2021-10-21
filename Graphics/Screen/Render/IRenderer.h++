//
// Created by 17105727 on 05.10.2021.
//

#ifndef GVIEWER_IRENDERER_H
#define GVIEWER_IRENDERER_H

#include "../../../Utils/Containers/DynArray.h++"
#include "../Screen.h++"


// For reduction of circular includes
class IRenderable;
class ILight;


class IRenderer {
protected:
    DynArray<std::shared_ptr<IRenderable>> objectsToRender;
    DynArray<std::shared_ptr<ILight>> lights;

public:
    IRenderer() noexcept = default;

    IRenderer(const IRenderer &copy) noexcept = default;
    IRenderer(IRenderer &&move) noexcept = default;

    IRenderer& operator = (const IRenderer &copy) noexcept = default;
    IRenderer& operator = (IRenderer &&move) noexcept = default;

    virtual void addToRender(std::shared_ptr<IRenderable> &&obj) { objectsToRender.append(std::move(obj)); }
    virtual void addToRender(std::shared_ptr<ILight> &&light) { lights.append(std::move(light)); }

    virtual Screen render() = 0;

    virtual ~IRenderer() = default;
};

#endif //GVIEWER_IRENDERER_H
