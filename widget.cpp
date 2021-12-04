#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    parser = new Parser();
    solver = new Solver();

    ui->tableWidget_Truth->horizontalHeader()->setStyleSheet("::section { background-color:#181818;}");
    ui->tableWidget_KMap->horizontalHeader()->setStyleSheet("::section { background-color:#181818;}");
}

Widget::~Widget() {
    delete ui;
}


void printTruthTableDebug(TruthTable table) {
    qDebug() << "Кол-во переменных: " << table.vars_number_of;
    for (qint8 i = 0; i < table.table.size();i++) {
        qDebug()  << "\n" << "Результат выражения: " << table.table[i].result;
        for (auto data_key: table.table[i].data.keys()) {
            qDebug() << "\nПри " + data_key << " равном " << QString::number(table.table[i].data[data_key]);
        }
    }
}

QString printTruthTableLog(TruthTable table, QString expr) {
    QString reply; 
    reply +="Выражение: " + expr;
    for (qint8 i = 0; i < table.table.size();i++) {
        reply +="\n\nРезультат выражения: ";
        reply += QString::number(table.table[i].result);
        for (auto data_key: table.table[i].data.keys()) {
            reply += "\nПри " + data_key + " равном " + QString::number(table.table[i].data[data_key]);
        }
    }
    reply +="\n\nКол-во переменных: " + QString::number(table.vars_number_of);
    return reply;
}

QString printKMapLog(TruthTable table) {
    QString reply;
    for (auto key: table.compressed.keys()) {
        reply += "\nНабор: " + QString(key) + " Результат: " + QString::number(table.compressed[key]);
    }

    return reply;
}


void Widget::CreateTruthTable() {
    ui->tableWidget_Truth->setRowCount(pow(2,table.vars_number_of) + 1);
    ui->tableWidget_Truth->setColumnCount(table.vars_number_of + 1);

    ui->tableWidget_Truth->setMaximumWidth(BASE_COL_SIZE * ui->tableWidget_Truth->columnCount());
    ui->tableWidget_Truth->setMinimumWidth(BASE_COL_SIZE * ui->tableWidget_Truth->columnCount());
    ui->tableWidget_Truth->setMaximumHeight(BASE_ROW_SIZE * ui->tableWidget_Truth->rowCount());
    ui->tableWidget_Truth->setMinimumHeight(BASE_ROW_SIZE * ui->tableWidget_Truth->rowCount());

    auto tmp = expr_parsed.vars;
    tmp.append("Func");
    for (int i = 0; i < tmp.size();i++){
        ui->tableWidget_Truth->setItem(0, i, new QTableWidgetItem(tmp[i]));
    }
    tmp.clear();
    for (int i=0; i < table.table.size(); i++) {
        quint8 j = 0;
        for (auto data_key: table.table[i].data.keys()) {
            ui->tableWidget_Truth->setItem(i+1, j, new QTableWidgetItem(QString::number(table.table[i].data[data_key])));
            j++;
        }
        ui->tableWidget_Truth->setItem(i+1, table.table[i].data.size(), new QTableWidgetItem(QString::number(table.table[i].result)));

    }

    qDebug() << ui->tableWidget_Truth->rowCount();
}


void Widget::CreateKMapTable() {
    qint8 cols = table.vars_number_of % 2 == 0?table.vars_number_of+1:table.vars_number_of;
    qint8 rows = table.vars_number_of % 2 == 0?table.vars_number_of+1:table.vars_number_of+2;
    ui->tableWidget_KMap->setRowCount(cols);
    ui->tableWidget_KMap->setColumnCount(rows);

    ui->tableWidget_KMap->setMaximumWidth((BASE_COL_SIZE+20) * ui->tableWidget_KMap->columnCount());
    ui->tableWidget_KMap->setMinimumWidth((BASE_COL_SIZE+20) * ui->tableWidget_KMap->columnCount());
    ui->tableWidget_KMap->setMaximumHeight((BASE_ROW_SIZE+20) * ui->tableWidget_KMap->rowCount());
    ui->tableWidget_KMap->setMinimumHeight((BASE_ROW_SIZE+20) * ui->tableWidget_KMap->rowCount());

    auto tmp = expr_parsed.vars;
    QString first = "";
    QString second = "";
    QString buff = ",";
    for (int i = 0;i < expr_parsed.vars.size() ;i++ ) {
        (i == expr_parsed.vars.size() - 1 ||i == expr_parsed.vars.size()/2-1)?buff="":buff=",";
        i<expr_parsed.vars.size()/2?first += (expr_parsed.vars[i] + buff):second += (expr_parsed.vars[i] + buff);
    }
    ui->tableWidget_KMap->setItem(0, 0, new QTableWidgetItem(first + '/' + second));


    for (int i = 0; i < cols-1; i++) {
        ui->tableWidget_KMap->setItem(i+1, 0, new QTableWidgetItem(GRAYCODE[QString::number(cols-1)][i]));
    }

    for (int i = 0; i < rows-1; i++) {
        ui->tableWidget_KMap->setItem(0, i+1, new QTableWidgetItem(GRAYCODE[QString::number(rows-1)][i]));
    }

    QAbstractItemModel *model =  ui->tableWidget_KMap->model();

    for (int i = 1; i < rows; i++) {
        QModelIndex value_up = model->index(0,i);
        for (int j = 1; j < cols; j++) {
            qDebug() << "Done?";
            QModelIndex value_left = model->index(j,0);
            ui->tableWidget_KMap->setItem(j,i, new QTableWidgetItem(QString::number(table.compressed[value_left.data().toString() + value_up.data().toString()])));
        }
    }

}


void Widget::on_pushButton_clicked() {
    ui->textBrowser->clear();

    QString expression = ui->lineEdit_input_line->text().toUtf8();
    qDebug() << expression;
    expr_parsed = parser->parseString(expression);

    if (expr_parsed.status == false) {
         ui->textBrowser->setText("Ошибка в формуле.");
         return;
    }
    table = solver->solveExpr(expr_parsed);
    printTruthTableDebug(table);
    CreateTruthTable();

    auto reply = printTruthTableLog(table, expression);
    ui->textBrowser->setText(reply);
    if ((expr_parsed.vars_number_of > 4) || (expr_parsed.vars_number_of < 2)) {
        ui->textBrowser->setText("Карта Карно доступна от 2х до 4х переменных.");
        return;
    }
    auto k_reply = printKMapLog(table);
    CreateKMapTable();
    ui->textBrowser->append(k_reply);

}


