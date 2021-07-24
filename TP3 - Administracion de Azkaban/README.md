# Trabajo Practico 3 - Administración de Azkaban :european_castle:

La prisión de Azkaban guarda la información de sus presos según la
Maldición que usaron. Para esto ​se cuenta con dos archivos binarios de acceso
secuencial​, los cuales están ordenados por nombre, en uno de ellos figuran los
presos que realizaron la maldición ​Crucio ​(crucio.dat) ​y en el otro los que realizaron
la maldición ​Imperius (imperius.dat). No se interesan los que realizaron Avada
Kedavra ya que esa se paga con cadena perpetua.
Para liberar a los presos, la Administración se encarga de saber quiénes cumplen las
condiciones para poder ser perdonados. Los únicos que pueden ser alguna vez
liberados son aquellos que hicieron sólo una de las dos Maldiciones “perdonables”.

Cada mes ​se crea un archivo de texto con los nombres de quienes van a
ser liberado (si es que su ​fecha de liberación coincide con el
año/mes ingresado y su conducta es la requerida). Al liberar a los presos, se actualizan los dos archivos binarios mencionados al principio, eliminando a todos los que fueron liberados.
Por último, si lo desea se pueden ​mostrar los nombres de todos aquellos que liberados en cierto año/mes.

Detalles del enunciado: [TP3-Enunciado.pdf](https://github.com/stephanieizquierdo/FIUBA-AlgoritmosYProgramacion1-7540-/blob/master/TP3%20-%20Administracion%20de%20Azkaban/TP3-Enunciado.pdf)

## :pushpin: Compilación
Abrir terminal en la carpeta donde reciden los archivos e ingresar lo siguiente:
```
gcc *.c -o azkaban -std=c99 -Wall -Werror -Wconversion
```
## :pushpin: Ejecución
Abrir terminal donde se encuentra el ejecutable "azkaban" e ingresar lo siguiente:
```
./azkaban
```
