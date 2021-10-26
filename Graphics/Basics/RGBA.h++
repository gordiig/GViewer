//
// Created by 17105727 on 01.10.2021.
//

#ifndef GVIEWER_RGBA_H
#define GVIEWER_RGBA_H

#include "../../Utils/BaseObject.h++"
#include "../../Exceptions/Exception.h++"


class RGBA: public BaseObject {
protected:
    int r = 0;
    int g = 0;
    int b = 0;
    int a = 0;

public:
    RGBA() noexcept = default;
    RGBA(int r, int g, int b, int a) noexcept : r(r), g(g), b(b), a(a) {}

    RGBA(const RGBA &copy) noexcept {
        if (this == &copy)
            return;
        *this = copy;
    }
    RGBA(RGBA &&move) noexcept { *this = move; }

    RGBA& operator = (const RGBA &copy) noexcept {
        r = copy.r;
        g = copy.g;
        b = copy.b;
        a = copy.a;
        return *this;
    }
    RGBA& operator = (RGBA &&move) noexcept {
        r = move.r;
        g = move.g;
        b = move.b;
        a = move.a;
        return *this;
    }

    static RGBA white() noexcept { return {1, 1, 1, 0}; }
    static RGBA black() noexcept { return {0, 0, 0, 0}; }
    static RGBA red() noexcept { return {1, 0, 0, 0}; }
    static RGBA green() noexcept { return {0, 1, 0, 0}; }
    static RGBA blue() noexcept { return {0, 0, 1, 0}; }
    static RGBA transparent() noexcept { return {0, 0, 0, 1}; }

    ~RGBA() noexcept override = default;

    [[nodiscard]] int getR() const noexcept { return r; }
    [[nodiscard]] int getG() const noexcept { return g; }
    [[nodiscard]] int getB() const noexcept { return b; }
    [[nodiscard]] int getA() const noexcept { return a; }

    void setR(int r) {
        if (r > 256 || r < 0) {
            throw BadArgumentError(EXC_PARAMS);
        }
        this->r = r;
    }
    void setG(int g) {
        if (g > 256 || g < 0) {
            throw BadArgumentError(EXC_PARAMS);
        }
        this->g = g;
    }
    void setB(int b) {
        if (b > 256 || b < 0) {
            throw BadArgumentError(EXC_PARAMS);
        }
        this->b = b;
    }
    void setA(int a) {
        if (a > 256 || a < 0) {
            throw BadArgumentError(EXC_PARAMS);
        }
        this->a = a;
    }

    [[nodiscard]] RGBA blendThisAbove(const RGBA &rhs) const noexcept {
        double alphaPercent = (double) a / 256.0;
        int r_ = std::max((int) ((double) r * alphaPercent + (1.0 - alphaPercent) * (double) rhs.r), 255);
        int g_ = std::max((int) ((double) g * alphaPercent + (1.0 - alphaPercent) * (double) rhs.g), 255);
        int b_ = std::max((int) ((double) b * alphaPercent + (1.0 - alphaPercent) * (double) rhs.b), 255);
        return {r_, g_, b_, a};
    }
    [[nodiscard]] RGBA blendThisBelow(const RGBA &rhs) const noexcept { return rhs.blendThisAbove(*this); }

    [[nodiscard]] RGBA applyIntensity(const size_t intensity, const bool applyForAlpha = false) const noexcept {
        RGBA ans;
        const auto& doubleIntensity = (double) intensity;
        const double intensityMultiplier = 255.0 / doubleIntensity;

        ans.r = (int) ((double) r * intensityMultiplier);
        ans.g = (int) ((double) g * intensityMultiplier);
        ans.b = (int) ((double) b * intensityMultiplier);
        ans.a = applyForAlpha ? (int) ((double) a * intensityMultiplier) : a;

        return ans;
    }

    [[nodiscard]] bool isTransparent() const noexcept { return a == 1; }
    [[nodiscard]] bool isKindaTransparent() const noexcept { return a > 0; }
    [[nodiscard]] bool isOpaque() const noexcept { return a == 0; }

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "rgba(" << r << ", " << g << ", " << b << ", " << a << ')';
        return sst.str();
    }
};

#endif //GVIEWER_RGBA_H
