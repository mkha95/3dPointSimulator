#include "SimulationGUI.h"
#include <QtWidgets/QMessageBox>
#include <QApplication>
#include <iostream>
#include <sstream>

SimulationGUI::SimulationGUI(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    setDefaultParameters();
    setWindowTitle("3D Physics Point Simulation");
    resize(500, 600);
}

SimulationGUI::~SimulationGUI()
{
}

void SimulationGUI::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    mainLayout = new QVBoxLayout(centralWidget);
    
    basicGroup = new QGroupBox("Basic Parameters");
    QGridLayout *basicLayout = new QGridLayout(basicGroup);
    basicLayout->addWidget(new QLabel("Cube Size:"), 0, 0);
    cubeSizeEdit = new QLineEdit();
    basicLayout->addWidget(cubeSizeEdit, 0, 1);
    basicLayout->addWidget(new QLabel("Number of Points:"), 1, 0);
    numPointsEdit = new QLineEdit();
    basicLayout->addWidget(numPointsEdit, 1, 1);
    basicLayout->addWidget(new QLabel("Simulation Time (s):"), 2, 0);
    simTimeEdit = new QLineEdit();
    basicLayout->addWidget(simTimeEdit, 2, 1);
    
    frictionGroup = new QGroupBox("Friction Parameters");
    QGridLayout *frictionLayout = new QGridLayout(frictionGroup);
    frictionLayout->addWidget(new QLabel("Min Friction:"), 0, 0);
    minFrictionEdit = new QLineEdit();
    frictionLayout->addWidget(minFrictionEdit, 0, 1);
    frictionLayout->addWidget(new QLabel("Max Friction:"), 1, 0);
    maxFrictionEdit = new QLineEdit();
    frictionLayout->addWidget(maxFrictionEdit, 1, 1);
    
    forceGroup = new QGroupBox("Force Parameters");
    QGridLayout *forceLayout = new QGridLayout(forceGroup);
    forceLayout->addWidget(new QLabel("Number of Forces:"), 0, 0);
    numForcesEdit = new QLineEdit();
    forceLayout->addWidget(numForcesEdit, 0, 1);
    forceLayout->addWidget(new QLabel("Min Acceleration:"), 1, 0);
    minAccelEdit = new QLineEdit();
    forceLayout->addWidget(minAccelEdit, 1, 1);
    forceLayout->addWidget(new QLabel("Max Acceleration:"), 2, 0);
    maxAccelEdit = new QLineEdit();
    forceLayout->addWidget(maxAccelEdit, 2, 1);
    
    velocityGroup = new QGroupBox("Velocity Parameters");
    QGridLayout *velocityLayout = new QGridLayout(velocityGroup);
    velocityLayout->addWidget(new QLabel("Min Velocity:"), 0, 0);
    minVelEdit = new QLineEdit();
    velocityLayout->addWidget(minVelEdit, 0, 1);
    velocityLayout->addWidget(new QLabel("Max Velocity:"), 1, 0);
    maxVelEdit = new QLineEdit();
    velocityLayout->addWidget(maxVelEdit, 1, 1);
    velocityLayout->addWidget(new QLabel("Min Initial Velocity:"), 2, 0);
    minInitVelEdit = new QLineEdit();
    velocityLayout->addWidget(minInitVelEdit, 2, 1);
    velocityLayout->addWidget(new QLabel("Max Initial Velocity:"), 3, 0);
    maxInitVelEdit = new QLineEdit();
    velocityLayout->addWidget(maxInitVelEdit, 3, 1);
    
    outputGroup = new QGroupBox("Output Options");
    QGridLayout *outputLayout = new QGridLayout(outputGroup);
    enableVTKCheck = new QCheckBox("Enable VTK Output");
    outputLayout->addWidget(enableVTKCheck, 0, 0);
    outputLayout->addWidget(new QLabel("VTK Filename:"), 1, 0);
    vtkFileEdit = new QLineEdit();
    vtkFileEdit->setPlaceholderText("simulation_output");
    outputLayout->addWidget(vtkFileEdit, 1, 1);
    
    buttonLayout = new QHBoxLayout();
    runButton = new QPushButton("Run Simulation");
    resetButton = new QPushButton("Reset to Defaults");
    buttonLayout->addWidget(resetButton);
    buttonLayout->addWidget(runButton);
    
    outputText = new QTextEdit();
    outputText->setReadOnly(true);
    outputText->setMaximumHeight(150);
    outputText->setPlaceholderText("Simulation output will appear here...");
    
    mainLayout->addWidget(basicGroup);
    mainLayout->addWidget(frictionGroup);
    mainLayout->addWidget(forceGroup);
    mainLayout->addWidget(velocityGroup);
    mainLayout->addWidget(outputGroup);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(new QLabel("Output:"));
    mainLayout->addWidget(outputText);
    
    connect(runButton, &QPushButton::clicked, this, &SimulationGUI::runSimulation);
    connect(resetButton, &QPushButton::clicked, this, &SimulationGUI::resetParameters);
}

void SimulationGUI::setDefaultParameters()
{
    cubeSizeEdit->setText("10.0");
    numPointsEdit->setText("5");
    minFrictionEdit->setText("0.1");
    maxFrictionEdit->setText("0.5");
    numForcesEdit->setText("2");
    minAccelEdit->setText("-2.0");
    maxAccelEdit->setText("2.0");
    minVelEdit->setText("-1.0");
    maxVelEdit->setText("1.0");
    minInitVelEdit->setText("-0.5");
    maxInitVelEdit->setText("0.5");
    simTimeEdit->setText("10");
    vtkFileEdit->setText("simulation_output");
    enableVTKCheck->setChecked(false);
}

SimulationParams SimulationGUI::getParametersFromGUI()
{
    SimulationParams params;
    
    params.cubeSize = cubeSizeEdit->text().toDouble();
    params.numPoints = numPointsEdit->text().toInt();
    params.minFriction = minFrictionEdit->text().toDouble();
    params.maxFriction = maxFrictionEdit->text().toDouble();
    params.numForces = numForcesEdit->text().toInt();
    params.minAcceleration = minAccelEdit->text().toDouble();
    params.maxAcceleration = maxAccelEdit->text().toDouble();
    params.minVelocity = minVelEdit->text().toDouble();
    params.maxVelocity = maxVelEdit->text().toDouble();
    params.minInitialVelocity = minInitVelEdit->text().toDouble();
    params.maxInitialVelocity = maxInitVelEdit->text().toDouble();
    params.simulationTime = simTimeEdit->text().toInt();
    params.enableVTKOutput = enableVTKCheck->isChecked();
    params.vtkOutputFile = vtkFileEdit->text().toStdString();
    
    return params;
}

void SimulationGUI::runSimulation()
{
    try {
        SimulationParams params = getParametersFromGUI();
        
        if (params.cubeSize <= 0 || params.numPoints <= 0 || params.numForces <= 0 || params.simulationTime < 0) {
            QMessageBox::warning(this, "Invalid Parameters", 
                "Error: Invalid parameter values. All values must be positive (except simulation time which can be 0).");
            return;
        }
        
        if (params.minFriction > params.maxFriction || 
            params.minAcceleration > params.maxAcceleration ||
            params.minVelocity > params.maxVelocity ||
            params.minInitialVelocity > params.maxInitialVelocity) {
            QMessageBox::warning(this, "Invalid Parameters",
                "Error: Minimum values cannot be greater than maximum values.");
            return;
        }
        
        outputText->clear();
        std::ostringstream oss;
        oss << "3D Physics Point Simulation\n";
        oss << "============================\n";
        oss << "Cube size: " << params.cubeSize << "\n";
        oss << "Number of points: " << params.numPoints << "\n";
        oss << "Friction range: [" << params.minFriction << ", " << params.maxFriction << "]\n";
        oss << "Number of forces: " << params.numForces << "\n";
        oss << "Acceleration range: [" << params.minAcceleration << ", " << params.maxAcceleration << "]\n";
        oss << "Velocity range: [" << params.minVelocity << ", " << params.maxVelocity << "]\n";
        oss << "Initial velocity range: [" << params.minInitialVelocity << ", " << params.maxInitialVelocity << "]\n";
        oss << "Simulation time: " << params.simulationTime << " seconds\n";
        if (params.enableVTKOutput) {
            oss << "VTK output file: " << params.vtkOutputFile << "\n";
        }
        oss << "\nRunning simulation...\n";
        
        outputText->setPlainText(QString::fromStdString(oss.str()));
        QApplication::processEvents();
        
        runButton->setEnabled(false);
        runButton->setText("Running...");
        
        Simulator simulator(params);
        simulator.simulate();
        
        outputText->append("Simulation completed successfully!");
        
        runButton->setEnabled(true);
        runButton->setText("Run Simulation");
        
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Simulation Error", 
            QString("Error running simulation: %1").arg(e.what()));
        runButton->setEnabled(true);
        runButton->setText("Run Simulation");
    }
}

void SimulationGUI::resetParameters()
{
    setDefaultParameters();
    outputText->clear();
}

