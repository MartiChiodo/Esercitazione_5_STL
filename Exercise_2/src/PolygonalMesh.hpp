#pragma once
#include <iostream>
#include <vector>
#include <Eigen/Eigen>

using namespace std;
using namespace Eigen;

namespace PolygonalLibrary{

/*
La struttura dati che devo definire per le mesh poligonali è molto simile a quella vista per le mesh triangolari, con l'unica
accortezza che non sappiamo a priori la dimensione delle celle 2-dimensionali quindi non possiamo usare un vettore di array ma
dovremo sfruttare una struttura dati che ci permetta l'allocazione dinamica in memoria dei vertici e dei lati delle celle 2-dim.
 */


struct PolygonalMesh{

    //strutture per la definzione delle celle 0-dim
    unsigned int NumberCell0D = 0;
    vector <unsigned int> IdCell0D = {}; //vettore 1 x NumberCell0D
    vector <Vector2d> CoordinatesCell0D = {}; // vettore 2 x NumberCell0D
    map<unsigned int, list<unsigned int>> Cell0DMarkers = {}; // dimensione 1 x NumberCell0D

    //strutture per la definzione delle celle 1-dim
    unsigned int NumberCell1D = 0;
    vector <unsigned int> IdCell1D = {}; //vettore 1 x NumberCell1D
    vector <array<unsigned int, 2>> VerticesCell1D = {}; //vettore  2x NumberCell1D
    map<unsigned int, list<unsigned int>> Cell1DMarkers = {}; //dimensione 1 x NumberCell1D

    //strutture per la definzione delle celle 2-dim
    unsigned int NumberCell2D = 0;
    vector <unsigned int> IdCell2D = {};
    vector <vector<unsigned int>> VerticesCell2D = {};
    vector <vector<unsigned int>> EdgesCell2D = {};
    map<unsigned int, list<unsigned int>> Cell2DMarkers = {};

};

}
