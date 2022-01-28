#include "charactersheet.h"
#include "ui_charactersheet.h"

CharacterSheet::CharacterSheet(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CharacterSheet)
{
    ui->setupUi(this);
    QPixmap pixmap("D:\\Character-Sheet_NG_Courses_21\\Character_Sheet\\resourec\\GURPS_Logo");
    ui->i_gurps_logo->setPixmap(pixmap);

    ui->lcd_n_counter_points->display(points);

    ui->lcd_n_strength->display(strength);
    connect(ui->b_strength_plus, &QPushButton::clicked, this, &CharacterSheet::PressButton);
    connect(ui->b_strength_minus, &QPushButton::clicked, this, &CharacterSheet::PressButton);

    ui->lcd_n_dexterity->display(dexterity);
    connect(ui->b_dexterity_plus, &QPushButton::clicked, this, &CharacterSheet::PressButton);
    connect(ui->b_dexterity_minus, &QPushButton::clicked, this, &CharacterSheet::PressButton);

    ui->lcd_n_intelligence->display(dexterity);
    connect(ui->b_intelligence_plus, &QPushButton::clicked, this, &CharacterSheet::PressButton);
    connect(ui->b_intelligence_minus, &QPushButton::clicked, this, &CharacterSheet::PressButton);

}

CharacterSheet::~CharacterSheet()
{
    delete ui;
}

void CharacterSheet::PressButton()
{
    QPushButton *button = (QPushButton*) sender();

    if(button == ui->b_strength_plus){
        if(strength >= 0 && points > 0){
            strength++;
            points -= 10;
        }
        ui->lcd_n_counter_points->display(points);
        ui->lcd_n_strength->display(strength);
    }
    else if(button == ui->b_strength_minus){
        if(strength > 0 && points > 0){
            strength--;
            points += 10;
        }
        ui->lcd_n_counter_points->display(points);
        ui->lcd_n_strength->display(strength);
    }
    else if(button == ui->b_intelligence_plus){
        if(dexterity > 0 && points > 0){
            intelligence--;
            points += 10;
        }
        ui->lcd_n_counter_points->display(points);
        ui->lcd_n_dexterity->display(intelligence);
    }
    else if(button == ui->b_intelligence_minus){
        if(dexterity > 0 && points > 0){
            intelligence--;
            points += 10;
        }
        ui->lcd_n_counter_points->display(points);
        ui->lcd_n_dexterity->display(intelligence);
    }
}

