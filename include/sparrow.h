#pragma once

#include <type_traits>

namespace sparrow {

enum Constraint {
  kNoConstraints = 0,
  kCustomCopyAssignment = 1 << 0,
  kCustomCopyConstructor = 1 << 1,
  kCustomMoveAssignment = 1 << 2,
  kCustomMoveConstructor = 1 << 3,
  kDeletedCopyAssignment = 1 << 4,
  kDeletedCopyConstructor = 1 << 5,
  kDeletedMoveAssignment = 1 << 6,
  kDeletedMoveConstructor = 1 << 7,
  kTrivialCopyAssignment = 1 << 8,
  kTrivialCopyConstructor = 1 << 9,
  kTrivialMoveAssignment = 1 << 10,
  kTrivialMoveConstructor = 1 << 11,
  kAllCustom = kCustomCopyAssignment | kCustomCopyConstructor |
               kCustomMoveAssignment | kCustomMoveConstructor,
  kAllDeleted = kDeletedCopyAssignment | kDeletedCopyConstructor |
                kDeletedMoveAssignment | kDeletedMoveConstructor,
  kAllTrivial = kTrivialCopyAssignment | kTrivialCopyConstructor |
                kTrivialMoveAssignment | kTrivialMoveConstructor,
};

template <typename T, int config = kNoConstraints>
class TypeChecker {
 public:
  static constexpr bool mutually_exclusive(Constraint c1,
                                           Constraint c2,
                                           Constraint c3) {
    return !((config & c1) && (config & c2)) &&
           !((config & c1) && (config & c3)) &&
           !((config & c2) && (config & c3));
  }

  static constexpr bool trivial_copy_assignment() {
    return (config & kTrivialCopyAssignment)
               ? std::is_trivially_copy_assignable<T>::value
               : true;
  }

  static constexpr bool trivial_copy_constructor() {
    return (config & kTrivialCopyConstructor)
               ? std::is_trivially_copy_constructible<T>::value
               : true;
  }

  static constexpr bool trivial_move_assignment() {
    return (config & kTrivialMoveAssignment)
               ? std::is_trivially_move_assignable<T>::value
               : true;
  }

  static constexpr bool trivial_move_constructor() {
    return (config & kTrivialMoveConstructor)
               ? std::is_trivially_move_constructible<T>::value
               : true;
  }

  static constexpr bool custom_copy_assignment() {
    return (config & kCustomCopyAssignment)
               ? !std::is_trivially_copy_assignable<T>::value
               : true;
  }

  static constexpr bool custom_copy_constructor() {
    return (config & kCustomCopyConstructor)
               ? !std::is_trivially_copy_constructible<T>::value
               : true;
  }

  static constexpr bool custom_move_assignment() {
    return (config & kCustomMoveAssignment)
               ? !std::is_trivially_move_assignable<T>::value
               : true;
  }

  static constexpr bool custom_move_constructor() {
    return (config & kCustomMoveConstructor)
               ? !std::is_trivially_move_constructible<T>::value &&
                     std::is_move_constructible<T>::value
               : true;
  }

  static constexpr bool deleted_copy_assignment() {
    return (config & kDeletedCopyAssignment)
               ? !std::is_trivially_copy_assignable<T>::value &&
                     !std::is_copy_assignable<T>::value
               : true;
  }

  static constexpr bool deleted_copy_constructor() {
    return (config & kDeletedCopyConstructor)
               ? !std::is_trivially_copy_constructible<T>::value &&
                     !std::is_copy_constructible<T>::value
               : true;
  }

  static constexpr bool deleted_move_assignment() {
    return (config & kDeletedMoveAssignment)
               ? !std::is_trivially_move_assignable<T>::value &&
                     !std::is_move_assignable<T>::value
               : true;
  }

  static constexpr bool deleted_move_constructor() {
    return (config & kDeletedMoveConstructor)
               ? !std::is_trivially_move_constructible<T>::value &&
                     !std::is_move_constructible<T>::value
               : true;
  }

  static constexpr bool all_custom() {
    return custom_copy_assignment() && custom_copy_constructor() &&
           custom_move_assignment() && custom_move_constructor();
  }

  static constexpr bool all_deleted() {
    return deleted_copy_assignment() && deleted_copy_constructor() &&
           deleted_move_assignment() && deleted_move_constructor();
  }

  static constexpr bool all_trivial() {
    return trivial_copy_assignment() && trivial_copy_constructor() &&
           trivial_move_assignment() && trivial_move_constructor();
  }

  static_assert(mutually_exclusive(kCustomCopyAssignment,
                                   kDeletedCopyAssignment,
                                   kTrivialCopyAssignment));
  static_assert(mutually_exclusive(kCustomCopyConstructor,
                                   kDeletedCopyConstructor,
                                   kTrivialCopyConstructor));
  static_assert(mutually_exclusive(kCustomMoveAssignment,
                                   kDeletedMoveAssignment,
                                   kTrivialMoveAssignment));
  static_assert(mutually_exclusive(kCustomMoveConstructor,
                                   kDeletedMoveConstructor,
                                   kTrivialMoveConstructor));

  static_assert(custom_copy_assignment());
  static_assert(custom_copy_constructor());
  static_assert(custom_move_assignment());
  static_assert(custom_move_constructor());

  static_assert(deleted_copy_assignment());
  static_assert(deleted_copy_constructor());
  static_assert(deleted_move_assignment());
  static_assert(deleted_move_constructor());

  static_assert(trivial_copy_assignment());
  static_assert(trivial_copy_constructor());
  static_assert(trivial_move_assignment());
  static_assert(trivial_move_constructor());
};

}  // namespace sparrow
