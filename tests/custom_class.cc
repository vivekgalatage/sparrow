#include <gtest/gtest.h>

#include "sparrow.h"

class ClassWithAllCustom {
 public:
  ClassWithAllCustom(const ClassWithAllCustom&) {}
  ClassWithAllCustom& operator=(const ClassWithAllCustom&) { return *this; }
  ClassWithAllCustom(ClassWithAllCustom&&) {}
  ClassWithAllCustom& operator=(ClassWithAllCustom&&) { return *this; }
};

TEST(CustomClass, AllCustomTest) {
  sparrow::Trait<ClassWithAllCustom, sparrow::kAllCustom> all_custom;
  ASSERT_TRUE(true);
}

#if defined(USE_COMPILER_ERROR)

TEST(CustomClass, AllTrivialTest) {
  // This statement will result in compiler error: static_assert failed due to
  // requirement 'trivial_copy_constructor()'
  sparrow::Trait<ClassWithAllCustom, sparrow::kAllTrivial> all_trivial;
  ASSERT_TRUE(true);
}

#endif
