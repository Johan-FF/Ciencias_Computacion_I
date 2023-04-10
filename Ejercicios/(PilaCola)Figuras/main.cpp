#include <cstdlib>
#include <iostream>
#include <ctype.h>
#include <iomanip>
#include "Pila.h"
#include "Cola.h"

using namespace std;

int main(){
    Cola<char> cola; 
    Pila<char> pila[3]; 
    int i,j, tam, grupo=0, orden[3];
    char x;

    do{
        cout<<"Escriba un mùltiplo de 3: ";
        cin>> tam;
    } while(tam%3!=0);

    i=1;
    x=0;
    cout<<x;
    while(i<=tam && i<255){
        if((x==0)||(x==13)||(x==32)||(x>6&&x<11)) x++;
        else {
            cola.insCola(x);
            i++; x++;
        }
    }
    cout<<"mire cuidadosamente los sìmbolos y elija uno\n";

    for(j=1; j<tam/3; j++){
        cout<<"  Gr1  "<<"Gr2  "<<"Gr3  "<<endl;
        while (!cola.colaVacia()){
            for (i=0; i<3; i++){
                x=cola.atenderCola();
                cout<<setw(4)<< x;
                pila[i].push(x);
                }
            cout<<"\n"; 
        }

        cout<< "elija el grupo en el que quedò el sìmbolo elegido (1, 2 o 3): ";
        cin>> grupo;
        switch(grupo){
            case 1 : {orden[0]=1; orden[1]=0; orden[2]=2;break;}
            case 2 : {orden[0]=0; orden[1]=1; orden[2]=2;break;}       
            case 3 : {orden[0]=0; orden[1]=2; orden[2]=1;break;}       
        }
        for (i=0; i<3; i++){
            while (!pila[orden[i]].pilaVacia()){
                cola.insCola(pila[orden[i]].pop());
            }
        }
    }

    j=tam-tam/2;

    for (i=1; i<=j; i++){
        x=cola.atenderCola();
    }
    
    cout<<"La figura elegida es: "<< x<<endl; 
    system("PAUSE");
    return 0;
}