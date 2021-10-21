//
// Created by 17105727 on 13.10.2021.
//

#ifndef GVIEWER_RENDERABLEPOLYGON_H
#define GVIEWER_RENDERABLEPOLYGON_H

#include "Renderable3DObject.h++"
#include "../../../../Basics/Polygon.h++"
#include "../../../../Scene/ConcreteObjects/Cameras/ICamera.h++"
#include "../../../../Materials/IMaterial.h++"
#include "../../../../../Utils/Interpolator.h++"
#include "../../../../../Utils/LineInterpolator.h++"
#include "../../../../../Geometry/Basics/Vector.h++"
#include "../../../../../Geometry/Transform/PointTransformer.h++"
#include "../../../../../Settings/Settings.h++"

class RenderablePolygon: public Renderable3DObject {
protected:
    std::shared_ptr<IMaterial> material;

    [[nodiscard]] static LineInterpolator<size_t, double> getLineInterpolatorTx(const VertexLine &line) noexcept {
        Point2 lineStart2D = {line.first.pos.x, line.first.pos.y};
        Point2 lineEnd2D = {line.second.pos.x, line.second.pos.y};
        Point2 lineStartTx = {line.first.tx.x, line.first.tx.y};
        Point2 lineEndTx = {line.second.tx.x, line.second.tx.y};

        LineInterpolator<size_t, double> ans({lineStart2D, lineEnd2D}, {lineStartTx, lineEndTx});
        return ans;
    }

    [[nodiscard]] static Interpolator<size_t, double> getInterpolatorZByY(const VertexLine &line) {
        Point2 lineStart2D = {line.first.pos.x, line.first.pos.y};
        Point2 lineEnd2D = {line.second.pos.x, line.second.pos.y};
        double lineStartZ = line.first.pos.z;
        double lineEndZ = line.second.pos.z;

        Interpolator<size_t, double> ans({lineStart2D.y, lineEnd2D.y}, {lineStartZ, lineEndZ});
        return ans;
    }

    void transformToCameraSpace() override {
        const auto &cameraOrigin = camera->getOrigin();
        const auto cameraOriginNeg = -cameraOrigin;
        const auto &cameraAnglesNeg = -camera->getAngles();

        for (auto &vtx : vtxs) {
            auto &vtxCoord = vtx.pos;
            auto &vtxVec = vtx.vec;

            PointTransformer::move(vtxCoord, cameraOriginNeg);
            PointTransformer::move(vtxVec, cameraOriginNeg);

            PointTransformer::turn(vtxCoord, cameraAnglesNeg, cameraOrigin);
            PointTransformer::turn(vtxVec, cameraAnglesNeg, cameraOrigin);
        }
    }

    void cutByCameraPyramid() override {
        Settings& settings = Settings::getInstance();
        CameraPyramid& cameraPyramid = settings.getCameraPyramid();
        vtxs = cameraPyramid.cutObject(vtxs);
    }

    void projectToScreen() override {
        projectedVtxs.reserve(vtxs.count());
        const double distanceFromCameraToScreen = camera->getScreenDistanceFromCamera();
        Vertex appendee = Vertex::zero();

        for (const auto &vtx : vtxs) {
            const auto &vtxPos = vtx.pos;
            const double absZ = abs(vtxPos.z);
            const double denominator = distanceFromCameraToScreen + absZ;

            appendee = vtx;
            appendee.pos.x = distanceFromCameraToScreen * vtxPos.x / denominator;
            appendee.pos.y = distanceFromCameraToScreen * vtxPos.y / denominator;
            projectedVtxs.append(appendee);
        }
    }

    void transformToScreenSpace() override {
        screenVtxs.reserve(projectedVtxs.count());

        ScreenCoordinate screenCoordinate = ScreenCoordinate::zero();
        ScreenVertex screenVertex = ScreenVertex::zero();
        size_t screenWidth = camera->getScreenWidth();
        size_t screenHeight = camera->getScreenHeight();

        for (const auto &vtx : projectedVtxs) {
            const auto &vtxPos = vtx.pos;

            screenCoordinate.x = screenWidth + (int) vtxPos.x;
            screenCoordinate.y = screenHeight - (int) vtxPos.y;
            screenCoordinate.z = vtxPos.z;

            screenVertex.pos = screenCoordinate;
            screenVertex.vec = vtx.vec;
            screenVertex.tx = vtx.tx;
            screenVertex.sc = vtx.sc;

            screenVtxs.append(screenVertex);
        }
    }

    Screen drawObject() override {
        // Getting screen width and height
        const auto [screenWidth, screenHeight] = getScreenSize();
        if (screenWidth == 0 || screenHeight == 0)
            return {0, 0, {0, 0}};

        // Initializing screen
        Screen screen(screenWidth, screenHeight);

        // Getting top vtx info
        const long topYCoordIdx = findTopScreenCoordIdx();
        const auto& topYVtx = screenVtxs[topYCoordIdx];
        size_t sy = topYVtx.pos.y;

        // Getting vtxs count
        const long screenVtxsCount = (long) screenVtxs.count();

        // Calculating indexes for first 2 lines
        long idx1 = topYCoordIdx - 1;
        long idx2 = (topYCoordIdx + 1) % screenVtxsCount;

        // Initializing pairs for first and second lines
        Pair line1{screenVtxs[topYCoordIdx], screenVtxs[idx1]};
        Pair line2{screenVtxs[topYCoordIdx], screenVtxs[idx2]};

        // Initializing interpolators
        LineInterpolator line1InterpolatorTx = getLineInterpolatorTx(line1);
        LineInterpolator line2InterpolatorTx = getLineInterpolatorTx(line2);
        Interpolator line1ZInterpolatorByY = getInterpolatorZByY(line1);
        Interpolator line2ZInterpolatorByY = getInterpolatorZByY(line2);

        // Getting bottom vtx y
        const auto& bottomYVtx = std::max_element(
                screenVtxs.begin(),
                screenVtxs.end(),
                [](const ScreenVertex& v1, const ScreenVertex& v2) {
                    return v1.pos.y > v2.pos.y;
                });
        const size_t bottomY = bottomYVtx->pos.y;

        // Main loop
        size_t x1, x2;
        while (sy <= bottomY) {
            // For readability
            const auto& topPt1 = line1.first;
            const auto& topPt1Pos = topPt1.pos;
            const auto& topPt2 = line2.first;
            const auto& topPt2Pos = topPt2.pos;
            const auto& bottomPt1 = line1.second;
            const auto& bottomPt1Pos = bottomPt1.pos;
            const auto& bottomPt2 = line2.second;
            const auto& bottomPt2Pos = bottomPt2.pos;

            // Calculating x for first line
            if (bottomPt1Pos.y == topPt1Pos.y)
                x1 = bottomPt1Pos.x;
            else
                x1 = topPt1Pos.x + (sy - topPt1Pos.y) * (bottomPt1Pos.x - topPt1Pos.x) / (bottomPt1Pos.y - topPt1Pos.y);

            // Calculating x for second line
            if (bottomPt2Pos.y == topPt2Pos.y)
                x2 = bottomPt2Pos.x;
            else
                x2 = topPt2Pos.x + (sy - topPt2Pos.y) * (bottomPt2Pos.x - topPt2Pos.x) / (bottomPt2Pos.y - topPt2Pos.y);

            // Getting tx and z from both lines
            Point2 line1Tx = line1InterpolatorTx.interpolate({x1, sy});
            Point2 line2Tx = line2InterpolatorTx.interpolate({x2, sy});
            double line1Z = line1ZInterpolatorByY.interpolate(sy);
            double line2Z = line2ZInterpolatorByY.interpolate(sy);

            // Swap x1 and x2 if needed
            if (x1 > x2) {
                std::swap(x1, x2);
                std::swap(line1Tx, line2Tx);
                std::swap(line1Z, line2Z);
            }

            // Initializing tx, ty and z interpolator
            Interpolator<size_t, double> txInterpolator({x1, x2}, {line1Tx.x, line2Tx.x});
            Interpolator<size_t, double> tyInterpolator({x1, x2}, {line1Tx.y, line2Tx.y});
            Interpolator<size_t, double> zInterpolator({x1, x2}, {line1Z, line2Z});

            // Draw line
            double tx, ty, z;
            for (size_t x = x1; x <= x2; x++) {
                tx = txInterpolator.interpolate(x);
                ty = tyInterpolator.interpolate(x);
                z = zInterpolator.interpolate(x);
                screen.setPixelColor(x, sy, material->getColor(tx, ty), z);
            }

            // Changing first line and line interpolator if needed
            if (sy == bottomPt1.pos.y) {
                idx1--;
                line1.first = line1.second;
                line1.second = screenVtxs[idx1];
                line1InterpolatorTx = getLineInterpolatorTx(line1);
                line1ZInterpolatorByY = getInterpolatorZByY(line1);
            }

            // Changing second line if needed
            if (sy == bottomPt2.pos.y) {
                idx2 = (idx2 + 1) % screenVtxsCount;
                line2.first = line2.second;
                line2.second = screenVtxs[idx2];
                line2InterpolatorTx = getLineInterpolatorTx(line2);
                line2ZInterpolatorByY = getInterpolatorZByY(line2);
            }

            // Going down
            sy += 1;
        }

        return screen;
    }

public:
    explicit RenderablePolygon(const Polygon &polygon, const std::shared_ptr<ICamera>& camera) :
            Renderable3DObject({}, camera), material(polygon.getMaterialPtr()) {
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
        PointTransformer::transform(v1.vec, origin,
                                    angles, turnOrigin,
                                    sf, scaleOrigin);

        PointTransformer::transform(v2.pos, origin,
                                    angles, turnOrigin,
                                    sf, scaleOrigin);
        PointTransformer::transform(v2.vec, origin,
                                    angles, turnOrigin,
                                    sf, scaleOrigin);

        PointTransformer::transform(v3.pos, origin,
                                    angles, turnOrigin,
                                    sf, scaleOrigin);
        PointTransformer::transform(v3.vec, origin,
                                    angles, turnOrigin,
                                    sf, scaleOrigin);

        vtxs = {v1, v2, v3};
    }

    RenderablePolygon(const RenderablePolygon &copy) = default;
    RenderablePolygon(RenderablePolygon &&move) noexcept = default;

    RenderablePolygon& operator = (const RenderablePolygon &copy) = default;
    RenderablePolygon& operator = (RenderablePolygon &&move) noexcept = default;

    [[nodiscard]] Screen render() override {
        if (vtxs.isEmpty())
            return {0, 0, {0, 0}};

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
