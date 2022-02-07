#include "charactersheet.h"
#include "ui_charactersheet.h"

CharacterSheet::CharacterSheet(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CharacterSheet)
{
    ui->setupUi(this);

    impactForce = new ImpactForce();
    heal = new Heal();

    connect(ui->b_dmg, &QPushButton::clicked, this, &CharacterSheet::showImapactForce);

    connect(ui->b_heal, &QPushButton::clicked, heal, &Heal::show);
    connect(heal, &Heal::sendCurrentHitPoints, this, &CharacterSheet::recieveCurrentHitPoints);


    connect(this, &CharacterSheet::sendStrenge, impactForce, &ImpactForce::recieveStrength);

    QPixmap pixmap("D:\\Character-Sheet_NG_Courses_21\\Character_Sheet\\resource_image\\GURPS_Logo.png");
    ui->i_gurps_logo->setPixmap(pixmap);

    ui->lcd_n_counter_points->display(m_points);

    ui->lcd_n_strength->display(m_strength);
    connect(ui->b_strength_plus, &QPushButton::clicked, this, &CharacterSheet::pressButton);
    connect(ui->b_strength_minus, &QPushButton::clicked, this, &CharacterSheet::pressButton);

    ui->lcd_n_dexterity->display(m_dexterity);
    connect(ui->b_dexterity_plus, &QPushButton::clicked, this, &CharacterSheet::pressButton);
    connect(ui->b_dexterity_minus, &QPushButton::clicked, this, &CharacterSheet::pressButton);

    ui->lcd_n_intelligence->display(m_intelligence);
    connect(ui->b_intelligence_plus, &QPushButton::clicked, this, &CharacterSheet::pressButton);
    connect(ui->b_intelligence_minus, &QPushButton::clicked, this, &CharacterSheet::pressButton);

    ui->lcd_n_health->display(m_health);
    connect(ui->b_health_plus, &QPushButton::clicked, this, &CharacterSheet::pressButton);
    connect(ui->b_health_minus, &QPushButton::clicked, this, &CharacterSheet::pressButton);

    ui->lcd_n_hit_points->display(m_hitPoints);
    connect(ui->b_hit_points_plus, &QPushButton::clicked, this, &CharacterSheet::pressButton);
    connect(ui->b_hit_points_minus, &QPushButton::clicked, this, &CharacterSheet::pressButton);

    ui->lcd_n_current_hp->display(m_currentHP);
    connect(ui->b_current_hp_minus, &QPushButton::clicked, this, &CharacterSheet::pressButton);

    ui->lcd_n_will->display(m_will);
    connect(ui->b_will_plus, &QPushButton::clicked, this, &CharacterSheet::pressButton);
    connect(ui->b_will_minus, &QPushButton::clicked, this, &CharacterSheet::pressButton);

    ui->lcd_n_perception->display(m_perception);
    connect(ui->b_perception_plus, &QPushButton::clicked, this, &CharacterSheet::pressButton);
    connect(ui->b_perception_minus, &QPushButton::clicked, this, &CharacterSheet::pressButton);

    ui->lcd_n_fatigue_points->display(m_fatiguePoints);
    connect(ui->b_fatigue_points_plus, &QPushButton::clicked, this, &CharacterSheet::pressButton);
    connect(ui->b_fatigue_points_minus, &QPushButton::clicked, this, &CharacterSheet::pressButton);

    ui->lcd_n_basic_lift->display(round((m_strength * m_strength)/5));
    ui->l_thrust_range->setText("от (-1) до 4");
    ui->l_swing_range->setText("от 1 до 6");



    connect(ui->b_import, &QPushButton::clicked, this, &CharacterSheet::openFile);

    connect(ui->b_export, &QPushButton::clicked, this, &CharacterSheet::saveFileAs);
}

CharacterSheet::~CharacterSheet()
{
    delete ui;
}

void CharacterSheet::pressButton()
{
    QPushButton *button = (QPushButton*) sender();

    // Strenght
    if(button == ui->b_strength_plus){
        m_hitPoints = m_strength < logicsPlusButton(m_strength, 0)? logicsDependentPlusButton(m_hitPoints, m_strength + 1, 0): m_hitPoints;
        m_strength = logicsPlusButton(m_strength, 10);
        rangeDamage();
    }
    else if(button == ui->b_strength_minus){
        m_hitPoints = m_strength > logicsMinusButton(m_strength, 0) ? logicsDependentMinusButton(m_hitPoints, m_strength + 2, 0): m_hitPoints;
        m_strength = logicsMinusButton(m_strength, 10);
        rangeDamage();
    }

    // Dexterity
    else if(button == ui->b_dexterity_plus){
        m_dexterity = logicsPlusButton(m_dexterity, 10);
    }
    else if(button == ui->b_dexterity_minus){
        m_dexterity = logicsMinusButton(m_dexterity, 10);
    }

    // Intelligence
    else if(button == ui->b_intelligence_plus){
        m_perception = m_intelligence < logicsPlusButton(m_intelligence, 0) ? logicWillOrPerceptionPlusButton(m_perception, 0): m_perception;
        m_will = m_intelligence < logicsPlusButton(m_intelligence, 0) ? logicWillOrPerceptionPlusButton(m_will, 0): m_will;
        m_intelligence = logicsPlusButton(m_intelligence, 20);
    }
    else if(button == ui->b_intelligence_minus){
        m_perception = m_intelligence > logicsMinusButton(m_intelligence, 0) ? logicsWillOrPerceptionMinusButton(m_perception, 0): m_perception;
        m_will = m_intelligence > logicsMinusButton(m_intelligence, 0) ? logicsWillOrPerceptionMinusButton(m_will, 0): m_will;
        m_intelligence = logicsMinusButton(m_intelligence, 20);
    }

    //Health
    else if(button == ui->b_health_plus){
        m_health = logicsPlusButton(m_health, 10);
        m_fatiguePoints = m_health < logicsPlusButton(m_health, 0) ? logicsDependentPlusButton(m_fatiguePoints, m_health + 1, 0): m_health;
    }
    else if(button == ui->b_health_minus){
        m_health = logicsMinusButton(m_health, 10);
        m_fatiguePoints = m_health > logicsMinusButton(m_health, 0) ? logicsDependentMinusButton(m_fatiguePoints, m_health + 2, 0): m_health;
    }

    // Hit points
    else if(button == ui->b_hit_points_plus){
        m_currentHP = m_hitPoints < logicsDependentPlusButton(m_hitPoints, m_strength, 0) ? m_currentHP + 1:  m_currentHP;
        m_hitPoints = logicsDependentPlusButton(m_hitPoints, m_strength, 2);

    }
    else if(button == ui->b_hit_points_minus){
        m_currentHP = ((m_hitPoints > logicsDependentMinusButton(m_hitPoints, m_strength, 0)) && (m_currentHP > 0)) ? m_currentHP - 1:  m_currentHP;
        m_hitPoints = logicsDependentMinusButton(m_hitPoints, m_strength, 2);
    }
    else if(button == ui->b_current_hp_minus && m_currentHP > 0){
        m_currentHP--;
        ui->lcd_n_current_hp->display(m_currentHP);
    }

    //Will
    else if(button == ui->b_will_plus){
        m_will = logicWillOrPerceptionPlusButton(m_will, 5);
    }
    else if(button == ui->b_will_minus){
        m_will = logicsWillOrPerceptionMinusButton(m_will, 5);
    }

    //Perception
    else if(button == ui->b_perception_plus){
        m_perception = logicWillOrPerceptionPlusButton(m_perception, 5);
    }
    else if(button == ui->b_perception_minus){
        m_perception = logicsWillOrPerceptionMinusButton(m_perception, 5);
    }

    // Fatigue points
    else if(button == ui->b_fatigue_points_plus){
        m_fatiguePoints = logicsDependentPlusButton(m_fatiguePoints, m_health, 3);
    }
    else if(button == ui->b_fatigue_points_minus){
        m_fatiguePoints = logicsDependentMinusButton(m_fatiguePoints, m_health, 3);
    }
    ui->lcd_n_basic_lift->display(round((m_strength * m_strength)/5));
    ui->lcd_n_strength->display(m_strength);
    ui->lcd_n_dexterity->display(m_dexterity);
    ui->lcd_n_intelligence->display(m_intelligence);
    ui->lcd_n_health->display(m_health);
    ui->lcd_n_hit_points->display(m_hitPoints);
    ui->lcd_n_current_hp->display(m_currentHP);
    ui->lcd_n_will->display(m_will);
    ui->lcd_n_perception->display(m_perception);
    ui->lcd_n_fatigue_points->display(m_fatiguePoints);
    ui->lcd_n_counter_points->display(m_points);
}

int CharacterSheet::logicsPlusButton(int characteristic, int deductingPoints)
{
    if(characteristic >= 7 && characteristic < 16 && m_points - deductingPoints >= 0){
        characteristic++;
        m_points -= deductingPoints;
    }

    return characteristic;
}

int CharacterSheet::logicsDependentPlusButton(int dependentCharacteristic, int characteristic, int deductingPoints)
{
    if(dependentCharacteristic < ceil(characteristic * 1.3) &&
       dependentCharacteristic >= floor(characteristic * 0.7)&&
       m_points - deductingPoints >= 0){
        dependentCharacteristic++;
        m_points -= deductingPoints;
    }

    return dependentCharacteristic;
}


int CharacterSheet::logicsMinusButton(int characteristic, int addPoints)
{
    if( characteristic <= 16 && characteristic > 7){
        characteristic--;
        m_points += addPoints;
    }

    return characteristic;
}

int CharacterSheet::logicsDependentMinusButton(int dependentCharacteristic, int characteristic, int deductingPoints)
{
    if(dependentCharacteristic > floor(characteristic * 0.7)){
        dependentCharacteristic--;
        m_points += deductingPoints;
    }

    return dependentCharacteristic;
}

int CharacterSheet::logicWillOrPerceptionPlusButton(int characteristic, int deductingPoints)
{
    if( characteristic < 20 &&
        characteristic >= 4 &&
        m_points - deductingPoints >= 0){
        characteristic++;
        m_points -= deductingPoints;
    }

    return characteristic;
}

int CharacterSheet::logicsWillOrPerceptionMinusButton(int characteristic, int addPoints)
{
    if(characteristic <= 20 &&
       characteristic > 4){
        characteristic--;
        m_points += addPoints;
    }
    return characteristic;
}

void CharacterSheet::openFile()
{
    QString value;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Choose character sheet"),
                                                    QDir::homePath(),
                                                    tr("Sheet(*.chs)"));
    fileJson.setFileName(fileName);
    fileJson.open(QIODevice::ReadOnly);
    value = fileJson.readAll();
    fileJson.close();

    QJsonDocument doc = QJsonDocument::fromJson(value.toUtf8());
    QJsonObject json = doc.object();
    ui->l_name->setText(json["Name"].toString());
    ui->l_player->setText(json["Player name"].toString());
    ui->lcd_n_counter_points->display(m_points = json["Total points"].toInt());
    ui->lcd_n_strength->display(m_strength = json["Strength"].toInt());
    ui->lcd_n_dexterity->display(m_dexterity = json["Dexterity"].toInt());
    ui->lcd_n_intelligence->display(m_intelligence = json["Intelligence"].toInt());
    ui->lcd_n_health->display(m_health = json["Health"].toInt());
    ui->lcd_n_hit_points->display(m_hitPoints = json["Hit Points"].toInt());
    ui->lcd_n_current_hp->display(m_currentHP = json["Current Hit Points"].toInt());
    ui->lcd_n_will->display(m_will = json["Will"].toInt());
    ui->lcd_n_will->display(m_perception = json["Perception"].toInt());
    ui->lcd_n_fatigue_points->display(m_fatiguePoints = json["Fatigue Points"].toInt());
    rangeDamage();
}

void CharacterSheet::saveFileAs()
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
    data.insert("Total points", m_points);
    data.insert("Strength", m_strength);
    data.insert("Dexterity", m_dexterity);
    data.insert("Intelligence", m_intelligence);
    data.insert("Health", m_health);
    data.insert("Hit Points", m_hitPoints);
    data.insert("Current Hit Points", m_currentHP);
    data.insert("Will", m_will);
    data.insert("Perception", m_perception);
    data.insert("Fatigue Points", m_fatiguePoints);

    fileJson.write(QJsonDocument(QJsonObject::fromVariantMap(data)).toJson());

    fileJson.close();


}

void CharacterSheet::showImapactForce()
{
    emit sendStrenge(m_strength);
    impactForce->show();
}

void CharacterSheet::rangeDamage()
{
    switch(m_strength){
        case 7:
        case 8:
            ui->l_thrust_range->setText("от 0 до 3");
            ui->l_swing_range->setText("от 0 до 4");
             break;

        case 9:
            ui->l_thrust_range->setText("от 0 до 4");
            ui->l_swing_range->setText("от 0 до 5");
            break;

        case 10:
            ui->l_thrust_range->setText("от 0 до 4");
            ui->l_swing_range->setText("от 1 до 6");
            break;

        case 11:
            ui->l_thrust_range->setText("от 0 до 5");
            ui->l_swing_range->setText("от 2 до 7");
            break;
        case 12:
            ui->l_thrust_range->setText("от 0 до 5");
            ui->l_swing_range->setText("от 3 до 8");
            break;

        case 13:
            ui->l_thrust_range->setText("от 1 до 6");
            ui->l_swing_range->setText("от 1 до 11");
            break;
        case 14:
            ui->l_thrust_range->setText("от 1 до 6");
            ui->l_swing_range->setText("от 2 до 12");
            break;

        case 15:
            ui->l_thrust_range->setText("от 2 до 7");
            ui->l_swing_range->setText("от 3 до 13");
            break;
        case 16:
            ui->l_thrust_range->setText("от 2 до 7");
            ui->l_swing_range->setText("от 4 до 14");
            break;
    }
}

void CharacterSheet::recieveCurrentHitPoints(int hitPoints)
{

    m_currentHP + hitPoints <=  m_hitPoints? m_currentHP += hitPoints : m_currentHP = m_hitPoints;
    ui->lcd_n_current_hp->display(m_currentHP);
}

