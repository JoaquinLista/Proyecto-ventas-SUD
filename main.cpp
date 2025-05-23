
#include <iostream>
#include <sstream>
#include <fstream>
#define NOMBRE_ARCHIVO "ProductosExportados_SPOS3.csv"
using namespace std;

void Mostrarmenu () {
  cout << "==============================" << endl;
  cout << "      SISTEMA DE VENTAS       " << endl;
  cout << "==============================" << endl;
  cout << "1. Ver estadísticas de ventas" << endl;
  cout << "2. Modificar un registro" << endl;
  cout << "3. Agregar una nueva venta" << endl;
  cout << "4. Eliminar una venta existente" << endl;
  cout << "5. Consultas avanzadas" << endl;
  cout << "==============================" << endl;
  cout << "Seleccione una opcion (1-5): ";

}



int main(){

  int opcion_menu;

do {

  Mostrarmenu();
  cin >> opcion_menu;
  cin.ignore();

switch (opcion_menu) {

  case 1:
}

}


  switch (opcion_menu) {
    case 1 : ;
  }








  // FUNCION PARA IMPRIMIR EL CSV
ifstream archivo("ventas_sudamerica.csv");
  string linea;
  char delimitador = ',';
  // Leemos la primer línea para descartarla, pues es el encabezado
  getline(archivo, linea);
  // Leemos todas las líneas
  while (getline(archivo, linea))
  {

    stringstream stream(linea); // Convertir la cadena a un stream
    string ID_Venta,Fecha,Pais,Ciudad,Cliente,Producto,Categoria,Cantidad,Precio_Unitario,Monto_Total,Medio_Envio,Estado_Envio;
    // Extraer todos los valores de esa fila
    getline(stream, ID_Venta, delimitador);
    getline(stream, Fecha, delimitador);
    getline(stream, Pais, delimitador);
    getline(stream, Ciudad, delimitador);
    getline(stream, Cliente, delimitador);
    getline(stream, Producto, delimitador);
    getline(stream, Categoria, delimitador);
    getline(stream, Cantidad, delimitador);
    getline(stream, Precio_Unitario, delimitador);
    getline(stream, Monto_Total, delimitador);
    getline(stream, Medio_Envio, delimitador);
    getline(stream, Estado_Envio, delimitador);
    // Imprimir
    cout << "==================" << endl;
    cout << "Id de venta: " << ID_Venta << endl;
    cout << "Fecha: " << Fecha << endl;
    cout << "Pais: " << Pais << endl;
    cout << "Ciudad: " << Ciudad << endl;
    cout << "Cliente: " << Cliente << endl;
    cout << "Producto: " << Producto << endl;
    cout << "Categoria: " << Categoria << endl;
    cout << "Cantidad: " << Cantidad << endl;
    cout << "Precio unitario: $" << Precio_Unitario << endl;
    cout << "Monto total: $" << Monto_Total << endl;
    cout << "Medio de envio: " << Medio_Envio << endl;
    cout << "Estado del envio: " << Estado_Envio << endl;
  }
  archivo.close();
}