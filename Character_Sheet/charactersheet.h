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

signals:
    void sendStrenge(int strength);

public slots:
    void recieveCurrentHitPoints(int hitPoints);

private slots:
    void pressButton();
    void openFile();
    void saveFileAs();
    void showImapactForce();
    void rangeDamage();
    int logicsPlusButton(int characteristic, int deductingPoints);
    int logicsDependentPlusButton(int dependentCharacteristic, int characteristic, int deductingPoints);
    int logicsMinusButton(int characteristic, int addPoints);
    int logicsDependentMinusButton(int dependentCharacteristic, int characteristic, int deductingPoints);
    int logicWillOrPerceptionPlusButton(int characteristic, int deductingPoints);
    int logicsWillOrPerceptionMinusButton(int characteristic, int addPoints);


private:
    Ui::CharacterSheet *ui;
    ImpactForce *impactForce;
    Heal *heal;

    QFile fileJson;
    int m_points = 200;
    int m_strength = 10;
    int m_dexterity = 10;
    int m_intelligence = 10;
    int m_health = 10;
    int m_hitPoints = m_strength;
    int m_currentHP = m_hitPoints;
    int m_will = m_intelligence;
    int m_perception = m_intelligence;
    int m_fatiguePoints = m_health;
};
#endif // CHARACTERSHEET_H
