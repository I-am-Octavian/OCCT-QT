#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LearnQT.h"

class Viewer;

class LearnQT : public QMainWindow
{
    Q_OBJECT

public:
    LearnQT(QWidget *parent = nullptr);
    ~LearnQT();


private slots:
    void on_actionBox_triggered();

    void on_actionSphere_triggered();

    void on_actionAbout_triggered();

    void on_actionReset_triggered();

private:
    Ui::LearnQTClass ui;

    Viewer* m_Viewer;
};
