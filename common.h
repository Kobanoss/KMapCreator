#ifndef COMMON_H
#define COMMON_H

#include <QVector>
#include <QMap>
#include <bits/stdc++.h>
#include <QDebug>
#include <algorithm>
#include <QStack>
#include <QPair>
#include <QAbstractItemModel>
#include <QModelIndex>


#define BASE_ROW_SIZE 15
#define BASE_COL_SIZE 35

#define GRAYCODE QMap<QString, QStringList> {{"2", {"0", "1"}},{"4", {"00", "01", "11", "10"}}}

#define NOT "!"
#define AND "+"
#define OR "*"
#define NOR "\\|/"
#define NAND "|"
#define XNOR "<->"
#define XOR "^"
#define IMPLY "->"
#define REVERSED_IMPLY "<-"
#define DECREMENT "->|"
#define INCREMENT "|<-"

#define OPEN_BRACKET "("
#define CLOSE_BRACKET ")"

#define OPERATORS QStringList {INCREMENT, DECREMENT,  NOR, XNOR, IMPLY,REVERSED_IMPLY, AND, OR, NAND, XOR}

#define OPERATORS_PRIORITY QMap<qint8,QStringList> {{1,{NOT}},{2,{AND}},{3,{OR,XOR}},{4,{NAND}}, {5,{NOR}}, {6,{INCREMENT, DECREMENT, IMPLY, REVERSED_IMPLY}}, {7, {XNOR}} }

#define OPERATORS_LENGTH QMap<QString,qint8> {{NOT,1},{AND,1}, {OR,1}, {NOR,3}, {NAND,1}, {XNOR,3}, {XOR,1}, {IMPLY,3},{REVERSED_IMPLY,3}, {INCREMENT,4}, {DECREMENT,4}}

#define OPERATORS_REPLY QMap<QString,QMap<QString, qint8>>  {       {NOT,{              \
                                                                            {"1", 0},   \
                                                                            {"0", 1}}}, \
                                                                                        \
                                                                    {AND,{              \
                                                                            {"00", 0},  \
                                                                            {"10", 0},  \
                                                                            {"01", 0},  \
                                                                            {"11", 1}}},\
                                                                                        \
                                                                    {OR,{               \
                                                                            {"00", 0},  \
                                                                            {"10", 1},  \
                                                                            {"01", 1},  \
                                                                            {"11", 1}}},\
                                                                                        \
                                                                    {NOR,{              \
                                                                            {"00", 1},  \
                                                                            {"10", 0},  \
                                                                            {"01", 0},  \
                                                                            {"11", 0}}},\
                                                                                        \
                                                                    {NAND,{             \
                                                                            {"00", 1},  \
                                                                            {"10", 1},  \
                                                                            {"01", 1},  \
                                                                            {"11", 0}}},\
                                                                                        \
                                                                    {XNOR,{             \
                                                                            {"00", 1},  \
                                                                            {"10", 0},  \
                                                                            {"01", 0},  \
                                                                            {"11", 1}}},\
                                                                                        \
                                                                    {XOR,{              \
                                                                            {"00", 0},  \
                                                                            {"10", 1},  \
                                                                            {"01", 1},  \
                                                                            {"11", 0}}},\
                                                                                        \
                                                                    {IMPLY,{            \
                                                                            {"00", 1},  \
                                                                            {"10", 1},  \
                                                                            {"01", 0},  \
                                                                            {"11", 1}}},\
                                                                                        \
                                                                    {REVERSED_IMPLY,{   \
                                                                            {"00", 1},  \
                                                                            {"10", 0},  \
                                                                            {"01", 1},  \
                                                                            {"11", 1}}},\
                                                                                        \
                                                                    {DECREMENT,{        \
                                                                            {"00", 0},  \
                                                                            {"10", 0},  \
                                                                            {"01", 1},  \
                                                                            {"11", 0}}},\
                                                                                        \
                                                                    {INCREMENT,{        \
                                                                            {"00", 0},  \
                                                                            {"10", 1},  \
                                                                            {"01", 0},  \
                                                                            {"11", 0}}} }





typedef struct {
    QString expression;
    qint8 vars_number_of;
    QStringList vars;
    bool status;
} Expr;

typedef struct  {
    QMap<QString,qint8> data;
    quint8 result;
} MultiTable;

typedef struct {
    qint8 vars_number_of;
    QVector<MultiTable> table;
    QMap <QString,quint8> compressed;
} TruthTable;

typedef struct {
    QString cols;
    QMap<QString, QMap<QString, qint8>> items;
} KMap;



#endif // COMMON_H
