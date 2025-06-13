#include "includes/Operaciones.h"
#include <iostream>
#include <fstream>
using namespace std;


int main() {

    string archivo = "data/ventas_sudamerica.csv";
    vector<Venta> ventas = leer_csv(archivo);

    if (ventas.empty()) {
        cout << "No se pudieron cargar ventas.\n";
    } else {
        cout << "Se cargaron " << ventas.size() << " ventas correctamente.\n";
    }


    int opcion;
    do {
         opcion = menu();
        switch (opcion) {
            case 1:
                mostrar_ventas (ventas);
                break;
            case 2:
                agregar_ventas (ventas);
                break;
            case 3:
                //eliminar_ventas
                break;
            case 4:
                modificar_venta(ventas);
                break;
            case 5:
                //estadisticas_ventas
                break;
            case 6:
                //consultas_dinamicas
                break;
        }
    }while (opcion != 0);
    return 0;
}


