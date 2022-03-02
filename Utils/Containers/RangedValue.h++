//
// Created by 17105727 on 15.11.2021.
//

#ifndef GVIEWER_RANGEDVALUE_H
#define GVIEWER_RANGEDVALUE_H

#include <sstream>
#include "../BaseObject.h++"
#include "../../Exceptions/Exception.h++"


template <
        typename T,
        typename = std::enable_if_t<std::is_arithmetic_v<T>>
>
class RangedValue: public BaseObject {
protected:
    T minValue;
    T maxValue;

    T value;

public:
    explicit RangedValue(const T& val, const T& minVal, const T& maxVal): value(val), minValue(minVal), maxValue(maxVal) {
        if (!testValue(val))
            throw BadArgumentError(EXC_PARAMS);
    }

    RangedValue(const RangedValue& copy) noexcept = default;
    RangedValue(RangedValue&& copy) noexcept = default;

    RangedValue& operator = (const RangedValue& copy) noexcept = default;
    RangedValue& operator = (RangedValue&& copy) noexcept = default;

    RangedValue& operator = (const T& val) {
        testValue(val, true);
        value = val;
        return *this;
    }
    RangedValue& operator = (T&& val) {
        testValue(val, true);
        value = val;
        return *this;
    }

    inline bool testValue(const T& val, bool throws = false) const {
        bool ans = minValue <= val && val <= maxValue;

        // If need to throw — throw bad arg exception
        if (throws && !ans)
            throw BadArgumentError(EXC_PARAMS);

        return ans;
    }

    inline explicit operator T() const noexcept { return getValue(); }
    inline T getValue() const noexcept { return value; }
    inline T getMinValue() const noexcept { return minValue; }
    inline T getMaxValue() const noexcept { return maxValue; }

    // Compare
    inline bool operator == (const RangedValue &rhs) const { return *this == rhs.value; }
    inline bool operator == (const T &rhs) const { return value == rhs; }
    inline bool operator != (const RangedValue &rhs) const { return !(rhs == *this); }
    inline bool operator != (const T &rhs) const { return !(rhs == *this); }

    inline bool operator <= (const RangedValue &rhs) const { return *this <= rhs.value; }
    inline bool operator <= (const T &rhs) const { return value <= rhs; }
    inline bool operator < (const RangedValue &rhs) const { return *this < rhs.value; }
    inline bool operator < (const T &rhs) const { return value < rhs; }
    inline bool operator >= (const RangedValue &rhs) const { return *this >= rhs.value; }
    inline bool operator >= (const T &rhs) const { return value >= rhs; }
    inline bool operator > (const RangedValue &rhs) const { return *this > rhs.value; }
    inline bool operator > (const T &rhs) const { return value > rhs; }

    // Arithmetics
    inline RangedValue operator + (const RangedValue<T> &rhs) const {
        return *this + rhs.value;
    }
    inline RangedValue operator + (const T& rhs) const {
        return RangedValue<T>(value + rhs);
    }
    inline RangedValue& operator += (const RangedValue<T> &rhs) const {
        return *this += rhs.value;
    }
    inline RangedValue& operator += (const T& rhs) const {
        *this = value + rhs;
        return *this;
    }

    inline RangedValue operator - (const RangedValue<T> &rhs) const {
        return *this - rhs.value;
    }
    inline RangedValue operator - (const T& rhs) const {
        return RangedValue<T>(value - rhs);
    }
    inline RangedValue& operator -= (const RangedValue<T> &rhs) const {
        return *this -= rhs.value;
    }
    inline RangedValue& operator -= (const T& rhs) const {
        *this = value - rhs;
        return *this;
    }

    inline RangedValue operator * (const RangedValue<T> &rhs) const {
        return *this * rhs.value;
    }
    inline RangedValue operator * (const T& rhs) const {
        return RangedValue<T>(value * rhs);
    }
    inline RangedValue& operator *= (const RangedValue<T> &rhs) const {
        return *this *= rhs.value;
    }
    inline RangedValue& operator *= (const T& rhs) const {
        *this = value * rhs;
        return *this;
    }

    inline RangedValue operator / (const RangedValue<T> &rhs) const {
        return *this / rhs.value;
    }
    inline RangedValue operator / (const T& rhs) const {
        return RangedValue<T>(value / rhs);
    }
    inline RangedValue& operator /= (const RangedValue<T> &rhs) const {
        return *this /= rhs.value;
    }
    inline RangedValue& operator /= (const T& rhs) const {
        *this = value / rhs;
        return *this;
    }

    ~RangedValue() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[RangedValue val = " << value << ", minValue = " << minValue << ", maxValue = " << maxValue << ']';
        return sst.str();
    }

};

#endif //GVIEWER_RANGEDVALUE_H
