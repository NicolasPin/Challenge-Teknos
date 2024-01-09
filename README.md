# *Challenge Teknos*
- Trabajo Realizado por Nicolas Pinto 

Se desea obtener un programa que permita codificar y decodificar una frase teniendo en cuenta una tabla de duplas formada por letra/codigo.
  
En el siguiente apartado describiré de qué manera funciona el programa y por qué fueron tomadas ciertas decisiones. 

## *Modelado de tabla*
A la hora de modelar codigo, existen diferentes formas de hacerlo y cada una de ella acarrea ciertas ventajas y desventajas.

En el código presentado, se optó por modelarlo mediante un vector llamado tabla. Este vector es de tipo *CodigoTabla*, la cual es una estructura formada por  *wchar_t* y  *string* los cuales representan la letra y el codigo respectivamente.
Se optó por tomar como tipo de dato wchar_t ya que este al estar formado por mas bytes (entre 2-4 dependiendo del compilador utilizado) y consecuentemente mas bits, puede representar mas caracteres y, en mi caso, busqué poder representar la "ñ".

La otra forma de modelar la tabla fue la utilizacion de la estructura unordered_map, de la cual hablaremos mas adelante en el informe.

## *Modelado de Funciones*
Se utilizó para la entrada de datos dos funciones; *obtenerFrase* y *obtenerModo*, las cuales utilizan como flujo de entrada el estandard  de C++, incluido por la biblioteca iostream.
Se utiliza la funcion *transform*, la cual es de orden superior, para convertirlas en lowerCase.

Una vez obtenidos tanto frase como modo, se invoca seleccionarConversor, en donde se utiliza un operador ternario para elegir cual es el modo que deseo utilizar para la conversion. 

### *Codificar* 
El modelado propuesto consiste en ciclar cada uno de los caracteres provenientes de la frase y compararlo uno a uno con cada uno de los caracteres de mi tabla hasta encontrar aquel que coincida. Una vez que coincide, devolverá el simbolo asociado.
Este tipo de modelado tiene una desventaja; La eficiencia. Al ser un programa con una cantidad "pequeña" de valores, no es un gran problema la comparacion de *chars* uno por uno, pero si fuera una tabla con miles de datos si podría serlo.
Por eso se investigó y consideró la opcion de unordered_map, la cual consiste en asignar una clave( o ID) a ciertos conjuntos de valores. Esta funcion permite una busqueda eficiente del valor sin la necesidad de comparar cada string hasta encontrarlo. 

### *Decodificar* 
La funcion decodificar consiste en recibir la frase, obtener un vector con cada una de sus palabras(en este caso codigos), *mapear* cada uno de estos valores a su respectivo valor de tabla (letras) y concatenarlo hasta resultar en la frase final.

## *Testing*
Se implementan dos funciones sin retorno, las cuales utilizaremos por su efecto de lado. En este caso, su efecto de lado es la ejecución de una bateria de asserts.
Cabe aclarar que a la hora de formalizar un proyecto, es recomendable separar en un archivo aparte los test, utilizando la sintaxis proporcionada por cada lenguaje para la integracion de los mismos. En este caso al ser un proyecto pequeño, se optó por integrarlos en el archivo principal.

