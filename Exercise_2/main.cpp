#include "Utils.hpp"
#include "PolygonalMesh.hpp"

using namespace std;
using namespace PolygonalLibrary;

int main()
{
    double epsilon_macc = numeric_limits<double>::epsilon();
    double toll_1D = pow(10,-15);
    double area_min = pow(toll_1D, 2) /4 * sqrt(3); //la più piccola area calcolabile è quella di un triangolo equilatero di lato toll_1D
    double toll_2D = trova_massimo(epsilon_macc,toll_1D, area_min);

    //definisco un oggetto di tipo PolygonalMesh e poi la importo
    PolygonalMesh mesh;
    string path = "PolygonalMesh";

    if (! importMesh(path, mesh)){
        cerr << "Errore nell'importazione della mesh poligonale." << endl;
        return 1;
    }

    cout << endl;

    //eseguiamo dei test per verificare la correttezza della mesh importata
    if (!verificaEdges(mesh, toll_1D)){cout << "Alcune celle 1D sono dei lati degeneri." << endl;}
    else {cout << "La mesh ha superato la verifica di lati degeneri." << endl;}

    if (!verificaAreas(mesh, toll_2D)){cout << "Alcune celle 2D hanno area degenere" << endl;}
    else {cout << "La mesh ha superato la verifica di aree degeneri." << endl;}


    return 0;
}
