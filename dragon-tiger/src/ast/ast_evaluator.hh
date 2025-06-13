#ifndef AST_EVALUATOR_HH
#define AST_EVALUATOR_HH

#include "../utils/errors.hh"
#include "nodes.hh"

namespace ast {

class ASTEvaluator : public ConstASTIntVisitor {
public:
  int32_t visit(const IntegerLiteral & literal) override {
    return literal.value;
  }

  int32_t visit(const BinaryOperator & oper) override {
    int32_t left = oper.get_left().accept(*this);
    int32_t right = oper.get_right().accept(*this);

    switch (oper.op) {
      case o_plus:  return left + right;
      case o_minus: return left - right;
      case o_times: return left * right;
      case o_divide:
        if (right == 0) {
          utils::error("Division by zero");
        }
        return left / right;
      case o_eq:  return left == right;
      case o_neq: return left != right;
      case o_lt:  return left < right;
      case o_le:  return left <= right;
      case o_gt:  return left > right;
      case o_ge:  return left >= right;
      default:
        utils::error("Unknown binary operator");
    }
    return 0;
  }

  int32_t visit(const Sequence & seq) override {
    const auto & exprs = seq.get_exprs();
    if (exprs.empty()) {
      utils::error("Empty sequence");
    }
    int32_t result = 0;
    for (Expr* expr : exprs) {
      result = expr->accept(*this);
    }
    return result;
  }

  int32_t visit(const IfThenElse & ite) override {
    if (ite.get_condition().accept(*this)) {
      return ite.get_then_part().accept(*this);
    } else {
      return ite.get_else_part().accept(*this);
    }
  }

  int32_t visit(const StringLiteral &) override {
    utils::error("StringLiteral evaluation not implemented");
  }
  int32_t visit(const Let &) override {
    utils::error("Let evaluation not implemented");
  }
  int32_t visit(const Identifier &) override {
    utils::error("Identifier evaluation not implemented");
  }
  int32_t visit(const VarDecl &) override {
    utils::error("VarDecl evaluation not implemented");
  }
  int32_t visit(const FunDecl &) override {
    utils::error("FunDecl evaluation not implemented");
  }
  int32_t visit(const FunCall &) override {
    utils::error("FunCall evaluation not implemented");
  }
  int32_t visit(const WhileLoop &) override {
    utils::error("WhileLoop evaluation not implemented");
  }
  int32_t visit(const ForLoop &) override {
    utils::error("ForLoop evaluation not implemented");
  }
  int32_t visit(const Break &) override {
    utils::error("Break evaluation not implemented");
  }
  int32_t visit(const Assign &) override {
    utils::error("Assign evaluation not implemented");
  }
};

}

#endif
