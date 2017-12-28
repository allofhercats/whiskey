#include "Module.inc"

#include <whiskey/Parsing/Parser.hpp>

namespace whiskey {
ParserResult Parser::parseBoundList(ParserContext &ctx,
                                    Token::ID left,
                                    ParserContext::Rule rule,
                                    const std::string &expected,
                                    Token::ID right) {
  Token leftToken = ctx.getToken();
  if (leftToken.getID() == left) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  ParserContext save = ctx;

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
      ctx = save;
      ctx.errorUnexpectedToken(expected);
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
    ctx = save;
    std::stringstream ss;
    ss << "closing ";
    Token::printTokenID(ss, right);
    ctx.errorUnexpectedToken(ss.str());
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
  Token leftToken = ctx.getToken();
  if (leftToken.getID() == left) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  ParserContext save = ctx;

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
      ctx = save;
      std::stringstream ss;
      Token::printTokenID(ss, sep);
      ctx.errorUnexpectedToken(ss.str());
      return ParserResult();
    }

    ParserResult arg = ctx.parse(rule);
    if (!arg.isGood()) {
      ctx = save;
      ctx.errorUnexpectedToken(expected);
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
    } else if (rightToken.getID() == right) {
      continue;
    } else {
      ctx = save;
      std::stringstream ss;
      Token::printTokenID(ss, sep);
      ctx.errorUnexpectedToken(ss.str());
      return ParserResult();
    }
  }

  if (!endedCorrectly) {
    ctx = save;
    std::stringstream ss;
    ss << "closing ";
    Token::printTokenID(ss, right);
    ctx.errorUnexpectedToken(ss.str());
    return ParserResult();
  }

  return ParserResult(front);
}

ParserResult Parser::parseTemplateList(ParserContext &ctx,
                                       ParserContext::Rule rule,
                                       const std::string &expected) {
  Token leftToken = ctx.getToken();
  if (leftToken.getID() == Token::LT) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  ParserContext save = ctx;

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
      ctx = save;
      ctx.errorUnexpectedToken(",");
      return ParserResult();
    }

    ParserResult arg = ctx.parse(rule);
    if (!arg.isGood()) {
      ctx = save;
      ctx.errorUnexpectedToken(expected);
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
      ctx = save;
      ctx.errorUnexpectedToken(",");
      return ParserResult();
    }
  }

  if (!endedCorrectly) {
    ctx = save;
    ctx.errorUnexpectedToken("closing >");
    return ParserResult();
  }

  return ParserResult(front);
}

ParserResult Parser::parseSymbol(ParserContext &ctx,
                                 ParserContext::Rule templateArgRule,
                                 std::function<Node *(Node *, Range)> builder) {
  Token symbolToken = ctx.getToken();
  if (symbolToken.getID() == Token::Symbol) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  Token tokenLT = ctx.getToken();
  if (tokenLT.getID() == Token::LT) {
    ParserResult templateArgs =
        parseTemplateList(ctx, templateArgRule, "template arg");
    if (templateArgs.isGood()) {
      return builder(templateArgs.getNode(), symbolToken.getRange());
    } else {
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
  Token opToken = ctx.getToken();
  ParserContext save = ctx;
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

  ParserResult res = ctx.parse(baseRule);
  if (res.isGood()) {
    bool gotOp = false;

    ParserContext save = ctx;

    while (true) {
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
  ParserResult lhs = ctx.parse(lhsRule);
  if (!lhs.isGood()) {
    return ParserResult();
  }

  ParserContext save = ctx;

  for (const std::pair<Token::ID, std::function<Node *(Node *, Node *, Range)>>
           &kv : builders) {
    ctx = save;
    Token opToken = ctx.getToken();
    if (opToken.getID() == kv.first) {
      ctx.eatToken();

      ParserResult rhs = ctx.parse([&](ParserContext &ctx) {
        return parseBinary(ctx, lhsRule, expected, builders);
      });
      if (!rhs.isGood()) {
        ctx.errorUnexpectedToken(expected);
        return ParserResult();
      }

      return ParserResult(
          kv.second(lhs.getNode(), rhs.getNode(), opToken.getRange()));
    }
  }

  ctx = save;
  return lhs;
}

ParserResult
Parser::parseBoundTerm(ParserContext &ctx,
                       Token::ID left,
                       ParserContext::Rule rule,
                       const std::string &expected,
                       Token::ID right,
                       std::function<Node *(Node *, Range)> builder) {
  Token leftToken = ctx.getToken();
  if (leftToken.getID() == left) {
    ctx.eatToken();
  } else {
    return ParserResult();
  }

  ParserContext save = ctx;

  ParserResult rtn = ctx.parse(parseType);
  if (!rtn.isGood()) {
    ctx = save;
    ctx.errorUnexpectedToken(expected);
    return ParserResult();
  }

  Token rightToken = ctx.getToken();
  if (rightToken.getID() == Token::RParen) {
    ctx.eatToken();
  } else {
    ctx = save;
    std::stringstream ss;
    ss << "closing ";
    Token::printTokenID(ss, right);
    ctx.errorUnexpectedToken(ss.str());
    return ParserResult();
  }

  ctx = save;
  return ParserResult(builder(rtn.getNode(), leftToken.getRange()));
}

ParserResult Parser::parseTemplateEvalArg(ParserContext &ctx) {
  return ctx.parseAny({parseType, parseExpr});
}

ParserResult Parser::parseTypeSymbol(ParserContext &ctx) {
  return parseSymbol(ctx, parseTemplateEvalArg, [](Node *args, Range range) {
    return Node::createTypeSymbol(
        Field::createString8(range.getText().c_str()), {args}, range);
  });
}

ParserResult Parser::parseTypeTerm(ParserContext &ctx) {
  return ctx.parseAny({parseTypeSymbol, parseTypeGroup});
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
      ctx, parseTypeTerm, "type", {{Token::Period, [](Node *arg, Range range) {
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
                         parseExprTerm,
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
    ctx.errorUnexpectedToken("(");
    return ParserResult();
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

// ParserResult Parser::parseStmtDecl(ParserContext &ctx) {
//   ParserResult arg = ctx.parse(parseDecl);
//   if (!arg.isGood()) {
//     return ParserResult();
//   }

//   Token tokenSemicolon = ctx.getToken();
//   if (tokenSemicolon.getID() == Token::Semicolon) {
//     ctx.eatToken();
//   } else {
//     ctx.errorUnexpectedToken(";");
//     return ParserResult();
//   }

//   return ParserResult(
//       Node::createStmtDecl(arg.getNode(), tokenSemicolon.getRange()));
// }

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

// ParserResult Parser::parseStmtFor(ParserContext &ctx) {
//   Token tokenFor = ctx.getToken();
//   if (tokenFor.getID() == Token::KWFor) {
//     ctx.eatToken();
//   } else {
//     return ParserResult();
//   }

//   Token tokenLParen = ctx.getToken();
//   if (tokenLParen.getID() == Token::LParen) {
//     ctx.eatToken();
//   } else {
//     ctx.errorUnexpectedToken("(");
//     return ParserResult();
//   }

//   ParserResult res =
//       ParserResult(Node::createStmtFor({}, nullptr, {},
//       tokenFor.getRange()));

//   Node *front = nullptr;
//   Node *back = nullptr;

//   bool endedCorrectly = false;
//   while (ctx.areMoreTokens()) {
//     Token tokenSepFirst = ctx.getToken();
//     if (!tokenSepFirst.isGood()) {
//       ctx.errorUnexpectedToken("variable declaration or ;");
//       return ParserResult();
//     } else if (tokenSepFirst.getID() == Token::Semicolon) {
//       ctx.eatToken();
//       endedCorrectly = true;
//       break;
//     } else if (tokenSepFirst.getID() == Token::Comma) {
//       ctx.eatToken();
//     } else {
//       ParserResult decl = ctx.parse(parseDeclVariable);
//       if (!decl.isGood()) {
//         ctx.errorUnexpectedToken("variable declaration");
//         return ParserResult();
//       }
//       if (front == nullptr) {
//         front = back = decl.getNode();
//       } else {
//         back->setNext(decl.getNode());
//         back = decl.getNode();
//       }
//     }
//   }

//   res.getNode()->getField(Node::FieldTag::StmtFor_Decls)->setNode(front);

//   if (!endedCorrectly) {
//     ctx.errorUnexpectedToken(";");
//     return ParserResult();
//   }

//   ParserResult cond = ctx.parse(parseExpr);
//   if (!cond.isGood()) {
//     ctx.errorUnexpectedToken("condition");
//     return ParserResult();
//   }

//   res.getNode()
//       ->getField(Node::FieldTag::StmtFor_Condition)
//       ->setNode(cond.getNode());

//   Token tokenSepSecond = ctx.getToken();
//   if (tokenSepSecond.getID() == Token::Semicolon) {
//     ctx.eatToken();
//   } else {
//     ctx.errorUnexpectedToken(";");
//     return ParserResult();
//   }

//   front = back = nullptr;

//   endedCorrectly = false;
//   while (ctx.areMoreTokens()) {
//     Token tokenSepThird = ctx.getToken();
//     if (!tokenSepThird.isGood()) {
//       ctx.errorUnexpectedToken("expression or )");
//     } else if (tokenSepThird.getID() == Token::RParen) {
//       ctx.eatToken();
//       break;
//     } else if (tokenSepThird.getID() == Token::Comma) {
//       ctx.eatToken();
//     } else {
//       ParserResult step = ctx.parse(parseExpr);
//       if (!step.isGood()) {
//         ctx.errorUnexpectedToken("expression");
//         return ParserResult();
//       }
//       if (front == nullptr) {
//         front = back = step.getNode();
//       } else {
//         back->setNext(step.getNode());
//         back = step.getNode();
//       }
//     }
//   }

//   res.getNode()->getField(Node::FieldTag::StmtFor_Steps)->setNode(front);

//   if (!endedCorrectly) {
//     ctx.errorUnexpectedToken(")");
//     return ParserResult();
//   }

//   ParserResult body = ctx.parse(parseStmt);
//   if (!body.isGood()) {
//     ctx.errorUnexpectedToken("body clause");
//     return ParserResult();
//   }

//   res.getNode()
//       ->getField(Node::FieldTag::StmtFor_Body)
//       ->setNode(body.getNode());

//   return res;
// }

// ParserResult Parser::parseStmtForEach(ParserContext &ctx) {
//   Token tokenFor = ctx.getToken();
//   if (tokenFor.getID() == Token::KWFor) {
//     ctx.eatToken();
//   } else {
//     return ParserResult();
//   }

//   Token tokenLParen = ctx.getToken();
//   if (tokenLParen.getID() == Token::LParen) {
//     ctx.eatToken();
//   } else {
//     ctx.errorUnexpectedToken("(");
//     return ParserResult();
//   }

//   ParserResult res =
//       ParserResult(Node::createStmtForEach({}, {}, tokenFor.getRange()));

//   Node *front = nullptr;
//   Node *back = nullptr;

//   bool endedCorrectly = false;
//   while (ctx.areMoreTokens()) {
//     Token tokenSepFirst = ctx.getToken();
//     if (!tokenSepFirst.isGood()) {
//       ctx.errorUnexpectedToken("variable declaration or ;");
//       return ParserResult();
//     } else if (tokenSepFirst.getID() == Token::Semicolon) {
//       ctx.eatToken();
//       endedCorrectly = true;
//       break;
//     } else if (tokenSepFirst.getID() == Token::Comma) {
//       ctx.eatToken();
//     } else {
//       ParserResult decl = ctx.parse(parseDeclVariable);
//       if (!decl.isGood()) {
//         ctx.errorUnexpectedToken("variable declaration");
//         return ParserResult();
//       }
//       if (front == nullptr) {
//         front = back = decl.getNode();
//       } else {
//         back->setNext(decl.getNode());
//         back = decl.getNode();
//       }
//     }
//   }

//   res.getNode()->getField(Node::FieldTag::StmtForEach_Decls)->setNode(front);

//   if (!endedCorrectly) {
//     ctx.errorUnexpectedToken(";");
//     return ParserResult();
//   }

//   Token tokenSepSecond = ctx.getToken();
//   if (tokenSepSecond.getID() == Token::Semicolon) {
//     ctx.eatToken();
//   } else {
//     ctx.errorUnexpectedToken(";");
//     return ParserResult();
//   }

//   front = back = nullptr;

//   endedCorrectly = false;
//   while (ctx.areMoreTokens()) {
//     Token tokenSepThird = ctx.getToken();
//     if (!tokenSepThird.isGood()) {
//       ctx.errorUnexpectedToken("expression or )");
//     } else if (tokenSepThird.getID() == Token::RParen) {
//       ctx.eatToken();
//       break;
//     } else if (tokenSepThird.getID() == Token::Comma) {
//       ctx.eatToken();
//     } else {
//       ParserResult sequence = ctx.parse(parseExpr);
//       if (!sequence.isGood()) {
//         ctx.errorUnexpectedToken("expression");
//         return ParserResult();
//       }
//       if (front == nullptr) {
//         front = back = sequence.getNode();
//       } else {
//         back->setNext(sequence.getNode());
//         back = sequence.getNode();
//       }
//     }
//   }

//   res.getNode()
//       ->getField(Node::FieldTag::StmtForEach_Sequences)
//       ->setNode(front);

//   if (!endedCorrectly) {
//     ctx.errorUnexpectedToken(")");
//     return ParserResult();
//   }

//   ParserResult body = ctx.parse(parseStmt);
//   if (!body.isGood()) {
//     ctx.errorUnexpectedToken("body clause");
//     return ParserResult();
//   }

//   res.getNode()
//       ->getField(Node::FieldTag::StmtForEach_Body)
//       ->setNode(body.getNode());

//   return res;
// }

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
                       // parseStmtFor,
                       // parseStmtForEach,
                       parseStmtReturn,
                       parseStmtEmpty,
                       parseStmtExpr});
}

// ParserResult Parser::parseDeclVariable(ParserContext &ctx) {
// 	ParserResult type = ctx.expectParse(parseType, "type");
// 	if (!type.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenSymbol = ctx.tryToken(Token::Symbol);
// 	if (!tokenSymbol.isGood()) {
// 		return ParserResult();
// 	}

// 	ParserResult res = ParserResult(new DeclVariable(tokenSymbol.getRange(),
// type.getAST()->cloneAs<Type>(), tokenSymbol.getRange().getText()));

// 	Token tokenLBracket = ctx.tryToken(Token::LT);
// 	if (tokenLBracket.isGood()) {
// 		// put template args here
// 	}

// 	Token tokenSep = ctx.getToken();
// 	if (!tokenSep.isGood()) {
// 		ctx.errorUnexpectedToken("= or ;");
// 		return ParserResult();
// 	} else if (tokenSep.getID() == Token::Semicolon) {
// 		ctx.eatToken();
// 		return res;
// 	} else if (tokenSep.getID() == Token::Assign) {
// 		ctx.eatToken();
// 		ParserResult init = ctx.expectParse(parseExpr, "expression");
// 		if (!init.isGood()) {
// 			return ParserResult();
// 		}

// 		tokenSep = ctx.expectToken(Token::Semicolon, ";");
// 		if (!tokenSep.isGood()) {
// 			return ParserResult();
// 		}

// 		res.getAST()->as<DeclVariable>()->setInit(init.getAST()->cloneAs<Expr>());
// 	}

// 	return res;
// }

// ParserResult Parser::parseDeclFunction(ParserContext &ctx) {
// 	ParserResult type = ctx.expectParse(parseType, "type");
// 	if (!type.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenSymbol = ctx.tryToken(Token::Symbol);
// 	if (!tokenSymbol.isGood()) {
// 		return ParserResult();
// 	}

// 	ParserResult res = ParserResult(new DeclFunction(tokenSymbol.getRange(),
// type.getAST()->cloneAs<Type>(), tokenSymbol.getRange().getText()));

// 	Token tokenLBracket = ctx.tryToken(Token::LT);
// 	if (tokenLBracket.isGood()) {
// 		bool endedCorrectly = false;
// 		while (ctx.areMoreTokens()) {
// 			ParserResult arg = ctx.expectParse(parseDeclVariable,
// "template arg"); 			if (arg.isGood()) {
// 				res.getAST()->as<DeclFunction>()->getTemplateDeclArgs().push_back(arg.getAST()->cloneAs<DeclVariable>());
// 			}
// 			Token tokenSep = ctx.getToken();
// 			if (tokenSep.getID() == Token::Comma) {
// 				ctx.eatToken();
// 			} else if (tokenSep.getID() == Token::GT) {
// 				ctx.eatToken();
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::GE) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::Assign));
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::BitShR) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::GT));
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::BitShRAssign) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::GE));
// 				endedCorrectly = true;
// 				break;
// 			} else {
// 				ctx.errorUnexpectedToken(", or >");
// 				ctx.eatToken();
// 			}
// 		}

// 		if (!endedCorrectly) {
// 			ctx.errorUnexpectedToken("closing >");
// 			return ParserResult();
// 		}
// 	}

// 	Token tokenLBrace = ctx.expectToken(Token::LParen, "(");
// 	if (!tokenLBrace.isGood()) {
// 		return ParserResult();
// 	}

// 	bool endedCorrectly = false;
// 	while (ctx.areMoreTokens()) {
// 		Token tokenSep = ctx.getToken();
// 		if (!tokenSep.isGood()) {
// 			ctx.errorUnexpectedToken("argument or )");
// 			return ParserResult();
// 		} else if (tokenSep.getID() == Token::RParen) {
// 			ctx.eatToken();
// 			endedCorrectly = true;
// 			break;
// 		} else {
// 			ParserResult arg = ctx.expectParse(parseDeclVariable,
// "argument"); 			if (!arg.isGood()) {
// 				return ParserResult();
// 			}
// 			res.getAST()->as<DeclFunction>()->getArgs().push_back(arg.getAST()->cloneAs<DeclVariable>());
// 		}
// 	}

// 	if (!endedCorrectly) {
// 		ctx.errorUnexpectedToken(")");
// 		return ParserResult();
// 	}

// 	Token tokenSep = ctx.getToken();
// 	if (!tokenSep.isGood()) {
// 		ctx.errorUnexpectedToken("=, ;, or {");
// 		return ParserResult();
// 	} else if (tokenSep.getID() == Token::Semicolon) {
// 		ctx.eatToken();
// 		return res;
// 	} else if (tokenSep.getID() == Token::Assign) {
// 		ctx.eatToken();
// 		ParserResult init = ctx.expectParse(parseStmtExpr,
// "expression"); 		if (!init.isGood()) { 			return
// ParserResult();
// 		}

// 		res.getAST()->as<DeclFunction>()->setBody(init.getAST()->cloneAs<Stmt>());
// 	} else if (tokenSep.getID() == Token::LBrace) {
// 		ParserResult body = ctx.expectParse(parseStmtBlock, "body");
// 		if (!body.isGood()) {
// 			return ParserResult();
// 		}

// 		tokenSep = ctx.expectToken(Token::Semicolon, ";");
// 		if (!tokenSep.isGood()) {
// 			return ParserResult();
// 		}

// 		res.getAST()->as<DeclFunction>()->setBody(body.getAST()->cloneAs<Stmt>());
// 	} else {
// 		ctx.errorUnexpectedToken("=, ;, or {");
// 		return ParserResult();
// 	}

// 	return res;
// }

// ParserResult Parser::parseDeclClass(ParserContext &ctx) {
// 	Token tokenClass = ctx.tryToken(Token::KWClass);
// 	if (!tokenClass.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenSymbol = ctx.tryToken(Token::Symbol);
// 	if (!tokenSymbol.isGood()) {
// 		return ParserResult();
// 	}

// 	ParserResult res = ParserResult(new DeclClass(tokenSymbol.getRange(),
// tokenSymbol.getRange().getText()));

// 	Token tokenLBracket = ctx.tryToken(Token::LT);
// 	if (tokenLBracket.isGood()) {
// 		bool endedCorrectly = false;
// 		while (ctx.areMoreTokens()) {
// 			ParserResult arg = ctx.expectParse(parseDeclVariable,
// "template arg"); 			if (arg.isGood()) {
// 				res.getAST()->as<DeclClass>()->getTemplateDeclArgs().push_back(arg.getAST()->cloneAs<DeclVariable>());
// 			}
// 			Token tokenSep = ctx.getToken();
// 			if (tokenSep.getID() == Token::Comma) {
// 				ctx.eatToken();
// 			} else if (tokenSep.getID() == Token::GT) {
// 				ctx.eatToken();
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::GE) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::Assign));
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::BitShR) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::GT));
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::BitShRAssign) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::GE));
// 				endedCorrectly = true;
// 				break;
// 			} else {
// 				ctx.errorUnexpectedToken(", or >");
// 				ctx.eatToken();
// 			}
// 		}

// 		if (!endedCorrectly) {
// 			ctx.errorUnexpectedToken("closing >");
// 			return ParserResult();
// 		}
// 	}

// 	Token tokenSep = ctx.getToken();
// 	if (!tokenSep.isGood()) {
// 		ctx.errorUnexpectedToken("inherits or {");
// 		return ParserResult();
// 	} else if (tokenSep.getID() == Token::KWInherits) {
// 		ctx.eatToken();

// 		bool endedCorrectly = false;
// 		while (ctx.areMoreTokens()) {
// 			Token tokenSep = ctx.getToken();
// 			if (!tokenSep.isGood()) {
// 				ctx.errorUnexpectedToken("type or {");
// 				return ParserResult();
// 			} else if (tokenSep.getID() == Token::LBrace) {
// 				ctx.eatToken();
// 				endedCorrectly = true;
// 				break;
// 			} else {
// 				ParserResult arg = ctx.expectParse(parseType,
// "type"); 				if (!arg.isGood()) {
// 					return ParserResult();
// 				}
// 				res.getAST()->as<DeclClass>()->getInherits().push_back(arg.getAST()->cloneAs<Type>());
// 			}
// 		}

// 		if (!endedCorrectly) {
// 			ctx.errorUnexpectedToken("{");
// 			return ParserResult();
// 		}
// 	} else if (tokenSep.getID() == Token::LBrace) {
// 		ctx.eatToken();
// 	} else {
// 		ctx.errorUnexpectedToken("implements or {");
// 		return ParserResult();
// 	}

// 	bool endedCorrectly = false;
// 	while (ctx.areMoreTokens()) {
// 		Token tokenSep = ctx.getToken();
// 		if (!tokenSep.isGood()) {
// 			ctx.errorUnexpectedToken("declaration or }");
// 			return ParserResult();
// 		} else if (tokenSep.getID() == Token::RBrace) {
// 			ctx.eatToken();
// 			endedCorrectly = true;
// 			break;
// 		} else {
// 			ParserResult decl = ctx.expectParse(parseDecl,
// "declaration"); 			if (!decl.isGood()) {
// 				return ParserResult();
// 			}
// 			res.getAST()->as<DeclClass>()->getMembers().push_back(decl.getAST()->cloneAs<Decl>());
// 		}
// 	}

// 	if (!endedCorrectly) {
// 		ctx.errorUnexpectedToken("}");
// 		return ParserResult();
// 	}

// 	return res;
// }

// ParserResult Parser::parseDeclNamespace(ParserContext &ctx) {
// 	Token tokenClass = ctx.tryToken(Token::KWNamespace);
// 	if (!tokenClass.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenSymbol = ctx.tryToken(Token::Symbol);
// 	if (!tokenSymbol.isGood()) {
// 		return ParserResult();
// 	}

// 	ParserResult res = ParserResult(new
// DeclNamespace(tokenSymbol.getRange(), tokenSymbol.getRange().getText()));

// 	Token tokenSep = ctx.expectToken(Token::LBrace, "{");
// 	if (!tokenSep.isGood()) {
// 		return ParserResult();
// 	}

// 	bool endedCorrectly = false;
// 	while (ctx.areMoreTokens()) {
// 		Token tokenSep = ctx.getToken();
// 		if (!tokenSep.isGood()) {
// 			ctx.errorUnexpectedToken("declaration or }");
// 			return ParserResult();
// 		} else if (tokenSep.getID() == Token::RBrace) {
// 			ctx.eatToken();
// 			endedCorrectly = true;
// 			break;
// 		} else {
// 			ParserResult decl = ctx.expectParse(parseDecl,
// "declaration"); 			if (!decl.isGood()) {
// 				return ParserResult();
// 			}
// 			res.getAST()->as<DeclNamespace>()->getMembers().push_back(decl.getAST()->cloneAs<Decl>());
// 		}
// 	}

// 	if (!endedCorrectly) {
// 		ctx.errorUnexpectedToken("}");
// 		return ParserResult();
// 	}

// 	return res;
// }

// ParserResult Parser::parseDecl(ParserContext &ctx) {
// 	return ctx.tryParseAny({
// 		parseDeclClass,
// 		parseDeclNamespace,
// 		parseDeclFunction,
// 		parseDeclVariable
// 	});
// }

// ParserResult Parser::parseImport(ParserContext &ctx) {
// 	Token tokenImport = ctx.tryToken(Token::KWImport);
// 	if (!tokenImport.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenLParen = ctx.tryToken(Token::LParen);
// 	if (!tokenLParen.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenPath = ctx.expectToken(Token::String, "path");
// 	if (!tokenPath.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenRParen = ctx.tryToken(Token::RParen);
// 	if (!tokenRParen.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenSemicolon = ctx.tryToken(Token::Semicolon);
// 	if (!tokenSemicolon.isGood()) {
// 		return ParserResult();
// 	}

// 	std::string path;
// 	if (!evalLiteralString(tokenPath.getRange(), path)) {
// 		return ParserResult();
// 	}

// 	return ParserResult(new Import(tokenImport.getRange(), path));
// }

// ParserResult Parser::parseTopLevel(ParserContext &ctx) {
// 	return ctx.tryParseAny({
// 		parseImport,
// 		parseDecl
// 	});
// }

// FIX HERE

Parser::Parser(const std::vector<Token> &tokens,
               MessageBuffer &msgs,
               unsigned int offset)
    : ctx(tokens, msgs, offset) {
}

// Node *Parser::parse() {
// 	Node *rtn = Node::createUnit();

// 	Node *tmp = nullptr;
// 	while (ctx.areMoreTokens()) {
// 		ParserResult res = ctx.expectParse(parseTopLevel, "top-level
// statement"); 		if (res.isGood()) {
// 			if (tmp == nullptr) {
// 				rtn->getField(Node::FieldTag::Unit_Members)->setNode(tmp);
// 				tmp->setNext(res.getNode());
// 			} else {
// 				tmp = res.getNode();
// 			}
// 		}
// 	}

// 	return rtn;
// }
} // namespace whiskey
