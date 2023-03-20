#include <gtest/gtest.h>

#include "sparrow.h"

struct Person {
  Person(int a) : age(a) {}
  Person(Person&& rhs) {
    age = std::move(rhs.age);
    rhs.age = -1;
  }

  int age = -1;
};

struct IncorrectPerson {
  IncorrectPerson(int a) : age(a) {}
  int age = -1;
};

TEST(PersonExample, PersonMove) {
  using TypeChecker =
      sparrow::TypeChecker<Person, sparrow::kCustomMoveConstructor>;
  constexpr TypeChecker c1;
  Person p1(42);
  Person p2 = std::move(p1);
  ASSERT_EQ(p1.age, -1);
  ASSERT_EQ(p2.age, 42);
}

TEST(PersonExample, IncorrectPersonMove) {
  using TypeChecker = sparrow::TypeChecker<IncorrectPerson>;
  using TypeChecker2 =
      sparrow::TypeChecker<IncorrectPerson, sparrow::kTrivialMoveConstructor>;

  constexpr TypeChecker t1;
  constexpr TypeChecker2 t2;

  IncorrectPerson p1(42);
  IncorrectPerson p2 = std::move(p1);
  ASSERT_NE(p1.age, -1);
  ASSERT_EQ(p2.age, 42);
}
