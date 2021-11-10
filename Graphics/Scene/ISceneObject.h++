//
// Created by 17105727 on 30.09.2021.
//

#ifndef GVIEWER_ISCENEOBJECT_H
#define GVIEWER_ISCENEOBJECT_H

#include <memory>
#include "../../Utils/Containers/DynArray.h++"
#include "../../Geometry/Basics/Point3.h++"
#include "../../Geometry/Basics/Vector.h++"
#include "../../Geometry/Utils/AngleSystem.h++"
#include "../../Geometry/Utils/ScaleFactor.h++"

class IMaterial;


class ISceneObject: public BaseObject {
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

public:
    ISceneObject() : origin(), turnOrigin(), scaleOrigin(), angles(), sf(), material(nullptr), subObjects() {
        id = idCounter++;
    }

    ISceneObject(const ISceneObject &copy) = default;
    ISceneObject(ISceneObject &&move) noexcept = default;

    ISceneObject& operator = (const ISceneObject &copy) = default;
    ISceneObject& operator = (ISceneObject &&move) noexcept = default;

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


#endif //GVIEWER_ISCENEOBJECT_H
