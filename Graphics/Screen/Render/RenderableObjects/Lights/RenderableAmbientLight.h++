//
// Created by 17105727 on 20.10.2021.
//

#ifndef GVIEWER_RENDERABLEAMBIENTLIGHT_H
#define GVIEWER_RENDERABLEAMBIENTLIGHT_H

#include "IRenderableLight.h++"
#include "../../../../Scene/ConcreteObjects/Lights/AmbientLight.h++"
#include "../../../../Basics/Vertex.h++"
#include "../../../../../Geometry/Basics/Vector.h++"

class ICamera;

class RenderableAmbientLight: public IRenderableLight {
public:
    explicit RenderableAmbientLight(const AmbientLight &light) noexcept : IRenderableLight(light) { }

    RenderableAmbientLight(const RenderableAmbientLight &copy) noexcept = default;
    RenderableAmbientLight(RenderableAmbientLight &&move) noexcept = default;

    RenderableAmbientLight& operator = (const RenderableAmbientLight &copy) noexcept = default;
    RenderableAmbientLight& operator = (RenderableAmbientLight &&move) noexcept = default;

    unsigned short getIntensity(const Vertex &vertex) override {
        // Initializing some variables for later
        unsigned short ans;
        double ka = vertex.sc.getKa();

        // Calculating intensity based on ambient
        ans = (unsigned short) ((double) lightIntensity * ka);

        // Returning resulting intensity as min between max possible intensity and calculated intensity
        return std::min(ans, MAX_INTENSITY);
    }

    ~RenderableAmbientLight() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[RenderableAmbientLight]"; }
};

#endif //GVIEWER_RENDERABLEAMBIENTLIGHT_H
