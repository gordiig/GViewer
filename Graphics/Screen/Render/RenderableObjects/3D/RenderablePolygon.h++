//
// Created by 17105727 on 13.10.2021.
//

#ifndef GVIEWER_RENDERABLEPOLYGON_H
#define GVIEWER_RENDERABLEPOLYGON_H

#include "Renderable3DObject.h++"
#include "../../Shaders/IShader.h++"
#include "../../../../Basics/Polygon.h++"
#include "../../../../Scene/ConcreteObjects/Cameras/ICamera.h++"
#include "../../../../Materials/IMaterial.h++"
#include "../../../../../Utils/Interpolation/Interpolator.h++"
#include "../../../../../Utils/Interpolation/LineInterpolation/LineInterpolator.h++"
#include "../../../../../Geometry/Basics/Vector.h++"
#include "../../../../../Geometry/Transform/PointTransformer.h++"
#include "../../../../../Settings/Settings.h++"

class RenderablePolygon: public Renderable3DObject {
protected:
    std::shared_ptr<IMaterial> material;

    void transformToCameraSpace() override {
        // Initializing some variables for later
        const auto &cameraOrigin = camera->getOrigin();
        const auto cameraOriginNeg = -cameraOrigin;
        const auto &cameraAnglesNeg = -camera->getAngles();
        const auto &cameraScales = camera->getSf();

        // Reserving memory for vtxs in camera space array
        vtxsInCameraSpace.reserve(vtxs.count());

        for (const auto &vtx : vtxs) {
            // Getting position and norm vector of current vertex
            Vertex newVertex(vtx);
            auto& newVertexPos = newVertex.pos;
            auto& newVertexVec = newVertex.vec;

            // Moving, turning and scaling vertex and vector in mirrored direction of camera origin
            // If camera moves or turn to the left — object will move right on the screen, but for scale it's not neg
            PointTransformer::transform(newVertexPos, cameraOriginNeg,
                                        cameraAnglesNeg, cameraOrigin,
                                        cameraScales, cameraOrigin);
            PointTransformer::transform(newVertexVec, cameraOriginNeg,
                                        cameraAnglesNeg, cameraOrigin,
                                        cameraScales, cameraOrigin);

            vtxsInCameraSpace.append(newVertex);
        }
    }

    void cutByCameraPyramid() override {
        Settings& settings = Settings::getInstance();
        CameraPyramid& cameraPyramid = settings.getCameraPyramid();
        vtxsCuttedByCameraPyramid = cameraPyramid.cutObject(vtxsInCameraSpace);
    }

    void projectToScreen() override {
        // Reserving space for projected vertixes — same amount as cutted
        projectedVtxs.reserve(vtxsCuttedByCameraPyramid.count());

        // Initializing needed variables
        const double distanceFromCameraToScreen = camera->getScreenDistanceFromCamera();
        Vertex appendee = Vertex::zero();

        for (const auto &vtx : vtxsCuttedByCameraPyramid) {
            // Getting needed positions from current vtx, and initializing denominator for perspective
            const auto &vtxPos = vtx.pos;
            const double absZ = abs(vtxPos.z);
            const double denominator = distanceFromCameraToScreen + absZ;

            // Calculating new x and y for vtx
            appendee = vtx;
            appendee.pos.x = distanceFromCameraToScreen * vtxPos.x / denominator;
            appendee.pos.y = distanceFromCameraToScreen * vtxPos.y / denominator;
            projectedVtxs.append(appendee);
        }
    }

    void transformToScreenSpace() override {
        // Reserving space for screen vtxs — same amount as projected vtxs
        screenVtxs.reserve(projectedVtxs.count());

        // Initializing some variables, that we are going to use later
        ScreenCoordinate screenCoordinate = ScreenCoordinate::zero();
        ScreenVertex screenVertex = ScreenVertex::zero();
        size_t screenWidthHalf = camera->getScreenWidth() / 2;
        size_t screenHeightHalf = camera->getScreenHeight() / 2;

        for (const auto &vtx : projectedVtxs) {
            // Getting position of current vtx
            const auto &vtxPos = vtx.pos;

            // Transforming coordinate of projected vtx to screen space
            // 1. Screen has discrete graphics — pixels. So, x and y must be integers
            // 2. Projected vtxs had positions, relative to the camera space (camera was at the center of Oxy),
            // but screen origin at the left top corner. Because of that we need to move projected vtx.
            // Z remains the same
            screenCoordinate.x = screenWidthHalf + (int) vtxPos.x;
            screenCoordinate.y = screenHeightHalf - (int) vtxPos.y;
            screenCoordinate.z = vtxPos.z;

            // Setting new position to screen vertex
            // All other vtx values stay the same — they don't depend on projection
            // To be honest, I think norm does, but fuck it,
            // It's easier to have several arrays of vtxs for different calculations
            screenVertex.pos = screenCoordinate;
            screenVertex.vec = vtx.vec;
            screenVertex.tx = vtx.tx;
            screenVertex.sc = vtx.sc;

            screenVtxs.append(screenVertex);
        }
    }

    Screen drawObject() override {
        const auto& settings = Settings::getInstance();
        auto& shader = settings.getShader();
        Screen ans = shader.shade(vtxs, screenVtxs, *material);
        return ans;
    }

public:
    explicit RenderablePolygon(const Polygon &polygon) :
            Renderable3DObject({}), material(polygon.getMaterialPtr()) {
        Vertex v1 = polygon.getV1();
        Vertex v2 = polygon.getV2();
        Vertex v3 = polygon.getV3();

        const auto& origin = polygon.getOrigin();
        const auto& angles = polygon.getAngles();
        const auto& turnOrigin = polygon.getTurnOrigin();
        const auto& sf = polygon.getSf();
        const auto& scaleOrigin = polygon.getScaleOrigin();

        PointTransformer::transform(v1.pos, origin,
                                    angles, turnOrigin,
                                    sf, scaleOrigin);
        PointTransformer::turn(v1.vec, angles, turnOrigin);

        PointTransformer::transform(v2.pos, origin,
                                    angles, turnOrigin,
                                    sf, scaleOrigin);
        PointTransformer::turn(v2.vec, angles, turnOrigin);

        PointTransformer::transform(v3.pos, origin,
                                    angles, turnOrigin,
                                    sf, scaleOrigin);
        PointTransformer::turn(v3.vec, angles, turnOrigin);

        vtxs = {v1, v2, v3};
    }

    RenderablePolygon(const RenderablePolygon &copy) = default;
    RenderablePolygon(RenderablePolygon &&move) noexcept = default;

    RenderablePolygon& operator = (const RenderablePolygon &copy) = default;
    RenderablePolygon& operator = (RenderablePolygon &&move) noexcept = default;

    [[nodiscard]] Screen render() override {
        if (vtxs.isEmpty() || !testFigure())
            return EMPTY_SCREEN;

        transformToCameraSpace();
        cutByCameraPyramid();
        projectToScreen();
        transformToScreenSpace();
        Screen ans = drawObject();

        return ans;
    }

    ~RenderablePolygon() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[RenderablePolygon]"; }

};

#endif //GVIEWER_RENDERABLEPOLYGON_H
