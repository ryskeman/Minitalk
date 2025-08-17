# Minitalk

Este proyecto es una implementación de un programa de comunicación cliente-servidor en C, utilizando el sistema de señales de UNIX para transmitir datos. El cliente y el servidor se comunican de forma asíncrona, donde el cliente envía un mensaje de texto que el servidor decodifica y muestra.

## Características Principales

-   **Comunicación Cliente-Servidor:** El cliente envía una cadena de caracteres al servidor a través de señales.
-   **Codificación de Bits:** La información se codifica bit a bit, representando cada bit con las señales `SIGUSR1` y `SIGUSR2`.
-   **Manejo de Señales:** El servidor utiliza `sigaction` para manejar de forma robusta las señales entrantes.
-   **Gestión de Memoria:** El servidor gestiona la memoria de forma dinámica (`malloc`, `free`) para recibir mensajes de cualquier tamaño.
-   **Robustez:** El código incluye manejo de errores para verificar la asignación de memoria y la correcta comunicación entre procesos.

## Cómo Usar

### Compilación

Clona el repositorio y usa `make` para compilar ambos programas:

```bash
git clone [https://github.com/](https://github.com/)[tu_usuario]/minitalk.git
cd minitalk
make

./server
Server PID: [PID_del_servidor]

EN OTRA TERMINAL:

./client [PID_del_servidor] "Hola mundo, esto es Minitalk!"

---
