# Práctica 2 - Algorítmos Genéticos
### José Luis Fernández Aguilera
##### Puede seguir el desarrollo de esta práctica [en mi Gitlab](https://makefile.us.to/Okynos/Genetics)
Para la realización de esta práctica se han realizado varias implementaciones comenzando por las más sencillas e intuitivas pero que no resolvían el problema de manera adecuada hasta las citadas en la memoria con variación de los distintos parámetros para obtener una buena puntuación en el análisis QAP pasamos a detallar cada paso realizado en nuestra implementación como describe este breve índice:

* Primera implementación (estándar e intuición)
* Segunda implementación (estándar, Baldwin y Lamarck)
* Tercera implementación (operadores de cruce, selección y mutación específicos)
* Análisis de datos
* Problemas encontrados


### Primera implementación
En esta primera implementación se optó por el camino más sencillo y se incorporó a la implementación un sistema de evaluación estándar en la que lo único que se realiza es el cálculo del fitness del individuo a través de la matriz de pesos y de distancias.

A esta implementación se le incorporó un sistema de selección propio el cual trataba de elegir a los mejores individuos (la mitad mejor) y cruzarlos entre sí una única vez y en orden descendente, esto proporcionaba una selección pobre de las mejores soluciones dado que aunque siempre se escogían los mejores individuos no permitía la posibilidad de cruce de un padre bueno con varios menos o más buenos, por lo que se perdía una parte importante del objetivo que era minimizar el fitness y por lo tanto no se conseguían buenos resultados.

En cuanto a la implementación del cruce tambien se realizó de manera propia cruzando de manera alterna y sin repeticiones los genes de padre y madre este método producía hijos que no tenian apenas genes organizados y comunes de los padres, otro fallo de implementación que derivó en malos resultados del algoritmo de cruce.

Finalmente la mutación se implemento de manera totalmente arbitraria en la cual se escogían el número de individuos que mutarian, el número de genes que mutarían y el par de genes que iban a mutar, este método no era el idóneo dado que mutaba demasiadas veces y de manera muy agresiva lo que producía que buenos indivíduos o conjuntos de ellos se perdieran diendo lugar a peores soluciones.

En esta primera implementación los mejores resultados obtenidos para bur26a.dat eran de aproximadamente 5.800.000  que no estaba lejos del mejor fitness encontrado 5.426.670 pero aún así era un resultado bastante malo, es por ello que no se han registrado gráficas ni análisis de esta implementación dado los resultados que no eran muy relevantes para la práctica, se comenta en este documento a modo instructivo de algunas decisiones tomadas durante la realización de la práctica y que han tenido que ser modificadas en etapas posteriores.


### Segunda implamentación
En la segunda implementación realizada del algoritmo genético se incorporó las técnicas de evaluación Baldwiniana y Lamarckiana las cuales se basan en una evaluación herística de los individuos en busca de la mejor solución posible para nuestro problema, en nuestro caso con la implementación que teníamos anteriormente no se pudieron obtener mejores resultados dado que los operadores de selección, cruce y mutación no eran adecuados para estas implementaciones, incluso no eran adecuados para algunos casos en la evaluación estándar, es por ello que se modificaron los operadores para obtener mejores soluciones.

Los resultados en esta implementación empeoraron con respecto a la implementación anterior por lo que no se han incorporado datos de ello a este documento.


### Tercera implementación
En la tercera y definitiva implementación se han mejorado e incorporado todas las posibles mejoras de los operadores (específicos) para el problema de la evaluación mediante mecanismos como es el de Lamarck o Baldwin, es por ello que casi se ha tenido que reescribir la práctica de nuevo manteniendo la estructura, la inicialización y poco más, aún así esta implementación merece la pena dado que se han obtenido resultados óptimos en el caso de bur26a.dat o resultados muy cercanos al óptimo como puede ser 4.4820.538 (el mejor resultado obtenido hasta ahora) en el conjunto de datos tai256c.dat pasamos ahora a detallar los cambios y la implementación realizada en este caso.

El operador de cruce se ha adaptado y mejorado para producir unos cruces más eficientes y acordes con la herencia de padre y madre dado que en el método anterior se perdía parte de la esencia genética al cruzar alelos de padre y madre, en este caso se ha aplicado la técnica de cruce en un punto que oscila entre el principio y la mitad del individuo menos uno al elegir ese punto de cruce se copia a partir de ahí la mitad de los genes del padre en el hijo y se continúa por la cola copiando en orden y sin repetidos los alelos de la madre, lo que da lugar a un cruce de orden que genera buenos resultados en la población.

En cuanto al operador de selección se ha decidido remodelarlo y aplicar una selección por torneo clásico en el que se escogen cinco individuos al azar y se elige al mejor de ellos que será el padre del nuevo individuo a continuación se repite este proceso para elegir a la madre del individuo y una vez elegidos se cruzan por el método anteriormente comentado, en cuanto al método de herencia o de reemplazo de la generación anterior se han implementado dos variantes, la primera en la que toda la población era sustituida por sus descendientes de igual tamaño y la segunda implementación que sustituye a toda la población anterior salvo los dos mejores para que se preserve el mejor valor de la generación anterior, en ambas implementaciones se han obtenido buenos resultados.

En cuanto al operador de mutación se han implementado dos variantes de nuevo para probar los posibles efectos sobre la solución que pueden tener ambos, en el primer método se recorren todos los individuos y todos sus genes y para cada gen de un individuo se genera un número aleatorio desde uno al número de genes, si el número aleatorio coincidiera con el alelo se cambiaría éste por otro alelo del mismo individuo seleccionado aleatoriamente (método de intercambio), esa solución produce buenos resultados y modificandolo se ha probado aumentando la probabilidad de mutación para comprobar si haciendo unas mutaciones más sería posible mejorar el resultado, pero no se han obtenido resultados muy diferenciales pero si algo de mejora en el caso de mayor probabilidad de mutación la cual es de un total de 2/N siendo N el número de genes de la población.


### Análisis de datos
En este apartado vamos a detallar los resultados obtenidos sobre los diferentes conjuntos de prueba que hemos analizado, para ello mostramos diferentes gráficas que muestran el decrecimiento del fitness por generación y por tipo de evaluación.

![Gráfico bur26a estandar](http://makefile.es/master/geneticos/bur26a_estandar.png "bur26a 100 individuos")

![Gráfico bur26a baldwin](http://makefile.es/master/geneticos/bur26a_baldwin.png "bur26a 100 individuos")

![Gráfico bur26a lamarck](http://makefile.es/master/geneticos/bur26a_lamarck.png "bur26a 100 individuos")

En este caso podemos observar los tres tipos de evaluaciones que se han realizado sobre el conjunto de datos bur26a observandose en el caso de Lamarck que se obtiene el óptimo de este problema, los demás obtiene soluciones aceptables pero más alejadas del óptimo.

![Gráfico chr15a estandar](http://makefile.es/master/geneticos/chr15a_estandar.png "chr15a 100 individuos")

![Gráfico chr15a baldwin](http://makefile.es/master/geneticos/chr15a_baldwin.png "chr15a 100 individuos")

![Gráfico chr15a lamarck](http://makefile.es/master/geneticos/chr15a_lamarck.png "chr15a 100 individuos")

En cuanto al chr15a se puede observar una tendencia un poco diferente y más alejada del valor óptimo pero aún así en el método de evaluación de Lamarck se obtuvieron mejores resultados.

![Gráfico lipa50b estandar](http://makefile.es/master/geneticos/lipa50b_estandar.png "lipa50b 100 individuos")

![Gráfico lipa50b baldwin](http://makefile.es/master/geneticos/lipa50b_baldwin.png "lipa50b 100 individuos")

![Gráfico lipa50b lamarck](http://makefile.es/master/geneticos/lipa50b_lamarck.png "lipa50b 100 individuos")

En este caso al igual que en bur26a obtenemos un resultado que es el óptimo en Lamarck mientras que en los otros obtenemos resultados algo inferiores.

![Gráfico nug30 estandar](http://makefile.es/master/geneticos/nug30_estandar.png "nug30 100 individuos")

![Gráfico nug30 baldwin](http://makefile.es/master/geneticos/nug30_baldwin.png "nug30 100 individuos")

![Gráfico nug30 lamarck](http://makefile.es/master/geneticos/nug30_lamarck.png "nug30 100 individuos")

En el caso de nug se repite lo mismo que en bur26a y lipa50b obtenemos el óptimo en Lamarck lo que nos deja muy buen sabor de boca sobre nuestra implementación de Lamarck y los operadores asociados que hemos comentado con anterioridad.

![Gráfico tai256c estandar](http://makefile.es/master/geneticos/tai256c_estandar.png "tai256c 50 individuos")

![Gráfico tai256c baldwin](http://makefile.es/master/geneticos/tai256c_baldwin.png "tai256c 50 individuos")

![Gráfico tai256c lamarck](http://makefile.es/master/geneticos/tai256c_lamarck.png "tai256c 50 individuos")

En este caso el cual es el más relevante de la práctica podemos ver como el método de Lamarck de nuevo obtiene los mejores resultados en cuanto a valor mínimo y velocidad de convergencia hacia el menor fitness aunque en este caso no se ha podido obtener el mejor valor calculado se pueden obtener valores de 44.840.310 lo que nos deja muy cerca de la mejor permutación encontrada, se han obtenido otros valores cercanos pero mayores que el mencionado.


### Problemas encontrados
Algunos de los problemas encontrados durante la implementación de los algoritmos son los siguientes:

* Dificultad para calcular correctamente o comprobar el fitness de cada individuo, en este caso se daba por válida una solución que en muchas ocasiones estaba adulterada por algún cambio en el individuo o el fitness que hacía que al comprobar la permutación que proporcionaba la mejor solución esta produjese un valor de fitness diferente lo que indicaba que el fitness asociado a esa permutación no era correcto (al menos en Lamarck y en el estándar).
* Problemas de excesiva o poca mutación, se han producido muchos fallos o desajustes debido a la relación entre exploración explotación debido a que en algunos momentos sobre todo en la primera implementación se mutaba demasiado y en algunos momentos de la tercera implementación se mutaba muy poco es por ello que se debe llegar a un equilibrio.
* Problemas con el cruce, durante el cruce aunque no es implícito de los algoritmos genéticos se realizaba de manera errónea debido por una parte al operador utilizado y por otro lado a la copia entre matrices controlando los límites y los valores no repetidos de los mismos lo que ha ocasionado algunos inconvenientes.
* Se han encontrado dificultades en algunas variables asociadas al 2opt dado que no se ajustaba de manera adecuada el fitness o no se correspondía al individuo que estaba en ejecución en ese momento lo que producía desajustes en el fitness.
