#include "solver.h"

Solver::Solver() {
}


QVector<QVector<qint8>> Solver::generateSeq(qint8 size) {

    QVector<QVector<qint8>> reply;

    QVector<qint8> tmp;
    tmp.reserve(size);
    for (qint8 i=0; i < size; i++)
        tmp.push_back(0);

    for (qint8 i = 0; i < size;) {
        reply.push_back(tmp);
    for (i = 0; i < size; ++i)
        if (++tmp[i] == 2)
            tmp[i] = 0;
        else
            break;
    }

    for (auto val:reply) {
            qDebug() << val << "\n";
        }

    return reply;
}

TruthTable Solver::solveExpr(Expr expr_parsed, QString expr) {
    qint16 size = expr.length();

    TruthTable table;
    table.vars_number_of = expr_parsed.vars_number_of;

    QVector<QVector<qint8>> seq = generateSeq(expr_parsed.vars_number_of);

    for (qint64 pack = 0; pack < seq.length(); pack++) {
        MultiTable vars_pack;
        QString new_expr = expr;
        for (qint8 pos = 0; pos < expr_parsed.vars_number_of; pos++) {
            new_expr.replace(expr_parsed.vars[pos], QString::number(seq[pack][pos]));
            VarTable vtb;
            vtb.var = expr_parsed.vars[pos];
            vtb.value = seq[pack][pos];
            vars_pack.data.append(vtb);
        }
        for (qint8 i = 0;i < size; i+=2) {

            if (new_expr[i + 1] == '+') {
                if (new_expr[i + 2] == '0'|| new_expr[i] == '0')
                    new_expr[i + 2] = '0';
                else
                    new_expr[i + 2] = '1';
            }


            else if (new_expr[i + 1] == '*') {
                if (new_expr[i + 2] == '1'|| new_expr[i] == '1')
                    new_expr[i + 2] = '1';
                else
                    new_expr[i + 2] = '0';
            }


            else if (new_expr[i + 1] == '^'){
                if (new_expr[i + 2] == new_expr[i])
                    new_expr[i + 2] = '0';
                else
                    new_expr[i + 2] = '1';
            }
        }
        vars_pack.result = new_expr[size - 1].toLatin1() - '0';
        table.table.append(vars_pack);

    }

    return table;
}
