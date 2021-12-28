#include<iostream>
#include<string>
#include<fstream>

using namespace std;
struct cancion {
    char nbre[30];
    float duracion;
};

struct disco {
    char nbre[50];
    unsigned int idDisco;
    cancion listaCanciones[30];
    int nCanciones;
};


disco *obtenerDiscos(string filename, float duracion, int &size) {
    int n, contador=0;
    disco* A;
    fstream fp;
    disco* Retorno;

    fp.open(filename, ios::in|ios::binary);
    fp.read((char * )&n, sizeof(int));
    A = new disco[n];
    fp.read((char*)A, n*sizeof(disco));
    fp.close();

    int indices[n];
    for (int i = 0; i < n; i++)
    {
        float limite = 0.0;
        for (int x = 0; x < 30; x++) 
        {
            limite += A[i].listaCanciones[x].duracion;
            
        }
        if (limite <= duracion) {
            size++;
        }
        
    }
    Retorno = new disco[size];

    for (int i = 0; i < n; i++)
    {
    
        float limite = 0.0;
        for (int x = 0; x < 30; x++) 
        {
            limite += A[i].listaCanciones[x].duracion;
            
        }
        if (limite <= duracion) {
            Retorno[contador] = A[i];
            contador++;
            
        }
        
    }
    delete [] A;
    return Retorno;







}


int main () {

    return 0;

}