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
    void sendHitPoints(int hitPoints);


private slots:
    void pressButton();

private:
    Ui::Heal *ui;
};

#endif // HEAL_H
