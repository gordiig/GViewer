//
// Created by 17105727 on 07.10.2021.
//

#ifndef GVIEWER_DOTLIGHT_H
#define GVIEWER_DOTLIGHT_H

#include "ILight.h++"


// TURN_POSITION НУЖНО ОТДЕЛЬНЫМ ОТ ПОЗОШН ДЕЛАТЬ (0, 0, 0) — иначе крутиться вокруг себя будет — а это нам не надо
class DotLight: public ILight {
public:
    explicit DotLight(unsigned short intensity) : ILight(intensity) { }

    DotLight(const DotLight &copy) noexcept = default;
    DotLight(DotLight &&move) noexcept = default;

    DotLight& operator = (const DotLight &copy) noexcept = default;
    DotLight& operator = (DotLight &&move) noexcept = default;

    void setToRender() const override;

    ~DotLight() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[DotLight id = " << id << ", int = " << intensity << ']';
        return sst.str();
    }

};

#endif //GVIEWER_DOTLIGHT_H
