#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <whiskey/Core/Color.hpp>
#include <whiskey/Source/Source.hpp>
#include <whiskey/Source/Token.hpp>
#include <whiskey/Messages/Message.hpp>
#include <whiskey/Messages/MessageContext.hpp>

using namespace whiskey;

TEST(Unit_Messages_MessageContext, PrintFirstLine) {
	Color::enabled = false;

	std::stringstream sourceStream("\nhello, world.\ngoodbye, world.\n\nhello, new world.\n");
	Source source(sourceStream);

	MessageContext ctx;

	ctx.emit(Token(1, 1, 1, TokenID::None), Message::Error);

	std::stringstream msgStream;
	ctx.print(msgStream, source);

	std::string output = msgStream.str();

	ASSERT_TRUE(output.find("hello, world.") == std::string::npos);
	ASSERT_TRUE(output.find("goodbye, world.") == std::string::npos);
	ASSERT_TRUE(output.find("hello, new world.") == std::string::npos);
}

TEST(Unit_Messages_MessageContext, PrintSecondLine_Begin) {
	Color::enabled = false;

	std::stringstream sourceStream("\nhello, world.\ngoodbye, world.\n\nhello, new world.\n");
	Source source(sourceStream);

	MessageContext ctx;

	ctx.emit(Token(2, 1, 1, TokenID::None), Message::Error);

	std::stringstream msgStream;
	ctx.print(msgStream, source);

	std::string output = msgStream.str();

	ASSERT_FALSE(output.find("hello, world.") == std::string::npos);
	ASSERT_TRUE(output.find("goodbye, world.") == std::string::npos);
	ASSERT_TRUE(output.find("hello, new world.") == std::string::npos);
}

TEST(Unit_Messages_MessageContext, PrintSecondLine_Middle) {
	Color::enabled = false;

	std::stringstream sourceStream("\nhello, world.\ngoodbye, world.\n\nhello, new world.\n");
	Source source(sourceStream);

	MessageContext ctx;

	ctx.emit(Token(2, 13, 1, TokenID::None), Message::Error);

	std::stringstream msgStream;
	ctx.print(msgStream, source);

	std::string output = msgStream.str();

	ASSERT_FALSE(output.find("hello, world.") == std::string::npos);
	ASSERT_TRUE(output.find("goodbye, world.") == std::string::npos);
	ASSERT_TRUE(output.find("hello, new world.") == std::string::npos);
}

TEST(Unit_Messages_MessageContext, PrintSecondLine_End) {
	Color::enabled = false;

	std::stringstream sourceStream("\nhello, world.\ngoodbye, world.\n\nhello, new world.\n");
	Source source(sourceStream);

	MessageContext ctx;

	ctx.emit(Token(2, 14, 1, TokenID::None), Message::Error);

	std::stringstream msgStream;
	ctx.print(msgStream, source);

	std::string output = msgStream.str();

	ASSERT_FALSE(output.find("hello, world.") == std::string::npos);
	ASSERT_TRUE(output.find("goodbye, world.") == std::string::npos);
	ASSERT_TRUE(output.find("hello, new world.") == std::string::npos);
}

TEST(Unit_Messages_MessageContext, PrintThirdLine_Begin) {
	Color::enabled = false;

	std::stringstream sourceStream("\nhello, world.\ngoodbye, world.\n\nhello, new world.\n");
	Source source(sourceStream);

	MessageContext ctx;

	ctx.emit(Token(3, 1, 1, TokenID::None), Message::Error);

	std::stringstream msgStream;
	ctx.print(msgStream, source);

	std::string output = msgStream.str();

	ASSERT_TRUE(output.find("hello, world.") == std::string::npos);
	ASSERT_FALSE(output.find("goodbye, world.") == std::string::npos);
	ASSERT_TRUE(output.find("hello, new world.") == std::string::npos);
}

TEST(Unit_Messages_MessageContext, PrintThirdLine_Middle) {
	Color::enabled = false;

	std::stringstream sourceStream("\nhello, world.\ngoodbye, world.\n\nhello, new world.\n");
	Source source(sourceStream);

	MessageContext ctx;

	ctx.emit(Token(3, 15, 1, TokenID::None), Message::Error);

	std::stringstream msgStream;
	ctx.print(msgStream, source);

	std::string output = msgStream.str();

	ASSERT_TRUE(output.find("hello, world.") == std::string::npos);
	ASSERT_FALSE(output.find("goodbye, world.") == std::string::npos);
	ASSERT_TRUE(output.find("hello, new world.") == std::string::npos);
}

TEST(Unit_Messages_MessageContext, PrintThirdLine_End) {
	Color::enabled = false;

	std::stringstream sourceStream("\nhello, world.\ngoodbye, world.\n\nhello, new world.\n");
	Source source(sourceStream);

	MessageContext ctx;

	ctx.emit(Token(3, 16, 1, TokenID::None), Message::Error);

	std::stringstream msgStream;
	ctx.print(msgStream, source);

	std::string output = msgStream.str();

	ASSERT_TRUE(output.find("hello, world.") == std::string::npos);
	ASSERT_FALSE(output.find("goodbye, world.") == std::string::npos);
	ASSERT_TRUE(output.find("hello, new world.") == std::string::npos);
}

TEST(Unit_Messages_MessageContext, PrintFourthLine) {
	Color::enabled = false;

	std::stringstream sourceStream("\nhello, world.\ngoodbye, world.\n\nhello, new world.\n");
	Source source(sourceStream);

	MessageContext ctx;

	ctx.emit(Token(4, 1, 1, TokenID::None), Message::Error);

	std::stringstream msgStream;
	ctx.print(msgStream, source);

	std::string output = msgStream.str();

	ASSERT_TRUE(output.find("hello, world.") == std::string::npos);
	ASSERT_TRUE(output.find("goodbye, world.") == std::string::npos);
	ASSERT_TRUE(output.find("hello, new world.") == std::string::npos);
}

TEST(Unit_Messages_MessageContext, PrintFifthLine_Begin) {
	Color::enabled = false;

	std::stringstream sourceStream("\nhello, world.\ngoodbye, world.\n\nhello, new world.\n");
	Source source(sourceStream);

	MessageContext ctx;

	ctx.emit(Token(5, 1, 1, TokenID::None), Message::Error);

	std::stringstream msgStream;
	ctx.print(msgStream, source);

	std::string output = msgStream.str();

	ASSERT_TRUE(output.find("hello, world.") == std::string::npos);
	ASSERT_TRUE(output.find("goodbye, world.") == std::string::npos);
	ASSERT_FALSE(output.find("hello, new world.") == std::string::npos);
}

TEST(Unit_Messages_MessageContext, PrintFifthLine_Middle) {
	Color::enabled = false;

	std::stringstream sourceStream("\nhello, world.\ngoodbye, world.\n\nhello, new world.\n");
	Source source(sourceStream);

	MessageContext ctx;

	ctx.emit(Token(5, 17, 1, TokenID::None), Message::Error);

	std::stringstream msgStream;
	ctx.print(msgStream, source);

	std::string output = msgStream.str();

	ASSERT_TRUE(output.find("hello, world.") == std::string::npos);
	ASSERT_TRUE(output.find("goodbye, world.") == std::string::npos);
	ASSERT_FALSE(output.find("hello, new world.") == std::string::npos);
}

TEST(Unit_Messages_MessageContext, PrintFifthLine_End) {
	Color::enabled = false;

	std::stringstream sourceStream("\nhello, world.\ngoodbye, world.\n\nhello, new world.\n");
	Source source(sourceStream);

	MessageContext ctx;

	ctx.emit(Token(5, 18, 1, TokenID::None), Message::Error);

	std::stringstream msgStream;
	ctx.print(msgStream, source);

	std::string output = msgStream.str();

	ASSERT_TRUE(output.find("hello, world.") == std::string::npos);
	ASSERT_TRUE(output.find("goodbye, world.") == std::string::npos);
	ASSERT_FALSE(output.find("hello, new world.") == std::string::npos);
}
