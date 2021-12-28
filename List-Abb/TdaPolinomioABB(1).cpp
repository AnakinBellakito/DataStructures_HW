#include <iostream>
#include <string>
#include <cmath>

using namespace std;

typedef int tElem;

struct monomio{
    int coef;
    int exp;
};

struct nodo{
    monomio info;
    nodo* izq;
    nodo* der;

};

class tABB{
    private:

        nodo*raiz;
        int nElems;
        nodo* preNodo;

        // Funciones Private
        int * procesar(monomio info){

        }

        void clearHelp(nodo* nodo){
            if (nodo == NULL) return;
            clearHelp(nodo->izq);
            clearHelp(nodo->der); 
            delete nodo; 
        }

        void inOrdenHelp (nodo* nodo) {
            if (nodo == NULL) return;
            inOrdenHelp (nodo->izq); 
            procesar(nodo->info); 
            inOrdenHelp (nodo->der); 
        }
        void preOrdenHelp(nodo* nodo) {
            if (nodo == NULL) return;
            procesar(nodo->info);
            preOrdenHelp(nodo->izq);
            preOrdenHelp(nodo->der);
        }

        void postOrdenHelp(nodo* nodo) {
            if (nodo == NULL) return;
            postOrdenHelp(nodo->izq);
            postOrdenHelp(nodo->der);
            procesar(nodo->info);

        }
        int findHelp(nodo* nodo, tElem exp) {
            if (nodo == NULL) return 0; 
            if (nodo->info.exp == exp ) return 1; 
            if (exp < nodo->info.exp){
                return findHelp(nodo->izq,exp);
            }
            else{
                return findHelp(nodo->der,exp);
            }
        }
        void insertHelp(nodo *node,tElem coef, tElem exp){
            if (find(exp) == 0){
                if ( nElems == 0){
                    //cout << "entra primera" << endl;
                    raiz = new nodo;
                    raiz->info.coef = coef;
                    raiz->info.exp = exp;
                    //cout << raiz->info << endl;
                    raiz->izq = NULL;
                    raiz->der = NULL;
                    //cout << "sale primera" << endl;
                    //cout << aux->info << endl;
                    nElems++;
                    return;
                }
                if (node -> info.exp < exp){
                    if(node->der == NULL){
                        node->der = new nodo;
                        node->der->info.coef = coef;
                        node->der->info.exp = exp;
                        node->der->izq =NULL;
                        node->der->der = NULL;
                        nElems++;
                        return;
                    }
                    insertHelp(node->der,coef,exp);
                }else{
                    if(node->izq == NULL){
                        node->izq = new nodo;
                        node->izq->info.coef = coef;
                        node->izq->info.exp = exp;
                        node->izq->izq =NULL;
                        node->izq->der = NULL;
                        nElems++;
                        return;
                    }
                    insertHelp(node->izq,coef,exp);
                }
            }

        }
        void displayHelp(nodo* nodo , int nivel)  {
            int i;
            if (nodo != NULL) {
                displayHelp(nodo -> der, nivel +1);
                cout << endl;
                if (nodo == raiz) cout << "Raiz->: ";
                else {
                    for (i = 0;i < nivel;i++)
                    cout << "       ";

                }
                cout << nodo->info.exp <<" " << nodo->info.coef << endl;
                displayHelp(nodo->izq,nivel+1);
            }
        }

        void removeHelp(nodo* preNodo ,nodo* node,tElem coef, tElem exp) {
            //cout << nodo->info << endl;
            if ( node == NULL){
                return;
            }
            //cout << "entra" << endl;
            //cout << nodo->info<< endl;
            if (node->info.coef == coef && node->info.exp == exp){
                //caso 1
                if (node->izq == NULL && node->der == NULL){
                    cout << "elimina caso 1" << endl;
                    if (raiz->info.coef == coef && raiz->info.exp == exp){
                        delete node;
                        raiz = NULL;
                        return;
                    }
                    if (preNodo->der->info.coef == coef && preNodo->der->info.exp == exp){
                        delete node;
                        preNodo->der =NULL;
                        return;
                    }else{
                        delete node;
                        preNodo->izq =NULL; 
                        return;
                    }
                }
                //caso 2
                if (node->izq == NULL && node->der != NULL){
                    cout << "eliminar caso 2" << endl;
                    if (preNodo->der->info.coef == coef && preNodo->der->info.exp == exp){
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
                    cout << "eliminar caso 2" << endl;
                    if (preNodo->der->info.coef == coef && preNodo->der->info.exp == exp){
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
                cout << "eliminar caso 3" << endl;
                nodo* pred =  predecesor(node->izq);
                //cout << "el predecesor es: "<< pred->info<<endl;
                //caso 3.1
                if (pred->der == NULL && pred->izq == NULL){ 
                    node->info = pred->info;
                    node->izq = NULL;
                    delete pred;
                    return;
                }
                //caso 3.2
                if (pred->der==NULL && pred->izq !=NULL){
                    node->info = pred->info;
                    node->izq = pred->izq;
                    delete pred;
                    return;
                }
                //caso 3.3
                nodo* aux =pred->der;
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
            removeHelp(preNodo,node->izq,coef,exp);
            removeHelp(preNodo,node->der,coef,exp); 

        }

        nodo* predecesor(nodo* nodo){
            if (nodo->der == NULL){
                return nodo;
            }
            if (nodo->der->der == NULL){
                return nodo;
            }
            predecesor(nodo->der);
        }

    public:
        tABB(){
            raiz = NULL;
            nElems = 0;
        }
        ~tABB(){
            clear();
        }
        void clear();
        void insert(tElem coef, tElem exp);
        void remove(tElem coef, tElem exp);
        int find(tElem exp);
        int size();
        void inOrden();
        void preOrden();
        void postOrden();
        void display();
};


void tABB::clear(){
    clearHelp(raiz);
    raiz = NULL;
    nElems = 0;
}

void tABB::inOrden () {
    inOrdenHelp (raiz);
}

void tABB::preOrden() {
    preOrdenHelp(raiz);
}

void tABB::postOrden() {
    postOrdenHelp(raiz);
}

int tABB::find(tElem exp) {
    return findHelp(raiz,exp);
}

void tABB::insert(tElem coef, tElem exp ){
    insertHelp(raiz,coef,exp);
}

void tABB::remove(tElem coef, tElem exp) {
    if( find(exp) == 0) {
        cerr << "elemento no existente en arbol" << endl;
        return;
    }
    nElems--;
    nodo* nulo;
    removeHelp(nulo,raiz,coef,exp);  
} 

void tABB::display(){
    displayHelp(raiz,1);
}

/*+
int main(){
    tABB arbol;
    /*
    // caso 1 simple
    cout << "caso 1 simple" << endl;
    cout << "original" << endl;
    cout << endl;
    arbol.insert(0,28);
    arbol.insert(0,16);
    arbol.insert(0,30);
    arbol.insert(0,5);
    arbol.insert(0,19);
    arbol.insert(0,17);
    arbol.insert(0,21);
    arbol.insert(0,12);
    arbol.insert(0,29);
    arbol.insert(0,32);
    arbol.insert(0,28);
    arbol.display();
    cout << endl;
    cout << "despues del remove" << endl;
    cout << endl;
    arbol.remove(0,17);
    arbol.display();


    arbol.clear();

    // caso 1 complejo
    cout << "caso 1 complejo" << endl;
    cout << "original" << endl;
    cout << endl;
    arbol.insert(6,28);
    arbol.insert(2,16);
    arbol.insert(4,30);
    arbol.insert(6,5);
    arbol.insert(33,19);
    arbol.insert(2,17);
    arbol.insert(8,21);
    arbol.insert(10,12);
    arbol.insert(44,29);
    arbol.insert(50,32);
    arbol.insert(1,28);
    arbol.display();
    cout << endl;
    cout << "despues del remove" << endl;
    cout << endl;
    arbol.remove(2,17);
    arbol.display();
    */


    //caso 2 

    /*
    cout << "original" << endl;
    cout << endl;
    arbol.insert(6,28);
    arbol.insert(8,30);
    arbol.insert(1,16);
    arbol.insert(5,19);
    arbol.insert(2,17);
    arbol.insert(3,21);
    arbol.insert(0,29);
    arbol.insert(7,32);
    arbol.insert(7,32);
    arbol.insert(2,32);
    arbol.display();
    cout << endl;
    cout << "despues del remove" << endl;
    cout << endl;
    arbol.remove(1,16);
    arbol.display();
    */


    // caso 3
/*
    cout << "original" << endl;
    cout << endl;
    arbol.insert(6,28);
    arbol.insert(2,16);
    arbol.insert(4,30);
    arbol.insert(3,25);
    arbol.insert(8,5);
    arbol.insert(7,12);
    arbol.insert(66,20);
    arbol.insert(6,18);
    arbol.insert(9,23);
    arbol.insert(0,29);
    arbol.insert(22,32);
    arbol.display();
    cout << endl;
    cout << "despues de remove" << endl;
    cout << endl;
    arbol.remove(6,28);
    arbol.display();

    return 0;
}
*/

