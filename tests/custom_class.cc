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
  sparrow::TypeChecker<ClassWithAllCustom, sparrow::kAllCustom> all_custom;
  ASSERT_TRUE(true);
}

#if defined(USE_COMPILER_ERROR)

TEST(CustomClass, AllTrivialTest) {
  sparrow::TypeChecker<ClassWithAllCustom, sparrow::kAllTrivial> all_trivial;
  ASSERT_TRUE(true);
}

#endif
