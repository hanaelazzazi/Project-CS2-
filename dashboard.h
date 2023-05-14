#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>
#include "choose.h"
#include "detection.h"
#include <QFileDialog>

namespace Ui {
class dashboard;
}

class dashboard : public QDialog
{
    Q_OBJECT

public:
   // explicit dashboard(detection* detectionInstance = nullptr, QWidget *parent = nullptr);
    explicit dashboard(QWidget *parent = nullptr);
    ~dashboard();


private slots:
    void on_pushButton_clicked();

    void on_push_clicked();

public:
    void on_pointsLabel_linkActivated(const QString &link);
    void on_levelLabel_linkActivated(const QString &link);
    void on_dashboardLabel_linkActivated(const QString &link);

    void on_level_linkActivated(const QString &link);

    void on_points_linkActivated(const QString &link);

    void on_dashboard_2_linkActivated(const QString &link);

    //void updatePoints(bool hasPlagiarism, float plagiarismPercentage, QString username);

    void updateRank(QString username);

private:
    Ui::dashboard *ui;
    Choose *c;
    QString fileName=" ";
    QString filePathWriting ="";
};

#endif // DASHBOARD_H
