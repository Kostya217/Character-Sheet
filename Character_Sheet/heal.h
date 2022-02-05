#ifndef HEAL_H
#define HEAL_H

#include <QMainWindow>
#include <QMessageBox>
#include <QLineEdit>
#include <QValidator>


namespace Ui {
class Heal;
}

class Heal : public QMainWindow
{
    Q_OBJECT

public:
    explicit Heal(QWidget *parent = nullptr);
    ~Heal();

signals:
    void sendCurrentHitPoints(int hitPoints);

private slots:
    void pressButton();


private:
    Ui::Heal *ui;
    int m_maxHP = 0;
    int m_currentHP = 0;
};

#endif // HEAL_H
