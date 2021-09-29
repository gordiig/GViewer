//
// Created by 17105727 on 29.09.2021.
//

#ifndef GVIEWER_VECTOR_H
#define GVIEWER_VECTOR_H

#include <vector>
#include <ostream>
#include <sstream>
#include "../../Exceptions/Range.h++"

template<typename T>
class Vector: public BaseObject {
protected:
    std::vector<T> vec;

public:
    Vector() = default;

    explicit Vector(size_t count) : vec(count) {}
    Vector(size_t count, const T &val) : vec(count, val) {}
    explicit Vector(const std::vector<T> &vec) : vec(vec) {}
    Vector(const std::initializer_list<T> initializerList) : vec(initializerList) {}

    Vector(const Vector<T> &copy) { *this = copy; }
    Vector(Vector<T> &&move) noexcept { *this = move; }
    Vector<T> &operator=(const Vector<T> &copy) {
        if (&copy == this)
            return *this;

        this->vec = copy.vec;
        return *this;
    }
    Vector<T> &operator=(Vector<T> &&move) noexcept {
        this->vec = move.vec;
        move.vec.clear();
        return *this;
    }

    ~Vector() override = default;

    T &operator[](long idx) {
        if (idx < 0)
            idx = count() - idx;

        try {
            // stl does not throws on [] (WTF)
            return vec.at(idx);
        } catch (std::out_of_range &exc) {
            throw IndexError(EXC_PARAMS, exc);
        }
    }
    const T &operator[](long idx) const {
        if (idx < 0)
            idx = count() - idx;
        try {
            // stl does not throws on [] (WTF)
            return vec.at(idx);
        } catch (std::out_of_range &exc) {
            throw IndexError(EXC_PARAMS, exc);
        }
    }

    bool operator==(const Vector &rhs) const { return vec == rhs.vec; }
    bool operator!=(const Vector &rhs) const { return !(rhs == *this); }

    auto begin() { return vec.begin(); }
    auto end() { return vec.end(); }
    auto begin() const { return vec.begin(); }
    auto end() const { return vec.end(); }

    [[nodiscard]] size_t count() const { return vec.size(); }

    [[nodiscard]] bool isEmpty() const { return vec.empty(); }
    bool contains(const T &val) const { return std::find(begin(), end(), val) != end(); }

    auto iterForValue(const T &val) const { return std::find(begin(), end(), val); }

    size_t valueIndex(const T &val) const {
        auto iter = iterForValue(val);
        if (iter == end())
            throw NotFoundInCollectionError(EXC_PARAMS);

        return iter - begin();
    }

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << *this;
        return sst.str();
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector &vector) {
        for (const auto &item : vector.vec)
            os << item << " ";
        return os;
    }
};

#endif //GVIEWER_VECTOR_H
