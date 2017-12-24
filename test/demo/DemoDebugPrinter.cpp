#include <iostream>

#include <whiskey/Whiskey.hpp>

using namespace whiskey;

int main() {
	DebugPrinter dp;

	dp.print(std::cout, new TypeAtomic(AST::ID::TypeAtomicBool));
	std::cout << "\n\n";

	dp.print(std::cout, new TypeAtomic(AST::ID::TypeAtomicInt8));
	std::cout << "\n\n";

	dp.print(std::cout, new TypeAtomic(AST::ID::TypeAtomicInt16));
	std::cout << "\n\n";

	dp.print(std::cout, new TypeAtomic(AST::ID::TypeAtomicInt32));
	std::cout << "\n\n";

	dp.print(std::cout, new TypeAtomic(AST::ID::TypeAtomicInt64));
	std::cout << "\n\n";

	dp.print(std::cout, new TypeAtomic(AST::ID::TypeAtomicUInt8));
	std::cout << "\n\n";

	dp.print(std::cout, new TypeAtomic(AST::ID::TypeAtomicUInt16));
	std::cout << "\n\n";

	dp.print(std::cout, new TypeAtomic(AST::ID::TypeAtomicUInt32));
	std::cout << "\n\n";

	dp.print(std::cout, new TypeAtomic(AST::ID::TypeAtomicUInt64));
	std::cout << "\n\n";

	dp.print(std::cout, new TypeAtomic(AST::ID::TypeAtomicFloat32));
	std::cout << "\n\n";

	dp.print(std::cout, new TypeAtomic(AST::ID::TypeAtomicFloat64));
	std::cout << "\n\n";

	dp.print(std::cout, new TypeAtomic(AST::ID::TypeAtomicReal));
	std::cout << "\n\n";

	dp.print(std::cout, new TypeSymbol("x", {
		new TypeAtomic(AST::ID::TypeAtomicInt32),
		new ExprSymbol("x")
	}));
	std::cout << "\n\n";

	dp.print(std::cout, new TypeUnary(AST::ID::TypeAccessUnary,
		new TypeSymbol("x")
	));
	std::cout << "\n\n";

	dp.print(std::cout, new TypeFunction(
		new TypeAtomic(AST::ID::TypeAtomicInt32),
		{
			new TypeAtomic(AST::ID::TypeAtomicInt32),
			new TypeAtomic(AST::ID::TypeAtomicInt32)
		}
	));
	std::cout << "\n\n";

	dp.print(std::cout, new ExprLiteralInt(
		new TypeAtomic(AST::ID::TypeAtomicInt32),
		5
	));
	std::cout << "\n\n";

	dp.print(std::cout, new ExprLiteralFloat(
		new TypeAtomic(AST::ID::TypeAtomicFloat64),
		3.14
	));
	std::cout << "\n\n";

	dp.print(std::cout, new ExprSymbol("x", {
		new TypeAtomic(AST::ID::TypeAtomicInt32),
		new ExprSymbol("x")
	}));
	std::cout << "\n\n";

	dp.print(std::cout, new ExprCall(
		new ExprSymbol("f"),
		{
			new ExprSymbol("x"),
			new ExprSymbol("y")
		}
	));
	std::cout << "\n\n";

	dp.print(std::cout, new ExprUnary(AST::ID::ExprBoolNot,
		new ExprSymbol("x")
	));
	std::cout << "\n\n";

	dp.print(std::cout, new ExprBinary(AST::ID::ExprBoolAnd,
		new ExprSymbol("x"),
		new ExprSymbol("y")
	));
	std::cout << "\n\n";

	dp.print(std::cout, new ExprUnary(AST::ID::ExprGroup,
		new ExprSymbol("x")
	));
	std::cout << "\n\n";

	dp.print(std::cout, new StmtEmpty());
	std::cout << "\n\n";

	dp.print(std::cout, new StmtExpr(AST::ID::StmtExpr, new ExprSymbol("x")));
	std::cout << "\n\n";

	dp.print(std::cout, new StmtExpr(AST::ID::StmtReturn, new ExprSymbol("x")));
	std::cout << "\n\n";

	dp.print(std::cout, new StmtIf(
		new ExprSymbol("x"),
		new StmtEmpty()
	));
	std::cout << "\n\n";

	dp.print(std::cout, new StmtIf(
		new ExprSymbol("x"),
		new StmtEmpty(),
		new StmtEmpty()
	));
	std::cout << "\n\n";

	dp.print(std::cout, new StmtWhile(
		new ExprSymbol("x")
	));
	std::cout << "\n\n";

	dp.print(std::cout, new StmtWhile(
		new ExprSymbol("x"),
		new StmtEmpty()
	));
	std::cout << "\n\n";

	dp.print(std::cout, new StmtFor());
	std::cout << "\n\n";

	dp.print(std::cout, new StmtFor({
		new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt32), "x"),
		new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt32), "y")
	},
	new ExprSymbol("x"),
	{
		new ExprSymbol("x"),
		new ExprSymbol("y")
	},
	new StmtEmpty()));
	std::cout << "\n\n";

	dp.print(std::cout, new StmtForEach(
		new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt32), "x"),
		new ExprSymbol("y")
	));
	std::cout << "\n\n";

	dp.print(std::cout, new StmtForEach(
		new DeclVariable(new TypeAtomic(AST::ID::TypeAtomicInt32), "x"),
		new ExprSymbol("y"),
		new StmtEmpty()
	));
	std::cout << "\n\n";

	dp.print(std::cout, new StmtBlock());
	std::cout << "\n\n";

	dp.print(std::cout, new StmtBlock({
		new StmtEmpty(),
		new StmtEmpty()
	}));
	std::cout << "\n\n";

	dp.print(std::cout, new DeclVariable(
		new TypeAtomic(AST::ID::TypeAtomicInt32),
		"x"
	));
	std::cout << "\n\n";

	DeclVariable *dv0 = new DeclVariable(
		new TypeAtomic(AST::ID::TypeAtomicInt32),
		"x",
		new ExprSymbol("y")
	);
	dv0->getTemplateDeclArgs().push_back(
		new DeclVariable(
			new TypeAtomic(AST::ID::TypeAtomicInt32),
			"z"
		)
	);
	dv0->getTemplateDeclArgs().push_back(
		new DeclVariable(
			new TypeAtomic(AST::ID::TypeAtomicInt32),
			"w"
		)
	);
	dp.print(std::cout, dv0);
	std::cout << "\n\n";

	dp.print(std::cout, new DeclFunction(
		new TypeAtomic(AST::ID::TypeAtomicInt32),
		"f"
	));
	std::cout << "\n\n";

	DeclFunction *df0 = new DeclFunction(
		new TypeAtomic(AST::ID::TypeAtomicInt32),
		"f",
		{
			new DeclVariable(
				new TypeAtomic(AST::ID::TypeAtomicInt32),
				"x"
			),
			new DeclVariable(
				new TypeAtomic(AST::ID::TypeAtomicInt32),
				"y"
			)
		},
		new StmtEmpty()
	);
	df0->getTemplateDeclArgs().push_back(
		new DeclVariable(
			new TypeAtomic(AST::ID::TypeAtomicInt32),
			"z"
		)
	);
	df0->getTemplateDeclArgs().push_back(
		new DeclVariable(
			new TypeAtomic(AST::ID::TypeAtomicInt32),
			"w"
		)
	);
	dp.print(std::cout, df0);
	std::cout << "\n\n";

	dp.print(std::cout, new DeclClass(
		"a"
	));
	std::cout << "\n\n";

	DeclClass *dc0 = new DeclClass(
		"a",
		{
			new TypeAtomic(AST::ID::TypeAtomicInt32),
			new TypeAtomic(AST::ID::TypeAtomicInt64)
		},
		{
			new DeclVariable(
				new TypeAtomic(AST::ID::TypeAtomicInt32),
				"x"
			),
			new DeclVariable(
				new TypeAtomic(AST::ID::TypeAtomicInt32),
				"y"
			)
		}
	);
	dc0->getTemplateDeclArgs().push_back(
		new DeclVariable(
			new TypeAtomic(AST::ID::TypeAtomicInt32),
			"z"
		)
	);
	dc0->getTemplateDeclArgs().push_back(
		new DeclVariable(
			new TypeAtomic(AST::ID::TypeAtomicInt32),
			"w"
		)
	);
	dp.print(std::cout, dc0);
	std::cout << "\n\n";

	dp.print(std::cout, new DeclNamespace(
		"a"
	));
	std::cout << "\n\n";

	DeclNamespace *dn0 = new DeclNamespace(
		"a",
		{
			new DeclVariable(
				new TypeAtomic(AST::ID::TypeAtomicInt32),
				"x"
			),
			new DeclVariable(
				new TypeAtomic(AST::ID::TypeAtomicInt32),
				"y"
			)
		}
	);
	dn0->getTemplateDeclArgs().push_back(
		new DeclVariable(
			new TypeAtomic(AST::ID::TypeAtomicInt32),
			"z"
		)
	);
	dn0->getTemplateDeclArgs().push_back(
		new DeclVariable(
			new TypeAtomic(AST::ID::TypeAtomicInt32),
			"w"
		)
	);
	dp.print(std::cout, dn0);
	std::cout << "\n\n";

	dp.print(std::cout, new Import(
		"M"
	));
	std::cout << "\n\n";

	return 0;
}
