#include<iostream>
#include <string>
#include<fstream>

using namespace std;

struct empleado {
    char estado;
    string rut;
    string hora;
};

void cuentaEmpleados(string hora, empleado arreglo[], int &p) {
    
    
    string temp_rut;
    char temp_estado;
    string temp_hora;
    char ptr;
    int contador;

    

    for(int i = 0;i <100; i ++ ) {
        contador =0;
        temp_estado = arreglo[i].estado;
        temp_rut = arreglo[i].rut;

        cout << 'a' <<endl;



        for(int j = 0; j < 100; j++) {
            if( temp_rut == arreglo[j].rut && arreglo[j].hora <= hora ){
                ptr = arreglo[j].estado;
                cout << 'b'<< endl;

                if (ptr == 'E' && contador == 0 ) {
                    contador++;
                    p++;

                }

                if (ptr =='S' && contador == 1) {
                    contador++;
                    p--;
                }



                
                

            }

        }
    }

    
}



int main() {

    fstream fp;

    empleado arr[100];
    char stat;
    string rutt;
    string time;

    fp.open("asistencia.txt", ios::in );
    for(int i=0; i<100; i++) {
       fp >> stat;
       fp >> rutt;
       fp >> time;

       arr[i].estado = stat;
       arr[i].rut= rutt;
       arr[i].hora = time;




    }
    fp.close();



    for (int  x = 0; x < 5; x++)
    {
        cout << arr[x].estado 
        << " "
        << arr[x].rut
        << " "   
        << arr[x].hora << endl;
    }
    
    int c_empleado = 0;
    
    
    string var = "14:00";
    

    cuentaEmpleados(var , &arr[100],c_empleado);

    cout << c_empleado << endl;




    return 0;
}