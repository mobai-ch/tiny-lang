#include "Sema.h"
#include <set>
#include <string>

namespace {
class DeclCheck : public ASTVisitor {
    std::set<std::string> Scope;
    bool HasError;

    enum ErrorType {Twice, Not};

    void error(ErrorType ET, std::string V) {
        std::cerr << "Variable " << V << " "
                  << (ET == Twice ? "already" : "not")
                  << " declared\n";
        HasError = true;
    }

public:
    DeclCheck() : HasError(false) {}
    bool hasError() { return HasError; }

    virtual void visit(Factor &Node) override {
        if(Node.getKind() == Factor::Ident) {
            if (Scope.find(Node.getVal()) == Scope.end())
                error(Not, Node.getVal());
        }
    };

    virtual void visit(BinaryOp &Node) override {
        if (Node.getLeft())
            Node.getLeft()->accept(*this);
        else
            HasError = true;
        if (Node.getRight())
            Node.getRight()->accept(*this);
        else
            HasError = true;
    };

    virtual void visit(WithDecl &Node) {
        for(auto I=Node.begin(), E=Node.end(); I!=E; ++I) {
            if(!Scope.insert(*I).second)
                error(Twice, *I);
        }
        if(Node.getExpr())
            Node.getExpr()->accept(*this);
        else
            HasError = true;
    };
};
}

bool Sema::semantic(AST *Tree) {
    if(!Tree)
        return false;
    DeclCheck check;
    Tree->accept(check);
    return check.hasError();
}