Diseño y Análisis de Algoritmos : Tarea II
Búsqueda en texto.

Script de DFA: MainDFA.java
Desarrollado en:
Requiere Java version 7 o mayor.
IntelliJ IDEA 2017.1.2
JRE: 1.8.0_112-release-736-b16 x86_64
JVM: OpenJDK 64-Bit Server VM by JetBrains s.r.o
Mac OS X 10.11.6 

No es necesario lidiar con este script pues se provee T2V1.jar. Antes de ejecutar este se debe crear una carpeta donde se guarden todos los inputs a probar dentro de ella. Luego al correr el .jar se debe especificar como argumento la ubicación de esta.

Asegurarse que los únicos archivos dentro de esta carpeta sean los inputs. Revisar y eliminar archivos ocultos de existir (.Ds_Store por ejemplo en OSX).

El .jar creara una version limpia de cada input y ademas creara un archivo results.csv en el cual se guardan las distintas métricas pedidas asociadas al DFA.


Script de SA: SuffixArray.cpp
Desarrollado en: Sublime Text
Requiere C++11

Para ejecutar es necesario tener C++ instalado. Para su compilación se necesita tener el Makefile y el archivo en la misma carpeta, ejecutar "make" en un terminal con la dirección de los archivos. Luego ejecutar ./output para correr el código. Uno tiene la opción de correr un full test ("full test") o entregarle un archivo específico y hacer tests específicos.