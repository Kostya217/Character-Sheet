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
    connect(heal, &Heal::sendHitPoints, this, &CharacterSheet::recieveHitPoints);

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

    ui->lcd_n_hit_points->display(m_hit_points);
    connect(ui->b_hit_points_plus, &QPushButton::clicked, this, &CharacterSheet::pressButton);
    connect(ui->b_hit_points_minus, &QPushButton::clicked, this, &CharacterSheet::pressButton);

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
        m_hit_points = m_strength < logicsPlusButton(m_strength, 0)? logicsDependentPlusButton(m_hit_points, m_strength + 1, 0): m_hit_points;
        m_strength = logicsPlusButton(m_strength, 10);
        rangeDamage();
    }
    else if(button == ui->b_strength_minus){
        m_hit_points = m_strength > logicsMinusButton(m_strength, 0) ? logicsDependentMinusButton(m_hit_points, m_strength + 2, 0): m_hit_points;
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
        m_hit_points = logicsDependentPlusButton(m_hit_points, m_strength, 2);
    }
    else if(button == ui->b_hit_points_minus){
        m_hit_points = logicsDependentMinusButton(m_hit_points, m_strength, 2);
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
    ui->lcd_n_hit_points->display(m_hit_points);
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
                                                              tr("Sheet(*.chs);;All Files (*)"));
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
    ui->lcd_n_hit_points->display(m_hit_points = json["Hit Points"].toInt());
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
    data.insert("Hit Points", m_hit_points);
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

void CharacterSheet::pressHeal()
{
    Heal *heal = new Heal();
    heal->show();
}

void CharacterSheet::rangeDamage()
{
    switch(m_strength){
        case 1:
        case 2:
            ui->l_thrust_range->setText("от (-5) до 0");
            ui->l_swing_range->setText("от (-4) до 1");
            break;

        case 3:
        case 4:
            ui->l_thrust_range->setText("от (-4) до 1");
            ui->l_swing_range->setText("от (-3) до 2");
            break;

        case 5:
        case 6:
            ui->l_thrust_range->setText("от (-3) до 2");
            ui->l_swing_range->setText("от (-2) до 3");
            break;

        case 7:
        case 8:
            ui->l_thrust_range->setText("от (-2) до 3");
            ui->l_swing_range->setText("от (-1) до 4");
             break;

        case 9:
            ui->l_thrust_range->setText("от (-1) до 4");
            ui->l_swing_range->setText("от 0 до 5");
            break;

        case 10:
            ui->l_thrust_range->setText("от (-1) до 4");
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

        case 17:
            ui->l_thrust_range->setText("от 3 до 8");
            ui->l_swing_range->setText("от 2 до 17");
            break;
        case 18:
            ui->l_thrust_range->setText("от 3 до 8");
            ui->l_swing_range->setText("от 3 до 18");
            break;

        case 19:
            ui->l_thrust_range->setText("от 1 до 11");
            ui->l_swing_range->setText("от 4 до 19");
            break;
        case 20:
            ui->l_thrust_range->setText("от 1 до 11");
            ui->l_swing_range->setText("от 5 до 20");
            break;

        case 21:
            ui->l_thrust_range->setText("от 2 до 12");
            ui->l_swing_range->setText("от 3 до 23");
            break;
        case 22:
            ui->l_thrust_range->setText("от 2 до 12");
            ui->l_swing_range->setText("от 4 до 24");
            break;

        case 23:
            ui->l_thrust_range->setText("от 3 до 13");
            ui->l_swing_range->setText("от 5 до 25");
            break;
        case 24:
            ui->l_thrust_range->setText("от 3 до 13");
            ui->l_swing_range->setText("от 6 до 26");
            break;

        case 25:
            ui->l_thrust_range->setText("от 4 до 14");
            ui->l_swing_range->setText("от 4 до 29");
            break;
        case 26:
            ui->l_thrust_range->setText("от 4 до 14");
            ui->l_swing_range->setText("от 5 до 30");
            break;

        case 27:
        case 28:
            ui->l_thrust_range->setText("от 2 до 17");
            ui->l_swing_range->setText("от 6 до 26");
            break;

        case 29:
        case 30:
            ui->l_thrust_range->setText("от 3 до 18");
            ui->l_swing_range->setText("от 7 до 27");
            break;

        case 31:
        case 32:
            ui->l_thrust_range->setText("4 до 19");
            ui->l_swing_range->setText("от 5 до 35");
            break;

        case 33:
        case 34:
            ui->l_thrust_range->setText("5 до 20");
            ui->l_swing_range->setText("от 6 до 36");
            break;

        case 35:
        case 36:
            ui->l_thrust_range->setText("3 до 23");
            ui->l_swing_range->setText("от 7 до 37");
            break;

        case 37:
        case 38:
            ui->l_thrust_range->setText("4 до 24");
            ui->l_swing_range->setText("от 8 до 38");
                break;

        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
            ui->l_thrust_range->setText("5 до 25");
            ui->l_swing_range->setText("от 6 до 41");
            break;

        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
            ui->l_thrust_range->setText("5 до 30");
            ui->l_swing_range->setText("от 8 до 43");
            break;

        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
            ui->l_thrust_range->setText("7 до 32");
            ui->l_swing_range->setText("от 7 до 47");
            break;


        case 55:
        case 56:
        case 57:
        case 58:
        case 59:
            ui->l_thrust_range->setText("6 до 36");
            ui->l_swing_range->setText("от 9 до 49");
            break;

        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
            ui->l_thrust_range->setText("6 до 41");
            ui->l_swing_range->setText("от 9 до 54");
            break;

        case 65:
        case 66:
        case 67:
        case 68:
        case 69:
            ui->l_thrust_range->setText("8 до 43");
            ui->l_swing_range->setText("от 11 до 56");
            break;
        case 70:
        case 71:
        case 72:
        case 73:
        case 74:
            ui->l_thrust_range->setText("8 до 48");
            ui->l_swing_range->setText("от 10 до 60");
            break;

        case 75:
        case 76:
        case 77:
        case 78:
        case 79:
            ui->l_thrust_range->setText("10 до 50");
            ui->l_swing_range->setText("от 12 до 62");
            break;

        case 80:
        case 81:
        case 82:
        case 83:
        case 84:
            ui->l_thrust_range->setText("9 до 54");
            ui->l_swing_range->setText("от 11 до 66");
            break;

        case 85:
        case 86:
        case 87:
        case 88:
        case 89:
            ui->l_thrust_range->setText("11 до 56");
            ui->l_swing_range->setText("от 13 до 68");
            break;

        case 90:
        case 91:
        case 92:
        case 93:
        case 94:
            ui->l_thrust_range->setText("10 до 60");
            ui->l_swing_range->setText("от 12 до 72");
            break;

        case 95:
        case 96:
        case 97:
        case 98:
        case 99:
            ui->l_thrust_range->setText("12 до 62");
            ui->l_swing_range->setText("от 14 до 74");
            break;
        case 100:
            ui->l_thrust_range->setText("от 11 до 66");
            ui->l_swing_range->setText("от 13 до 78");
            break;
    }
}

void CharacterSheet::recieveHitPoints(int hitPoints)
{

    m_hit_points + hitPoints <= ceil(m_strength * 1.3) ? m_hit_points += hitPoints : m_hit_points = ceil(m_strength * 1.3) ;
    ui->lcd_n_hit_points->display(this->m_hit_points);
}

