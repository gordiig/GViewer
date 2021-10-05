//
// Created by 17105727 on 01.10.2021.
//

#ifndef GVIEWER_POINTTRANSFORMER_H
#define GVIEWER_POINTTRANSFORMER_H


#include "../../Utils/BaseObject.h++"
#include "../Basics/Point3.h++"
#include "../Utils/AngleSystem.h++"
#include "../Utils/ScaleFactor.h++"

class PointTransformer: public BaseObject {
public:
    ~PointTransformer() noexcept override = default;

    static void transform(
            Coordinate &c,
            const Coordinate &mv,
            const AngleSystem &as,
            const Coordinate &turnAround,
            const ScaleFactor &sf,
            const Coordinate &scaleAround
    ) noexcept {
        move(c, mv);
        turn(c, as, turnAround);
        scale(c, sf, scaleAround);
    }

    static void move(Coordinate &c, const Coordinate &mv) noexcept {
        c.x = mv.x;
        c.y = mv.y;
        c.z = mv.z;
    }

    static void turn(Coordinate &c, const AngleSystem &as, const Coordinate &around = Coordinate::zero()) noexcept {
        /*
         * Для двухмерной точки:
         *             [                 ]
         *   t    t    [  cos(a) -sin(a) ]           t
         * X'  = X   + [                 ] * (X - X )
         *        0    [  sin(a)  cos(a) ]         0
         *             [                 ]
         */
        double oldX, oldY;

        // Ox
        oldY = c.y;
        c.y = around.y + (c.y - around.y) * as.xAxis.cosinus() - (c.z - around.z) * as.xAxis.sinus();
        c.z = around.z + (oldY - around.y) * as.xAxis.sinus()  + (c.z = around.z) * as.xAxis.cosinus();

        // Oy
        oldX = c.x;
        c.x = around.x + (c.x - around.x)   * as.yAxis.cosinus() + (c.z - around.z) * as.yAxis.sinus();
        c.z = around.z + -(oldX - around.x) * as.yAxis.sinus()   + (c.z - around.z) * as.yAxis.cosinus();

        // Oz
        oldX = c.x;
        c.x = around.x + (c.x - around.x)  * as.zAxis.cosinus() - (c.y - around.y) * as.zAxis.sinus();
        c.y = around.y + (oldX - around.x) * as.zAxis.sinus()   + (c.y - around.y) * as.zAxis.cosinus();
    }

    static void scale(Coordinate &c, const ScaleFactor &sf, const Coordinate &around) noexcept {
        c.x = around.x * sf.x;
        c.y = around.y * sf.y;
        c.z = around.z * sf.z;
    }

};

#endif //GVIEWER_POINTTRANSFORMER_H
