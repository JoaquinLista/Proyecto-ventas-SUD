#include "includes/Operaciones.h"
#include "includes/Procesamiento.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
using namespace std;


int main() {

    string archivo = "data/ventas_sudamerica.csv";
    vector<Venta> ventas = leer_csv(archivo);

    unordered_map<string, int> indice;    // guardamos el incide de cada


    if (ventas.empty()) {
        cout << "No se pudieron cargar ventas.\n";
    } else {
        cout << "Se cargaron " << ventas.size() << " ventas correctamente.\n";


        for (int i = 0; i < ventas.size(); ++i) {
            indice[ventas[i].id_venta] = i;
        }
    }


    int opcion;
    do {
        opcion = menu();
        switch (opcion) {
            case 1:
                mostrar_ventas(ventas);
            break;
            case 2:
                agregar_ventas(ventas);
            calcular_estadisticas(ventas);
            // reconstruir índice
            indice.clear();
            for (int i = 0; i < ventas.size(); ++i)
                indice[ventas[i].id_venta] = i;
            break;
            case 3:
                cin.ignore();
            eliminar_ventas(ventas, indice);
            calcular_estadisticas(ventas);
            // ya se reconstruye el índice adentro de eliminar_ventas
            break;
            case 4:
                // modificar_ventas(ventas, indice);
                    calcular_estadisticas(ventas);
            break;
            case 5:
            break;
            case 6:
                calcular_estadisticas(ventas);
            break;
        }
    } while (opcion != 0);

}


