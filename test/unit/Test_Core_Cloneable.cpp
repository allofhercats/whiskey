#include <gtest/gtest.h>

#include <whiskey/Whiskey.hpp>

using namespace whiskey;

// class Simple : public Cloneable<Simple> {
// public:
//   int x, y;

// protected:
//   virtual Simple *
//   onClone() const {
//     return new Simple(x, y);
//   }

// public:
//   Simple(int x, int y) : x(x), y(y) {}
// };

// TEST(Test_Core_Cloneable, Simple) {
//   Simple *s0 = new Simple(0, 1);
//   Simple *s1 = new Simple(1, 1);

//   ASSERT_EQ(s0->x, 0);
//   ASSERT_EQ(s0->y, 1);
//   ASSERT_EQ(s1->x, 1);
//   ASSERT_EQ(s1->y, 1);

//   Simple *s2 = s0->clone();
//   Simple *s3 = s1->clone();

//   ASSERT_EQ(s2->x, 0);
//   ASSERT_EQ(s2->y, 1);
//   ASSERT_EQ(s3->x, 1);
//   ASSERT_EQ(s3->y, 1);

//   s0->x = 2;
//   s1->x = 3;

//   ASSERT_EQ(s0->x, 2);
//   ASSERT_EQ(s0->y, 1);
//   ASSERT_EQ(s1->x, 3);
//   ASSERT_EQ(s1->y, 1);

//   ASSERT_EQ(s2->x, 0);
//   ASSERT_EQ(s2->y, 1);
//   ASSERT_EQ(s3->x, 1);
//   ASSERT_EQ(s3->y, 1);
// }

// class Inherited : public Simple {
// public:
//   int z;

// protected:
//   Simple *
//   onClone() const {
//     return new Inherited(x, y, z);
//   }

// public:
//   Inherited(int x, int y, int z) : Simple(x, y), z(z) {}
// };

// TEST(Test_Core_Cloneable, Inherited) {
//   Simple *s0 = new Simple(0, 1);
//   Simple *s1 = new Inherited(1, 1, 1);

//   ASSERT_EQ(s0->x, 0);
//   ASSERT_EQ(s0->y, 1);
//   ASSERT_EQ(s1->x, 1);
//   ASSERT_EQ(s1->y, 1);
//   ASSERT_EQ(static_cast<Inherited *>(s1)->z, 1);

//   Simple *s2 = s0->clone();
//   Simple *s3 = s1->clone();

//   ASSERT_EQ(s2->x, 0);
//   ASSERT_EQ(s2->y, 1);
//   ASSERT_EQ(s3->x, 1);
//   ASSERT_EQ(s3->y, 1);
//   ASSERT_EQ(static_cast<Inherited *>(s3)->z, 1);

//   s0->x                           = 2;
//   s1->x                           = 3;
//   static_cast<Inherited *>(s1)->z = 4;

//   ASSERT_EQ(s0->x, 2);
//   ASSERT_EQ(s0->y, 1);
//   ASSERT_EQ(s1->x, 3);
//   ASSERT_EQ(s1->y, 1);
//   ASSERT_EQ(static_cast<Inherited *>(s1)->z, 4);

//   ASSERT_EQ(s2->x, 0);
//   ASSERT_EQ(s2->y, 1);
//   ASSERT_EQ(s3->x, 1);
//   ASSERT_EQ(s3->y, 1);
//   ASSERT_EQ(static_cast<Inherited *>(s3)->z, 1);
// }
