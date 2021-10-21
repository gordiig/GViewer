//
// Created by 17105727 on 29.09.2021.
//

#ifndef GVIEWER_BASEOBJECT_H
#define GVIEWER_BASEOBJECT_H

#include <string>
#include <sstream>
#include <ostream>

class BaseObject {
protected:
    [[nodiscard]] bool doubleEq(double x, double y, double eps = 1e-6) const noexcept { return abs(x - y) <= eps; }

public:
    // typeid.name() может вообще давать что угодно, но имя класса можно разглядеть
    [[nodiscard]] std::string getClassName() const { return typeid(*this).name(); }

    [[nodiscard]] virtual std::string toString() const = 0;

    [[nodiscard]] bool isIdenticTo(const BaseObject &val) const { return this == &val; }

    friend std::ostream &operator<<(std::ostream &os, const BaseObject &object) {
        os << object.toString();
        return os;
    }

    virtual ~BaseObject() = default;
};

#endif //GVIEWER_BASEOBJECT_H
