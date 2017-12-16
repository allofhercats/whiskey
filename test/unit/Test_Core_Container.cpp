#include <gtest/gtest.h>

#include <whiskey/Whiskey.hpp>

using namespace whiskey;

class Simple : public Cloneable<Simple> {
public:
	int x, y;

protected:
	Simple *onClone() const {
		return new Simple(x, y);
	}

public:
	Simple(int x, int y) : x(x), y(y) {}

	bool operator==(const Simple &other) const {
		return x == other.x && y == other.y;
	}
};

TEST(Test_Core_Container, Simple_Empty) {
	Container<Simple> c0;

	ASSERT_FALSE(c0);

	ASSERT_DEATH({
		int r = c0->x;
		std::cout << r; // to prevent optimizing out
	}, "");

	ASSERT_DEATH({
		Simple &r = *c0;
		std::cout << r.x; // to prevent optimizing out
	}, "");

	Container<Simple> c1;

	ASSERT_TRUE(c0 == c1);
	ASSERT_FALSE(c0 != c1);

	c1 = c0;

	ASSERT_FALSE(c1);

	ASSERT_DEATH({
		int r = c1->x;
		std::cout << r; // to prevent optimizing out
	}, "");

	ASSERT_DEATH({
		Simple &r = *c1;
		std::cout << r.x; // to prevent optimizing out
	}, "");

	ASSERT_TRUE(c0 == c1);
	ASSERT_FALSE(c0 != c1);
}

TEST(Test_Core_Container, Simple_NonEmpty) {
	Container<Simple> c0 = new Simple(0, 1);

	ASSERT_TRUE(c0);

	ASSERT_EQ(c0->x, 0);
	ASSERT_EQ(c0->y, 1);

	ASSERT_EQ((*c0).x, 0);
	ASSERT_EQ((*c0).y, 1);

	Container<Simple> c1;

	ASSERT_FALSE(c0 == c1);
	ASSERT_TRUE(c0 != c1);

	c1 = c0;

	ASSERT_TRUE(c1);

	ASSERT_EQ(c1->x, 0);
	ASSERT_EQ(c1->y, 1);

	ASSERT_EQ((*c1).x, 0);
	ASSERT_EQ((*c1).y, 1);

	ASSERT_TRUE(c0 == c1);
	ASSERT_FALSE(c0 != c1);
}

TEST(Test_Core_Container, Simple_Copying) {
	Container<Simple> c0 = new Simple(0, 1);

	ASSERT_EQ(c0->x, 0);
	ASSERT_EQ(c0->y, 1);

	Container<Simple> c1 = c0;

	ASSERT_EQ(c0->x, 0);
	ASSERT_EQ(c0->y, 1);

	c0->x = 2;

	ASSERT_EQ(c0->x, 2);
	ASSERT_EQ(c0->y, 1);

	ASSERT_EQ(c1->x, 0);
	ASSERT_EQ(c1->y, 1);
}

TEST(Test_Core_Container, Simple_Moving) {
	Container<Simple> c0 = new Simple(0, 1);

	ASSERT_TRUE(c0);

	ASSERT_EQ(c0->x, 0);
	ASSERT_EQ(c0->y, 1);

	Container<Simple> c1 = std::move(c0);

	ASSERT_FALSE(c0);

	ASSERT_EQ(c1->x, 0);
	ASSERT_EQ(c1->y, 1);

	c1->x = 2;

	ASSERT_EQ(c1->x, 2);
	ASSERT_EQ(c1->y, 1);
}
