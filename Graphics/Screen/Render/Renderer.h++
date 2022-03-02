//
// Created by 17105727 on 05.10.2021.
//

#ifndef GVIEWER_RENDERER_H
#define GVIEWER_RENDERER_H

#include "IRenderer.h++"
#include "Shaders/IShader.h++"
#include "RenderableObjects/IRenderable.h++"
#include "../Screen.h++"
#include "../../Scene/ConcreteObjects/Cameras/ICamera.h++"
#include "../../../Settings/Settings.h++"
#include "../../../Utils/Containers/DynArray.h++"


class Renderer: public IRenderer {
public:
    Renderer() noexcept = default;

    Renderer(const Renderer &copy) noexcept = default;
    Renderer(Renderer &&move) noexcept = default;

    Renderer& operator = (const Renderer &copy) noexcept = default;
    Renderer& operator = (Renderer &&move) noexcept = default;

    Screen render() override {
        // Getting shader and configuring it with lights
        const auto& settings = Settings::getInstance();
        auto& shader = settings.getShader();
        shader.addLights(lights);

        // Getting camera screen size
        const auto& camera = settings.getCamera();
        const size_t screenWidth = camera.getScreenWidth();
        const size_t screenHeight = camera.getScreenHeight();

        // Initializing screen with 0 offset
        Screen ans = Screen(screenWidth, screenHeight, {0, 0}, backgroundColor);

        // Initializing temp screen for every figure
        Screen currentFigureScreen{0, 0, {0, 0}};
//        for (int i = 0; i < objectsToRender.count(); i++) {
//            const auto& figure = objectsToRender[i];
        for (const auto& figure : objectsToRender) {
            // Rendering current figure, and applying its screen to the main screen
            currentFigureScreen = figure->render();
            ans.apply(currentFigureScreen);
        }

        return ans;
    }

    ~Renderer() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[Rederer]"; }

};


#endif //GVIEWER_RENDERER_H
