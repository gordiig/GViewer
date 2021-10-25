//
// Created by 17105727 on 05.10.2021.
//

#ifndef GVIEWER_COMPOSITESCENEOBJECT_H
#define GVIEWER_COMPOSITESCENEOBJECT_H

#include "ISceneObject.h++"
#include "../../Utils/BaseObject.h++"
#include "../../Utils/Containers/DynArray.h++"
#include "../../Geometry/Basics/Point3.h++"
#include "../../Geometry/Utils/AngleSystem.h++"
#include "../../Geometry/Utils/ScaleFactor.h++"


class CompositeSceneObject: public ISceneObject {
protected:
    void setKa(double ka) override {
        for (auto& subObj : subObjects)
            subObj->setKa(ka);
    }

public:
    CompositeSceneObject() : ISceneObject() { }

    CompositeSceneObject(const CompositeSceneObject &copy) = default;
    CompositeSceneObject(CompositeSceneObject &&move) noexcept = default;

    CompositeSceneObject& operator = (const CompositeSceneObject &copy) = default;
    CompositeSceneObject& operator = (CompositeSceneObject &&move) noexcept = default;

    void setOrigin(const Coordinate &coord) noexcept override {
        Coordinate coordForSubobj;
        for (auto& obj : subObjects) {
            // Subitems have different origins, and they must move to the point, different from coord
            // Point, where they need to move, equals `coord - (this.origin - obj.origin)`
            coordForSubobj = coord - this->origin + obj->getOrigin();
            obj->setOrigin(coordForSubobj);
        }
        origin = coord;
    }
    void setTurnOrigin(const Coordinate &turnOrigin) noexcept override {
        Coordinate coordForSubobj;
        for (auto& obj : subObjects) {
            // Subitems have different origins, and they must move to the point, different from coord
            // Point, where they need to move, equals `coord - (this.origin - obj.origin)`
            coordForSubobj = turnOrigin - this->origin + obj->getTurnOrigin();
            obj->setTurnOrigin(coordForSubobj);
        }
        this->turnOrigin = turnOrigin;
    }
    void setScaleOrigin(const Coordinate &scaleOrigin) noexcept override {
        Coordinate coordForSubobj;
        for (auto& obj : subObjects) {
            // Subitems have different origins, and they must move to the point, different from coord
            // Point, where they need to move, equals `coord - (this.origin - obj.origin)`
            coordForSubobj = scaleOrigin - this->scaleOrigin + obj->getScaleOrigin();
            obj->setScaleOrigin(coordForSubobj);
        }
        this->scaleOrigin = scaleOrigin;
    }

    void turnTo(const AngleSystem &angs) noexcept override {
        angles = angs;
        for (auto &obj : subObjects)
            obj->turnTo(angs);
    }
    void scale(const ScaleFactor &sf) noexcept override  {
        this->sf = sf;
        for (auto &obj : subObjects)
            obj->scale(sf);
    }

    void setMaterial(const std::shared_ptr<IMaterial> &material) noexcept override {
        this->material = material;
        for (auto &obj : subObjects)
            obj->setMaterial(material);
    }

    void setToRender() const override {
        for (const auto &obj : subObjects)
            obj->setToRender();
    }

    ~CompositeSceneObject() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[CompositeSceneObject id = " << id << ']';
        return sst.str();
    }
};

#endif //GVIEWER_COMPOSITESCENEOBJECT_H
