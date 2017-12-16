#include <gtest/gtest.h>

#include <whiskey/Whiskey.hpp>

using namespace whiskey;

TEST(Test_Core_Assert, All) {
	ASSERT_DEATH({
		W_ASSERT_UNREACHABLE("Hey, now.");
	}, "Hey, now.");

	W_ASSERT_TRUE(true, "");

	ASSERT_DEATH({
		W_ASSERT_TRUE(false, "You're an all star.");
	}, "You're an all star.");

	W_ASSERT_FALSE(false, "");

	ASSERT_DEATH({
		W_ASSERT_FALSE(true, "Get your game on,");
	}, "Get your game on,");

	W_ASSERT_NULL(nullptr, "");

	int x;

	ASSERT_DEATH({
		W_ASSERT_NULL(&x, "Go play!");
	}, "Go play!");

	W_ASSERT_NONNULL(&x, "");

	ASSERT_DEATH({
		W_ASSERT_NONNULL(nullptr, "Hey, now.");
	}, "Hey, now.");

	W_ASSERT_LT(0, 1, "");

	W_ASSERT_LT(-1, 1, "");

	W_ASSERT_LT(-1, 0, "");

	ASSERT_DEATH({
		W_ASSERT_LT(0, 0, "You're a rock star.");
	}, "You're a rock star.");

	ASSERT_DEATH({
		W_ASSERT_LT(1, 0, "Get your game on,");
	}, "Get your game on,");

	ASSERT_DEATH({
		W_ASSERT_LT(1, -1, "Go play!");
	}, "Go play!");

	W_ASSERT_LE(0, 1, "");

	W_ASSERT_LE(-1, 1, "");

	W_ASSERT_LE(-1, 0, "");

	W_ASSERT_LE(0, 0, "");

	ASSERT_DEATH({
		W_ASSERT_LE(1, 0, "It's a cool place,");
	}, "It's a cool place,");

	ASSERT_DEATH({
		W_ASSERT_LE(1, -1, "And they say it gets colder.");
	}, "And they say it gets colder.");

	W_ASSERT_GT(1, 0, "");

	W_ASSERT_GT(1, -1, "");

	W_ASSERT_GT(0, -1, "");

	ASSERT_DEATH({
		W_ASSERT_GT(0, 0, "Bundled up now,");
	}, "Bundled up now,");

	ASSERT_DEATH({
		W_ASSERT_GT(0, 1, "Wait till you get older.");
	}, "Wait till you get older.");

	ASSERT_DEATH({
		W_ASSERT_GT(-1, 1, "It's the medium back the big dipper,");
	}, "It's the medium back the big dipper,");

	W_ASSERT_GE(1, 0, "");

	W_ASSERT_GE(1, -1, "");

	W_ASSERT_GE(0, -1, "");

	W_ASSERT_GE(0, 0, "");

	ASSERT_DEATH({
		W_ASSERT_GE(0, 1, "Wonder why it's not the bad the big flipper.");
	}, "Wonder why it's not the bad the big flipper.");

	ASSERT_DEATH({
		W_ASSERT_GE(-1, 1, "The ice we skate");
	}, "The ice we skate");

















	W_ASSERT_ULT(0, 1, "");

	ASSERT_DEATH({
		W_ASSERT_ULT(0, 0, "Is getting pretty thin.");
	}, "Is getting pretty thin.");

	ASSERT_DEATH({
		W_ASSERT_ULT(1, 0, "Waters gettin' warm,");
	}, "Waters gettin' warm,");

	W_ASSERT_ULE(0, 1, "");

	W_ASSERT_ULE(0, 0, "");

	ASSERT_DEATH({
		W_ASSERT_ULE(1, 0, "Yeah, we might as well swim.");
	}, "Yeah, we might as well swim.");

	W_ASSERT_UGT(1, 0, "");

	ASSERT_DEATH({
		W_ASSERT_UGT(0, 0, "World's on fire,");
	}, "World's on fire,");

	ASSERT_DEATH({
		W_ASSERT_UGT(0, 1, "How 'bout jaws.");
	}, "How 'bout jaws.");

	W_ASSERT_UGE(1, 0, "");

	W_ASSERT_UGE(0, 0, "");

	ASSERT_DEATH({
		W_ASSERT_UGE(0, 1, "That's the way I like it");
	}, "That's the way I like it");

	W_ASSERT_NE(0, 1, "");

	W_ASSERT_NE(0, -1, "");

	W_ASSERT_NE(-1, 1, "");

	ASSERT_DEATH({
		W_ASSERT_NE(0, 0, "And I never get bored.");
	}, "And I never get bored.");

	W_ASSERT_EQ(0, 0, "");

	ASSERT_DEATH({
		W_ASSERT_EQ(0, 1, "Do the chorus again lol xD");
	}, "Do the chorus again lol xD");

	ASSERT_DEATH({
		W_ASSERT_EQ(0, -1, "Do the chorus again lol xD");
	}, "Do the chorus again lol xD");

	ASSERT_DEATH({
		W_ASSERT_EQ(1, -1, "Do the chorus again lol xD");
	}, "Do the chorus again lol xD");
}
