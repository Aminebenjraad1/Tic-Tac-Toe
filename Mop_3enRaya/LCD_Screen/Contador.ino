#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

// Pines para Software SPI de la pantalla TFT
#define TFT_SCLK  10
#define TFT_MOSI  9
#define TFT_RST   8
#define TFT_DC    7
#define TFT_CS    6

// Pines para los botones (usa botones con resistencia pull-up interno)
#define BUTTON1_PIN 2  // Botón para incrementar el contador de la parte roja
#define BUTTON2_PIN 3  // Botón para incrementar el contador de la parte azul
#define BUTTON3_PIN 4

// Inicializar la pantalla ST7789 con Software SPI
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// Variables de contador
int contadorRojo = 0;
int contadorAzul = 0;

// Variables para comparar y refrescar la pantalla solo cuando cambian
int contadorRojoAnterior = -1;
int contadorAzulAnterior = -1;

// Coordenadas y dimensiones para actualizar la zona de cada contador
const int xTextoRojo = 50;
const int yTextoRojo = 50;
const int anchoTextoRojo = 60; 
const int altoTextoRojo = 30;

const int xTextoAzul =  tft.width()/2 + 50;
const int yTextoAzul = 50;
const int anchoTextoAzul = 60; 
const int altoTextoAzul = 30;

// Constante para indicar el límite de puntos para ganar
const int LIMITE_GANA = 3;

bool modoEmpate = false;
unsigned long tiempoEmpate = 0;

void setup() {
  Serial.begin(9600);

  // Inicializar la pantalla TFT (ajusta las dimensiones según tu display)
  tft.init(135, 240);
  tft.setRotation(3);
  
  // Configurar botones como entradas con pull-up interno
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  
  // Dibujar pantalla inicial con ambas zonas
  actualizarPantalla();
}

void loop() {
 if (digitalRead(BUTTON3_PIN) == LOW) {
    // Espera a que se suelte el botón para evitar rebotes
    while (digitalRead(BUTTON3_PIN) == LOW);
    delay(50);
    tft.fillScreen(ST77XX_BLACK);
    // Opcional: Puedes mostrar un mensaje en gris, por ejemplo:
    tft.setTextSize(3);
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(70, tft.height()/2 - 15);
    tft.print("Empate");
    // Espera unos instantes para visualizar
    delay(3000);
    // Al finalizar se vuelve a dibujar la pantalla inicial con los contadores
    actualizarPantalla();
    // Finalizamos esta iteración para evitar conflictos con otras actualizaciones
    return;
  }

  // Lectura y manejo del BOTÓN 1 (contador rojo)
  if (digitalRead(BUTTON1_PIN) == LOW) {
    contadorRojo++;
    Serial.print("Contador Rojo: ");
    Serial.println(contadorRojo);
    while (digitalRead(BUTTON1_PIN) == LOW); // Evitar rebotes
    delay(50);
  }
  
  // Lectura y manejo del BOTÓN 2 (contador azul)
  if (digitalRead(BUTTON2_PIN) == LOW) {
    contadorAzul++;
    Serial.print("Contador Azul: ");
    Serial.println(contadorAzul);
    while (digitalRead(BUTTON2_PIN) == LOW); // Evitar rebotes
    delay(50);
  }
  
  // Verificar si alguno de los contadores ha alcanzado o superado el límite
  if (contadorRojo >= LIMITE_GANA || contadorAzul >= LIMITE_GANA) {
    if (contadorRojo >= LIMITE_GANA) {
      // Rellena la pantalla de rojo si el contador rojo llega a 5
      tft.fillScreen(ST77XX_RED);
      tft.setTextSize(3);
      tft.setTextColor(ST77XX_WHITE);
      tft.setCursor(45, tft.height()/2 - 15);
      tft.print("Red Wins");
    } else if (contadorAzul >= LIMITE_GANA) {
      // Rellena la pantalla de azul si el contador azul llega a 5
      tft.fillScreen(ST77XX_BLUE);
      tft.setTextSize(3);
      tft.setTextColor(ST77XX_WHITE);
      tft.setCursor(45, tft.height()/2 - 15);
      tft.print("Blue Wins");
    }
    
    // Esperar unos segundos para mostrar el mensaje
    delay(3000);
    
    // Reiniciar contadores y variables de estado
    contadorRojo = 0;
    contadorAzul = 0;
    contadorRojoAnterior = -1;
    contadorAzulAnterior = -1;
    
    // Volver a dibujar la pantalla inicial dividida
    actualizarPantalla();
    
    // Finaliza esta iteración para evitar actualizar parcialmente la pantalla 
    return;
  }
  
  // Actualizar solo la parte del contador rojo si cambió
  if (contadorRojo != contadorRojoAnterior) {
    // Borrar la región donde se muestra el contador rojo (rellenándola con el color de fondo)
    tft.fillRect(xTextoRojo, yTextoRojo, anchoTextoRojo, altoTextoRojo, ST77XX_RED);
    // Dibujar el nuevo valor
    tft.setCursor(xTextoRojo, yTextoRojo);
    tft.setTextSize(4);
    tft.setTextColor(ST77XX_WHITE);
    tft.print(contadorRojo);
    contadorRojoAnterior = contadorRojo;
  }
  
  // Actualizar solo la parte del contador azul si cambió
  if (contadorAzul != contadorAzulAnterior) {
    // Borrar la región donde se muestra el contador azul
    tft.fillRect(xTextoAzul, yTextoAzul, anchoTextoAzul, altoTextoAzul, ST77XX_BLUE);
    // Dibujar el nuevo valor
    tft.setCursor(xTextoAzul, yTextoAzul);
    tft.setTextSize(4);
    tft.setTextColor(ST77XX_WHITE);
    tft.print(contadorAzul);
    contadorAzulAnterior = contadorAzul;
  }
  
  delay(10);  // Pequeño delay para estabilizar la lectura
}

void actualizarPantalla() {
  // Dividir la pantalla: mitad izquierda roja y mitad derecha azul
  int pantallaAncho = tft.width();
  int pantallaAlto  = tft.height();
  int mitadAncho = pantallaAncho / 2;
  
  tft.fillRect(0, 0, mitadAncho, pantallaAlto, ST77XX_RED);
  tft.fillRect(mitadAncho, 0, mitadAncho, pantallaAlto, ST77XX_BLUE);
  
  // Dibujar los contadores iniciales
  tft.setTextSize(4);
  tft.setTextColor(ST77XX_WHITE);
  
  tft.setCursor(xTextoRojo, yTextoRojo);
  tft.print(contadorRojo);
  
  tft.setCursor(xTextoAzul, yTextoAzul);
  tft.print(contadorAzul);
}
