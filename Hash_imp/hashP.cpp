#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#define VACIA 0

using namespace std;

typedef int tipoClave;

struct producto {
    int cod_producto; //key
    char nombre_producto[31];
    int precio;
};


class table_products{
    private:
        struct ranura{
            tipoClave clave;
            producto info;
        };

        producto VALORINVALIDO;

        int nElems;
        int size;
        ranura* HT;
        int *colisiones;
        int r;
        int M;
        bool prim;
        bool pow_2;
        bool h_2;

        /******
        *   TipoFuncion: Int , NombreFuncion: h
        *******
        *   Resumen: Funcion hash que se encarga de proporcionar una alietoridad para las claves
        *             Esta usa el metodo del cuadrado medio, expadiendo los numero y usando los de al medio
        *******
        *   Input:
        *       tipoParametro: tipoClave = typedef Int, NombreParemtro: k "key" : El parametro es la clave de acceso para generar cierta posicion en las ranuras de la tabla hashing.
        *
        *******
        *   Return:
        *       TipoRetorno: int, retorna la posicion de la tabla en la que ingresar la informacion del par (k,i).
        *
        ********/

        int h(tipoClave k){
            int x = (pow(2,31)-1)/k;
            bool bandera = true;
            while(bandera){
                if(x/k != 0){
                    k = k*k;
                    bandera = false;
                    k = k*10;
                }
                k=k/10;
            }

            int a = 1;
            int largo = 0;
            bool flag = true;
            for (int i = 1; flag; i++){
                a = a*10;
                if (k%a == k){
                    largo = i;
                    flag = false;
                }
            }
            //cout << "el largo es: " << largo << endl;
            int *arr = new int[largo];
            for (int j = 0 ; j<largo; j++){
                flag = true;
                a = 1;
                while (flag){
                    for (int i = 0; i<= largo-j-1 ; i++){
                        a = a*10;
                        //cout << "valor de a: " << a << endl;
                        //cout << "mod k%a: " << k%a << endl;
                        if (i==largo-j-1){
                            flag = false;
                            //cout << " ingresa al arr: "<< k/(a/10)<< endl;
                            arr[j]=k/(a/10);
                            //cout << "resto: " << k%(a/10) << endl;
                            k = k%(a/10);
                        }
                    }

                }
            }
    
           // for( int i = 0; i< largo; i++){
               // cout << arr[i] << endl;// lectura del arr
            //}

            // encontrar el medio
            int medio = 0;
            flag = true;
            for(int i = 0; i < largo && flag; i++){
                if((largo-r)/2 == i && largo-r >= 0){
                    flag = false;
                    for (int j = 0; j<r; j++){
                        medio+=arr[i+j]*pow(10,r-1-j);
                        //cout << "medio vale: " << medio << endl;
                    }
                }
                if ((largo-r) < 0){
                    //cout << "r mayor que el largo" << endl;
                    flag = false;
                    for (int j = 0; j<largo; j++){
                        medio+=arr[j]*pow(10,largo-1-j);
                        //cout << "medio vale: " << medio << endl;
                    }
                }
            }
            if(M <= medio){
                //cout <<"valor medio: "<< medio%M << endl;
                delete [] arr;
                return medio%M;
            }
            //cout <<"valor medio: "<< medio << endl;
            delete [] arr;
            return medio;

        };

        /******
        *   TipoFuncion: Int , NombreFuncion: p
        *******
        *   Resumen: Genera valores para ir avanzando en las ranuras
        *           
        *******
        *   Input:
        *       tipoParametro: tipoClave = typedef Int, NombreParemtro: k "key" : El parametro corresponde a una clave de la tabla de hashing 
        *       tipoParametro: int  i: corresponde a un entero que aumenta su valor de 1 en 1.
        *
        *******
        *   Return:
        *       TipoRetorno: int, retorna un entero que corresponde a los espacios avanzar en la tabla hash.
        *
        ********/

        int p(tipoClave k, int i ){
            return i*h2(k);
        };

        /******
        *   TipoFuncion: Int , NombreFuncion: mcd
        *******
        *   Resumen: Funcion minimo comun divisor que se encarga de buscar el mcd respecto a la llave k y M, 
        *           
        *******
        *   Input:
        *       tipoParametro: tipoClave = typedef Int, NombreParemtro: k "key" : El parametro corresponde a una clave de la tabla de hashing 
        *
        *******
        *   Return:
        *       TipoRetorno: int, retorna un entero que corresponde al mcd de la clave k en la tabla actual.
        *
        ********/

        int mcd(tipoClave k){
            if (k != M){
                if(k < M){
                    int aux = k;
                    for(int i = 0; i <k; i++){
                        if (k%aux == 0 && M%aux == 0){
                            return aux;
                        }
                        aux-=1;
                    }
                }else{
                    int aux = M;
                    for(int i = 0; i <M; i++){
                        if (k%aux == 0 && M%aux == 0){
                            return aux;
                        }
                        aux-=1;
                    }
                }
            }
            return k;

        };

        /******
        *   TipoFuncion: Int , NombreFuncion: h2
        *******
        *   Resumen: Funcion hash numero 2 que se encarga de proporcionar una alietoridad en caso de que ocurran colisiones, funcion usada para lograr el doble hashing.
        *             
        *******
        *   Input:
        *       tipoParametro: tipoClave = typedef Int, NombreParemtro: k "key" : El parametro es la clave de acceso para generar cierta posicion en las ranuras de la tabla hashing.
        *
        *******
        *   Return:
        *       TipoRetorno: int, retorna el largo del numero si M es primo y si M se puede escribir como 2^m retorna el primer numero impar entre 1 y M, si M no es primo ni se puede escribir de forma 2^m se busca el primer k%M que sea primo relativo con M.
        *
        *******/


        int h2(tipoClave k){ // retorna el modulo de k%M si M es primo y si M se puede escribir como 2^m retorna el primer numero impar entre 1 y M, si M no es primo ni se puede escribir de forma 2^m se busca el primer k%M que sea primo relativo con M;
            if (prim != true){
                k = k%M;
                if(h_2 == true){
                    while (true){
                        if(mcd(k) == 1){
                            return k;
                        } 
                        k+=1;
                    }
                }else{//caso -> pow_2 == true 
                    if(k%2 == 0){
                        if (k == 0){
                            return 3;
                        }
                        return k+1;
                    }
                    return k;
                }
            }
            bool flag = true;
            int i = 1;
            if(k == 0){
                return 5;
            }else{
                for(int a = 10;flag;a=a*10){
                    if(k/a==0){
                        flag = false;
                    }
                    i++;
                }
            }
            return i;
        };

        /******
        *   TipoFuncion: bool , NombreFuncion: is_primo
        *******
        *   Resumen: funcion que se encarga de proporcionar la informacion si un numero es primo
        *             
        *******
        *   Input:
        *       tipoParametro: int, NombreParemtro: n : entero que deseamos saber si cumple la propiedad de ser primo.
        *
        *******
        *   Return:
        *       TipoRetorno: bool, retorna true si cumple las condiciones y false en caso contrario.
        *
        ********/

        bool is_primo(int n){
            for (int i = 2; i<n; i++){
                if(n%i == 0){
                    //cout << " no es primo" << endl;
                    return false;
                }
            }
            //cout << "es primo" << endl;
            return true;

        };

         /******
        *   TipoFuncion: bool , NombreFuncion: is_2m
        *******
        *   Resumen: funcion encargada de proporcionarnos informacion de si M puede escribirse como potencias de 2 o no.
        *             
        *******
        *   Input:
        *       tipoParametro: int, NombreParemtro: n : entero con el cual comparamos las potencias de 2, 
        *
        *******
        *   Return:
        *       TipoRetorno: bool, retorna true si cumple las condiciones y false en caso contrario.
        *
        ********/

        bool is_2m(int n){
            bool flag = true;
            for(int i = 0; flag ; i++){
                if(n == pow(2,i)){
                    flag=false;
                    //cout << "se puede escribir como potencia de 2" << endl;
                    return true; // M se puede escribir como potencia de 2.
                }
                if (n < pow(2,i)){
                    flag=false;
                    //cout << "no se puede escribir como potencia de 2" << endl;
                    return false; // M no se puede escribir como potencia de 2.
                }
            }
            return true;
        }

        /******
        *   TipoFuncion: int , NombreFuncion: get_r
        *******
        *   Resumen: funcion encargada de decirnos la cantidad de elementos que debemos cortar de al medio, de los numeros expandidos.
                        En otras palabras, parte primordial del metodo del cuadrado medio.
        *             
        *******
        *   Input:
        *       tipoParametro: int, NombreParemtro: M : Largo de la tabla de hashing
        *
        *******
        *   Return:
        *       TipoRetorno: int. Retorna la cantidad de digitos centrales a extraer cada vez que usamos la funcion hashing.
        *
        ********/

        int get_r(int M){
            int a = 1;
            int largo = 0;
            bool flag = true;
            for (int i = 1; flag; i++){
                a = a*10;
                if (M%a == M){
                    largo = i;
                    flag = false;
                }
            }
            for(int i = 0; pow(10,i) <= M; i++){
                if( pow(10,i) == M){
                    return largo-1;
                }
            }
            return largo;
        };

    public:
        /******
        *    NombreFuncion: table_offer
        *******
        *   Resumen: Constructor encargado de inicializar dinamicamente la tabla de hash con un tamano dado.
        *             
        *******
        *   Input:
        *       tipoParametro: int, NombreParemtro: m : entero con el tamano que deseamos crear la tablas de hashing 
        *
        *******
        *   Return:
        *       TipoRetorno: tda, Retorna una estructura tipo hashing, con todos los metodos asociados a esta.
        *
        ********/
        table_products(int m){
            if (m == 1 || m == 2){
                m++;
            }
            HT = new ranura[m];
            colisiones = new int [m];
            for (int i = 0; i<m; i++){
                HT[i].clave = colisiones[i] = 0;
            }
            size = M = m;
            nElems = 0;
            r = get_r(m);
            prim = is_primo(m);
            pow_2 = is_2m(m);
            if(prim == false && pow_2 == false){
                h_2 = true;
            }else {
                h_2 = false;
            }

        }
        ~table_products(){
        }
        int hashInsert(tipoClave k, producto I);
        producto hashSearch(tipoClave k);
        void printTable();
        float factorCarga();
};


/******
*    NombreFuncion: hashInsert
*******
*   Resumen: Funcion encargada de insertar informacion en las ranuras de la tabla de hashing
*******
*   Input:
*       tipoParametro: tipoCLave = "typedef int", struct oferta = "int & *int", NombreParemtro: k , I : Par de datos que conforman "Llave-valor" el cual intentara ser insertado en una ranura por la funcion.
*
*******
*   Return:
*       TipoRetorno: int, Retorna varia entre 2 enteros, 1 si se pudo insertar el elemento I en la tabla o 0 en caso de que no fue posible.
*
********/
int table_products::hashInsert(tipoClave k, producto I) {
    int inicio, i;
    int pos = inicio = h(k);
    int cols = 0;
    for (i = 1; HT[pos].clave != VACIA && HT[pos].clave != k; i++){
        cols++;
        pos = (inicio + p(k, i)) % M; // próxima ranura en la secuencia
    }
    if (HT[pos].clave == k){
        return 0; // inserción no exitosa: clave repetida
    }
    else {
        nElems++;
        HT[pos].clave = k;
        HT[pos].info = I;
        colisiones[pos]=cols;
        return 1; // inserción exitosa
    }
}

/******
*    NombreFuncion: hashSearch
*******
*   Resumen: Funcion encargada de buscar un struct oferta en la tabla de hashing dado una clave.
*******
*   Input:
*       tipoParametro: tipoCLave = "typedef int", parametro "k"  usado como llave que es usado para buscar su correspondiente I en la tabla.
*
*******
*   Return:
*       TipoRetorno: struct oferta, Retorna el struct oferta si es encontrado, en caso contrario retorna un struct invalido;
*
********/

producto table_products::hashSearch(tipoClave k) {
    VALORINVALIDO.cod_producto = -1; // clave -1 invalida.
    int inicio, i;
    int pos = inicio = h(k);
    for (i = 1; HT[pos].clave != VACIA && HT[pos].clave != k; i++){
         pos = (inicio + p(k, i)) % M; // próxima ranura en la secuencia
    }
    if (HT[pos].clave == k){
        return HT[pos].info; // registro encontrado, búsqueda exitosa
    }
    else{
        return VALORINVALIDO; // Ejercicio: solucionar esto!
    }
}

/******
*    NombreFuncion: printTable()
*******
*   Resumen: Funcion encargada de imprimir por pantalla la tabla de hash actual, es decir la estructura de datos al momento de llamar a esta funcion
*******
*   Input:
*       tipoParametro: sin parametros
*
*******
*   Return:
*       TipoRetorno: void, no retorna nada, realiza cout internos al ser llamada.
*
********/

void table_products::printTable() {
    cout << "Tabla Hash" << endl;
    cout << endl;
    for(int i=0;i<size;i++){
        cout << i << ": " << HT[i].info.cod_producto << "\n";
    }
    cout<<"\n";
    cout << endl;

    cout << " Tabla de Colisiones" << endl;
    cout << endl;
    for(int i=0;i<size;i++){
        cout << i << ": " << colisiones[i] << "\n";
    }
    cout<<"\n";
}

/******
*    NombreFuncion: factorCarga()
*******
*   Resumen: calcula cuan llena esta la tabla hash para cumplir el alfa = 0.7
*******
*   Input:
*       tipoParametro: sin parametros
*
*******
*   Return:
*       TipoRetorno: int, retorna el factor de carga.
*
********/

float table_products::factorCarga(){
    return nElems/size;
};

/*
int main(){
    table_products prod(10);
    producto i;

    i.cod_producto = 123;
    i.precio = 1;
    prod.hashInsert(i.cod_producto,i);

    i.cod_producto = 3124;
    i.precio = 2;
    prod.hashInsert(i.cod_producto,i);

    i.cod_producto = 4341;
    i.precio = 3;
    prod.hashInsert(i.cod_producto,i);

    i.cod_producto =7467 ;
    i.precio = 4;
    prod.hashInsert(i.cod_producto,i);

    i.cod_producto = 897;
    i.precio = 5;
    prod.hashInsert(i.cod_producto,i);

    i.cod_producto = 321;
    i.precio = 6;
    prod.hashInsert(i.cod_producto,i);

    i.cod_producto = 888;
    i.precio = 7;
    prod.hashInsert(i.cod_producto,i);

    prod.printTable();

    return 0;
}
*/