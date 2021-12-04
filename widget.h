#ifndef WIDGET_H
#define WIDGET_H

#include "parser.h"
#include "solver.h"

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;


    // Объекты классов парсера и солвера
    Parser *parser;
    Solver *solver;

    Expr expr_parsed;
    TruthTable table;
    // Функция, занимающаяся созданием и заполнением таблицы истинности
    void CreateTruthTable();
    // Функция, занимающаяся созданием и заполнением карты Карно
    void CreateKMapTable();
};
#endif // WIDGET_H
