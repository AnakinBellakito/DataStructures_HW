#include<iostream>
#include<string>
#include<fstream>

using namespace std;

struct flujoNeto {
    int hora;
    int personas;


} ;

// Func cantidad de personas --> 

int main() {
    flujoNeto prueba[10] = { {14,5} ,{45,8},{78,4},{90,7},{90,8},{90,9},{90,10},{90,14},{90,45},{90,7} }; 
    fstream fp;
    int a[10];
    
    fp.open("flujo-publico.dat", ios::out|ios::binary);
    if (!fp.is_open())
        cout << "Error en la matrix" << endl;
    
    cout << sizeof(flujoNeto) << endl;

    fp.write((char *)prueba, 10*sizeof(flujoNeto));

   
    
    fp.close();
    fp.open("flujo-publico.dat", ios::binary|ios::in);
    
    fp.read((char *)a, sizeof(flujoNeto));
    
    cout <<a[0] << endl;

   /* fp.open("flujo-publico.dat", ios::in | ios:: binary);
    for (int i =0; i <1440; i++ ) {
       

    }

     */   
    

    return 0;
} 