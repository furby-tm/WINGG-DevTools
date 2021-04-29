#line 1 "C:/Users/tyler/dev/WINGG/forge/base/gf/vec4h.h"
/*
 * Copyright 2021 Forge. All Rights Reserved.
 *
 * The use of this software is subject to the terms of the
 * Forge license agreement provided at the time of installation
 * or download, or which otherwise accompanies this software in
 * either electronic or hard copy form.
 *
 * Portions of this file are derived from original work by Pixar
 * distributed with Universal Scene Description, a project of the
 * Academy Software Foundation (ASWF). https://www.aswf.io/
 *
 * Original Copyright (C) 2016-2021 Pixar.
 * Modifications copyright (C) 2020-2021 ForgeXYZ LLC.
 *
 * Forge. The Animation Software & Motion Picture Co.
 */
////////////////////////////////////////////////////////////////////////
// This file is generated by a script.  Do not edit directly.  Edit the
// vec.template.h file to make changes.

#ifndef FORGE_BASE_GF_VEC4H_H
#define FORGE_BASE_GF_VEC4H_H

/// \file gf/vec4h.h
/// \ingroup group_gf_LinearAlgebra

#include "forge/forge.h"
#include "forge/base/tf/diagnostic.h"
#include "forge/base/gf/api.h"
#include "forge/base/gf/limits.h"
#include "forge/base/gf/traits.h"
#include "forge/base/gf/math.h"
#include "forge/base/gf/half.h"

#include <boost/functional/hash.hpp>

#include <cstddef>
#include <cmath>

#include <iosfwd>

FORGE_NAMESPACE_BEGIN

class GfVec4h;

template <>
struct GfIsGfVec<class GfVec4h> { static const bool value = true; };

/// \class GfVec4h
/// \ingroup group_gf_LinearAlgebra
///
/// Basic type for a vector of 4 GfHalf components.
///
/// Represents a vector of 4 components of type \c GfHalf.
/// It is intended to be fast and simple.
///
class GfVec4h
{
public:
    /// Scalar element type and dimension.
    typedef GfHalf ScalarType;
    static const size_t dimension = 4;

    /// Default constructor does no initialization.
    GfVec4h() = default;

    /// Initialize all elements to a single value.
    constexpr explicit GfVec4h(GfHalf value)
        : _data{ value, value, value, value }
    {
    }

    /// Initialize all elements with explicit arguments.
    constexpr GfVec4h(GfHalf s0, GfHalf s1, GfHalf s2, GfHalf s3)
        : _data{ s0, s1, s2, s3 }
    {
    }

    /// Construct with pointer to values.
    template <class Scl>
    constexpr explicit GfVec4h(Scl const *p)
        : _data{ p[0], p[1], p[2], p[3] }
    {
    }

    /// Construct from GfVec4d.
    explicit GfVec4h(class GfVec4d const &other);

    /// Construct from GfVec4f.
    explicit GfVec4h(class GfVec4f const &other);

    /// Implicitly convert from GfVec4i.
    GfVec4h(class GfVec4i const &other);

    /// Create a unit vector along the X-axis.
    static GfVec4h XAxis() {
        GfVec4h result(0);
        result[0] = 1;
        return result;
    }
    /// Create a unit vector along the Y-axis.
    static GfVec4h YAxis() {
        GfVec4h result(0);
        result[1] = 1;
        return result;
    }
    /// Create a unit vector along the Z-axis.
    static GfVec4h ZAxis() {
        GfVec4h result(0);
        result[2] = 1;
        return result;
    }
    /// Create a unit vector along the W-axis.
    static GfVec4h WAxis() {
        GfVec4h result(0);
        result[3] = 1;
        return result;
    }

    /// Create a unit vector along the i-th axis, zero-based.  Return the zero
    /// vector if \p i is greater than or equal to 4.
    static GfVec4h Axis(size_t i) {
        GfVec4h result(0);
        if (i < 4)
            result[i] = 1;
        return result;
    }

    /// Set all elements with passed arguments.
    GfVec4h &Set(GfHalf s0, GfHalf s1, GfHalf s2, GfHalf s3) {
        _data[0] = s0;
        _data[1] = s1;
        _data[2] = s2;
        _data[3] = s3;
        return *this;
    }

    /// Set all elements with a pointer to data.
    GfVec4h &Set(GfHalf const *a) {
        return Set(a[0], a[1], a[2], a[3]);
    }

    /// Direct data access.
    GfHalf const *data() const { return _data; }
    GfHalf *data() { return _data; }
    GfHalf const *GetArray() const { return data(); }

    /// Indexing.
    GfHalf const &operator[](size_t i) const { return _data[i]; }
    GfHalf &operator[](size_t i) { return _data[i]; }

    /// Hash.
    friend inline size_t hash_value(GfVec4h const &vec) {
        size_t h = 0;
        boost::hash_combine(h, vec[0]);
        boost::hash_combine(h, vec[1]);
        boost::hash_combine(h, vec[2]);
        boost::hash_combine(h, vec[3]);
        return h;
    }

    /// Equality comparison.
    bool operator==(GfVec4h const &other) const {
        return _data[0] == other[0] &&
               _data[1] == other[1] &&
               _data[2] == other[2] &&
               _data[3] == other[3];
    }
    bool operator!=(GfVec4h const &other) const {
        return !(*this == other);
    }

    // TODO Add inequality for other vec types...
    /// Equality comparison.
    GF_API
    bool operator==(class GfVec4d const &other) const;
    /// Equality comparison.
    GF_API
    bool operator==(class GfVec4f const &other) const;
    /// Equality comparison.
    GF_API
    bool operator==(class GfVec4i const &other) const;

    /// Create a vec with negated elements.
    GfVec4h operator-() const {
        return GfVec4h(-_data[0], -_data[1], -_data[2], -_data[3]);
    }

    /// Addition.
    GfVec4h &operator+=(GfVec4h const &other) {
        _data[0] += other[0];
        _data[1] += other[1];
        _data[2] += other[2];
        _data[3] += other[3];
        return *this;
    }
    friend GfVec4h operator+(GfVec4h const &l, GfVec4h const &r) {
        return GfVec4h(l) += r;
    }

    /// Subtraction.
    GfVec4h &operator-=(GfVec4h const &other) {
        _data[0] -= other[0];
        _data[1] -= other[1];
        _data[2] -= other[2];
        _data[3] -= other[3];
        return *this;
    }
    friend GfVec4h operator-(GfVec4h const &l, GfVec4h const &r) {
        return GfVec4h(l) -= r;
    }

    /// Multiplication by scalar.
    GfVec4h &operator*=(double s) {
        _data[0] *= s;
        _data[1] *= s;
        _data[2] *= s;
        _data[3] *= s;
        return *this;
    }
    GfVec4h operator*(double s) const {
        return GfVec4h(*this) *= s;
    }
    friend GfVec4h operator*(double s, GfVec4h const &v) {
        return v * s;
    }

        /// Division by scalar.
    // TODO should divide by the scalar type.
    GfVec4h &operator/=(double s) {
        // TODO This should not multiply by 1/s, it should do the division.
        // Doing the division is more numerically stable when s is close to
        // zero.
        return *this *= (1.0 / s);
    }
    GfVec4h operator/(double s) const {
        return *this * (1.0 / s);
    }

    /// See GfDot().
    GfHalf operator*(GfVec4h const &v) const {
        return _data[0] * v[0] + _data[1] * v[1] + _data[2] * v[2] + _data[3] * v[3];
    }

    /// Returns the projection of \p this onto \p v. That is:
    /// \code
    /// v * (*this * v)
    /// \endcode
    GfVec4h GetProjection(GfVec4h const &v) const {
        return v * (*this * v);
    }

    /// Returns the orthogonal complement of \p this->GetProjection(b).
    /// That is:
    /// \code
    ///  *this - this->GetProjection(b)
    /// \endcode
    GfVec4h GetComplement(GfVec4h const &b) const {
        return *this - this->GetProjection(b);
    }

    /// Squared length.
    GfHalf GetLengthSq() const {
        return *this * *this;
    }

    /// Length
    GfHalf GetLength() const {
        // TODO should use GfSqrt.
        return sqrt(GetLengthSq());
    }

    /// Normalizes the vector in place to unit length, returning the
    /// length before normalization. If the length of the vector is
    /// smaller than \p eps, then the vector is set to vector/\c eps.
    /// The original length of the vector is returned. See also GfNormalize().
    ///
    /// \todo This was fixed for bug 67777. This is a gcc64 optimizer bug.
    /// By tickling the code, it no longer tries to write into
    /// an illegal memory address (in the code section of memory).
    GfHalf Normalize(GfHalf eps = 0.001) {
        // TODO this seems suspect...  suggest dividing by length so long as
        // length is not zero.
        GfHalf length = GetLength();
        *this /= (length > eps) ? length : eps;
        return length;
    }

    GfVec4h GetNormalized(GfHalf eps = 0.001) const {
        GfVec4h normalized(*this);
        normalized.Normalize(eps);
        return normalized;
    }


private:
    GfHalf _data[4];
};

/// Output a GfVec4h.
/// \ingroup group_gf_DebuggingOutput
GF_API std::ostream& operator<<(std::ostream &, GfVec4h const &);


FORGE_NAMESPACE_END

#include "forge/base/gf/vec4d.h"
#include "forge/base/gf/vec4f.h"
#include "forge/base/gf/vec4i.h"

FORGE_NAMESPACE_BEGIN

inline
GfVec4h::GfVec4h(class GfVec4d const &other)
{
    _data[0] = other[0];
    _data[1] = other[1];
    _data[2] = other[2];
    _data[3] = other[3];
}
inline
GfVec4h::GfVec4h(class GfVec4f const &other)
{
    _data[0] = other[0];
    _data[1] = other[1];
    _data[2] = other[2];
    _data[3] = other[3];
}
inline
GfVec4h::GfVec4h(class GfVec4i const &other)
{
    _data[0] = other[0];
    _data[1] = other[1];
    _data[2] = other[2];
    _data[3] = other[3];
}

/// Returns component-wise multiplication of vectors \p v1 and \p v2.
inline GfVec4h
GfCompMult(GfVec4h const &v1, GfVec4h const &v2) {
    return GfVec4h(
        v1[0] * v2[0],
        v1[1] * v2[1],
        v1[2] * v2[2],
        v1[3] * v2[3]
        );
}

/// Returns component-wise quotient of vectors \p v1 and \p v2.
inline GfVec4h
GfCompDiv(GfVec4h const &v1, GfVec4h const &v2) {
    return GfVec4h(
        v1[0] / v2[0],
        v1[1] / v2[1],
        v1[2] / v2[2],
        v1[3] / v2[3]
        );
}

/// Returns the dot (inner) product of two vectors.
inline GfHalf
GfDot(GfVec4h const &v1, GfVec4h const &v2) {
    return v1 * v2;
}


/// Returns the geometric length of \c v.
inline GfHalf
GfGetLength(GfVec4h const &v)
{
    return v.GetLength();
}

/// Normalizes \c *v in place to unit length, returning the length before
/// normalization. If the length of \c *v is smaller than \p eps then \c *v is
/// set to \c *v/eps.  The original length of \c *v is returned.
inline GfHalf
GfNormalize(GfVec4h *v, GfHalf eps = 0.001)
{
    return v->Normalize(eps);
}

/// Returns a normalized (unit-length) vector with the same direction as \p v.
/// If the length of this vector is smaller than \p eps, the vector divided by
/// \p eps is returned.
inline GfVec4h
GfGetNormalized(GfVec4h const &v, GfHalf eps = 0.001)
{
    return v.GetNormalized(eps);
}

/// Returns the projection of \p a onto \p b. That is:
/// \code
/// b * (a * b)
/// \endcode
inline GfVec4h
GfGetProjection(GfVec4h const &a, GfVec4h const &b)
{
    return a.GetProjection(b);
}

/// Returns the orthogonal complement of \p a.GetProjection(b). That is:
/// \code
///  a - a.GetProjection(b)
/// \endcode
inline GfVec4h
GfGetComplement(GfVec4h const &a, GfVec4h const &b)
{
    return a.GetComplement(b);
}

/// Tests for equality within a given tolerance, returning \c true if the
/// length of the difference vector is less than or equal to \p tolerance.
inline bool
GfIsClose(GfVec4h const &v1, GfVec4h const &v2, double tolerance)
{
    GfVec4h delta = v1 - v2;
    return delta.GetLengthSq() <= tolerance * tolerance;
}



FORGE_NAMESPACE_END

#endif // FORGE_BASE_GF_VEC4H_H
