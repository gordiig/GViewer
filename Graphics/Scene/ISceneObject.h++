//
// Created by 17105727 on 30.09.2021.
//

#ifndef GVIEWER_ISCENEOBJECT_H
#define GVIEWER_ISCENEOBJECT_H

#include <sstream>
#include "../../Utils/Containers/DynArray.h++"
#include "../../Geometry/Basics/Point3.h++"
#include "../../Geometry/Basics/Vector.h++"
#include "../../Geometry/Utils/AngleSystem.h++"
#include "../../Geometry/Utils/ScaleFactor.h++"
#include "../../Graphics/Materials/IMaterial.h++"

class ISceneObject: public BaseObject {
    friend class CompositeSceneObject;

protected:
    Coordinate origin;
    Coordinate turnOrigin;
    Coordinate scaleOrigin;

    AngleSystem angles;
    ScaleFactor sf;

    std::shared_ptr<IMaterial> material;

    DynArray<std::shared_ptr<ISceneObject>> subObjects;

    static unsigned long long idCounter;
    unsigned long long id;

    virtual void setKa(double ka) = 0;

public:
    [[nodiscard]] virtual const Coordinate &getOrigin() const noexcept { return origin; }
    [[nodiscard]] virtual const Coordinate &getTurnOrigin() const noexcept { return turnOrigin; }
    [[nodiscard]] virtual const Coordinate &getScaleOrigin() const noexcept { return scaleOrigin; }

    [[nodiscard]] virtual const AngleSystem& getAngles() const { return angles; }
    [[nodiscard]] virtual const ScaleFactor& getSf() const { return sf; }

    [[nodiscard]] virtual const IMaterial& getMaterial() const { return *material; }
    [[nodiscard]] virtual const std::shared_ptr<IMaterial>& getMaterialPtr() const { return material; }

    [[nodiscard]] virtual const DynArray<std::shared_ptr<ISceneObject>>& getSubObjects() const noexcept {
        return subObjects;
    }

    [[nodiscard]] unsigned long long getId() const noexcept { return id; }

    virtual void setOrigin(const Coordinate &coord) noexcept = 0;
    virtual void setTurnOrigin(const Coordinate &turnOrigin) noexcept = 0;
    virtual void setScaleOrigin(const Coordinate &scaleOrigin) noexcept = 0;

    virtual void moveTo(const Coordinate &coord) noexcept { setOrigin(coord); }
    virtual void turnTo(const AngleSystem &angs) noexcept = 0;
    virtual void scale(const ScaleFactor &sf) noexcept = 0;

    virtual void setMaterial (const std::shared_ptr<IMaterial> &material) noexcept = 0;

    [[nodiscard]] virtual double width() const noexcept = 0;
    [[nodiscard]] virtual double height() const noexcept = 0;
    [[nodiscard]] virtual double depth() const noexcept = 0;

    virtual void setToRender() const = 0;

    ~ISceneObject() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[ISceneObject id = " << id << ']';
        return sst.str();
    }

};

unsigned long long ISceneObject::idCounter = 0;


#endif //GVIEWER_ISCENEOBJECT_H
