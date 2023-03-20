#include <gtest/gtest.h>

#include "sparrow.h"

class Class {};

struct Struct {};

TEST(EmptyClass, NoConstraintTest) {
  sparrow::Trait<Class> no_constraint;
  ASSERT_TRUE(true);
}

TEST(EmptyClass, NoConstraintStruct) {
  sparrow::Trait<Struct> no_constraint;
  ASSERT_TRUE(true);
}
