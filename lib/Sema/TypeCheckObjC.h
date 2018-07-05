//===--- TypeCheckObjC.h - Type Checking for ObjC interop -------*- C++ -*-===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2017 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//
//
// This file provides utilities for type-checking interoperability with
// Objective-C.
//
//===----------------------------------------------------------------------===//
#ifndef SWIFT_SEMA_TYPE_CHECK_OBJC_H
#define SWIFT_SEMA_TYPE_CHECK_OBJC_H

#include "swift/AST/ForeignErrorConvention.h"
#include "llvm/ADT/Optional.h"

namespace swift {

class ASTContext;
class TypeChecker;
class ValueDecl;

using llvm::Optional;

/// Describes the reason why are we trying to apply @objc to a declaration.
///
/// Should only affect diagnostics. If you change this enum, also change
/// the OBJC_ATTR_SELECT macro in DiagnosticsSema.def.
enum class ObjCReason {
  /// Has the '@cdecl' attribute.
  ExplicitlyCDecl,
  /// Has the 'dynamic' modifier.
  ExplicitlyDynamic,
  /// Has an explicit '@objc' attribute.
  ExplicitlyObjC,
  /// Has an explicit '@IBOutlet' attribute.
  ExplicitlyIBOutlet,
  /// Has an explicit '@IBAction' attribute.
  ExplicitlyIBAction,
  /// Has an explicit '@NSManaged' attribute.
  ExplicitlyNSManaged,
  /// Is a member of an @objc protocol.
  MemberOfObjCProtocol,
  /// Implicitly-introduced @objc.
  ImplicitlyObjC,
  /// Is an override of an @objc member.
  OverridesObjC,
  /// Is a witness to an @objc protocol requirement.
  WitnessToObjC,
  /// Has an explicit '@IBInspectable' attribute.
  ExplicitlyIBInspectable,
  /// Has an explicit '@GKInspectable' attribute.
  ExplicitlyGKInspectable,
  /// Is it a member of an @objc extension of a class.
  MemberOfObjCExtension,
  /// Is it a member of an @objcMembers class.
  MemberOfObjCMembersClass,
  /// A member of an Objective-C-defined class or subclass.
  MemberOfObjCSubclass,
  /// An accessor to a property.
  Accessor,
};

/// Determine whether we should diagnose conflicts due to inferring @objc
/// with this particular reason.
bool shouldDiagnoseObjCReason(ObjCReason reason, ASTContext &ctx);

/// Return the %select discriminator for the OBJC_ATTR_SELECT macro used to
/// complain about the correct attribute during @objc inference.
unsigned getObjCDiagnosticAttrKind(ObjCReason reason);

/// Figure out if a declaration should be exported to Objective-C.
Optional<ObjCReason> shouldMarkAsObjC(TypeChecker &TC,
                                      const ValueDecl *VD,
                                      bool allowImplicit = false);

/// Record whether the given declatation is @objc, and why.
void markAsObjC(TypeChecker &TC, ValueDecl *D,
                Optional<ObjCReason> isObjC,
                Optional<ForeignErrorConvention> errorConvention = llvm::None);

} // end namespace swift

#endif // SWIFT_SEMA_TYPE_CHECK_OBJC_H
