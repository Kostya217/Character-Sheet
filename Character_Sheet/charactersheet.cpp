#include "charactersheet.h"
#include "ui_charactersheet.h"

CharacterSheet::CharacterSheet(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CharacterSheet)
{
    ui->setupUi(this);
}

CharacterSheet::~CharacterSheet()
{
    delete ui;
}

