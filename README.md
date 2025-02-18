# 🎮 3 en Raya MOP  

**3 en Raya MOP** es una versión electrónica del clásico juego **Tres en Raya**, que incorpora **LEDs RGB, una pantalla TFT, botones físicos y sonido**. Dos jugadores pueden enfrentarse, y el sistema **gestiona automáticamente los turnos y la puntuación**, mostrando los resultados en una pantalla y proporcionando retroalimentación con luces y sonido.

---

## 📌 Características  

- **Pantalla TFT ST7789** para mostrar la puntuación y el estado del juego.  
- **72 LEDs RGB** controlados con `FastLED`, para iluminar la placa del juego y resaltar las partidas ganadas.  
- **Buzzer** que emite sonidos al presionar botones y al detectar un ganador.  
- **9 botones físicos** conectados al microcontrolador para interactuar con el juego.  
- **Expansor de pines MCP23X17** para manejar más entradas/salidas sin ocupar todos los pines de Arduino.  
- **Sistema automático de turnos** y detección de victorias.  

---

## 🤖 ¿Qué es el ATmega328P?

El **ATmega328P** es un microcontrolador de 8 bits de la familia AVR, fabricado por Atmel (ahora parte de Microchip). Es el corazón de muchas placas de desarrollo, incluido el popular **Arduino UNO**. Entre sus características destacan:

![](https://electrojoan.com/wp-content/uploads/2014/01/atmega328p.jpg)

- **Arquitectura RISC:** Permite ejecutar instrucciones de manera eficiente.
- **32 KB de memoria flash:** Utilizados para almacenar el programa.
- **2 KB de SRAM:** Para el manejo de variables durante la ejecución.
- **1 KB de EEPROM:** Permite guardar datos de forma no volátil.
- **Velocidad de reloj de 16 MHz:** Brinda un equilibrio entre rendimiento y consumo de energía.
- **Amplia cantidad de pines de entrada/salida (I/O):** Facilita la conexión de sensores, LEDs, botones y otros periféricos.

En este proyecto, el **ATmega328P** (con bootloader) se encarga de gestionar la pantalla TFT, los botones físicos, los LEDs RGB y el buzzer, coordinando la lógica del juego **3 en Raya MOP**.

---

## 🏭 Fabricación de la PCB con LPKF  

Para la fabricación de la **PCB (Placa de Circuito Impreso)**, se ha utilizado la **máquina LPKF**, un sistema de **fresado y grabado de PCBs**.

### 🔹 ¿Qué es la LPKF?  
La **LPKF (Laser & Electronics)** es una máquina especializada en la creación de **prototipos de PCB** mediante **fresado mecánico**. Se utiliza para eliminar el cobre sobrante de una placa y dejar solo los caminos eléctricos que interconectan los componentes.

![](https://www.lpkf.com/fileadmin/mediafiles/_processed_/0/8/csm_lpkf-protomat-s64-frontview_58078250c5.jpg)

### 🔹 Proceso de fabricación con LPKF:  
1. **Exportación de archivos Gerber**, que contienen la información de las pistas y perforaciones.  
2. **Carga del diseño en la LPKF**, donde se ajustan la profundidad y velocidad del fresado.  
3. **Fresado de la PCB**, eliminando el cobre innecesario y dejando solo las pistas.  
4. **Perforación** para insertar los componentes electrónicos.  
5. **Soldadura de los componentes** y prueba final.


La LPKF permitió fabricar un prototipo funcional de la placa sin necesidad de enviarlo a una fábrica externa, agilizando el desarrollo.

---

## 📺 Explicación de la Pantalla TFT ST7789  

![](https://www.icstation.com/images/uploads/14588_4.jpg)

El código usa la librería **Adafruit ST7789** para manejar la pantalla TFT.  

- **Se configura en el `setup()`** estableciendo la resolución, la orientación y limpiando la pantalla.  
- **Se actualiza la pantalla en cada turno**, mostrando la puntuación de cada jugador.  
- **Cuando un jugador gana, la pantalla muestra un mensaje indicando el ganador**.  

El objetivo principal de la pantalla es **mostrar el estado actual del juego, incluyendo las puntuaciones y el mensaje de victoria**.

---

## 💡 Explicación de la Placa de LEDs y Conexión  

El juego cuenta con una **placa de circuito impreso (PCB) personalizada** que contiene **72 LEDs RGB WS2812B** organizados en el tablero de juego.  

![](https://keebd.com/cdn/shop/products/WS2812B-RGB-LED-KEEBD-1664353665.jpg?v=1664353667)

- **Se han utilizado LEDs WS2812B, similares a los de las tiras LED RGB direccionables**.  
- **Cada LED se conecta en serie**, formando una única línea de datos.  
- **El control se realiza a través de un solo pin del Arduino**, que envía señales a toda la cadena de LEDs.  

### 🔌 ¿Cómo están conectados los LEDs?  

Los **WS2812B** son LEDs **direccionables**, lo que significa que cada uno tiene su propio chip de control y pueden ser controlados individualmente con una única línea de datos.  

![](https://elecfreaks.com/wp-content/uploads/content/093017_0609_GettoKnowWS3.jpg)

| LED WS2812B | Conexión en la PCB |
|-------------|-------------------|
| **VCC** | 5V |
| **GND** | GND |
| **DIN (Data In)** | Conectado a Arduino (Pin 3) |
| **DOUT (Data Out)** | Conectado al siguiente LED |

---

## 📋 Lista de Materiales  

| Cantidad | Descripción |
|----------|------------|
| 1 | ATmega328P with Bootloader |
| 1 | Pantalla TFT ST7789 |
| 72 | LED RGB WS2812B de 5 mm |
| 9 | Botones táctiles SPST |
| 1 | Expansor de pines MCP23X17 |
| 1 | Regulador de voltaje 7805 de 5 V |
| 2 | 28-pin IC Sockets |
| 1 | FTDI USB to Serial Converter |
| 1 | Hookup Wire |
| 1 | PCB personalizada (LPKF) |

---

## 🎮 Modo de Uso  

![](https://curator-production.s3.us.cloud-object-storage.appdomain.cloud/uploads/md5-10bc4d3b74451c4a46ff626c5624482f-course_card.png)

1. **Encender el dispositivo.**  
2. Los jugadores toman turnos presionando los botones correspondientes.  
3. La pantalla muestra el estado actual y la puntuación.  
4. **Los LEDs se iluminan según las jugadas realizadas.**  
5. El buzzer emite sonidos en cada jugada y cuando hay un ganador.  
6. Para reiniciar el juego, se debe apagar y encender el sistema.

---

## 🚀 Mejoras Futuras  

- Agregar efectos de sonido más variados.  
- Habilitar música de fondo para mayor inmersión.  
- Integrar conectividad inalámbrica para una versión en línea del juego.  
- Mejorar la interfaz de la pantalla con animaciones dinámicas.  
