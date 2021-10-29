//
// Created by 17105727 on 19.10.2021.
//

#ifndef GVIEWER_CAMERAPYRAMID_H
#define GVIEWER_CAMERAPYRAMID_H

#include "../Scene/ConcreteObjects/Cameras/ICamera.h++"
#include "../Basics/Vertex.h++"
#include "../../Utils/BaseObject.h++"
#include "../../Utils/Containers/DynArray.h++"
#include "../../Utils/Containers/Pair.h++"
#include "../../Geometry/Basics/Point3.h++"
#include "../../Geometry/Basics/Vector.h++"

class CameraPyramid: public BaseObject {
protected:
    using Plane = Pair<Coordinate, Vector>;

    Plane screenPlane = {{}, {}};
    Plane topPlane = {{}, {}};
    Plane bottomPlane = {{}, {}};
    Plane leftPlane = {{}, {}};
    Plane rightPlane = {{}, {}};

    [[nodiscard]] static Vertex createNewVertexOnCut(const Vertex &vtx1, const Vertex &vtx2, double k) noexcept {
        // Initializing ans vertex
        Vertex ans = Vertex::zero();

        // Getting reference to positions
        const auto& vtx1Pos = vtx1.pos;
        const auto& vtx2Pos = vtx2.pos;

        // Getting reference to tx
        const auto& vtx1Tx = vtx1.tx;
        const auto& vtx2Tx = vtx2.tx;

        // Getting sc on first vertex
        const auto& vtx1ScKd = vtx1.sc.getKd();
        const auto& vtx1ScKa = vtx1.sc.getKa();

        // Getting sc on second vertex
        const auto& vtx2ScKd = vtx2.sc.getKd();
        const auto& vtx2ScKa = vtx2.sc.getKa();

        // Getting reference to vectors
        const auto& vtx1Vec = vtx1.vec;
        const auto& vtx2Vec = vtx2.vec;

        // Calculating new vertex position
        ans.pos.x = vtx1Pos.x + k * (vtx2Pos.x - vtx1Pos.x);
        ans.pos.y = vtx1Pos.y + k * (vtx2Pos.y - vtx1Pos.y);
        ans.pos.z = vtx1Pos.z + k * (vtx2Pos.z - vtx1Pos.z);

        // Calculating new vertex tx
        ans.tx.x = vtx1Tx.x + k * (vtx2Tx.x - vtx1Tx.x);
        ans.tx.y = vtx1Tx.y + k * (vtx2Tx.y - vtx1Tx.y);

        // Calculating new vertex shading coefs
        ans.sc.setKd(vtx1ScKd + k * (vtx2ScKd - vtx1ScKd));
        ans.sc.setKa(vtx1ScKa + k * (vtx2ScKa - vtx1ScKa));

        // Calculating new vertex vectors
        ans.vec.x = vtx1Vec.x + k * (vtx2Vec.x - vtx1Vec.x);
        ans.vec.y = vtx1Vec.y + k * (vtx2Vec.y - vtx1Vec.y);
        ans.vec.z = vtx1Vec.z + k * (vtx2Vec.z - vtx1Vec.z);

        return ans;
    }

    [[nodiscard]] DynArray<Vertex> cutByPlane(const Plane& plane, const DynArray<Vertex> vtxs) const noexcept {
        // If no points given — return
        if (vtxs.isEmpty())
            return vtxs;

        // Initializing ans array
        DynArray<Vertex> ans;

        // Getting some values
        const size_t vtxsCount = vtxs.count();
        const Coordinate& planeCoord = plane.first;
        const Vector& planeNorm = plane.second;

        // Values needed for cutting
        double k;
        Vertex vtxToAppendOnCut = Vertex::zero();

        // Main loop
        for (int i = 0; i < vtxsCount; i++) {
            // Getting current line vertexes
            const Vertex v1 = vtxs[i];
            const Vertex v2 = vtxs[(i + 1) % vtxsCount];

            // Calculating vectors from point on plane to line corners
            const Vector vecToV1(planeCoord, v1.pos);
            const Vector vecToV2(planeCoord, v2.pos);

            // Getting cos between vectors and norm sign via scalar multiply
            const double cosBetweenNormAndVecToV1Sign = vecToV1.scalarMultiply(planeNorm);
            const double cosBetweenNormAndVecToV2Sign = vecToV2.scalarMultiply(planeNorm);

            // If first vertex is on the norm side of the plane
            if (cosBetweenNormAndVecToV1Sign >= 0)
                ans.append(v1);

            // Calculating bool values, that flags situation to cut the line
            bool v1InsideV2Outside = (cosBetweenNormAndVecToV1Sign > 0) && (cosBetweenNormAndVecToV2Sign < 0);
            bool v2InsideV1Outside = (cosBetweenNormAndVecToV1Sign < 0) && (cosBetweenNormAndVecToV2Sign >= 0);

            // Cutting if needed
            if (v1InsideV2Outside || v2InsideV1Outside) {
                k = 1 - planeNorm.scalarMultiply(v2.pos) / planeNorm.scalarMultiply(v1.pos);
                Vertex newVertex = createNewVertexOnCut(v1, v2, k);
                ans.append(newVertex);
            }
        }

        return ans;
    }

public:
    CameraPyramid() = delete;

    explicit CameraPyramid(const ICamera &camera) noexcept {
        // Getting some values from camera
        const double cameraZ = camera.getZCameraCoord();
        const double distFromCameraToScreen = camera.getScreenDistanceFromCamera();
        const double screenWidthHalf = (double) camera.getScreenWidth() / 2;
        const double screenHeightHalf = (double) camera.getScreenHeight() / 2;

        // Calculating coordinates for pyramid planes
        const Coordinate coordForFirstPlane{0, 0, cameraZ + distFromCameraToScreen};
        const Coordinate coordForPlanes{0, 0, cameraZ};

        // Initializing norms for all planes
        const Vector screenNorm(0, 0, 1);
        const Vector topNorm(0, -distFromCameraToScreen, screenHeightHalf);
        const Vector bottomNorm(0, distFromCameraToScreen, screenHeightHalf);
        const Vector leftNorm(-distFromCameraToScreen, 0, screenWidthHalf);
        const Vector rightNorm(-distFromCameraToScreen, 0, screenWidthHalf);

        // Initializing planes with coordinate and unit norm vectors
        screenPlane = Plane{coordForFirstPlane, screenNorm};
        topPlane = Plane{coordForPlanes, topNorm.normalized()};
        bottomPlane = Plane{coordForPlanes, bottomNorm.normalized()};
        rightPlane = Plane{coordForPlanes, rightNorm.normalized()};
        leftPlane = Plane{coordForPlanes, leftNorm.normalized()};
    }

    CameraPyramid(const CameraPyramid &copy) noexcept = default;
    CameraPyramid(CameraPyramid &&move) noexcept = default;

    CameraPyramid& operator = (const CameraPyramid &copy) noexcept = default;
    CameraPyramid& operator = (CameraPyramid &&move) noexcept = default;

    [[nodiscard]] DynArray<Vertex> cutObject(const DynArray<Vertex> &obj) const {
        // Cutting figure with all planes
        auto cuttedByScreenPlane = cutByPlane(screenPlane, obj);
        auto cuttedByLeftPlane = cutByPlane(leftPlane, cuttedByScreenPlane);
        auto cuttedByRightPlane = cutByPlane(rightPlane, cuttedByLeftPlane);
        auto cuttedByTopPlane = cutByPlane(topPlane, cuttedByRightPlane);
        auto cuttedByBottomPlane = cutByPlane(bottomPlane, cuttedByTopPlane);

        return cuttedByBottomPlane;
    }

    ~CameraPyramid() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[CameraPyramid]"; }
};

#endif //GVIEWER_CAMERAPYRAMID_H
