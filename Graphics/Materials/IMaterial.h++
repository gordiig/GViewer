//
// Created by 17105727 on 06.10.2021.
//

#ifndef GVIEWER_IMATERIAL_H
#define GVIEWER_IMATERIAL_H

#include <sstream>
#include "../../Utils/BaseObject.h++"
#include "../Basics/RGBA.h++"


class IMaterial: public BaseObject {
public:
    [[nodiscard]] virtual const RGBA& getColor(double x, double y) const = 0;

    ~IMaterial() noexcept override = default;

    [[nodiscard]] virtual std::shared_ptr<IMaterial> copyShared() const = 0;
    [[nodiscard]] virtual std::unique_ptr<IMaterial> copyUnique() const = 0;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[IMaterial]";
        return sst.str();
    }
};

#endif //GVIEWER_IMATERIAL_H
