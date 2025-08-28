#ifndef SIMULATIONGUI_H
#define SIMULATIONGUI_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QTextEdit>
#include "Simulator.h"

class SimulationGUI : public QMainWindow
{
    Q_OBJECT

public:
    SimulationGUI(QWidget *parent = nullptr);
    ~SimulationGUI();

private slots:
    void runSimulation();
    void resetParameters();

private:
    void setupUI();
    SimulationParams getParametersFromGUI();
    void setDefaultParameters();

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QGridLayout *paramLayout;
    QHBoxLayout *buttonLayout;
    
    QGroupBox *basicGroup;
    QGroupBox *frictionGroup;
    QGroupBox *forceGroup;
    QGroupBox *velocityGroup;
    QGroupBox *outputGroup;
    
    QLineEdit *cubeSizeEdit;
    QLineEdit *numPointsEdit;
    QLineEdit *minFrictionEdit;
    QLineEdit *maxFrictionEdit;
    QLineEdit *numForcesEdit;
    QLineEdit *minAccelEdit;
    QLineEdit *maxAccelEdit;
    QLineEdit *minVelEdit;
    QLineEdit *maxVelEdit;
    QLineEdit *minInitVelEdit;
    QLineEdit *maxInitVelEdit;
    QLineEdit *simTimeEdit;
    QLineEdit *vtkFileEdit;
    QCheckBox *enableVTKCheck;
    
    QPushButton *runButton;
    QPushButton *resetButton;
    
    QTextEdit *outputText;
};

#endif // SIMULATIONGUI_H