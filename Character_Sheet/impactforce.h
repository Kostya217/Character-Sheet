#ifndef IMPACTFORCE_H
#define IMPACTFORCE_H

#include <QMainWindow>
#include <QRandomGenerator>
#include "damageoutput.h"


namespace Ui {class ImpactForce;}

class ImpactForce : public QMainWindow
{
    Q_OBJECT
signals:
    void sendDamage(int damage);

public slots:
    void recieveStrength(int strength);

public:
    explicit ImpactForce(QWidget *parent = nullptr);
    ~ImpactForce();

private slots:
    void Thrust();
    void Swing();
    int GetCubeRoll(int numberForCubes);

private:
    Ui::ImpactForce *ui;
    int m_damage = 0;
    int m_strength = 0;
    QRandomGenerator *random;
    DamageOutput *dmgOutput;
};

#endif // IMPACTFORCE_H
