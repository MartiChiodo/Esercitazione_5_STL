#include "Utils.hpp"
#include <fstream>
#include <sstream>
#include <cmath>


namespace PolygonalLibrary{

//funzione per importare la mesh
bool importMesh (const string& path, PolygonalMesh& mesh){

    if (!importCell0D(path + "/Cell0Ds.csv", mesh)){return false; }
    else{
        //verifico di aver importato correttamente i marker non nulli
        cout << "Cell0D marker:" << endl;
        if (mesh.Cell0DMarkers.size() == 0){cout << "Non ci sono marker non nulli per le celle 0D." << endl;}
        else{
            for(auto it = mesh.Cell0DMarkers.begin(); it != mesh.Cell0DMarkers.end(); it++){
                cout << "key:\t" << it -> first << "\t values:";
                for(const unsigned int id : it -> second)
                    cout << "\t" << id;

                cout << endl;
            }
        }
    }


    if (!importCell1D(path + "/Cell1Ds.csv", mesh)){return false;}
    else{
        //verifico di aver importato correttamente i marker non nulli
        cout << "Cell1D marker:" << endl;
        if (mesh.Cell1DMarkers.size() == 0){cout << "Non ci sono marker non nulli per le celle 1D." << endl;}
        else{
            for(auto it = mesh.Cell1DMarkers.begin(); it != mesh.Cell1DMarkers.end(); it++){
                cout << "key:\t" << it -> first << "\t values:";
                for(const unsigned int id : it -> second)
                    cout << "\t" << id;

                cout << endl;
            }
        }
    }

    if (!importCell2D(path + "/Cell2Ds.csv", mesh)){return false;}
    else{
        //verifico di aver importato correttamente i marker non nulli
        cout << "Cell2D marker: " << endl;
        if (mesh.Cell2DMarkers.size() == 0){cout << "Non ci sono marker non nulli per le celle 2D." << endl;}
        else{
            for(auto it = mesh.Cell2DMarkers.begin(); it != mesh.Cell2DMarkers.end(); it++){
                cout << "key:\t" << it -> first << "\t values:";
                for(const unsigned int id : it -> second)
                    cout << "\t" << id;

                cout << endl;
            }
        }

    }

    //se non ho avuto problemi nell'importare i tre tipi di celle, la funzione ritorna true
    return true;
}

//seguono le funzioni che importano le varie celle
bool importCell0D (const string& path, PolygonalMesh& mesh){

    //apro il file di input e verifico che nulla sia crashato
    ifstream file(path);
    if(file.fail()){
        return false;
    }

    //ignoro la prima riga di intestazione
    string header;
    getline(file, header);

    //mi leggo i dati e li incodo alla lista di supporto
    list<string> lines;
    string line;
    while(getline(file, line)){
        lines.push_back(line);
    }
    file.close();

    //riservo ai vettori la capacità necessaria che deduco dalla dimensione della lista
    mesh.NumberCell0D = lines.size();

    if (mesh.NumberCell0D == 0){
        cerr << "There is no cell 0D." << endl;
        return false;
    }

    mesh.IdCell0D.reserve(mesh.NumberCell0D);
    mesh.CoordinatesCell0D.reserve(mesh.NumberCell0D);

    //scorro la lista, mi converto la stringa nei dati necessari e li salvo nelle strutture dati create ad hoc
    for (const string& line : lines){

        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2d coord;
        char delimiter; //mi serve per fermare la conversione ogni volta che incontro un ;

        //conversione dell'oggetto stringa in oggetti che hanno il tipo richiesto
        converter >>  id >> delimiter >> marker >> delimiter >> coord(0) >> delimiter >> coord(1);

        //salvo i dati nelle apposite strutture dati
        mesh.CoordinatesCell0D.push_back(coord);
        mesh.IdCell0D.push_back(id);

        //mi salvo i marker che non sono nulli
        unsigned int zero = 0;
        if( marker != zero){
            auto ret = (mesh.Cell0DMarkers).insert({marker, {id}});
            if(!ret.second)
                (ret.first)->second.push_back(id);
        }
    }

    return true;
}


bool importCell1D (const string& path, PolygonalMesh& mesh){

    //apro il file di input e verifico che nulla sia crashato
    ifstream file(path);
    if(file.fail()){
        return false;
    }

    //ignoro la prima riga di intestazione
    string header;
    getline(file, header);

    //mi leggo i dati e li incodo alla lista di supporto
    list<string> lines;
    string line;
    while(getline(file, line)){
        lines.push_back(line);
    }

    //riservo ai vettori la capacità necessaria che deduco dalla dimensione della lista
    mesh.NumberCell1D = lines.size();
    if (mesh.NumberCell1D == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    mesh.VerticesCell1D.reserve(mesh.NumberCell1D);
    mesh.IdCell1D.reserve(mesh.NumberCell1D);


    //scorro la lista, mi converto la stringa nei dati necessari e li salvo nelle strutture dati create ad hoc
    for (const string& line : lines){

        istringstream convert(line);

        //varibili temporanee finalizzate alla conversione
        unsigned int id;
        unsigned int marker;
        unsigned int origin;
        unsigned int end;
        char delimiter; //mi serve per fermare la conversione ogni volta che incontro un ;

        //conversione dell'oggetto stringa in oggetti che hanno il tipo richiesto
        convert >> id >> delimiter >> marker >> delimiter >> origin >> delimiter  >> end;

        //salvo i dati nelle apposite strutture dati
        mesh.IdCell1D.push_back(id);
        mesh.VerticesCell1D.push_back({origin, end});

        //mi salvo i marker che non sono nulli
        if( marker != 0){
            auto ret = mesh.Cell1DMarkers.insert({marker, {id}});
            if(!ret.second)
                (ret.first)->second.push_back(id);
        }
    }

    file.close();
    return true;
}


bool importCell2D (const string& path, PolygonalMesh& mesh){

    //apro il file di input e verifico che nulla sia crashato
    ifstream file(path);
    if(file.fail()){
        return false;
    }

    //ignoro la prima riga di intestazione
    string header;
    getline(file, header);

    //mi leggo i dati e li incodo alla lista di supporto
    list<string> lines;
    string line;
    while(getline(file, line)){
        lines.push_back(line);
    }

    //riservo ai vettori la capacità necessaria
    mesh.NumberCell2D = lines.size();
    if (mesh.NumberCell2D == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }


    mesh.IdCell2D.reserve(mesh.NumberCell2D);
    mesh.VerticesCell2D.reserve(mesh.NumberCell2D);
    mesh.EdgesCell2D.reserve(mesh.NumberCell2D);


    for (const string& line : lines){

        //inizializzo delle variabili di supporto
        unsigned int id;
        unsigned int marker;
        unsigned int NumVertices;
        unsigned int NumEdges;
        vector <unsigned int> vertices;
        vector <unsigned int> edges;
        char delimiter; //mi serve per fermare la conversione ogni volta che incontro un ;

        istringstream convert(line);

        //converto la stringa
        convert >> id >> delimiter >> marker >> delimiter >> NumVertices >> delimiter;
        vertices.reserve(NumVertices);

        for (unsigned int i = 0; i < NumVertices; i++){
            convert  >> vertices[i] >> delimiter; //mi salvo i vari vertici in un array
        }

        convert >> NumEdges >> delimiter;
        edges.reserve(NumEdges);
        for (unsigned int i = 0; i < NumVertices; i++){
            convert  >> vertices[i] >> delimiter; //mi salvo i vari vertici in un array
        }

        //mi salvo i dati nelle loro strutture dati
        mesh.IdCell2D.push_back(id);
        mesh.VerticesCell2D.push_back(vertices);
        mesh.EdgesCell2D.push_back(edges);

        //mi salvo i marker che non sono nulli
        if( marker != 0)
        {
            auto ret = mesh.Cell2DMarkers.insert({marker, {id}});
            if(!ret.second)
                (ret.first)->second.push_back(id);
        }

    }

    file.close();
    return true;
}


//definisco le funzioni per testare la corretta importazione della mesh
bool verificaEdges (const PolygonalMesh& mesh, const double& toll){
    bool verifica = true;
    for (unsigned int i = 0; i<mesh.NumberCell1D; i++){
        array<unsigned int, 2> vert = mesh.VerticesCell1D[i];
        Vector2d origin = mesh.CoordinatesCell0D[vert[0]];
        Vector2d end = mesh.CoordinatesCell0D[vert[1]];

        double distanza = calcolo_distanza_euclidea(origin, end);

        if (distanza < toll){verifica  = false;}
    }

    return verifica;
}


bool verificaAreas (const PolygonalMesh& mesh, const double& toll){
    bool verifica = true;

    for(unsigned int i = 0; i< mesh.NumberCell2D; i++){
        //mi salvo le coordinate dei vertici in una struttura di tipo vettori di array
        vector <Vector2d> vertici;
        for (unsigned k = 0; k < mesh.VerticesCell2D[i].size(); k++){
            vertici[i] = mesh.CoordinatesCell0D[mesh.VerticesCell2D[i][k]];
            if (formula_Gauss_aree(vertici) < toll){verifica = false;}
        }
    }
    return verifica;
}



//alcune funzioni di supporto
double trova_massimo(const double& a, const double& b, const double& c){
    double mass = max(max(a,b),c);
    return mass;
}

double calcolo_distanza_euclidea (const Vector2d& v1, const Vector2d& v2){
    double dist = sqrt(pow((v1[0] - v2[0]), 2) + pow((v1[1] - v2[1]), 2));
    return dist;
}

double formula_Gauss_aree(const vector <Vector2d>& vertici){
    double area = 0;

    // area  = 0.5 * sum (x(i)*y(i+1) - x(i+1)*y(i) con i=1,..., n)
    // si noti che x(n+1) = x(1) e y(n+1) = y(1) quindi l'ultimo termine della sommatoria lo trattiamo a parte
    for (unsigned int i = 0; i < vertici.size() - 1; i++){
        area += vertici[i][0] * vertici[i+1][1] - vertici[i+1][0] * vertici[i][1];
    }
    area +=  vertici[vertici.size()-1][0] * vertici[0][1] - vertici[vertici.size()-1][0] * vertici[0][1];
    area *= 0.5;

    return area;
}


}
