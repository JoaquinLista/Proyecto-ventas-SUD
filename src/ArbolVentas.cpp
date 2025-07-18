
#include "../includes/Operaciones.h"
#include "../includes/ArbolVentas.h"
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





// Inserta por ciudad (ordenado alfabéticamente)
void insertar_por_ciudad(NodoVenta *&raiz, const Venta &v) {
    if (raiz == nullptr) {
        raiz = new NodoVenta(v);
    } else if (v.ciudad < raiz->venta.ciudad) {
        insertar_por_ciudad(raiz->izquierda, v);
    } else {
        insertar_por_ciudad(raiz->derecha, v);
    }
}

// Inserta por país y fecha (clave compuesta)
void insertar_por_pais_fecha(NodoVenta *&raiz, const Venta &v) {
    if (raiz == nullptr) {
        raiz = new NodoVenta(v);
    } else {
        string clave_v = v.pais + v.fecha;
        string clave_raiz = raiz->venta.pais + raiz->venta.fecha;

        if (clave_v < clave_raiz) {
            insertar_por_pais_fecha(raiz->izquierda, v);
        } else {
            insertar_por_pais_fecha(raiz->derecha, v);
        }
    }
}

// Recorrer en orden para listar ventas por ciudad
void buscar_ciudad(NodoVenta *raiz, const string &ciudad) {
    if (!raiz) return;

    buscar_ciudad(raiz->izquierda, ciudad);

    if (raiz->venta.ciudad == ciudad) {
        mostrar_ventas({raiz->venta}, 1);
    }

    buscar_ciudad(raiz->derecha, ciudad);
}

// Buscar por país y rango de fechas
void buscar_pais_y_fecha(NodoVenta *raiz, const string &pais, const string &desde, const string &hasta,
                         bool &encontrada) {
    if (!raiz) return;

    buscar_pais_y_fecha(raiz->izquierda, pais, desde, hasta, encontrada);

    if (raiz->venta.pais == pais && raiz->venta.fecha >= desde && raiz->venta.fecha <= hasta) {
        mostrar_ventas({raiz->venta}, 1);
        encontrada = true;
    }

    buscar_pais_y_fecha(raiz->derecha, pais, desde, hasta, encontrada);
}
void liberar_arbol(NodoVenta *raiz) {
    if (!raiz) return;
    liberar_arbol(raiz->izquierda);
    liberar_arbol(raiz->derecha);
    delete raiz;
}

string invertir_fecha(const string &fecha) {
    smatch match;
    regex patron(R"((\d{2})/(\d{2})/(\d{4}))");
    if (regex_match(fecha, match, patron)) {
        return match[3].str() + "-" + match[2].str() + "-" + match[1].str();
    }
    return "";  // Devuelve string vacío si no coincide
}
