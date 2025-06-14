#include "includes/Operaciones.h"
#include "includes/Procesamiento.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <ctime>  // para medir tiempo
using namespace std;

int main() {
    string archivo = "data/ventas_sudamerica.csv";

    clock_t inicio_carga = clock();
    vector<Venta> ventas = leer_csv(archivo);
    clock_t fin_carga = clock();
    double tiempo_carga = static_cast<double>(fin_carga - inicio_carga) / CLOCKS_PER_SEC;
    cout << "Tiempo de carga del archivo: " << tiempo_carga << " segundos.\n";

    unordered_map<string, int> indice;

    if (ventas.empty()) {
        cout << "No se pudieron cargar ventas.\n";
    } else {
        cout << "Se cargaron " << ventas.size() << " ventas correctamente.\n";
        for (int i = 0; i < ventas.size(); ++i)
            indice[ventas[i].id_venta] = i;
    }

    int opcion;
    do {
        opcion = menu();
        clock_t inicio_op = clock(); // comienzo del tiempo de operación

        switch (opcion) {
            case 1:
                mostrar_ventas(ventas);
            calcular_estadisticas(ventas);
                break;
            case 2:
                agregar_ventas(ventas);
                calcular_estadisticas(ventas);
                indice.clear();
                for (int i = 0; i < ventas.size(); ++i)
                    indice[ventas[i].id_venta] = i;
                break;
            case 3:
                cin.ignore();
                eliminar_venta_filtrada(ventas, indice);
                calcular_estadisticas(ventas);
                break;
            case 4:
                modificar_venta(ventas);
                calcular_estadisticas(ventas);
                break;
            case 5:
                calcular_estadisticas(ventas);
                break;
            case 6:
                menu_consultas_dinamicas(ventas);
                calcular_estadisticas(ventas);
                break;
        }

        clock_t fin_op = clock();
        double tiempo_op = static_cast<double>(fin_op - inicio_op) / CLOCKS_PER_SEC;
        if (opcion != 0)
            cout << "Tiempo de operación: " << tiempo_op << " segundos.\n\n";
    } while (opcion != 0);

    return 0;
}
