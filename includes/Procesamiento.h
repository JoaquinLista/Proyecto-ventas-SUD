#ifndef PROCESAMIENTO_H
#define PROCESAMIENTO_H

#include "Ventas.h"
#include <vector>
/**
 * Calcula e imprime estadísticas generales sobre las ventas.
 * Muestra métricas como el total de ventas, promedio por categoría,
 * productos más y menos vendidos, medios de envío más usados,
 * y otros datos relevantes.
 *
 * @param ventas Vector que contiene todas las ventas cargadas.
 */
void calcular_estadisticas(const std::vector<Venta> &ventas);

#endif // PROCESAMIENTO_H
