#ifndef OPERACIONES_H
#define OPERACIONES_H
#include <iomanip>
#include "../includes/Ventas.h"
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;



// ─── Validaciones ─────────────────────────────

/**
 * @brief Valida si un texto contiene solo letras (mayúsculas o minúsculas) y espacios.
 *
 * Incluye soporte para letras con tilde y la letra Ñ.
 *
 * @param input Texto a validar.
 * @return true si el texto es válido, false en caso contrario.
 */
bool esTextoValido(const string &input);
/**
 * @brief Verifica si una cadena representa un número entero positivo.
 *
 * No acepta decimales ni signos negativos.
 *
 * @param input Cadena a verificar.
 * @return true si es un número entero válido, false si no.
 */
bool esNumeroEntero(const string &input);
/**
 * @brief Verifica si una cadena representa un número decimal válido.
 *
 * Acepta números con o sin parte decimal (ej: "123", "45.67").
 *
 * @param input Cadena a verificar.
 * @return true si es un número decimal válido, false si no.
 */
bool esNumeroDecimal(const string &input);
/**
 * @brief Verifica si una fecha tiene el formato dd/mm/yyyy.
 *
 * No valida si la fecha realmente existe en el calendario,
 * solo el patrón de formato.
 *
 * @param fecha Cadena a validar.
 * @return true si cumple el formato, false en caso contrario.
 */
bool es_fecha_valida(const string& fecha);
/**
 * @brief Verifica si un texto contiene únicamente letras y espacios.
 *
 * Similar a esTextoValido, pero sin acentos ni letras especiales.
 *
 * @param texto Cadena a verificar.
 * @return true si cumple con la condición, false si no.
 */
bool contiene_solo_letras_y_espacios(const string& texto);

// ─── Utilidades ───────────────────────────────
vector<Venta> leer_csv(const string &path);
/**
 * @brief Muestra por consola un subconjunto del listado de ventas.
 *
 * @param ventas Vector de ventas
 * @param max_mostrar Cantidad máxima de ventas a mostrar (-1 para mostrar todas)
 */
void mostrar_ventas(const vector<Venta>& ventas, int max_mostrar = -1);

// ─── Operaciones sobre ventas ─────────────────
/**
 * @brief Agrega una nueva venta al vector y al archivo CSV.
 *
 * Solicita los datos por consola, los guarda en memoria y persiste en disco.
 *
 * @param ventas Vector de ventas (se actualiza con la nueva)
 */
void agregar_ventas(vector<Venta> &ventas);
/**
 * @brief Elimina una venta según filtro por país o ciudad.
 *
 * Muestra las coincidencias y permite elegir una venta a eliminar por ID,
 * actualizando el índice y el vector de ventas.
 *
 * @param ventas Vector de ventas
 * @param indice Mapa que relaciona ID de venta con su índice en el vector
 */
void eliminar_venta_filtrada(std::vector<Venta> &ventas, std::unordered_map<std::string, int> &indice);


/**
 * @brief Modifica una venta existente según su ID.
 *
 * Permite editar campo por campo, y reescribe el archivo CSV con las modificaciones.
 *
 * @param ventas Vector de ventas (se actualiza en memoria y disco)
 */
void modificar_venta(std::vector<Venta> &ventas);


// ─── Consultas dinámicas ──────────────────────
/**
 * @brief Busca productos con promedio de monto mayor a un umbral.
 *
 * Agrupa las ventas por producto y calcula el promedio de monto total,
 * mostrando los que superan el umbral ingresado.
 *
 * @param ventas Vector de ventas
 */
void buscar_productos_por_promedio_superior(const vector<Venta> &ventas);

/**
 * @brief Lista productos cuyo monto promedio es inferior al umbral en un país.
 *
 * Agrupa ventas por producto dentro de un país y calcula el promedio,
 * mostrando solo los que estén por debajo del umbral indicado.
 *
 * @param ventas Vector de ventas
 */
void buscar_promedio_bajo_por_pais(const vector<Venta> &ventas);
/**
 * Compara dos productos seleccionados por el usuario.
 * Muestra la cantidad total vendida y el monto total acumulado de cada uno.
 *
 * @param ventas Vector que contiene todas las ventas cargadas.
 */
void comparar_productos(const vector<Venta> &ventas);
/**
 * @brief Compara dos países en base a métricas comerciales.
 *
 * Analiza y muestra para cada país: el monto total de ventas,
 * el producto más vendido y el medio de envío más utilizado.
 *
 * @param ventas Vector con todas las ventas cargadas.
 */
void comparar_paises(const vector<Venta> &ventas);
/**
 * @brief Lista todas las ventas realizadas en una ciudad específica.
 *
 * Solicita el nombre de una ciudad al usuario, crea un árbol binario
 * ordenado por ciudad y muestra las ventas correspondientes.
 *
 * @param ventas Vector con todas las ventas cargadas.
 */
void listar_ventas_por_ciudad(const vector<Venta> &ventas);

/**
 * Lista todas las ventas realizadas en un país específico y dentro de un rango de fechas dado.
 * Solicita al usuario el país y las fechas límite, e imprime las coincidencias.
 *
 * @param ventas Vector que contiene todas las ventas cargadas.
 */

void listar_ventas_por_pais_rango_fechas(const vector<Venta> &ventas);
/**
 * Muestra un submenú interactivo con distintas consultas dinámicas sobre los datos de ventas.
 * Permite comparar países, productos, hacer filtrados por ciudad, rango de fechas o promedios.
 *
 * @param ventas Vector que contiene todas las ventas cargadas.
 */
void menu_consultas_dinamicas(const std::vector<Venta> &ventas);

// ─── Menú ─────────────────────────────────────
int menu();

int menu();
#endif
