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
    connect(this, &ImpactForce::sendDamage, dmgOutput, &DamageOutput::recieveDamage);
}

ImpactForce::~ImpactForce()
{
    delete ui;
}

void ImpactForce::Thrust()
{
    switch(m_strength){
        case 1:
        case 2:
            m_damage = GetCubeRoll(1) - 6;
            break;

        case 3:
        case 4:
            m_damage = GetCubeRoll(1) - 5;
            break;

        case 5:
        case 6:
            m_damage = GetCubeRoll(1) - 4;
            break;

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

        case 17:
        case 18:
            m_damage = GetCubeRoll(1) + 2;
            break;

        case 19:
        case 20:
            m_damage = GetCubeRoll(2) - 1;
            break;

        case 21:
        case 22:
            m_damage = GetCubeRoll(2);
            break;

        case 23:
        case 24:
            m_damage = GetCubeRoll(2) + 1;
            break;

        case 25:
        case 26:
            m_damage = GetCubeRoll(2) + 2;
            break;

        case 27:
        case 28:
                m_damage = GetCubeRoll(3) - 1;
            break;

        case 29:
        case 30:
            m_damage = GetCubeRoll(3);
            break;

        case 31:
        case 32:
            m_damage = GetCubeRoll(3) + 1;
            break;

        case 33:
        case 34:
            m_damage = GetCubeRoll(3) + 2;
            break;

        case 35:
        case 36:
            m_damage = GetCubeRoll(4) - 1;
            break;

        case 37:
        case 38:
            m_damage = GetCubeRoll(4);
                break;

        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
            m_damage = GetCubeRoll(4) + 1;
            break;

        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
            m_damage = GetCubeRoll(5);
            break;

        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
            m_damage = GetCubeRoll(5) + 2;
            break;


        case 55:
        case 56:
        case 57:
        case 58:
        case 59:
            m_damage = GetCubeRoll(6);
            break;

        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
            m_damage = GetCubeRoll(7) - 1;
            break;

        case 65:
        case 66:
        case 67:
        case 68:
        case 69:
            m_damage = GetCubeRoll(7) + 1;
            break;
        case 70:
        case 71:
        case 72:
        case 73:
        case 74:
            m_damage = GetCubeRoll(8) + 1;
            break;

        case 75:
        case 76:
        case 77:
        case 78:
        case 79:
            m_damage = GetCubeRoll(8) + 2;
            break;

        case 80:
        case 81:
        case 82:
        case 83:
        case 84:
            m_damage = GetCubeRoll(9);
            break;

        case 85:
        case 86:
        case 87:
        case 88:
        case 89:
            m_damage = GetCubeRoll(9) + 2;
            break;

        case 90:
        case 91:
        case 92:
        case 93:
        case 94:
            m_damage = GetCubeRoll(10);
            break;

        case 95:
        case 96:
        case 97:
        case 98:
        case 99:
            m_damage = GetCubeRoll(10) + 2;
            break;
        case 100:
            m_damage = GetCubeRoll(11);
            break;
    }
    emit sendDamage(m_damage);
    dmgOutput->show();
    this->close();
}

void ImpactForce::Swing()
{

    switch(m_strength){
        case 1:
        case 2:
            m_damage = GetCubeRoll(1) - 5;
            break;

        case 3:
        case 4:
            m_damage = GetCubeRoll(1) - 4;
            break;

        case 5:
        case 6:
            m_damage = GetCubeRoll(1) - 3;
            break;

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

        case 17:
            m_damage = GetCubeRoll(3) - 1;
            break;
        case 18:
            m_damage = GetCubeRoll(3) + 2;
            break;

        case 19:
            m_damage = GetCubeRoll(3) + 1;
            break;
        case 20:
            m_damage = GetCubeRoll(3) + 2;
            break;

        case 21:
            m_damage = GetCubeRoll(4) - 1;
            break;
        case 22:
            m_damage = GetCubeRoll(4);
            break;

        case 23:
            m_damage = GetCubeRoll(4) + 1;
            break;
        case 24:
            m_damage = GetCubeRoll(4) + 2;
            break;

        case 25:
            m_damage = GetCubeRoll(5) - 1;
            break;
        case 26:
            m_damage = GetCubeRoll(5);
            break;

        case 27:
        case 28:
            m_damage = GetCubeRoll(5) + 2;
            break;

        case 29:
        case 30:
            m_damage = GetCubeRoll(5) + 2;
            break;

        case 31:
        case 32:
            m_damage = GetCubeRoll(6) - 1;
            break;

        case 33:
        case 34:
            m_damage = GetCubeRoll(6);
            break;

        case 35:
        case 36:
            m_damage = GetCubeRoll(6) + 1;
            break;

        case 37:
        case 38:
            m_damage = GetCubeRoll(6) + 2;
                break;

        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
            m_damage = GetCubeRoll(7) - 1;
            break;

        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
            m_damage = GetCubeRoll(7) + 1;
            break;

        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
            m_damage = GetCubeRoll(8) - 1;
            break;


        case 55:
        case 56:
        case 57:
        case 58:
        case 59:
            m_damage = GetCubeRoll(8) + 1;
            break;

        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
            m_damage = GetCubeRoll(9);
            break;

        case 65:
        case 66:
        case 67:
        case 68:
        case 69:
            m_damage = GetCubeRoll(9) + 2;
            break;
        case 70:
        case 71:
        case 72:
        case 73:
        case 74:
            m_damage = GetCubeRoll(10);
            break;

        case 75:
        case 76:
        case 77:
        case 78:
        case 79:
            m_damage = GetCubeRoll(10) + 2;
            break;
        case 80:
        case 81:
        case 82:
        case 83:
        case 84:
            m_damage = GetCubeRoll(11);
            break;

        case 85:
        case 86:
        case 87:
        case 88:
        case 89:
            m_damage = GetCubeRoll(11) + 2;
            break;

        case 90:
        case 91:
        case 92:
        case 93:
        case 94:
            m_damage = GetCubeRoll(12);
            break;

        case 95:
        case 96:
        case 97:
        case 98:
        case 99:
            m_damage = GetCubeRoll(12) + 2;
            break;
        case 100:
            m_damage = GetCubeRoll(13);
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
