//
// Created by 17105727 on 30.09.2021.
//

#ifndef GVIEWER_VECTOR_H
#define GVIEWER_VECTOR_H

#include <ostream>
#include "Point3.h++"
#include "../../Exceptions/Math.h++"

struct Vector: public Point3<double, double, double> {
    Vector() noexcept = default;
    Vector(double x, double y, double z) : Point3(x, y, z) {}
    Vector(const Point3<double, double, double> &pt) : Vector(pt.x, pt.y, pt.z) {}

    Vector(const Vector &copy) noexcept = default;
    Vector(Vector &&move) noexcept = default;

    Vector& operator = (const Vector &copy) noexcept = default;
    Vector& operator = (Vector &&move) noexcept = default;

    ~Vector() noexcept override = default;

    [[nodiscard]] double scalarMultiply(const Vector &rhs) const noexcept { return x * rhs.x + y * rhs.y + z * rhs.z; }

    [[nodiscard]] double length() const noexcept { return std::sqrt(x*x + y*y + z*z); }
    [[nodiscard]] Vector normalized() const {
        double len = length();
        if (fabs(len) <= 1e-6)
            throw DivideByZeroError(EXC_PARAMS, "Vector length is 0");

        Vector ans(x / len, y / len, z / len);
        return ans;
    }
    void normalize() { *this = this->normalized(); }

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "vector[" << Point3(x, y, z) << "]";
        return sst.str();
    }
};

#endif //GVIEWER_VECTOR_H
