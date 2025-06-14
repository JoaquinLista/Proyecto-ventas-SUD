# Proyecto-ventas-SUD


# SUDVentas - Sistema de Gestión de Ventas en Sudamérica

Este programa permite gestionar, analizar y consultar datos de ventas realizadas en distintos países y ciudades de Sudamérica. Utiliza estructuras eficientes (como árboles binarios) y está orientado a brindar estadísticas claras y filtrados dinámicos al usuario.

## Requisitos

- Sistema operativo: Windows, Linux o macOS
- Compilador compatible con C++11 o superior
- Archivo CSV con las ventas ubicado en: `data/ventas_sudamerica.csv`

## Ejecución

1. Abrir una terminal.
2. Navegar a la carpeta del proyecto.
3. Compilar el programa:
   ```bash
   g++ -std=c++11 -o ventas main.cpp ArbolVentas.cpp Operaciones.cpp Procesamiento.cpp
   ```
4. Ejecutar el programa:
   ```bash
   ./ventas
   ```

## Menú Principal

Al iniciar el programa, se presenta el siguiente menú:

```
========= MENÚ PRINCIPAL =========
1. Mostrar todas las ventas
2. Agregar una nueva venta
3. Eliminar una venta
4. Modificar una venta
5. Estadísticas generales
6. Consultas dinámicas
0. Salir
```

## Funcionalidades

### 1. Mostrar todas las ventas
Lista por consola todas las ventas cargadas desde el archivo CSV y genera estadísticas generales como:

- Productos más y menos vendidos
- Medios de envío más usados
- Promedio por categoría y país
- Día con mayor monto vendido

### 2. Agregar una nueva venta
Solicita todos los campos de una venta desde consola (validando texto y números) y guarda el registro tanto en memoria como en el CSV.

### 3. Eliminar una venta
Permite buscar ventas por país o ciudad, muestra coincidencias y permite eliminar una específica por su ID.

### 4. Modificar una venta
Pide un ID de venta existente y permite editar cualquier campo, guardando los cambios en el archivo.

### 5. Estadísticas generales
Calcula métricas relevantes sobre el total de ventas, incluyendo comparaciones por país, ciudad, categoría y fecha.

### 6. Consultas dinámicas
Submenú interactivo para:
- Comparar dos países (monto total, producto más vendido, medio de envío más usado)
- Comparar dos productos (cantidad total y monto total)
- Buscar productos con promedio de venta bajo por país
- Listar ventas por ciudad
- Listar ventas por país y rango de fechas
- Buscar productos con promedio de venta alto global

## Formato del CSV

El archivo `ventas_sudamerica.csv` debe estar en la carpeta `data/` y tener la siguiente estructura:

```
ID_Venta,Fecha,Pais,Ciudad,Cliente,Producto,Categoria,Cantidad,Precio_Unitario,Monto_Total,Medio_Envio,Estado_Envio
001,01/01/2023,Argentina,Buenos Aires,Juan Perez,Laptop,Electrónica,1,1000.00,1000.00,Aéreo,Entregado
...
```

## Estructura del Proyecto

```
includes/
├── ArbolVentas.h
├── Operaciones.h
├── Procesamiento.h
├── Ventas.h
src/
├── ArbolVentas.cpp
├── Operaciones.cpp
├── Procesamiento.cpp
main.cpp
data/
└── ventas_sudamerica.csv
```

## Créditos

Desarrollado por estudiantes de la cátedra de Programación Estructurada (UCC, 2024-2025) como proyecto final.

## Notas

- El sistema usa estructuras de árbol binario para ciertas búsquedas, lo que mejora el rendimiento en consultas filtradas.
- Todas las operaciones son persistentes en el archivo CSV.
