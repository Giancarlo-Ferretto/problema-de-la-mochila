# Instrucciones para la ejecución

Para programar la solución se utilizó el lenguaje de programación C++, y el compilador g++ integrado al editor de código Visual Studio Code (VSC). En la carpeta "src" de este repositorio se encuentra un archivo "main.cpp", donde esta el código del algoritmo de búsqueda Best-First. Para correr este código con VSC y en Windows, se deben instalar las extensiones de C++, el compilador g++ y descargar MinGW-x64 (el instructivo completo se encuentra en https://code.visualstudio.com/docs/languages/cpp). Para correr el código en otro sistema operativo, visitar el siguiente link: https://code.visualstudio.com/docs/languages/cpp#_tutorials.

Completada la instalación, abrir el archivo main.cpp con VSC, hacer click derecho en el código y seleccionar Run Code o usando el atajo Ctrl + Alt + N.

# Problema de la mochila (knapsack problem)

En este taller se resolverá el conocido problema de la mochila. Este problema consiste en cargar diferentes objetos (referidos de aquí en adelante como items) a una mochila sin exceder su peso límite, con el objetivo de maximizar el valor total de los items guardados dentro de esta. Entre las variables del problema se encuentra una cantidad (n) de items, y cada uno tiene asociado un peso (weight) y asimismo un valor o precio (price). Los items almacenados en la mochila serán referidos como "x". La función a maximizar sería entonces la sumatoria del valor de los items almacenados en la mochila: Sum( price * x ). Por otro lado, la restricción es limita el peso de los items por la capacidad de la mochila: ( weight * x ) <= MAX_WEIGHT.

Este problema se define como un problema combinatorio de optimización, ya que existe una gran cantidad de combinaciones posibles entre los distintos items, siempre y cuando no se exceda la capacidad máxima de la mochila. Por ello ha sido caso de estudio desde su primer mención en 1897 por el matemático Tobias Dantzig, y se ha visto aplicado a otros problemas de optimización combinatoria como la compra de inversiones teniendo un presupuesto limitado o también el recorte más eficiente para disminuir el desecho de materias primas en industrias primarias como por ejemplo, la madera en la producción de tablas.

La complejidad del knapsack problem es lo que lo hace desafiante, puesto que corresponde a la clase de complejidad de tipo NP-completo, debido a que al definir arbitrariamente un conjunto S de combinaciones de items que satisfagan la capacidad de la mochila, no es posible determinar si esta es la mejor solución sin antes evaluar las otras combinaciones ((2^n) - 1) de items. 

Así han surgido desde su concepción varias soluciones, entre ellas la programación dinámica con el método de tabulado, o usando un algoritmo de búsqueda de tipo Greedy. Particularmente el último modela este problema usando la estructura de datos llamada grafo o árbol de búsqueda, y nuestra propuesta aborda el knapsack problem de la misma manera, pero utilizando un algoritmo de búsqueda llamado Best-First (BFS abreviado en inglés).

# Propuesta de solución

Como propuesta de solución del knapsack problem se implementó el algoritmo de búsqueda Best-First, que utiliza un árbol de búsqueda. Un árbol de búsqueda es una estructura de datos donde cada uno de los nodos (u hojas) del árbol corresponde a un estado, y estos representan el listado de acciones que fueron tomadas para llegar a ese estado. Las acciones en este problema simulan tomar un item y colocarlo en la mochila, por lo que cada estado contiene una lista de acciones, es decir, el orden en que los items se han puesto dentro de la mochila y el peso actual que tiene la mochila. El estado inicial se define como el estado donde la mochila se encuentra vacía y a medida que se coloca un nuevo item en la mochila, se transiciona a un nuevo estado hasta llegar a la máxima capacidad de la mochila, siendo este el estado final. 

Lo que caracteriza este tipo de búsqueda es que para decidir el siguiente estado, el algoritmo emplea una heurística. Como grupo de trabajo se definió la heurística como la razón entre el precio y el peso (heuristic_eval = price / value) de cada item. Mientras más alta sea esta razón, más prioridad tendrá ese estado para ser considerado para la siguiente transición. Los estados posibles son almacenados en una cola con prioridad, donde son ordenados por su evaluación heurística. En otras palabras, el algoritmo va a priorizar meter en la mochila los items que tienen un mayor valor y un menor peso.

Los resultados obtenidos por este algoritmo de búsqueda acreditan su efectividad, logrando capturar la mejor combinatoria posible de items en la mochila después de visitar un total de 154 estados cuando el dataset contaba con 10 items, obteniendo un tiempo de ejecución de 1.512 segundos. Cuando se aumentó la cantidad de items a 20 (y manteniendo la misma capacidad de la mochila), se obtuvo un tiempo de ejecución de 1.643 segundos, visitando un total de 4979 estados, evidenciando el gran aumento de nodos que debe rastrear el algoritmo cuando crece el dataset. Esto ilustra la desventaja de usar este algoritmo, si seguimos aumentando el dataset, eventualmente la máquina en que se ejecuta va a agotar la memoria disponible. Sin embargo, cuando se trata de un dataset reducido, el algoritmo de búsqueda Best-First encuentra la mejor solución de combinatoria satisfaciendo la restricción de capacidad de la mochila y maximizando el valor de los items en esta.

# Dataset

El dataset de prueba consiste en un arreglo estático de ítems de prueba. Estos declararon en el comienzo de la función main, para aquello se utilizó un arreglo de objetos de tipo Item llamado "test_items". Cada objeto de prueba se les define sus valores peso, precio y un nombre como constantes.

# Funciones Principales:

> list <Action> get_actions(State& state, Item items[])

Esta función recibe un puntero a un objeto del tipo State y un arreglo de tipo Item. Esta función inicializa una lista de acciones vacía “actions”, y después recorre cada elemento del arreglo items[], durante esta iteración mete en la mochila todos los items de la lista items del State. Luego se comprueba con is_valid_action( ) si todavía tiene espacio en la mochila para colocar un nuevo item. De ser posible colocar un nuevo item, lo agrega al final de la lista “actions”. Finalmente se retorna esta lista con todos los objetos que pueden ser guardados en la mochila por los hijos del State actual.

> State transition(State& state, Action& action)

Esta función recibe un puntero a un tipo State y un puntero a un tipo Action. Esta función recibe una acción y la agrega al estado actual en la pila de items, luego este nuevo estado es retornado. ¿Por qué se llama transition? Es una función intermedia que se realiza después de evaluar las condiciones para ingresar un objeto en la mochila y poder pasar de un estado a otro.
	
> int is_final_state(list<Action> actions)

Esta función recibe una lista de objetos tipo Action, en este caso, el listado de acciones contenidas en un State y retorna un valor numérico. Su funcionamiento es sencillo, es verificar si hay acciones disponibles, si retorna 1, se ha encontrado el estado final. De encontrar por lo menos una acción, retorna 0.

> float heuristic_eval(State& state)

Esta función recibe un objeto tipo State y retorna un valor numérico de tipo float. Esta función retorna la división entre el price y el weight. Esta es la función que usa la heurística que evalúa cada estado y dependiendo del valor obtenido en la heurística, lo ordena en la cola de prioridad. Los estados con mayor heuristic_eval( ) se ubican al comienzo de la cola con una mayor prioridad, y al final de la cola los que obtengan una evaluación menor.

> State best_first(State& initial_state, Item items[])

Esta función recibe el estado inicial y un arreglo de objetos del tipo Item que corresponde al dataset. Lo primero que hace es inicializar una cola de prioridad y define como función de comparación Compare( ) para la priorización de la cola, la que retorna un boolean TRUE si la cola está correctamente ordenada con los items de mayor prioridad al comienzo. Luego agrega a la cola el estado inicial con un push(), entrando a un ciclo iterativo que termina cuando se vacía la cola de prioridad. 
Este ciclo iterativo recoge y quita el State de mayor prioridad de la cola, recogiendo las acciones de este estado con get_actions( ) para comprobar si es el estado final. De no ser el estado final, se entra a la función transition(state, action), creando un nuevo State por cada acción posible y agregando estos hijos del State padre a la cola de prioridad, finalmente terminando el ciclo y comenzando desde el inicio del bucle. De lo contrario, si es el estado final, se retorna el final State y se imprime la cantidad de nodos visitados.

# Vídeo presentación
https://drive.google.com/file/d/1KJyt6AdRCM57bwu7XXcoXVf4eho8r49Q/view?usp=sharing
