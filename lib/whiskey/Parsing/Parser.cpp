#include <whiskey/Parsing/Parser.hpp>

#include <sstream>

#include <whiskey/AST/Node.hpp>
#include <whiskey/Parsing/EvalLiterals.hpp>

namespace whiskey {
ParserResult Parser::parseBoundList(ParserContext &ctx,
                                    TokenID left,
                                    ParserContext::Rule rule,
                                    const std::string &expected,
                                    TokenID right) {
  ParserContext save = ctx;

  Token leftToken = ctx.getToken();
  if (leftToken.getID() == left) {
    ctx.eatToken();
  } else {
    ctx = save;
    return ParserResult();
  }

  Node *front = nullptr;
  Node *back = nullptr;

  bool endedCorrectly = false;

  while (ctx.areMoreTokens()) {
    Token rightToken = ctx.getToken();
    if (rightToken.getID() == right) {
      ctx.eatToken();
      endedCorrectly = true;
      break;
    }

    ParserResult arg = ctx.parse(rule);
    if (!arg.isGood()) {
      ctx.errorUnexpectedToken(expected);
      ctx = save;
      return ParserResult();
    }

    if (front == nullptr) {
      front = back = arg.getNode();
    } else {
      back->setNext(arg.getNode());
      back = arg.getNode();
    }
  }

  if (!endedCorrectly) {
    std::stringstream ss;
    ss << "closing ";
    printTokenID(ss, right);
    ctx.errorUnexpectedToken(ss.str());
    ctx = save;
    return ParserResult();
  }

  return ParserResult(front);
}

ParserResult Parser::parseBoundSeparatedList(ParserContext &ctx,
                                             TokenID left,
                                             ParserContext::Rule rule,
                                             const std::string &expected,
                                             TokenID sep,
                                             TokenID right) {
  ParserContext save = ctx;

  Token leftToken = ctx.getToken();
  if (leftToken.getID() == left) {
    ctx.eatToken();
  } else {
    ctx = save;
    return ParserResult();
  }

  Node *front = nullptr;
  Node *back = nullptr;

  bool endedCorrectly = false;

  while (ctx.areMoreTokens()) {
    Token rightToken = ctx.getToken();
    if (rightToken.getID() == right) {
      ctx.eatToken();
      endedCorrectly = true;
      break;
    } else if (rightToken.getID() == sep) {
      std::stringstream ss;
      printTokenID(ss, sep);
      ctx.errorUnexpectedToken(ss.str());
      ctx = save;
      return ParserResult();
    }

    ParserResult arg = ctx.parse(rule);
    if (!arg.isGood()) {
      ctx.errorUnexpectedToken(expected);
      ctx = save;
      return ParserResult();
    }

    if (front == nullptr) {
      front = back = arg.getNode();
    } else {
      back->setNext(arg.getNode());
      back = arg.getNode();
    }

    rightToken = ctx.getToken();
    if (rightToken.getID() == sep) {
      ctx.eatToken();

      rightToken = ctx.getToken();
      if (rightToken.getID() == right) {
        ctx.errorUnexpectedToken(expected);
        ctx = save;
        return ParserResult();
      }
    } else if (rightToken.getID() == right) {
      continue;
    } else {
      std::stringstream ss;
      printTokenID(ss, sep);
      ctx.errorUnexpectedToken(ss.str());
      ctx = save;
      return ParserResult();
    }
  }

  if (!endedCorrectly) {
    std::stringstream ss;
    ss << "closing ";
    printTokenID(ss, right);
    ctx.errorUnexpectedToken(ss.str());
    ctx = save;
    return ParserResult();
  }

  return ParserResult(front);
}

ParserResult Parser::parseTemplateList(ParserContext &ctx,
                                       ParserContext::Rule rule,
                                       const std::string &expected) {
  ParserContext save = ctx;

  Token leftToken = ctx.getToken();
  if (leftToken.getID() == TokenID::LT) {
    ctx.eatToken();
  } else {
    ctx = save;
    return ParserResult();
  }

  Node *front = nullptr;
  Node *back = nullptr;

  bool endedCorrectly = false;

  while (ctx.areMoreTokens()) {
    Token rightToken = ctx.getToken();
    if (rightToken.getID() == TokenID::GT) {
      ctx.eatToken();
      endedCorrectly = true;
      break;
    } else if (rightToken.getID() == TokenID::GE) {
      ctx.eatToken();
      ctx.injectToken(Token(TokenID::Assign));
      endedCorrectly = true;
      break;
    } else if (rightToken.getID() == TokenID::BitShR) {
      ctx.eatToken();
      ctx.injectToken(Token(TokenID::GT));
      endedCorrectly = true;
      break;
    } else if (rightToken.getID() == TokenID::BitShRAssign) {
      ctx.eatToken();
      ctx.injectToken(Token(TokenID::GE));
      endedCorrectly = true;
      break;
    } else if (rightToken.getID() == TokenID::Comma) {
      ctx.errorUnexpectedToken(",");
      ctx = save;
      return ParserResult();
    }

    ParserResult arg = ctx.parse(rule);
    if (!arg.isGood()) {
      ctx.errorUnexpectedToken(expected);
      ctx = save;
      return ParserResult();
    }

    if (front == nullptr) {
      front = back = arg.getNode();
    } else {
      back->setNext(arg.getNode());
      back = arg.getNode();
    }

    rightToken = ctx.getToken();
    if (rightToken.getID() == TokenID::Comma) {
      ctx.eatToken();
    } else if (rightToken.getID() == TokenID::GT ||
               rightToken.getID() == TokenID::GE ||
               rightToken.getID() == TokenID::BitShR ||
               rightToken.getID() == TokenID::BitShRAssign) {
      continue;
    } else {
      ctx.errorUnexpectedToken(",");
      ctx = save;
      return ParserResult();
    }
  }

  if (!endedCorrectly) {
    ctx.errorUnexpectedToken("closing >");
    ctx = save;
    return ParserResult();
  }

  return ParserResult(front);
}

ParserResult Parser::parseSymbol(ParserContext &ctx,
                                 ParserContext::Rule templateArgRule,
                                 std::function<Node *(Node *, Token)> builder) {
  ParserContext save = ctx;

  Token symbolToken = ctx.getToken();
  if (symbolToken.getID() == TokenID::Symbol) {
    ctx.eatToken();
  } else {
    ctx = save;
    return ParserResult();
  }

  Token tokenLT = ctx.getToken();
  if (tokenLT.getID() == TokenID::LT) {
    ParserResult templateArgs =
        parseTemplateList(ctx, templateArgRule, "template arg");
    if (templateArgs.isGood()) {
      return builder(templateArgs.getNode(), symbolToken);
    } else {
      ctx = save;
      return ParserResult();
    }
  } else {
    return ParserResult(builder(nullptr, symbolToken));
  }
}

ParserResult Parser::parseUnaryRight(
    ParserContext &ctx,
    ParserContext::Rule baseRule,
    const std::string &expected,
    std::initializer_list<
        std::pair<TokenID, std::function<Node *(Node *, Token)>>> builders) {
  ParserContext save = ctx;

  Token opToken = ctx.getToken();

  for (const std::pair<TokenID, std::function<Node *(Node *, Token)>> &kv :
       builders) {
    ctx = save;
    if (opToken.getID() == kv.first) {
      ctx.eatToken();

      ParserResult arg = parseUnaryRight(ctx, baseRule, expected, builders);
      if (arg.isGood()) {
        return ParserResult(kv.second(arg.getNode(), opToken));
      } else {
        ctx.errorUnexpectedToken(expected);
        ctx = save;
        return ParserResult();
      }
    }
  }

  ctx = save;
  return ctx.parse(baseRule);
}

ParserResult Parser::parseUnaryLeft(
    ParserContext &ctx,
    ParserContext::Rule baseRule,
    const std::string &expected,
    std::initializer_list<
        std::pair<TokenID, std::function<Node *(Node *, Token)>>> builders) {
  ParserContext save = ctx;

  ParserResult res = ctx.parse(baseRule);
  if (res.isGood()) {
    bool gotOp = false;

    while (ctx.areMoreTokens()) {
      save = ctx;
      for (const std::pair<TokenID, std::function<Node *(Node *, Token)>>
               &kv : builders) {
        ctx = save;
        Token opToken = ctx.getToken();
        if (opToken.getID() == kv.first) {
          res = ParserResult(kv.second(res.getNode(), opToken));
          ctx.eatToken();
          gotOp = true;
          break;
        }
      }

      if (!gotOp) {
        break;
      }
    }

    return res;
  } else {
    ctx.errorUnexpectedToken(expected);
    ctx = save;
    return ParserResult();
  }
}

ParserResult Parser::parseBinary(
    ParserContext &ctx,
    ParserContext::Rule lhsRule,
    const std::string &expected,
    std::initializer_list<
        std::pair<TokenID, std::function<Node *(Node *, Node *, Token)>>>
        builders) {
  ParserContext save = ctx;

  ParserResult lhs = ctx.parse(lhsRule);
  if (!lhs.isGood()) {
    return ParserResult();
  }

  for (const std::pair<TokenID, std::function<Node *(Node *, Node *, Token)>>
           &kv : builders) {
    Token opToken = ctx.getToken();
    if (opToken.getID() == kv.first) {
      ctx.eatToken();

      ParserResult rhs = ctx.parse([&](ParserContext &ctx) {
        return parseBinary(ctx, lhsRule, expected, builders);
      });
      if (!rhs.isGood()) {
        ctx.errorUnexpectedToken(expected);
        ctx = save;
        return ParserResult();
      }

      return ParserResult(
          kv.second(lhs.getNode(), rhs.getNode(), opToken));
    }
  }
  return lhs;
}

ParserResult
Parser::parseBoundTerm(ParserContext &ctx,
                       TokenID left,
                       ParserContext::Rule rule,
                       const std::string &expected,
                       TokenID right,
                       std::function<Node *(Node *, Token)> builder) {
  ParserContext save = ctx;

  Token leftToken = ctx.getToken();
  if (leftToken.getID() == left) {
    ctx.eatToken();
  } else {
    ctx = save;
    return ParserResult();
  }

  ParserResult rtn = ctx.parse(rule);
  if (!rtn.isGood()) {
    ctx.errorUnexpectedToken(expected);
    ctx = save;
    return ParserResult();
  }

  Token rightToken = ctx.getToken();
  if (rightToken.getID() == TokenID::RParen) {
    ctx.eatToken();
  } else {
    std::stringstream ss;
    ss << "closing ";
    printTokenID(ss, right);
    ctx.errorUnexpectedToken(ss.str());
    ctx = save;
    return ParserResult();
  }

  return ParserResult(builder(rtn.getNode(), leftToken));
}

ParserResult Parser::parseTemplateEvalArg(ParserContext &ctx) {
  return ctx.parseAny({parseType, parseExpr});
}

ParserResult Parser::parseTypeAtomic(ParserContext &ctx) {
  Token tokenSymbol = ctx.getToken();
  if (tokenSymbol.getID() == TokenID::KWBool) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicBool(tokenSymbol));
  } else if (tokenSymbol.getID() == TokenID::KWInt8) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicInt8(tokenSymbol));
  } else if (tokenSymbol.getID() == TokenID::KWInt16) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicInt16(tokenSymbol));
  } else if (tokenSymbol.getID() == TokenID::KWInt32) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicInt32(tokenSymbol));
  } else if (tokenSymbol.getID() == TokenID::KWInt64) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicInt64(tokenSymbol));
  } else if (tokenSymbol.getID() == TokenID::KWUInt8) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicUInt8(tokenSymbol));
  } else if (tokenSymbol.getID() == TokenID::KWUInt16) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicUInt16(tokenSymbol));
  } else if (tokenSymbol.getID() == TokenID::KWUInt32) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicUInt32(tokenSymbol));
  } else if (tokenSymbol.getID() == TokenID::KWUInt64) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicUInt64(tokenSymbol));
  } else if (tokenSymbol.getID() == TokenID::KWFloat32) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicFloat32(tokenSymbol));
  } else if (tokenSymbol.getID() == TokenID::KWFloat64) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicFloat64(tokenSymbol));
  } else if (tokenSymbol.getID() == TokenID::KWReal) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicReal(tokenSymbol));
  } else {
    return ParserResult();
  }
}

ParserResult Parser::parseTypeSymbol(ParserContext &ctx) {
  return parseSymbol(ctx, parseTemplateEvalArg, [](Node *args, Token range) {
    return Node::createTypeSymbol(
        Field::createString(range.getText()), {args}, range);
  });
}

ParserResult Parser::parseTypeTerm(ParserContext &ctx) {
  return ctx.parseAny({parseTypeSymbol, parseTypeAtomic, parseTypeGroup});
}

ParserResult Parser::parseTypeAccess(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseTypeTerm,
                     "type",
                     {{TokenID::Period, [](Node *lhs, Node *rhs, Token range) {
                         return Node::createTypeAccess({lhs, rhs}, range);
                       }}});
}

ParserResult Parser::parseTypeAccessUnary(ParserContext &ctx) {
  return parseUnaryRight(ctx,
                         parseTypeAccess,
                         "type",
                         {{TokenID::Period, [](Node *arg, Token range) {
                             return Node::createTypeAccessUnary(arg, range);
                           }}});
}

ParserResult Parser::parseTypeFunction(ParserContext &ctx) {
  ParserResult callee = ctx.parse(parseTypeAccessUnary);
  if (!callee.isGood()) {
    return ParserResult();
  }

  Token lArrowToken = ctx.getToken();
  if (lArrowToken.getID() == TokenID::LArrow) {
    ctx.eatToken();
  } else {
    return callee;
  }

  Token lParenToken = ctx.getToken();
  if (lParenToken.getID() == TokenID::LParen) {
    ParserResult args = parseBoundSeparatedList(
        ctx, TokenID::LParen, parseType, "type", TokenID::Comma, TokenID::RParen);
    if (!args.isGood()) {
      return ParserResult();
    }

    return Node::createTypeFunction(
        callee.getNode(), {args.getNode()}, lArrowToken);
  } else {
    ctx.errorUnexpectedToken("(");
    return ParserResult();
  }
}

ParserResult Parser::parseTypeGroup(ParserContext &ctx) {
  return parseBoundTerm(
      ctx,
      TokenID::LParen,
      parseType,
      "type",
      TokenID::RParen,
      [](Node *arg, Token range) { return Node::createTypeGroup(arg, range); });
}

ParserResult Parser::parseType(ParserContext &ctx) {
  return parseTypeFunction(ctx);
}

ParserResult Parser::parseExprSymbol(ParserContext &ctx) {
  return parseSymbol(ctx, parseTemplateEvalArg, [](Node *args, Token range) {
    return Node::createExprSymbol(
        Field::createString(range.getText()), {args}, range);
  });
}

ParserResult Parser::parseExprLiteralUInt(ParserContext &ctx) {
  Token tokenInt = ctx.getToken();
  if (tokenInt.getID() == TokenID::Int) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  UInt64 tmp;
  if (!evalLiteralUInt(tokenInt.getText(), tmp)) {
    return ParserResult();
  }

  return ParserResult(Node::createExprLiteralUInt(
      Node::createTypeAtomicUInt64(), tmp, tokenInt));
}

ParserResult Parser::parseExprLiteralReal(ParserContext &ctx) {
  Token tokenInt = ctx.getToken();
  if (tokenInt.getID() == TokenID::Real) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  Real tmp;
  if (!evalLiteralReal(tokenInt.getText(), tmp)) {
    return ParserResult();
  }

  return ParserResult(Node::createExprLiteralReal(
      Node::createTypeAtomicReal(), tmp, tokenInt));
}

ParserResult Parser::parseExprGroup(ParserContext &ctx) {
  return parseBoundTerm(
      ctx,
      TokenID::LParen,
      parseExpr,
      "value",
      TokenID::RParen,
      [](Node *arg, Token range) { return Node::createExprGroup(arg, range); });
}

ParserResult Parser::parseExprTerm(ParserContext &ctx) {
  return ctx.parseAny({parseExprSymbol,
                       parseExprLiteralUInt,
                       parseExprLiteralReal,
                       parseExprGroup});
}

ParserResult Parser::parseExprAccess(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprTerm,
                     "value",
                     {{TokenID::Period, [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprAccess({lhs, rhs}, range);
                       }}});
}

ParserResult Parser::parseExprAccessUnary(ParserContext &ctx) {
  return parseUnaryRight(ctx,
                         parseExprAccess,
                         "value",
                         {{TokenID::Period, [](Node *arg, Token range) {
                             return Node::createExprAccessUnary(arg, range);
                           }}});
}

ParserResult Parser::parseExprCall(ParserContext &ctx) {
  ParserResult callee = ctx.parse(parseExprAccessUnary);
  if (!callee.isGood()) {
    return ParserResult();
  }

  Token lParenToken = ctx.getToken();
  if (lParenToken.getID() == TokenID::LParen) {
    ParserResult args = parseBoundSeparatedList(
        ctx, TokenID::LParen, parseExpr, "value", TokenID::Comma, TokenID::RParen);
    if (!args.isGood()) {
      return ParserResult();
    }

    return Node::createExprCall(
        callee.getNode(), {args.getNode()}, lParenToken);
  } else {
    return callee;
  }
}

ParserResult Parser::parseExprUnaryRight(ParserContext &ctx) {
  return parseUnaryRight(ctx,
                         parseExprCall,
                         "value",
                         {{TokenID::Inc,
                           [](Node *arg, Token range) {
                             return Node::createExprIncPre(arg, range);
                           }},
                          {TokenID::Dec,
                           [](Node *arg, Token range) {
                             return Node::createExprDecPre(arg, range);
                           }},
                          {TokenID::BitNot, [](Node *arg, Token range) {
                             return Node::createExprBitNot(arg, range);
                           }}});
}

ParserResult Parser::parseExprUnaryLeft(ParserContext &ctx) {
  return parseUnaryLeft(ctx,
                        parseExprUnaryRight,
                        "value",
                        {{TokenID::Inc,
                          [](Node *arg, Token range) {
                            return Node::createExprIncPost(arg, range);
                          }},
                         {TokenID::Dec, [](Node *arg, Token range) {
                            return Node::createExprDecPost(arg, range);
                          }}});
}

ParserResult Parser::parseExprExp(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprUnaryLeft,
                     "value",
                     {{TokenID::Exp, [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprExp(lhs, rhs, range);
                       }}});
}

ParserResult Parser::parseExprMul(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprExp,
                     "value",
                     {{TokenID::Mul,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprMul({lhs, rhs}, range);
                       }},
                      {TokenID::Div,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprDiv(lhs, rhs, range);
                       }},
                      {TokenID::DivInt,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprDivInt(lhs, rhs, range);
                       }},
                      {TokenID::DivReal, [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprDivReal(lhs, rhs, range);
                       }}});
}

ParserResult Parser::parseExprAdd(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprMul,
                     "value",
                     {{TokenID::Add,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprAdd({lhs, rhs}, range);
                       }},
                      {TokenID::Sub, [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprSub(lhs, rhs, range);
                       }}});
}

ParserResult Parser::parseExprMod(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprAdd,
                     "value",
                     {{TokenID::Mod, [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprMod(lhs, rhs, range);
                       }}});
}

ParserResult Parser::parseExprBitShR(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprMod,
                     "value",
                     {{TokenID::BitShR, [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprBitShR(lhs, rhs, range);
                       }}});
}

ParserResult Parser::parseExprBitShL(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprBitShR,
                     "value",
                     {{TokenID::BitShL, [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprBitShL(lhs, rhs, range);
                       }}});
}

ParserResult Parser::parseExprBitAnd(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprBitShL,
                     "value",
                     {{TokenID::BitAnd, [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprBitAnd({lhs, rhs}, range);
                       }}});
}

ParserResult Parser::parseExprBitOr(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprBitAnd,
                     "value",
                     {{TokenID::BitOr,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprBitOr({lhs, rhs}, range);
                       }},
                      {TokenID::BitXor, [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprBitXor({lhs, rhs}, range);
                       }}});
}

ParserResult Parser::parseExprCompare(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprBitOr,
                     "value",
                     {{TokenID::LT,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprLT(lhs, rhs, range);
                       }},
                      {TokenID::LE,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprLE(lhs, rhs, range);
                       }},
                      {TokenID::GT,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprGT(lhs, rhs, range);
                       }},
                      {TokenID::GE,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprGE(lhs, rhs, range);
                       }},
                      {TokenID::NE,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprNE(lhs, rhs, range);
                       }},
                      {TokenID::EQ, [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprEQ(lhs, rhs, range);
                       }}});
}

ParserResult Parser::parseExprBoolNot(ParserContext &ctx) {
  return parseUnaryRight(ctx,
                         parseExprCompare,
                         "value",
                         {{TokenID::KWNot, [](Node *arg, Token range) {
                             return Node::createExprBoolNot(arg, range);
                           }}});
}

ParserResult Parser::parseExprBoolAnd(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprBoolNot,
                     "value",
                     {{TokenID::KWAnd, [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprBoolAnd({lhs, rhs}, range);
                       }}});
}

ParserResult Parser::parseExprBoolOr(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprBoolAnd,
                     "value",
                     {{TokenID::KWOr, [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprBoolOr({lhs, rhs}, range);
                       }}});
}

ParserResult Parser::parseExprBoolImplies(ParserContext &ctx) {
  return parseBinary(
      ctx,
      parseExprBoolOr,
      "value",
      {{TokenID::BoolImplies, [](Node *lhs, Node *rhs, Token range) {
          return Node::createExprBoolImplies({lhs, rhs}, range);
        }}});
}

ParserResult Parser::parseExprAssign(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprBoolImplies,
                     "value",
                     {{TokenID::AddAssign,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprAddAssign(lhs, rhs, range);
                       }},
                      {TokenID::SubAssign,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprSubAssign(lhs, rhs, range);
                       }},
                      {TokenID::MulAssign,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprMulAssign(lhs, rhs, range);
                       }},
                      {TokenID::ExpAssign,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprExpAssign(lhs, rhs, range);
                       }},
                      {TokenID::DivAssign,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprDivAssign(lhs, rhs, range);
                       }},
                      {TokenID::DivIntAssign,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprDivIntAssign(lhs, rhs, range);
                       }},
                      {TokenID::DivRealAssign,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprDivRealAssign(lhs, rhs, range);
                       }},
                      {TokenID::ModAssign,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprModAssign(lhs, rhs, range);
                       }},
                      {TokenID::BitAndAssign,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprBitAndAssign(lhs, rhs, range);
                       }},
                      {TokenID::BitOrAssign,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprBitOrAssign(lhs, rhs, range);
                       }},
                      {TokenID::BitXorAssign,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprBitXorAssign(lhs, rhs, range);
                       }},
                      {TokenID::BitShLAssign,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprBitShLAssign(lhs, rhs, range);
                       }},
                      {TokenID::BitShRAssign,
                       [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprBitShRAssign(lhs, rhs, range);
                       }},
                      {TokenID::Assign, [](Node *lhs, Node *rhs, Token range) {
                         return Node::createExprAssign(lhs, rhs, range);
                       }}});
}

ParserResult Parser::parseExpr(ParserContext &ctx) {
  return parseExprAssign(ctx);
}

ParserResult Parser::parseStmtEmpty(ParserContext &ctx) {
  Token tokenSemicolon = ctx.getToken();
  if (tokenSemicolon.getID() == TokenID::Semicolon) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  return ParserResult(Node::createStmtEmpty(tokenSemicolon));
}

ParserResult Parser::parseStmtExpr(ParserContext &ctx) {
  ParserResult arg = ctx.parse(parseExpr);
  if (!arg.isGood()) {
    return ParserResult();
  }

  Token tokenSemicolon = ctx.getToken();
  if (tokenSemicolon.getID() == TokenID::Semicolon) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken(";");
    return ParserResult();
  }

  return ParserResult(
      Node::createStmtExpr(arg.getNode(), tokenSemicolon));
}

ParserResult Parser::parseStmtDecl(ParserContext &ctx) {
  ParserResult arg = ctx.parse(parseDecl);
  if (!arg.isGood()) {
    return ParserResult();
  }

  return ParserResult(
      Node::createStmtDecl(arg.getNode(), arg.getNode()->getToken()));
}

ParserResult Parser::parseStmtReturn(ParserContext &ctx) {
  Token tokenKWReturn = ctx.getToken();
  if (tokenKWReturn.getID() == TokenID::KWReturn) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  Token tokenLParen = ctx.getToken();
  if (tokenLParen.getID() == TokenID::LParen) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken("(");
    return ParserResult();
  }

  ParserResult arg;

  Token tokenRParen = ctx.getToken();
  if (tokenRParen.getID() == TokenID::RParen) {
    ctx.eatToken();
  } else {
    arg = ctx.parse(parseExpr);
    if (!arg.isGood()) {
      ctx.errorUnexpectedToken("value");
      return ParserResult();
    }

    tokenRParen = ctx.getToken();
    if (tokenRParen.getID() == TokenID::RParen) {
      ctx.eatToken();
    } else {
      ctx.errorUnexpectedToken("closing )");
      return ParserResult();
    }
  }

  Token tokenSemicolon = ctx.getToken();
  if (tokenSemicolon.getID() == TokenID::Semicolon) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken(";");
    return ParserResult();
  }

  return ParserResult(
      Node::createStmtReturn(arg.getNode(), tokenSemicolon));
}

ParserResult Parser::parseStmtContinue(ParserContext &ctx) {
  Token tokenKWContinue = ctx.getToken();
  if (tokenKWContinue.getID() == TokenID::KWContinue) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  Token tokenLParen = ctx.getToken();
  if (tokenLParen.getID() == TokenID::LParen) {
    ctx.eatToken();
  } else if (tokenLParen.getID() == TokenID::Semicolon) {
    ctx.eatToken();
    return ParserResult(Node::createStmtContinue(tokenKWContinue));
  } else {
    ctx.errorUnexpectedToken("(");
    return ParserResult();
  }

  Token tokenName;

  Token tokenRParen = ctx.getToken();
  if (tokenRParen.getID() == TokenID::RParen) {
    ctx.eatToken();
  } else {
    tokenName = ctx.getToken();
    if (tokenName.getID() == TokenID::String) {
      ctx.eatToken();
    } else {
      tokenName = Token();
    }

    tokenRParen = ctx.getToken();
    if (tokenRParen.getID() == TokenID::RParen) {
      ctx.eatToken();
    } else {
      ctx.errorUnexpectedToken("closing )");
      return ParserResult();
    }
  }

  Token tokenSemicolon = ctx.getToken();
  if (tokenSemicolon.getID() == TokenID::Semicolon) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken(";");
    return ParserResult();
  }

  if (tokenName.getID() != TokenID::None) {
    return ParserResult(Node::createStmtContinue(
        Field::createString(tokenName.getText()),
        tokenSemicolon));
  } else {
    return ParserResult(Node::createStmtContinue(tokenSemicolon));
  }
}

ParserResult Parser::parseStmtBreak(ParserContext &ctx) {
  Token tokenKWBreak = ctx.getToken();
  if (tokenKWBreak.getID() == TokenID::KWBreak) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  Token tokenLParen = ctx.getToken();
  if (tokenLParen.getID() == TokenID::LParen) {
    ctx.eatToken();
  } else if (tokenLParen.getID() == TokenID::Semicolon) {
    ctx.eatToken();
    return ParserResult(Node::createStmtBreak(tokenKWBreak));
  } else {
    ctx.errorUnexpectedToken("(");
    return ParserResult();
  }

  Token tokenName;

  Token tokenRParen = ctx.getToken();
  if (tokenRParen.getID() == TokenID::RParen) {
    ctx.eatToken();
  } else {
    tokenName = ctx.getToken();
    if (tokenName.getID() == TokenID::String) {
      ctx.eatToken();
    } else {
      tokenName = Token();
    }

    tokenRParen = ctx.getToken();
    if (tokenRParen.getID() == TokenID::RParen) {
      ctx.eatToken();
    } else {
      ctx.errorUnexpectedToken("closing )");
      return ParserResult();
    }
  }

  Token tokenSemicolon = ctx.getToken();
  if (tokenSemicolon.getID() == TokenID::Semicolon) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken(";");
    return ParserResult();
  }

  if (tokenName.isGood()) {
    return ParserResult(Node::createStmtBreak(
        Field::createString(tokenName.getText()),
        tokenSemicolon));
  } else {
    return ParserResult(Node::createStmtBreak(tokenSemicolon));
  }
}

ParserResult Parser::parseStmtIf(ParserContext &ctx) {
  Token tokenKWIf = ctx.getToken();
  if (tokenKWIf.getID() == TokenID::KWIf) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  ParserResult condition =
      parseBoundTerm(ctx,
                     TokenID::LParen,
                     parseExpr,
                     "value",
                     TokenID::RParen,
                     [](Node *arg, Token range) { return arg; });
  if (!condition.isGood()) {
    ctx.errorUnexpectedToken("(");
    return ParserResult();
  }

  ParserResult then = ctx.parse(parseStmt);
  if (!then.isGood()) {
    ctx.errorUnexpectedToken("then clause");
    return ParserResult();
  }

  Token tokenKWElse = ctx.getToken();
  if (tokenKWElse.getID() == TokenID::KWElse) {
    ctx.eatToken();

    ParserResult _else = ctx.parse(parseStmt);
    if (!_else.isGood()) {
      ctx.errorUnexpectedToken("else clause");
      return ParserResult();
    }

    return ParserResult(Node::createStmtIf(condition.getNode(),
                                           then.getNode(),
                                           _else.getNode(),
                                           tokenKWIf));
  } else {
    return ParserResult(Node::createStmtIf(
        condition.getNode(), then.getNode(), tokenKWIf));
  }
}

ParserResult Parser::parseStmtWhile(ParserContext &ctx) {
  Token tokenKWWhile = ctx.getToken();
  if (tokenKWWhile.getID() == TokenID::KWWhile) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  ParserResult condition =
      parseBoundTerm(ctx,
                     TokenID::LParen,
                     parseExpr,
                     "value",
                     TokenID::RParen,
                     [](Node *arg, Token range) { return arg; });
  if (!condition.isGood()) {
    ctx.errorUnexpectedToken("(");
    return ParserResult();
  }

  ParserResult body = ctx.parse(parseStmt);
  if (!body.isGood()) {
    ctx.errorUnexpectedToken("body clause");
    return ParserResult();
  }

  return ParserResult(Node::createStmtWhile(
      condition.getNode(), body.getNode(), tokenKWWhile));
}

ParserResult Parser::parseStmtFor(ParserContext &ctx) {
  Token tokenFor = ctx.getToken();
  if (tokenFor.getID() == TokenID::KWFor) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  Token tokenLParen = ctx.getToken();
  if (tokenLParen.getID() == TokenID::LParen) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken("(");
    return ParserResult();
  }

  ParserResult res =
      ParserResult(Node::createStmtFor({}, nullptr, {}, tokenFor));

  Node *front = nullptr;
  Node *back = nullptr;

  bool endedCorrectly = false;
  while (ctx.areMoreTokens()) {
    Token tokenSepFirst = ctx.getToken();
    if (!tokenSepFirst.isGood()) {
      ctx.errorUnexpectedToken("variable declaration or ;");
      return ParserResult();
    } else if (tokenSepFirst.getID() == TokenID::Semicolon) {
      ctx.eatToken();
      endedCorrectly = true;
      break;
    } else if (tokenSepFirst.getID() == TokenID::Comma) {
      ctx.eatToken();
    } else {
      ParserResult decl = ctx.parse(parseDeclVariableNoSemicolon);
      if (!decl.isGood()) {
        ctx.errorUnexpectedToken("variable declaration");
        return ParserResult();
      }
      if (front == nullptr) {
        front = back = decl.getNode();
      } else {
        back->setNext(decl.getNode());
        back = decl.getNode();
      }
    }
  }

  res.getNode()->getField(Node::FieldTag::StmtFor_Decls)->setNode(front);

  if (!endedCorrectly) {
    ctx.errorUnexpectedToken(";");
    return ParserResult();
  }

  Token tokenSepSecond = ctx.getToken();
  if (tokenSepSecond.getID() != TokenID::Semicolon) {
    ParserResult cond = ctx.parse(parseExpr);
    if (!cond.isGood()) {
      ctx.errorUnexpectedToken("condition");
      return ParserResult();
    }

    res.getNode()
        ->getField(Node::FieldTag::StmtFor_Condition)
        ->setNode(cond.getNode());
  }

  tokenSepSecond = ctx.getToken();
  if (tokenSepSecond.getID() == TokenID::Semicolon) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken(";");
    return ParserResult();
  }

  front = back = nullptr;

  endedCorrectly = false;
  while (ctx.areMoreTokens()) {
    Token tokenSepThird = ctx.getToken();
    if (!tokenSepThird.isGood()) {
      ctx.errorUnexpectedToken("expression or )");
    } else if (tokenSepThird.getID() == TokenID::RParen) {
      endedCorrectly = true;
      ctx.eatToken();
      break;
    } else if (tokenSepThird.getID() == TokenID::Comma) {
      ctx.eatToken();
    } else {
      ParserResult step = ctx.parse(parseExpr);
      if (!step.isGood()) {
        ctx.errorUnexpectedToken("expression");
        return ParserResult();
      }
      if (front == nullptr) {
        front = back = step.getNode();
      } else {
        back->setNext(step.getNode());
        back = step.getNode();
      }
    }
  }

  res.getNode()->getField(Node::FieldTag::StmtFor_Steps)->setNode(front);

  if (!endedCorrectly) {
    ctx.errorUnexpectedToken(")");
    return ParserResult();
  }

  ParserResult body = ctx.parse(parseStmt);
  if (!body.isGood()) {
    ctx.errorUnexpectedToken("body clause");
    return ParserResult();
  }

  res.getNode()
      ->getField(Node::FieldTag::StmtFor_Body)
      ->setNode(body.getNode());

  return res;
}

ParserResult Parser::parseStmtForEach(ParserContext &ctx) {
  Token tokenForEach = ctx.getToken();
  if (tokenForEach.getID() == TokenID::KWForEach) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  Token tokenLParen = ctx.getToken();
  if (tokenLParen.getID() == TokenID::LParen) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken("(");
    return ParserResult();
  }

  ParserResult res =
      ParserResult(Node::createStmtForEach({}, {}, tokenForEach));

  Node *front = nullptr;
  Node *back = nullptr;

  bool endedCorrectly = false;
  while (ctx.areMoreTokens()) {
    Token tokenSepFirst = ctx.getToken();
    if (!tokenSepFirst.isGood()) {
      ctx.errorUnexpectedToken("variable declaration or ;");
      return ParserResult();
    } else if (tokenSepFirst.getID() == TokenID::Semicolon) {
      ctx.eatToken();
      endedCorrectly = true;
      break;
    } else if (tokenSepFirst.getID() == TokenID::Comma) {
      ctx.eatToken();
    } else {
      ParserResult decl = ctx.parse(parseDeclVariableNoSemicolon);
      if (!decl.isGood()) {
        ctx.errorUnexpectedToken("variable declaration");
        return ParserResult();
      }

      if (front == nullptr) {
        front = back = decl.getNode();
      } else {
        back->setNext(decl.getNode());
        back = decl.getNode();
      }

      tokenSepFirst = ctx.getToken();
      if (tokenSepFirst.getID() == TokenID::Comma) {
        continue;
      } else if (tokenSepFirst.getID() == TokenID::Semicolon) {
        ctx.eatToken();
        endedCorrectly = true;
        break;
      }
    }
  }

  res.getNode()->getField(Node::FieldTag::StmtForEach_Decls)->setNode(front);

  if (!endedCorrectly) {
    ctx.errorUnexpectedToken(";");
    return ParserResult();
  }

  front = back = nullptr;

  endedCorrectly = false;
  while (ctx.areMoreTokens()) {
    Token tokenSepThird = ctx.getToken();
    if (!tokenSepThird.isGood()) {
      ctx.errorUnexpectedToken("expression or )");
    } else if (tokenSepThird.getID() == TokenID::RParen) {
      ctx.eatToken();
      endedCorrectly = true;
      break;
    } else if (tokenSepThird.getID() == TokenID::Comma) {
      ctx.eatToken();
    } else {
      ParserResult sequence = ctx.parse(parseExpr);
      if (!sequence.isGood()) {
        ctx.errorUnexpectedToken("expression");
        return ParserResult();
      }

      if (front == nullptr) {
        front = back = sequence.getNode();
      } else {
        back->setNext(sequence.getNode());
        back = sequence.getNode();
      }

      tokenSepThird = ctx.getToken();
      if (tokenSepThird.getID() == TokenID::RParen) {
        ctx.eatToken();
        endedCorrectly = true;
        break;
      }
    }
  }

  res.getNode()
      ->getField(Node::FieldTag::StmtForEach_Sequences)
      ->setNode(front);

  if (!endedCorrectly) {
    ctx.errorUnexpectedToken(")");
    return ParserResult();
  }

  ParserResult body = ctx.parse(parseStmt);
  if (!body.isGood()) {
    ctx.errorUnexpectedToken("body clause");
    return ParserResult();
  }

  res.getNode()
      ->getField(Node::FieldTag::StmtForEach_Body)
      ->setNode(body.getNode());

  return res;
}

ParserResult Parser::parseStmtBlock(ParserContext &ctx) {
  Token tokenLBrace = ctx.getToken();
  if (tokenLBrace.getID() == TokenID::LBrace) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  ParserResult res =
      ParserResult(Node::createStmtBlock(tokenLBrace));

  Node *front = nullptr;
  Node *back = nullptr;

  bool endedCorrectly = false;
  while (ctx.areMoreTokens()) {
    Token tokenSep = ctx.getToken();
    if (!tokenSep.isGood()) {
      ctx.errorUnexpectedToken("statement or }");
      return ParserResult();
    } else if (tokenSep.getID() == TokenID::RBrace) {
      ctx.eatToken();
      endedCorrectly = true;
      break;
    } else {
      ParserResult stmt = ctx.parse(parseStmt);
      if (!stmt.isGood()) {
        ctx.errorUnexpectedToken("statement");
        return ParserResult();
      }
      if (front == nullptr) {
        front = back = stmt.getNode();
      } else {
        back->setNext(stmt.getNode());
        back = stmt.getNode();
      }
    }
  }

  res.getNode()->getField(Node::FieldTag::StmtBlock_Stmts)->setNode(front);

  if (!endedCorrectly) {
    ctx.errorUnexpectedToken("}");
    return ParserResult();
  }

  return res;
}

ParserResult Parser::parseStmt(ParserContext &ctx) {
  return ctx.parseAny({parseStmtBlock,
                       parseStmtIf,
                       parseStmtWhile,
                       parseStmtFor,
                       parseStmtForEach,
                       parseStmtReturn,
                       parseStmtEmpty,
                       parseStmtExpr,
                       parseStmtDecl});
}

ParserResult Parser::parseDeclVariableNoSemicolon(ParserContext &ctx) {
  ParserResult type = ctx.parse(parseType);
  if (!type.isGood()) {
    ctx.errorUnexpectedToken("type");
    return ParserResult();
  }

  Token tokenSymbol = ctx.getToken();
  if (tokenSymbol.getID() == TokenID::Symbol) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken("symbol");
    return ParserResult();
  }

  ParserResult res = ParserResult(Node::createDeclVariable(
      type.getNode(), Field::createString(tokenSymbol.getText())));

  Token tokenLT = ctx.getToken();
  if (tokenLT.getID() == TokenID::LT) {
    ParserResult templateArgs =
        parseTemplateList(ctx, parseDeclVariableNoSemicolon, "template arg");
    if (templateArgs.isGood()) {
      res.getNode()
          ->getField(Node::FieldTag::DeclVariable_TemplateDeclArgs)
          ->setNode(templateArgs.getNode());
    } else {
      return ParserResult();
    }
  }

  Token tokenSep = ctx.getToken();
  if (tokenSep.getID() == TokenID::Assign) {
    ctx.eatToken();
    ParserResult init = ctx.parse(parseExpr);
    if (!init.isGood()) {
      ctx.errorUnexpectedToken("value");
      return ParserResult();
    }

    res.getNode()
        ->getField(Node::FieldTag::DeclVariable_Initial)
        ->setNode(init.getNode());
  }

  return res;
}

ParserResult Parser::parseDeclVariable(ParserContext &ctx) {
  ParserResult res = ctx.parse(parseDeclVariableNoSemicolon);
  if (!res.isGood()) {
    return ParserResult();
  }

  Token tokenSymbol = ctx.getToken();
  if (tokenSymbol.getID() == TokenID::Semicolon) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken(";");
    return ParserResult();
  }

  return res;
}

ParserResult Parser::parseDeclFunction(ParserContext &ctx) {
  ParserResult type = ctx.parse(parseType);
  if (!type.isGood()) {
    ctx.errorUnexpectedToken("type");
    return ParserResult();
  }

  Token tokenSymbol = ctx.getToken();
  if (tokenSymbol.getID() == TokenID::Symbol) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken("symbol");
    return ParserResult();
  }

  ParserResult res = ParserResult(Node::createDeclFunction(
      type.getNode(),
      Field::createString(tokenSymbol.getText()),
      {}));

  Token tokenLT = ctx.getToken();
  if (tokenLT.getID() == TokenID::LT) {
    ParserResult templateArgs =
        parseTemplateList(ctx, parseDeclVariableNoSemicolon, "template arg");
    if (templateArgs.isGood()) {
      res.getNode()
          ->getField(Node::FieldTag::DeclFunction_TemplateDeclArgs)
          ->setNode(templateArgs.getNode());
    } else {
      return ParserResult();
    }
  }

  Token tokenLParen = ctx.getToken();
  if (tokenLParen.getID() == TokenID::LParen) {
    ParserResult args = parseBoundSeparatedList(ctx,
                                                TokenID::LParen,
                                                parseDeclVariableNoSemicolon,
                                                "arg",
                                                TokenID::Comma,
                                                TokenID::RParen);
    if (!args.isGood()) {
      return ParserResult();
    } else {
      res.getNode()
          ->getField(Node::FieldTag::DeclFunction_Args)
          ->setNode(args.getNode());
    }
  } else {
    return ParserResult();
  }

  Token tokenSep = ctx.getToken();
  if (!tokenSep.isGood()) {
    ctx.errorUnexpectedToken("function body");
    return ParserResult();
  } else if (tokenSep.getID() == TokenID::Semicolon) {
    ctx.eatToken();
    return res;
  } else if (tokenSep.getID() == TokenID::Assign) {
    ctx.eatToken();
    ParserResult body = ctx.parse(parseStmtExpr);
    if (!body.isGood()) {
      ctx.errorUnexpectedToken("value");
      return ParserResult();
    }

    res.getNode()
        ->getField(Node::FieldTag::DeclFunction_Body)
        ->setNode(body.getNode());
  } else {
    ParserResult body = ctx.parse(parseStmtBlock);
    if (!body.isGood()) {
      ctx.errorUnexpectedToken("body");
      return ParserResult();
    }

    res.getNode()
        ->getField(Node::FieldTag::DeclFunction_Body)
        ->setNode(body.getNode());
  }

  return res;
}

ParserResult Parser::parseDeclClass(ParserContext &ctx) {
  Token tokenKWClass = ctx.getToken();
  if (tokenKWClass.getID() == TokenID::KWClass) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  Token tokenSymbol = ctx.getToken();
  if (tokenSymbol.getID() == TokenID::Symbol) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken("symbol");
    return ParserResult();
  }

  ParserResult res = ParserResult(Node::createDeclClass(
      Field::createString(tokenSymbol.getText())));

  Token tokenLT = ctx.getToken();
  if (tokenLT.getID() == TokenID::LT) {
    ParserResult templateArgs =
        parseTemplateList(ctx, parseDeclVariableNoSemicolon, "template arg");
    if (templateArgs.isGood()) {
      res.getNode()
          ->getField(Node::FieldTag::DeclClass_TemplateDeclArgs)
          ->setNode(templateArgs.getNode());
    } else {
      return ParserResult();
    }
  }

  Token tokenKWInherits = ctx.getToken();
  if (tokenKWInherits.getID() == TokenID::KWInherits) {
    ctx.eatToken();

    Node *front = nullptr;
    Node *back = nullptr;

    bool endedCorrectly = false;
    while (ctx.areMoreTokens()) {
      Token tokenSep = ctx.getToken();
      if (!tokenSep.isGood()) {
        ctx.errorUnexpectedToken("type, {, or ;");
        return ParserResult();
      } else if (tokenSep.getID() == TokenID::LBrace) {
        ctx.eatToken();
        endedCorrectly = true;
        break;
      } else if (tokenSep.getID() == TokenID::Semicolon) {
        ctx.eatToken();
        endedCorrectly = true;
        break;
      } else {
        ParserResult type = ctx.parse(parseType);
        if (!type.isGood()) {
          ctx.errorUnexpectedToken("type");
          return ParserResult();
        }

        if (front == nullptr) {
          front = back = type.getNode();
        } else {
          back->setNext(type.getNode());
          back = type.getNode();
        }

        tokenSep = ctx.getToken();
        if (tokenSep.getID() == TokenID::Comma) {
          ctx.eatToken();
          continue;
        } else if (tokenSep.getID() == TokenID::LBrace) {
          endedCorrectly = true;
          break;
        } else if (tokenSep.getID() == TokenID::Semicolon) {
          endedCorrectly = true;
          break;
        } else {
          ctx.errorUnexpectedToken("class body");
          return ParserResult();
        }
      }
    }

    res.getNode()->getField(Node::FieldTag::DeclClass_Inherits)->setNode(front);

    if (!endedCorrectly) {
      ctx.errorUnexpectedToken("}");
      return ParserResult();
    }
  }

  Token tokenSep = ctx.getToken();
  if (!tokenSep.isGood()) {
    ctx.errorUnexpectedToken("{ or ;");
    return ParserResult();
  } else if (tokenSep.getID() == TokenID::Semicolon) {
    ctx.eatToken();
    return res;
  } else if (tokenSep.getID() == TokenID::LBrace) {
    ctx.eatToken();

    Node *front = nullptr;
    Node *back = nullptr;

    bool endedCorrectly = false;
    while (ctx.areMoreTokens()) {
      Token tokenSep = ctx.getToken();
      if (!tokenSep.isGood()) {
        ctx.errorUnexpectedToken("declaration or }");
        return ParserResult();
      } else if (tokenSep.getID() == TokenID::RBrace) {
        ctx.eatToken();
        endedCorrectly = true;
        break;
      } else {
        ParserResult decl = ctx.parse(parseDecl);
        if (!decl.isGood()) {
          ctx.errorUnexpectedToken("declaration");
          return ParserResult();
        }
        if (front == nullptr) {
          front = back = decl.getNode();
        } else {
          back->setNext(decl.getNode());
          back = decl.getNode();
        }
      }
    }

    res.getNode()->getField(Node::FieldTag::DeclClass_Members)->setNode(front);

    if (!endedCorrectly) {
      ctx.errorUnexpectedToken("}");
      return ParserResult();
    }
  } else {
    ctx.errorUnexpectedToken("{ or ;");
    return ParserResult();
  }

  return res;
}

ParserResult Parser::parseDeclNamespace(ParserContext &ctx) {
  Token tokenKWNamespace = ctx.getToken();
  if (tokenKWNamespace.getID() == TokenID::KWNamespace) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  Token tokenSymbol = ctx.getToken();
  if (tokenSymbol.getID() == TokenID::Symbol) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken("symbol");
    return ParserResult();
  }

  ParserResult res = ParserResult(Node::createDeclNamespace(
      Field::createString(tokenSymbol.getText())));

  Token tokenSep = ctx.getToken();
  if (!tokenSep.isGood()) {
    ctx.errorUnexpectedToken("{");
    return ParserResult();
  } else if (tokenSep.getID() == TokenID::LBrace) {
    ctx.eatToken();

    Node *front = nullptr;
    Node *back = nullptr;

    bool endedCorrectly = false;
    while (ctx.areMoreTokens()) {
      Token tokenSep = ctx.getToken();
      if (!tokenSep.isGood()) {
        ctx.errorUnexpectedToken("declaration or }");
        return ParserResult();
      } else if (tokenSep.getID() == TokenID::RBrace) {
        ctx.eatToken();
        endedCorrectly = true;
        break;
      } else {
        ParserResult decl = ctx.parse(parseDecl);
        if (!decl.isGood()) {
          ctx.errorUnexpectedToken("declaration");
          return ParserResult();
        }
        if (front == nullptr) {
          front = back = decl.getNode();
        } else {
          back->setNext(decl.getNode());
          back = decl.getNode();
        }
      }
    }

    res.getNode()
        ->getField(Node::FieldTag::DeclNamespace_Members)
        ->setNode(front);

    if (!endedCorrectly) {
      ctx.errorUnexpectedToken("}");
      return ParserResult();
    }
  } else {
    ctx.errorUnexpectedToken("{");
    return ParserResult();
  }

  return res;
}

ParserResult Parser::parseDecl(ParserContext &ctx) {
  return ctx.parseAny({parseDeclClass,
                       parseDeclNamespace,
                       parseDeclFunction,
                       parseDeclVariable});
}

ParserResult Parser::parseImport(ParserContext &ctx) {
  Token tokenKWImport = ctx.getToken();
  if (tokenKWImport.getID() == TokenID::KWImport) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  Token tokenLParen = ctx.getToken();
  if (tokenLParen.getID() == TokenID::LParen) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken("(");
    return ParserResult();
  }

  Token tokenString = ctx.getToken();
  if (tokenString.getID() == TokenID::String) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken("path");
    return ParserResult();
  }

  Token tokenRParen = ctx.getToken();
  if (tokenRParen.getID() == TokenID::RParen) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken(")");
    return ParserResult();
  }

  Token tokenSemicolon = ctx.getToken();
  if (tokenSemicolon.getID() == TokenID::Semicolon) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken(";");
    return ParserResult();
  }

  std::string path;
  if (!evalLiteralString(tokenString.getText(), path)) {
    return ParserResult();
  }

  return ParserResult(
      Node::createImport(Field::createString(path), tokenKWImport));
}

ParserResult Parser::parseUnit(ParserContext &ctx) {
  Node *front = nullptr;
  Node *back = nullptr;

  while (ctx.areMoreTokens()) {
    ParserResult tmp = ctx.parseAny({parseImport, parseDecl});

    if (!tmp.isGood()) {
      ctx.errorUnexpectedToken("declaration");
      return ParserResult();
    }

    if (front == nullptr) {
      front = back = tmp.getNode();
    } else {
      back->setNext(tmp.getNode());
      back = tmp.getNode();
    }
  }

  return Node::createUnit({front});
}

Parser::Parser(const std::vector<Token> &tokens,
               MessageBuffer &msgs,
               unsigned int offset)
    : ctx(tokens, msgs, offset) {
}

Node *Parser::parse() {
  return parseUnit(ctx).getNode();
}
} // namespace whiskey
