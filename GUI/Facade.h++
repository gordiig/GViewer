//
// Created by 17105727 on 25.10.2021.
//

#ifndef GVIEWER_FACADE_H
#define GVIEWER_FACADE_H

#include "../Utils/BaseObject.h++"
#include "../Graphics/Screen/Screen.h++"
#include "../Graphics/Scene/ConcreteObjects/Scene.h++"
#include "../Graphics/Scene/ConcreteObjects/Box.h++"
#include "../Graphics/Scene/ConcreteObjects/Lights/AmbientLight.h++"
#include "../Graphics/Scene/ConcreteObjects/Cameras/ICamera.h++"
#include "../Graphics/Scene/ConcreteObjects/Cameras/Camera.h++"
#include "../Graphics/Screen/Render/Shaders/LambertShader.h++"
#include "../Graphics/Screen/Render/IRenderer.h++"
#include "../Graphics/Screen/Render/Renderer.h++"
#include "../Graphics/Materials/IMaterial.h++"
#include "../Graphics/Materials/ColorMaterial.h++"


class Facade: public BaseObject {
protected:
    size_t screenWidth;
    size_t screenHeight;
    Scene scene;
    std::shared_ptr<ICamera> camera;
    std::shared_ptr<IRenderer> renderer;

public:
    Facade(size_t screenWidth, size_t screenHeight) :
            screenWidth(screenWidth), screenHeight(screenHeight), scene() {
        auto& settings = Settings::getInstance();

        // Adding camera to settings and scene
        camera = std::make_shared<Camera>(Camera(screenWidth, screenHeight));
        settings.setCamera(camera);
        scene.addSubobject(camera);

        // Adding shader to settings
        std::shared_ptr<IShader> shader = std::make_shared<LambertShader>(LambertShader());
        settings.setShader(shader);

        // Adding Renderer to settings
        renderer = std::make_shared<Renderer>(Renderer());
        settings.setRenderer(renderer);

        // Adding box to the scene
        std::shared_ptr<ISceneObject> box = std::make_shared<Box>(Box(20, 20, 20));
        Coordinate newBoxOrigin = {0, 0, 20};
        box->moveTo(newBoxOrigin);
        box->setTurnOrigin(newBoxOrigin);
        box->setScaleOrigin(newBoxOrigin);
        std::shared_ptr<IMaterial> colorMaterial = std::make_shared<ColorMaterial>(ColorMaterial(RGBA::white()));
        box->setMaterial(colorMaterial);
        scene.addSubobject(box);

        // Adding ambient light to the scene
        std::shared_ptr<ISceneObject> light = std::make_shared<AmbientLight>(AmbientLight(128));
        scene.addSubobject(light);
    }

    Screen render() {
        renderer->clear();
        scene.setToRender();
        return renderer->render();
    }

    ~Facade() override = default;

    [[nodiscard]] std::string toString() const override { return "[Facade]"; }
};




#endif //GVIEWER_FACADE_H
