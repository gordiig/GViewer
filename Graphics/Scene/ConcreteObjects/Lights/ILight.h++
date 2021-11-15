//
// Created by 17105727 on 07.10.2021.
//

#ifndef GVIEWER_ILIGHT_H
#define GVIEWER_ILIGHT_H

#include "../../BaseSceneObject.h++"
#include "../../../../Exceptions/Exception.h++"
#include "../../../../Graphics/Basics/Vertex.h++"
#include "../../../../Utils/Containers/RangedValue.h++"


class ILight: public BaseSceneObject {
protected:
    RangedValue<unsigned short> intensity;

public:
    explicit ILight(unsigned short intensity = 128) : BaseSceneObject(), intensity(intensity, 0, 255) {

    }

    ILight(const ILight &copy) noexcept = default;
    ILight(ILight &&move) noexcept = default;

    ILight& operator = (const ILight &copy) noexcept = default;
    ILight& operator = (ILight &&move) noexcept = default;

    [[nodiscard]] inline RangedValue<unsigned short > getIntensity() const noexcept { return intensity; }

    inline void setIntensity(unsigned short value) { this->intensity = value; }

    [[nodiscard]] inline double width() const noexcept override { return 0; }
    [[nodiscard]] inline double height() const noexcept override { return 0; }
    [[nodiscard]] inline double depth() const noexcept override { return 0; }

    ~ILight() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[ILight id = " << id << ']';
        return sst.str();
    }

};

#endif //GVIEWER_ILIGHT_H
