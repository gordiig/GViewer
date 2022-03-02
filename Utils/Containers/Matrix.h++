//
// Created by 17105727 on 30.09.2021.
//

#ifndef GVIEWER_MATRIX_H
#define GVIEWER_MATRIX_H

#include "DynArray.h++"
#include "../BaseObject.h++"
#include "../../Exceptions/Range.h++"

template <typename T>
class Matrix: public BaseObject{
protected:
    DynArray<DynArray<T>> mat;
    size_t _rows;
    size_t _columns;

public:
    Matrix() = delete;
    Matrix(size_t rows, size_t columns, const T &fill = T()) : _rows(rows), _columns(columns) {
        for (int i = 0; i < rows; i++)
            mat.append(DynArray(columns, fill));
    }
    Matrix(const std::initializer_list<std::initializer_list<T>> &initializerList) : _columns(0) {
        _rows = initializerList.size();
        for (const auto &lst : initializerList) {
            if (_columns != 0 && lst.size() != _columns)
                throw BadArgumentError(EXC_PARAMS);

            _columns = lst.size();
            mat.append(lst);
        }
    }

    static Matrix<T> unit(size_t size, const T& zero = 0, const T& one = 1) {
        Matrix<T> ans(size, size, zero);
        for (int i = 0; i < size; i++)
            ans[i][i] = one;
        return ans;
    }

    Matrix(const Matrix<T> &copy) noexcept = default;
    Matrix(Matrix<T> &&move) noexcept = default;
    Matrix<T>& operator = (const Matrix<T> &copy) noexcept = default;
    Matrix<T>& operator = (Matrix<T> &&move) noexcept = default;

    ~Matrix() noexcept override = default;

    DynArray<T>& operator [] (size_t idx) { return mat[idx]; }
    const DynArray<T>& operator [] (size_t idx) const { return mat[idx]; }

    auto begin() { return mat.begin(); }
    auto end() { return mat.end(); }
    auto begin() const { return mat.begin(); }
    auto end() const { return mat.end(); }

    [[nodiscard]] size_t rows() const { return _rows; }
    [[nodiscard]] size_t columns() const { return _columns; }

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[Matrix rows = " << rows() << ", columns = " << columns() << ']';
        return sst.str();
    }
};

#endif //GVIEWER_MATRIX_H
