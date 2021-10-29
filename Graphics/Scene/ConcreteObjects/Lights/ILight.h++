//
// Created by 17105727 on 07.10.2021.
//

#ifndef GVIEWER_ILIGHT_H
#define GVIEWER_ILIGHT_H

#include "../../BaseSceneObject.h++"
#include "../../../../Exceptions/Exception.h++"
#include "../../../../Graphics/Basics/Vertex.h++"


class ILight: public BaseSceneObject {
protected:
    unsigned short intensity = 128;

public:
    explicit ILight(unsigned short intensity = 128) : BaseSceneObject() { setIntensity(intensity); }

    ILight(const ILight &copy) noexcept = default;
    ILight(ILight &&move) noexcept = default;

    ILight& operator = (const ILight &copy) noexcept = default;
    ILight& operator = (ILight &&move) noexcept = default;

    [[nodiscard]] unsigned short getIntensity() const noexcept { return intensity; }

    void setIntensity(unsigned short intensity) {
        if (intensity > 255)
            throw BadArgumentError(EXC_PARAMS, "aIntensity must be in [0, 255] range");
        this->intensity = intensity;
    }

    [[nodiscard]] double width() const noexcept override { return 0; }
    [[nodiscard]] double height() const noexcept override { return 0; }
    [[nodiscard]] double depth() const noexcept override { return 0; }

    ~ILight() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[ILight id = " << id << ']';
        return sst.str();
    }

};

#endif //GVIEWER_ILIGHT_H
