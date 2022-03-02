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
#include "../Graphics/Scene/ConcreteObjects/Lights/DotLight.h++"
#include "../Graphics/Scene/ConcreteObjects/Cameras/ICamera.h++"
#include "../Graphics/Scene/ConcreteObjects/Cameras/Camera.h++"
#include "../Graphics/Screen/Render/Shaders/LambertShader.h++"
#include "../Graphics/Screen/Render/Shaders/SceletShader.h++"
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
        camera->scale(ScaleFactor(20.0, 20.0, 1));
//        camera->moveTo({0, 50, 0});
        settings.setCamera(camera);
        scene.addSubobject(camera);

        // Adding shader to settings
//        std::shared_ptr<IShader> shader = std::make_shared<SceletShader>(SceletShader());
        std::shared_ptr<IShader> shader = std::make_shared<LambertShader>(LambertShader());
        settings.setShader(shader);

        // Adding Renderer to settings
        renderer = std::make_shared<Renderer>(Renderer());
        settings.setRenderer(renderer);

        // Adding box to the scene
        std::shared_ptr<ISceneObject> box = std::make_shared<Box>(Box(10, 10, 5));
        Coordinate newBoxOrigin = {8, -7, 5};
        box->moveTo(newBoxOrigin);
        box->setTurnOrigin(newBoxOrigin);
        box->setScaleOrigin(newBoxOrigin);
        std::shared_ptr<IMaterial> colorMaterial = std::make_shared<ColorMaterial>(ColorMaterial(RGBA::white()));
        box->setMaterial(colorMaterial);
        scene.addSubobject(box);

        // Adding poly
//        double x = 300;
//        Vertex v1 = Vertex::zero();
//        v1.pos = {x, 100, 0};
//        Vertex v2 = Vertex::zero();
//        v2.pos = {x, 0, 0};
//        Vertex v3 = Vertex::zero();
//        v3.pos = {0, 0, 0};
//        std::shared_ptr<ISceneObject> box = std::make_shared<Polygon>(Polygon(v1, v2, v3));
//        Coordinate newBoxOrigin = {0, 0, 5};
//        box->moveTo(newBoxOrigin);
//        box->setTurnOrigin(newBoxOrigin);
//        box->setScaleOrigin(newBoxOrigin);
//        std::shared_ptr<IMaterial> colorMaterial = std::make_shared<ColorMaterial>(ColorMaterial(RGBA::white()));
//        box->setMaterial(colorMaterial);
//        scene.addSubobject(box);

        // Adding ambient light to the scene
//        std::shared_ptr<ISceneObject> alight = std::make_shared<AmbientLight>(AmbientLight(64));
//        scene.addSubobject(alight);
        std::shared_ptr<ISceneObject> dlight = std::make_shared<DotLight>(DotLight(255));
        scene.addSubobject(dlight);

        scene.setKa(0.2);
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
