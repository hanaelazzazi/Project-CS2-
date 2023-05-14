#include "dashboard.h"
#include "ui_dashboard.h"
#include "choose.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "detection.h"
#include <QFile>
#include <QTextStream>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "plagirism.h"

dashboard::dashboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dashboard)
{
    ui->setupUi(this);
}

dashboard::~dashboard()
{
    delete ui;
}

void dashboard::on_pushButton_clicked()
{
    c =new Choose();
    c->show();
    this->close();
}

/*void dashboard::updatePoints( )
{

}
*/
void dashboard::updateRank(QString username)
{
    // Retrieve all users from the database sorted by level in descending order
    QSqlQuery query("/Users/hanaelazzazi/Desktop/Spring 2023/CS 2/Project and Paper/Database/signup.db");
    query.prepare("SELECT Username, Level FROM clients ORDER BY Level DESC");
    query.exec();

    int rank = 0; // Initialize the rank to 0
    int currentUserLevel=0; // Initialize the current user's level to 0

    // Iterate over the query results
    while (query.next()) {
        QString user = query.value(0).toString();
        int level = query.value(1).toInt();

        if (user == username) { // If the current row corresponds to the current user
            currentUserLevel = level; // Save the current user's level
            break; // Stop iterating over the results
        }

        rank++; // Increment the rank for each user that has been iterated over
    }

    // Calculate the user's rank based on their level
    int userRank = rank + 1;

    // Update the dashboard label with the user's rank
    ui->dashboard_2->setText(QString("%1").arg(userRank));
}

void dashboard::on_push_clicked()
{
    float plagiarismPercentage;
    QString username;
    float hasPlagiarism;
    QLabel *pointsLabel = ui->points;
    QLabel *levelLabel = ui->level;

    updateRank(username);
    int currentPoints = pointsLabel->text().toInt();
    int updatedPoints = currentPoints;

    int currentLevel = levelLabel->text().toInt();
    int updatedLevel = currentLevel;  // Initialize the variable with the current level

    // Check plagiarism percentage and update points accordingly
    if (hasPlagiarism && plagiarismPercentage > 50.0) {
        updatedPoints -= 5; // Deduct 5 points for high plagiarism
    } else if (hasPlagiarism && plagiarismPercentage <= 50.0) {
        updatedPoints += 5; // Add 5 points for low plagiarism
    }

    // Check if level needs to be updated
    if (updatedPoints >= currentLevel * 10) {
        updatedLevel++; // Increase level if points meet or exceed level requirement
    } else if (updatedPoints < (currentLevel - 1) * 10) {
        updatedLevel--; // Decrease level if points fall below level requirement
    }

    // Update points and level labels
    pointsLabel->setText(QString::number(updatedPoints));
    levelLabel->setText(QString::number(updatedLevel));

    // Update clients table in database
    QSqlQuery query("/Users/hanaelazzazi/Desktop/Spring 2023/CS 2/Project and Paper/Database/signup.db");
    query.prepare("UPDATE clients SET  Level = :Level, Points = :Points WHERE Username = :Username");
    query.bindValue(":Points", updatedPoints);
    query.bindValue(":Level", updatedLevel);  // Use the updatedLevel variable here
    query.bindValue(":Username", username);
    query.exec();
}
