#include<iostream>
#include <string>
#include<fstream>
#include "TdaPolinomio.cpp"

using namespace std;



eLista lista;

int tamano(){
    fstream fp;
    fp.open("poli.txt", ios::in); // cambiar nombre polinomio.txt

    if(!fp.is_open()) {
        cerr << "Error al abrir el archivo" << endl;
        return -1;
    }
    string s;
    int largo = 0;
    while (getline(fp,s)){
        largo++;
    }
    fp.close();
    return largo;
}




int main() {
    int n;
    fstream fp;
    fp.open("poli.txt", ios::in); // cambiar nombre polinomio.txt

    if(!fp.is_open()) {
        cerr << "Error al abrir el archivo" << endl;
        return -1;
    }

    fp >> n;
    int n_coef;
    int n_exp;
    int n_poli;
    int final = 0;
    int aux = 0;
    int aux1;
    int total = 0;
    
    for(int i =0; i< n; i++) {
        fp >>  n_poli;
        total+= n_poli;
        //cout << "total " << total << endl;
        for(int j = 0; j<n_poli ; j++){
            fp >> n_exp;
            fp >> n_coef;
            lista.append(n_coef,n_exp,i); // i representa al polinomio al que pertenece.
            final++;

        }
        //lista.printL();
        monomio monomio1;
        monomio monomio2;
        for (int j = aux ; j <total; j++){
            lista.moveToPos(j);
            monomio1 = lista.getValue();
            //cout << " n poli: " << n_poli << endl;
            for (int k = 0 ; k < n_poli; k++){
                lista.moveToPos(j+k);
                monomio2 = lista.getValue();
                //cout << "monomio 1: " << monomio1.exp <<" monomio 2: "<< monomio2.exp  << endl;
                if (monomio1.exp < monomio2.exp){
                    //cout << "entra" << endl;
                    lista.moveToPos(j);
                    lista.erase();
                    lista.insert(monomio2.coef,monomio2.exp,monomio2.poli);
                    lista.moveToPos(j+k);
                    lista.erase();
                    lista.insert(monomio1.coef,monomio1.exp,monomio1.poli);
                    monomio1 = monomio2;
                    //cout << "cambio en la lista" << endl;
                    //lista.printL();
                    //cout << endl;
                }
            }
        }
        aux += n_poli;
        //lista.printL();
    }
    lista.printL();

    cout << lista.evaluar(2,3.5) << endl;//7.5
    cout << lista.evaluar(2,9) << endl;//24

    cout << "alerta " << endl;
    cout << lista.evaluar(0,1) << endl;//6
    cout << lista.evaluar(0,5.0) << endl;//1028
    cout << lista.evaluar(1,1) << endl;//-4
    cout << lista.evaluar(0,3.5) << endl;//363.5
   
    
    
    return 0;
}
    
    /*
    int aux = 0;
  
    int tmp,tmp1,temp2,temp3;
    int total = 0;
    for (int t = 0; t < lista_nmon.lenght(); t++) 
    {       
        lista_nmon.moveToPos(t);
        int val = lista_nmon.getValue();
        //cout << val << endl;
        total+=val;
        for(int i = aux; i < total;i++ )
        {
            lista_expo.moveToPos(i);
            tmp = lista_expo.getValue();
            //cout << "tmp :" << tmp << endl;
            aux++;
            for(int j = i+1; j <total; j++ ){
                lista_expo.moveToPos(j);
                tmp1 = lista_expo.getValue();
                //cout << "tmp1: " << tmp1 << endl;
                //cout << "j vale: " << j << endl;
                if ( tmp < tmp1 ){
                    //cout << "entra" << endl;
                    lista_expo.moveToPos(i); 
                    lista_expo.erase();
                    lista_expo.insert(tmp1);
                    lista_expo.moveToPos(j);
                    lista_expo.erase();
                    lista_expo.insert(tmp);


                    lista_coef.moveToPos(j);
                    temp3 = lista_coef.erase();
                       
                       
                    lista_coef.moveToPos(i);
                    temp2 = lista_coef.erase();
                    lista_coef.insert(temp3);

                    lista_coef.moveToPos(j);
                    lista_coef.insert(temp2);
                    lista_expo.moveToPos(i);
                    tmp = lista_expo.getValue();
                    //cout << "nuevo valor tmp: " << tmp << endl;
                    //cout << endl;
                    //lista_expo.printL();
                    //cout << " " << endl; //prueba ordenamiento listas
                    //lista_coef.printL();
                }
            }
        }
            
   
    }

    calculo.clear();
    int total0 = 0;
    int aux0 = 0;
    int aux1 = 0;
    int n1,n2 = 0;
    for (int t = 0; t < lista_nmon.lenght(); t++){
       lista_nmon.moveToPos(t);
       int val = lista_nmon.getValue();
       total0+= val;
       bool first = true;
       aux1 = aux0;
       int cantidad = 0;
       for (int s = aux0; s <total0; s++){
           //cout << " s vale: " << s << endl;
           lista_expo.moveToPos(s);
           lista_coef.moveToPos(s);
           aux0++;
           if(first){
               n1 = lista_expo.getValue();
               //cout << "agrego:  " << lista_coef.getValue()<< endl;
               calculo.append(lista_coef.getValue());
               first = false;
               cantidad++;
               //cout << "n1: " << n1 << endl;
           }else{
                if (n1-1 == lista_expo.getValue()){
                    n1 = lista_expo.getValue();
                    //cout << "agrego:  " << lista_coef.getValue()<< endl;
                    calculo.append(lista_coef.getValue());
                    //cout << "n1: " << n1 << endl;
                    cantidad++;
                }else{
                    calculo.append(0);
                    //cout << "agrego 0 " << endl;
                    n1--;
                    aux0--;
                    s--;
                    cantidad++;
                    //cout << "n1: " << n1 << endl;
                }
           }
       }

       for ( n1; n1 != 0; n1--){
           calculo.append(0);
           cantidad++;
           //cout << "agrego: 0" << endl;
       }
       can.append(cantidad);

    
    }



    /*cout << "Lista calculo" << endl;
    cout << endl;
    calculo.printL();
    cout << endl;
    cout << " Lista con la cantidad cantidad de monomios por polinomio de la lista calculo" << endl;
    cout<< endl;
    can.printL();
    cout << endl;
        

    cout << endl;
    lista_expo.printL();
    cout << " " << endl; //prueba ordenamiento listas
    lista_coef.printL();
    cout << endl;
    

    cout << "evaluar" << endl;
    float test,test1,test2;
    test = evaluar(2,3.5);
    test1 = evaluar(0,3);
    
    test2 = evaluar(1,1);
    cout << test << endl;
     cout << test2 << endl;
     cout << test1 << endl;
    cout << "fin evaluar" << endl;*/

   
   /*
   //2da parte lectura de funciones 
    ofstream pf ;
    pf.open("salidaPolinomio.txt");
    if (!pf.is_open()) {
        cerr << " Error el abrir el archivo " << endl ;
        return 1; 
    }
    string linea;
    string s;
    float x0;
    int x1;
    int x2;
    // nose cantidad de ciclos que hara
    getline(fp,linea);
    for (int i = 0; i<tamano()-largo;i++){
        fp >> s;
        //cout << s << endl;
        if (s == "COEFICIENTE"){
            //cout << "entro a coficiente" << endl;
            fp >> x1;
            //cout << x1 << endl;
            fp >> x2;
            //cout << x2 << endl;
            //cout << endl;
            cout << coeficiente(x1,x2) << endl;
            pf << coeficiente(x1,x2) << endl;
        }else{
            //cout << "entro a evaluar" << endl;
            fp >> x1;
            //cout << x1 << endl;
            fp >> x0;
            //cout << x0 << endl;
            cout << evaluar(x1,x0) << endl;
            pf << evaluar(x1,x0) << endl;
        }
    }
    //cout << largo << endl;
    //cout << tamano() << endl;
    fp.close();
    pf.close();
    return 0;
}
*/