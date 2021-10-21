//
// Created by 17105727 on 05.10.2021.
//

#ifndef GVIEWER_RENDERER_H
#define GVIEWER_RENDERER_H

#include <sstream>
#include "../../../Utils/BaseObject.h++"
#include "../../../Utils/Containers/DynArray.h++"
#include "../../Scene/ISceneObject.h++"
#include "../Screen.h++"
#include "IRenderer.h++"


class Renderer: public BaseObject, public IRenderer {
public:
    Renderer() noexcept = default;

    Renderer(const Renderer &copy) noexcept = default;
    Renderer(Renderer &&move) noexcept = default;

    Renderer& operator = (const Renderer &copy) noexcept = default;
    Renderer& operator = (Renderer &&move) noexcept = default;

    ~Renderer() noexcept override = default;

    Screen render() override {
        // TODO
        objectsToRender.clear();
    }

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "Renderer";
        return sst.str();
    }

};


#endif //GVIEWER_RENDERER_H
