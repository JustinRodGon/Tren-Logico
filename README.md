# Tren-Lógico

![Estructura del Tren](imagenes/Screenshot%20From%202025-10-06%2022-02-08.png)

## Descripción General

**Tren Lógico** es un proyecto desarrollado en **C++** que modela la estructura y funcionamiento de un tren utilizando distintas estructuras de datos dinámicas.  
El sistema permite administrar la información de los vagones, pasajeros, amenidades y lugares de parada, además de generar reportes con información consolidada del tren.

El objetivo principal es ofrecer una aplicación modular, eficiente y fácil de usar para gestionar un tren a nivel lógico mediante listas dobles, circulares y listas de la biblioteca estándar de C++.

---

## Estructuras de Datos Utilizadas

- **Tren (Lista Doble):**  
  Representa la secuencia de vagones. Cada nodo es un vagón con enlaces al siguiente y al anterior.

- **Amenidades por Vagón (Lista Circular):**  
  Cada vagón contiene una lista circular de amenidades (cocinas, baños, asientos de primera clase o turista), permitiendo una navegación continua.

- **Pasajeros (std::list):**  
  Cada vagón mantiene una lista de pasajeros utilizando la clase `std::list` de C++ para facilitar inserciones y eliminaciones dinámicas.

- **Lugares de Parada (std::list):**  
  Representa los lugares donde el tren se detiene. Los elementos están ordenados por **id**.

---

## Funcionalidades Principales

### 1. Administración de Información

Permite agregar, modificar, eliminar y visualizar datos del tren.

#### a. Gestión de Vagones
- **Agregar:** Inserta un nuevo vagón después del vagón actual.  
- **Eliminar:** Elimina el vagón actual previa confirmación.  
- **Modificar:** Permite cambiar el nombre o identificador del vagón actual.  
- **Mostrar:** Lista todos los vagones existentes con su información principal.

#### b. Gestión de Pasajeros
- **Agregar:** Añade un nuevo pasajero al vagón actual y valida su lugar de parada.  
- **Eliminar:** Elimina un pasajero según su identificador o criterio.  
- **Mostrar:** Despliega la lista completa de pasajeros del vagón actual.

#### c. Gestión de Amenidades
- **Agregar:** Añade una nueva amenidad al vagón actual (como cocinas, baños o asientos).  
- **Modificar:** Permite editar el nombre o cantidad de una amenidad existente.  
- **Eliminar:** Elimina una amenidad específica.  
- **Mostrar:** Muestra todas las amenidades disponibles en el vagón actual.

#### d. Gestión de Lugares de Parada
- **Agregar:** Inserta un nuevo lugar de parada manteniendo el orden por id.  
- **Eliminar:** Elimina un lugar y reasigna los pasajeros al lugar más próximo.  
- **Mostrar:** Despliega los lugares en orden por id y por nombre.

---

### 2. Generación de Reportes

Proporciona información agregada y estadística sobre los elementos del tren.

#### a. Reporte de Amenidades Totales por Tipo
Permite seleccionar una amenidad y obtener la cantidad total presente en todos los vagones.  
Ejemplo:

Seleccione una amenidad: Asientos de Primera Clase
Total en el tren: 85


#### b. Número Total de Pasajeros
Muestra la cantidad total de pasajeros a bordo del tren.

#### c. Vagón con Más Pasajeros
Identifica el vagón que tiene el mayor número de pasajeros.

#### d. Distribución de Pasajeros por Vagón
Muestra un resumen de la cantidad de pasajeros en cada vagón.

#### e. Reporte de Lugares de Parada
Indica cuántos pasajeros se bajan en cada lugar o estación.

---

## Interfaz del Sistema

El programa funciona mediante un **menú de texto interactivo** dividido en dos secciones:

- **Administración de Información:**  
  Gestión completa de los vagones, pasajeros, amenidades y lugares.

- **Generación de Reportes:**  
  Consultas y estadísticas generales del tren.

Durante la navegación, el sistema indica el **vagón actual** y permite moverse al siguiente o anterior, evitando las opciones si se encuentra en los extremos de la lista doble.

---

## Ejemplo de Estructura Interna

Cada **vagón** del tren contiene:

- Una **lista circular** de amenidades (baños, cocinas, asientos, etc.).
- Una **lista dinámica de pasajeros** utilizando `std::list`.
- Enlaces al **vagón anterior** y al **vagón siguiente**.

Ejemplo visual simplificado:

- **Vagón Azul:** Ana, Juan, Pedro, Sofía  
- **Vagón Verde:** Mario, Fer, Mateo  
- **Vagón Gris:** Pablo, Mari, Yuan, Lino, Marta

---

## Tecnologías y Lenguaje

- **Lenguaje:** C++17 o superior  
- **Librerías estándar:** `<iostream>`, `<list>`, `<string>`, `<memory>`  
- **Paradigma:** Programación estructurada y orientada a objetos  
- **Estructuras dinámicas:**  
  - Lista doble (tren)  
  - Lista circular (amenidades)  
  - Listas estándar STL (pasajeros y lugares)

---

## Autores

Desarrollo e implementación del proyecto **Tren Lógico** con enfoque en estructuras dinámicas, listas enlazadas y manipulación eficiente de datos en C++.
