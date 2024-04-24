#pragma once
#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;

namespace PolygonalLibrary{

//invoco le funzioni necessarie ad importare i dati per costruire la mesh
bool importMesh (const string& path, PolygonalMesh& mesh);
bool importCell0D (const string& path, PolygonalMesh& mesh);
bool importCell1D (const string& path, PolygonalMesh& mesh);
bool importCell2D (const string& path, PolygonalMesh& mesh);

//definisco le funzioni per testare la corretta importazione della mesh
bool verificaEdges (const PolygonalMesh& mesh, const double& toll);
bool verificaAreas (const PolygonalMesh& mesh, const double& toll);

//alcune funzioni di supporto
double trova_massimo(const double& a, const double& b, const double& c);
double calcolo_distanza_euclidea (const Vector2d& v1, const Vector2d& v2);
double formula_Gauss_aree(const vector <Vector2d>& vertici);
}


