#include <gtest/gtest.h>

#include <whiskey/Whiskey.hpp>

using namespace whiskey;

template<class T> void testHelper(std::initializer_list<T *> nodes) {
	for (typename std::initializer_list<T *>::iterator iterA = nodes.begin(); iterA != nodes.end(); ++iterA) {
		T *astA0 = *iterA;
		T *astA1 = astA0->template cloneAs<T>();

		ASSERT_TRUE(astA0->compare(*astA0));
		ASSERT_TRUE(astA0->compare(*astA1));
		ASSERT_TRUE(astA1->compare(*astA0));
		ASSERT_TRUE(astA1->compare(*astA1));

		for (typename std::initializer_list<T *>::iterator iterB = nodes.begin(); iterB != iterA; ++iterB) {
			T *astB0 = *iterB;
			T *astB1 = astB0->template cloneAs<T>();

			ASSERT_FALSE(astA0->compare(*astB0));
			ASSERT_FALSE(astA0->compare(*astB1));
			ASSERT_FALSE(astA1->compare(*astB0));
			ASSERT_FALSE(astA1->compare(*astB1));

			delete astB1;
		}

		delete astA1;
	}
}

TEST(Test_AST_CloneCompare, TypeAtomic) {
	testHelper({
		new TypeAtomic(AST::ID::TypeAtomicBool),
		new TypeAtomic(AST::ID::TypeAtomicInt8)
	});
}

TEST(Test_AST_CloneCompare, TypeSymbol) {
	testHelper({
		new TypeSymbol("x"),
		new TypeSymbol("y")
	});
}

TEST(Test_AST_CloneCompare, TypeUnary) {
	testHelper({
		new TypeUnary(AST::ID::TypeAccessUnary, new TypeAtomic(AST::ID::TypeAtomicBool)),
		new TypeUnary(AST::ID::TypeAccessBinary, new TypeAtomic(AST::ID::TypeAtomicBool)),
		new TypeUnary(AST::ID::TypeAccessUnary, new TypeAtomic(AST::ID::TypeAtomicInt8)),
		new TypeUnary(AST::ID::TypeAccessBinary, new TypeAtomic(AST::ID::TypeAtomicInt8))
	});
}

TEST(Test_AST_CloneCompare, TypeBinary) {
	testHelper({
		new TypeBinary(AST::ID::TypeAccessUnary, new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicBool)),
		new TypeBinary(AST::ID::TypeAccessBinary, new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicBool)),
		new TypeBinary(AST::ID::TypeAccessUnary, new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicBool)),
		new TypeBinary(AST::ID::TypeAccessBinary, new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicBool)),
		new TypeBinary(AST::ID::TypeAccessUnary, new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicInt8)),
		new TypeBinary(AST::ID::TypeAccessBinary, new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicInt8)),
		new TypeBinary(AST::ID::TypeAccessUnary, new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicInt8)),
		new TypeBinary(AST::ID::TypeAccessBinary, new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicInt8))
	});
}

TEST(Test_AST_CloneCompare, TypeFunction) {
	testHelper({
		new TypeFunction(new TypeAtomic(AST::ID::TypeAtomicBool)),
		new TypeFunction(new TypeAtomic(AST::ID::TypeAtomicInt8)),
		new TypeFunction(new TypeAtomic(AST::ID::TypeAtomicBool), {new TypeAtomic(AST::ID::TypeAtomicBool)}),
		new TypeFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), {new TypeAtomic(AST::ID::TypeAtomicBool)}),
		new TypeFunction(new TypeAtomic(AST::ID::TypeAtomicBool), {new TypeAtomic(AST::ID::TypeAtomicInt8)}),
		new TypeFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), {new TypeAtomic(AST::ID::TypeAtomicInt8)}),
		new TypeFunction(new TypeAtomic(AST::ID::TypeAtomicBool), {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicBool)}),
		new TypeFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicBool)}),
		new TypeFunction(new TypeAtomic(AST::ID::TypeAtomicBool), {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicBool)}),
		new TypeFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicBool)}),
		new TypeFunction(new TypeAtomic(AST::ID::TypeAtomicBool), {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicInt8)}),
		new TypeFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicInt8)}),
		new TypeFunction(new TypeAtomic(AST::ID::TypeAtomicBool), {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicInt8)}),
		new TypeFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicInt8)})
	});
}

TEST(Test_AST_CloneCompare, ExprLiteralInt) {
	testHelper({
		new ExprLiteralInt(new TypeAtomic(AST::ID::TypeAtomicBool), 0),
		new ExprLiteralInt(new TypeAtomic(AST::ID::TypeAtomicInt8), 0),
		new ExprLiteralInt(new TypeAtomic(AST::ID::TypeAtomicBool), 1),
		new ExprLiteralInt(new TypeAtomic(AST::ID::TypeAtomicInt8), 1)
	});
}

TEST(Test_AST_CloneCompare, ExprLiteralFloat) {
	testHelper({
		new ExprLiteralFloat(new TypeAtomic(AST::ID::TypeAtomicBool), 0),
		new ExprLiteralFloat(new TypeAtomic(AST::ID::TypeAtomicInt8), 0),
		new ExprLiteralFloat(new TypeAtomic(AST::ID::TypeAtomicBool), 1),
		new ExprLiteralFloat(new TypeAtomic(AST::ID::TypeAtomicInt8), 1)
	});
}

TEST(Test_AST_CloneCompare, ExprSymbol) {
	testHelper({
		new ExprSymbol("x"),
		new ExprSymbol("y")
	});
}



TEST(Test_AST_CloneCompare, ExprUnary) {
	testHelper({
		new ExprUnary(AST::ID::TypeAccessUnary, new ExprSymbol("x")),
		new ExprUnary(AST::ID::TypeAccessBinary, new ExprSymbol("x")),
		new ExprUnary(AST::ID::TypeAccessUnary, new ExprSymbol("y")),
		new ExprUnary(AST::ID::TypeAccessBinary, new ExprSymbol("y"))
	});
}

TEST(Test_AST_CloneCompare, ExprBinary) {
	testHelper({
		new ExprBinary(AST::ID::TypeAccessUnary, new ExprSymbol("x"), new ExprSymbol("x")),
		new ExprBinary(AST::ID::TypeAccessBinary, new ExprSymbol("x"), new ExprSymbol("x")),
		new ExprBinary(AST::ID::TypeAccessUnary, new ExprSymbol("y"), new ExprSymbol("x")),
		new ExprBinary(AST::ID::TypeAccessBinary, new ExprSymbol("y"), new ExprSymbol("x")),
		new ExprBinary(AST::ID::TypeAccessUnary, new ExprSymbol("x"), new ExprSymbol("y")),
		new ExprBinary(AST::ID::TypeAccessBinary, new ExprSymbol("x"), new ExprSymbol("y")),
		new ExprBinary(AST::ID::TypeAccessUnary, new ExprSymbol("y"), new ExprSymbol("y")),
		new ExprBinary(AST::ID::TypeAccessBinary, new ExprSymbol("y"), new ExprSymbol("y"))
	});
}

TEST(Test_AST_CloneCompare, ExprCall) {
	testHelper({
		new ExprCall(new ExprSymbol("x")),
		new ExprCall(new ExprSymbol("y")),
		new ExprCall(new ExprSymbol("x"), {new ExprSymbol("x")}),
		new ExprCall(new ExprSymbol("y"), {new ExprSymbol("x")}),
		new ExprCall(new ExprSymbol("x"), {new ExprSymbol("y")}),
		new ExprCall(new ExprSymbol("y"), {new ExprSymbol("y")}),
		new ExprCall(new ExprSymbol("x"), {new ExprSymbol("x"), new ExprSymbol("x")}),
		new ExprCall(new ExprSymbol("y"), {new ExprSymbol("x"), new ExprSymbol("x")}),
		new ExprCall(new ExprSymbol("x"), {new ExprSymbol("y"), new ExprSymbol("x")}),
		new ExprCall(new ExprSymbol("y"), {new ExprSymbol("y"), new ExprSymbol("x")}),
		new ExprCall(new ExprSymbol("x"), {new ExprSymbol("x"), new ExprSymbol("y")}),
		new ExprCall(new ExprSymbol("y"), {new ExprSymbol("x"), new ExprSymbol("y")}),
		new ExprCall(new ExprSymbol("x"), {new ExprSymbol("y"), new ExprSymbol("y")}),
		new ExprCall(new ExprSymbol("y"), {new ExprSymbol("y"), new ExprSymbol("y")})
	});
}

TEST(Test_AST_CloneCompare, StmtEmpty) {
	testHelper({
		new StmtEmpty()
	});
}

TEST(Test_AST_CloneCompare, StmtExpr) {
	testHelper({
		new StmtExpr(AST::ID::StmtExpr),
		new StmtExpr(AST::ID::StmtReturn),
		new StmtExpr(AST::ID::StmtExpr, new ExprSymbol("x")),
		new StmtExpr(AST::ID::StmtReturn, new ExprSymbol("x")),
		new StmtExpr(AST::ID::StmtExpr, new ExprSymbol("y")),
		new StmtExpr(AST::ID::StmtReturn, new ExprSymbol("y"))
	});
}

TEST(Test_AST_CloneCompare, StmtIf) {
	testHelper({
		new StmtIf(new ExprSymbol("x"), new StmtExpr(AST::ID::StmtExpr)),
		new StmtIf(new ExprSymbol("y"), new StmtExpr(AST::ID::StmtExpr)),
		new StmtIf(new ExprSymbol("x"), new StmtExpr(AST::ID::StmtReturn)),
		new StmtIf(new ExprSymbol("y"), new StmtExpr(AST::ID::StmtReturn)),
		new StmtIf(new ExprSymbol("x"), new StmtExpr(AST::ID::StmtExpr), new StmtExpr(AST::ID::StmtExpr)),
		new StmtIf(new ExprSymbol("y"), new StmtExpr(AST::ID::StmtExpr), new StmtExpr(AST::ID::StmtExpr)),
		new StmtIf(new ExprSymbol("x"), new StmtExpr(AST::ID::StmtReturn), new StmtExpr(AST::ID::StmtExpr)),
		new StmtIf(new ExprSymbol("y"), new StmtExpr(AST::ID::StmtReturn), new StmtExpr(AST::ID::StmtExpr)),
		new StmtIf(new ExprSymbol("x"), new StmtExpr(AST::ID::StmtExpr), new StmtExpr(AST::ID::StmtReturn)),
		new StmtIf(new ExprSymbol("y"), new StmtExpr(AST::ID::StmtExpr), new StmtExpr(AST::ID::StmtReturn)),
		new StmtIf(new ExprSymbol("x"), new StmtExpr(AST::ID::StmtReturn), new StmtExpr(AST::ID::StmtReturn)),
		new StmtIf(new ExprSymbol("y"), new StmtExpr(AST::ID::StmtReturn), new StmtExpr(AST::ID::StmtReturn))
	});
}

TEST(Test_AST_CloneCompare, StmtWhile) {
	testHelper({
		new StmtWhile(new ExprSymbol("x"), new StmtExpr(AST::ID::StmtExpr)),
		new StmtWhile(new ExprSymbol("y"), new StmtExpr(AST::ID::StmtExpr)),
		new StmtWhile(new ExprSymbol("x"), new StmtExpr(AST::ID::StmtReturn)),
		new StmtWhile(new ExprSymbol("y"), new StmtExpr(AST::ID::StmtReturn))
	});
}

TEST(Test_AST_CloneCompare, DeclVariable) {
	testHelper({
		new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"),
		new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"),
		new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"),
		new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"),
		new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x", new ExprSymbol("x")),
		new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x", new ExprSymbol("x")),
		new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y", new ExprSymbol("x")),
		new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y", new ExprSymbol("x")),
		new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x", new ExprSymbol("y")),
		new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x", new ExprSymbol("y")),
		new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y", new ExprSymbol("y")),
		new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y", new ExprSymbol("y"))
	});
}

TEST(Test_AST_CloneCompare, StmtFor) {
	testHelper({
		new StmtFor(),
		new StmtFor({}, new ExprSymbol("x"), {}),
		new StmtFor({}, new ExprSymbol("y"), {}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {}),
		new StmtFor({}, new ExprSymbol("x"), {new ExprSymbol("x")}),
		new StmtFor({}, new ExprSymbol("y"), {new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {new ExprSymbol("x")}),
		new StmtFor({}, new ExprSymbol("x"), {new ExprSymbol("y")}),
		new StmtFor({}, new ExprSymbol("y"), {new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {new ExprSymbol("y")}),
		new StmtFor({}, new ExprSymbol("x"), {new ExprSymbol("x"), new ExprSymbol("x")}),
		new StmtFor({}, new ExprSymbol("y"), {new ExprSymbol("x"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {new ExprSymbol("x"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {new ExprSymbol("x"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {new ExprSymbol("x"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {new ExprSymbol("x"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {new ExprSymbol("x"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {new ExprSymbol("x"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {new ExprSymbol("x"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {new ExprSymbol("x"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {new ExprSymbol("x"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {new ExprSymbol("x"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {new ExprSymbol("x"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {new ExprSymbol("x"), new ExprSymbol("x")}),
		new StmtFor({}, new ExprSymbol("x"), {new ExprSymbol("y"), new ExprSymbol("x")}),
		new StmtFor({}, new ExprSymbol("y"), {new ExprSymbol("y"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {new ExprSymbol("y"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {new ExprSymbol("y"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {new ExprSymbol("y"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {new ExprSymbol("y"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {new ExprSymbol("y"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {new ExprSymbol("y"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {new ExprSymbol("y"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {new ExprSymbol("y"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {new ExprSymbol("y"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {new ExprSymbol("y"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {new ExprSymbol("y"), new ExprSymbol("x")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {new ExprSymbol("y"), new ExprSymbol("x")}),
		new StmtFor({}, new ExprSymbol("x"), {new ExprSymbol("x"), new ExprSymbol("y")}),
		new StmtFor({}, new ExprSymbol("y"), {new ExprSymbol("x"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {new ExprSymbol("x"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {new ExprSymbol("x"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {new ExprSymbol("x"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {new ExprSymbol("x"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {new ExprSymbol("x"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {new ExprSymbol("x"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {new ExprSymbol("x"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {new ExprSymbol("x"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {new ExprSymbol("x"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {new ExprSymbol("x"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {new ExprSymbol("x"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {new ExprSymbol("x"), new ExprSymbol("y")}),
		new StmtFor({}, new ExprSymbol("x"), {new ExprSymbol("y"), new ExprSymbol("y")}),
		new StmtFor({}, new ExprSymbol("y"), {new ExprSymbol("y"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {new ExprSymbol("y"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {new ExprSymbol("y"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {new ExprSymbol("y"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {new ExprSymbol("y"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {new ExprSymbol("y"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {new ExprSymbol("y"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("x"), {new ExprSymbol("y"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new ExprSymbol("y"), {new ExprSymbol("y"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {new ExprSymbol("y"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {new ExprSymbol("y"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("x"), {new ExprSymbol("y"), new ExprSymbol("y")}),
		new StmtFor({new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new ExprSymbol("y"), {new ExprSymbol("y"), new ExprSymbol("y")})
	});
}

TEST(Test_AST_CloneCompare, StmtForEach) {
	testHelper({
		new StmtForEach(new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new ExprSymbol("x"), new StmtExpr(AST::ID::StmtExpr)),
		new StmtForEach(new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new ExprSymbol("x"), new StmtExpr(AST::ID::StmtExpr)),
		new StmtForEach(new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new ExprSymbol("y"), new StmtExpr(AST::ID::StmtExpr)),
		new StmtForEach(new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new ExprSymbol("y"), new StmtExpr(AST::ID::StmtExpr)),
		new StmtForEach(new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new ExprSymbol("x"), new StmtExpr(AST::ID::StmtReturn)),
		new StmtForEach(new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new ExprSymbol("x"), new StmtExpr(AST::ID::StmtReturn)),
		new StmtForEach(new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new ExprSymbol("y"), new StmtExpr(AST::ID::StmtReturn)),
		new StmtForEach(new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new ExprSymbol("y"), new StmtExpr(AST::ID::StmtReturn))
	});
}

TEST(Test_AST_CloneCompare, StmtBlock) {
	testHelper({
		new StmtBlock(),
		new StmtBlock({new StmtExpr(AST::ID::StmtExpr)}),
		new StmtBlock({new StmtExpr(AST::ID::StmtReturn)}),
		new StmtBlock({new StmtExpr(AST::ID::StmtExpr), new StmtExpr(AST::ID::StmtExpr)}),
		new StmtBlock({new StmtExpr(AST::ID::StmtReturn), new StmtExpr(AST::ID::StmtExpr)}),
		new StmtBlock({new StmtExpr(AST::ID::StmtExpr), new StmtExpr(AST::ID::StmtReturn)}),
		new StmtBlock({new StmtExpr(AST::ID::StmtReturn), new StmtExpr(AST::ID::StmtReturn)})
	});
}

TEST(Test_AST_CloneCompare, DeclFunction) {
	testHelper({
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "x", {}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "x", {}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "y", {}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "y", {}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtExpr)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "x", {}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "x", {}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "y", {}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "y", {}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicBool), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtReturn)),
		new DeclFunction(new TypeAtomic(AST::ID::TypeAtomicInt8), "y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}, new StmtExpr(AST::ID::StmtReturn))
	});
}

TEST(Test_AST_CloneCompare, DeclClass) {
	testHelper({
		new DeclClass("x", {}, {}),
		new DeclClass("y", {}, {}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool)}, {}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool)}, {}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8)}, {}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8)}, {}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicBool)}, {}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicBool)}, {}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicBool)}, {}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicBool)}, {}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {}),
		new DeclClass("x", {}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("x", {}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x")}),
		new DeclClass("x", {}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("x", {}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicBool)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicBool), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("x", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")}),
		new DeclClass("y", {new TypeAtomic(AST::ID::TypeAtomicInt8), new TypeAtomic(AST::ID::TypeAtomicInt8)}, {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt8), "y")})
	});
}

TEST(Test_AST_CloneCompare, DeclNamespace) {
	testHelper({
		new DeclNamespace("x"),
		new DeclNamespace("y"),
		new DeclNamespace("x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}),
		new DeclNamespace("y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}),
		new DeclNamespace("x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}),
		new DeclNamespace("y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}),
		new DeclNamespace("x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}),
		new DeclNamespace("y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}),
		new DeclNamespace("x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}),
		new DeclNamespace("y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x")}),
		new DeclNamespace("x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}),
		new DeclNamespace("y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "x"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}),
		new DeclNamespace("x", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")}),
		new DeclNamespace("y", {new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y"), new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicBool), "y")})
	});
}

TEST(Test_AST_CloneCompare, Import) {
	testHelper({
		new Import("x"),
		new Import("y")
	});
}
