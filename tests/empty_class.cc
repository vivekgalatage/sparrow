#include <gtest/gtest.h>

#include "sparrow.h"

class Class {};

struct Struct {};

TEST(EmptyClass, NoConstraintTest) {
  sparrow::TypeChecker<Class> no_constraint;
  ASSERT_TRUE(true);
}

TEST(EmptyClass, NoConstraintStruct) {
  sparrow::TypeChecker<Struct> no_constraint;
  ASSERT_TRUE(true);
}
