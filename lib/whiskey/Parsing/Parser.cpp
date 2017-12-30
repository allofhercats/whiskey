#include "Module.inc"

#include <whiskey/Parsing/Parser.hpp>

namespace whiskey {
ParserResult Parser::parseBoundList(ParserContext &ctx,
                                    Token::ID left,
                                    ParserContext::Rule rule,
                                    const std::string &expected,
                                    Token::ID right) {
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
    Token::printTokenID(ss, right);
    ctx.errorUnexpectedToken(ss.str());
    ctx = save;
    return ParserResult();
  }

  return ParserResult(front);
}

ParserResult Parser::parseBoundSeparatedList(ParserContext &ctx,
                                             Token::ID left,
                                             ParserContext::Rule rule,
                                             const std::string &expected,
                                             Token::ID sep,
                                             Token::ID right) {
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
      Token::printTokenID(ss, sep);
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
      Token::printTokenID(ss, sep);
      ctx.errorUnexpectedToken(ss.str());
      ctx = save;
      return ParserResult();
    }
  }

  if (!endedCorrectly) {
    std::stringstream ss;
    ss << "closing ";
    Token::printTokenID(ss, right);
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
  if (leftToken.getID() == Token::LT) {
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
    if (rightToken.getID() == Token::GT) {
      ctx.eatToken();
      endedCorrectly = true;
      break;
    } else if (rightToken.getID() == Token::GE) {
      ctx.eatToken();
      ctx.injectToken(Token(Token::Assign));
      endedCorrectly = true;
      break;
    } else if (rightToken.getID() == Token::BitShR) {
      ctx.eatToken();
      ctx.injectToken(Token(Token::GT));
      endedCorrectly = true;
      break;
    } else if (rightToken.getID() == Token::BitShRAssign) {
      ctx.eatToken();
      ctx.injectToken(Token(Token::GE));
      endedCorrectly = true;
      break;
    } else if (rightToken.getID() == Token::Comma) {
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
    if (rightToken.getID() == Token::Comma) {
      ctx.eatToken();
    } else if (rightToken.getID() == Token::GT ||
               rightToken.getID() == Token::GE ||
               rightToken.getID() == Token::BitShR ||
               rightToken.getID() == Token::BitShRAssign) {
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
                                 std::function<Node *(Node *, Range)> builder) {
  ParserContext save = ctx;

  Token symbolToken = ctx.getToken();
  if (symbolToken.getID() == Token::Symbol) {
    ctx.eatToken();
  } else {
    ctx = save;
    return ParserResult();
  }

  Token tokenLT = ctx.getToken();
  if (tokenLT.getID() == Token::LT) {
    ParserResult templateArgs =
        parseTemplateList(ctx, templateArgRule, "template arg");
    if (templateArgs.isGood()) {
      return builder(templateArgs.getNode(), symbolToken.getRange());
    } else {
      ctx = save;
      return ParserResult();
    }
  } else {
    return ParserResult(builder(nullptr, symbolToken.getRange()));
  }
}

ParserResult Parser::parseUnaryRight(
    ParserContext &ctx,
    ParserContext::Rule baseRule,
    const std::string &expected,
    std::initializer_list<
        std::pair<Token::ID, std::function<Node *(Node *, Range)>>> builders) {
  ParserContext save = ctx;

  Token opToken = ctx.getToken();

  for (const std::pair<Token::ID, std::function<Node *(Node *, Range)>> &kv :
       builders) {
    ctx = save;
    if (opToken.getID() == kv.first) {
      ctx.eatToken();

      ParserResult arg = parseUnaryRight(ctx, baseRule, expected, builders);
      if (arg.isGood()) {
        return ParserResult(kv.second(arg.getNode(), opToken.getRange()));
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
        std::pair<Token::ID, std::function<Node *(Node *, Range)>>> builders) {
  ParserContext save = ctx;

  ParserResult res = ctx.parse(baseRule);
  if (res.isGood()) {
    bool gotOp = false;

    while (ctx.areMoreTokens()) {
      save = ctx;
      for (const std::pair<Token::ID, std::function<Node *(Node *, Range)>>
               &kv : builders) {
        ctx = save;
        Token opToken = ctx.getToken();
        if (opToken.getID() == kv.first) {
          res = ParserResult(kv.second(res.getNode(), opToken.getRange()));
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
        std::pair<Token::ID, std::function<Node *(Node *, Node *, Range)>>>
        builders) {
  ParserContext save = ctx;

  ParserResult lhs = ctx.parse(lhsRule);
  if (!lhs.isGood()) {
    return ParserResult();
  }

  for (const std::pair<Token::ID, std::function<Node *(Node *, Node *, Range)>>
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
          kv.second(lhs.getNode(), rhs.getNode(), opToken.getRange()));
    }
  }
  return lhs;
}

ParserResult
Parser::parseBoundTerm(ParserContext &ctx,
                       Token::ID left,
                       ParserContext::Rule rule,
                       const std::string &expected,
                       Token::ID right,
                       std::function<Node *(Node *, Range)> builder) {
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
  if (rightToken.getID() == Token::RParen) {
    ctx.eatToken();
  } else {
    std::stringstream ss;
    ss << "closing ";
    Token::printTokenID(ss, right);
    ctx.errorUnexpectedToken(ss.str());
    ctx = save;
    return ParserResult();
  }

  return ParserResult(builder(rtn.getNode(), leftToken.getRange()));
}

ParserResult Parser::parseTemplateEvalArg(ParserContext &ctx) {
  return ctx.parseAny({parseType, parseExpr});
}

ParserResult Parser::parseTypeAtomic(ParserContext &ctx) {
  Token tokenSymbol = ctx.getToken();
  if (tokenSymbol.getID() == Token::KWBool) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicBool(tokenSymbol.getRange()));
  } else if (tokenSymbol.getID() == Token::KWInt8) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicInt8(tokenSymbol.getRange()));
  } else if (tokenSymbol.getID() == Token::KWInt16) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicInt16(tokenSymbol.getRange()));
  } else if (tokenSymbol.getID() == Token::KWInt32) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicInt32(tokenSymbol.getRange()));
  } else if (tokenSymbol.getID() == Token::KWInt64) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicInt64(tokenSymbol.getRange()));
  } else if (tokenSymbol.getID() == Token::KWUInt8) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicUInt8(tokenSymbol.getRange()));
  } else if (tokenSymbol.getID() == Token::KWUInt16) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicUInt16(tokenSymbol.getRange()));
  } else if (tokenSymbol.getID() == Token::KWUInt32) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicUInt32(tokenSymbol.getRange()));
  } else if (tokenSymbol.getID() == Token::KWUInt64) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicUInt64(tokenSymbol.getRange()));
  } else if (tokenSymbol.getID() == Token::KWFloat32) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicFloat32(tokenSymbol.getRange()));
  } else if (tokenSymbol.getID() == Token::KWFloat64) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicFloat64(tokenSymbol.getRange()));
  } else if (tokenSymbol.getID() == Token::KWReal) {
    ctx.eatToken();
    return ParserResult(Node::createTypeAtomicReal(tokenSymbol.getRange()));
  } else {
    return ParserResult();
  }
}

ParserResult Parser::parseTypeSymbol(ParserContext &ctx) {
  return parseSymbol(ctx, parseTemplateEvalArg, [](Node *args, Range range) {
    return Node::createTypeSymbol(
        Field::createString8(range.getText().c_str()), {args}, range);
  });
}

ParserResult Parser::parseTypeTerm(ParserContext &ctx) {
  return ctx.parseAny({parseTypeSymbol, parseTypeAtomic, parseTypeGroup});
}

ParserResult Parser::parseTypeAccess(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseTypeTerm,
                     "type",
                     {{Token::Period, [](Node *lhs, Node *rhs, Range range) {
                         return Node::createTypeAccess({lhs, rhs}, range);
                       }}});
}

ParserResult Parser::parseTypeAccessUnary(ParserContext &ctx) {
  return parseUnaryRight(
      ctx, parseTypeAccess, "type", {{Token::Period, [](Node *arg, Range range) {
                                      return Node::createTypeAccessUnary(arg,
                                                                         range);
                                    }}});
}

ParserResult Parser::parseTypeFunction(ParserContext &ctx) {
  ParserResult callee = ctx.parse(parseTypeAccessUnary);
  if (!callee.isGood()) {
    return ParserResult();
  }

  Token lArrowToken = ctx.getToken();
  if (lArrowToken.getID() == Token::LArrow) {
    ctx.eatToken();
  } else {
    return callee;
  }

  Token lParenToken = ctx.getToken();
  if (lParenToken.getID() == Token::LParen) {
    ParserResult args = parseBoundSeparatedList(
        ctx, Token::LParen, parseType, "type", Token::Comma, Token::RParen);
    if (!args.isGood()) {
      return ParserResult();
    }

    return Node::createTypeFunction(
        callee.getNode(), {args.getNode()}, lArrowToken.getRange());
  } else {
    ctx.errorUnexpectedToken("(");
    return ParserResult();
  }
}

ParserResult Parser::parseTypeGroup(ParserContext &ctx) {
  return parseBoundTerm(
      ctx,
      Token::LParen,
      parseType,
      "type",
      Token::RParen,
      [](Node *arg, Range range) { return Node::createTypeGroup(arg, range); });
}

ParserResult Parser::parseType(ParserContext &ctx) {
  return parseTypeFunction(ctx);
}

ParserResult Parser::parseExprSymbol(ParserContext &ctx) {
  return parseSymbol(ctx, parseTemplateEvalArg, [](Node *args, Range range) {
    return Node::createExprSymbol(
        Field::createString8(range.getText().c_str()), {args}, range);
  });
}

ParserResult Parser::parseExprLiteralUInt(ParserContext &ctx) {
  Token tokenInt = ctx.getToken();
  if (tokenInt.getID() == Token::Int) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  UInt tmp;
  if (!evalLiteralUInt(tokenInt.getRange(), tmp)) {
    return ParserResult();
  }

  return ParserResult(Node::createExprLiteralUInt(
      Node::createTypeAtomicUInt64(), tmp, tokenInt.getRange()));
}

ParserResult Parser::parseExprLiteralReal(ParserContext &ctx) {
  Token tokenInt = ctx.getToken();
  if (tokenInt.getID() == Token::Real) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  Real tmp;
  if (!evalLiteralReal(tokenInt.getRange(), tmp)) {
    return ParserResult();
  }

  return ParserResult(Node::createExprLiteralReal(
      Node::createTypeAtomicReal(), tmp, tokenInt.getRange()));
}

ParserResult Parser::parseExprGroup(ParserContext &ctx) {
  return parseBoundTerm(
      ctx,
      Token::LParen,
      parseExpr,
      "value",
      Token::RParen,
      [](Node *arg, Range range) { return Node::createExprGroup(arg, range); });
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
                     {{Token::Period, [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprAccess({lhs, rhs}, range);
                       }}});
}

ParserResult Parser::parseExprAccessUnary(ParserContext &ctx) {
  return parseUnaryRight(ctx,
                         parseExprAccess,
                         "value",
                         {{Token::Period, [](Node *arg, Range range) {
                             return Node::createExprAccessUnary(arg, range);
                           }}});
}

ParserResult Parser::parseExprCall(ParserContext &ctx) {
  ParserResult callee = ctx.parse(parseExprAccessUnary);
  if (!callee.isGood()) {
    return ParserResult();
  }

  Token lParenToken = ctx.getToken();
  if (lParenToken.getID() == Token::LParen) {
    ParserResult args = parseBoundSeparatedList(
        ctx, Token::LParen, parseExpr, "value", Token::Comma, Token::RParen);
    if (!args.isGood()) {
      return ParserResult();
    }

    return Node::createExprCall(
        callee.getNode(), {args.getNode()}, lParenToken.getRange());
  } else {
    return callee;
  }
}

ParserResult Parser::parseExprUnaryRight(ParserContext &ctx) {
  return parseUnaryRight(ctx,
                         parseExprCall,
                         "value",
                         {{Token::Inc,
                           [](Node *arg, Range range) {
                             return Node::createExprIncPre(arg, range);
                           }},
                          {Token::Dec,
                           [](Node *arg, Range range) {
                             return Node::createExprDecPre(arg, range);
                           }},
                          {Token::BitNot, [](Node *arg, Range range) {
                             return Node::createExprBitNot(arg, range);
                           }}});
}

ParserResult Parser::parseExprUnaryLeft(ParserContext &ctx) {
  return parseUnaryLeft(ctx,
                        parseExprUnaryRight,
                        "value",
                        {{Token::Inc,
                          [](Node *arg, Range range) {
                            return Node::createExprIncPost(arg, range);
                          }},
                         {Token::Dec, [](Node *arg, Range range) {
                            return Node::createExprDecPost(arg, range);
                          }}});
}

ParserResult Parser::parseExprExp(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprUnaryLeft,
                     "value",
                     {{Token::Exp, [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprExp(lhs, rhs, range);
                       }}});
}

ParserResult Parser::parseExprMul(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprExp,
                     "value",
                     {{Token::Mul,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprMul({lhs, rhs}, range);
                       }},
                      {Token::Div,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprDiv(lhs, rhs, range);
                       }},
                      {Token::DivInt,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprDivInt(lhs, rhs, range);
                       }},
                      {Token::DivReal, [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprDivReal(lhs, rhs, range);
                       }}});
}

ParserResult Parser::parseExprAdd(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprMul,
                     "value",
                     {{Token::Add,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprAdd({lhs, rhs}, range);
                       }},
                      {Token::Sub, [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprSub(lhs, rhs, range);
                       }}});
}

ParserResult Parser::parseExprMod(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprAdd,
                     "value",
                     {{Token::Mod, [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprMod(lhs, rhs, range);
                       }}});
}

ParserResult Parser::parseExprBitShR(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprMod,
                     "value",
                     {{Token::BitShR, [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprBitShR(lhs, rhs, range);
                       }}});
}

ParserResult Parser::parseExprBitShL(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprBitShR,
                     "value",
                     {{Token::BitShL, [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprBitShL(lhs, rhs, range);
                       }}});
}

ParserResult Parser::parseExprBitAnd(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprBitShL,
                     "value",
                     {{Token::BitAnd, [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprBitAnd({lhs, rhs}, range);
                       }}});
}

ParserResult Parser::parseExprBitOr(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprBitAnd,
                     "value",
                     {{Token::BitOr,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprBitOr({lhs, rhs}, range);
                       }},
                      {Token::BitXor, [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprBitXor({lhs, rhs}, range);
                       }}});
}

ParserResult Parser::parseExprCompare(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprBitOr,
                     "value",
                     {{Token::LT,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprLT(lhs, rhs, range);
                       }},
                      {Token::LE,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprLE(lhs, rhs, range);
                       }},
                      {Token::GT,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprGT(lhs, rhs, range);
                       }},
                      {Token::GE,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprGE(lhs, rhs, range);
                       }},
                      {Token::NE,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprNE(lhs, rhs, range);
                       }},
                      {Token::EQ, [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprEQ(lhs, rhs, range);
                       }}});
}

ParserResult Parser::parseExprBoolNot(ParserContext &ctx) {
  return parseUnaryRight(ctx,
                         parseExprCompare,
                         "value",
                         {{Token::KWNot, [](Node *arg, Range range) {
                             return Node::createExprBoolNot(arg, range);
                           }}});
}

ParserResult Parser::parseExprBoolAnd(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprBoolNot,
                     "value",
                     {{Token::KWAnd, [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprBoolAnd({lhs, rhs}, range);
                       }}});
}

ParserResult Parser::parseExprBoolOr(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprBoolAnd,
                     "value",
                     {{Token::KWOr, [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprBoolOr({lhs, rhs}, range);
                       }}});
}

ParserResult Parser::parseExprBoolImplies(ParserContext &ctx) {
  return parseBinary(
      ctx,
      parseExprBoolOr,
      "value",
      {{Token::BoolImplies, [](Node *lhs, Node *rhs, Range range) {
          return Node::createExprBoolImplies({lhs, rhs}, range);
        }}});
}

ParserResult Parser::parseExprAssign(ParserContext &ctx) {
  return parseBinary(ctx,
                     parseExprBoolImplies,
                     "value",
                     {{Token::AddAssign,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprAddAssign(lhs, rhs, range);
                       }},
                      {Token::SubAssign,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprSubAssign(lhs, rhs, range);
                       }},
                      {Token::MulAssign,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprMulAssign(lhs, rhs, range);
                       }},
                      {Token::ExpAssign,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprExpAssign(lhs, rhs, range);
                       }},
                      {Token::DivAssign,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprDivAssign(lhs, rhs, range);
                       }},
                      {Token::DivIntAssign,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprDivIntAssign(lhs, rhs, range);
                       }},
                      {Token::DivRealAssign,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprDivRealAssign(lhs, rhs, range);
                       }},
                      {Token::ModAssign,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprModAssign(lhs, rhs, range);
                       }},
                      {Token::BitAndAssign,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprBitAndAssign(lhs, rhs, range);
                       }},
                      {Token::BitOrAssign,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprBitOrAssign(lhs, rhs, range);
                       }},
                      {Token::BitXorAssign,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprBitXorAssign(lhs, rhs, range);
                       }},
                      {Token::BitShLAssign,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprBitShLAssign(lhs, rhs, range);
                       }},
                      {Token::BitShRAssign,
                       [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprBitShRAssign(lhs, rhs, range);
                       }},
                      {Token::Assign, [](Node *lhs, Node *rhs, Range range) {
                         return Node::createExprAssign(lhs, rhs, range);
                       }}});
}

ParserResult Parser::parseExpr(ParserContext &ctx) {
  return parseExprAssign(ctx);
}

ParserResult Parser::parseStmtEmpty(ParserContext &ctx) {
  Token tokenSemicolon = ctx.getToken();
  if (tokenSemicolon.getID() == Token::Semicolon) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  return ParserResult(Node::createStmtEmpty(tokenSemicolon.getRange()));
}

ParserResult Parser::parseStmtExpr(ParserContext &ctx) {
  ParserResult arg = ctx.parse(parseExpr);
  if (!arg.isGood()) {
    return ParserResult();
  }

  Token tokenSemicolon = ctx.getToken();
  if (tokenSemicolon.getID() == Token::Semicolon) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken(";");
    return ParserResult();
  }

  return ParserResult(
      Node::createStmtExpr(arg.getNode(), tokenSemicolon.getRange()));
}

ParserResult Parser::parseStmtDecl(ParserContext &ctx) {
  ParserResult arg = ctx.parse(parseDecl);
  if (!arg.isGood()) {
    return ParserResult();
  }

  return ParserResult(
      Node::createStmtDecl(arg.getNode(), arg.getNode()->getRange()));
}

ParserResult Parser::parseStmtReturn(ParserContext &ctx) {
  Token tokenKWReturn = ctx.getToken();
  if (tokenKWReturn.getID() == Token::KWReturn) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  Token tokenLParen = ctx.getToken();
  if (tokenLParen.getID() == Token::LParen) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken("(");
    return ParserResult();
  }

  ParserResult arg;

  Token tokenRParen = ctx.getToken();
  if (tokenRParen.getID() == Token::RParen) {
    ctx.eatToken();
  } else {
    arg = ctx.parse(parseExpr);
    if (!arg.isGood()) {
      ctx.errorUnexpectedToken("value");
      return ParserResult();
    }

    tokenRParen = ctx.getToken();
    if (tokenRParen.getID() == Token::RParen) {
      ctx.eatToken();
    } else {
      ctx.errorUnexpectedToken("closing )");
      return ParserResult();
    }
  }

  Token tokenSemicolon = ctx.getToken();
  if (tokenSemicolon.getID() == Token::Semicolon) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken(";");
    return ParserResult();
  }

  return ParserResult(
      Node::createStmtReturn(arg.getNode(), tokenSemicolon.getRange()));
}

ParserResult Parser::parseStmtContinue(ParserContext &ctx) {
  Token tokenKWContinue = ctx.getToken();
  if (tokenKWContinue.getID() == Token::KWContinue) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  Token tokenLParen = ctx.getToken();
  if (tokenLParen.getID() == Token::LParen) {
    ctx.eatToken();
  } else if (tokenLParen.getID() == Token::Semicolon) {
    ctx.eatToken();
    return ParserResult(Node::createStmtContinue(tokenKWContinue.getRange()));
  } else {
    ctx.errorUnexpectedToken("(");
    return ParserResult();
  }

  Token tokenName;

  Token tokenRParen = ctx.getToken();
  if (tokenRParen.getID() == Token::RParen) {
    ctx.eatToken();
  } else {
    tokenName = ctx.getToken();
    if (tokenName.getID() == Token::String) {
      ctx.eatToken();
    } else {
      tokenName = Token();
    }

    tokenRParen = ctx.getToken();
    if (tokenRParen.getID() == Token::RParen) {
      ctx.eatToken();
    } else {
      ctx.errorUnexpectedToken("closing )");
      return ParserResult();
    }
  }

  Token tokenSemicolon = ctx.getToken();
  if (tokenSemicolon.getID() == Token::Semicolon) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken(";");
    return ParserResult();
  }

  if (tokenName.isGood()) {
    return ParserResult(Node::createStmtContinue(
        Field::createString8(tokenName.getRange().getText().c_str()),
        tokenSemicolon.getRange()));
  } else {
    return ParserResult(Node::createStmtContinue(tokenSemicolon.getRange()));
  }
}

ParserResult Parser::parseStmtBreak(ParserContext &ctx) {
  Token tokenKWBreak = ctx.getToken();
  if (tokenKWBreak.getID() == Token::KWBreak) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  Token tokenLParen = ctx.getToken();
  if (tokenLParen.getID() == Token::LParen) {
    ctx.eatToken();
  } else if (tokenLParen.getID() == Token::Semicolon) {
    ctx.eatToken();
    return ParserResult(Node::createStmtBreak(tokenKWBreak.getRange()));
  } else {
    ctx.errorUnexpectedToken("(");
    return ParserResult();
  }

  Token tokenName;

  Token tokenRParen = ctx.getToken();
  if (tokenRParen.getID() == Token::RParen) {
    ctx.eatToken();
  } else {
    tokenName = ctx.getToken();
    if (tokenName.getID() == Token::String) {
      ctx.eatToken();
    } else {
      tokenName = Token();
    }

    tokenRParen = ctx.getToken();
    if (tokenRParen.getID() == Token::RParen) {
      ctx.eatToken();
    } else {
      ctx.errorUnexpectedToken("closing )");
      return ParserResult();
    }
  }

  Token tokenSemicolon = ctx.getToken();
  if (tokenSemicolon.getID() == Token::Semicolon) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken(";");
    return ParserResult();
  }

  if (tokenName.isGood()) {
    return ParserResult(Node::createStmtBreak(
        Field::createString8(tokenName.getRange().getText().c_str()),
        tokenSemicolon.getRange()));
  } else {
    return ParserResult(Node::createStmtBreak(tokenSemicolon.getRange()));
  }
}

ParserResult Parser::parseStmtIf(ParserContext &ctx) {
  Token tokenKWIf = ctx.getToken();
  if (tokenKWIf.getID() == Token::KWIf) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  ParserResult condition =
      parseBoundTerm(ctx,
                     Token::LParen,
                     parseExpr,
                     "value",
                     Token::RParen,
                     [](Node *arg, Range range) { return arg; });
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
  if (tokenKWElse.getID() == Token::KWElse) {
    ctx.eatToken();

    ParserResult _else = ctx.parse(parseStmt);
    if (!_else.isGood()) {
      ctx.errorUnexpectedToken("else clause");
      return ParserResult();
    }

    return ParserResult(Node::createStmtIf(condition.getNode(),
                                           then.getNode(),
                                           _else.getNode(),
                                           tokenKWIf.getRange()));
  } else {
    return ParserResult(Node::createStmtIf(
        condition.getNode(), then.getNode(), tokenKWIf.getRange()));
  }
}

ParserResult Parser::parseStmtWhile(ParserContext &ctx) {
  Token tokenKWWhile = ctx.getToken();
  if (tokenKWWhile.getID() == Token::KWWhile) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  ParserResult condition =
      parseBoundTerm(ctx,
                     Token::LParen,
                     parseExpr,
                     "value",
                     Token::RParen,
                     [](Node *arg, Range range) { return arg; });
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
      condition.getNode(), body.getNode(), tokenKWWhile.getRange()));
}

ParserResult Parser::parseStmtFor(ParserContext &ctx) {
  Token tokenFor = ctx.getToken();
  if (tokenFor.getID() == Token::KWFor) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  Token tokenLParen = ctx.getToken();
  if (tokenLParen.getID() == Token::LParen) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken("(");
    return ParserResult();
  }

  ParserResult res =
      ParserResult(Node::createStmtFor({}, nullptr, {},
      tokenFor.getRange()));

  Node *front = nullptr;
  Node *back = nullptr;

  bool endedCorrectly = false;
  while (ctx.areMoreTokens()) {
    Token tokenSepFirst = ctx.getToken();
    if (!tokenSepFirst.isGood()) {
      ctx.errorUnexpectedToken("variable declaration or ;");
      return ParserResult();
    } else if (tokenSepFirst.getID() == Token::Semicolon) {
      ctx.eatToken();
      endedCorrectly = true;
      break;
    } else if (tokenSepFirst.getID() == Token::Comma) {
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
  if (tokenSepSecond.getID() != Token::Semicolon) {
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
  if (tokenSepSecond.getID() == Token::Semicolon) {
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
    } else if (tokenSepThird.getID() == Token::RParen) {
      endedCorrectly = true;
      ctx.eatToken();
      break;
    } else if (tokenSepThird.getID() == Token::Comma) {
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
  if (tokenForEach.getID() == Token::KWForEach) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  Token tokenLParen = ctx.getToken();
  if (tokenLParen.getID() == Token::LParen) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken("(");
    return ParserResult();
  }

  ParserResult res =
      ParserResult(Node::createStmtForEach({}, {}, tokenForEach.getRange()));

  Node *front = nullptr;
  Node *back = nullptr;

  bool endedCorrectly = false;
  while (ctx.areMoreTokens()) {
    Token tokenSepFirst = ctx.getToken();
    if (!tokenSepFirst.isGood()) {
      ctx.errorUnexpectedToken("variable declaration or ;");
      return ParserResult();
    } else if (tokenSepFirst.getID() == Token::Semicolon) {
      ctx.eatToken();
      endedCorrectly = true;
      break;
    } else if (tokenSepFirst.getID() == Token::Comma) {
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
      if (tokenSepFirst.getID() == Token::Comma) {
        continue;
      } else if (tokenSepFirst.getID() == Token::Semicolon) {
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
    } else if (tokenSepThird.getID() == Token::RParen) {
      ctx.eatToken();
      endedCorrectly = true;
      break;
    } else if (tokenSepThird.getID() == Token::Comma) {
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
      if (tokenSepThird.getID() == Token::RParen) {
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
  if (tokenLBrace.getID() == Token::LBrace) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  ParserResult res =
      ParserResult(Node::createStmtBlock(tokenLBrace.getRange()));

  Node *front = nullptr;
  Node *back = nullptr;

  bool endedCorrectly = false;
  while (ctx.areMoreTokens()) {
    Token tokenSep = ctx.getToken();
    if (!tokenSep.isGood()) {
      ctx.errorUnexpectedToken("statement or }");
      return ParserResult();
    } else if (tokenSep.getID() == Token::RBrace) {
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
  if (tokenSymbol.getID() == Token::Symbol) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken("symbol");
    return ParserResult();
  }
	
	ParserResult res = ParserResult(Node::createDeclVariable(type.getNode(), Field::createString8(tokenSymbol.getRange().getText().c_str())));

	Token tokenLT = ctx.getToken();
  if (tokenLT.getID() == Token::LT) {
    ParserResult templateArgs =
        parseTemplateList(ctx, parseDeclVariableNoSemicolon, "template arg");
    if (templateArgs.isGood()) {
      res.getNode()->getField(Node::FieldTag::DeclVariable_TemplateDeclArgs)->setNode(templateArgs.getNode());
    } else {
      return ParserResult();
    }
  }

	Token tokenSep = ctx.getToken();
	if (tokenSep.getID() == Token::Assign) {
		ctx.eatToken();
		ParserResult init = ctx.parse(parseExpr);
		if (!init.isGood()) {
      ctx.errorUnexpectedToken("value");
			return ParserResult();
		}

		res.getNode()->getField(Node::FieldTag::DeclVariable_Initial)->setNode(init.getNode());
	}

	return res;
}

ParserResult Parser::parseDeclVariable(ParserContext &ctx) {
  ParserResult res = ctx.parse(parseDeclVariableNoSemicolon);
  if (!res.isGood()) {
    return ParserResult();
  }

  Token tokenSymbol = ctx.getToken();
  if (tokenSymbol.getID() == Token::Semicolon) {
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
  if (tokenSymbol.getID() == Token::Symbol) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken("symbol");
    return ParserResult();
  }
  
  ParserResult res = ParserResult(Node::createDeclFunction(type.getNode(), Field::createString8(tokenSymbol.getRange().getText().c_str()), {}));

  Token tokenLT = ctx.getToken();
  if (tokenLT.getID() == Token::LT) {
    ParserResult templateArgs =
        parseTemplateList(ctx, parseDeclVariableNoSemicolon, "template arg");
    if (templateArgs.isGood()) {
      res.getNode()->getField(Node::FieldTag::DeclFunction_TemplateDeclArgs)->setNode(templateArgs.getNode());
    } else {
      return ParserResult();
    }
  }

  Token tokenLParen = ctx.getToken();
  if (tokenLParen.getID() == Token::LParen) {
   ParserResult args = parseBoundSeparatedList(ctx, Token::LParen, parseDeclVariableNoSemicolon, "arg", Token::Comma, Token::RParen);
   if (!args.isGood()) {
    return ParserResult();
   } else {
    res.getNode()->getField(Node::FieldTag::DeclFunction_Args)->setNode(args.getNode());
   }
  } else {
    return ParserResult();
  }

  Token tokenSep = ctx.getToken();
  if (!tokenSep.isGood()) {
    ctx.errorUnexpectedToken("function body");
    return ParserResult();
  } else if (tokenSep.getID() == Token::Semicolon) {
    ctx.eatToken();
    return res;
  } else if (tokenSep.getID() == Token::Assign) {
    ctx.eatToken();
    ParserResult body = ctx.parse(parseStmtExpr);
    if (!body.isGood()) {
      ctx.errorUnexpectedToken("value");
      return ParserResult();
    }

    res.getNode()->getField(Node::FieldTag::DeclFunction_Body)->setNode(body.getNode());
  } else {
    ParserResult body = ctx.parse(parseStmtBlock);
    if (!body.isGood()) {
      ctx.errorUnexpectedToken("body");
      return ParserResult();
    }

    res.getNode()->getField(Node::FieldTag::DeclFunction_Body)->setNode(body.getNode());
  }

  return res;
}

ParserResult Parser::parseDeclClass(ParserContext &ctx) {
  Token tokenKWClass = ctx.getToken();
  if (tokenKWClass.getID() == Token::KWClass) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  Token tokenSymbol = ctx.getToken();
  if (tokenSymbol.getID() == Token::Symbol) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken("symbol");
    return ParserResult();
  }
  
  ParserResult res = ParserResult(Node::createDeclClass(Field::createString8(tokenSymbol.getRange().getText().c_str())));

  Token tokenLT = ctx.getToken();
  if (tokenLT.getID() == Token::LT) {
    ParserResult templateArgs =
        parseTemplateList(ctx, parseDeclVariableNoSemicolon, "template arg");
    if (templateArgs.isGood()) {
      res.getNode()->getField(Node::FieldTag::DeclClass_TemplateDeclArgs)->setNode(templateArgs.getNode());
    } else {
      return ParserResult();
    }
  }

  Token tokenKWInherits = ctx.getToken();
  if (tokenKWInherits.getID() == Token::KWInherits) {
    ctx.eatToken();

    Node *front = nullptr;
    Node *back = nullptr;

    bool endedCorrectly = false;
    while (ctx.areMoreTokens()) {
      Token tokenSep = ctx.getToken();
      if (!tokenSep.isGood()) {
        ctx.errorUnexpectedToken("type, {, or ;");
        return ParserResult();
      } else if (tokenSep.getID() == Token::LBrace) {
        ctx.eatToken();
        endedCorrectly = true;
        break;
      } else if (tokenSep.getID() == Token::Semicolon) {
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
        if (tokenSep.getID() == Token::Comma) {
          ctx.eatToken();
          continue;
        } else if (tokenSep.getID() == Token::LBrace) {
          endedCorrectly = true;
          break;
        } else if (tokenSep.getID() == Token::Semicolon) {
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
  } else if (tokenSep.getID() == Token::Semicolon) {
    ctx.eatToken();
    return res;
  } else if (tokenSep.getID() == Token::LBrace) {
    ctx.eatToken();
    
    Node *front = nullptr;
    Node *back = nullptr;

    bool endedCorrectly = false;
    while (ctx.areMoreTokens()) {
      Token tokenSep = ctx.getToken();
      if (!tokenSep.isGood()) {
        ctx.errorUnexpectedToken("declaration or }");
        return ParserResult();
      } else if (tokenSep.getID() == Token::RBrace) {
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
  if (tokenKWNamespace.getID() == Token::KWNamespace) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  Token tokenSymbol = ctx.getToken();
  if (tokenSymbol.getID() == Token::Symbol) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken("symbol");
    return ParserResult();
  }
  
  ParserResult res = ParserResult(Node::createDeclNamespace(Field::createString8(tokenSymbol.getRange().getText().c_str())));

  Token tokenSep = ctx.getToken();
  if (!tokenSep.isGood()) {
    ctx.errorUnexpectedToken("{");
    return ParserResult();
  } else if (tokenSep.getID() == Token::LBrace) {
    ctx.eatToken();
    
    Node *front = nullptr;
    Node *back = nullptr;

    bool endedCorrectly = false;
    while (ctx.areMoreTokens()) {
      Token tokenSep = ctx.getToken();
      if (!tokenSep.isGood()) {
        ctx.errorUnexpectedToken("declaration or }");
        return ParserResult();
      } else if (tokenSep.getID() == Token::RBrace) {
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

    res.getNode()->getField(Node::FieldTag::DeclNamespace_Members)->setNode(front);

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
	return ctx.parseAny({
		parseDeclClass,
		parseDeclNamespace,
		parseDeclFunction,
		parseDeclVariable
	});
}

ParserResult Parser::parseImport(ParserContext &ctx) {
	Token tokenKWImport = ctx.getToken();
  if (tokenKWImport.getID() == Token::KWImport) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  Token tokenLParen = ctx.getToken();
  if (tokenLParen.getID() == Token::LParen) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken("(");
    return ParserResult();
  }

	Token tokenString = ctx.getToken();
  if (tokenString.getID() == Token::String) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken("path");
    return ParserResult();
  }

	Token tokenRParen = ctx.getToken();
  if (tokenRParen.getID() == Token::RParen) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken(")");
    return ParserResult();
  }

	Token tokenSemicolon = ctx.getToken();
  if (tokenSemicolon.getID() == Token::Semicolon) {
    ctx.eatToken();
  } else {
    ctx.errorUnexpectedToken(";");
    return ParserResult();
  }

	std::string path;
	if (!evalLiteralString8(tokenString.getRange(), path)) {
		return ParserResult();
	}

	return ParserResult(Node::createImport(Field::createString8(path.c_str()), tokenKWImport.getRange()));
}

ParserResult Parser::parseUnit(ParserContext &ctx) {
  Node *front = nullptr;
  Node *back = nullptr;

  while (ctx.areMoreTokens()) {
    ParserResult tmp = ctx.parseAny({
      parseImport,
      parseDecl
    });

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
