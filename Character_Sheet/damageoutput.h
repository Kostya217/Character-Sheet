#ifndef DAMAGEOUTPUT_H
#define DAMAGEOUTPUT_H

#include <QMainWindow>

namespace Ui {
class DamageOutput;
}

class DamageOutput : public QMainWindow
{
    Q_OBJECT

public slots:
    void recieveDamage(int damage);

public:
    explicit DamageOutput(QWidget *parent = nullptr);
    ~DamageOutput();

private:
    Ui::DamageOutput *ui;
    int damage = 0;
};

#endif // DAMAGEOUTPUT_H
