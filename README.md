# Path Planning - Planificación de Rutas para Robots

Este repositorio contiene la implementación de algoritmos de planificación de rutas (path planning) para robots que navegan en laberintos bidimensionales. El proyecto está estructurado en dos actividades principales que implementan diferentes enfoques y estructuras de datos para resolver el problema de encontrar rutas desde una posición inicial hasta un destino.

## 📋 Descripción General

El objetivo principal del proyecto es desarrollar algoritmos eficientes que permitan a un robot navegar por un mapa representado como una matriz bidimensional, donde:
- `#` representa obstáculos
- `.` representa espacios libres
- El robot debe encontrar un camino válido desde su posición inicial hasta un destino especificado

## 🗂️ Estructura del Proyecto

### Actividad 1
Implementación básica del sistema de navegación que incluye:
- **Estructuras de datos**: Pilas, listas genéricas, tablas hash
- **Componentes principales**:
  - `robot.c/h`: Lógica del robot y navegación básica
  - `mapa.c/h`: Representación y manejo del mapa
  - `pila.c/h`: Implementación de pila para el algoritmo de navegación
  - `tablahash.c/h`: Tabla hash para optimización
  - `simulacion.c/h`: Simulación del recorrido del robot

### Actividad 2
Implementación avanzada que mejora la eficiencia y funcionalidad:
- **Estructuras de datos avanzadas**: Colas de prioridad, heaps binarios
- **Componentes principales**:
  - `robot.c`: Robot con capacidades mejoradas
  - `colaprioridad.c/h`: Cola de prioridad para algoritmos óptimos (A*, Dijkstra, etc.)
  - `bheap.c/h`: Heap binario para la cola de prioridad
  - `sensor.c`: Sistema de sensores para percepción del entorno
  - `mapa.c/h`: Mapa mejorado con funcionalidades adicionales

### Informe
Documentación completa del proyecto en LaTeX que incluye:
- Descripción de los algoritmos implementados
- Análisis de complejidad
- Resultados y comparaciones
- Detalles de implementación

## 🚀 Características

- ✅ Navegación básica en laberintos 2D
- ✅ Detección de obstáculos
- ✅ Validación de posición inicial y destino
- ✅ Visualización del recorrido
- ✅ Algoritmos de búsqueda optimizados (en Actividad 2)
- ✅ Estructuras de datos eficientes
- ✅ Generación de laberintos aleatorios
- ✅ Simulación completa del comportamiento del robot

## 📝 Formato de Entrada

Los archivos de configuración siguen el siguiente formato:

```
alto ancho
posI posJ
destI destJ
#######
#.....#
#..#..#
#.....#
#######
```

Donde:
- Primera línea: Dimensiones del mapa (alto y ancho)
- Segunda línea: Posición inicial del robot (fila, columna)
- Tercera línea: Posición destino (fila, columna)
- Líneas siguientes: Representación del mapa (`#` = obstáculo, `.` = libre)

## 🛠️ Compilación y Uso

### Actividad 1
```bash
cd actividad-1
make
./main <archivo_laberinto>
```

### Actividad 2
```bash
cd actividad-2
make
./main <archivo_laberinto>
```

## 📄 Archivos Adicionales

- `TPFinal.pdf`: Documento final del trabajo práctico
- `clean.sh`: Script para limpiar archivos compilados
- `laberintos/`: Directorio con ejemplos de laberintos
- `tableros/`: Directorio con tableros de prueba

## 🔧 Tecnologías Utilizadas

- **Lenguaje**: C (C99)
- **Herramientas**: Make, GCC
- **Estructuras de datos**: Listas, Pilas, Colas de prioridad, Heaps, Tablas hash
- **Documentación**: LaTeX

## 📚 Conceptos Implementados

- Algoritmos de búsqueda en grafos
- Estructuras de datos abstractas (ADT)
- Gestión de memoria dinámica
- Validación de entrada
- Simulación de sistemas

## 👤 Autor

Este proyecto forma parte de un trabajo práctico académico sobre planificación de rutas y algoritmos de búsqueda.

---

**Nota**: Este repositorio contiene implementaciones educativas de algoritmos de planificación de rutas para robots en entornos de laberintos.

