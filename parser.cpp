#include "parser.h"

Parser::Parser() {
}

Expr Parser::parseString(QString expr) {
    expr.replace(' ', "");
    Expr reply;
    reply.status = true;

    if (expr.count(OPEN_BRACKET) != expr.count(CLOSE_BRACKET))
        reply.status = false;
    else if (expr.indexOf(OPEN_BRACKET) > expr.indexOf(CLOSE_BRACKET))
        reply.status = false;
    else if (expr.lastIndexOf(OPEN_BRACKET) > expr.lastIndexOf(CLOSE_BRACKET))
        reply.status = false;


    QString new_expr = expr;
    new_expr.replace(NOT, " " + QString(NOT) + " ");
    for (auto op: OPERATORS) {
        new_expr.replace(op, " " + op + " ");
    }
    new_expr.push_front(OPEN_BRACKET);
    new_expr.push_back(CLOSE_BRACKET);
    reply.expression = new_expr;


    expr.replace(NOT, "");
    for (auto op: OPERATORS) {
        expr.replace(op, " ");
    }

    reply.vars = expr.replace(OPEN_BRACKET, " ").replace(CLOSE_BRACKET," ").split(" ");
    reply.vars.removeDuplicates();
    reply.vars.removeAll("");
    std::sort(std::begin(reply.vars),
              std::end(reply.vars),
              [](QString first, QString second) {return first.length() > second.length();});

    reply.vars_number_of = reply.vars.length();

    if (reply.vars.join("").contains(OPEN_BRACKET) || reply.vars.join("").contains(CLOSE_BRACKET))
        reply.status = false;

    if (reply.vars.size() > 5)
        reply.status = false;

    return reply;
}
