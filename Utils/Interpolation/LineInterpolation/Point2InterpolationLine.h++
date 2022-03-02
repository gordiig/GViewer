//
// Created by 17105727 on 16.11.2021.
//

#ifndef GVIEWER_POINT2INTERPOLATIONLINE_H
#define GVIEWER_POINT2INTERPOLATIONLINE_H

#include <utility>

#include "ILineInterpolatorLine.h++"
#include "../../Containers/Pair.h++"
#include "../../../Geometry/Basics/Point2.h++"


class Point2InterpolationLine: public ILineInterpolatorLine {
protected:
    using Point2D = Point2<double, double>;

    Point2D startPt;
    Point2D endPt;

public:
    Point2InterpolationLine(Point2D start, Point2D end) noexcept : startPt(std::move(start)), endPt(std::move(end)) {

    }

    Point2InterpolationLine(double startX, double startY, double endX, double endY) noexcept :
        Point2InterpolationLine({startX, startY}, {endX, endY}) {

    }

    [[nodiscard]] InterpolationLinePoint getLineStart() const noexcept override { return {startPt.x, startPt.y}; }
    [[nodiscard]] InterpolationLinePoint getLineEnd() const noexcept override { return {endPt.x, endPt.y}; }

    ~Point2InterpolationLine() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[Point2InterpolationLine]"; }
};

#endif //GVIEWER_POINT2INTERPOLATIONLINE_H
