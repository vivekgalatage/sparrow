#include <gtest/gtest.h>

#include "sparrow.h"

class ClassWithAllTrivial {
 public:
  ClassWithAllTrivial(const ClassWithAllTrivial&) = default;
  ClassWithAllTrivial& operator=(const ClassWithAllTrivial&) = default;
  ClassWithAllTrivial(ClassWithAllTrivial&&) = default;
  ClassWithAllTrivial& operator=(ClassWithAllTrivial&&) = default;
};

TEST(TrivialClass, AllTrivialTest) {
  sparrow::Trait<ClassWithAllTrivial, sparrow::kAllTrivial> all_trivial;
  ASSERT_TRUE(true);
}

#if defined(USE_COMPILER_ERROR)

TEST(TrivialClass, AllCustomTest) {
  // This statement will result in compiler error: static_assert failed due to
  // requirement 'custom_copy_constructor()'
  sparrow::Trait<ClassWithAllTrivial, sparrow::kAllCustom> all_custom;
  ASSERT_TRUE(true);
}

#endif
