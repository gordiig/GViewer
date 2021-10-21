//
// Created by 17105727 on 20.10.2021.
//

#ifndef GVIEWER_RENDERABLEDOTLIGHT_H
#define GVIEWER_RENDERABLEDOTLIGHT_H

#include "IRenderableLight.h++"
#include "../../../../Scene/ConcreteObjects/Lights/DotLight.h++"
#include "../../../../Basics/Vertex.h++"
#include "../../../../../Geometry/Basics/Vector.h++"

class ICamera;

class RenderableDotLight: public IRenderableLight {
public:
    RenderableDotLight(const DotLight &light, std::shared_ptr<ICamera> &camera) noexcept : IRenderableLight(light, camera) { }

    RenderableDotLight(const RenderableDotLight &copy) noexcept = default;
    RenderableDotLight(RenderableDotLight &&move) noexcept = default;

    RenderableDotLight& operator = (const RenderableDotLight &copy) noexcept = default;
    RenderableDotLight& operator = (RenderableDotLight &&move) noexcept = default;

    unsigned short getIntensity(const Vertex &vertex) override {
        // Initializing some variables for later
        unsigned short ans;
        double cosForDiffuse;
        double diffuse;
        double kd = vertex.sc.getKd();

        // Initializing vector from vertex to light source
        Vector vtxToLightVector(vertex.pos, lightPosition);

        // Calculating cos between norm and prev vector
        cosForDiffuse = vtxToLightVector.cosBetweenVectors(vertex.vec);

        // Calculating diffuse light
        diffuse = cosForDiffuse * kd;

        // Calculating intensity based on diffuse (ambient is calculating on special light source)
        ans = (unsigned short) ((double) lightIntensity * diffuse);

        // Returning resulting intensity as min between max possible intensity and calculated intensity
        return std::min(ans, MAX_INTENSITY);
    }

    ~RenderableDotLight() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[RenderableDotLight]"; }
};

#endif //GVIEWER_RENDERABLEDOTLIGHT_H
