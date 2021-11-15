//
// Created by 17105727 on 01.10.2021.
//

#ifndef GVIEWER_RGBA_H
#define GVIEWER_RGBA_H

#include "../../Utils/BaseObject.h++"
#include "../../Utils/Containers/RangedValue.h++"
#include "../../Exceptions/Exception.h++"


class RGBA: public BaseObject {
protected:
    RangedValue<short> r {0, 0, 255};
    RangedValue<short> g {0, 0, 255};
    RangedValue<short> b {0, 0, 255};
    RangedValue<short> a {255, 0, 255};

public:
    RGBA() noexcept = default;
    RGBA(short r, short g, short b, short a) noexcept {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    RGBA(const RGBA &copy) noexcept = default;
    RGBA(RGBA &&move) noexcept = default;

    RGBA& operator = (const RGBA &copy) noexcept = default;
    RGBA& operator = (RGBA &&move) noexcept = default;

    inline static RGBA white() noexcept { return {255, 255, 255, 255}; }
    inline static RGBA black() noexcept { return {0, 0, 0, 255}; }
    inline static RGBA red() noexcept { return {255, 0, 0, 255}; }
    inline static RGBA green() noexcept { return {0, 255, 0, 255}; }
    inline static RGBA blue() noexcept { return {0, 0, 255, 255}; }
    inline static RGBA transparent() noexcept { return {0, 0, 0, 0}; }

    [[nodiscard]] inline short getR() const noexcept { return (short) r; }
    [[nodiscard]] inline short getG() const noexcept { return (short) g; }
    [[nodiscard]] inline short getB() const noexcept { return (short) b; }
    [[nodiscard]] inline short getA() const noexcept { return (short) a; }

    inline void setR(short value) { this->r = value; }
    inline void setG(short value) { this->g = value; }
    inline void setB(short value) { this->b = value; }
    inline void setA(short value) { this->a = value; }

    [[nodiscard]] RGBA blendThisAbove(const RGBA &rhs) const noexcept {
        double alphaPercent = (double) a.getValue() / (double) a.getMaxValue();

        double newR = (double) r.getValue() * alphaPercent + (double) rhs.r.getValue() * (1.0 - alphaPercent);
        double newG = (double) g.getValue() * alphaPercent + (double) rhs.g.getValue() * (1.0 - alphaPercent);
        double newB = (double) b.getValue() * alphaPercent + (double) rhs.b.getValue() * (1.0 - alphaPercent);
        double newA = (double) a.getValue() * alphaPercent + (double) rhs.a.getValue() * (1.0 - alphaPercent);

        return {(short) newR, (short) newG, (short) newB, (short) newA};
    }
    [[nodiscard]] RGBA blendThisBelow(const RGBA &rhs) const noexcept { return rhs.blendThisAbove(*this); }

    [[nodiscard]] RGBA applyIntensity(const size_t intensity, const bool applyForAlpha = false) const noexcept {
        RGBA ans = *this;
        const auto& doubleIntensity = (double) intensity;
        const double intensityMultiplier = doubleIntensity / 255.0;

        ans.r = (short) ((double) r.getValue() * intensityMultiplier);
        ans.g = (short) ((double) g.getValue() * intensityMultiplier);
        ans.b = (short) ((double) b.getValue() * intensityMultiplier);
        if (applyForAlpha)
            ans.a = (short) ((double) a.getValue() * intensityMultiplier);

        return ans;
    }

    [[nodiscard]] inline bool isTransparent() const noexcept { return a == 0; }
    [[nodiscard]] inline bool isKindaTransparent() const noexcept { return a < 255; }
    [[nodiscard]] inline bool isOpaque() const noexcept { return a == 255; }

    ~RGBA() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "rgba(" << r << ", " << g << ", " << b << ", " << a << ')';
        return sst.str();
    }
};

#endif //GVIEWER_RGBA_H
