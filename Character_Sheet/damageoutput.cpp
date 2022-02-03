#include "damageoutput.h"
#include "ui_damageoutput.h"
#include "impactforce.h"
#include <QDebug>

void DamageOutput::recieveDamage(int damage)
{
    this->damage = damage;
    ui->lcd_n_damage->display(this->damage);
}

DamageOutput::DamageOutput(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DamageOutput)
{
    ui->setupUi(this);
}

DamageOutput::~DamageOutput()
{
    delete ui;
}
