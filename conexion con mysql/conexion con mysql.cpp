// conexion con mysql.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <Windows.h>
#include <mysql.h>
#include<string>
#include<conio.h>
#include<cstring>



using namespace std; 
int q_estado; 
double cantidad_existente, mas_cantidad, menos_cantidad;;
int id_productos;
double conver, mas_conver, existente2;

string user, contra;  
string usuario;  
string new_usuario; 
string contrasena; 
string new_contra, contrasena_actual, verificacion_contra; 


void mostrar_productosE();
void recuperar_producto();
void nuevo_usuario();
void nuevo_contra();
void entrar_al_programa();
void extraer_cantidad(); 
void anadir_cantidad();
void actualizarCantidad(); 
void actualizarNombre(); 
void actualizar(); 
void confi(); 
void dibujarCuadro(int x1, int y1, int x2, int y2); 
void gotoxy(int x, int y); 
void mostrar_productos(); 
void ingresar_productos(); 
void eliminar_productos(); 
void eliminar_basecompleta(); 
void menu();

MYSQL* conectar; 
MYSQL_ROW fila; 
MYSQL_RES* resultado; 

int opc; 
bool listo = false;

int main(){
	
	//system("mode con: cols=80 lines=25 "); 
	 
	system("color 70"); 
	
	
	conectar = mysql_init(0);
	conectar = mysql_real_connect(conectar, "localhost", "root", "30949243", "chicha", 3306, NULL, 0);
	
	dibujarCuadro(0, 0, 78, 24);
	dibujarCuadro(1, 1, 77, 3);

	bool ingresar = false;
	int contador = 0;



	do {

		gotoxy(33, 2); cout << "Inciar Sesion" << endl;
		gotoxy(29, 10); cout << "Usuario: "; getline(cin, user); cout << endl;
		gotoxy(29, 11); cout << "Contrasena: ";//etline(cin, contra); cout<<endl; 

		char caracter;
		caracter = _getch();
		while (caracter != 13) {
			if (caracter != 8) {
				contra.push_back(caracter);
				cout << "*";


			}
			else {
				if (contra.length() > 0) {
					cout << "\b \b";
					contra = contra.substr(0, contra.length() - 1);
				}
			}
			caracter = _getch();

		}

		string login = "SELECT* FROM login WHERE usuario = '" + user + "' AND contraseña = '" + contra + "'";
		const char* l = login.c_str();
		int q_estado = mysql_query(conectar, l);

		if (!q_estado) {//MODIFICAR
			MYSQL_RES* res = mysql_store_result(conectar);
			int row = mysql_num_rows(res);    //ingresar = true;

			if (row == 1) {
				ingresar = true;
			}
			else {
				gotoxy(23, 15); cout << "Usuario y/o contraseña son incorrectos";
				cin.get();
				system("cls");
				dibujarCuadro(0, 0, 78, 24);
				dibujarCuadro(1, 1, 77, 3);
				contador++;
			}


		}

		contra = "";

	} while (!ingresar && contador < 3);//aqui

	if (!ingresar) {
		gotoxy(33, 2); cout << "Inciar Sesion" << endl;
		gotoxy(31, 12); cout << "limite alcanzado" << endl;
		gotoxy(25, 22);  system("pause");
		listo = true;
		gotoxy(3,50); return 0;
	}
	if (conectar) {
		menu();
	}
	else {
		cout << "Error en la Conexion..." << endl;
	}



	
   return 0; 
}

void ingresar_productos() {

	string nombre_producto;
	string cero = "0";
	string tipo_medida, tipo_medida2; 
	int opc; 
	double conver,mas_conver,existente2; 
	int existencia = 1; 

	dibujarCuadro(0, 0, 78, 24);
	dibujarCuadro(1, 1, 77, 3);
	gotoxy(26, 2); cout << "'Insertando un Producto'" << endl << endl;

	gotoxy(3, 8);  cout << "Presionar la tecla 0 para volver al menu de inicio. ";
	gotoxy(3,10); cout << "Ingrese Nuevo Ingrediente: "; cin.ignore();
	getline(cin, nombre_producto);

	if (nombre_producto != cero) {

		gotoxy(3, 12); cout << "Ingrese la cantidad del producto:  "; cin >> cantidad_existente; cout << endl;
		
		if (cantidad_existente > 0) {

		gotoxy(3, 14); cout << "1. Kg" << endl;
		gotoxy(3, 15); cout << "2. g" << endl;
		gotoxy(3, 16); cout << "3. L" << endl;
		gotoxy(3, 17); cout << "4. ml" << endl;
		gotoxy(3, 18); cout << "5. volver al menu" << endl;

		gotoxy(3,20); cout << "Ingrese el Tipo de Medida Del producto: "; cin >> opc;

			if (opc == 1) {
				tipo_medida = "Kg", tipo_medida2 = "g";

				conver = cantidad_existente * 1000; 

			}
			else if(opc == 2){ //g
				tipo_medida2 = "g", tipo_medida = "kg"; 

				existente2 = cantidad_existente;
				conver = existente2 / 1000;
				cantidad_existente = conver; 
				conver = existente2; 
				
				

			}
			else if (opc == 3) {

				tipo_medida = "L", tipo_medida2 = "ml";
				 
				conver = cantidad_existente * 1000;


				
			}
			else if (opc == 4) {
				tipo_medida2 = "ml", tipo_medida = "L"; 
				
				existente2 = cantidad_existente;
				conver = existente2 / 1000;
				cantidad_existente = conver;
				conver = existente2;

			}
			else if (opc == 5) {
				menu(); 
			}
			else {
				gotoxy(25,15);  cout << "Ingreso una opcion invalida.";
				gotoxy(23,17);  system("puase");
			}

			//                           nombre de la tabla (nombre de la columna)
			
			string insert = "insert into ingredientes(nombre_producto, cantidad_existente, medida_1, conver, medida_2, existe) values('" + nombre_producto + "', " + to_string(cantidad_existente) + ", '" + tipo_medida + "', " + to_string(conver) + ", '" + tipo_medida2 + "', " + to_string(existencia) + ")";
			const char* i = insert.c_str();
			q_estado = mysql_query(conectar, i);
			if (!q_estado) {
				gotoxy(30, 22); cout << "Ingreso exitoso..." << endl;

			}
			else {
				gotoxy(3, 18); cout << "\nError al intentar ingresar nuevo producto." << mysql_error(conectar) << endl;

			}




		}
		else {
			gotoxy(23, 15); cout << "No Puedes Ingresar un Numero Negativo."; //getch();

		}
		gotoxy(23, 23); system("pause");



	}
	else {
		gotoxy(25, 20); system("pause");
		menu(); 
	}

	
}

void eliminar_productos() {

	
	int existe = 1; 
	gotoxy(26, 2); cout << "Eliminando un Producto";
	dibujarCuadro(0, 0, 78, 24);
	dibujarCuadro(1, 1, 77, 3);

	gotoxy(3, 8);  cout << "Presionar la tecla 0 para volver al menu de inicio. ";
	gotoxy(3, 10); cout << "Ingrese la ID del producto que desee eliminar: "; cin >> id_productos;


	// Verificar si la ID existe en la base de datos

	string consulta = "SELECT * FROM ingredientes WHERE id_productos = " + to_string(id_productos);
	const char* c = consulta.c_str();
	q_estado = mysql_query(conectar, c);
	if (!q_estado) {
		resultado = mysql_store_result(conectar);
		if (mysql_num_rows(resultado) == 0) {
			gotoxy(18,16); cout << "La ID ingresada no existe en la base de datos." << endl;
			gotoxy(23, 17);  system("pause");
			mysql_free_result(resultado);
			menu();
			
		}
		mysql_free_result(resultado);
	}
	else {
		cout << "\n\tError al verificar la existencia de la ID." << mysql_error(conectar);
		menu();
	
	}

	if (id_productos != 0) {
		if (existe == 1) {
			string eliminar = "UPDATE ingredientes SET existe = " + to_string(0) + " WHERE id_productos = " + to_string(id_productos);
			const char* e = eliminar.c_str();
			q_estado = mysql_query(conectar, e);


			if (!q_estado) {
				gotoxy(30, 15); cout << "Eliminacion exitosa...";
				gotoxy(23, 17); system("pause");
				
			}
			else {
				cout << "\nError al intentar eliminar el producto." << mysql_error(conectar) << endl;
				gotoxy(23, 17); system("pause");
				
			}
		}
		else {
			gotoxy(25, 15); cout << "Ese Producto ya fue eliminado.";
			gotoxy(23, 17); system("pause");
		
			menu();
		}
		

	}
	else {
		gotoxy(23, 17); system("pause");
		gotoxy(23, 18); system("pause");
		menu(); 
	}

	


}

void mostrar_productos() {
	
	char nombre(50); 
	
	
	dibujarCuadro(0, 0, 160, 100);
	dibujarCuadro(1, 1, 159, 3);
	gotoxy(67, 2); cout << "'Productos  Almacen'" << endl << endl;
	string consulta = "select * from ingredientes WHERE	existe = 1"; 
	const char* c = consulta.c_str(); 
	q_estado = mysql_query(conectar, c); 
	if (!q_estado) {
		
		resultado = mysql_store_result(conectar); 


		if (mysql_num_rows(resultado) == 0) {
			system("cls");
			
			dibujarCuadro(0, 0, 78, 24);
			dibujarCuadro(1, 1, 77, 3);

			gotoxy(28,2); cout << "No Hay productos Disponibles." << endl;
			gotoxy(25, 22); system("pause"); 
		}
		else {
			while (fila = mysql_fetch_row(resultado)) {
				 
				if (strlen(fila[1]) <= 7) {
					//system("mode con: cols=120 lines=30 ");
					cout << "\n\n\tID del Producto\t\tNombre Del Producto\tCantidad existente\tMedida Del Producto\tCantidad existente\tMedida Del Producto" << endl << endl;
					cout << "\t\t" << fila[0] << "\t\t\t" << fila[1] << "\t\t\t" << fila[2] << "\t\t\t" << fila[3] << "\t\t\t" << fila[4] << "\t\t\t" << fila[5] << endl << endl;

				}
				else if (strlen(fila[1]) == 7 || strlen(fila[1]) < 8) {
					//system("mode con: cols=120 lines=30 ");
					cout << "\n\n\tID del Producto\t\tNombre Del Producto\tCantidad existente\tMedida Del Producto\tCantidad existente\tMedida Del Producto" << endl << endl;
					cout << "\t\t" << fila[0] << "\t\t\t" << fila[1] << "\t\t" << fila[2] << "\t\t\t" << fila[3] << "\t\t\t" << fila[4] << "\t\t\t" << fila[5] << endl << endl;
				}
				else if (strlen(fila[1]) == 8 || strlen(fila[1]) <= 9) {
					//system("mode con: cols=120 lines=30 ");
					cout << "\n\n\tID del Producto\t\tNombre Del Producto\tCantidad existente\tMedida Del Producto\tCantidad existente\tMedida Del Producto" << endl << endl;
					cout << "\t\t" << fila[0] << "\t\t\t" << fila[1] << "\t\t" << fila[2] << "\t\t\t" << fila[3] << "\t\t\t" << fila[4] << "\t\t\t" << fila[5] << endl << endl;
				}
				else if (strlen(fila[1]) == 10 || strlen(fila[1]) <= 24) {
					//system("mode con: cols=120 lines=30 ");
					cout << "\n\n\tID del Producto\t\tNombre Del Producto\tCantidad existente\tMedida Del Producto\tCantidad existente\tMedida Del Producto" << endl << endl;
					cout << "\t\t" << fila[0] <<"\t\t"<< fila[1] << "\t\t\t" << fila[2] << "\t\t\t" << fila[3] << "\t\t\t" << fila[4] << "\t\t\t" << fila[5] << endl << endl;
				}
				else {
					//system("mode con: cols=120 lines=30 ");
					cout << "\n\n\tID del Producto\t\tNombre Del producto\tCantidad existente\tMedida Del Producto\tCantidad existente\tMedida Del Producto" << endl << endl;
					cout << "\t\t" << fila[0] << "\t\t\t" << fila[1] << "\t\t\t" << fila[2] << "\t\t\t" << fila[3] << "\t\t\t" << fila[4] << "\t\t\t" << fila[5] << endl << endl;
				}


			}
			gotoxy(66, 98); system("pause");//
		}
		
	}
	else {
		cout << "\nError en la consulta."; 
	}

}


void eliminar_basecompleta() {



	gotoxy(29, 8); cout << "Ingrese la contraseña actual: ";
	cin.ignore();
	getline(cin, contrasena_actual);



	string borrar = " delete from ingredientes";
	const char* d = borrar.c_str();
	q_estado = mysql_query(conectar, d);

	if (!q_estado) {
		resultado = mysql_store_result(conectar);
		if (fila = mysql_fetch_row(resultado)) {
			if (contrasena_actual == fila[0]) {



				fila = mysql_fetch_row(resultado);



				cout << "\n\tSe ha Borrado la base de Datos con exito.";
				system("pause");
			}



		}
	}
	else {
		cout << "\n\tError.";
	}
}

//APARCIENCIA 
void gotoxy(int x, int y) {
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}



void dibujarCuadro(int x1, int y1, int x2, int y2) {
	int i;

	for (i = x1; i < x2; i++) {
		gotoxy(i, y1); cout << "\304"; //linea horizontal superior
		gotoxy(i, y2); cout << "\304"; //linea horizontal inferior
	}

	for (i = y1; i < y2; i++) {
		gotoxy(x1, i); cout << "\263"; //linea vertical izquierda
		gotoxy(x2, i); cout << "\263"; //linea vertical derecha
	}

	gotoxy(x1, y1); cout << "\332";
	gotoxy(x1, y2); cout << "\300";
	gotoxy(x2, y1); cout << "\277";
	gotoxy(x2, y2); cout << "\331";
}

void confi() {

	dibujarCuadro(0, 0, 78, 24);
	dibujarCuadro(1, 1, 77, 3);
	gotoxy(33, 2); cout << "'Configuracion'" << endl << endl;


	cout << "\n\t1. Cambiar nombre de usuario. "<<endl;
	cout << "\n\t2. Cambiar contraseña." << endl; 
	cout << "\n\t3. Mostrar Productos eliminados." << endl;
	cout << "\n\t4. Recuperar Productos eliminados." << endl;
	//cout << "\t100. Borrar todos los Registros de la Base de Datos."<<endl;
	cout << "\n\t5. volver."<<endl; 
	cout << "\n\tIngrese la opcion que desea ejecutar: "; cin >> opc;

	switch (opc)
	{

	case 1: system("cls"); nuevo_usuario(); break;


	case 2: system("cls"); nuevo_contra();  break;
	
	
	case 3: system("cls"); mostrar_productosE(); break;

	case 4:  system("cls"); recuperar_producto(); break;
	
	case 100:  system("cls"); 
		     eliminar_basecompleta(); break;
	case 5:  menu();  break;
	default: break;
	}



}
void actualizar() {
	
	gotoxy(26, 2); cout << "Actualizando Datos";
	dibujarCuadro(0, 0, 78, 24);
	dibujarCuadro(1, 1, 77, 3);


	cout << "\n\n\t1. Actualizar Nombre del producto. " << endl; 
	cout << "\n\t2. Actulizar Cantidad Existente del producto." << endl; 
	cout << "\n\t3.Volver." << endl; 
	cout << "\n\tIngrese una opcion: "; cin >> opc; 


	switch (opc) {
	case 1: actualizarNombre(); 

		break;

	case 2: system("cls"); actualizarCantidad();
		break; 

	case 3: menu(); break;

	default: cout << "Esa opcion no es valida. ";  break;

	}



}
void actualizarNombre() {

	int id_productos;
	string nuevo_nombre;

	cout << "\n\tIgrese la ID del producto que desee Actualizar: "; cin >> id_productos;
	


	// Verificar si la ID existe en la base de datos
	string consulta = "SELECT * FROM ingredientes WHERE id_productos = " + to_string(id_productos) + " AND existe = 1";
	const char* c = consulta.c_str();
	q_estado = mysql_query(conectar, c);
	if (!q_estado) {
		resultado = mysql_store_result(conectar);
		if (mysql_num_rows(resultado) == 0) {
			gotoxy(18, 16); cout << "La ID ingresada no existe en la base de datos." << endl;
			gotoxy(23, 17);  system("pause");
			mysql_free_result(resultado);
			menu();

		}
		mysql_free_result(resultado);
	}
	else {
		cout << "\n\tError al verificar la existencia de la ID." << mysql_error(conectar);
		menu();

	}

	
	cout << "\n\tIngrese el nuevo Nombre del Producto: "; cin.ignore();  getline(cin, nuevo_nombre); cout << endl;
    
	

	string actulizar = "UPDATE ingredientes SET nombre_producto = '" + nuevo_nombre + "' WHERE id_productos = " + to_string(id_productos);
	const char* cons = actulizar.c_str();
	q_estado = mysql_query(conectar, cons);
	if (!q_estado) {
		gotoxy(23, 15);  cout << "Actualizacion exitosa.";
		gotoxy(23, 17);  system("pause"); 
	}
	else {
		cout << "\n\tError." << mysql_error(conectar);
	}
	

	gotoxy(23, 17);  system("pause");
}


void actualizarCantidad() {

	int id_productos;
	double nueva_cantidad_existente;
	string tipo_medida, tipo_medida2;
	double conver, mas_conver, existente2;

	gotoxy(26, 2); cout << "Actualizando Datos";
	dibujarCuadro(0, 0, 78, 24);
	dibujarCuadro(1, 1, 77, 3);

	gotoxy(3, 6); cout << "Ingrese la ID del Producto que desea actualizar: "; cin >> id_productos;


	// Verificar si la ID existe en la base de datos
	string consulta = "SELECT * FROM ingredientes WHERE id_productos = " + to_string(id_productos) + " AND existe = 1";
	const char* c = consulta.c_str();
	q_estado = mysql_query(conectar, c);
	if (!q_estado) {
		resultado = mysql_store_result(conectar);
		if (mysql_num_rows(resultado) == 0) {
			gotoxy(18, 16); cout << "La ID ingresada no existe en la base de datos." << endl;
			gotoxy(23, 17);  system("pause");
			mysql_free_result(resultado);
			menu();

		}
		mysql_free_result(resultado);
	}
	else {
		cout << "\n\tError al verificar la existencia de la ID." << mysql_error(conectar);
		menu();

	}

	gotoxy(3, 10);  cout << "Presionar la tecla 0 para volver al menu de inicio. ";
	gotoxy(3, 12); cout << "Ingrese la nueva cantidad: "; cin >> nueva_cantidad_existente;

	if (nueva_cantidad_existente != 0) {

		


		gotoxy(3, 14); cout << "1. Kg" << endl;
		gotoxy(3, 15); cout << "2. g" << endl;
		gotoxy(3, 16); cout << "3. l" << endl;
		gotoxy(3, 17); cout << "4. ml" << endl;
		gotoxy(3, 18); cout << "5. volver al menu" << endl;

		gotoxy(3, 20); cout << "Ingrese el Tipo de Medida Del producto: "; cin >> opc;

		if (nueva_cantidad_existente > 0) {


			if (opc == 1) {

				tipo_medida = "Kg", tipo_medida2 = "g";

				conver = nueva_cantidad_existente * 1000;

				string nueva_cantidad = "UPDATE ingredientes SET cantidad_existente = '" + to_string(nueva_cantidad_existente) + "', medida_1 = '" + tipo_medida + "', conver = '" + to_string(conver) + "', medida_2 = '" + tipo_medida2 + "' WHERE id_productos = " + to_string(id_productos);
				const char* n = nueva_cantidad.c_str();
				q_estado = mysql_query(conectar, n);


			}
			else if (opc == 2) { //g
				tipo_medida2 = "g", tipo_medida = "kg";

				existente2 = nueva_cantidad_existente;
				conver = existente2 / 1000;
				nueva_cantidad_existente = conver;
				conver = existente2;

				string nueva_cantidad = "UPDATE ingredientes SET cantidad_existente = '" + to_string(nueva_cantidad_existente) + "', medida_1 = '" + tipo_medida + "', conver = '" + to_string(conver) + "', medida_2 = '" + tipo_medida2 + "' WHERE id_productos = " + to_string(id_productos);
				const char* n = nueva_cantidad.c_str();

				q_estado = mysql_query(conectar, n);

			}
			else if (opc == 3) {

				tipo_medida = "L", tipo_medida2 = "ml";

				conver = nueva_cantidad_existente * 1000;

				string nueva_cantidad = "UPDATE ingredientes SET cantidad_existente = '" + to_string(nueva_cantidad_existente) + "', medida_1 = '" + tipo_medida + "', conver = '" + to_string(conver) + "', medida_2 = '" + tipo_medida2 + "' WHERE id_productos = " + to_string(id_productos);
				const char* n = nueva_cantidad.c_str();

				q_estado = mysql_query(conectar, n);
			}
			else if (opc == 4) {
				tipo_medida2 = "ml", tipo_medida = "L";

				existente2 = nueva_cantidad_existente;
				conver = existente2 / 1000;
				nueva_cantidad_existente = conver;
				conver = existente2;
				string nueva_cantidad = "UPDATE ingredientes SET cantidad_existente = '" + to_string(nueva_cantidad_existente) + "', medida_1 = '" + tipo_medida + "', conver = '" + to_string(conver) + "', medida_2 = '" + tipo_medida2 + "' WHERE id_productos = " + to_string(id_productos);
				const char* n = nueva_cantidad.c_str();

				q_estado = mysql_query(conectar, n);

			}
			else if (opc == 5) {
				menu();
			}
			else {
				gotoxy(25, 22);  cout << "Ingreso una opcion invalida.";
				gotoxy(23, 23);  system("pause");
			}
			

			if (!q_estado) {
				gotoxy(25, 22);  cout << "Actualizacion exitosa.";
				gotoxy(23, 23);  system("pause");
			}
			else {
				cout << "\n\tError." << mysql_error(conectar);
			}
		}
		else {
			gotoxy(17, 22); cout << "Error. No puedes ingresar un numero negativo";
			gotoxy(17, 23); system("pause"); 
		}
	}
}


void anadir_cantidad() {
	
	gotoxy(26, 2); cout << "Ingresando Producto";//*
	dibujarCuadro(0, 0, 78, 24);
	dibujarCuadro(1, 1, 77, 3);
	
	gotoxy(3, 8);  cout << "Presionar la tecla 0 para volver al menu de inicio. "; 
    gotoxy(3, 10); cout << "Ingrese la ID del Producto: "; cin >> id_productos;

	bool listo = false; 
	double mas_conver;
	string tipo_medida, tipo_medida2; 
	int opc; 


	// Verificar si la ID existe en la base de datos
	string consulta = "SELECT * FROM ingredientes WHERE id_productos = " + to_string(id_productos) + " AND existe = 1";
	const char* c = consulta.c_str();
	q_estado = mysql_query(conectar, c);
	if (!q_estado) {
		resultado = mysql_store_result(conectar);
		if (mysql_num_rows(resultado) == 0) {
			gotoxy(18, 16); cout << "La ID ingresada no existe en la base de datos." << endl;
			gotoxy(23, 17);  system("pause");
			mysql_free_result(resultado);
			menu();

		}
		mysql_free_result(resultado);
	}
	else {
		cout << "\n\tError al verificar la existencia de la ID." << mysql_error(conectar);
		menu();

	}



	       gotoxy(3, 12); cout << "Ingrese la Cantidad a añadir al producto: "; cin >> mas_cantidad;

		   
	
		   gotoxy(3, 14); cout << "1. Kg" << endl;
		   gotoxy(3, 15); cout << "2. g" << endl;
		   gotoxy(3, 16); cout << "3. l" << endl;
		   gotoxy(3, 17); cout << "4. ml" << endl;
		   gotoxy(3, 18); cout << "5. volver al menu" << endl;

		   gotoxy(3, 20); cout << "Ingrese el Tipo de Medida Del producto: "; cin >> opc;
		   
		   if (mas_cantidad > 0 || id_productos != 0) {
		
			   if (opc == 1) {
				   tipo_medida = "Kg", tipo_medida2 = "g";
				   
				   mas_conver = mas_cantidad  * 1000;




			   }
			   else if (opc == 2) {
				  
				   tipo_medida2 = "g",  tipo_medida = "Kg";

				   conver = mas_cantidad;
				   mas_conver = conver / 1000;
				   mas_cantidad = mas_conver;
				   mas_conver = conver;

				  
				  

			   }
			   else if (opc == 3) {

				   tipo_medida = "L", tipo_medida2 = "ml";
				   mas_conver = mas_cantidad * 1000;

				   

			   }
			   else if (opc == 4) {
				   tipo_medida2 = "ml",tipo_medida = "L";
				  
				   conver = mas_cantidad;
				   mas_conver = conver / 1000;
				   mas_cantidad = mas_conver;
				   mas_conver = conver;

			   }
			   else if (opc == 5) {
				   menu();
			   }
			   else {
				   gotoxy(25, 15);  cout << "Ingreso una opcion invalida.";
				   gotoxy(23, 17);  cout << "726";	system("puase");
				   menu(); 
			   }
			
			system("cls");   gotoxy(26, 2); cout << "Ingresando Producto";

			dibujarCuadro(0, 0, 78, 24);
			dibujarCuadro(1, 1, 77, 3);
			if (mas_cantidad == 0 || mas_cantidad > 0) {
				listo = true;

				string mas = "UPDATE ingredientes SET cantidad_existente = cantidad_existente + '" + to_string(mas_cantidad) + "', medida_1 = '" + tipo_medida + "', conver = conver + '" + to_string(mas_conver) +"', medida_2 = '" + tipo_medida2 + "'WHERE id_productos = " + to_string(id_productos);
				const char* m = mas.c_str();    
				q_estado = mysql_query(conectar, m);
				if (!q_estado) {
					gotoxy(29, 20); cout << "Actualizacion exitosa.";
                    gotoxy(23, 22); system("pause");

				}

				cout << existente2 << " " << mas_cantidad << " " << mas_conver; 
				
				menu();
			}
			else if (mas_cantidad >= 0) { // Agregar esta condición

				string mas = "UPDATE ingredientes SET cantidad_existente = cantidad_existente + '" + to_string(mas_cantidad) + "'WHERE id_productos = " + to_string(id_productos);
				const char* m = mas.c_str();    q_estado = mysql_query(conectar, m);
				if (!q_estado) {
					cout << "\n\tActualizacion exitosa.";
				}
				else {
					cout << "\n\tError." << mysql_error(conectar);
				}

			}
			else {
				//gotoxy(3, 9);  cout << "Presionar la tecla 0 para volver al menu de inicio o ";   
				//gotoxy(3, 10); cout << "Por favor ingrese un numero mayor a cero (0) para continuar ";
				gotoxy(17, 20); cout << "Error. No puedes ingresar un numero negativo";
			}
		//while

	}
	else {
			   gotoxy(23, 22); cout << "774"; system("pause");
		menu();
	}
	
		   gotoxy(23, 22); cout << "774"; system("pause");
	
	}


	


void extraer_cantidad() {

	double menos_conver;
	string tipo_medida, tipo_medida2;
	double menos_cantidad2; 

	gotoxy(26, 2); cout << "Extrayendo Producto";
	dibujarCuadro(0, 0, 78, 24);
	dibujarCuadro(1, 1, 77, 3);

	gotoxy(3, 8);  cout << "Presionar la tecla 0 para volver al menu de inicio. ";
	gotoxy(3, 10); cout << "Ingrese la ID del Producto: "; cin >> id_productos;
	


	// Verificar si la ID existe en la base de datos
	string consulta = "SELECT * FROM ingredientes WHERE id_productos = " + to_string(id_productos) + " AND existe = 1"; 
	const char* c = consulta.c_str();
	q_estado = mysql_query(conectar, c);
	if (!q_estado) {
		resultado = mysql_store_result(conectar);
		if (mysql_num_rows(resultado) == 0) {
			gotoxy(18, 16); cout << "La ID ingresada no existe en la base de datos." << endl;
			gotoxy(23, 17);  system("pause");
			mysql_free_result(resultado);
			menu();

		}
		mysql_free_result(resultado);
	}
	else {
		cout << "\n\tError al verificar la existencia de la ID." << mysql_error(conectar);
		menu();

	}
	
	if (id_productos != 0) {

	string consulta = "SELECT cantidad_existente, conver FROM ingredientes WHERE id_productos = " + to_string(id_productos);
    const char* c = consulta.c_str();
    q_estado = mysql_query(conectar, c);

    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        if (fila = mysql_fetch_row(resultado)) {
            cantidad_existente = stoi(fila[0]); // Convertir el valor obtenido a entero
        }
        mysql_free_result(resultado);
    } else {
        cout << "\n\tError al obtener la cantidad existente del producto." << mysql_error(conectar);
    }


	gotoxy(3, 14); cout << "1. Kg" << endl; 
	gotoxy(3, 15); cout << "2. g" << endl; 
	gotoxy(3, 16); cout << "3. l" << endl; 
	gotoxy(3, 17); cout << "4. ml" << endl; 
	gotoxy(3, 18); cout << "5. volver al menu" << endl; 

	gotoxy(3, 20); cout << "Ingrese el Tipo de Medida Del producto: "; cin >> opc; 
	
	if (opc == 2 || opc == 4) {

		gotoxy(3, 12); cout << "Ingrese la Cantidad a extraer al producto: "; cin >> menos_cantidad2;

	}
	else {
		gotoxy(3, 12); cout << "Ingrese la Cantidad a extraer al producto: "; cin >> menos_cantidad;


	}
	
	
		if (menos_cantidad > 0 || menos_cantidad2 > 0 ) {
		
			

			if (cantidad_existente > menos_cantidad || cantidad_existente == menos_cantidad || conver > menos_cantidad || conver > menos_cantidad2 || menos_cantidad2 == conver ) {
				
				if (opc == 1) {

					tipo_medida = "Kg", tipo_medida2 = "g";

					menos_conver = menos_cantidad * 1000;
					
					string mas = "UPDATE ingredientes SET cantidad_existente = cantidad_existente - '" + to_string(menos_cantidad) + "', medida_1 = '" + tipo_medida + "', conver = conver - '" + to_string(menos_conver) + "', medida_2 = '" + tipo_medida2 + "'WHERE id_productos = " + to_string(id_productos);
					const char* m = mas.c_str();
					q_estado = mysql_query(conectar, m);

				}
				else if (opc == 2) {

					tipo_medida2 = "g", tipo_medida = "Kg";

					conver = menos_cantidad2;
					menos_conver = conver / 1000;
					menos_cantidad2 = menos_conver;
					menos_conver = conver;

					string mas = "UPDATE ingredientes SET cantidad_existente = cantidad_existente - '" + to_string(menos_cantidad2) + "', medida_1 = '" + tipo_medida + "', conver = conver - '" + to_string(menos_conver) + "', medida_2 = '" + tipo_medida2 + "'WHERE id_productos = " + to_string(id_productos); 
					const char* m = mas.c_str();
					q_estado = mysql_query(conectar, m);
				}
				else if (opc == 3) {

					tipo_medida = "L", tipo_medida2 = "ml";
					menos_conver = menos_cantidad * 1000;

					string mas = "UPDATE ingredientes SET cantidad_existente = cantidad_existente - '" + to_string(menos_cantidad) + "', medida_1 = '" + tipo_medida + "', conver = conver - '" + to_string(menos_conver) + "', medida_2 = '" + tipo_medida2 + "'WHERE id_productos = " + to_string(id_productos);
					const char* m = mas.c_str();
					q_estado = mysql_query(conectar, m);
				}
				else if (opc == 4) {
					tipo_medida2 = "ml", tipo_medida = "L";

					conver = menos_cantidad2;
					menos_conver = conver / 1000;
					menos_cantidad2 = menos_conver;
					menos_conver = conver;

					string mas = "UPDATE ingredientes SET cantidad_existente = cantidad_existente - '" + to_string(menos_conver) + "', medida_1 = '" + tipo_medida + "', conver = conver - '" + to_string(menos_cantidad2) + "', medida_2 = '" + tipo_medida2 + "'WHERE id_productos = " + to_string(id_productos);
					const char* m = mas.c_str();
					q_estado = mysql_query(conectar, m);
				}
				else if (opc == 5) {
					menu();
				}
				else {
					gotoxy(25, 15);  cout << "Ingreso una opcion invalida.";
					gotoxy(23, 17);  	system("puase");
					menu();
				}

			
			
			

			if (!q_estado) {
				gotoxy(27, 21); cout << "Actualizacion exitosa.";
			}
			else {
				cout << "\n\tError." << mysql_error(conectar);
			}

			}
			else {
				gotoxy(3, 22); cout << "La cantidad a extraer es mayor a la cantidad existente del producto"; 
			}


		}
		else {
			gotoxy(17, 20); cout << "Error. No puedes ingresar un numero negativo";
		}

	}
	else {
		menu(); 
	}
	
		


	gotoxy(23, 23); system("pause");
}


void entrar_al_programa() {

	
	
	bool ingresar = false;
	int contador = 0;



	do {
		
		gotoxy(33, 2); cout << "Inciar Sesion"<<endl;
		gotoxy(29,10); cout << "Usuario: "; getline(cin, user); cout << endl;
		gotoxy(29,11); cout << "Contrasena: ";//etline(cin, contra); cout<<endl; 

		char caracter;
		caracter = _getch();
		while (caracter != 13) {
			if (caracter != 8) {
				contra.push_back(caracter);
				cout << "*";


			}
			else {
				if (contra.length() > 0) {
					cout << "\b \b";
					contra = contra.substr(0, contra.length() - 1);
				}
			}
			caracter = _getch();

		}

		string login = "SELECT* FROM login WHERE usuario = '" + user + "' AND contraseña = '" + contra + "'";
		const char* l = login.c_str(); 
		int q_estado = mysql_query(conectar, l); 

		if (!q_estado){//MODIFICAR
			MYSQL_RES* res = mysql_store_result(conectar);
			int row = mysql_num_rows(res);    //ingresar = true;

			if (row == 1) {
				ingresar = true;
			}else {
			gotoxy(23, 15); cout << "Usuario y/o contraseña son incorrectos";
			cin.get();
			system("cls"); 
			dibujarCuadro(0, 0, 78, 24);
			dibujarCuadro(1, 1, 77, 3);
			contador++;
		}


		}
		
		contra = "";
	
	} while (!ingresar && contador < 3);//aqui

	if (!ingresar) {
		gotoxy(33, 2); cout << "Inciar Sesion" << endl;
		gotoxy(31, 12); cout << "limite alcanzado" << endl;
		gotoxy(25, 22);  system("pause");
		listo = true; 
		 
	}
	
}


void nuevo_usuario() {

	 
	gotoxy(30, 2); cout << "Configuracion";
	dibujarCuadro(0, 0, 78, 24);
	dibujarCuadro(1, 1, 77, 3);
	int id = 1;
	string contrasena_actual;

	gotoxy(3, 8); cout << "Ingrese la contraseña actual: ";
	cin.ignore();
	getline(cin, contrasena_actual);


	string consulta = "SELECT contraseña FROM login WHERE id = " + to_string(id);
	const char* c = consulta.c_str();
	q_estado = mysql_query(conectar, c);

	if (!q_estado) {
		resultado = mysql_store_result(conectar);
		if (fila = mysql_fetch_row(resultado)) {
		

				if (contrasena_actual == fila[0]) {  
					gotoxy(3, 10); cout << "Ingrese el nuevo Nombre del Usuario: "; cin >> new_usuario; cout << endl;
					string actualizar = "UPDATE login SET usuario = '" + new_usuario + "' WHERE id = " + to_string(id);
					const char* a = actualizar.c_str();
					q_estado = mysql_query(conectar, a);
					if (!q_estado) {
						gotoxy(29, 20); cout << "Actualizacion Exitosa.";
						gotoxy(23, 22); system("pause");
						usuario = new_usuario;
						
						system("cls");
					}
					else {
						cout << "\n\tError al actualizar el usuario." << mysql_error(conectar);
						gotoxy(25, 22);   system("pause");
					}
				}
				else {
					gotoxy(25, 20); cout << "La contraseñaa ingresada es incorrecta.";
					gotoxy(25, 22);  system("pause");
				
				}





			
		}
		mysql_free_result(resultado);
	}
	else {
		gotoxy(20,20); cout << "Error al obtener la contrasena actual.";
		gotoxy(23, 22); cout << "1096."; system("pause");
		menu();

	
		
	}

	
	menu();
}



	



void nuevo_contra() {
	gotoxy(30, 2); cout << "Configuracion";
	dibujarCuadro(0, 0, 78, 24);
	dibujarCuadro(1, 1, 77, 3);
	int id = 1;

	gotoxy(3, 8); cout << "Ingrese la contraseña actual: ";
	cin.ignore();
	getline(cin, contrasena_actual);

	// Verificar si la contraseña actual ingresada coincide con la almacenada en la base de datos
	string consulta = "SELECT contraseña FROM login WHERE id = " + to_string(id);
	const char* p = consulta.c_str();
	q_estado = mysql_query(conectar, p);

	if (!q_estado) {
		resultado = mysql_store_result(conectar);
		if (fila = mysql_fetch_row(resultado)) {
			if (contrasena_actual == fila[0]) {
				// La contraseña actual es correcta, solicitar la nueva contraseña
				
				cin.ignore();
				gotoxy(3, 10); cout << "Ingrese la nueva contraseña: ";
				//flushall(); // Limpiar el búfer de entrada
				
				getline(cin, new_contra);

				// Verificar si las contraseñas coinciden
                cin.ignore();
				gotoxy(3, 12); cout << "Verifique la nueva contraseña: ";
				//flushall(); // Limpiar el búfer de entrada
				
				getline(cin, verificacion_contra);
                 
				if (new_contra == verificacion_contra) {
					// Las contraseñas coinciden, actualizar la contraseña en la base de datos
					string actualizar = "UPDATE login SET contraseña = '" + new_contra + "' WHERE id = " + to_string(id);
					const char* a = actualizar.c_str();
					q_estado = mysql_query(conectar, a);
					if (!q_estado) {
						gotoxy(28, 20); cout << "Actualizacion exitosa.";
						gotoxy(23, 22); system("pause");
					}
					else {
						gotoxy(27, 14); cout << "Error al actualizar la contraseña: ";
						gotoxy(23, 22); system("pause");
					}
				}
				else {
					gotoxy(19, 20); cout << "Las contraseñas no coinciden. Intentelo de nuevo.";
					gotoxy(23, 22); system("pause");
				}
			}
			else {
				gotoxy(21, 17); cout << "La contraseña actual es incorrecta.";
				gotoxy(23,20); system("pause");
			}
		}
	}
	else {
		gotoxy(29, 5); cout << "Error al consultar la contraseña actual: ";
	}
	menu();
}

void menu() {
		//system("mode con: cols=80 lines=25 "); 

		dibujarCuadro(0, 0, 78, 24);
		dibujarCuadro(1, 1, 77, 3);
		listo = false;

		while (!listo) {
			//gotoxy(22,20); system("pause");
			system("cls");

			dibujarCuadro(0, 0, 78, 24);
			dibujarCuadro(1, 1, 77, 3);
			gotoxy(33, 2); cout << "'Bienvenido'" << endl << endl;

			



				cout << "\n\t1. Ingresar Un Nuevo Producto." << endl;;
				cout << "\n\t2. Eliminar Un Producto." << endl;
				cout << "\n\t3. Ingresar Producto al Inventario." << endl; //aqui
				cout << "\n\t4. Extraer Producto del Inventario. " << endl; //aqui
				cout << "\n\t5. Mostrar Todos los Productos." << endl;
				cout << "\n\t6. Actualizar. " << endl;
				cout << "\n\t7. Configuracion." << endl;
				cout << "\n\t8. Salir Del Programa. " << endl;
				cout << "\n\tIngrese la opcion que desea ejecutar: "; cin >> opc; cout << endl;

				switch (opc)
				{
				case 1:system("cls");
					ingresar_productos();

					break;

				case 2: system("cls");
					eliminar_productos();

					break; 

				case 3: system("cls");
					anadir_cantidad();  break;



				case 4:system("cls");
					extraer_cantidad(); break;

				case 5: system("cls");
					mostrar_productos();   break;

				case 6:system("cls");
					actualizar();  break;


				case 7:system("cls");

					confi(); break;



				case 8:listo = true; break;


				default:
					cout << "\nError, Opcion no disponible. "; break;
				}

			


		};

		


		system("cls");
	
	}


void recuperar_producto() {

	int existe = 1;
	gotoxy(26, 2); cout << "Recuperando un Producto";
	dibujarCuadro(0, 0, 78, 24);
	dibujarCuadro(1, 1, 77, 3);

	gotoxy(3, 8);  cout << "Presionar la tecla 0 para volver al menu de inicio. ";
	gotoxy(3, 10); cout << "Ingrese la ID del producto que desee recuperar: "; cin >> id_productos;


	// Verificar si la ID existe en la base de datos

	
	string consulta = "SELECT * FROM ingredientes WHERE id_productos = " + to_string(id_productos);
	const char* c = consulta.c_str();
	q_estado = mysql_query(conectar, c);
	if (!q_estado) {
		resultado = mysql_store_result(conectar);
		if (mysql_num_rows(resultado) == 0) {
			gotoxy(18, 16); cout << "La ID ingresada no existe en la base de datos." << endl;
			gotoxy(23, 17);  system("pause");
			mysql_free_result(resultado);
			menu();

		}
		mysql_free_result(resultado);
	}
	else {
		cout << "\n\tError al verificar la existencia de la ID." << mysql_error(conectar);
		menu();

	}

	if (id_productos != 0) {
		if (existe == 1) {
			string eliminar = "UPDATE ingredientes SET existe = " + to_string(existe) + " WHERE id_productos = " + to_string(id_productos);
			const char* e = eliminar.c_str();
			q_estado = mysql_query(conectar, e);


			if (!q_estado) {
				gotoxy(30, 15); cout << "Recuperacion exitosa...";
				gotoxy(23, 17); system("pause");

			}
			else {
				cout << "\nError al intentar eliminar el producto." << mysql_error(conectar) << endl;
				gotoxy(23, 17); system("pause");

			}
		}
		else {
			gotoxy(25, 15); cout << "Ese Producto ya Existe en la Base Datos.";
			gotoxy(23, 17); system("pause");

			menu();
		}


	}
	else {
		gotoxy(23, 17); system("pause");
		gotoxy(23, 18); system("pause");
		menu();
	}




}
void mostrar_productosE() {

	dibujarCuadro(0, 0, 160, 100);
	dibujarCuadro(1, 1, 159, 3);
	gotoxy(67, 2); cout << "'Productos de Almacen'" << endl << endl;
	string consulta = "select * from ingredientes WHERE	existe = 0";
	const char* c = consulta.c_str();
	q_estado = mysql_query(conectar, c);
	if (!q_estado) {

		resultado = mysql_store_result(conectar);


		if (mysql_num_rows(resultado) == 0) {
			system("cls");

			dibujarCuadro(0, 0, 78, 24);
			dibujarCuadro(1, 1, 77, 3);

			gotoxy(28, 2); cout << "No Hay productos Disponibles." << endl;
			gotoxy(25, 22); system("pause");
		}
		else {
			while (fila = mysql_fetch_row(resultado)) {

				if (strlen(fila[1]) <= 7) {
					//system("mode con: cols=120 lines=30 ");
					cout << "\n\n\tID del Producto\t\tNombre Del Producto\tCantidad existente\tMedida Del Producto\tCantidad existente\tMedida Del Producto" << endl << endl;
					cout << "\t\t" << fila[0] << "\t\t\t" << fila[1] << "\t\t\t" << fila[2] << "\t\t\t" << fila[3] << "\t\t\t" << fila[4] << "\t\t\t" << fila[5] << endl << endl;

				}
				else if (strlen(fila[1]) == 7 || strlen(fila[1]) < 8) {
					//system("mode con: cols=120 lines=30 ");
					cout << "\n\n\tID del Producto\t\tNombre Del Producto\tCantidad existente\tMedida Del Producto\tCantidad existente\tMedida Del Producto" << endl << endl;
					cout << "\t\t" << fila[0] << "\t\t\t" << fila[1] << "\t\t" << fila[2] << "\t\t\t" << fila[3] << "\t\t\t" << fila[4] << "\t\t\t" << fila[5] << endl << endl;
				}
				else if (strlen(fila[1]) == 8 || strlen(fila[1]) <= 9) {
					//system("mode con: cols=120 lines=30 ");
					cout << "\n\n\tID del Producto\t\tNombre Del Producto\tCantidad existente\tMedida Del Producto\tCantidad existente\tMedida Del Producto"<< endl << endl;
					cout << "\t\t" << fila[0] << "\t\t\t" << fila[1] << "\t\t" << fila[2] << "\t\t\t" << fila[3] << "\t\t\t" << fila[4] << "\t\t\t" << fila[5] << endl << endl;
				}
				else if (strlen(fila[1]) == 10 || strlen(fila[1]) <= 24) {
					//system("mode con: cols=120 lines=30 ");
					cout << "\n\n\tID del Producto\t\tNombre Del Producto\tCantidad existente\tMedida Del Producto\tCantidad existente\tMedida Del Producto" << endl << endl;
					cout << "\t\t" << fila[0] << "\t\t" << fila[1] << "\t\t\t" << fila[2] << "\t\t\t" << fila[3] << "\t\t\t" << fila[4] << "\t\t\t" << fila[5] << endl << endl;
				}
				else {
					//system("mode con: cols=120 lines=30 ");
					cout << "\n\n\tID del Producto\t\tNombre Del producto\tCantidad existente\tMedida Del Producto\tCantidad existente\tMedida Del Producto"<< endl << endl;
					cout << "\t\t" << fila[0] << "\t\t\t" << fila[1] << "\t\t\t" << fila[2] << "\t\t\t" << fila[3] << "\t\t\t" << fila[4] << "\t\t\t" << fila[5] << endl << endl;
				}

			}
			gotoxy(66, 98); system("pause");//
		}

	}
	else {
		cout << "\nError en la consulta.";
	}
}
