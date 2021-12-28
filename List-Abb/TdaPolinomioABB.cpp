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
        monomio procesar(monomio info){
            return info;
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
            if (nodo == NULL) return ;
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
        monomio getMonomioHelp(nodo* nodo,tElem exp){
            monomio mon;
            mon.coef = 0;
            mon.exp = 0;
            if (nodo != NULL){
                if (nodo->info.exp == exp ) return nodo->info; 
                if (exp < nodo->info.exp){
                    return getMonomioHelp(nodo->izq,exp);
                }
                else{
                    return getMonomioHelp(nodo->der,exp);
                }
            }
            return mon;
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
        };
        /*****                                                                                                                                                                                                     
        * int maxHelp                                                                                                                                                                                   
        ******                                                                                                                                                                                                     
        *   Dado un puntero dentro de un arbol, la funcion busca el exponente maximo desde ese nodo;                                                 
        * Input:                                                                                                                                                                                                   
        *   nodo * nodo: Es un puntero que actuara de base para la busca de maximo                                                                                                                                                    
        *                                                                                                                                    
        ******                                                                                                                                                                                                     
        * Returns:                                                                                                                                                                                                 
        *   retorna el exponente maximo de dicho arbol                                                                                                                                                                        
        *****/
        int maxHelp(nodo* nodo){
            int val;
            while(nodo != NULL){
                val = nodo->info.exp;
                nodo = nodo->der;
            }

            return val;
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
        float evaluar(int pos , float x);
        monomio getMonomio(tElem exp);
        

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
monomio tABB::getMonomio(tElem exp) {
    return getMonomioHelp(raiz,exp);
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


/*****                                                                                                                                                                                                     
* float evaluar                                                                                                                                                                                          
******                                                                                                                                                                                                     
* La funcion Obtiene un arbol y busca por los monomios del arbol, luego almacena un copia del exponente mas grande y en base a eso entra en un ciclo que dura esa cantidad de iteraciones                                                 
* Input:                                                                                                                                                                                                   
*   int pos: Es el número del polinomio que se ocupara.                                                                                                                                                    
*   float x: Es el flotante por el que te multiplacara el polinomio.                                                                                                                                 
******                                                                                                                                                                                                     
* Returns:                                                                                                                                                                                                 
*   retorna la evaluacion del x en el polinomio.                                                                                                                                                                               
*****/
float tABB::evaluar(int pos , float x){
     nodo* aux;
     monomio temp;
     aux = raiz;
     int exp_temp, coef_temp;
     float result = 0;
     bool flag= true;
     int count,max;
     max = maxHelp(aux);
     exp_temp = max;
       //cout << "max: " << max << endl;
    
     

     for(int i = 0; i <= max; i++)
    {
        
        temp = getMonomio(exp_temp);
         // cout << "temp.coef " << temp.coef << endl;
           // cout << "temp.exp: " << temp.exp << endl;
       
        if (temp.coef != 0 && temp.exp != 0) {
            result = (result +temp.coef)*x;
             // cout << "result: " << result << endl;
            exp_temp--;

        }
        else if (temp.coef == 0 && temp.exp == 0 && exp_temp !=0) {
           result = result*x; 
             //cout << "result: " << result << endl;
            exp_temp--;
            
        }
        else if (temp.coef != 0 && temp.exp == 0){
            result +=temp.coef;
            //cout << "result: " << result << endl;
        }
      
        else if (temp.coef == 0 && temp.exp == 0 && exp_temp ==0) {
            exp_temp--;
            
        
        }
      
    
    }
     
return result;
}
     



     
 


int main(){
    tABB arbol;
    tABB arbol2;
    tABB arbol3;
    arbol.insert(-3,0);
    arbol.insert(3,1);
    arbol2.insert(3,0);
    arbol2.insert(8,3);
    arbol2.insert(5,1);
    arbol3.insert(-8,100);
    arbol3.insert(4,2);
   

    
    
/*
    cout << arbol.evaluar(2,3.5) << endl;//7.5
    cout << arbol.evaluar(2,9) << endl;//24*/
    cout << arbol2.evaluar(0,5) << endl;
    
   arbol2.display();
    cout << arbol2.evaluar(0,3.5) << endl;//363.5
    cout << arbol3.evaluar(1,1) << endl;//-4    
    

    return 0;
}

 