//
// Created by 17105727 on 05.10.2021.
//

#ifndef GVIEWER_BASESCENEOBJECT_H
#define GVIEWER_BASESCENEOBJECT_H

#include <sstream>
#include "ISceneObject.h++"

class BaseSceneObject: public ISceneObject {
public:
    BaseSceneObject() : ISceneObject() {}

    BaseSceneObject(const BaseSceneObject &copy) = default;
    BaseSceneObject(BaseSceneObject &&move) noexcept = default;

    BaseSceneObject& operator = (const BaseSceneObject &copy) = default;
    BaseSceneObject& operator = (BaseSceneObject &&move) noexcept = default;

    void setOrigin(const Coordinate &coord) noexcept override { origin = coord; }
    void setTurnOrigin(const Coordinate &turnOrigin) noexcept override { this->turnOrigin = turnOrigin; }
    void setScaleOrigin(const Coordinate &scaleOrigin) noexcept override { this->scaleOrigin = scaleOrigin; }

    void turnTo(const AngleSystem &angs) noexcept override { angles = angs; }
    void scale(const ScaleFactor &sf) noexcept override { this->sf = sf; }

    void setMaterial(const std::shared_ptr<IMaterial> &material) noexcept override { this->material = material; }

    ~BaseSceneObject() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[BaseSceneObject id = " << id << ']';
        return sst.str();
    }

};

#endif //GVIEWER_BASESCENEOBJECT_H
