#include "parser.h"

Parser::Parser() {
}

Expr Parser::parseString(QString expr) {
    Expr reply;
    reply.expression = expr;
    reply.vars_number_of = expr.count('^') + expr.count('*') + expr.count('+') + 1;

    expr.replace('^', ' ');
    expr.replace('*', ' ');
    expr.replace('+', ' ');
    QStringList tmp = expr.split(' ');
    reply.vars = tmp;

    return reply;
}
