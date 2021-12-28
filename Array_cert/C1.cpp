#include<iostream>
#include<string>
#include<fstream>

using namespace std;
struct transaccion {
    int codigo_prod;
    int cantidad;
}; 

struct vendedor {
    int id;
    char nombre[31];
    transaccion ventas[1000];
    int n_ventas;
};

vendedor *vendeProducto(string filename, int codigo, int k, int &size) {
    int n,m;
    m=0;
    int count = 0;
    
    vendedor *A;
    vendedor *B;

    fstream fp;

    fp.open(filename, ios::in | ios::binary);
    fp.read((char *)&n, sizeof(int));
    
    A = new vendedor[n];
    fp.read((char *)A, n*sizeof(vendedor));
    fp.close();

    for(int i = 0; i < n; i++) {
        int contador =0;
        bool flag = false;
        for (int j = 0; j<A[i].n_ventas; j++ ) {
            
            
            if(A[i].ventas[j].codigo_prod == codigo) {
                contador += A[i].ventas[j].cantidad;
                
                if(contador >= k && flag == false) {
                    m++;
                    flag = true;
                    
                }
            }



        }
    }
    
    int *aux = new int[m];
    

    for(int i = 0; i < n; i++) {
        int contador = 0;
        bool flag = false;
        for (int j = 0; j<A[i].n_ventas; j++ ) {
            
            if(A[i].ventas[j].codigo_prod == codigo) {
                contador += A[i].ventas[j].cantidad;
                
                if(contador >= k && flag == false) {
                    aux[count] = i;
                    count++;
                    flag = true;
                    
                }
            }



        }
    }
    count = 0;
    B = new vendedor[m];
    for (int i = 0; i < n; i++)
    {
        if (i == aux[count]) {
            B[count] = A[i];
            count++;
        }
    }
    delete [] A;
    delete [] aux;
    size = m;
    return B;

}



int main () {

}