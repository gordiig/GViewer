//
// Created by 17105727 on 30.09.2021.
//

#ifndef GVIEWER_ANGLE_H
#define GVIEWER_ANGLE_H

#include <sstream>
#include <ostream>
#include <cmath>
#include "../../Utils/BaseObject.h++"
#include "../../Exceptions/Math.h++"

class Angle: public BaseObject {
protected:
    double deg = 0.0;

public:
    Angle() noexcept = default;

    Angle(const Angle &copy) noexcept = default;
    Angle(Angle &&move) noexcept = default;

    Angle& operator = (const Angle &copy) noexcept = default;
    Angle& operator = (Angle &&move) noexcept = default;

    static Angle initDeg(double deg) noexcept {
        Angle ans;
        ans.setDeg(deg);
        return ans;
    }
    static Angle initRad(double rad) noexcept {
        Angle ans;
        ans.setRad(rad);
        return ans;
    }

    static Angle initAtan(double angTan) noexcept {
        double degRad = atan(angTan);
        Angle ans = Angle::initRad(degRad);
        return ans;
    }

    ~Angle() noexcept override = default;

    [[nodiscard]] static double normalizeDeg(double ang) noexcept {
        ang = fmod(ang, 360.0);
        if (ang < 0)
            ang += 360.0;
        return ang;
    }
    [[nodiscard]] static double degToRad(double angDeg) noexcept { return M_PI * normalizeDeg(angDeg) / 180; }
    [[nodiscard]] static double radToDeg(double angRad) noexcept { return normalizeDeg(angRad * 180 / M_PI); }

    bool operator == (const Angle &rhs) const noexcept { return doubleEq(deg, rhs.deg); }
    bool operator != (const Angle &rhs) const noexcept { return !(rhs == *this); }

    Angle operator + (const Angle &rhs) const noexcept {
        Angle ans;
        ans.setDeg(deg + rhs.deg);
        return ans;
    }
    Angle operator - (const Angle &rhs) const noexcept {
        Angle ans;
        ans.setDeg(deg - rhs.deg);
        return ans;
    }

    Angle& operator += (const Angle &rhs) noexcept {
        setDeg(deg + rhs.deg);
        return *this;
    }
    Angle& operator -= (const Angle &rhs) noexcept {
        setDeg(deg - rhs.deg);
        return *this;
    }

    Angle operator - () const noexcept {
        Angle ans;
        ans.setDeg(-deg);
        return ans;
    }

    [[nodiscard]] double getDeg() const { return deg; }
    [[nodiscard]] double getRad() const { return degToRad(deg); }

    void setDeg(double deg) { this->deg = normalizeDeg(deg); }
    void setRad(double rad) { this->deg = normalizeDeg(radToDeg(rad)); }

    [[nodiscard]] double sinus() const noexcept { return sin(getRad()); }
    [[nodiscard]] double cosinus() const noexcept { return cos(getRad()); }
    [[nodiscard]] double tangens() const { return tan(getRad()); }
    [[nodiscard]] double cotangens() const {
        if (doubleEq(deg, 0))
            throw CotangensOfZeroError(EXC_PARAMS);

        return 1 / tangens();
    }

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << deg << "°";
        return sst.str();
    }
};

#endif //GVIEWER_ANGLE_H
