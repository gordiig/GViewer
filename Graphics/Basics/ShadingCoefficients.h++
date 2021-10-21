//
// Created by 17105727 on 30.09.2021.
//

#ifndef GVIEWER_SHADINGCOEFFICIENTS_H
#define GVIEWER_SHADINGCOEFFICIENTS_H

#include <sstream>
#include "../../Exceptions/Exception.h++"
#include "../../Utils/BaseObject.h++"

class ShadingCoefficients: public BaseObject {
protected:
    double kd = 0;
    double ka = 0;

public:
    explicit ShadingCoefficients(double kd = 0, double ka = 0) {
        setKd(kd);
        setKa(ka);
    }

    ShadingCoefficients(const ShadingCoefficients &sc) noexcept  = default;
    ShadingCoefficients(ShadingCoefficients &&sc) noexcept = default;

    ShadingCoefficients& operator = (const ShadingCoefficients &sc) = default;
    ShadingCoefficients& operator = (ShadingCoefficients &&sc) noexcept = default;

    ~ShadingCoefficients() noexcept override = default;

    bool operator == (const ShadingCoefficients &rhs) const { return doubleEq(ka, rhs.ka) && doubleEq(kd, rhs.kd); }
    bool operator != (const ShadingCoefficients &rhs) const { return !(rhs == *this); }

    [[nodiscard]] double getKd() const { return kd; }
    [[nodiscard]] double getKa() const { return ka; }

    void setKd(double kd) {
        if (kd < 0 || kd > 1)
            throw BadArgumentError(EXC_PARAMS, "Kd must be in [0, 1] range");
        this->kd = kd;
    }
    void setKa(double ka) {
        if (ka < 0 || ka > 1)
            throw BadArgumentError(EXC_PARAMS, "Ka must be in [0, 1] range");
        this->ka = ka;
    }

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[kd = " << kd << ", ka = " << ka << ']';
        return sst.str();
    }

};

#endif //GVIEWER_SHADINGCOEFFICIENTS_H
