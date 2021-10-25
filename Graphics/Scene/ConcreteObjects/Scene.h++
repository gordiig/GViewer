//
// Created by 17105727 on 25.10.2021.
//

#ifndef GVIEWER_SCENE_H
#define GVIEWER_SCENE_H

#include "../CompositeSceneObject.h++"
#include "../../Basics/RGBA.h++"
#include "../../../Settings/Settings.h++"

class Scene: public CompositeSceneObject {
protected:
    RGBA backgroundColor;

public:
    explicit Scene(RGBA bgColor = RGBA::black()) : CompositeSceneObject(), backgroundColor(std::move(bgColor)) { }

    Scene(const Scene &copy) = default;
    Scene(Scene &&move) = default;

    Scene& operator = (const Scene &copy) = default;
    Scene& operator = (Scene &&move) = default;

    [[nodiscard]] const RGBA &getBackgroundColor() const { return backgroundColor; }
    void setBackgroundColor(const RGBA &bgColor) { backgroundColor = bgColor; }

    // Overriding methods to do nothing
    void setOrigin(const Coordinate &coord) noexcept override { }
    void setTurnOrigin(const Coordinate &turnOrigin) noexcept override { }
    void setScaleOrigin(const Coordinate &scaleOrigin) noexcept override { }
    void turnTo(const AngleSystem &angs) noexcept override { }
    void scale(const ScaleFactor &sf) noexcept override { }
    void moveTo(const Coordinate &coord) noexcept override { }
    void setMaterial(const std::shared_ptr<IMaterial> &material) noexcept override { }
    [[nodiscard]] double width() const noexcept override { return 0.0; }
    [[nodiscard]] double height() const noexcept override { return 0.0; }
    [[nodiscard]] double depth() const noexcept override { return 0.0; }

    void setToRender() const override {
        const auto &s = Settings::getInstance();
        auto &r = s.getRenderer();
        r.setBackgroundColor(backgroundColor);

        for (const auto& subObj : subObjects)
            subObj->setToRender();
    }

    ~Scene() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[Scene]"; }

};

#endif //GVIEWER_SCENE_H
