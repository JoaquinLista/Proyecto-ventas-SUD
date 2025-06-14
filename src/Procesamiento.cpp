#include "../includes/Procesamiento.h"
#include <iostream>
#include <unordered_map>
#include <map>
#include <algorithm>

using namespace std;

void calcular_estadisticas(const vector<Venta> &ventas) {
    unordered_map<string, unordered_map<string, double> > monto_por_ciudad_pais;
    unordered_map<string, unordered_map<string, double> > monto_por_producto_pais;
    unordered_map<string, unordered_map<string, pair<double, int> > > suma_y_cant_por_categoria_pais;
    unordered_map<string, unordered_map<string, int> > envios_por_pais;
    unordered_map<string, unordered_map<string, int> > envios_por_categoria;
    unordered_map<string, double> monto_por_fecha;
    unordered_map<string, unordered_map<string, int> > estado_envio_por_pais;
    unordered_map<string, int> cantidad_por_producto;

    for (const auto &v: ventas) {
        monto_por_ciudad_pais[v.pais][v.ciudad] += v.monto_total;
        monto_por_producto_pais[v.pais][v.producto] += v.monto_total;
        suma_y_cant_por_categoria_pais[v.pais][v.categoria].first += v.monto_total;
        suma_y_cant_por_categoria_pais[v.pais][v.categoria].second++;
        envios_por_pais[v.pais][v.medio_envio]++;
        envios_por_categoria[v.categoria][v.medio_envio]++;
        monto_por_fecha[v.fecha] += v.monto_total;
        estado_envio_por_pais[v.pais][v.estado_envio]++;
        cantidad_por_producto[v.producto] += v.cantidad;
    }

    cout << "\n Top 5 ciudades con mayor monto de ventas por país:\n";
    for (const auto &[pais, ciudades]: monto_por_ciudad_pais) {
        vector<pair<string, double> > lista(ciudades.begin(), ciudades.end());
        sort(lista.begin(), lista.end(), [](auto &a, auto &b) {
            return a.second > b.second;
        });
        cout << "- " << pais << ":\n";
        for (int i = 0; i < min(5, (int) lista.size()); ++i) {
            cout << "   " << lista[i].first << ": $" << lista[i].second << endl;
        }
    }

    auto max_prod = max_element(cantidad_por_producto.begin(), cantidad_por_producto.end(),
                                [](auto &a, auto &b) { return a.second < b.second; });
    auto min_prod = min_element(cantidad_por_producto.begin(), cantidad_por_producto.end(),
                                [](auto &a, auto &b) { return a.second < b.second; });

    cout << "\n Producto más vendido: " << max_prod->first << " (" << max_prod->second << " unidades)" << endl;
    cout << "Producto menos vendido: " << min_prod->first << " (" << min_prod->second << " unidades)" << endl;

    auto max_dia = max_element(monto_por_fecha.begin(), monto_por_fecha.end(),
                               [](auto &a, auto &b) { return a.second < b.second; });
    cout << "\n Día con mayor monto vendido: " << max_dia->first << " ($" << max_dia->second << ")" << endl;

    cout << "\n Medio de envío más utilizado por país:\n";
    for (auto &[pais, envios]: envios_por_pais) {
        auto max_envio = max_element(envios.begin(), envios.end(),
                                     [](auto &a, auto &b) { return a.second < b.second; });
        cout << "- " << pais << ": " << max_envio->first << " (" << max_envio->second << " veces)\n";
    }

    cout << "\n Medio de envío más utilizado por categoría:\n";
    for (auto &[cat, envios]: envios_por_categoria) {
        auto max_envio = max_element(envios.begin(), envios.end(),
                                     [](auto &a, auto &b) { return a.second < b.second; });
        cout << "- " << cat << ": " << max_envio->first << " (" << max_envio->second << " veces)\n";
    }

    cout << "\nEstado de envío más frecuente por país:\n";
    for (auto &[pais, estados]: estado_envio_por_pais) {
        auto max_estado = max_element(estados.begin(), estados.end(),
                                      [](auto &a, auto &b) { return a.second < b.second; });
        cout << "- " << pais << ": " << max_estado->first << " (" << max_estado->second << " veces)\n";
    }

    cout << "\n Promedio de ventas por categoría en cada país:\n";
    for (auto &[pais, categorias]: suma_y_cant_por_categoria_pais) {
        cout << "- " << pais << ":\n";
        for (auto &[cat, datos]: categorias) {
            double promedio = datos.first / datos.second;
            cout << "   " << cat << ": $" << promedio << " promedio\n";
        }
    }

    cout << "\n Estadísticas calculadas correctamente.\n";
}
