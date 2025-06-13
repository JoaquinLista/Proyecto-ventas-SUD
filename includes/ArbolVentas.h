#ifndef ARBOL_VENTAS_H
#define ARBOL_VENTAS_H

#include "Ventas.h"
#include <string>

using namespace std;

struct NodoVenta {
    Venta venta;
    NodoVenta* izquierda;
    NodoVenta* derecha;

    NodoVenta(const Venta& v) : venta(v), izquierda(nullptr), derecha(nullptr) {}
};

// Inserta por ciudad (ordenado alfabéticamente)
void insertar_por_ciudad(NodoVenta*& raiz, const Venta& v) {
    if (raiz == nullptr) {
        raiz = new NodoVenta(v);
    } else if (v.ciudad < raiz->venta.ciudad) {
        insertar_por_ciudad(raiz->izquierda, v);
    } else {
        insertar_por_ciudad(raiz->derecha, v);
    }
}

// Inserta por país y fecha (clave compuesta)
void insertar_por_pais_fecha(NodoVenta*& raiz, const Venta& v) {
    string clave_v = v.pais + v.fecha;
    string clave_raiz = raiz->venta.pais + raiz->venta.fecha;

    if (raiz == nullptr) {
        raiz = new NodoVenta(v);
    } else if (clave_v < clave_raiz) {
        insertar_por_pais_fecha(raiz->izquierda, v);
    } else {
        insertar_por_pais_fecha(raiz->derecha, v);
    }
}

// Recorrer en orden para listar ventas por ciudad
void buscar_ciudad(NodoVenta* raiz, const string& ciudad) {
    if (!raiz) return;

    buscar_ciudad(raiz->izquierda, ciudad);

    if (raiz->venta.ciudad == ciudad) {
        mostrar_ventas({raiz->venta}, 1);
    }

    buscar_ciudad(raiz->derecha, ciudad);
}

void buscar_pais_y_fecha(NodoVenta* raiz, const string& pais, const string& desde, const string& hasta, bool& encontrada) {
    if (!raiz) return;

    buscar_pais_y_fecha(raiz->izquierda, pais, desde, hasta, encontrada);

    if (raiz->venta.pais == pais && raiz->venta.fecha >= desde && raiz->venta.fecha <= hasta) {
        mostrar_ventas({raiz->venta}, 1);
        encontrada = true;
    }

    buscar_pais_y_fecha(raiz->derecha, pais, desde, hasta, encontrada);
}

#endif