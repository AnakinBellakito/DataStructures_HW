#include <iostream>
#include <string>

using namespace std;

typedef int tElem;

struct offer{
    int cantidad_descuento;
    int descuento;
    int productos_equivalentes[10];
};

struct cantidadProd{
    int cod_producto;
    int cantidad;
    int precio;
    offer val;
};

struct nodo{
    cantidadProd info;
    nodo* izq;
    nodo* der;
};

class tABB{
    private:
    int total;
    int descuento;
    nodo* raiz;
    int nElems;
    nodo* preNodo;

        //Funciones Private

        /*****
        * void clearHelp
        ******
        *   La función verifica si el nodo ingresado es vacío o no, si es el caso la función termina, en el caso contrario, elimina el nodo y sus hijos.
        * Input:
        *   nodo* nodo: Es la información del nodo que se ocupara.
        ******
        * Returns:
        *   No retorna ningun valor. 
        *****/

        void clearHelp(nodo* nodo){
            if(nodo == NULL) return;
            clearHelp(nodo->izq);
            clearHelp(nodo->der);
            delete nodo;
        }


        /*****
        * cantidadProd procesar
        ******
        *   La función procesa un struct cantidadProd y lo retorna.
        * Input:
        *   cantidadProd info: Es el struct del tipo cantidadProd que se utilizara en la función.
        ******
        * Returns:
        *   Retorna el struct info. 
        *****/

        cantidadProd procesar(cantidadProd info){
            return info;
        }

        /*****
        * void inOrdenHelp
        ******
        *   La función recorre al nodo struct ingresado y a sus hijos en in-orden.
        * Input:
        *   nodo* nodo: Es el struct nodo que se ocupara.
        ******
        * Returns:
        *   No retorna ningun valor. 
        *****/

        void inOrdenHelp(nodo* nodo){
            if (nodo == NULL) return;
            inOrdenHelp(nodo->izq);
            procesar(nodo->info);
            inOrdenHelp(nodo->der);
        }

        /*****
        * void preOrdenHelp
        ******
        *   La función recorre al nodo struct ingresado y a sus hijos en pre-orden.
        * Input:
        *   nodo* nodo: Es el struct nodo que se ocupara.
        ******
        * Returns:
        *   No retorna ningun valor. 
        *****/

        void preOrdenHelp(nodo* nodo){
            if (nodo == NULL) return;
            procesar(nodo->info);
            preOrdenHelp(nodo->izq);
            preOrdenHelp(nodo->der);
        }

        /*****
        * void postOrdenHelp
        ******
        *   La función recorre al nodo struct ingresado y a sus hijos en post-orden.
        * Input:
        *   nodo* nodo: Es el struct nodo que se ocupara.
        ******
        * Returns:
        *   No retorna ningun valor. 
        *****/

        void postOrdenHelp(nodo* nodo){
            if (nodo == NULL) return;
            postOrdenHelp(nodo->izq);
            postOrdenHelp(nodo->der);
            procesar(nodo->info);
        }

        /*****
        * int findHelp
        ******
        *   La función verifica si la variable key se encuentra en el código del producto guardado en el nodo.
        * Input:
        *   nodo* nodo: Es el struct nodo que se ocupara.
        *   tElem key: Numero entero que se ultilizara en la función.
        ******
        * Returns:
        *   Retorna 0 si el nodo es vacío o retorna 1 si la variable key es igual al código del producto guardado en el nodo.
        *****/

        int findHelp(nodo* nodo, tElem key){
            if (nodo == NULL) return 0;
            if (nodo->info.cod_producto == key) return 1;
            if (key < nodo->info.cod_producto){
                return findHelp(nodo->izq,key);
            }
            else{
                return findHelp(nodo->der,key);
            }
        }

        /*****
        * void insertHelp
        ******
        * inserta una clave cumpliendo la regla de arbol binario de busqueda, si la clave ya esta le suma 1 a cantidad.
        ******
        * Input:
        * nodo *node: recibe el nodo raiz y avanza hasta encontrar donde insertar.
        * tElem key: recibe la clave a insertar.
        * tElem price: recibe el precio a insertar.
        * tElem off: recibe un struct que nos ayudara a aplicar descuentos.
        ******
        * Returns:
        *void 
        *****/

        void insertHelp(nodo *node, tElem key, tElem price, offer off){
            if (find(key)== 0){
                if (nElems == 0){
                    raiz = new nodo;
                    raiz->info.cod_producto = key;
                    raiz->info.cantidad = 1;
                    raiz->info.precio = price;
                    raiz->info.val = off;
                    raiz->izq = NULL;
                    raiz->der = NULL;
                    nElems++;
                    return;
                }
                if (node->info.cod_producto < key){
                    if(node->der == NULL){
                        node->der = new nodo;
                        node->der->info.cod_producto = key;
                        node->der->info.cantidad = 1;
                        node->der->info.precio = price;
                        node->der->info.val =  off;
                        node->der->der = NULL;
                        nElems++;
                        return;
                    }
                    insertHelp(node->der,key,price,off);
                } else{
                    if(node->izq == NULL){
                        node->izq = new nodo;
                        node->izq->info.cod_producto = key;
                        node->izq->info.cantidad = 1;
                        node->izq->info.precio = price;
                        node->izq->info.val = off;
                        node->izq->izq = NULL;
                        node->izq->der = NULL;
                        nElems++;
                        return;
                    }
                    insertHelp(node->izq,key,price,off);
                }
            }else{
                if (node->info.cod_producto == key){
                    node->info.cantidad+=1;
                    return;
                }
                if (node->info.cod_producto <key){
                    if(node->der == NULL){
                        return;
                    }
                    insertHelp(node->der,key,price,off);
                }else{
                    if(node->izq == NULL){
                        return;
                    }
                    insertHelp(node->izq,key,price,off);
                }
            }
        }

        /*****
        * void removeHelp
        ******
        * Elimina un elemento ingresado, en caso de no estar no hace nada.
        ******
        * Input:
        * nodo *preNodo :recibe inicialmente un nodo nulo que luego sera el predecesor de los siguientes nodos.
        * nodo*node: recibe inicialmente el nodo raiz donde empezara a recorrer para eliminar el nodo a buscar.
        * tElem key: recibe la clave a eliminar.
        ******
        * Returns:
        *void 
        *****/

        void removeHelp(nodo* preNodo, nodo* node, tElem key){
            if (node == NULL){
                return;
            }
            if (node->info.cod_producto == key){
                //caso 1
                if (node->izq == NULL && node->der == NULL){
                    if (raiz->info.cod_producto == key){
                        delete node;
                        raiz = NULL;
                        return;
                    }
                    if (preNodo->der->info.cod_producto == key){
                        delete node;
                        preNodo->der = NULL;
                        return;
                    }else{
                        delete node;
                        preNodo->izq = NULL;
                        return;
                    }
                }
                //caso 2
                if (node->izq == NULL && node->der != NULL){
                    if(preNodo->der->info.cod_producto == key){
                        preNodo->der = node->der;
                        delete node;
                        return;
                    }else{
                        preNodo->izq = node->der;
                        delete node;
                        return;
                    }
                }
                if (node->izq != NULL && node->der == NULL){
                    if(preNodo->der->info.cod_producto == key){
                        preNodo->der = node->izq;
                        delete node;
                        return;
                    }else{
                        preNodo->izq = node->izq;
                        delete node;
                        return;
                    }
                }
                //caso 3
                nodo* pred = predecesor(node->izq);
                //caso 3.1
                if (pred->der == NULL && pred->izq == NULL){
                    node->info = pred->info;
                    node->izq = NULL;
                    delete pred;
                    return;
                }
                //caso 3.2
                if (pred->der == NULL && pred->izq != NULL){
                    node->info = pred->info;
                    node->izq = pred->izq;
                    delete pred;
                    return;
                }
                //caso 3.3
                nodo* aux=pred->der;
                if (aux->der == NULL && aux->izq == NULL){
                    node->info = aux->info;
                    pred->der = NULL;
                    delete aux;
                    return;
                }
                //caso 3.4
                if (aux->der == NULL && aux->izq != NULL){
                    node->info = aux->info;
                    pred->der = aux->izq;
                    delete aux;
                    return;
                }
            }
            preNodo = node;
            removeHelp(preNodo,node->izq,key);
            removeHelp(preNodo,node->der,key);
        }

        /*****
        * nodo* predecesor
        ******
        * Para realizar el caso 3 del remove utilizamos el predecesor del nodo con 2 hijos, esta funcion encuentra ese predecesor de manera recursiva.
        ******
        * Input:
        * nodo* nodo: recibe nodo a recorrer.
        ******
        * Returns:
        * nodo*, retorna un nodo que corresponde al anterior del predecesor.
        *****/

        nodo* predecesor(nodo* nodo){
            if(nodo->der == NULL) return nodo;
            if(nodo->der->der == NULL) return nodo;
            return predecesor(nodo->der);
        }

        /*****
        * cantidadProd getProdHelp
        ******
        * Recorre el arbol recursivamente desde la raiz hasta encontrar un nodo de cierta clave y retorna su struct
        ******
        * Input:
        * nodo* nodo: recibe un nodo que se ira recorriendo, inicialmente es el nodo raiz.
        * tElem key: recibe clave a buscar.
        ******
        * Returns:
        * cantidadProd, retorna el struct asociado a la clave.
        *****/

        cantidadProd getProdHelp(nodo *nodo, tElem key){
            cantidadProd prod;
            prod.cantidad = 0;
            prod.cod_producto = 0;
            prod.precio = 0;
            if (nodo != NULL){
                if (nodo->info.cod_producto == key) return nodo->info;
                if (key < nodo->info.cod_producto) {
                    return getProdHelp(nodo->izq,key);
                }else{
                    return getProdHelp(nodo->der,key);
                }
            }
            return prod;
        }

        /*****
        * void displayHelp
        ******
        * Recorre el arbol recursivamente imprimiendo sus elementos en forma de arbol.
        ******
        * Input:
        * nodo* nodo: recibe un nodo que se ira recorriendo, inicialmente es el nodo raiz.
        * int nivel:
        ******
        * Returns:
        * void
        *****/

        void displayHelp(nodo *nodo, int nivel){
            int i;
            if (nodo != NULL) {
                displayHelp(nodo -> der, nivel +1);
                cout << endl;
                if (nodo == raiz) cout << "Raiz->: ";
                else {
                    for (i = 0;i < nivel;i++)
                    cout << "       ";

                }
                cout << nodo->info.cod_producto <<" "<< nodo->info.cantidad<< " " << nodo->info.precio << " " << nodo->info.val.productos_equivalentes[0] << endl;
                displayHelp(nodo->izq,nivel+1);
            }
        }

        /*****
        * void resetHelp
        ******
        * Recorre el arbol desde la raiz buscando el nodo para resetearle sus componentes
        ******
        * Input:
        * nodo* nodo: recibe un nodo que se ira recorriendo, inicialmente es el nodo raiz.
        * tElem key: recibe la clave a resetear.
        ******
        * Returns:
        * void
        *****/

        void resetHelp(nodo* nodo, tElem key){
            if (nodo==NULL) return;
            if (nodo->info.cod_producto == key){
                nodo->info.val.descuento = 0;
                return;
            }
            if (key < nodo->info.cod_producto){
                return resetHelp(nodo->izq,key);
            }else{
                return resetHelp(nodo->der,key);
            }
        }

        /*****
        * void calculator
        ******
        * calcula el costo de un producto esto se almacena en total y descuento .
        ******
        * Input:
        * cantidadProd info: recibe un struct con la informacion del nodo para calcular el valor.
        ******
        * Returns:
        * void
        *****/

        void calculator(cantidadProd info){
            if (info.val.descuento == 0){
                total += info.precio*info.cantidad;
                return;
            }else {
                bool flag = true;
                int key;
                int cantidad = info.cantidad;
                //cout << "cantidad inicio: " << cantidad << endl;
                int amount;
                for (int i = 0;flag && i<10; i++){
                    key = info.val.productos_equivalentes[i];
                    //cout << "key: " << key << endl;
                    if (key != -1){
                        //cout << "key " << key << endl;
                        //cout << "antes" << cantidad << endl;
                        cantidad+= getProd(key).cantidad;
                        //cout << "despues"<< cantidad << endl;
                        reset(key);
                    }else{
                        flag = false;
                    }
                }  
                //cout << "cantidad: " << cantidad << endl;
                amount = cantidad/info.val.cantidad_descuento;
                //cout << "amount: " << amount << endl;
                descuento += amount*info.val.descuento;
                total += info.precio*info.cantidad;
                return;
            }
        }

        /*****
        * void costHelp
        ******
        * recorre el arbol calculandole el valor y descuento a cada nodo.
        ******
        * Input:
        * nodo* nodo: recibe un nodo que se ira recorriendo, inicialmente es el nodo raiz.
        ******
        * Returns:
        * void
        *****/

        void costHelp(nodo *nodo){
            if (nodo == NULL) return;
            calculator(nodo->info);
            costHelp(nodo->izq);
            costHelp(nodo->der);
        }

    public:

        tABB(){
            raiz = NULL;
            nElems = total = descuento = 0;
        }

        ~tABB(){
            clear();
        }
        void clear();
        void insert(tElem key,tElem price,offer off);
        void remove(tElem key);
        int find(tElem key);
        int size();
        void inOrden();
        void preOrden();
        void postOrden();
        void display();
        cantidadProd getProd(tElem key);
        int cost();

        /*****
        * void reset
        ******
        * resetea un nodo de cierta clave utiliza resetHelp
        ******
        * Input:
        * tElem key: recibe la clave a resetear
        ******
        * Returns:
        * void
        *****/
        void reset(tElem key){
            return resetHelp(raiz,key);
        }
};

/*****
* void clear
******
*   La función verifica si el nodo ingresado es vacío o no, si es el caso la función termina, en el caso contrario, elimina el nodo y sus hijos.
* Input:
*   No tiene parametro
******
* Returns:
*   No retorna ningun valor. 
*****/

void tABB::clear(){
    clearHelp(raiz);
    raiz = NULL;
    nElems = total = descuento = 0;
}

/*****
* void insert
******
* inserta un elemento cumpliendo la regla de arbol binario de busqueda utiliza las claves para ello.
******
* Input:
* tElem key: recibe clave a insertar.
* tElem price: recibe precio a insertar.
* tElem off: recibe un struct a insertar.
******
* Returns:
*void 
*****/

void tABB::insert(tElem key,tElem price,offer off){
    insertHelp(raiz,key,price,off);
}

/*****
* void remove
******
* Elimina un elemento ingresado, en caso de no estar no hace nada.
******
* Input:
* tElem key: recibe una clave a eliminar.
******
* Returns:
*void 
*****/

void tABB::remove(tElem key) {
    if( find(key) == 0) {
        cerr << "elemento no existente en arbol" << endl;
        return;
    }
    nElems--;
    nodo* nulo = NULL;
    removeHelp(nulo,raiz,key);  
}

/*****
* int find
******
*   La función verifica si la variable key se encuentra en el código del producto guardado en el nodo (Implementa la función findHelp).
* Input:
*   No hay parametros.
******
* Returns:
*   Retorna el resultado de la función findHelp. 
*****/

int tABB::find(tElem key) {
    return findHelp(raiz,key);
}

/*****
* int size
******
* Extrae el numero de elementos del arbol.
******
* Input:
* No recibe.
******
* Returns:
* int, retorna el numero de elementos en el arbol.
*****/

int tABB::size(){
    return nElems;
}

/*****
* void inOrden
******
*   La función recorre al nodo struct ingresado y a sus hijos en in-orden.
* Input:
*   No hay parametros.
******
* Returns:
*   No retorna ningun valor. 
*****/

void tABB::inOrden () {
    inOrdenHelp (raiz);
}

/*****
* void preOrden
******
*   La función recorre al nodo struct ingresado y a sus hijos en pre-orden.
* Input:
*   No hay parametros.
******
* Returns:
*   No retorna ningun valor. 
*****/

void tABB::preOrden() {
    preOrdenHelp(raiz);
}

/*****
* void postOrden
******
*   La función recorre al nodo struct ingresado y a sus hijos en post-orden.
* Input:
*   No hay parametros.
******
* Returns:
*   No retorna ningun valor. 
*****/

void tABB::postOrden() {
    postOrdenHelp(raiz);
}

/*****
* cantidadProd getProd
******
* Busca una clave y retrona sus componentes
******
* Input:
* tElem key: clave a buscar.
******
* Returns:
* cantidadProd , retorna un struct con los componentes del nodo.
*****/

cantidadProd tABB::getProd(tElem key){
    return getProdHelp(raiz,key);
}

/*****
* void display
******
* imprime los nodos del arbol
******
* Input:
* No recibe parametros.
******
* Returns:
* void
*****/

void tABB::display(){
    displayHelp(raiz,1);
}

/*****
* int cost
******
* Cacula el costo total de la compra de un cliente
******
* Input:
* No recibe parametros
******
* Returns:
* int, retorna el costo de la compra.
*****/

int tABB::cost(){
    costHelp(raiz);
    return total-descuento;
}
/*
int main(){

    tABB arbol;
    
    // caso 1 simple
    cout << "caso 1 simple" << endl;
    cout << "original" << endl;
    cout << endl;
    arbol.insert(28,0);
    arbol.insert(16,0);
    arbol.insert(30,0);
    arbol.insert(5,0);
    arbol.insert(19,0);
    arbol.insert(17,0);
    arbol.insert(21,0);
    arbol.insert(12,0);
    arbol.insert(29,0);
    arbol.insert(32,0);
    arbol.insert(28,0);
    arbol.display();
    cout << endl;
    cout << "despues del remove" << endl;
    cout << endl;
    arbol.remove(17);
    arbol.display();


    arbol.clear();

    // caso 1 complejo
    cout << "caso 1 complejo" << endl;
    cout << "original" << endl;
    cout << endl;
    arbol.insert(28,2);
    arbol.insert(16,3);
    arbol.insert(30,5);
    arbol.insert(5,7);
    arbol.insert(19,22);
    arbol.insert(17,3);
    arbol.insert(21,77);
    arbol.insert(12,1);
    arbol.insert(29,98);
    arbol.insert(32,2);
    arbol.insert(28,2);
    arbol.display();
    cout << endl;
    cout << "despues del remove" << endl;
    cout << endl;
    arbol.remove(17);
    arbol.display();

    cout << endl;
    arbol.clear();
    //caso 2 

    cout << "original caso 2" << endl;
    cout << endl;
    arbol.insert(28,3);
    arbol.insert(30,5);
    arbol.insert(16,2);
    arbol.insert(19,4);
    arbol.insert(17,66);
    arbol.insert(21,99);
    arbol.insert(29,12);
    arbol.insert(32,1);
    arbol.insert(32,1);
    arbol.insert(32,1);
    arbol.display();
    cout << endl;
    cout << "despues del remove" << endl;
    cout << endl;
    arbol.remove(16);
    arbol.display();
    
    cout << endl;
    arbol.clear();

    // caso 3

    cout << "original caso 3" << endl;
    cout << endl;
    arbol.insert(28,0);
    arbol.insert(16,0);
    arbol.insert(30,0);
    arbol.insert(25,0);
    arbol.insert(5,0);
    arbol.insert(12,0);
    arbol.insert(20,0);
    arbol.insert(18,0);
    arbol.insert(23,0);
    arbol.insert(29,0);
    arbol.insert(32,0);
    arbol.display();
    cout << endl;
    cout << "despues de remove" << endl;
    cout << endl;
    arbol.remove(28);
    arbol.display();

    return 0;
}
*/
