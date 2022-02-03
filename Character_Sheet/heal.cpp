#include "heal.h"
#include "ui_heal.h"
#include "charactersheet.h"

Heal::Heal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Heal)
{
    ui->setupUi(this);
    connect(ui->b_get_hit_points, &QPushButton::clicked, this, &Heal::pressButton);
    //connect(this, &Heal::sendHitPoints, )
}

Heal::~Heal()
{
    delete ui;
}

void Heal::pressButton()
{
    try{
        emit sendHitPoints(ui->l_value_hp->text().toInt());
        this->close();
    }catch(QString){
        (new QErrorMessage(this))->showMessage("Wrong Format");
    }

}
