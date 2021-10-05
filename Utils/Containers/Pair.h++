//
// Created by 17105727 on 05.10.2021.
//

#ifndef GVIEWER_PAIR_H
#define GVIEWER_PAIR_H

#include <sstream>
#include "../BaseObject.h++"

template<typename T1, typename T2>
struct Pair: public BaseObject {
    T1 first;
    T2 second;

    Pair(const T1& first, const T2& second) noexcept : first(first), second(second) {}

    Pair(const Pair<T1, T2> &copy) noexcept = default;
    Pair(Pair<T1, T2> &&move) noexcept = default;

    Pair& operator = (const Pair<T1, T2> &copy) noexcept = default;
    Pair& operator = (Pair<T1, T2> &&move) noexcept = default;

    bool operator == (const Pair &rhs) const noexcept {
        return first == rhs.first && second == rhs.second;
    }
    bool operator != (const Pair &rhs) const noexcept {
        return !(rhs == *this);
    }

    ~Pair() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[pair first = " << first << ", second = " << second << ']';
        return sst.str();
    }
};

#endif //GVIEWER_PAIR_H
