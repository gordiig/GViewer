//
// Created by 17105727 on 05.10.2021.
//

#ifndef GVIEWER_COMPOSITESCENEOBJECT_H
#define GVIEWER_COMPOSITESCENEOBJECT_H

#include <sstream>
#include "ISceneObject.h++"
#include "../../Utils/BaseObject.h++"
#include "../../Utils/Containers/DynArray.h++"
#include "../../Geometry/Basics/Point3.h++"
#include "../../Geometry/Utils/AngleSystem.h++"
#include "../../Geometry/Utils/ScaleFactor.h++"


class CompositeSceneObject: public ISceneObject {
protected:
    [[nodiscard]] DynArray<std::unique_ptr<ISceneObject>> copySubObjs() const {
        DynArray<std::unique_ptr<ISceneObject>> newVec;
        newVec.reserve(subObjects.count());

        for (auto &obj : subObjects)
            newVec.append(obj->copy());

        return newVec;
    }

public:
    CompositeSceneObject() noexcept { id = idCounter++; }

    CompositeSceneObject(const CompositeSceneObject &copy) : CompositeSceneObject() {
        if (this == &copy)
            return;
        *this = copy;
    }
    CompositeSceneObject(CompositeSceneObject &&copy) noexcept : CompositeSceneObject() { *this = copy; }

    CompositeSceneObject& operator = (const CompositeSceneObject &copy) {
        this->origin = origin;
        this->turnOrigin = turnOrigin;
        this->scaleOrigin = scaleOrigin;
        this->angles = angles;
        this->sf = sf;
        this->subObjects = std::move(copy.copySubObjs());

        return *this;
    }
    CompositeSceneObject& operator = (CompositeSceneObject &&move) noexcept {
        this->origin = std::move(origin);
        this->turnOrigin = std::move(turnOrigin);
        this->scaleOrigin = std::move(scaleOrigin);
        this->angles = std::move(angles);
        this->sf = std::move(sf);
        this->subObjects = std::move(move.copySubObjs());

        return *this;
    }

    void setOrigin(const Coordinate &coord) noexcept override {
        Coordinate coordForSubobj;
        for (auto& obj : subObjects) {
            // У сабайтемов другие ориджины, которые должны сместиться в точку, отличающуюся от coord
            // Точка в которую они переносятся рассчитывается как `coord - (this.origin - obj.origin)`
            coordForSubobj = coord - this->origin + obj->getOrigin();
            obj->setOrigin(coordForSubobj);
        }
        origin = coord;
    }
    void setTurnOrigin(const Coordinate &turnOrigin) noexcept override {
        Coordinate coordForSubobj;
        for (auto& obj : subObjects) {
            // У сабайтемов другие ориджины, которые должны сместиться в точку, отличающуюся от coord
            // Точка в которую они переносятся рассчитывается как `coord - (this.origin - obj.origin)`
            coordForSubobj = turnOrigin - this->origin + obj->getTurnOrigin();
            obj->setTurnOrigin(coordForSubobj);
        }
        this->turnOrigin = turnOrigin;
    }
    void setScaleOrigin(const Coordinate &scaleOrigin) noexcept override {
        Coordinate coordForSubobj;
        for (auto& obj : subObjects) {
            // У сабайтемов другие ориджины, которые должны сместиться в точку, отличающуюся от coord
            // Точка в которую они переносятся рассчитывается как `coord - (this.origin - obj.origin)`
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

    void addToSubObjects(std::unique_ptr<ISceneObject> &&obj) { subObjects.append(std::move(obj)); }

    void setToRender() const override {
        for (auto &obj : subObjects)
            obj->setToRender();
    }

    [[nodiscard]] std::unique_ptr<ISceneObject> copy() const override {
        CompositeSceneObject newObj = *this;
        return std::make_unique<CompositeSceneObject>(newObj);
    }

    ~CompositeSceneObject() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[CompositeSceneObject id = " << id << ']';
        return sst.str();
    }
};

#endif //GVIEWER_COMPOSITESCENEOBJECT_H
