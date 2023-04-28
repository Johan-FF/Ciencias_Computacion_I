#include <iostream>

using namespace std;

class monticulo{
	private:
		int *Arr;
		int tam;
		int PosAct;
	public:
		monticulo(int);
		bool insertar(int);
		int atender();
		void imprimirArreglo();
		bool monticulo_lleno();
};

monticulo::monticulo(int t) {
    tam = t;
    Arr = new int[tam+1]; // Reservamos memoria para el arreglo
    PosAct = 0;
}

bool monticulo::monticulo_lleno() {
    return PosAct == tam;
}

bool monticulo::insertar(int valor) {
	if(monticulo_lleno()) {
		return false;
	}
	
	Arr[++PosAct] = valor;
	int pos_hijo = PosAct;
	int pos_padre = pos_hijo / 2;
	
	while(pos_padre >= 1 && Arr[pos_hijo] > Arr[pos_padre]) {
		swap(Arr[pos_hijo], Arr[pos_padre]);
		pos_hijo = pos_padre;
		pos_padre = pos_hijo / 2;
	}
	
	return true;
}

int monticulo::atender() {
	int pen=Arr[PosAct--];
	int atendido=Arr[1], pos=1;

	do {
		if( pen>Arr[pos*2] && pen>Arr[pos*2+1] ){
			Arr[pos]=pen;
			break;
		} else if( Arr[pos*2]>pen && Arr[pos*2]>Arr[pos*2+1] ){
			Arr[pos] = Arr[pos*2];
			pos = pos*2;
		} else if( Arr[pos*2+1]>pen && Arr[pos*2+1]>Arr[pos*2] ){
			Arr[pos] = Arr[pos*2+1];
			pos = pos*2+1;
		}
		if( pos*2+1>PosAct ) break;
	} while ( pos<PosAct );
	Arr[pos]=pen;

	return atendido;
}

void monticulo::imprimirArreglo() {
    for (int i = 1; i <= PosAct; i++) {
        cout << Arr[i] << " ";
    }
    cout << endl;
}
