#ifndef OPERACIONES_H
#define OPERACIONES_H

#include "../includes/Ventas.h"
#include <vector>
#include <string>
using namespace std;

vector<Venta> leer_csv(const string& path);
void mostrar_ventas(const vector<Venta>& ventas, int max_mostrar = 20);
void agregar_ventas (vector<Venta>& ventas);
int menu ();
#endif
