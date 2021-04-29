#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pyModule.h"
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
#ifdef FORGE_BASE_TF_PY_MODULE_H
#error This file should only be included once in any given source (.cpp) file.
#endif
#define FORGE_BASE_TF_PY_MODULE_H

#include "forge/forge.h"

#include "forge/base/arch/attributes.h"
#include "forge/base/tf/api.h"
#include "forge/base/tf/preprocessorUtilsLite.h"

#include <boost/preprocessor/cat.hpp>
#include <boost/python/module.hpp>

// Helper macros for module files.  If you implement your wrappers for classes
// as functions named wrapClassName(), then you can create your module like
// this:
//
// TF_WRAP_MODULE(ModuleName) {
//    TF_WRAP(ClassName1);
//    TF_WRAP(ClassName2);
//    TF_WRAP(ClassName3);
// }
//

// Forward declare the function that will be provided that does the wrapping.
static void WrapModule();

FORGE_NAMESPACE_BEGIN

TF_API
void Tf_PyInitWrapModule(void (*wrapModule)(),
                         const char* packageModule,
                         const char* packageName,
                         const char* packageTag,
                         const char* packageTag2);

ARCH_EXPORT
void BOOST_PP_CAT(init_module_, MFB_PACKAGE_NAME)() {

    Tf_PyInitWrapModule(
        WrapModule,
        TF_PP_STRINGIZE(MFB_PACKAGE_MODULE),
        TF_PP_STRINGIZE(MFB_ALT_PACKAGE_NAME),
        "Wrap " TF_PP_STRINGIZE(MFB_ALT_PACKAGE_NAME),
        TF_PP_STRINGIZE(MFB_PACKAGE_NAME)
        );
}

FORGE_NAMESPACE_END

#if PY_MAJOR_VERSION == 2
// When we generate boost python bindings for a library named Foo,
// we generate a python package that has __init__.py and _Foo.so,
// and we put all the python bindings in _Foo.so.  The __init__.py
// file imports _Foo and then publishes _Foo's symbols as its own.
// Since the module with the bindings is named _Foo, the init routine
// must be named init_Foo.  This little block produces that function.
//
extern "C"
ARCH_EXPORT
void BOOST_PP_CAT(init_, MFB_PACKAGE_NAME)() {
    FORGE_NAMESPACE_USING
    boost::python::detail::init_module
        (TF_PP_STRINGIZE(BOOST_PP_CAT(_,MFB_PACKAGE_NAME)),
         TF_PP_CAT(&init_module_, MFB_PACKAGE_NAME));
}

// We also support the case where both the library contents and the
// python bindings go into libfoo.so.  We still generate a package named foo
// but the __init__.py file in the package foo imports libfoo and
// publishes it's symbols as its own.  Since the module with the
// bindings is named libfoo, the init routine must be named initlibfoo.
// This little block produces that function.
//
// So there are two init routines in every library, but only the one
// that matches the name of the python module will be called by python
// when the module is imported.  So the total cost is a 1-line
// function that doesn't get called.
//
extern "C"
ARCH_EXPORT
void BOOST_PP_CAT(initlib, MFB_PACKAGE_NAME)() {
    FORGE_NAMESPACE_USING
    boost::python::detail::init_module
        (TF_PP_STRINGIZE(BOOST_PP_CAT(lib,MFB_PACKAGE_NAME)),
         TF_PP_CAT(&init_module_, MFB_PACKAGE_NAME));
}

#else // Python 3:

// These functions serve the same purpose as the python 2 implementations
// above, but are updated for the overhauled approach to module initialization
// in python 3. In python 3 init<name> is replaced by PyInit_<name>, and
// initlib<name> becomes PyInit_lib<name>. The init_module function still
// exists, but now takes a struct of input values instead of a list of
// parameters. Also, these functions now return a PyObject* instead of void.
//
// See https://docs.python.org/3/c-api/module.html#initializing-c-modules_
//
extern "C"
ARCH_EXPORT
PyObject* BOOST_PP_CAT(PyInit__, MFB_PACKAGE_NAME)() {

    static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        TF_PP_STRINGIZE(BOOST_PP_CAT(_, MFB_PACKAGE_NAME)), // m_name
        0,                                                  // m_doc
        -1,                                                 // m_size
        NULL,                                               // m_methods
        0,                                                  // m_reload
        0,                                                  // m_traverse
        0,                                                  // m_clear
        0,                                                  // m_free
    };

    FORGE_NAMESPACE_USING
    return boost::python::detail::init_module(moduledef,
                BOOST_PP_CAT(init_module_, MFB_PACKAGE_NAME));
}

extern "C"
ARCH_EXPORT
PyObject* BOOST_PP_CAT(PyInit_lib, MFB_PACKAGE_NAME)() {

    static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        TF_PP_STRINGIZE(BOOST_PP_CAT(lib, MFB_PACKAGE_NAME)), // m_name
        0,                                                    // m_doc
        -1,                                                   // m_size
        NULL,                                                 // m_methods
        0,                                                    // m_reload
        0,                                                    // m_traverse
        0,                                                    // m_clear
        0,                                                    // m_free
    };

    FORGE_NAMESPACE_USING
    return boost::python::detail::init_module(moduledef,
                BOOST_PP_CAT(init_module_, MFB_PACKAGE_NAME));
}

#endif


#define TF_WRAP_MODULE static void WrapModule()

// Declares and calls the class wrapper for x
#define TF_WRAP(x) ARCH_HIDDEN void wrap ## x (); wrap ## x ()
