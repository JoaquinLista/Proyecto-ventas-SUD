#ifndef OPERACIONES_H
#define OPERACIONES_H

#include "../includes/Ventas.h"
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;



vector<Venta> leer_csv(const string& path);
void mostrar_ventas(const vector<Venta>& ventas, int max_mostrar = 20);
void agregar_ventas (vector<Venta>& ventas);
void eliminar_ventas(vector<Venta>& ventas, unordered_map<string, int>& indice);
int menu ();
#endif
