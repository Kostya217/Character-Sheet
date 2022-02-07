#include "impactforce.h"
#include "ui_impactforce.h"
#include "ui_charactersheet.h"
#include <QDebug>

void ImpactForce::recieveStrength(int strength)
{
    this->m_strength = strength;
}

ImpactForce::ImpactForce(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImpactForce)
{
    random = new QRandomGenerator();
    dmgOutput = new DamageOutput();

    ui->setupUi(this);
    QPixmap thrust("D:\\Character-Sheet_NG_Courses_21\\Character_Sheet\\resource_image\\Thrust_dmg.jpg");
    ui->i_thrust->setPixmap(thrust);

    QPixmap swing("D:\\Character-Sheet_NG_Courses_21\\Character_Sheet\\resource_image\\Swing_dmg.jpg");
    ui->i_swing->setPixmap(swing);

    connect(ui->b_thrust_dmg, &QPushButton::clicked, this, &ImpactForce::Thrust);
    connect(ui->b_swing_dmg, &QPushButton::clicked, this, &ImpactForce::Swing);
    connect(this, &ImpactForce::sendDamage, dmgOutput, &DamageOutput::recieveDamage);
    //connect(this, &ImpactForce::sendDamage, dmgOutput, &DamageOutput::recieveDamage);
}

ImpactForce::~ImpactForce()
{
    delete ui;
}

void ImpactForce::Thrust()
{
    //qDebug() << m_strength;
    switch(m_strength){
        case 7:
        case 8:
            m_damage = GetCubeRoll(1) - 3;
             break;

        case 9:
        case 10:
            m_damage = GetCubeRoll(1) - 2;
            break;

        case 11:
        case 12:
            m_damage = GetCubeRoll(1) - 1;
            break;

        case 13:
        case 14:
            m_damage = GetCubeRoll(1);
            break;

        case 15:
        case 16:
            m_damage = GetCubeRoll(1) + 1;
            break;
    }
    emit sendDamage(m_damage);
    dmgOutput->show();
    this->close();
}

void ImpactForce::Swing()
{

    switch(m_strength){
        case 7:
        case 8:
            m_damage = GetCubeRoll(1) - 2;
             break;

        case 9:
            m_damage = GetCubeRoll(1) - 1;
            break;
        case 10:
            m_damage = GetCubeRoll(1);
            break;
        case 11:
            m_damage = GetCubeRoll(1) + 1;
            break;
        case 12:
            m_damage = GetCubeRoll(1) + 2;
            break;

        case 13:
            m_damage = GetCubeRoll(2) - 1;
            break;
        case 14:
            m_damage = GetCubeRoll(2);
            break;

        case 15:
        case 16:
            m_damage = GetCubeRoll(1) + 2;
            break;
    }
    emit sendDamage(m_damage);
    dmgOutput->show();
    this->close();
}

int ImpactForce::GetCubeRoll(int numberForCubes)
{
    int diceRollValue = 0;
    for(int i = 0; i < numberForCubes; i ++){
        diceRollValue += random->bounded(1,7);
    }
    return diceRollValue;
}
