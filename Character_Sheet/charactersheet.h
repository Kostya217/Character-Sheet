#ifndef CHARACTERSHEET_H
#define CHARACTERSHEET_H

#include <QMainWindow>

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
};
#endif // CHARACTERSHEET_H
