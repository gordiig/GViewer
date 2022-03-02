//
// Created by 17105727 on 20.10.2021.
//

#ifndef GVIEWER_IRENDERABLELIGHT_H
#define GVIEWER_IRENDERABLELIGHT_H

#include "../IRenderable.h++"
#include "../../../Screen.h++"
#include "../../../../Basics/Vertex.h++"
#include "../../../../Scene/ConcreteObjects/Lights/ILight.h++"
#include "../../../../../Geometry/Basics/Vector.h++"
#include "../../../../../Geometry/Basics/Point3.h++"
#include "../../../../../Geometry/Transform/PointTransformer.h++"
#include "../../../../../Utils/Containers/RangedValue.h++"

class ICamera;

class IRenderableLight: public IRenderable {
protected:
    Coordinate lightPosition;
    RangedValue<short> lightIntensity;

    // Do not draw lights yet
    void transformToCameraSpace() override { }
    void cutByCameraPyramid() override { }
    void projectToScreen() override { }
    void transformToScreenSpace() override { }
    Screen drawObject() override { return EMPTY_SCREEN; }

    // Do not draw lights yet
    [[nodiscard]] bool testFigure() const noexcept override { return true; }

public:
    const static short MAX_INTENSITY;

    explicit IRenderableLight(const ILight &light) noexcept :
            IRenderable(), lightPosition(light.getOrigin()), lightIntensity(light.getIntensity()) {
        PointTransformer::turn(lightPosition, light.getAngles(), light.getTurnOrigin());
    }

    IRenderableLight(const IRenderableLight &copy) noexcept = default;
    IRenderableLight(IRenderableLight &&move) noexcept = default;

    IRenderableLight& operator = (const IRenderableLight &copy) noexcept = default;
    IRenderableLight& operator = (IRenderableLight &&move) noexcept = default;

    virtual RangedValue<short> getIntensity(const Vertex &vertex) = 0;

    // Do not draw lights yet
    Screen render() override { return EMPTY_SCREEN; }

    ~IRenderableLight() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[IRenderableLight]"; }
};

#endif //GVIEWER_IRENDERABLELIGHT_H