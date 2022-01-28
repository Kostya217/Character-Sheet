#ifndef CHARACTERSHEET_H
#define CHARACTERSHEET_H
#include <QLabel>
#include <QMainWindow>
#include <QPicture>

QT_BEGIN_NAMESPACE
namespace Ui { class CharacterSheet; }
QT_END_NAMESPACE

class CharacterSheet : public QMainWindow
{
    Q_OBJECT

public:
    CharacterSheet(QWidget *parent = nullptr);
    ~CharacterSheet();

private:
    Ui::CharacterSheet *ui;
    void PressButton();
    int points = 300;
    int strength = 10;
    int dexterity = 10;
    int intelligence = 10;

};
#endif // CHARACTERSHEET_H
