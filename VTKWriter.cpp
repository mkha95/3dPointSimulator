#include "VTKWriter.h"
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkVertex.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkNew.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

void VTKWriter::writePoints(const std::vector<Point>& points, const std::string& filename, int timeStep) {
    vtkNew<vtkPoints> vtkPoints;
    vtkNew<vtkCellArray> vertices;
    vtkNew<vtkDoubleArray> velocityArray;
    vtkNew<vtkDoubleArray> accelerationArray;
    vtkNew<vtkDoubleArray> frictionArray;

    velocityArray->SetName("Velocity");
    velocityArray->SetNumberOfComponents(3);

    accelerationArray->SetName("Acceleration");
    accelerationArray->SetNumberOfComponents(3);

    frictionArray->SetName("Friction");
    frictionArray->SetNumberOfComponents(1);

    for (size_t i = 0; i < points.size(); ++i) {
        const Point& point = points[i];

        vtkPoints->InsertNextPoint(point.position.x, point.position.y, point.position.z);

        vtkNew<vtkVertex> vertex;
        vertex->GetPointIds()->SetId(0, i);
        vertices->InsertNextCell(vertex);

        double velocity[3] = {point.velocity.x, point.velocity.y, point.velocity.z};
        velocityArray->InsertNextTuple(velocity);

        double acceleration[3] = {point.acceleration.x, point.acceleration.y, point.acceleration.z};
        accelerationArray->InsertNextTuple(acceleration);

        frictionArray->InsertNextValue(point.frictionCoefficient);
    }

    vtkNew<vtkPolyData> polyData;
    polyData->SetPoints(vtkPoints);
    polyData->SetVerts(vertices);
    polyData->GetPointData()->SetVectors(velocityArray);
    polyData->GetPointData()->AddArray(accelerationArray);
    polyData->GetPointData()->AddArray(frictionArray);

    std::ostringstream oss;
    oss << filename << "_t" << std::setfill('0') << std::setw(4) << timeStep << ".vtp";

    vtkNew<vtkXMLPolyDataWriter> writer;
    writer->SetFileName(oss.str().c_str());
    writer->SetInputData(polyData);
    writer->Write();

    std::cout << "VTK output written to: " << oss.str() << std::endl;
}

void VTKWriter::writeTimeSeriesPoints(const std::vector<std::vector<Point>>& pointsHistory, const std::string& baseFilename) {
    for (size_t t = 0; t < pointsHistory.size(); ++t) {
        writePoints(pointsHistory[t], baseFilename, static_cast<int>(t));
    }

    std::ostringstream pvsm;
    pvsm << baseFilename << ".pvd";

    std::ofstream pvdFile(pvsm.str());
    pvdFile << "<?xml version=\"1.0\"?>\n";
    pvdFile << "<VTKFile type=\"Collection\" version=\"0.1\">\n";
    pvdFile << "  <Collection>\n";

    for (size_t t = 0; t < pointsHistory.size(); ++t) {
        std::ostringstream filename;
        filename << baseFilename << "_t" << std::setfill('0') << std::setw(4) << t << ".vtp";
        pvdFile << "    <DataSet timestep=\"" << t << "\" file=\"" << filename.str() << "\"/>\n";
    }

    pvdFile << "  </Collection>\n";
    pvdFile << "</VTKFile>\n";
    pvdFile.close();

    std::cout << "ParaView collection file written to: " << pvsm.str() << std::endl;
}
