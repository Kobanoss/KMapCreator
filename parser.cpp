#include "parser.h"

Parser::Parser() {
}

// Основная функция парсера
Expr Parser::parseString(QString expr) {
    expr.replace(' ', "");
    Expr reply;
    reply.status = true;

    // Проверка на ошибки в строке
    if (expr.count(OPEN_BRACKET) != expr.count(CLOSE_BRACKET))
        reply.status = false;
    else if (expr.indexOf(OPEN_BRACKET) > expr.indexOf(CLOSE_BRACKET))
        reply.status = false;
    else if (expr.lastIndexOf(OPEN_BRACKET) > expr.lastIndexOf(CLOSE_BRACKET))
        reply.status = false;

    // Формирования нового выражения для удобной работы солвера
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

    // Получение списка переменных путем разделения строки по операторам, и их последующая сортировка по длине
    reply.vars = expr.replace(OPEN_BRACKET, " ").replace(CLOSE_BRACKET," ").split(" ");
    reply.vars.removeDuplicates();
    reply.vars.removeAll("");
    std::sort(std::begin(reply.vars),
              std::end(reply.vars),
              [](QString first, QString second) {return first.length() > second.length();});

    reply.vars_number_of = reply.vars.length();

    // Проверка на ошибки в переменных
    if (reply.vars.join("").contains(OPEN_BRACKET) || reply.vars.join("").contains(CLOSE_BRACKET))
        reply.status = false;

    // Ограничитель в 5 переменных
    if (reply.vars.size() > 5)
        reply.status = false;

    return reply;
}
