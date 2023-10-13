#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QKeyEvent>
#include <QMainWindow>


#include <QTcpSocket>
#include <QString>
#include <QByteArray>

#include <unistd.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();




signals:
        void car_control(int car_status);

private slots:

    void ReadData();
    void ReadError(QAbstractSocket::SocketError);
    void car_status_handler(int car_status);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent* event);

#if 0
    void on_car_go_pressed();

    void on_car_back_pressed();

    void on_car_left_pressed();

    void on_car_right_pressed();

    void on_car_go_released();

    void on_car_back_released();

    void on_car_left_released();

    void on_car_right_released();
#endif

private:
    int KeyValue ;
    Ui::MainWindow *ui;
    QTcpSocket  *client ;
};

#endif // MAINWINDOW_H
