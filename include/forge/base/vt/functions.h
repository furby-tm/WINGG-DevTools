#line 1 "C:/Users/tyler/dev/WINGG/forge/base/vt/functions.h"
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
#if !BOOST_PP_IS_ITERATING

#ifndef FORGE_BASE_VT_FUNCTIONS_H
#define FORGE_BASE_VT_FUNCTIONS_H

/// \file vt/functions.h

#include "forge/forge.h"
#include "forge/base/vt/api.h"
#include "forge/base/vt/array.h"
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <vector>

FORGE_NAMESPACE_BEGIN

#define VT_FUNCTIONS_MAX_ARGS 6

// Set up preprocessor iterations to allow various functions to accept multiple
// arguments.

// VtCat
#define BOOST_PP_ITERATION_PARAMS_1 (4, \
    (0, VT_FUNCTIONS_MAX_ARGS, "forge/base/vt/functions.h", 0))
#include BOOST_PP_ITERATE()

// ****************************************************************************
// Doc headers for functions that are generated through macros.  These get
// decent doxygen (and epydoc) output even though we can't put them on the
// real functions because they're expanded through boost or cpp macros.
// ****************************************************************************

// documentation for bool-result array comparison functions
#ifdef doxygen

/// Returns a bool array specifying, element-by-element, if the two inputs
/// contain equal values.  The shape of the return array is the same as the
/// shape of the largest input array.
///
/// If one input is a single element (either a single-element array or a scalar
/// of the same type held in the array), it is compared to all the elements
/// in the other array.  Otherwise both arrays must have the same shape.
template<typename T>
VtArray<T>
VtEqual( VtArray<T> const &a, VtArray<T> const &b );
template<typename T>
VtArray<T>
VtEqual( T const &a, VtArray<T> const &b );
template<typename T>
VtArray<T>
VtEqual( VtArray<T> const &a, T const &b );

/// Returns a bool array specifying, element-by-element, if the two inputs
/// contain inequal values.  The shape of the return array is the same as the
/// shape of the largest input array.
///
/// If one input is a single element (either a single-element array or a scalar
/// of the same type held in the array), it is compared to all the elements
/// in the other array.  Otherwise both arrays must have the same shape.
template<typename T>
VtArray<T>
VtNotEqual( VtArray<T> const &a, VtArray<T> const &b );
template<typename T>
VtArray<T>
VtNotEqual( T const &a, VtArray<T> const &b );
template<typename T>
VtArray<T>
VtNotEqual( VtArray<T> const &a, T const &b );

/// Returns a bool array specifying, element-by-element, if the first input
/// contains values greater than those in the second input. The shape of the
/// return array is the same as the shape of the largest input array.
///
/// If one input is a single element (either a single-element array or a scalar
/// of the same type held in the array), it is compared to all the elements
/// in the other array.  Otherwise both arrays must have the same shape.
template<typename T>
VtArray<T>
VtGreater( VtArray<T> const &a, VtArray<T> const &b );
template<typename T>
VtArray<T>
VtGreater( T const &a, VtArray<T> const &b );
template<typename T>
VtArray<T>
VtGreater( VtArray<T> const &a, T const &b );

/// Returns a bool array specifying, element-by-element, if the first input
/// contains values less than those in the second input. The shape of the
/// return array is the same as the shape of the largest input array.
///
/// If one input is a single element (either a single-element array or a scalar
/// of the same type held in the array), it is compared to all the elements
/// in the other array.  Otherwise both arrays must have the same shape.
template<typename T>
VtArray<T>
VtLess( VtArray<T> const &a, VtArray<T> const &b );
template<typename T>
VtArray<T>
VtLess( T const &a, VtArray<T> const &b );
template<typename T>
VtArray<T>
VtLess( VtArray<T> const &a, T const &b );

/// Returns a bool array specifying, element-by-element, if the first input
/// contains values greater than or equal to those in the second input. The
/// shape of the return array is the same as the shape of the largest input
/// array.
///
/// If one input is a single element (either a single-element array or a scalar
/// of the same type held in the array), it is compared to all the elements
/// in the other array.  Otherwise both arrays must have the same shape.
template<typename T>
VtArray<T>
VtGreaterOrEqual( VtArray<T> const &a, VtArray<T> const &b );
template<typename T>
VtArray<T>
VtGreaterOrEqual( T const &a, VtArray<T> const &b );
template<typename T>
VtArray<T>
VtGreaterOrEqual( VtArray<T> const &a, T const &b );

/// Returns a bool array specifying, element-by-element, if the first input
/// contains values less than or equal to those in the second input. The shape
/// of the return array is the same as the shape of the largest input array.
///
/// If one input is a single element (either a single-element array or a scalar
/// of the same type held in the array), it is compared to all the elements
/// in the other array.  Otherwise both arrays must have the same shape.
template<typename T>
VtArray<T>
VtLessOrEqual( VtArray<T> const &a, VtArray<T> const &b );
template<typename T>
VtArray<T>
VtLessOrEqual( T const &a, VtArray<T> const &b );
template<typename T>
VtArray<T>
VtLessOrEqual( VtArray<T> const &a, T const &b );

#endif

// provide documentation for functions with variable numbers of inputs
#ifdef doxygen

/// Concatenates arrays.
///
/// The result is an array with length equal to the sum of the number
/// of elements in the source arrays.
template<typename T>
VtArray<T>
VtCat( VtArray<T> const &a0, VtArray<T> const &a1, ... VtArray<T> const &aN);

#endif

// ****************************************************************************
// Fixed-number-of-arguments functions go here (no preprocessor iteration to
// handle multiple args)
// ****************************************************************************

/// Returns true if any element of input array is not VtZero, else false.
///
/// Intended to be used to evaluate results of boolean operations on arrays, e.g.
/// \code
/// a = Vt.StringArray((3,),("foo","bar","baz"))
/// t = Vt.AnyTrue(Vt.Equal(a,"bar"))
/// \endcode
///
/// (This example, if
/// you look carefully, evaluates this function not on the strings, but on
/// the results of the comparison).
template<typename T>
bool VtAnyTrue(VtArray<T> const &a)
{
    if (a.empty())
        return false;

    for (size_t i = 0; i != a.size(); ++i) {
        if (a[i] != VtZero<T>())
            return true;
    }

    return false;
}


/// Returns true if every element of input array is not VtZero, else false.
///
/// Intended to be used to evaluate results of boolean operations on arrays, e.g.
/// \code
/// a = Vt.StringArray((3,),("foo","bar","baz"))
/// t = Vt.AllTrue(Vt.Equal(a,"bar"))
/// \endcode
///
/// (This example, if you look carefully, evaluates this function not on the
/// strings, but on the results of the comparison).
template<typename T>
bool
VtAllTrue(VtArray<T> const &a)
{
    if (a.empty())
        return false;

    for (size_t i = 0; i != a.size(); ++i) {
        if (a[i] == VtZero<T>())
            return false;
    }

    return true;
}

// Macro defining functions for element-by-element comparison
// operators (i.e. Equal, etc).  There are three versions; each returns
// a VtBoolArray of the same shape as the largest input.
// *) two input arrays:
//    If one array contains a single element, it is compared to all the elements
//    in the other array.  Otherwise both arrays must have the same shape.
// *) scalar and array:
//    The scalar is compared to all the elements in the array.
// *) array and scalar:
//    The same as scalar and array.
#define VTFUNCTION_BOOL(funcname,op)                                \
template<typename T>                                                \
VtArray<bool>                                                       \
funcname(T const &scalar, VtArray<T> const &vec) {                  \
    VtArray<bool> ret(vec.size());                                  \
    for (size_t i = 0, n = vec.size(); i != n; ++i) {               \
        ret[i] = (scalar op vec[i]);                                \
    }                                                               \
    return ret;                                                     \
}                                                                   \
template<typename T>                                                \
VtArray<bool>                                                       \
funcname(VtArray<T> const &vec, T const &scalar) {                  \
    VtArray<bool> ret(vec.size());                                  \
    for (size_t i = 0, n = vec.size(); i != n; ++i) {               \
        ret[i] = (vec[i] op scalar);                                \
    }                                                               \
    return ret;                                                     \
}                                                                   \
template<typename T>                                                \
VtArray<bool>                                                       \
funcname(VtArray<T> const &a, VtArray<T> const &b)                  \
{                                                                   \
    if (a.empty() || b.empty()) {                                   \
        return VtArray<bool>();                                     \
    }                                                               \
                                                                    \
    if (a.size() == 1) {                                            \
        return funcname(a[0], b);                                   \
    } else if (b.size() == 1) {                                     \
        return funcname(a, b[0]);                                   \
    } else if (a.size() == b.size()) {                              \
        VtArray<bool> ret(a.size());                                \
        for (size_t i = 0, n = a.size(); i != n; ++i) {             \
            ret[i] = (a[i] op b[i]);                                \
        }                                                           \
        return ret;                                                 \
    } else {                                                        \
        TF_CODING_ERROR("Non-conforming inputs.");                  \
        return VtArray<bool>();                                     \
    }                                                               \
}

VTFUNCTION_BOOL(VtEqual,==)
VTFUNCTION_BOOL(VtNotEqual,!=)
VTFUNCTION_BOOL(VtGreater,>)
VTFUNCTION_BOOL(VtLess,<)
VTFUNCTION_BOOL(VtGreaterOrEqual,>=)
VTFUNCTION_BOOL(VtLessOrEqual,<=)

FORGE_NAMESPACE_END

#endif // FORGE_BASE_VT_FUNCTIONS_H

#else // BOOST_PP_IS_ITERATING

// ****************************************************************************
// Variable-number-of-arguments functions go here; preprocessor iteration
// includes this file again and again, but turns off the pieces we don't
// want to use for a particular function.
// ****************************************************************************

#define N BOOST_PP_ITERATION()

#if BOOST_PP_ITERATION_FLAGS() == 0 // VtCat

#define VtCat_SIZE(dummy, n, dummy2) newSize += s##n.size();
#define VtCat_COPY(dummy, n, dummy2) \
    for (size_t i = 0; i < s##n.size(); ++i) \
        ret[offset+i] = s##n[i]; \
    offset += s##n.size();

// real documentation is above (for doxygen purposes)
template<typename T>
VtArray<T>
VtCat( BOOST_PP_ENUM_PARAMS(N, VtArray<T> const &s) )
{
    size_t newSize = 0;

    BOOST_PP_REPEAT( N, VtCat_SIZE, ignored )

    if (newSize == 0)
        return VtArray<T>();

    // new array with flattened size
    VtArray<T> ret(newSize);

    // fill it with data from old arrays
#if N > 0
    size_t offset = 0;
    BOOST_PP_REPEAT( N, VtCat_COPY, ignored )
#endif

    return ret;
}

#undef VtCat_SIZE
#undef VtCat_COPY

#endif // BOOST_PP_ITERATION_FLAGS

#undef N

#endif // BOOST_PP_IS_ITERATING
