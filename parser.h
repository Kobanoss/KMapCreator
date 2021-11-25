#ifndef PARSER_H
#define PARSER_H

#include "common.h"

class Parser {

public:
    Parser();

    Expr parseString(QString expr);
};
#endif // WIDGET_H
