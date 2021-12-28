#include <iostream>
#include <string>
#include <fstream>
#include "TdaPolinomioABB.cpp"

using namespace std;

tABB arbol;

int tamano(){
    fstream fp;
    fp.open("poli.txt", ios::in); // cambiar nombre polinomio.txt

    if(!fp.is_open()){
        cerr << "Error al abrir el archivo" << endl;
        return -1;
    }
    string s;
    int largo = 0;
    while (getline(fp,s)){
        largo++;
    }
    fp.close();
    return largo;
}

void genera_polinomio(int pos){
    arbol.clear();
    int n;
    int n_poli;
    int n_exp;
    int n_coef;
    fstream fp;
    fp.open("poli.txt",ios::in);  // cambiar nombre polinomio txt.

    if (!fp.is_open()){
        cerr << "Error al abrir el archivo" << endl;
        return;
    }
    fp>>n;

    for (int i = 0; i < n; i++){
        if (i == pos){
            fp >> n_poli;
            for (int j = 0; j < n_poli; j++){
                fp >> n_exp;
                fp >> n_coef;
                arbol.insert(n_coef,n_exp);
            }
            return;

        }
        fp >> n_poli;
        for (int j = 0; j<n_poli; j++){
            fp >> n_exp;
            fp >> n_coef;
        }
    }
    fp.close();
    return ;

}

int main(){
    int n;
    fstream fp;
    fp.open("poli.txt",ios::in); // cambiar nombre polinomio.txt

    if (!fp.is_open()){
        cerr << "Error al abrir el archivo" << endl;
        return -1;
    }
    fp >> n;
    int x;
    int y;
    int largo = 1;

    for (int i = 0; i <n; i++){
        fp >> x;
        largo++;
        for (int j = 0; j<x; j++){
            fp >> y;
            fp >> y;
            largo++;
        }
    }
    // 2da parte lectura de funciones.

    ofstream pf ;
    pf.open("salidaPolinomio.txt");
    if (!pf.is_open()) {
        cerr << " Error el abrir el archivo " << endl ;
        return 1; 
    }
    string linea;
    string s;
    float x0;
    int x1;
    int x2;
    getline(fp,linea);
    for (int i = 0; i<tamano()-largo;i++){
        fp >> s;
        if (s == "COEFICIENTE"){
            fp >> x1;
            genera_polinomio(x1);
            fp >> x2;
            pf << arbol.coeficiente(x2) << endl;
        }else{
            fp >> x1;
            genera_polinomio(x1);
            fp >> x0;
            pf << arbol.evaluar(x0) << endl;
        }
    }

    fp.close();
    pf.close();
    return 0;
}