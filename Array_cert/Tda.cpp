#include<iostream>
#include<string>
#include<fstream>
#include<cmath>

using namespace std;

class arr_extensible {
    
    private:
    unsigned long* ptrA; 
    unsigned long* ptrB; // Declaramos 2 punteros(para operar los arreglos) y un entero n 
    int n;

    
    
    public:
    arr_extensible() {
        n=0;
        ptrA = new unsigned long[n];               // Valoramos a n en 0 y arreglo A ;
        ptrB = new unsigned long[2];        // 2^k >> 0  es 2
          for (int j = 0; j < n; j++)
        {
            ptrA[j] = ptrB[j]; //Hacemos contener el arreglo A en base
        }
        


    };

    arr_extensible(int a) {
        n = a;
        int k = 0;                        //Usuario define el size del arreglo A
        ptrA = new unsigned long[n];        //Inicializamos arreglo dinamico con variables privadas + 
        for (int i = 0; i < 2147483647; i++)    // recorremos hasta valor maximo de los unsigned long
        {
            k = i;
            if (n> pow(2,k-1) && n<= pow(2,k)) {
                int size = pow(2,k);                //Chekeamos condicion de Arreglo base 2^k y asignamos
                ptrB = new unsigned long[size];     //Declaramos dinamicamente el arreglo base
                
                
                break;                          //break para quedarse con la primera k que cumpla la condicion
            }
        }
        for (int j = 0; j < n; j++)
        {
            ptrA[j] = ptrB[j]; //Hacemos contener el arreglo A en base
        }
        
        
    };

    arr_extensible(int a, int v) {
        n = a;
        int k = 0;                        //Usuario define el size del arreglo A
        ptrA = new unsigned long[n];        //Inicializamos arreglo dinamico con variables privadas + 
        for (int i = 0; i < 2147483647; i++)    // recorremos hasta valor maximo de los unsigned long
        {
            k = i;
            if (n> pow(2,k-1) && n<= pow(2,k)) {
                int size = pow(2,k);                //Chekeamos condicion de Arreglo base 2^k y asignamos
                ptrB = new unsigned long[size];     //Declaramos dinamicamente el arreglo base
                
                
                break;                          //break para quedarse con la primera k que cumpla la condicion
            }
        }
        for (int j = 0; j < n; j++)

        {
            ptrB[j] = v;
            ptrA[j] = ptrB[j]; //Hacemos contener el arreglo A en base con valor v
        }
        
        
    };
    
    ~arr_extensible() {
        delete [] ptrA;         
        delete [] ptrB; //Destructor que se encarga de eliminar memoria dinamica al fin del programa.
    };

    bool setValue(unsigned long i,int v);
    int getValue(unsigned long i );
    void append(int v );            //Declaramos los metodos requeridos dentro del public.
    void remove();
    unsigned long size();



};
    bool arr_extensible::setValue(unsigned long i, int v) {
        if( i < n && i >=0) {       //checkeamos condicion de largo
            ptrA[i] = v;            //Declaramos valores dados por usuario a ambos arreglos
            ptrB[i] = v;
            //cout << &ptrA[i] << endl;
            //cout << &ptrB[i] << endl;

            return true;
        }
        else {                      //retornamos acorde a las condiciones
            return false;
        }
    }

    int arr_extensible::getValue(unsigned long i ) {
        if( i < n && i >=0) {   //chekeamos condicion de largo

            return ptrA[i];     //retornamos valor en la posicion i del arreglo A
            
        }
        else { 
            cerr << "Error de acceso al arreglo" << endl;   //si no cumple condicion manda mensaje a stream de error.
            exit(1);                                
        }
    }



    void arr_extensible::append(int v) {
        ptrB[n] = v;            //arreglo base toma el valor dado por usuario
        n +=1;                  // sumamos 1 al largo 
        delete [] ptrA;         
        ptrA = new unsigned long[n];    //eliminamos el arreglo anterior y declaramos uno con el nuevo tamano

        for(int i = 0; i < n; i++)
        {
            ptrA[i] = ptrB[i];          // copiamos todos los valores del arreglo + el nuevo 

        }
        delete [] ptrB;                 //Borramos arreglo base
        int k =0;
         for (int i = 0; i < 2147483647; i++)     //Variable auxiliar k para nuevo size del arreglo Base  
        {
            k = i;
            if (n> pow(2,k-1) && n<= pow(2,k)) {  // for para cumplir con condicion k+1 del arreglo base
                int size = pow(2,k+1);
                ptrB = new unsigned long[size];     // declaramos nuevo arreglo dinamico con size correspondiente
                
                
                break;          // break para no hacer ciclos innecesarios
            }
        }

        for(int i = 0; i < n; i++)
        {
            ptrB[i] = ptrA[i];  // copiamos todos los valores que previamente tenia el arreglo Base

        }

    
    }
    void arr_extensible::remove() {
         n -=1;
        delete [] ptrA;
        ptrA = new unsigned long[n];    //Metodo y acciones similares a append pero decreciendo el size n

        for(int i = 0; i < n; i++)          
        {
            ptrA[i] = ptrB[i];

        }
        delete [] ptrB;
        int k =0;
         for (int i = 0; i < 2147483647; i++)
        {                                          //for y if para reducir size del arreglo Base
            k = i;
            if (n> pow(2,k-1) && n<= pow(2,k)) {         
                int size = pow(2,k);
                ptrB = new unsigned long[size];
                
                
                break;
            }
        }

        for(int i = 0; i < n; i++)
        {
            ptrB[i] = ptrA[i];

        }

    }

    unsigned long arr_extensible::size() {
        return (unsigned long)n;  //retornamos el size del arreglo A y lo casteamos al tipo correcto.
    }


int main () {
    arr_extensible arr(10);
    arr_extensible arreglo2(50, 6);
    arr_extensible arr_vacio;
    
    arr.setValue(1,10);
    cout << arr.size() << endl;
    arr.setValue(9,90);
    cout << arr.getValue(9) << endl;       //casos de prueba areglo 1.

    arr.append(15);
    cout << arr.getValue(10) << endl;

    arr.remove();
    cout << arr.getValue(9) << endl;
    

    //////////////////////////////////////////////////

    arreglo2.setValue(4,45);
    cout << arreglo2.size() << endl;
    arreglo2.setValue(5,60);
    cout << arreglo2.getValue(4) << endl;       //casos de prueba areglo 2.

    arreglo2.append(15);
    cout << arreglo2.getValue(15) << endl;

    arr.remove();
    cout << arreglo2.getValue(5) << endl;

/////////////////////////////////////////////////////
    
    cout << arr_vacio.size() << endl;

   
    arr_vacio.append(1);
    arr_vacio.append(2);
    arr_vacio.append(3);
    arr_vacio.append(199);

    cout <<  arr_vacio.getValue(0) << endl;
    cout <<  arr_vacio.getValue(2) << endl;
    cout <<  arr_vacio.getValue(3) << endl;

    arr_vacio.remove();
    
    cout <<  arr_vacio.getValue(3) << endl;



    





    return 0;

} 


//COMENTARIOS:

/*****
*   TipoFunción:Booleano. NombreFunción:setValue.
*   Resumen Función: Verifica si se encuentra la posición i en el largo del arreglo, si se cumple la condición define un valor v para cada arreglo y retorna verdadero o si no se cumple retorna falso.
******
*   Input:
*       tipoParámetro:Número entero (sin signo). NombreParámetro:i.
*       tipoParámetro:Número entero. NombreParámetro:v.
******
*   Returns:
*       TipoRetorno:Valor booleano. Descripción TipoRetorno:Retorna los valores verdadero o falso segun el condicional existente.
*****/

/*****
*   TipoFunción:Número entero. NombreFunción:getValue.
*   Resumen Función:Verifica si la posición i se encuentra en el arreglo, si es el caso retorna el valor en la posición o en el caso contrario entrega un error en pantalla y termina el programa.
******
*   Input:
*       tipoParámetro:Número entero(sin signo). NombreParámetro:i.
******
*   Returns:
*       TipoRetorno:Retorna un numero entero. Descripción TipoRetorno:Retorna un valor que se encuentra en la posición i del arreglo. 
*****/

/*****
*   TipoFunción:Vacía. NombreFunción:append.
*   Resumen Función: Se modifican los arreglos ptrA y ptrB para aumentar el largo del arreglo ptrB, además, se conserva los datos del mismo arreglo.
******
*   Input:
*       tipoParámetro:Número entero. NombreParámetro:v.
******
*   Returns:
*       TipoRetorno:Vacío. Descripción TipoRetorno:No hay retorno de la función.
*****/

/*****
*   TipoFunción:vacía NombreFunción:remove.
*   Resumen Función:Se modifican los arreglos ptrA y ptrB para disminuir el largo del arreglo ptrB, además, se conserva los datos del mismo arreglo.
******
*   Input:
*       No contiene parametros.
******
*   Returns:
*       TipoRetorno:Vacío Descripción TipoRetorno:No entrega retorno.
*****/

/*****
*   TipoFunción:Número entero(sin signo). NombreFunción:size.
*   Resumen Función:Retorna el largo del arreglo A y modifica el tipo de variable que lo contiene.
******
*   Input:
*       No contiene parametros.
******
*   Returns:
*       TipoRetorno:Vacío. Descripción TipoRetorno:NO entrega retorno.
*****/
