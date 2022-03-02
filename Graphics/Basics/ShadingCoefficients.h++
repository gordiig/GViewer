//
// Created by 17105727 on 30.09.2021.
//

#ifndef GVIEWER_SHADINGCOEFFICIENTS_H
#define GVIEWER_SHADINGCOEFFICIENTS_H

#include "../../Exceptions/Exception.h++"
#include "../../Utils/BaseObject.h++"
#include "../../Utils/Containers/RangedValue.h++"

class ShadingCoefficients: public BaseObject {
protected:
    RangedValue<double> kd {1.0, 0.0, 1.0};
    RangedValue<double> ka {1.0, 0.0, 1.0};
    RangedValue<double> ks {1.0, 0.0, 1.0};

public:
    explicit ShadingCoefficients(double kd = 0.0, double ka = 0.0, double ks = 0.0) {
        setKd(kd);
        setKa(ka);
        setKs(ks);
    }

    ShadingCoefficients(const ShadingCoefficients &sc) noexcept  = default;
    ShadingCoefficients(ShadingCoefficients &&sc) noexcept = default;

    ShadingCoefficients& operator = (const ShadingCoefficients &sc) = default;
    ShadingCoefficients& operator = (ShadingCoefficients &&sc) noexcept = default;

    ~ShadingCoefficients() noexcept override = default;

    bool operator == (const ShadingCoefficients &rhs) const {
        return kd == rhs.kd && ka == rhs.ka && ks == rhs.ks;
    }
    bool operator != (const ShadingCoefficients &rhs) const { return !(rhs == *this); }

    [[nodiscard]] double getKd() const { return (double) kd; }
    [[nodiscard]] double getKa() const { return (double) ka; }
    [[nodiscard]] double getKs() const { return (double) ks; }

    void setKd(double value) { this->kd = value; }
    void setKa(double value) { this->ka = value; }
    void setKs(double value) { this->ks = value; }

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[kd = " << kd << ", ka = " << ka << ']';
        return sst.str();
    }

};

#endif //GVIEWER_SHADINGCOEFFICIENTS_H
