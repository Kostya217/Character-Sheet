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

QT_BEGIN_NAMESPACE
namespace Ui { class CharacterSheet; }
QT_END_NAMESPACE

class CharacterSheet : public QMainWindow
{
    Q_OBJECT

public:
    CharacterSheet(QWidget *parent = nullptr);
    ~CharacterSheet();

private slots:
    void PressButton();
    void OpenFile();
    void SaveFileAs();

private:
    Ui::CharacterSheet *ui;
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
