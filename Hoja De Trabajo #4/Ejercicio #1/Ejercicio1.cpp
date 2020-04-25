/*					EJERCICIO 1
En la región de la sierra de los Cuchumatanes la compañía Xterminio S.a., tiene las siguientes tarifas: 

	TIPO	SERVICIO		COSTO X HECTAREA
	1		Mala Hierba			10
	2		Langostas			20
	3		Gusanos				30
	4		Todo lo anterior	50
	
Además del área a fumigar es mayor a 500 hectáreas se tienen un descuento del 5%. 
Adicionalmente, si el total a pagar por el servicio es mayor a Q1,500 se tiene un descuento adicional del 10% sobre el excedente.

La compañía necesita las estadísticas de los servicios que ha ofrecido a un grupo de agricultores durante un periodo de tiempo. 
Por cada servicio debe ingresar los datos siguientes:

	-Tipo de Fumigación (1-4)
	-Número de hectáreas 

Toda esta información deberá almacenarse en una base de datos (archivo plano).

El programa deberá de leer los datos del archivo que tiene la
información antes almacenada y mostrar la cantidad de servicios de cada tipo de fumigación, determinar
el tipo servicio con mayor demanda y el monto total pagado por los clientes.
*/


#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Declaración de estructura de tipo Servicio
struct Servicios{
	int tipoFumigacion;
	float noHectareas;
	float pagado;
};

//Delcaración de vector de tipo estructura de Servicio
std::vector<Servicios> vtrServicio;

//Función que muestra los tipos de servicios
void tipoServicios(){
	cout << "------------------------------REGISTRO DE SERVICIO------------------------------" << endl;
	cout << "TIPO" << "\t" << "SERVICIO" << "\t" << "COSTO X Hectarea" << endl;
	cout << "1" << "\t" << "Mala Hierba" << "\t" << "\t" << "Q. 10" << endl;
	cout << "2" << "\t" << "Langostas" << "\t" << "\t"<< "Q. 20" << endl;
	cout << "3" << "\t" << "Gusanos " << "\t" << "\t" << "Q. 30" << endl;
	cout << "4" << "\t" << "Todo lo anterior" << "\t" << "Q. 50" << endl;
}

/*Función encargada de calcular descuentos y totales a pagar
	-Devuelve un tipo de dato float
	-Recibe una variable de tipo int --> No Servicio
	-Recibe una variable de tipo float --> NoHectareas
*/
float totalPagar(int noServicio, float noHectareas){
	float totalPagar;
	float precioServicio;
	float excedente;
	float descuento;
	float descuentoHectareas;
	
	//Validación correspondiente al tipo de servicio
	switch(noServicio){
		case 1:
			precioServicio = 10.00;
			break;
		case 2:
			precioServicio = 20.00;
			break;
		case 3:
			precioServicio = 30.00;
			break;
		case 4: 
			precioServicio = 50.00;
			break;
	}
	
	//Realiza el descuento correspondiente a si el No. De Hectáreas es mayor a 500
	if (noHectareas > 500){
		descuentoHectareas = (precioServicio * noHectareas) * 0.05;
		totalPagar = (precioServicio * noHectareas) - descuentoHectareas;
	}else{
		totalPagar = precioServicio * noHectareas;
	}
	
	/*Realiza el descuento correspondiente a si el total a pagar es mayor a Q1,500.
		El descuento se realiza al accedente.
	*/
	if (totalPagar > 1500){
		excedente = (totalPagar - 1500);
		descuento = excedente * 0.10;
		totalPagar = 1500 + (excedente - descuento);
	}
	
	//Salida de la función en consola
	cout << "El total a pagar es: Q" << totalPagar << endl;
	
	//Retorna el valor de tipo float
	return totalPagar;
}

//Función encargada de procesar servicios 
void registrarServicio(){
	int opcionServicio;
	float hectareas;
	Servicios strServicio;
	
	//Se muestran los tipos de servicios
	tipoServicios();
	
	//Input de Tipo de Servicio y Número de Hectáreas
	cin >> opcionServicio;
	cout << "Ingrese el número de hectáreas: " << endl;
	cin >> hectareas;
	
	//Según el tipo de servicio se realizan las funciones correspondientes
	switch(opcionServicio){
		case 1:
			//Asigna el tipo de Fumigación a la estructura.
			strServicio.tipoFumigacion = 1;
			//Asigna el número de hectáreas a la estructura
			strServicio.noHectareas = hectareas;
			//Guarda el dato float que devuelve la función en la estructura de datos.
			strServicio.pagado = totalPagar(strServicio.tipoFumigacion, hectareas); 
			break;
		case 2:
			strServicio.tipoFumigacion = 2;
			strServicio.noHectareas = hectareas;
			strServicio.pagado = totalPagar(strServicio.tipoFumigacion, hectareas);
			break;
		case 3:
			strServicio.tipoFumigacion = 3;
			strServicio.noHectareas = hectareas;
			strServicio.pagado = totalPagar(strServicio.tipoFumigacion, hectareas);
			break;
		case 4:
			strServicio.tipoFumigacion = 4;
			strServicio.noHectareas = hectareas;
			strServicio.pagado = totalPagar(strServicio.tipoFumigacion, hectareas);
			break;
		default:
			cout << "Opción inválida";
			break;
	}
	
	//Grabar Servicio en archivo
	ofstream archivoServicios("SERVICIOS.txt", std::ios_base::app);
	
	archivoServicios <<
	strServicio.tipoFumigacion << "\t"<< strServicio.noHectareas << "\t" << 
	strServicio.pagado << endl;
	
	//Cerrar Archivo
	archivoServicios.close();
}

//Función encargada de extraer datos de archivo
void leerArchivo(){
	//Declaración de variable de tipo archivo.
	ifstream archivoServicios;
	
	//Declaración de variable de tipo estructura 
	Servicios stServicios;

	
	//Abrir archivo
	archivoServicios.open("SERVICIOS.txt", ios::in);
	
	//Obtener los datos desde el archivo.
	while(archivoServicios >> stServicios.tipoFumigacion >> stServicios.noHectareas >> stServicios.pagado){
		//Guardar los datos obtenidos en un vector
		vtrServicio.push_back(stServicios);
	}
	
	//Cerrar archivo
	archivoServicios.close();
	
	return;
}


/*Función encargada de realizar otras gestiones
	-Recibe una variable de tipo Int, para determinar la salida de la función.
*/
void otrasGestiones(int opcionMenu){
	int contadorServicio1 = 0;
	int contadorServicio2 = 0;
	int contadorServicio3 = 0;
	int contadorServicio4 = 0;
	float montoTotalPagado;
	int servicioMayorDemanda = 0;
	string servMayorDemanda;
	
	//Invocación de función para extraer datos de archivo
	leerArchivo();
	
	//Iteración del vector 
	for (int i = 0; i <= vtrServicio.size(); i ++){
		//Se realiza el cambio e incremento de contador según sea el tipo de servicio
		switch (vtrServicio[i].tipoFumigacion){
			case 1:
				contadorServicio1 = contadorServicio1 + 1;
				break;
			case 2:
				contadorServicio2 = contadorServicio2 +1;
				break;
			case 3:
				contadorServicio3 = contadorServicio3 +1;
				break;
			case 4:
				contadorServicio4 = contadorServicio4 + 1;
				break;
		}
		
		//Guarda el total pagado por los clientes
		montoTotalPagado = montoTotalPagado + vtrServicio[i].pagado;
	}
	
	//Declaración de arreglo de tipo Int, que almacena los totales de servicios según los contadores.
	int arregloTotales[4] = {contadorServicio1, contadorServicio2, contadorServicio3, contadorServicio4};
	
	//Iteración del arreglo para determinar el tipo de servicio con mayor demanda
	for (int i = 0; i <= 3; i ++){
		if (arregloTotales[i] > servicioMayorDemanda){
			servicioMayorDemanda = arregloTotales[i];
			if (i = 0){
				servMayorDemanda = "1. MALA HIERBA";
			}
			else if (i = 1){
				servMayorDemanda = "2. LANGOSTAS";
			}
			else if (i = 2){
				servMayorDemanda = "3. GUSANOS";
			}
			else if (i = 3){
				servMayorDemanda = "4. TODO LO ANTERIOR";
			}
		}
	}
	
	//Evalúa el valor de la variable opcionMenu para realizar la salida correspondiente
	switch(opcionMenu){
		case 2:
			cout << "------------------------------TOTAL DE SERVICIOS POR TIPO DE FUMIGACIÓN------------------------------" << endl;
			cout << "EL TOTAL DE SERVICIOS POR EL TIPO DE FUMIGACIÓN 1. MALA HIERBA ES: " << contadorServicio1 << endl;
			cout << "EL TOTAL DE SERVICIOS POR EL TIPO DE FUMIGACIÓN 2. LANGOSTAS ES: " << contadorServicio2 << endl;
			cout << "EL TOTAL DE SERVICIOS POR EL TIPO DE FUMIGACIÓN 3. GUSANOS ES: " << contadorServicio3 << endl;
			cout << "EL TOTAL DE SERVICIOS POR EL TIPO DE FUMIGACIÓN 4. TODO LO ANTERIOR ES: " << contadorServicio4 << endl;
			cout << "-----------------------------------------------------------------------------------------------------" << endl;
			break;
		case 3:
			cout << "------------------------------SERVICIO CON MAYOR DEMANDA------------------------------" << endl;
			cout << "EL SERVICIO CON MAYOR DE MANDA ES EL No. " << servMayorDemanda << endl;
			cout << "--------------------------------------------------------------------------------------" << endl;
			break;
		case 4:
			cout << "------------------------------MONTO TOTAL PAGADO------------------------------" << endl;
			cout << "EL MONTO TOTAL PAGADO ES DE Q." << montoTotalPagado << endl;
			cout << "------------------------------------------------------------------------------" << endl;
			break;	
	}
}

//Función Principal
int main(){
	//Declaración de variables
	char opcion;
	string vacio;
	bool finalizar = false;
	
	//Menú del programa
	
	do{
		fflush(stdin);
		cin.clear();
		cout << "------------------------------XTerminacion S.A.------------------------------" << endl;
		cout << "1. Registrar servicio" << endl;
		cout << "2. Cantidad de servicios por tipo de fumigación" << endl;
		cout << "3. Servicio con mayor demanda" << endl;
		cout << "4. Monto total pagado por los clientes" << endl;
		cout << "5. Salir" << endl;
		cout << "Elija una opción (1-5)" << endl;
		cin >> opcion;
		
		switch(opcion){
			case '1':
				registrarServicio();
				break;
			case '2':		
				/*Invocación de la función otrasGestiones		
					-Recibe un valor/variable de tipo Int, para determinar la salida de la función
				*/
				otrasGestiones(2);
				//Limpia el vector
				vtrServicio.clear();
				break;
			case '3':
				otrasGestiones(3);
				vtrServicio.clear();
				break;
			case '4':
				otrasGestiones(4);
				vtrServicio.clear();
				break;
			case '5':
				finalizar = true;
				break;
			default:
				cout << "Opción inválida";
				getchar();
				getline(cin, vacio);
				break;
		}
	}while (finalizar != true);
	
	return 0;
}
