//
// Created by 17105727 on 13.10.2021.
//

#ifndef GVIEWER_ISHADER_H
#define GVIEWER_ISHADER_H

#include "../../../Utils/Containers/DynArray.h++"
#include "../../../Utils/Containers/Pair.h++"
#include "../../../Graphics/Basics/Vertex.h++"
#include "../../../Geometry/Basics/Point2.h++"
#include "../../../Utils/BaseObject.h++"
#include "../../../Utils/Interpolator.h++"
#include "../../../Utils/LineInterpolator.h++"

class Screen;
class IRenderable;
class ICamera;
class ILight;

class IShader: public BaseObject {
protected:
    DynArray<std::shared_ptr<ILight>> lights{};

    using VertexLine = Pair<ScreenVertex, ScreenVertex>;

    [[nodiscard]] static LineInterpolator<size_t, double> getTxInterpolator(const VertexLine &line) noexcept {
        Point2 lineStart2D = {line.first.pos.x, line.first.pos.y};
        Point2 lineEnd2D = {line.second.pos.x, line.second.pos.y};
        Point2 lineStartTx = {line.first.tx.x, line.first.tx.y};
        Point2 lineEndTx = {line.second.tx.x, line.second.tx.y};

        LineInterpolator<size_t, double> ans({lineStart2D, lineEnd2D}, {lineStartTx, lineEndTx});
        return ans;
    }

    [[nodiscard]] static Interpolator<size_t, double> getZInterpolatorByY(const VertexLine &line) {
        Point2 lineStart2D = {line.first.pos.x, line.first.pos.y};
        Point2 lineEnd2D = {line.second.pos.x, line.second.pos.y};
        double lineStartZ = line.first.pos.z;
        double lineEndZ = line.second.pos.z;

        Interpolator<size_t, double> ans({lineStart2D.y, lineEnd2D.y}, {lineStartZ, lineEndZ});
        return ans;
    }

public:
    virtual Screen shade(const DynArray<Vertex>& figure, const DynArray<ScreenVertex>& screenVertex) = 0;

    virtual void configure(const DynArray<std::shared_ptr<ILight>> &lights) {
        this->lights = lights;
    }

    ~IShader() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[IShader]"; }
};

#endif //GVIEWER_ISHADER_H
