#ifndef DETECTION_H
#define DETECTION_H

#include <QDialog>
#include "upload.h"
#include "dashboard.h"
#include "ui_detection.h"

namespace Ui {
class detection;
}
class upload;
class detection : public QDialog
{
    Q_OBJECT

public:
    explicit detection(QWidget *parent = nullptr);
    ~detection();
    QString getPlagiarismDisplayText() const {
        return plagirismdisplay->text();
    }
public slots:
    void v11(QString q);
    void v22(QString w);

signals:
    QString value(QString x);

private slots:

    void on_Back_clicked();

    void on_next_clicked();

private:
    Ui::detection *ui;
    upload *u;
    QLabel *plagirismdisplay;
};

#endif // DETECTION_H
