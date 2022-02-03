#include "heal.h"
#include "ui_heal.h"
#include "charactersheet.h"

Heal::Heal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Heal)
{
    ui->setupUi(this);
    connect(ui->b_get_hit_points, &QPushButton::clicked, this, &Heal::pressButton);

}

Heal::~Heal()
{
    delete ui;
}

void Heal::pressButton()
{
    QIntValidator valid(0, 100, this);
    QString input = ui->l_value_hp->text();
    int pos = 0;

    if(valid.validate(input, pos)){
        emit sendHitPoints(ui->l_value_hp->text().toInt());
        this->close();
    }else{
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Wrong format used");
        messageBox.setFixedSize(500,200);
    }

}
