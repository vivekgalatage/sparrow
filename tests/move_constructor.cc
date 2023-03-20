#include <gtest/gtest.h>
#include <memory>

#include "sparrow.h"

class CustomMoveConstructor {
 public:
  CustomMoveConstructor() = default;
  CustomMoveConstructor(CustomMoveConstructor&&) {}
};

class DeletedMoveConstructor {
 public:
  DeletedMoveConstructor() = default;
  DeletedMoveConstructor(DeletedMoveConstructor&&) = delete;
};

class TrivialMoveConstructor {
 public:
  TrivialMoveConstructor() = default;
  TrivialMoveConstructor(TrivialMoveConstructor&&) = default;
};

TEST(MoveConstructor, Custom) {
  using CorrectType = sparrow::TypeChecker<CustomMoveConstructor,
                                           sparrow::kCustomMoveConstructor>;
  CorrectType c1;
  CustomMoveConstructor d1;
  CustomMoveConstructor d2 = std::move(d1);
}

#if defined(USE_COMPILER_ERROR)
TEST(MoveConstructor, CustomError) {
  using ErrorType1 = sparrow::TypeChecker<CustomMoveConstructor,
                                          sparrow::kTrivialMoveConstructor>;
  using ErrorType2 = sparrow::TypeChecker<CustomMoveConstructor,
                                          sparrow::kDeletedMoveConstructor>;
  ErrorType1 t1;
  ErrorType2 t2;
}
#endif  // defined(USE_COMPILER_ERROR)

TEST(MoveConstructor, Deleted) {
  DeletedMoveConstructor d1;
#if defined(USE_COMPILER_ERROR)
  DeletedMoveConstructor d2 = std::move(d1);
#endif
}

#if defined(USE_COMPILER_ERROR)
TEST(MoveConstructor, DeletedError) {
  using ErrorType1 = sparrow::TypeChecker<DeletedMoveConstructor,
                                          sparrow::kCustomMoveConstructor>;
  using ErrorType2 = sparrow::TypeChecker<DeletedMoveConstructor,
                                          sparrow::kTrivialMoveConstructor>;
  ErrorType1 t1;
  ErrorType2 t2;
}
#endif  // defined(USE_COMPILER_ERROR)

TEST(MoveConstructor, Trivial) {
  TrivialMoveConstructor d1;
  TrivialMoveConstructor d2 = std::move(d1);
}

#if defined(USE_COMPILER_ERROR)
TEST(MoveConstructor, TrivialError) {
  using ErrorType1 = sparrow::TypeChecker<TrivialMoveConstructor,
                                          sparrow::kCustomMoveConstructor>;
  using ErrorType2 = sparrow::TypeChecker<TrivialMoveConstructor,
                                          sparrow::kDeletedMoveConstructor>;
  ErrorType1 t1;
  ErrorType2 t2;
}
#endif  // defined(USE_COMPILER_ERROR)
