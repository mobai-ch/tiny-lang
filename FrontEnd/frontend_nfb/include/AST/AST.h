#ifndef TINYLANG_AST_H
#define TINYLANG_AST_H

#include <vector>
#include <string>

class AST;
class Expr;
class Factor;
class BinaryOp;
class WithDecl;

class ASTVisitor {
public:
    virtual void visit(AST &) {};
    virtual void visit(Expr &) {};
    virtual void visit(Factor &) = 0;
    virtual void visit(BinaryOp &) = 0;
    virtual void visit(WithDecl &) = 0;
};

class AST {
public:
    virtual ~AST() {}
    virtual void accept(ASTVisitor &V) = 0;
};

class Expr : public AST {
public:
    Expr() {};
};

class Factor : public Expr {
public:
    enum ValueKind {Ident, Number};
private:
    ValueKind Kind;
    std::string Val;
public:
    Factor(ValueKind Kind, std::string Val)
        : Kind(Kind), Val(Val) {}
    ValueKind getKind() { return Kind; }
    std::string getVal() { return Val; }
    virtual void accept(ASTVisitor &V) override {
        V.visit(*this);
    } 
};

class BinaryOp : public Expr {
public:
    enum Operator { Plus, Minus, Mul, Div };

private:
    Expr *Left;
    Expr *Right;
    Operator Op;

public:
    BinaryOp(Operator Op, Expr *L, Expr *R)
        : Op(Op), Left(L), Right(R) {}
    Expr *getLeft() { return Left; }
    Expr *getRight() { return Right; }
    Operator getOperator() { return Op; }
    virtual void accept(ASTVisitor &V) override {
        V.visit(*this);
    }
};

class WithDecl : public AST {
    using VarVector = std::vector<std::string>;
    VarVector Vars;
    Expr *E;

public:
    WithDecl(std::vector<std::string> Vars, Expr *E)
        : Vars(Vars), E(E) {}
    VarVector::iterator begin() { return Vars.begin(); }
    VarVector::iterator end() { return Vars.end(); }
    Expr *getExpr() { return E; }
    virtual void accept(ASTVisitor &v) override {
        v.visit(*this);
    } 
};

#endif