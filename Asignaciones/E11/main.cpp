//Librerias necesarias
#include <iostream>
#include <vector>

//Libreria para generar distintos seeds para rand()
#include <ctime>

//Librerias para el tiempo
#include <chrono>
#include <thread>

//Namespaces
using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

int main()
{
	//Generamos los distintos seeds para el tiempo
	srand(time(0));

	//Declaramos el número máximo de items que puede tener el inventario
	int inventorySpaceMinerals = 3;

	//Declaro el numero maximo de hojas que puede tener el inventario
	int inventorySpaceLeaves = 5;

	//Declarar el número de minerales y hojas que están en el inventario por el momento
	int inventorySpaceOccMin = 0;
	int inventorySpaceOccLeaf = 0;

	//Se crea el vector inventory
	vector<string> inventory;

	//Se crean los vectores que mantienen los cristales y hojas disponibles
	const vector<string> minerals
	{
		"Cristal Azul (A)", "Cristal Verde (V)"
	};

	const vector<string> leaves
	{
		"Verila Pluma (VP)", "Secta Doralis (SD)", "Crystalia Fulminis (CF)"
	};

	//Creamos la variable para la userInput
	string userInput = "N/A";

	//Creamos las variables para almacenar la posicion de los elementos aleatorios dentro de "minerals" y "leaves"
	int randomMineralPos;
	int randomLeavesPos;

	//Creamos las variables para el máximo y mínimo de los valores random
	const int mineralsMin = 0;
	const int mineralsMax = minerals.size() - 1;

	const int leavesMin = 0;
	const int leavesMax = leaves.size() - 1;

	//Se programa el emulador de "minando..."
	while (userInput != "exit" && userInput != "0")
	{
		//Se crea el menú para el usuario
		cout << "Presiona las teclas:" << "\n";
		cout << "i. Revisar inventario" << endl;
		cout << "h. Obtener hojas" << endl;
		cout << "m. Obtener minerales" << endl;
		cout << "0. Salir" << endl;

		cout << "=========================================" << endl;
		cout << "Entrada de usuario: ";
		cin >> userInput;

		//Si el usuario escribe I
		if (userInput == "i" || userInput == "I")
		{
			system("CLS");

			//Se usa la librería chrono y thread para hacer el segundo de conteo para la apertura del inventario
			cout << "Abriendo inventario.";
			sleep_for(milliseconds(500));
			cout << ".";
			sleep_for(milliseconds(500));
			cout << "." << endl;

			//Se verifica si el inventario está vacío
			if (inventorySpaceMinerals == 0 && inventorySpaceLeaves == 0)
			{
				cout << "INVENTARIO VACIO!!" << endl;
				sleep_for(seconds(1));
				system("pause");
				system("CLS");
			}
			else
			{
				for (int i = 0; i < inventory.size(); i++)
				{
					cout << inventory[i] << "\n";
				}
			}
		}

		//Si el usuario escribe M
		else if (userInput == "m" || userInput == "M")
		{
			system("CLS");
			
			//Como solo se puede agregar minerales cuando su parte del inventario tiene espacio, verificamos si tiene espacio o no.
			if (inventorySpaceOccMin < inventorySpaceMinerals)
			{
				//Se usan las librerías chrono y thread para hacer el temporizador de un segundo de minado.
				cout << "Minando.";
				sleep_for(milliseconds(500));
				cout << ".";
				sleep_for(milliseconds(500));
				cout << "." << endl;

				//Se genera una posición aleatoria dentro de minerals
				randomMineralPos = rand() % (mineralsMax - mineralsMin + 1) + mineralsMin;

				//Se le informa al usuario el mineral que se obtuvo al minar
				cout << "Obtuviste " << minerals[randomMineralPos] << endl;
				cout << endl;
				inventorySpaceOccMin++;

				//Se agrega el mineral obtenido al inventario
				inventory.push_back(minerals[randomMineralPos]);

				//Se le informa al usuario los espacios restantes para minerales
				cout << "Te quedan " << inventorySpaceMinerals - inventorySpaceOccMin << " espacios disponibles para minerales y " << inventorySpaceLeaves - inventorySpaceOccLeaf << " espacios para hojas en el inventario." << endl;

				system("pause");
				system("CLS");
			}
			else
			{
				system("CLS");
				cout << "INVENTARIO LLENO!!" << endl;
				sleep_for(seconds(2));
				system("pause");
				system("CLS");
			}
		}

		//Si el usuario escribe H
		else if (userInput == "h" || userInput == "H")
		{
			system("CLS");

			if (inventorySpaceOccLeaf < inventorySpaceMinerals)
			{
				//Se usan las librerias chrono y thread para hacer el temporizador de un segundo de recogida.
				cout << "Recogiendo.";
				sleep_for(milliseconds(500));
				cout << ".";
				sleep_for(milliseconds(500));
				cout << "." << endl;

				//Se genera una posicion aleatoria dentro de leaves
				randomLeavesPos = rand() & (leavesMax - leavesMin + 1) + leavesMin;

				//Se le informa al usuario la hoja que se recogio
				cout << "Obtuviste " << leaves[randomLeavesPos] << endl;
				cout << endl;
				inventorySpaceOccLeaf++;

				//Se agrega la hoja recogida al inventario
				inventory.push_back(leaves[randomLeavesPos]);

				//Se le informa al usuario los espacios restantes en los inventarios
				cout << "Te quedan " << inventorySpaceLeaves - inventorySpaceOccLeaf << " espacios disponibles para hojas y " << inventorySpaceMinerals - inventorySpaceOccMin << " espacios para minerales en el inventario." << endl;
				
				system("pause");
				system("CLS");
			}
		}
		cout << "\n\n";
	}

}