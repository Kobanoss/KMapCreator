#include "solver.h"

Solver::Solver() {
}

// Функция, генерирующая сочетания для замещения ими переменных
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

    return reply;
}

// Функция, находящая позиции всех парных скобок, основывается на стеке
QVector<QPair<quint8, quint8>> getBrackets(QString expression) {
    QVector<QPair<quint8, quint8>> reply_brackets;
    QStack<quint8> tmp;
    for (quint8 i = 0; i < expression.length(); i++) {
        if (expression[i] == OPEN_BRACKET) {
            tmp.push(i);
        }
        else if (expression[i] == CLOSE_BRACKET) {
            reply_brackets.append(QPair<quint8, quint8>{tmp.pop(), i});
        }
    }
    return reply_brackets;
}

// Основная функция солвера
TruthTable Solver::solveExpr(Expr expr_parsed) {


    TruthTable table;
    table.vars_number_of = expr_parsed.vars_number_of;

    // Генерируем последовательности для нашего числа переменных
    QVector<QVector<qint8>> seq = generateSeq(expr_parsed.vars_number_of);

    // Проходимся по каждой последовательности
    for (qint64 pack = 0; pack < seq.length(); pack++) {
        MultiTable vars_pack;
        QString edited_expr = expr_parsed.expression;

        // Заменяем переменные на необходимые значения последовательности
        // Ошибок при повторении и сочетании имен вызывать не должно, так как переменные уже ранее были отсортированы по длине
        for (qint8 pos = 0; pos < expr_parsed.vars_number_of; pos++) {
            edited_expr.replace(expr_parsed.vars[pos], QString::number(seq[pack][pos]));
            QPair<QString,qint8> vtb;
            vtb.first = expr_parsed.vars[pos];
            vtb.second = seq[pack][pos];
            vars_pack.data[vtb.first] = vtb.second;
        }

        // Поиск позиций всех парных скобок
        QVector<QPair<quint8, quint8>> brackets_pos = getBrackets(edited_expr);

        qDebug() << edited_expr << " - Base Expr";

        // Смещение размеров из-за замены скобок и их содержимого в последствии на значение
        quint8 bonus_step = 0;

        // Проходимся по всем парам скобок, стек позволяет нам находить их в порядке приоритета, так что это можно не контролировать
        for (auto pair: brackets_pos ){
            QString modified_expr = edited_expr.mid(pair.first + 1, pair.second-pair.first - 1 - bonus_step);

            qDebug() << modified_expr << " - Base Bracket Expr";

            // Далее, в рамках каждой скобки проходимся по операторам согласно их приоритету
            for (auto priority_pack: OPERATORS_PRIORITY) {
                for (auto op: priority_pack) {
                    qint8 op_pos;

                    // Далее, повторяем операцию по подставноке значений с таблицы истинности, пока встречаем необходимый оператор
                    while ((op_pos = modified_expr.indexOf(" "+op+" ") + 1) != 0){

                        if (op != "!") {
                        QString tmp = QString::number(OPERATORS_REPLY[op][QString(modified_expr[op_pos - 2]) + QString(modified_expr[op_pos+OPERATORS_LENGTH[op] + 1])]);
                        modified_expr.replace(op_pos-2,OPERATORS_LENGTH[op]+4, tmp);
                        }
                        else {
                            QString tmp = QString::number(OPERATORS_REPLY[op][QString(modified_expr[op_pos+OPERATORS_LENGTH[op] + 1])]);
                            modified_expr.replace(op_pos-1,OPERATORS_LENGTH[op]+3, tmp);
                        }
                        qDebug() << modified_expr << " - Modified" << op << " - Operator" << op_pos << " - Old Position";
                    }
                }
            }

            // Модифицируем наше выражение и добавляем "шаг" для скобок
            edited_expr.replace(pair.first, pair.second-pair.first + 1, modified_expr);
            bonus_step += pair.second-pair.first;
        }

        // Записываем получившееся значение и показания переменных в структуру Таблицы Истинности
        vars_pack.result = edited_expr.toInt();
        table.table.append(vars_pack);

        // Формируем сжатую версию таблицы истинности, она пригодится при построении Карты Карно
        QStringList tmp;
        for (auto val:seq[pack]) {
            tmp.append(QString::number(val));
        }
        table.compressed[tmp.join("")] = edited_expr.toInt();
        tmp.clear();
    }

    return table;
}
