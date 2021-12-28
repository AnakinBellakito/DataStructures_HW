#include <iostream>
#include <fstream>
#include <string>
#include "hashP.cpp"
#include "HashO.cpp"
#include "ABBp.cpp"

using namespace std;


int main(){
    // Almacenar los .dat en los Hash
    int m ;
    ifstream fp;
    producto p;
    fp.open("productos.dat", ios::binary);
    if (!fp.is_open()){
        cerr << "Error al abrir el .dat" << endl;
        exit(-1);
    }

    fp.read((char*)&m, sizeof(int));
    cout << endl;
    table_products prod(m/0.7); // definimos la tabla hash para los productos

    while(fp.read((char*)&p , sizeof(producto))){
        prod.hashInsert(p.cod_producto, p);
    }
    fp.close();

    //cout<<"Tabla hash productos"<< endl;
    //prod.printTable();
    //cout<<endl;

    oferta o;
    fp.open("ofertas.dat", ios::binary);
    if(!fp.is_open()){
        cerr << "Error al abrir el .dat" << endl;
        exit(-1);
    }

    fp.read((char*)&m, sizeof(int));
    table_offer of(m/0.7); // definimos la tabla hash para las ofertas

    while(fp.read((char*)&o , sizeof(oferta))){
        of.hashInsert(o.cod_producto, o);
    }
    fp.close();

    //cout << "Tabla hash ofertas" << endl;
    //of.printTable();
    //cout << endl;

    // Almacenar .txt en el ABB
    tABB arbol;

    fp.open("compras.txt");
    if(!fp.is_open()){
        cerr << "Error al abrir el archivo" << endl;
        exit(-1);
    }
    int n0;
    int n1;
    int key;
    offer v_oid;
    oferta off;

    fp >> n0;

    ofstream pf;
    pf.open("boleta.txt");
    if(!pf.is_open()){
        cerr << "Error al abrir en modo escritura" << endl;
        exit(-1);
    }
    pf << n0 << endl;
    for (int i = 0; i<n0; i++){ // cantidad de clientes
        fp >> n1;
        for (int j = 0; j<n1; j++){ // productos por cliente
            v_oid.cantidad_descuento = 0;
            v_oid.descuento = 0;
            v_oid.productos_equivalentes[0] = -1;
            fp >> key;
            off = of.hashSearch(key);
            if (off.cod_producto != -1){
                v_oid.cantidad_descuento = off.cantidad_descuento;
                v_oid.descuento = off.descuento;
                for (int k = 0; k<10;k++){
                    v_oid.productos_equivalentes[k] = off.productos_equivalentes[k];
                }
                arbol.insert(key,prod.hashSearch(key).precio,v_oid);
            }else{  
                arbol.insert(key,prod.hashSearch(key).precio,v_oid);
            }
        }
        pf << arbol.cost() << endl;
        arbol.clear();
    }
    pf.close();

    return 0;
}