//
// Created by 17105727 on 05.10.2021.
//

#ifndef GVIEWER_IRENDERER_H
#define GVIEWER_IRENDERER_H

#include <vector>

#include "../../Utils/Containers/DynArray.h++"
#include "../Scene/ISceneObject.h++"
#include "Screen.h++"


class IRenderer {
protected:
//    DynArray<std::unique_ptr<ISceneObject>> objectsToRender;
    std::vector<std::unique_ptr<ISceneObject>> objectsToRender;

public:
    IRenderer() noexcept = default;

    IRenderer(const IRenderer &copy) noexcept = default;
    IRenderer(IRenderer &&move) noexcept = default;

    IRenderer& operator = (const IRenderer &copy) noexcept = default;
    IRenderer& operator = (IRenderer &&move) noexcept = default;

    virtual void addToRender(std::unique_ptr<ISceneObject> &&obj) { objectsToRender.push_back(std::move(obj)); }

    virtual Screen render() = 0;

    virtual ~IRenderer() = default;
};

#endif //GVIEWER_IRENDERER_H
