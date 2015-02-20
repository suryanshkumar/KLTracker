/**
 * Author: Suryansh Kumar
 *
 **/

#include "dialog.h"
#include "ui_dialog.h"
#include "trackfeature.h"
#include <QtCore>

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);
    vid.open(0); //Use attached camera to take the feed.
    if(vid.isOpened()==false){return ;}

    tmr = new QTimer(this);
    connect(tmr, SIGNAL(timeout()), this, SLOT(PauseorRun()));
    tmr->start(10);

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::PauseorRun(){
    vid >>InputFrame2;
    InputFrame2.copyTo(InputFrame1);
    for(int i = 0; i<2; i++)
    {
      vid>>InputFrame2;
    }

trackfeature tf(InputFrame1, InputFrame2);
OutputFrame = tf.drawfeatureTrack();
WarpOutput = tf.getWarpImage();
cv::absdiff(InputFrame1, WarpOutput, WarpOutput);
cv::cvtColor(InputFrame1, InputFrame1, CV_BGR2RGB);
cv::cvtColor(OutputFrame, OutputFrame, CV_BGR2RGB);
//cv::cvtColor(WarpOutput, WarpOutput, CV_BGR2RGB);


QImage qInputFrame((uchar*) InputFrame1.data, InputFrame1.cols, InputFrame1.rows, InputFrame1.step, QImage::Format_RGB888 );
QImage qOutputFrame((uchar*) OutputFrame.data, OutputFrame.cols, OutputFrame.rows, OutputFrame.step, QImage::QImage::Format_RGB888);


ui->lblInputVideo->setPixmap(QPixmap::fromImage(qInputFrame));
ui->lblOuputVideo->setPixmap(QPixmap::fromImage(qOutputFrame));
}

void Dialog::on_pushButton_Track_clicked()
{

    if(tmr->isActive()==true)
    {
      tmr->stop();
      ui->pushButton_Track->setText("Resume");
    }else
    {
      tmr->start(10);
      ui->pushButton_Track->setText("Pause");
    }
}


