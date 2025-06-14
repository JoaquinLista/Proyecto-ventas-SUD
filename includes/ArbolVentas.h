
#ifndef ARBOL_VENTAS_H
#define ARBOL_VENTAS_H

#include "Ventas.h"
#include <string>
#include <vector>

using namespace std;


/**
 * @brief Nodo del árbol binario de ventas.
 *
 * Cada nodo contiene una venta y punteros a sus subárboles izquierdo y derecho.
 */
struct NodoVenta {
    Venta venta;
    NodoVenta *izquierda = nullptr;
    NodoVenta *derecha = nullptr;

    NodoVenta(const Venta &v) : venta(v) {}
};


/**
 * @brief Inserta una venta en el árbol binario ordenado por ciudad (orden alfabético).
 *
 * @param raiz Referencia al puntero raíz del árbol.
 * @param v Venta a insertar.
 */
void insertar_por_ciudad(NodoVenta *&raiz, const Venta &v);
/**
 * @brief Inserta una venta en el árbol binario ordenado por país y fecha (clave compuesta).
 *
 * Combina país y fecha como clave para ordenar las inserciones.
 *
 * @param raiz Referencia al puntero raíz del árbol.
 * @param v Venta a insertar.
 */
void insertar_por_pais_fecha(NodoVenta *&raiz, const Venta &v);

/**
 * @brief Busca y muestra ventas realizadas en una ciudad específica.
 *
 * Recorre el árbol inorden para imprimir ventas cuya ciudad coincida con el criterio.
 *
 * @param raiz Puntero al nodo raíz del árbol.
 * @param ciudad Ciudad a buscar.
 */
void buscar_ciudad(NodoVenta *raiz, const string &ciudad);
/**
 * @brief Busca y muestra ventas de un país dentro de un rango de fechas.
 *
 * Recorre el árbol e imprime las ventas que coincidan con el país y estén entre las fechas dadas.
 *
 * @param raiz Puntero al nodo raíz del árbol.
 * @param pais País a buscar.
 * @param desde Fecha inicial (formato dd/mm/yyyy).
 * @param hasta Fecha final (formato dd/mm/yyyy).
 * @param encontrada Variable booleana que se marca como true si se encontró al menos una coincidencia.
 */
void buscar_pais_y_fecha(NodoVenta *raiz, const string &pais, const string &desde, const string &hasta,bool &encontrada);
/**
 * @brief Libera la memoria de un árbol binario de ventas.
 *
 * Elimina recursivamente todos los nodos del árbol y libera sus recursos.
 *
 * @param raiz Puntero al nodo raíz del árbol (se libera).
 */
void liberar_arbol(NodoVenta *raiz);
/**
 * @brief Invierte el formato de una fecha de dd/mm/yyyy a yyyy-mm-dd.
 *
 * Útil para comparar fechas cronológicamente.
 *
 * @param fecha Fecha original en formato dd/mm/yyyy.
 * @return Cadena con la fecha en formato yyyy-mm-dd.
 */
string invertir_fecha(const string &fecha);

#endif
