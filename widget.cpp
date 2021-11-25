#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    parser = new Parser();
    solver = new Solver();
}

Widget::~Widget() {
    delete ui;
}


void printTruthTableDebug(TruthTable table) {
    qDebug() << "Кол-во переменных: " << table.vars_number_of;
    for (qint8 i = 0; i < table.table.size();i++) {
        qDebug()  << "\n" << "Результат выражения: " << table.table[i].result;
        for (qint8 j = 0; j < table.table[i].data.length();j++) {
            qDebug() << "При " << table.table[i].data[j].var << "равном" << table.table[i].data[j].value;
        }
    }
}

QString printTruthTableLog(TruthTable table) {
    QString reply;
    reply +="Кол-во переменных: " + QString::number(table.vars_number_of);
    for (qint8 i = 0; i < table.table.size();i++) {
        reply +="\n\nРезультат выражения: ";
        reply += QString::number(table.table[i].result);
        for (qint8 j = 0; j < table.table[i].data.length();j++) {
            reply += "\nПри " + table.table[i].data[j].var + " равном " + QString::number(table.table[i].data[j].value);
        }
    }
    return reply;
}

void Widget::on_pushButton_clicked() {
    ui->textBrowser->clear();

    QString expression = ui->lineEdit_input_line->text().toUtf8();
    Expr expr_parsed = parser->parseString(expression);
    TruthTable table = solver->solveExpr(expr_parsed, expression);

    printTruthTableDebug(table);
    auto reply = printTruthTableLog(table);
    ui->textBrowser->setText(reply);

}


