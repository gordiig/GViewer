//
// Created by 17105727 on 30.09.2021.
//

#ifndef GVIEWER_ISCENEOBJECT_H
#define GVIEWER_ISCENEOBJECT_H

#include <sstream>
#include "../../Utils/Containers/DynArray.h++"
#include "../../Geometry/Basics/Point3.h++"
#include "../../Geometry/Utils/AngleSystem.h++"
#include "../../Geometry/Utils/ScaleFactor.h++"

class ISceneObject: public BaseObject {
protected:
    Coordinate origin;
    Coordinate turnOrigin;
    Coordinate scaleOrigin;

    AngleSystem angles;
    ScaleFactor sf;

    DynArray<std::unique_ptr<ISceneObject>> subObjects;

    static unsigned long long idCounter;
    unsigned long long id;
public:
    [[nodiscard]] virtual const Coordinate& getOrigin() const noexcept { return origin; }
    [[nodiscard]] virtual const Coordinate &getTurnOrigin() const noexcept { return turnOrigin; }
    [[nodiscard]] virtual const Coordinate &getScaleOrigin() const noexcept { return scaleOrigin; }

    [[nodiscard]] virtual const AngleSystem& getAngles() const { return angles; }
    [[nodiscard]] virtual const ScaleFactor& getSf() const { return sf; }

    [[nodiscard]] virtual const DynArray<std::unique_ptr<ISceneObject>>& getSubObjects() const noexcept {
        return subObjects;
    }

    [[nodiscard]] unsigned long long getId() const noexcept { return id; }

    virtual void setOrigin(const Coordinate &coord) noexcept = 0;
    virtual void setTurnOrigin(const Coordinate &turnOrigin) noexcept = 0;
    virtual void setScaleOrigin(const Coordinate &scaleOrigin) noexcept = 0;

    virtual void moveTo(const Coordinate &coord) noexcept { setOrigin(coord); }
    virtual void turnTo(const AngleSystem &angs) noexcept = 0;
    virtual void scale(const ScaleFactor &sf) noexcept = 0;

    virtual void setToRender() const = 0;

    [[nodiscard]] virtual std::unique_ptr<ISceneObject> copy() const = 0;

    ~ISceneObject() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[ISceneObject id = " << id << ']';
        return sst.str();
    }

};

unsigned long long ISceneObject::idCounter = 0;


#endif //GVIEWER_ISCENEOBJECT_H
