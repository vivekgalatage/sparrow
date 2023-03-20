#pragma once

#include <type_traits>

namespace sparrow {

enum Constraint {
  kNoConstraints = 0,
  kTrivialMoveConstructor = 1 << 0,
  kTrivialMoveAssignment = 1 << 1,
  kTrivialCopyConstructor = 1 << 2,
  kTrivialCopyAssignment = 1 << 3,
  kCustomMoveConstructor = 1 << 4,
  kCustomMoveAssignment = 1 << 5,
  kCustomCopyConstructor = 1 << 6,
  kCustomCopyAssignment = 1 << 7,
  kAllTrivial = kTrivialCopyConstructor | kTrivialCopyAssignment |
                kTrivialMoveConstructor | kTrivialMoveAssignment,
  kAllCustom = kCustomCopyConstructor | kCustomCopyAssignment |
               kCustomMoveConstructor | kCustomMoveAssignment,
};

template <typename T, int config = kNoConstraints>
class Trait {
 public:
  static constexpr bool mutually_exclusive(Constraint c1, Constraint c2) {
    return !((config & c1) && (config & c2));
  }

  static constexpr bool trivial_copy_constructor() {
    if (!(config & kTrivialCopyConstructor)) {
      return true;
    }
    return std::is_trivially_copy_constructible<T>::value;
  }

  static constexpr bool trivial_copy_assignment() {
    if (!(config & kTrivialCopyAssignment)) {
      return true;
    }
    return std::is_trivially_copy_assignable<T>::value;
  }

  static constexpr bool trivial_move_constructor() {
    if (!(config & kTrivialMoveConstructor)) {
      return true;
    }
    return std::is_trivially_move_constructible<T>::value;
  }

  static constexpr bool trivial_move_assignment() {
    if (!(config & kTrivialMoveAssignment)) {
      return true;
    }
    return std::is_trivially_move_assignable<T>::value;
  }

  static constexpr bool custom_copy_constructor() {
    if (!(config & kCustomCopyConstructor)) {
      return true;
    }
    return !std::is_trivially_copy_constructible<T>::value;
  }

  static constexpr bool custom_copy_assignment() {
    if (!(config & kCustomCopyAssignment)) {
      return true;
    }
    return !std::is_trivially_copy_assignable<T>::value;
  }

  static constexpr bool custom_move_constructor() {
    if (!(config & kCustomMoveConstructor)) {
      return true;
    }
    return !std::is_trivially_move_constructible<T>::value &&
           std::is_move_constructible<T>::value;
  }

  static constexpr bool custom_move_assignment() {
    if (!(config & kCustomMoveAssignment)) {
      return true;
    }
    return !std::is_trivially_move_assignable<T>::value;
  }

  static_assert(mutually_exclusive(kTrivialMoveConstructor,
                                   kCustomMoveConstructor));
  static_assert(mutually_exclusive(kTrivialCopyConstructor,
                                   kCustomCopyConstructor));
  static_assert(mutually_exclusive(kTrivialMoveAssignment,
                                   kCustomMoveAssignment));
  static_assert(mutually_exclusive(kTrivialCopyAssignment,
                                   kCustomCopyAssignment));
  static_assert(trivial_copy_constructor());
  static_assert(trivial_copy_assignment());
  static_assert(trivial_move_constructor());
  static_assert(trivial_move_assignment());

  static_assert(custom_copy_constructor());
  static_assert(custom_copy_assignment());
  static_assert(custom_move_constructor());
  static_assert(custom_move_assignment());
};

}  // namespace sparrow
