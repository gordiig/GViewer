//
// Created by 17105727 on 30.09.2021.
//

#ifndef GVIEWER_VECTOR_H
#define GVIEWER_VECTOR_H

#include <ostream>
#include "Point3.h++"
#include "../../Exceptions/Math.h++"

struct Vector: public Point3<double, double, double> {
public:
    Vector() noexcept = default;
    Vector(double x, double y, double z) : Point3(x, y, z) {}

    Vector(const Vector &copy) noexcept = default;
    Vector(Vector &&move) noexcept { *this = move; }

    Vector& operator = (const Vector &copy) noexcept {
        x = copy.x;
        y = copy.y;
        z = copy.z;
        return *this;
    }
    Vector& operator = (Vector &&move) noexcept {
        x = move.x;
        y = move.y;
        z = move.z;
        return *this;
    }

    ~Vector() noexcept override = default;

    Vector operator * (double rhs) const noexcept {
        Vector ans(x * rhs, y * rhs, z * rhs);
        return ans;
    }
    Vector operator / (double rhs) const {
        if (fabs(rhs) <= 1e-6)
            throw DivideByZeroError(EXC_PARAMS);

        Vector ans (x / rhs, y / rhs, z / rhs);
        return ans;
    }

    Vector& operator *= (double rhs) noexcept {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }
    Vector& operator /= (double rhs) {
        if (fabs(rhs) <= 1e-6)
            throw DivideByZeroError(EXC_PARAMS);

        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    }

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
