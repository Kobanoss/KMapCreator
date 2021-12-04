#ifndef SOLVER_H
#define SOLVER_H

#include "common.h"

class Solver {

public:
    Solver();

    // Функция, генерирующая последовательности для подстановки в логическое выражение
    QVector<QVector<qint8>> generateSeq(qint8 size);

    // Функци, осуществляющая подстановку и рассчет логического выражения,
    // основываясь на данных ранее таблицах истинности логических операций
    TruthTable solveExpr(Expr expr_parsed);
};

#endif // WIDGET_H
