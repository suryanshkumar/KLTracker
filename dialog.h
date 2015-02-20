/**
 * Author: Suryansh Kumar
 *
 **/

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>



namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    
private:
    Ui::Dialog *ui;
    cv::VideoCapture vid;

    cv::Mat InputFrame1, InputFrame2;
    cv::Mat OutputFrame;
    cv::Mat WarpOutput;

    QImage qInputFrame;
    QImage qOutputFrame;

    QTimer* tmr;

public slots:
    void PauseorRun();


private slots:
    void on_pushButton_Track_clicked();

};

#endif // DIALOG_H
