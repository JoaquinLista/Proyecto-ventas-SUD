#include "../includes/Operaciones.h"
#include <fstream>
#include <unordered_map>
#include <functional>
#include <sstream>
#include "ArbolVentas.h"
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
using namespace std;

void destruir_arbol(NodoVenta *&raiz) {
    if (!raiz) return;
    destruir_arbol(raiz->izquierda);
    destruir_arbol(raiz->derecha);
    delete raiz;
    raiz = nullptr;
}
bool es_fecha_valida(const string& fecha) {
    regex formato("^\\d{2}/\\d{2}/\\d{4}$");
    return regex_match(fecha, formato);
}

bool contiene_solo_letras_y_espacios(const string& texto) {
    return all_of(texto.begin(), texto.end(), [](char c) {
        return isalpha(c) || isspace(c);
    });
}

bool esTextoValido(const string &input) {
    return regex_match(input, regex("^[A-Za-zÁÉÍÓÚáéíóúÑñ ]+$"));
}

bool esNumeroEntero(const string &input) {
    return regex_match(input, regex("^[0-9]+$"));
}

bool esNumeroDecimal(const string &input) {
    return regex_match(input, regex("^[0-9]+(\\.[0-9]+)?$"));
}


static string reemplazar_coma_por_punto(const string &texto) {
    string resultado = texto;
    replace(resultado.begin(), resultado.end(), ',', '.');
    return resultado;
}

bool buscar_en_indice(const unordered_map<string, int> &indice, const string &id, int &posicion) {
    auto it = indice.find(id);
    if (it != indice.end()) {
        posicion = it->second;
        return true;
    }
    return false;
}

vector<Venta> leer_csv(const string &path) {
    ifstream archivo(path);
    vector<Venta> ventas;
    string linea;

    if (!archivo.is_open()) {
        cerr << "Error: no se pudo abrir el archivo " << path << endl;
        return ventas;
    }

    getline(archivo, linea); // Saltear encabezado

    while (getline(archivo, linea)) {
        stringstream stream(linea);
        Venta v;
        string campo;

        try {
            getline(stream, v.id_venta, ',');
            getline(stream, v.fecha, ',');
            getline(stream, v.pais, ',');
            getline(stream, v.ciudad, ',');
            getline(stream, v.cliente, ',');
            getline(stream, v.producto, ',');
            getline(stream, v.categoria, ',');

            getline(stream, campo, ',');
            v.cantidad = stoi(campo);

            getline(stream, campo, ',');
            v.precio_unitario = stod(reemplazar_coma_por_punto(campo));

            getline(stream, campo, ',');
            v.monto_total = stod(reemplazar_coma_por_punto(campo));

            getline(stream, v.medio_envio, ',');
            getline(stream, v.estado_envio);

            ventas.push_back(v);
        } catch (const exception &e) {
            cerr << "Error al procesar línea:\n" << linea << "\nMotivo: " << e.what() << endl;
        }
    }

    archivo.close();
    return ventas;
}

void mostrar_ventas(const vector<Venta> &ventas, int max_mostrar) {
    if (max_mostrar < 0 || max_mostrar > static_cast<int>(ventas.size())) {
        max_mostrar = ventas.size();
    }

    for (int i = 0; i < max_mostrar; ++i) {
        const Venta &v = ventas[i];
        std::ostringstream oss;

        oss << "==========================\n";
        oss << "ID Venta:        " << v.id_venta << '\n';
        oss << "Fecha:           " << v.fecha << '\n';
        oss << "País:            " << v.pais << '\n';
        oss << "Ciudad:          " << v.ciudad << '\n';
        oss << "Cliente:         " << v.cliente << '\n';
        oss << "Producto:        " << v.producto << '\n';
        oss << "Categoría:       " << v.categoria << '\n';
        oss << "Cantidad:        " << v.cantidad << '\n';
        oss << "Precio Unitario: $" << v.precio_unitario << '\n';
        oss << "Monto Total:     $" << v.monto_total << '\n';
        oss << "Medio de Envío:  " << v.medio_envio << '\n';
        oss << "Estado Envío:    " << v.estado_envio << '\n';

        std::cout << oss.str();
    }
}

void agregar_ventas(vector<Venta> &ventas) {
    Venta nueva;
    string entrada;

    // Verificar ID único
    while (true) {
        cout << "Ingrese el ID de venta: ";
        cin >> nueva.id_venta;
        auto it = find_if(ventas.begin(), ventas.end(), [&](const Venta &v) {
            return v.id_venta == nueva.id_venta;
        });
        if (it != ventas.end()) {
            cout << "Ya existe una venta con ese ID. Intente con otro.\n";
        } else {
            break;
        }
    }

    cout << "Ingrese la fecha de la compra (ej: 2023-12-01): ";
    cin >> nueva.fecha;
    cin.ignore();

    // Ingreso de campos de texto
    auto pedirTexto = [](const string &campo, string &destino) {
        while (true) {
            cout << "Ingrese " << campo << ": ";
            getline(cin, destino);
            if (!esTextoValido(destino)) {
                cout << "Entrada inválida. Use solo letras y espacios.\n";
            } else {
                break;
            }
        }
    };

    pedirTexto("el país", nueva.pais);
    pedirTexto("la ciudad", nueva.ciudad);
    pedirTexto("el cliente", nueva.cliente);
    pedirTexto("el producto", nueva.producto);
    pedirTexto("la categoría", nueva.categoria);
    pedirTexto("el medio de envío", nueva.medio_envio);
    pedirTexto("el estado del envío", nueva.estado_envio);

    // Ingreso de números enteros y decimales
    auto pedirEntero = [](const string &campo, int &destino) {
        string temp;
        while (true) {
            cout << "Ingrese " << campo << ": ";
            getline(cin, temp);
            if (!esNumeroEntero(temp)) {
                cout << "Entrada inválida. Use solo números enteros positivos.\n";
            } else {
                destino = stoi(temp);
                break;
            }
        }
    };

    auto pedirDecimal = [](const string &campo, double &destino) {
        string temp;
        while (true) {
            cout << "Ingrese " << campo << ": ";
            getline(cin, temp);
            if (!esNumeroDecimal(temp)) {
                cout << "Entrada inválida. Use un número válido (ej: 123.45).\n";
            } else {
                destino = stod(temp);
                break;
            }
        }
    };

    pedirEntero("la cantidad", nueva.cantidad);
    pedirDecimal("el precio unitario", nueva.precio_unitario);
    pedirDecimal("el monto total", nueva.monto_total);

    // Guardar en CSV
    ofstream archivo("data/ventas_sudamerica.csv", ios::app);
    if (archivo.fail()) {
        cout << "Error al intentar escribir en el archivo.\n";
        exit(1);
    }

    archivo << nueva.id_venta << "," << nueva.fecha << "," << nueva.pais << "," << nueva.ciudad << ","
            << nueva.cliente << "," << nueva.producto << "," << nueva.categoria << "," << nueva.cantidad << ","
            << nueva.precio_unitario << "," << nueva.monto_total << "," << nueva.medio_envio << ","
            << nueva.estado_envio << "\n";

    archivo.close();
    ventas.push_back(nueva);

    cout << "La venta se agregó correctamente.\n";
    cout << "Producto: " << nueva.producto << " | Cliente: " << nueva.cliente << endl;
}
void modificar_venta(vector<Venta> &ventas) {
    unordered_map<string, int> mapa_indices;

    for (int i = 0; i < ventas.size(); ++i) {
        mapa_indices[ventas[i].id_venta] = i;
    }

    cout << "Ingrese el ID de la venta a modificar: ";
    string id;
    cin >> id;

    if (mapa_indices.find(id) == mapa_indices.end()) {
        cout << "No se encontró ninguna venta con ese ID." << endl;
        return;
    }

    int idx = mapa_indices[id];
    Venta &venta = ventas[idx];

    cout << "\nCampos actuales de la venta:\n";
    mostrar_ventas({venta}, 1);

    function<void()> editar = [&]() {
        int opcion;
        cout << "\n¿Qué campo desea modificar?\n";
        cout << "1. Fecha\n2. País\n3. Ciudad\n4. Cliente\n5. Producto\n6. Categoría\n7. Cantidad\n8. Precio Unitario\n9. Monto Total\n10. Medio de Envío\n11. Estado de Envío\n0. Finalizar\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Nueva fecha: ";
                getline(cin, venta.fecha);
                break;
            case 2:
                do {
                    cout << "Nuevo país (solo letras): ";
                    getline(cin, venta.pais);
                } while (!all_of(venta.pais.begin(), venta.pais.end(), [](char c){ return isalpha(c) || isspace(c); }));
                break;
            case 3:
                do {
                    cout << "Nueva ciudad (solo letras): ";
                    getline(cin, venta.ciudad);
                } while (!all_of(venta.ciudad.begin(), venta.ciudad.end(), [](char c){ return isalpha(c) || isspace(c); }));
                break;
            case 4:
                cout << "Nuevo cliente: ";
                getline(cin, venta.cliente);
                break;
            case 5:
                cout << "Nuevo producto: ";
                getline(cin, venta.producto);
                break;
            case 6:
                cout << "Nueva categoría: ";
                getline(cin, venta.categoria);
                break;
            case 7:
                while (true) {
                    cout << "Nueva cantidad: ";
                    if (cin >> venta.cantidad && venta.cantidad >= 0) break;
                    cout << "Ingrese un número válido.\n";
                    cin.clear(); cin.ignore(10000, '\n');
                }
                cin.ignore();
                break;
            case 8:
                while (true) {
                    cout << "Nuevo precio unitario: ";
                    if (cin >> venta.precio_unitario && venta.precio_unitario >= 0) break;
                    cout << "Ingrese un número válido.\n";
                    cin.clear(); cin.ignore(10000, '\n');
                }
                cin.ignore();
                break;
            case 9:
                while (true) {
                    cout << "Nuevo monto total: ";
                    if (cin >> venta.monto_total && venta.monto_total >= 0) break;
                    cout << "Ingrese un número válido.\n";
                    cin.clear(); cin.ignore(10000, '\n');
                }
                cin.ignore();
                break;
            case 10:
                cout << "Nuevo medio de envío: ";
                getline(cin, venta.medio_envio);
                break;
            case 11:
                cout << "Nuevo estado de envío: ";
                getline(cin, venta.estado_envio);
                break;
            case 0:
                return;
            default:
                cout << "Opción inválida.\n";
                break;
        }
        editar(); // llamada recursiva
    };

    editar();

    ofstream archivo("data/ventas_sudamerica.csv");
    if (!archivo) {
        cout << "Error al abrir el archivo para escribir." << endl;
        return;
    }

    archivo << "ID_Venta,Fecha,Pais,Ciudad,Cliente,Producto,Categoria,Cantidad,Precio_Unitario,Monto_Total,Medio_Envio,Estado_Envio\n";
    for (const auto &v: ventas) {
        archivo << v.id_venta << "," << v.fecha << "," << v.pais << "," << v.ciudad << "," << v.cliente << ","
                << v.producto << "," << v.categoria << "," << v.cantidad << "," << v.precio_unitario << ","
                << v.monto_total << "," << v.medio_envio << "," << v.estado_envio << "\n";
    }

    archivo.close();
    cout << "Venta modificada exitosamente." << endl;
}

void eliminar_venta_filtrada(vector<Venta> &ventas, unordered_map<string, int> &indice) {
    string criterio, valor;
    cout << "¿Desea buscar por 'pais' o 'ciudad'?: ";
    cin >> criterio;

    if (criterio != "pais" && criterio != "ciudad") {
        cout << "✖ Criterio inválido. Use 'pais' o 'ciudad'.\n";
        return;
    }

    cout << "Ingrese el valor a buscar (" << criterio << "): ";
    cin >> ws;
    getline(cin, valor);

    // Mostrar coincidencias
    vector<int> indices_filtrados;
    cout << "\n Ventas encontradas:\n";
    for (int i = 0; i < ventas.size(); ++i) {
        if ((criterio == "pais" && ventas[i].pais == valor) ||
            (criterio == "ciudad" && ventas[i].ciudad == valor)) {
            cout << "ID: " << ventas[i].id_venta << " | "
                    << "Cliente: " << ventas[i].cliente << " | "
                    << "Producto: " << ventas[i].producto << " | "
                    << "Ciudad: " << ventas[i].ciudad << " | "
                    << "País: " << ventas[i].pais << endl;
            indices_filtrados.push_back(i);
        }
    }

    if (indices_filtrados.empty()) {
        cout << "✖ No se encontraron ventas con ese filtro.\n";
        return;
    }

    // Elegir cuál eliminar
    string id_a_eliminar;
    cout << "\nIngrese el ID de la venta que desea eliminar: ";
    cin >> id_a_eliminar;

    auto it = find_if(ventas.begin(), ventas.end(), [&](const Venta &v) {
        return v.id_venta == id_a_eliminar;
    });

    if (it != ventas.end()) {
        ventas.erase(it);
        cout << "Venta eliminada correctamente.\n";

        // reconstruir índice
        indice.clear();
        for (int i = 0; i < ventas.size(); ++i) {
            indice[ventas[i].id_venta] = i;
        }
    } else {
        cout << "No se encontró ninguna venta con ese ID.\n";
    }
}

void buscar_productos_por_promedio_superior(const vector<Venta> &ventas) {
    unordered_map<string, pair<double, int> > acumulador;

    for (const auto &venta: ventas) {
        acumulador[venta.producto].first += venta.monto_total;
        acumulador[venta.producto].second += 1;
    }

    double umbral;
    cout << "\nIngrese el monto umbral mínimo: ";
    cin >> umbral;

    cout << "\nProductos con promedio de monto total mayor a " << umbral << ":\n";

    bool encontrado = false;
    for (const auto &par: acumulador) {
        const string &producto = par.first;
        double suma = par.second.first;
        int cantidad = par.second.second;
        double promedio = suma / cantidad;

        if (promedio > umbral) {
            cout << "Producto: " << producto << " | Promedio: $" << fixed << setprecision(2) << promedio << endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "Ningún producto supera el umbral ingresado.\n";
    }
}

void buscar_promedio_bajo_por_pais(const vector<Venta> &ventas) {
    unordered_map<string, unordered_map<string, pair<double, int> > > datos;

    for (const auto &venta: ventas) {
        auto &producto = venta.producto;
        auto &pais = venta.pais;
        datos[pais][producto].first += venta.monto_total;
        datos[pais][producto].second += 1;
    }

    string pais_input;
    double umbral;
    cout << "\nIngrese el país: ";
    cin >> ws;
    getline(cin, pais_input);
    cout << "Ingrese el monto umbral máximo: ";
    cin >> umbral;

    cout << "\nProductos en " << pais_input << " con promedio menor a $" << umbral << ":\n";

    bool encontrado = false;
    auto it = datos.find(pais_input);
    if (it != datos.end()) {
        for (const auto &par: it->second) {
            const string &producto = par.first;
            double suma = par.second.first;
            int cantidad = par.second.second;
            double promedio = suma / cantidad;

            if (promedio < umbral) {
                cout << "Producto: " << producto << " | Promedio: $" << fixed << setprecision(2) << promedio << endl;
                encontrado = true;
            }
        }
    }

    if (!encontrado) {
        cout << "No se encontraron productos debajo del umbral en ese país.\n";
    }
}

void comparar_paises(const vector<Venta> &ventas) {
    string pais1, pais2;
    cout << "Ingrese el primer país: ";
    cin >> ws;
    getline(cin, pais1);
    cout << "Ingrese el segundo país: ";
    getline(cin, pais2);

    double total1 = 0, total2 = 0;
    unordered_map<string, int> productos1, productos2;
    unordered_map<string, int> envio1, envio2;

    for (const auto &v: ventas) {
        if (v.pais == pais1) {
            total1 += v.monto_total;
            productos1[v.producto] += v.cantidad;
            envio1[v.medio_envio]++;
        } else if (v.pais == pais2) {
            total2 += v.monto_total;
            productos2[v.producto] += v.cantidad;
            envio2[v.medio_envio]++;
        }
    }

    auto max_producto = [](const unordered_map<string, int> &m) {
        return max_element(m.begin(), m.end(), [](auto &a, auto &b) {
            return a.second < b.second;
        });
    };

    auto max_envio = [](const unordered_map<string, int> &m) {
        return max_element(m.begin(), m.end(), [](auto &a, auto &b) {
            return a.second < b.second;
        });
    };

    cout << "\n>>> Comparación de países:\n";
    cout << pais1 << " - Monto total: $" << total1 << endl;
    cout << pais2 << " - Monto total: $" << total2 << endl;

    if (!productos1.empty())
        cout << pais1 << " - Producto más vendido: " << max_producto(productos1)->first
                << " (" << max_producto(productos1)->second << " unidades)\n";
    if (!productos2.empty())
        cout << pais2 << " - Producto más vendido: " << max_producto(productos2)->first
                << " (" << max_producto(productos2)->second << " unidades)\n";

    if (!envio1.empty())
        cout << pais1 << " - Medio de envío más usado: " << max_envio(envio1)->first
                << " (" << max_envio(envio1)->second << " veces)\n";
    if (!envio2.empty())
        cout << pais2 << " - Medio de envío más usado: " << max_envio(envio2)->first
                << " (" << max_envio(envio2)->second << " veces)\n";
}

void comparar_productos(const vector<Venta> &ventas) {
    string prod1, prod2;
    cout << "Ingrese el primer producto: ";
    cin >> ws;
    getline(cin, prod1);
    cout << "Ingrese el segundo producto: ";
    getline(cin, prod2);

    int cant1 = 0, cant2 = 0;
    double total1 = 0, total2 = 0;

    for (const auto &v: ventas) {
        if (v.producto == prod1) {
            cant1 += v.cantidad;
            total1 += v.monto_total;
        } else if (v.producto == prod2) {
            cant2 += v.cantidad;
            total2 += v.monto_total;
        }
    }

    cout << "\n>>> Comparación de productos:\n";
    cout << prod1 << " - Cantidad total: " << cant1 << " | Monto total: $" << total1 << endl;
    cout << prod2 << " - Cantidad total: " << cant2 << " | Monto total: $" << total2 << endl;
}

void listar_ventas_por_ciudad(const vector<Venta> &ventas) {
    cout << "Ingrese la ciudad a buscar: ";
    string ciudad;
    cin.ignore();
    getline(cin, ciudad);

    NodoVenta *arbol = nullptr;
    for (const auto &v: ventas) {
        insertar_por_ciudad(arbol, v);
    }

    cout << "\nVentas realizadas en la ciudad son:'" << ciudad << "':\n";
    buscar_ciudad(arbol, ciudad);

}

void listar_ventas_por_pais_rango_fechas(const vector<Venta> &ventas) {
    string pais, fecha_inicio, fecha_fin;

    cout << "Ingrese el país a buscar: ";
    getline(cin >> ws, pais);

    cout << "Ingrese la fecha inicial (dd/mm/yyyy): ";
    getline(cin >> ws, fecha_inicio);

    cout << "Ingrese la fecha final (dd/mm/yyyy): ";
    getline(cin >> ws, fecha_fin);

    if (invertir_fecha(fecha_inicio) > invertir_fecha(fecha_fin)) {
        cout << "Error: la fecha inicial es posterior a la fecha final." << endl;
        return;
    }

    NodoVenta *raiz = nullptr;
    for (const auto &v : ventas) {
        insertar_por_pais_fecha(raiz, v);
    }

    bool encontrada = false;
    buscar_pais_y_fecha(raiz, pais, fecha_inicio, fecha_fin, encontrada);

    if (!encontrada) {
        cout << "No se encontraron ventas en " << pais << " entre las fechas dadas." << endl;
    }

    liberar_arbol(raiz);  // Si usás esta función
}

void menu_consultas_dinamicas(const vector<Venta> &ventas) {
    while (true) {
        int opcion;
        cout << "\n===== CONSULTAS DINÁMICAS =====\n";
        cout << "1. Comparar dos países\n";
        cout << "2. Comparar dos productos\n";
        cout << "3. Buscar productos con promedio por debajo de un umbral (por país)\n";
        cout << "4. Listar ventas en una ciudad específica\n";
        cout << "5. Listar ventas por rango de fechas y país\n";
        cout << "6. Buscar productos con promedio por encima de un umbral (global)\n";
        cout << "0. Volver al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        clock_t begin = clock(); // Iniciar tiempo

        switch (opcion) {
            case 1:
                comparar_paises(ventas);
                break;
            case 2:
                comparar_productos(ventas);
                break;
            case 3:
                buscar_promedio_bajo_por_pais(ventas);
                break;
            case 4:
                listar_ventas_por_ciudad(ventas);
                break;
            case 5:
                listar_ventas_por_pais_rango_fechas(ventas);
                break;
            case 6:
                buscar_productos_por_promedio_superior(ventas);
                break;
            case 0:
                cout << "Volviendo al menú principal...\n";
                return;
            default:
                cout << "Opción inválida.\n";
                continue;
        }

        clock_t end = clock(); // Fin tiempo
        double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
        cout << "Tiempo de ejecución: " << elapsed_secs << " segundos\n";
    }
}

int menu() {
    int opcion_menu;
    cout << "========= MENÚ PRINCIPAL =========" << endl;
    cout << "1. Mostrar todas las ventas" << endl;
    cout << "2. Agregar una nueva venta" << endl;
    cout << "3. Eliminar una venta" << endl;
    cout << "4. Modificar una venta" << endl;
    cout << "5. Estadísticas generales (procesamiento del punto 5)" << endl;
    cout << "6. Consultas dinámicas (punto 7)" << endl;
    cout << "0. Salir" << endl;
    cout << "=================================" << endl;
    cout << "Ingrese una opción:";
    cin >> opcion_menu;
    return opcion_menu;
}
