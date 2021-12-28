#include<iostream>
#include<string>
#include<cmath>
 
using namespace std;

// Codigo


typedef int tElemLista; // Elementos dentro de un monomio.

struct monomio{
    int coef;
    int exp; 
    int poli;
};

struct nodo {
    monomio dato;
    nodo* next;
};

class eLista {
    private:
        nodo* head;
        nodo* tail;
        nodo* curr;

        unsigned int listSize;
        unsigned int pos;

    public:
        eLista(){
            head = tail = curr = new nodo;
            listSize = 0;
            pos = 0;           
        };
        ~eLista(){
            clear();
        };

    void clear ();
    int insert(tElemLista coef,tElemLista exp, tElemLista poli);
    void append(tElemLista coef,tElemLista exp, tElemLista poli);
    monomio erase();
    void moveToStart();
    void moveToEnd();
    void next();
    void prev();
    int lenght();
    int currPos();
    void moveToPos(unsigned int pos);
    monomio getValue();
    void ordenDes();
    void printL();
    float evaluar(int pos, float x);


};

void eLista::clear(){
    nodo* aux;
    curr = head;
    for(int i = 0; i< listSize; i++) {
        aux = curr;
        curr = curr -> next;
        delete aux;


    }
    pos = 0;
    listSize = 0;
    curr =head;
    curr->dato.coef = 0;
    curr->dato.exp = 0;
    curr->dato.poli = 0;
};

int eLista::insert(tElemLista coef,tElemLista exp, tElemLista poli ){

    nodo* aux = curr->next;
    curr->next = new nodo;
    curr->next->dato.coef = coef;
    curr->next->dato.exp = exp;
    curr->next->dato.poli = poli;
    curr->next->next = aux;
    if (curr == tail) tail = curr->next;
    listSize++;
    return pos;
};

void eLista::append(tElemLista coef, tElemLista exp, tElemLista poli ){
    tail = tail -> next = new nodo ;
    tail -> dato.coef = coef;
    tail -> dato.exp = exp;
    tail -> dato.poli = poli;
    tail -> next = NULL;
    listSize++;  
    
    
};
monomio eLista::erase(){
    monomio val;
    if (curr!=tail){      
        nodo* aux = curr->next;
        val = aux->dato;    
        curr->next = aux->next;
        listSize--;
        delete aux;
    }
    return val;
    
};
    
    
void eLista::moveToStart(){
    pos = 0;
    curr = head;
};

void eLista::moveToEnd(){
    pos = listSize;
    curr = tail;
};

void eLista::next() {
    if (curr == tail) {cerr << -1<< "Error posicion en la lista "<< endl;
    }
    curr = curr->next;
    pos++;

}
void eLista::prev(){
    if (curr == head) {cerr << -1<< "Error posicion en la lista" << endl;
    }
    nodo *aux;
    aux = head;
    bool flag =true;

    while(flag == true){
        aux = aux->next;
        if (aux->next == curr){
            curr = aux;
            pos--;
            flag = false;
        }
    }
};

monomio eLista::getValue(){
    
    monomio val;
    if (curr == tail) {
        val = curr-> dato;
        return val;
    }
    val = curr-> next-> dato;
    return val;


};

void eLista::moveToPos(unsigned int posicion){
    unsigned int i;
    if (posicion < 0 || posicion > listSize) return;
    curr = head;
    pos = 0;
    for (i = 0; i < posicion; i++) {
        curr = curr->next;
        pos++;
    }
};

int eLista::lenght(){
    return listSize;

};

int eLista::currPos() {
    return pos;
};
void eLista::printL() {
    nodo * aux;
    aux = head;
    for (int i = 0; i <= listSize; i++) 
    {   if (i != 0){
            cout <<aux->dato.coef << " ";
            cout <<aux->dato.exp << " ";
            cout <<aux->dato.poli << " ";
            cout << endl;
        }
        aux = aux->next;
    }
};

/*****                                                                                                                                                                                                     
* float evaluar                                                                                                                                                                                          
******                                                                                                                                                                                                     
* La funcion recorre la lista filtrando por posicion, luego almacena un copia del exponente mas grande y en base a eso entra en un ciclo que dura esa cantidad de iteraciones                                                 
* Input:                                                                                                                                                                                                   
*   int pos: Es el número del polinomio que se ocupara.                                                                                                                                                    
*   float x: Es el flotante por el que te multiplacara el polinomio.                                                                                                                                 
******                                                                                                                                                                                                     
* Returns:                                                                                                                                                                                                 
*   retorna la evaluacion del x en el polinomio.                                                                                                                                                                               
*****/

float eLista::evaluar(int pos , float x){
    nodo * aux;
    aux = head->next;
    int exp_temp, coef_temp;
    float result = 0;
    bool flag= true;
    for (int i = 0; i < listSize; i++)
    {
        if (aux -> dato.poli == pos)
        {
            break;
        }
        aux = aux->next;
    }
        
        while(aux -> dato.poli == pos){
            
            if (flag == true) {
                exp_temp = aux->dato.exp;
                cout << "entro " << endl;
                cout << "exp_temp; " << exp_temp << endl;
                flag = false;
            }

            while (exp_temp != aux->dato.exp) {
                result = result*x;
                  cout << "entro " << endl;
                cout << "result: " << result << endl;
                cout << "exp actual"  << aux->dato.exp << endl;
                exp_temp--;
            }
            if (aux->dato.exp == 0 ) {
                coef_temp = aux->dato.coef;
                //cout << "coef temp: " << coef_temp << endl;
                result += coef_temp;
                cout << "result: " << result << endl;
                cout << "exp actual"  << aux->dato.exp << endl;
                break;

                
            }
            else{
               // cout << "coef temp: " << aux->dato.coef << endl;
                coef_temp = aux->dato.coef;
                //cout << "coef temp: " << coef_temp << endl;
                result = (result + coef_temp) *x;
                 cout << "result: " << result << endl;
                 cout << "exp actual"  << aux->dato.exp << endl;
              
                exp_temp--;
                aux = aux->next;
            }
             
            
            
            
        

        }
     
    return result;
    

}











    