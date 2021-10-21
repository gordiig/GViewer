
//
// Created by 17105727 on 20.10.2021.
//

#ifndef GVIEWER_AMBIENTLIGHT_H
#define GVIEWER_AMBIENTLIGHT_H

#include <sstream>
#include "../../../../Settings/Settings.h++"
#include "../../../Screen/Render/IRenderer.h++"
#include "ILight.h++"


class AmbientLight: public ILight {
public:
    explicit AmbientLight (unsigned short intensity) : ILight(intensity) { }

    AmbientLight (const AmbientLight &copy) noexcept = default;
    AmbientLight (AmbientLight &&move) noexcept = default;

    AmbientLight& operator = (const AmbientLight &copy) noexcept = default;
    AmbientLight& operator = (AmbientLight &&move) noexcept = default;

    void setToRender() const override {
        Settings& s = Settings::getInstance();
        IRenderer& r = s.getRenderer();

        // TODO
    }

    ~AmbientLight() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[AmbientLight id = " << id << ", int = " << intensity << ']';
        return sst.str();
    }

};

#endif //GVIEWER_AMBIENTLIGHT_H
