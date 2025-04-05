# App1

## **Profesores 2**
- **María Loreto Arriagada** <br>
  <loreto.arriagada.v@edu.uai.cl>

- **Paulina González** <br>
  <paulina.gonzalez.p@edu.uai.cl>

- **Justo Vargas** <br>
  <justo.vargas@edu.uai.cl>

## **Ayudante**
- **Diego Duhalde** <br>
  <dduhalde@alumnos.uai.cl>


# **Tarea 1: Pizzería en C**

## 1. Objetivos

1. Aprender a estructurar un programa en varios archivos fuente de manera ordenada, lógica y modular.  
2. Utilizar herramientas clásicas de apoyo a la programación como GIT, make, debuggers, etc.  
3. Utilizar punteros y, en especial, punteros a funciones.  
4. Desarrollar un sistema capaz de leer un archivo CSV y aplicar sobre él varias métricas (fórmulas matemáticas simples).

---

## 2. Enunciado Original

> **TICS200 App #1 – Pizzería**

Una reconocida pizzería de Namekusei guardó todas sus ventas en un archivo CSV, el cual dispuso para su análisis. Desean un análisis simple, donde las métricas son sólo fórmulas matemáticas básicas.  
Se le ha pedido a usted, como experto en C y paradigma procedural, que genere un programa capaz de entregar los valores de las métricas solicitadas por la pizzería.

### 2.1. Requerimientos funcionales del sistema

- Su programa consistirá en un **ejecutable** llamado `app1` (puede llevar la extensión `.exe` en Windows).  
- Será ejecutado desde una consola (terminal), con el **nombre del archivo de ventas** como parámetro, seguido de las métricas a calcular.  
- Ejemplo de ejecución (donde `ventas.csv` es el archivo CSV y `metricaN` corresponde a las distintas métricas que se quieran solicitar):  
  ```bash
  TICS200@localhost:~$ ./app1 ventas.csv metrica0 metrica1 ...
  ```

- **Formato del archivo CSV** (ejemplo):
  ```
  pizza_id,order_id,pizza_name_id,quantity,order_date,order_time,unit_price,total_price,pizza_size,pizza_category,pizza_ingredients,pizza_name
  1.00,1.00,hawaiian_m,1.00,1/1/2015,11:38:36,13.25,13.25,M,Classic,"Sliced Ham, Pineapple, Mozzarella Cheese",The Hawaiian Pizza
  2.00,2.00,classic_dlx_m,1.00,1/1/2015,11:57:40,16.00,16.00,M,Classic,"Pepperoni, Mushrooms, Red Onions, Red Peppers, Bacon",The Classic Deluxe Pizza
  3.00,2.00,five_cheese_l,1.00,1/1/2015,11:57:40,18.50,18.50,L,Veggie,"Mozzarella Cheese, Provolone Cheese, Smoked Gouda Cheese, Romano Cheese, Blue Cheese, Garlic",The Five Cheese Pizza
  ```
- **Métricas a pedir** (ejecutadas según se especifique en los parámetros de la consola):
  1. `pms`: Pizza más vendida  
  2. `pls`: Pizza menos vendida  
  3. `dms`: Fecha con más ventas en términos de dinero (junto a la cantidad de dinero recaudado)  
  4. `dls`: Fecha con menos ventas en términos de dinero (junto a la cantidad de dinero recaudado)  
  5. `dmsp`: Fecha con más ventas en términos de cantidad de pizzas (junto a la cantidad de pizzas)  
  6. `dlsp`: Fecha con menos ventas en términos de cantidad de pizzas (junto a la cantidad de pizzas)  
  7. `apo`: Promedio de pizzas por orden  
  8. `apd`: Promedio de pizzas por día  
  9. `ims`: Ingrediente más vendido  
  10. `hp`: Cantidad de pizzas por categoría vendidas

#### Ejemplo de uso:

```bash
TICS200@localhost:~$ ./app1 ventas.csv pms pls
TICS200@localhost:~$ Pizza mas vendida: The Hawaiian Pizza
TICS200@localhost:~$ Pizza menos vendida: The classic Deluxe Pizza
```

### 2.2. Supuestos

1. El usuario siempre ingresará información válida.  
2. No habrán campos vacíos en el archivo de ventas.  
3. El orden en que se piden las métricas por pantalla es el orden en que se muestran.

### 2.3. Restricciones

1. Debe usar **punteros a funciones** para cada métrica (o un arreglo de punteros a funciones), con firma:
   ```c
   char* (metrica)(int *size, struct order *orders);
   ```
2. No se requieren validaciones extras de los datos de entrada.  
3. Se aceptan múltiples métricas en una misma ejecución.  
4. El nombre del ejecutable debe ser `app1`.

---

## 3. Sobre la entrega

1. **Lenguaje**: C (sin frameworks externos no estándar).  
2. **Grupos**: 2 o 3 personas.  (para la sección del día miércoles de Santiago, los grupos son de 4 personas y se entregan la inscripción de grupos por correo a la profesora)
3. **Fecha de entrega**: Sábado 29 de Marzo a las 22:00.  (Para la Sec. 2 de Santiago la entrega queda para el Sábado 5 de Abril a las 22:00)
   - Por cada día de atraso se descuenta 1 punto, comenzando a las 22:01.
   - Compilador a usar: `gcc` v5.1 o superior.  
4. La entrega se realiza por la plataforma Webcursos especificando el nombre del repo.  
5. El repo deberá cumplir con lo especificado en la sección 5 (Ver secciones siguientes para los **Formato de Entrega**)

---

## 4. **Entregables y Estructura Final**

1. **Informe de diseño y justificación de la solución**  
   - **Objetivo**: Explicar de manera breve cómo se organizó el código, las estructuras de datos empleadas (`struct order`, etc.), la justificación de la modularidad y el uso de punteros a funciones.  
   - **Contenido sugerido**:  
     - *Diagrama de flujo* general que muestre el flujo principal del programa.  
     - Razones de diseño (por qué se eligió un determinado método de parseo del CSV, cómo se almacenan ingredientes, etc.).  
     - Explicación de la interacción entre archivos (`main.c`, `metrics.c`, `utils.c`, etc.).  
     - Referencias a recursos externos utilizados.

2. **Sección de reflexiones finales o autoevaluación**  
   - Cada integrante o el grupo redactará **uno o dos párrafos** indicando:  
     - ¿Cómo enfrentaron los errores, pruebas y debugging?  
     - ¿Qué fue lo más complejo o interesante de la tarea?  
     - ¿Qué lecciones aprendieron al implementar en C este tipo de lectura de archivos y cálculos de métricas?

3. **Explicación de cómo usaron IA**  
   - Si se utilizó ChatGPT u otra herramienta, describir **qué tipo de ayuda** brindó la IA (e.g., sugerencia de estructuras, debug, explicación de errores) y **cómo validaron** dicha información.  
   - No se pide incrustar todo el historial de ChatGPT, sino una explicación clara de **cómo se integraron** o descartaron las ideas propuestas por la IA.  
   - En caso de **no** usar ninguna IA, basta con mencionarlo.

---

## 5. Formato de Entrega (vía repositorio GitHub)

1. **Fork del repositorio base**  
   - Deberán **forkear** el siguiente repositorio: [App1 en GitHub](https://github.com/UAI-Lenguaje-y-Paradigmas/App1).  
   - En ese repositorio forkeado, **agregar** a todos los integrantes del grupo como colaboradores.  

2. **Commits balanceados**  
   - Cada integrante del grupo debe **tener aproximadamente la misma cantidad de commits**.  
   - Se evaluará la participación equitativa a través del historial de commits (mensaje, fecha, contenido de los cambios, etc.).  

3. **Estructura del repositorio**  
   - Dentro de **la carpeta principal** (o la estructura que ustedes definan, pero claramente organizada), deberán incluir:  
     1. **Código fuente en C** (archivos `.c` y `.h`), siguiendo una división modular y lógica.  
     2. Un **Makefile** que compile la aplicación sin errores (y sin *warnings* en la medida de lo posible).  
     3. Un **Informe de diseño** (PDF o Markdown) que explique la arquitectura del proyecto, el uso de punteros a funciones, la estrategia de lectura de CSV, etc.  
     4. Una **Sección de reflexiones finales** o *autoevaluación*, que puede ir integrada al mismo informe u en un documento aparte.  
     5. Una **Explicación de uso de IA** (si se utilizó ChatGPT u otra herramienta), también puede estar en el mismo documento de diseño.  
     6. Un **README** breve con la información del grupo (nombres, correos, etc.) y la **línea de compilación** para `app1` (en caso de no especificarse ya en el Makefile).  

4. **Entrega**  
   - La entrega oficial consistirá en la **URL del repositorio forkeado**.  
   - Asegúrense de que el repositorio sea **público** o que el profesor/ayudante tenga acceso.  
   - Verifiquen que el programa compile y ejecute correctamente al clonar el repositorio y ejecutar `make` seguido de `./app1 ventas.csv pms ...` (o los parámetros de métricas requeridos).

El proceso de corrección será:

1. Se ingresará a la carpeta `tarea1/`.  
2. Se ejecutará `make`.  
3. Se probará con:  
   ```bash
   ./app1 ventas.csv pms pls dms ...
   ```  
   y se evaluará el correcto funcionamiento de cada métrica.

---

## 6. Rúbrica Actualizada

A continuación, la rúbrica con las ponderaciones finales, integrando los nuevos elementos:

| **Criterios generales**                                           | **Ponderación** | **Descripción**                                                                                                                                                                                                                                                                                    |
|:-----------------------------------------------------------------:|:---------------:|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **1. Funcionamiento del programa**                               |       40%       | <ul><li>El programa se compila y corre sin errores de ejecución (segmentation fault, etc.).</li><li>El formato de salida de cada métrica es acorde al enunciado.</li><li>Los resultados son correctos según el problema (parcial si cumple solo algunas).</li></ul> |
| **2. Paradigma Procedural**                                      |       25%       | <ul><li>Lógica clara y coherente con el problema.</li><li>Uso de funciones y modularidad adecuada, evitando variables globales innecesarias.</li><li>Incluye comentarios descriptivos (explicando la lógica de cada función/archivo).</li></ul>                                                |
| **3. Lenguaje C**                                                |       20%       | <ul><li>Uso apropiado de punteros a función (según se solicita).</li><li>Gestión de memoria dinámica correcta (malloc/free), sin fugas detectables.</li><li>Lectura de archivos y parseo dinámico del CSV (uso de structs, manejo de líneas e ingredientes).</li></ul>                                              |
| **4. Informe de diseño, reflexiones finales y uso de IA**        |       15%       | <ul><li><strong>Informe de diseño y justificación (5%)</strong>: claridad para explicar la arquitectura, estructuras de datos y decisiones de diseño.</li><li><strong>Reflexiones finales (5%)</strong>: identificación de desafíos y aprendizajes.</li><li><strong>Explicación de uso de IA (5%)</strong>: transparencia y análisis crítico.</li></ul> |

**Total:** 100%  

### Penalizaciones y bonus

- **Entrega atrasada**: Cada día de retraso resta 1 punto al máximo alcanzable (comenzando a las 00:00 del día siguiente a la entrega).  
- **Menos integrantes que lo propuesto (2-3)**: Puede existir un bonus o se mantiene la pauta según lo definido por el curso.  
- **Más integrantes que lo propuesto**: -1.0 a la nota final.  
- **Organización ejemplar en diferentes archivos**: Puede haber un leve bonus si está especialmente bien segmentado y documentado.

---

## 7. Ejemplo de Llamado al Programa

Como recordatorio, una posible ejecución para verificar las funcionalidades podría ser:

```bash
make
./app1 ventas.csv pms pls dms dlsp apo ims ...
```

La salida esperada (en la terminal) deberá mostrar cada resultado en el orden de los parámetros ingresados:

```
Pizza más vendida: ...
Pizza menos vendida: ...
Fecha con más ventas (dinero) + total recaudado: ...
Fecha con menos ventas (pizzas) + cantidad de pizzas: ...
Promedio de pizzas por orden: ...
Ingrediente más vendido: ...
... etc.
```

---

## 8. Conclusión

La tarea busca verificar no solo que el programa **funcione**, sino que el/la estudiante muestre comprensión y reflexión sobre su diseño, uso de punteros a funciones y manejo de archivos CSV en C. El agregado de **Informe de diseño**, **Reflexiones finales** y **Explicación de IA** permitirá evidenciar el proceso de desarrollo, la lógica implementada y la honestidad sobre las herramientas utilizadas.

¡Éxito con la entrega!
