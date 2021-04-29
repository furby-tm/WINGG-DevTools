#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/property.h"
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
#ifndef FORGE_USD_USD_PROPERTY_H
#define FORGE_USD_USD_PROPERTY_H

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/usd/usd/common.h"
#include "forge/usd/usd/object.h"
#include "forge/usd/usd/prim.h"

#include "forge/usd/sdf/path.h"
#include "forge/usd/sdf/propertySpec.h"
#include "forge/base/vt/value.h"

FORGE_NAMESPACE_BEGIN


class UsdProperty;

/// \class UsdProperty
///
/// Base class for UsdAttribute and UsdRelationship scenegraph objects.
///
/// UsdProperty has a bool conversion operator that validates that the property
/// IsDefined() and thus valid for querying and authoring values and metadata.
/// This is a fairly expensive query that we do <b>not</b> cache, so if client
/// code retains UsdProperty objects it should manage its object validity
/// closely for performance.  An ideal pattern is to listen for
/// UsdNotice::StageContentsChanged notifications, and revalidate/refetch
/// retained UsdObjects only then and otherwise use them without validity
/// checking.
///
class UsdProperty : public UsdObject {
public:
    /// Construct an invalid property.
    UsdProperty() : UsdObject(_Null<UsdProperty>()) {}

    // --------------------------------------------------------------------- //
    /// \name Object and Namespace Accessors
    // --------------------------------------------------------------------- //

    /// @{

    /// Returns a strength-ordered list of property specs that provide
    /// opinions for this property.
    ///
    /// If \p time is UsdTimeCode::Default(), *or* this property
    /// is a UsdRelationship (which are never affected by clips), we will
    /// not consider value clips for opinions. For any other \p time, for
    /// a UsdAttribute, clips whose samples may contribute an opinion will
    /// be included. These specs are ordered from strongest to weakest opinion,
    /// although if \p time requires interpolation between two adjacent clips,
    /// both clips will appear, sequentially.
    ///
    /// \note The results returned by this method are meant for debugging
    /// and diagnostic purposes.  It is **not** advisable to retain a
    /// PropertyStack for the purposes of expedited value resolution for
    /// properties, since the makeup of an attribute's PropertyStack may
    /// itself be time-varying.  To expedite repeated value resolution of
    /// attributes, you should instead retain a \c UsdAttributeQuery .
    ///
    /// \sa UsdClipsAPI
    USD_API
    SdfPropertySpecHandleVector GetPropertyStack(
        UsdTimeCode time = UsdTimeCode::Default()) const;

    /// Return this property's name with all namespace prefixes removed,
    /// i.e. the last component of the return value of GetName()
    ///
    /// This is generally the property's "client name"; property namespaces are
    /// often used to group related properties together.  The namespace prefixes
    /// the property name but many consumers will care only about un-namespaced
    /// name, i.e. its BaseName.  For more information, see \ref Usd_Ordering
    USD_API
    TfToken GetBaseName() const;

    /// Return this property's complete namespace prefix.  Return the empty
    /// token if this property has no namespaces.
    ///
    /// This is the complement of GetBaseName(), although it does \em not
    /// contain a trailing namespace delimiter
    USD_API
    TfToken GetNamespace() const;

    /// Return this property's name elements including namespaces and its base
    /// name as the final element.
    USD_API
    std::vector<std::string> SplitName() const;

    /// @}
    /// \name Core Metadata
    /// @{

    /// Return this property's display group (metadata).  This returns the
    /// empty token if no display group has been set.
    /// \sa SetDisplayGroup()
    USD_API
    std::string GetDisplayGroup() const;

    /// Sets this property's display group (metadata).  Returns true on success.
    ///
    /// DisplayGroup provides UI hinting for grouping related properties
    /// together for display.  We define a convention for specifying nesting
    /// of groups by recognizing the property namespace separator in
    /// displayGroup as denoting group-nesting.
    /// \sa SetNestedDisplayGroups()
    USD_API
    bool SetDisplayGroup(const std::string& displayGroup) const;

    /// Clears this property's display group (metadata) in
    /// the current EditTarget (only).  Returns true on success.
    USD_API
    bool ClearDisplayGroup() const;

    /// Returns true if displayGroup was explicitly authored and GetMetadata()
    /// will return a meaningful value for displayGroup.
    USD_API
    bool HasAuthoredDisplayGroup() const;

    /// Return this property's displayGroup as a sequence of groups to be
    /// nested, or an empty vector if displayGroup is empty or not authored.
    USD_API
    std::vector<std::string> GetNestedDisplayGroups() const;

    /// Sets this property's display group (metadata) to the nested sequence.
    /// Returns true on success.
    ///
    /// A displayGroup set with this method can still be retrieved with
    /// GetDisplayGroup(), with the namespace separator embedded in the result.
    /// If \p nestedGroups is empty, we author an empty string for displayGroup.
    /// \sa SetDisplayGroup()
    USD_API
    bool SetNestedDisplayGroups(
        const std::vector<std::string>& nestedGroups) const;

    /// Return this property's display name (metadata).  This returns the
    /// empty string if no display name has been set.
    /// \sa SetDisplayName()
    USD_API
    std::string GetDisplayName() const;

    /// Sets this property's display name (metadata).  Returns true on success.
    ///
    /// DisplayName is meant to be a descriptive label, not necessarily an
    /// alternate identifier; therefore there is no restriction on which
    /// characters can appear in it.
    USD_API
    bool SetDisplayName(const std::string& name) const;

    /// Clears this property's display name (metadata) in the current EditTarget
    /// (only).  Returns true on success.
    USD_API
    bool ClearDisplayName() const;

    /// Returns true if displayName was explicitly authored and GetMetadata()
    /// will return a meaningful value for displayName.
    USD_API
    bool HasAuthoredDisplayName() const;

    /// Return true if this is a custom property (i.e., not part of a
    /// prim schema).
    ///
    /// The 'custom' modifier in USD serves the same function as Alembic's
    /// 'userProperties', which is to say as a categorization for ad hoc
    /// client data not formalized into any schema, and therefore not
    /// carrying an expectation of specific processing by consuming applications.
    USD_API
    bool IsCustom() const;

    /// Set the value for custom at the current EditTarget, return true on
    /// success, false if the value can not be written.
    ///
    /// \b Note that this value should not be changed as it is typically either
    /// automatically authored or provided by a property definition. This method
    /// is provided primarily for fixing invalid scene description.
    USD_API
    bool SetCustom(bool isCustom) const;

    /// @}
    /// \name Existence and Validity
    /// @{

    /// Return true if this is a builtin property or if the strongest
    /// authored SdfPropertySpec for this property's path matches this
    /// property's dynamic type.  That is, SdfRelationshipSpec in case this is a
    /// UsdRelationship, and SdfAttributeSpec in case this is a UsdAttribute.
    /// Return \c false if this property's prim has expired.
    ///
    /// For attributes, a \c true return does not imply that this attribute
    /// possesses a value, only that has been declared, is of a certain type and
    /// variability, and that it is safe to use to query and author values and
    /// metadata.
    USD_API
    bool IsDefined() const;

    /// Return true if there are any authored opinions for this property
    /// in any layer that contributes to this stage, false otherwise.
    USD_API
    bool IsAuthored() const;

    /// Return true if there is an SdfPropertySpec authored for this
    /// property at the given \a editTarget, otherwise return false.  Note
    /// that this method does not do partial composition.  It does not consider
    /// whether authored scene description exists at \a editTarget or weaker,
    /// only <b>exactly at</b> the given \a editTarget.
    USD_API
    bool IsAuthoredAt(const class UsdEditTarget &editTarget) const;

    /// @}

    // --------------------------------------------------------------------- //
    /// \name Flattening
    // --------------------------------------------------------------------- //

    /// Flattens this property to a property spec with the same name
    /// beneath the given \p parent prim in the edit target of its owning stage.
    ///
    /// The \p parent prim may belong to a different stage than this property's
    /// owning stage.
    ///
    /// Flattening authors all authored resolved values and metadata for
    /// this property into the destination property spec. If this property
    /// is a builtin property, fallback values and metadata will also be
    /// authored if the destination property has a different fallback
    /// value or no fallback value, or if the destination property has an
    /// authored value that overrides its fallback.
    ///
    /// Attribute connections and relationship targets that target an
    /// object beneath this property's owning prim will be remapped to
    /// target objects beneath the destination \p parent prim.
    ///
    /// If the destination spec already exists, it will be overwritten.
    ///
    /// \sa UsdStage::Flatten
    USD_API
    UsdProperty FlattenTo(const UsdPrim &parent) const;

    /// \overload
    /// Flattens this property to a property spec with the given
    /// \p propName beneath the given \p parent prim in the edit target of its
    /// owning stage.
    ///
    /// The \p parent prim may belong to a different stage than this property's
    /// owning stage.
    USD_API
    UsdProperty FlattenTo(const UsdPrim &parent,
                          const TfToken &propName) const;

    /// \overload
    /// Flattens this property to a property spec for the given
    /// \p property in the edit target of its owning prim's stage.
    ///
    /// The \p property owning prim may belong to a different stage than this
    /// property's owning stage.
    USD_API
    UsdProperty FlattenTo(const UsdProperty &property) const;

protected:
    template <class Derived>
    UsdProperty(_Null<Derived>) : UsdObject(_Null<Derived>()) {}

    // Gets the targets of the given spec type. Returns true if an authored
    // opinion is found and no composition errors occured. If foundErrors is
    // provided, it will be set to true only if errors are encountered.
    bool _GetTargets(SdfSpecType specType, SdfPathVector *out,
                     bool *foundErrors = nullptr) const;

private:
    friend class UsdAttribute;
    friend class UsdObject;
    friend class UsdPrim;
    friend class UsdRelationship;
    friend class Usd_PrimData;

    UsdProperty(UsdObjType objType,
                const Usd_PrimDataHandle &prim,
                const SdfPath &proxyPrimPath,
                const TfToken &propName)
        : UsdObject(objType, prim, proxyPrimPath, propName) {}

};


FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_PROPERTY_H
