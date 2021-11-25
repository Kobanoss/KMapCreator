#ifndef SOLVER_H
#define SOLVER_H

#include "common.h"

class Solver {

public:
    Solver();

    QVector<QVector<qint8>> generateSeq(qint8 size);
    TruthTable solveExpr(Expr expr_parsed, QString expr);
};

#endif // WIDGET_H
