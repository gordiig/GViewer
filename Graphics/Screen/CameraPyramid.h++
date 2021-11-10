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
    using Line = Pair<Vertex, Vertex>;

    Plane screenPlane = {{}, {}};
    Plane topPlane = {{}, {}};
    Plane bottomPlane = {{}, {}};
    Plane leftPlane = {{}, {}};
    Plane rightPlane = {{}, {}};

    /**
     * Creation of the new vertex, that located between two given
     * @param vtx1 Start vertex
     * @param vtx2 End vertex
     * @param k Parameter in interval of [0, 1]. Same as parameter in parametrized line equation
     * @return New vertex
     */
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

    /**
     * Function for calculating vertex on the point of the intersection between line and plane
     * Constraints, which are true for this class and this specific usage:
     * 1. Line is definitely intersects with plane
     * 2. Line is definitely not a point
     * @param line Line (pair of 2 vertixes)
     * @param plane Plane (pair of point and norm)
     * @return Vertex in the point of the intersection
     */
    [[nodiscard]] static Vertex findIntersectedVertex(const Line& line, const Plane& plane) noexcept {
        // Getting values from containers
        const auto& planeCoord = plane.first;
        const auto& planeNorm = plane.second;
        const auto& startPos = line.first.pos;
        const auto& endPos = line.second.pos;

        // Calculating A, B, C, D for canonic plane equation Ax + By + Cz + D = 0
        // TODO wrap it to geometry plane class
        const double a = planeNorm.x;
        const double b = planeNorm.y;
        const double c = planeNorm.z;
        const double d = -(planeNorm.x * planeCoord.x + planeNorm.y * planeCoord.y + planeNorm.z * planeCoord.z);

        // Calculating p for parametric line equation x = xs + (xe - xs) * p (same for y and z)
        const double deltaX = endPos.x - startPos.x;
        const double deltaY = endPos.y - startPos.y;
        const double deltaZ = endPos.z - startPos.z;
        const double numerator = -(a * startPos.x + b * startPos.y + c * startPos.z + d);
        const double denominator = a * deltaX + b * deltaY + c * deltaZ;
        const double p = numerator / denominator;

        return createNewVertexOnCut(line.first, line.second, p);
    }

    /**
     * Cutting figure by the given plane
     * @param plane Plane, that cuts the figure
     * @param vtxs Figure
     * @return Cutted figure
     */
    [[nodiscard]] static DynArray<Vertex> cutByPlane(const Plane& plane, const DynArray<Vertex>& vtxs) noexcept {
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
                Vertex newVertex = findIntersectedVertex({v1, v2}, plane);
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

        // Calculating angle tan for Oyz and Oxz
        const double ky = abs(cameraZ / screenHeightHalf);
        const double kx = abs(cameraZ / screenWidthHalf);

        // Initializing norms for all planes
        // When line's function is written as Ay + Bx + C = 0, norm is (B, A)
        // For example, take top plane on Oyz:
        // Two coordinates of line on x = 0 cut are (screenHeightHalf, 0) and (0, camZ)
        // So, equation for this line is z = ky * x + camZ
        // Which is equal to -ky * x + z - camZ = 0
        // So, norm to this line is (-ky, 1)
        // But, there are 2 norms for 1 line -- outer and inner
        // We now, that (-ky, 1) is inner, because our camera is looking to the +Z
        const Vector screenNorm(.0, .0, 1.0);
        const Vector topNorm(.0, -ky, 1.0);
        const Vector bottomNorm(.0, ky, 1.0);
        const Vector leftNorm(kx, .0, 1.0);
        const Vector rightNorm(-kx, .0, 1.0);

        // Initializing planes with coordinate and unit norm vectors
        screenPlane = Plane{coordForFirstPlane, screenNorm};
        topPlane = Plane{coordForPlanes, topNorm};
        bottomPlane = Plane{coordForPlanes, bottomNorm};
        rightPlane = Plane{coordForPlanes, rightNorm};
        leftPlane = Plane{coordForPlanes, leftNorm};
    }

    CameraPyramid(const CameraPyramid &copy) noexcept = default;
    CameraPyramid(CameraPyramid &&move) noexcept = default;

    CameraPyramid& operator = (const CameraPyramid &copy) noexcept = default;
    CameraPyramid& operator = (CameraPyramid &&move) noexcept = default;

    /**
     * Cutting figure with the camera pyramid
     * @param obj Uncutted figure
     * @return Cutted figure
     */
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
