#ifndef COMMON_H
#define COMMON_H

#include <QVector>
#include <QMap>
#include <bits/stdc++.h>
#include <QDebug>

typedef struct {
    QString expression;
    qint8 vars_number_of;
    QStringList vars;
} Expr;

typedef struct {
    QString var;
    qint8 value;
} VarTable;

typedef struct  {
    QVector<VarTable> data;
    quint8 result;
} MultiTable;

typedef struct {
    qint8 vars_number_of;
    QVector<MultiTable> table;
} TruthTable;



#endif // COMMON_H
