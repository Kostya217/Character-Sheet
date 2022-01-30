#include "charactersheet.h"
#include "ui_charactersheet.h"

CharacterSheet::CharacterSheet(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CharacterSheet)
{
    ui->setupUi(this);
    QPixmap pixmap("D:\\Character-Sheet_NG_Courses_21\\Character_Sheet\\resource_image\\GURPS_Logo.j"
                   "pg");
    ui->i_gurps_logo->setPixmap(pixmap);

    ui->lcd_n_counter_points->display(points);

    ui->lcd_n_strength->display(strength);
    connect(ui->b_strength_plus, &QPushButton::clicked, this, &CharacterSheet::PressButton);
    connect(ui->b_strength_minus, &QPushButton::clicked, this, &CharacterSheet::PressButton);

    ui->lcd_n_dexterity->display(dexterity);
    connect(ui->b_dexterity_plus, &QPushButton::clicked, this, &CharacterSheet::PressButton);
    connect(ui->b_dexterity_minus, &QPushButton::clicked, this, &CharacterSheet::PressButton);

    ui->lcd_n_intelligence->display(intelligence);
    connect(ui->b_intelligence_plus, &QPushButton::clicked, this, &CharacterSheet::PressButton);
    connect(ui->b_intelligence_minus, &QPushButton::clicked, this, &CharacterSheet::PressButton);

    ui->lcd_n_health->display(health);
    connect(ui->b_health_plus, &QPushButton::clicked, this, &CharacterSheet::PressButton);
    connect(ui->b_health_minus, &QPushButton::clicked, this, &CharacterSheet::PressButton);

    ui->lcd_n_hit_points->display(hitPoints);
    connect(ui->b_hit_points_plus, &QPushButton::clicked, this, &CharacterSheet::PressButton);
    connect(ui->b_hit_points_minus, &QPushButton::clicked, this, &CharacterSheet::PressButton);

    ui->lcd_n_will->display(will);
    connect(ui->b_will_plus, &QPushButton::clicked, this, &CharacterSheet::PressButton);
    connect(ui->b_will_minus, &QPushButton::clicked, this, &CharacterSheet::PressButton);

    ui->lcd_n_fatigue_points->display(fatiguePoints);
    connect(ui->b_fatigue_points_plus, &QPushButton::clicked, this, &CharacterSheet::PressButton);
    connect(ui->b_fatigue_points_minus, &QPushButton::clicked, this, &CharacterSheet::PressButton);

    connect(ui->b_import, &QPushButton::clicked, this, &CharacterSheet::FindCharacterSheet);

    connect(ui->b_export, &QPushButton::clicked, this, &CharacterSheet::SaveFileAs);

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
    else if(button == ui->b_dexterity_plus){
        if(dexterity > 0 && points > 0){
            dexterity++;
            points += 10;
        }
        ui->lcd_n_counter_points->display(points);
        ui->lcd_n_dexterity->display(dexterity);
    }
    else if(button == ui->b_dexterity_minus){
        if(dexterity > 0 && points > 0){
            dexterity--;
            points -= 10;
        }
        ui->lcd_n_counter_points->display(points);
        ui->lcd_n_dexterity->display(dexterity);
    }
}

void CharacterSheet::FindCharacterSheet()
{
    QString value;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                              tr("Choose character sheet"),
                                                              QDir::homePath(),
                                                              tr("Sheet(*.chs);;All Files (*)"));
    fileJson.setFileName(fileName);
    fileJson.open(QIODevice::ReadOnly);
    value = fileJson.readAll();
    fileJson.close();

    QJsonDocument doc = QJsonDocument::fromJson(value.toUtf8());
    QJsonObject json = doc.object();
    ui->l_name->setText(json["Name"].toString());
    ui->l_player->setText(json["Player name"].toString());
    ui->lcd_n_counter_points->display(points = json["Total points"].toInt());
    ui->lcd_n_strength->display(strength = json["Strength"].toInt());
    ui->lcd_n_dexterity->display(dexterity = json["Dexterity"].toInt());
    ui->lcd_n_intelligence->display(intelligence = json["Intelligence"].toInt());
    ui->lcd_n_health->display(health = json["Health"].toInt());
    ui->lcd_n_hit_points->display(hitPoints = json["Hit Points"].toInt());
    ui->lcd_n_will->display(will = json["Will"].toInt());
    ui->lcd_n_fatigue_points->display(fatiguePoints = json["Fatigue Points"].toInt());
}

void CharacterSheet::SaveFileAs()
{

    QString fileName =  QFileDialog::getSaveFileName(this,
                                                     tr("Save Character Sheet"),
                                                     QDir::homePath(),
                                                     tr("Character Sheet (*.chs);;All Files (*)"));
    fileJson.setFileName(fileName);
    fileJson.open(QIODevice::WriteOnly);

    QVariantMap data;
    data.insert("Name", ui->l_name->text());
    data.insert("Player name", ui->l_player->text());
    data.insert("Total points", points);
    data.insert("Strength", strength);
    data.insert("Dexterity", dexterity);
    data.insert("Intelligence", intelligence);
    data.insert("Health", health);
    data.insert("Hit Points", hitPoints);
    data.insert("Will", will);
    data.insert("Fatigue Points", fatiguePoints);

    fileJson.write(QJsonDocument(QJsonObject::fromVariantMap(data)).toJson());

    fileJson.close();


}

