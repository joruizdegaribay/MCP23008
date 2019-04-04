MCP23008 arduino library for MCP23008 (8bits I/O expander) in I2C mode
=====

Esta librería permite la gestión básica del expansor I2C de 8 bits MCP23008 de Microchip:
* configuración de las entradas y salidas.
* lectura del estado de los pines de entrada y salida.
* escritura del estaodo de los pines de salida.
* actividación de resistencia pull-up internas.
* gestión de interrupciones.

Para ello, la librería implementa la clase MCP23008, por lo que habrá que crear un objeto de esta clase para cada componebte MCP23008 conectado al bus I2C. La clase MCP23008 implementa los siguientes métodos:
* begin(addr), inicializa el objeto de tipo MCP23008 asignandole la dirección I2C del componente en el bus.
* pinMode(iomode), configura los 8 pines de E/S como entrada (1) o salida (0) por medio de un byte.
* pinMode(pin, [INPUT, OUTPUT, INPUT_PULLUP]), configura un pin concreto de E/S como entrada o salida, pudiendose activar directamente la resistencia pull-up en el caso de ser una entrada. 
* setPullup(iopullup), activda (1) o desactiva(0) las resistencias pull-up internal de los pines de E/S por medio de un byte.
* int read(), lee el estado (0 o 1) de los 8 pines de E/S por medio de un byte.
* int read(pin), lee el estado (LOW o HIGH) de un pin concreto de E/S.
* write(iovalues), escribe el estado en los 8 pines de E/S por medio de un byte.
* write(pin, [LOW, HIGH]), escribe el estado de un pin concreto de E/S.
* enableInterrupt(pin, [CHANGE, RISING, FALLING]), habilita y configura el modo de interrupción para un pin concreto de E/S.
* disableInterrupt(pin), deshabilita la interrupción para un pin concreto de E/S.
Nota: En las operaciones de escritura, sólo se actualizarán los pines que hayan sido conifigurados como salidas, manteniendose los valores de los pines configurados como entrada.

Para los métodos anteriores en los que se configura, lee o escribe por medio de un byte completo para los 8 pines de E/S del componente MCP23008, el pin0 se corresponde con el bit de menos peso del byte. Por ejemplo, para la función pinMode(iomode), pasando el valor literal 0xF0, se configurarán los pines 0, 1, 2 y 3 como salidas y los pines 4, 5, 6 y 7 como entradas.

Esta librería trae implementados los siguientes ejemplos (en todos ellos, la dirección I2C del componente MCP23008 es 0x27):
* button, lee el estado del pin 3 (configurado como entrada con resistencia pull-up) del componente MCP23008 y copia el estado en el LED del pin 13 del Arduino.
* toogle, hace un blink sobre un diodo LED conectado en el pin 6 (configurado como salida) del componente MCP23008.
* readinputs, lee el estado de los 8 pines de E/S (configurados como entradas con resistencias pull-up) del componente MCP23008 y manda su valor por el puerto serie en forma binaria (no muestra los 0's a la izquierda).
* interrupt, configura el pin 3 de E/S del componente MCP23008 como una entrada con interrupción por flanco ascendente. A cada interrupción, leída por el pin 0 del Arduino, cambia el estado del pin 6 (configurado como salida) del componente MCP23008.
Nota: En el caso de habilitar una interrupción externa de Arduino para detectar un evento en el componente MCP23008, no es posible acceder al componente MCP23008 por medio de los métodos anteriores por incompatibilidades propias de la plataforma Arduino.
