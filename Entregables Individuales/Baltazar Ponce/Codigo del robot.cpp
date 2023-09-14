#include <iostream>
#include <string>
using namespace std;
class Motor{
private:
	int potencia;
public:
	Motor(int potencia){
		
	};
	void acelerar(int unidades){
		cout<<"El motor se desplazó "<<unidades<<" unidades de distancia"<<endl;
	}
};

class Sensor{
private:
	string nombre;
public:
	Sensor(string nombre){
		
	};
	bool emitir(){
		int senial;
		cout<<"Hay lugar para seguir avanzando? (1 si hay lugar)"<<endl;
		cin>>senial;
		if (senial == 1){
			return true;
		}else return false;
	}
	bool recibir(int senial){
		if (senial == true){
			return true;
		}
		else return false;
	};
};


int main() {
	bool boton_run = true;
	Sensor sensor("Sensor Ultrasonico");
	Motor motor_izq(80);
	Motor motor_der(100);
	string pregunta;
	
	while (boton_run == true){
		int senial = sensor.emitir();
		bool receptor = sensor.recibir(senial);
		if (receptor == true){
			motor_izq.acelerar(10), motor_der.acelerar(10);
			motor_izq.acelerar(5);
			cout<<"Desea apagar el dispositivo?"<<endl;
			cin>>pregunta;
			if (pregunta == "si"){
				boton_run = false;
			}
		} else {
			cout<<"El dispositivo no puede avanzar. ¿Desea apagarlo?"<<endl;
			cin>>pregunta;if (pregunta == "si"){
				boton_run = false;
			} else {
				cout<<"Mueva manualmente el dispositivo";
			}
		} 
	}
	
	cout<<"El dispositivo fue apagado";
	return 0;
}

