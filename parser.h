#ifndef PARSER_H
#define PARSER_H

#include "common.h"

class Parser {

public:
    Parser();

    // Функция, выполняющая парсинг строки
    Expr parseString(QString expr);
};
#endif // WIDGET_H
