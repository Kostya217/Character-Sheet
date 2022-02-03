#ifndef CHARACTERSHEET_H
#define CHARACTERSHEET_H
#include <QLabel>
#include <QMainWindow>
#include <QPicture>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include "impactforce.h"
#include "heal.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CharacterSheet; }
QT_END_NAMESPACE


class CharacterSheet : public QMainWindow
{
    Q_OBJECT

public:
    CharacterSheet(QWidget *parent = nullptr);
    ~CharacterSheet();
    int GetStrength();

signals:
    void sendStrenge(int strength);

public slots:
    void recieveHitPoints(int hitPoints);

private slots:
    void PressButton();
    void OpenFile();
    void SaveFileAs();
    void ShowImapactForce();
    void pressHeal();


private:
    Ui::CharacterSheet *ui;
    ImpactForce *impactForce;
    Heal *heal;

    QFile fileJson;
    int points = 300;
    int strength = 10;
    int dexterity = 10;
    int intelligence = 10;
    int health = 10;
    int hitPoints = strength;
    int will = intelligence;
    int perception = intelligence;
    int fatiguePoints = health;
};
#endif // CHARACTERSHEET_H
