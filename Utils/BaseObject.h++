//
// Created by 17105727 on 29.09.2021.
//

#ifndef GVIEWER_BASEOBJECT_H
#define GVIEWER_BASEOBJECT_H

#include <string>
#include <sstream>

class BaseObject {
protected:
    [[nodiscard]] std::string getClassName() const { return typeid(*this).name(); }

public:
    [[nodiscard]] virtual std::string toString() const {
        std::stringstream sstream;
        sstream << getClassName() << '[' << this << ']';
        return sstream.str();
    }

    [[nodiscard]] bool isIdenticTo(const BaseObject &val) const { return this == &val; }

    virtual ~BaseObject() = default;
};

#endif //GVIEWER_BASEOBJECT_H
