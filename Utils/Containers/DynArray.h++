//
// Created by 17105727 on 29.09.2021.
//

#ifndef GVIEWER_DYNARRAY_H
#define GVIEWER_DYNARRAY_H

#include <vector>
#include "../BaseObject.h++"
#include "../../Exceptions/Range.h++"

template<typename T>
class DynArray: public BaseObject {
protected:
    std::vector<T> vec;

public:
    DynArray() = default;

    explicit DynArray(size_t count) : vec(count) { }
    DynArray(size_t count, const T &val) : vec(count, val) {}
    explicit DynArray(const std::vector<T> &vec) : vec(vec) {}
    DynArray(const std::initializer_list<T> initializerList) : vec(initializerList) {}

    DynArray(const DynArray<T> &copy) = default;
    DynArray(DynArray<T> &&move) noexcept = default;

    DynArray<T> &operator=(const DynArray<T> &copy) = default;
    DynArray<T> &operator=(DynArray<T> &&move) noexcept = default;

    ~DynArray() override = default;

    T &operator[](long idx) {
        if (idx < 0)
            idx = count() + idx;

        try {
            // stl does not throws on [] (WTF)
            return vec.at(idx);
        } catch (std::out_of_range &exc) {
            throw IndexError(EXC_PARAMS, exc);
        }
    }
    const T &operator[](long idx) const {
        if (idx < 0)
            idx = count() + idx;
        try {
            // stl does not throws on [] (WTF)
            return vec.at(idx);
        } catch (std::out_of_range &exc) {
            throw IndexError(EXC_PARAMS, exc);
        }
    }

    bool operator==(const DynArray &rhs) const { return vec == rhs.vec; }
    bool operator!=(const DynArray &rhs) const { return !(rhs == *this); }

    auto begin() { return vec.begin(); }
    auto end() { return vec.end(); }
    auto begin() const { return vec.begin(); }
    auto end() const { return vec.end(); }

    void append(const T &val) { vec.push_back(val); }
    void append(T &&val) { vec.push_back(std::move(val)); }

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

    void reserve(size_t val) { vec.reserve(val); }

    void removeAt(long idx) {
        if (idx < 0)
            idx = count() + idx;

        try {
            vec.erase(vec.begin() + idx);
        } catch (std::out_of_range &exc) {
            throw IndexError(EXC_PARAMS, exc);
        }
    }
    void clear() noexcept { vec.clear(); }

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[DynArray: ";
        for (const auto &item : vec)
            sst << item << " ";
        sst << ']';
        return sst.str();
    }
};

#endif //GVIEWER_DYNARRAY_H
