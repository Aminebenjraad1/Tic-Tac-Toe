#include <FastLED.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_MCP23X17.h>

#define NUM_LEDS  72

#define LED_PIN   3
#define BOT1 4
#define BOT2 5
#define BOT3 6
#define BOT4 7
#define BOT5 8
#define BOT6 9
#define BOT7 10
#define BOT8 11
#define BOT9 12

#define TFT_SCLK 5
#define TFT_MOSI 4
#define TFT_RST 3
#define TFT_DC 2
#define TFT_CS 1

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
Adafruit_MCP23X17 mcp;

int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
int val5 = 0;
int val6 = 0;
int val7 = 0;
int val8 = 0;
int val9 = 0;

const int buzzerPin =2;
const int note1 =294;
const int note2 =100;
bool buttonState = HIGH;     
bool lastButtonState = HIGH; 

CRGB leds[NUM_LEDS];
int Jugador = 1;

int BOT1J = 0;
int BOT2J = 0;
int BOT3J = 0;
int BOT4J = 0;
int BOT5J = 0;
int BOT6J = 0;
int BOT7J = 0;
int BOT8J = 0;
int BOT9J = 0;

int contadorRojo = 0;
int contadorAzul = 0;

int contadorRojoAnterior = -1;
int contadorAzulAnterior = -1;

const int xTextoRojo = 50;
const int yTextoRojo = 50;
const int anchoTextoRojo = 60; 
const int altoTextoRojo = 30;

const int xTextoAzul =  tft.width()/2 + 50;
const int yTextoAzul = 50;
const int anchoTextoAzul = 60; 
const int altoTextoAzul = 30;

const int LIMITE_GANA = 3;

bool modoEmpate = false;
unsigned long tiempoEmpate = 0;

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(200);
  tft.init(135, 240);
  tft.setRotation(3);
  mcp.begin_I2C();
  pinMode(BOT1, INPUT);
  pinMode(BOT2, INPUT);
  pinMode(BOT3, INPUT);
  pinMode(BOT4, INPUT);
  pinMode(BOT5, INPUT);
  pinMode(BOT6, INPUT);
  pinMode(BOT7, INPUT);
  pinMode(BOT8, INPUT);
  pinMode(BOT9, INPUT);
  mcp.pinMode(TFT_SCLK, OUTPUT);
  mcp.pinMode(TFT_MOSI, OUTPUT);
  mcp.pinMode(TFT_RST, OUTPUT);
  mcp.pinMode(TFT_DC, OUTPUT);
  mcp.pinMode(TFT_CS, OUTPUT);
  pinMode(buzzerPin, OUTPUT);        // Configura el pin del buzzer como salida
  fill_solid(&leds[0], 72, CRGB::Black);
  Todo_a_0();
  Jugador = 1;
  FastLED.show();
  actualizarPantalla();
  noTone(buzzerPin); 
}


void loop() {
  
  Jugador_V();
  Jugador_A();
 
  H_D();
  H_M();
  H_U();
  
  V_D();
  V_M();
  V_I();

  L_D();
  L_I();

  EMPATE();
  
  WinR();
  WinB();
}



void H_D() {
  /*
    |0|  |0|  |0| 
    |0|  |0|  |0|
    |x|--|x|--|x|
  */
  if (BOT1J == 2 && BOT2J == 2 && BOT3J == 2)  {
  Abajo_I_B();
  Abajo_M_B();
  Abajo_D_B();   
  tone(buzzerPin, note2);
  delay(150);  
  noTone(buzzerPin); 
  delay(250);

  Abajo_I_N();
  Abajo_M_N();
  Abajo_D_N();         
  tone(buzzerPin, note1);
  delay(150);  
  noTone(buzzerPin); 
  delay(250);

  Abajo_I_B();
  Abajo_M_B();
  Abajo_D_B();  
  tone(buzzerPin, note2);
  delay(150);  
  noTone(buzzerPin); 
  delay(250);

  Abajo_I_N();
  Abajo_M_N();
  Abajo_D_N();         
  tone(buzzerPin, note1);
  delay(150); 
  noTone(buzzerPin); 
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  tone(buzzerPin, note2);
  delay(150);  
  noTone(buzzerPin); 
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  Todo_a_0();
  Jugador = 1;
  FastLED.show();
  contadorAzul++;
  }
  if (BOT1J == 1 && BOT2J == 1 && BOT3J == 1)  {
  Abajo_I_R();
  Abajo_M_R();
  Abajo_D_R();
  tone(buzzerPin, note2);
  delay(150);  
  noTone(buzzerPin);  
  delay(250);

  Abajo_I_N();
  Abajo_M_N();
  Abajo_D_N();
  tone(buzzerPin, note1);
  delay(150); 
  noTone(buzzerPin); 
  delay(250);

  Abajo_I_R();
  Abajo_M_R();
  Abajo_D_R();
  tone(buzzerPin, note2);
  delay(150);  
  noTone(buzzerPin); 
  delay(250);

  Abajo_I_N();
  Abajo_M_N();
  Abajo_D_N();
  tone(buzzerPin, note1);
  delay(150);
  noTone(buzzerPin); 
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Red);
  tone(buzzerPin, note2);
  delay(150);
  noTone(buzzerPin); 
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  Todo_a_0();
  Jugador = 1;
  FastLED.show();
  contadorRojo++;
  }
}




void H_M() {
  /*
    |0|  |0|  |0|
    |x|--|x|--|x|
    |0|  |0|  |0|
  */

 if (BOT4J == 2 && BOT5J == 2 && BOT6J == 2)  {
  Medio_I_B();
  Medio_M_B();
  Medio_D_B();
  tone(buzzerPin, note2);
  delay(150);  
  noTone(buzzerPin); 
  delay(250);

  Medio_I_N();
  Medio_M_N();
  Medio_D_N();    
  tone(buzzerPin, note1);
  delay(150); 
  noTone(buzzerPin);  
  delay(250);

  Medio_I_B();
  Medio_M_B();
  Medio_D_B();
  tone(buzzerPin, note2);
  delay(150);  
  noTone(buzzerPin);
  delay(250);

  Medio_I_N();
  Medio_M_N();
  Medio_D_N();
  tone(buzzerPin, note1);
  delay(150); 
  noTone(buzzerPin); 
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  tone(buzzerPin, note2);
  delay(150); 
  noTone(buzzerPin); 
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  Todo_a_0();
  Jugador = 1;
  FastLED.show();
  contadorAzul++;
  }
 if (BOT4J == 1 && BOT5J == 1 && BOT6J == 1)  {
  Medio_I_R();
  Medio_M_R();
  Medio_D_R();
  tone(buzzerPin, note2);
  delay(150);
  noTone(buzzerPin); 
  delay(250);

  Medio_I_N();
  Medio_M_N();
  Medio_D_N();
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  Medio_I_R();
  Medio_M_R();
  Medio_D_R();
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  Medio_I_N();
  Medio_M_N();
  Medio_D_N();
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Red);
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  Todo_a_0();
  Jugador = 1;
  FastLED.show();
  contadorRojo++;
  }
}




void H_U() {
  /*
    |x|--|x|--|x| 
    |0|  |0|  |0|
    |0|  |0|  |0|
  */
  if (BOT7J == 2 && BOT8J == 2 && BOT9J == 2)  {
  Arriva_I_B();
  Arriva_M_B();
  Arriva_D_B();
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  Arriva_I_N();
  Arriva_M_N();
  Arriva_D_N();
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  Arriva_I_B();
  Arriva_M_B();
  Arriva_D_B();
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  Arriva_I_N();
  Arriva_M_N();
  Arriva_D_N();
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  
  Todo_a_0();
  Jugador = 1;
  FastLED.show();
  contadorAzul++;
  }
 if (BOT7J == 1 && BOT8J == 1 && BOT9J == 1)  {
  Arriva_I_R();
  Arriva_M_R();
  Arriva_D_R();
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  Arriva_I_N();
  Arriva_M_N();
  Arriva_D_N();
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  Arriva_I_R();
  Arriva_M_R();
  Arriva_D_R();
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  Arriva_I_N();
  Arriva_M_N();
  Arriva_D_N();
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Red);
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  Todo_a_0();
  Jugador = 1;
  FastLED.show();
  contadorRojo++;
  }
}





void V_D() {
  /*
    |0|  |0|  |x|
    |0|  |0|  |x|
    |0|  |0|  |x|
  */
  if (BOT3J == 2 && BOT4J == 2 && BOT9J == 2)  {
  fill_solid(&leds[48], 24, CRGB::Blue);
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(&leds[48], 24, CRGB::Black);
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(&leds[48], 24, CRGB::Blue);
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(&leds[48], 24, CRGB::Black);
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  Todo_a_0();
  Jugador = 1;
  FastLED.show();
  contadorAzul++;
  }
  if (BOT3J == 1 && BOT4J == 1 && BOT9J == 1)  {
  fill_solid(&leds[48], 24, CRGB::Red);
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(&leds[48], 24, CRGB::Black);
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(&leds[48], 24, CRGB::Red);
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(&leds[48], 24, CRGB::Black);
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  Todo_a_0();
  Jugador = 1;
  FastLED.show();
  contadorRojo++;
  }
}





void V_M() {
  /*
    |0|  |x|  |0|
    |0|  |x|  |0|
    |0|  |x|  |0|
  */
  if (BOT2J == 2 && BOT5J == 2 && BOT8J == 2)  {
  fill_solid(&leds[24], 24, CRGB::Blue);
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(&leds[24], 24, CRGB::Black);
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(&leds[24], 24, CRGB::Blue);
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(&leds[24], 24, CRGB::Black);
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  Todo_a_0();
  Jugador = 1;
  FastLED.show();
  contadorAzul++;
  }
 if (BOT2J == 1 && BOT5J == 1 && BOT8J == 1)  {
  fill_solid(&leds[24], 24, CRGB::Red);
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(&leds[24], 24, CRGB::Black);
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(&leds[24], 24, CRGB::Red);
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(&leds[24], 24, CRGB::Black);
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  Todo_a_0();
  Jugador = 1;
  FastLED.show();
  contadorRojo++;
  }
}




void V_I() {
  /*
    |x|  |0|  |0|
    |x|  |0|  |0|
    |x|  |0|  |0|
  */
  if (BOT1J == 2 && BOT6J == 2 && BOT7J == 2)  {
  fill_solid(&leds[0], 24, CRGB::Blue);
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(&leds[0], 24, CRGB::Black);
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(&leds[0], 24, CRGB::Blue);
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(&leds[0], 24, CRGB::Black);
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  Todo_a_0();
  Jugador = 1;
  FastLED.show();
  contadorAzul++;
  }
  if (BOT1J == 1 && BOT6J == 1 && BOT7J == 1)  {
  fill_solid(&leds[0], 24, CRGB::Red);
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(&leds[0], 24, CRGB::Black);
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(&leds[0], 24, CRGB::Red);
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(&leds[0], 24, CRGB::Black);
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  Todo_a_0();
  Jugador = 1;
  FastLED.show();
  contadorRojo++;
  }
}


void L_D() {
  /*
    |0|  |0| -|x|
    |0| -|x|- |0|
    |x|- |0|  |0|
  */
  if (BOT1J == 2 && BOT5J == 2 && BOT9J == 2)  {
  Abajo_I_B();
  Medio_M_B();
  Arriva_D_B();
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  Abajo_I_N();
  Medio_M_N();
  Arriva_D_N();
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  Abajo_I_B();
  Medio_M_B();
  Arriva_D_B();
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  Abajo_I_N();
  Medio_M_N();
  Arriva_D_N();
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  Todo_a_0();
  Jugador = 1;
  FastLED.show();
  contadorAzul++;
  }
  if (BOT1J == 1 && BOT5J == 1 && BOT9J == 1)  {
  Abajo_I_R();
  Medio_M_R();
  Arriva_D_R();
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  Abajo_I_N();
  Medio_M_N();
  Arriva_D_N();
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  Abajo_I_R();
  Medio_M_R();
  Arriva_D_R();
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  Abajo_I_N();
  Medio_M_N();
  Arriva_D_N();
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  Todo_a_0();
  Jugador = 1;
  FastLED.show();
  contadorRojo++;
  }
}




void L_I() {
  /*
    |x|- |0|  |0|
    |0| -|x|- |0|
    |0|  |0| -|x|
  */
  if (BOT3J == 2 && BOT5J == 2 && BOT7J == 2)  {
  Arriva_I_B();
  Medio_M_B();
  Abajo_D_B();
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  Arriva_I_N();
  Medio_M_N();
  Abajo_D_N();
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  Arriva_I_B();
  Medio_M_B();
  Abajo_D_B();
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  Arriva_I_N();
  Medio_M_N();
  Abajo_D_N();
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  Todo_a_0();
  Jugador = 1;
  FastLED.show();
  contadorAzul++;
  }
  if (BOT3J == 1 && BOT5J == 1 && BOT7J == 1)  {
  Arriva_I_R();
  Medio_M_R();
  Abajo_D_R();
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  Arriva_I_N();
  Medio_M_N();
  Abajo_D_N();
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  Arriva_I_R();
  Medio_M_R();
  Abajo_D_R();
  tone(buzzerPin, note2);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  Arriva_I_N();
  Medio_M_N();
  Abajo_D_N();
  tone(buzzerPin, note1);
  delay(150);  // Duración del tono
  noTone(buzzerPin);  // Apagar el tono
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  Todo_a_0();
  Jugador = 1;
  FastLED.show();
  contadorRojo++;
  }
}




void Jugador_V(){

 if (Jugador == 2){

    if (digitalRead(BOT1) == LOW && BOT1J == 0)
  {
    Abajo_I_R();
    val1 = 1;
    Jugador = 1;
    BOT1J = 1;
    tone(buzzerPin, note1);
    delay(50);  // Duración del tono
    noTone(buzzerPin);  // Apagar el tono
  }


    if (digitalRead(BOT2) == LOW && BOT2J == 0)
  {
    Abajo_M_R();
    val2 = 1;
    Jugador = 1;
    BOT2J = 1;
    tone(buzzerPin, note1);
    delay(50);  // Duración del tono
    noTone(buzzerPin);  // Apagar el tono
  }


    if (digitalRead(BOT3) == LOW && BOT3J == 0)
  {
    Abajo_D_R();
    val3 = 1;
    Jugador = 1;
    BOT3J = 1;
    tone(buzzerPin, note1);
    delay(50);  // Duración del tono
    noTone(buzzerPin);  // Apagar el tono
  }


    if (digitalRead(BOT4) == LOW && BOT4J == 0)
  {
    Medio_I_R();
    val4 = 1;
    Jugador = 1;
    BOT4J = 1;
    tone(buzzerPin, note1);
    delay(50);  // Duración del tono
    noTone(buzzerPin);  // Apagar el tono
  }


    if (digitalRead(BOT5) == LOW && BOT5J == 0)
  {
    Medio_M_R();
    val5 = 1;
    Jugador = 1;
    BOT5J = 1;
    tone(buzzerPin, note1);
    delay(50);  // Duración del tono
    noTone(buzzerPin);  // Apagar el tono
  }


    if (digitalRead(BOT6) == LOW && BOT6J == 0)
  {
    Medio_D_R();
    val6 = 1;
    Jugador = 1;
    BOT6J = 1;
    tone(buzzerPin, note1);
    delay(50);  // Duración del tono
    noTone(buzzerPin);  // Apagar el tono
  }


    if (digitalRead(BOT7) == LOW && BOT7J == 0)
  {
    Arriva_I_R();
    val7 = 1;
    Jugador = 1;
    BOT7J = 1;
    tone(buzzerPin, note1);
    delay(50);  // Duración del tono
    noTone(buzzerPin);  // Apagar el tono
  }


    if (digitalRead(BOT8) == LOW && BOT8J == 0)
  {
    Arriva_M_R();
    val8 = 1;
    Jugador = 1;
    BOT8J = 1;
    tone(buzzerPin, note1);
    delay(50);  // Duración del tono
    noTone(buzzerPin);  // Apagar el tono
  }


    if (digitalRead(BOT9) == LOW && BOT9J == 0)
  {
    Arriva_D_R();
    val9 = 1;
    Jugador = 1;
    BOT9J = 1;
    tone(buzzerPin, note1);
    delay(50);  // Duración del tono
    noTone(buzzerPin);  // Apagar el tono
  }
 }
}




void Jugador_A(){

  if (Jugador == 1){
  if (digitalRead(BOT1) == LOW && BOT1J == 0)
    {
      Abajo_I_B();
      val1 = 1;
      Jugador = 2;
      BOT1J = 2;
      tone(buzzerPin, note1);
      delay(50);  // Duración del tono
      noTone(buzzerPin);  // Apagar el tono
    }

  if (digitalRead(BOT2) == LOW && BOT2J == 0)
    {
      Abajo_M_B();
      val2 = 1;
      Jugador = 2;
      BOT2J = 2;
      tone(buzzerPin, note1);
      delay(50);  // Duración del tono
      noTone(buzzerPin);  // Apagar el tono
    }

    if (digitalRead(BOT3) == LOW && BOT3J == 0)
  {
    Abajo_D_B();
    val3 = 1;
    Jugador = 2;
    BOT3J = 2;
    tone(buzzerPin, note1);
    delay(50);  // Duración del tono
    noTone(buzzerPin);  // Apagar el tono
  }

    if (digitalRead(BOT4) == LOW && BOT4J == 0)
  {
    Medio_I_B();
    val4 = 1;
    Jugador = 2;
    BOT4J = 2;
    tone(buzzerPin, note1);
    delay(50);  // Duración del tono
    noTone(buzzerPin);  // Apagar el tono
  }


    if (digitalRead(BOT5) == LOW && BOT5J == 0)
  {
    Medio_M_B();
    val5 = 1;
    Jugador = 2;
    BOT5J = 2;
    tone(buzzerPin, note1);
    delay(50);  // Duración del tono
    noTone(buzzerPin);  // Apagar el tono
  }


    if (digitalRead(BOT6) == LOW && BOT6J == 0)
  {
    Medio_D_B();
    val6 = 1;
    Jugador = 2;
    BOT6J = 2;
    tone(buzzerPin, note1);
    delay(50);  // Duración del tono
    noTone(buzzerPin);  // Apagar el tono
  }


    if (digitalRead(BOT7) == LOW && BOT7J == 0)
  {
    Arriva_I_B();
    val7 = 1;
    Jugador = 2;
    BOT7J = 2;
    tone(buzzerPin, note1);
    delay(50);  // Duración del tono
    noTone(buzzerPin);  // Apagar el tono
  }


    if (digitalRead(BOT8) == LOW && BOT8J == 0)
  {
    Arriva_M_B();
    val8 = 1;
    Jugador = 2;
    BOT8J = 2;
    tone(buzzerPin, note1);
    delay(50);  // Duración del tono
    noTone(buzzerPin);  // Apagar el tono
  }


    if (digitalRead(BOT9) == LOW && BOT9J == 0)
  {
    Arriva_D_B();
    val9 = 1;
    Jugador = 2;
    BOT9J = 2;
    tone(buzzerPin, note1);
    delay(50);  // Duración del tono
    noTone(buzzerPin);  // Apagar el tono
  }
 }
}



void EMPATE() 
{
 if (val1 == 1 && val2 == 1 && val3 == 1 && val4 == 1 && val5 == 1 && val6 == 1 && val7 == 1 && val8 == 1 && val9 == 1){
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(250);
  fill_solid(leds, NUM_LEDS, CRGB::White);
  FastLED.show();
  delay(250);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(250);
  fill_solid(leds, NUM_LEDS, CRGB::White);
  FastLED.show();
  delay(250);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  Todo_a_0();
  Jugador = 1;
  FastLED.show();
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
 }
}

  void WinR(){
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
  delay(10);  // Pequeño delay para estabilizar la lectura
 }

void WinB(){
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
//////////////////////////////////////////////
  void Arriva_I_B() {
  leds[1] = CRGB::Blue;
  fill_solid(&leds[13], 2, CRGB::Blue);
  leds[16] = CRGB::Blue;
  FastLED.show();
  }

  void Arriva_M_B() {
  leds[31] = CRGB::Blue;
  fill_solid(&leds[33], 2, CRGB::Blue);
  leds[46] = CRGB::Blue;
  FastLED.show();
  }

  void Arriva_D_B() {
  leds[49] = CRGB::Blue;
  fill_solid(&leds[61], 2, CRGB::Blue);
  leds[64] = CRGB::Blue;
  FastLED.show();
  }




  void Arriva_I_R() {
  leds[0] = CRGB::Red;
  leds[2] = CRGB::Red;
  leds[15] = CRGB::Red;
  leds[17] = CRGB::Red;
  FastLED.show();
  }

  void Arriva_M_R() {
  leds[30] = CRGB::Red;
  leds[32] = CRGB::Red;
  leds[47] = CRGB::Red;
  leds[45] = CRGB::Red;
  FastLED.show();
  }

  void Arriva_D_R() {
  leds[48] = CRGB::Red;
  leds[50] = CRGB::Red;
  leds[63] = CRGB::Red;
  leds[65] = CRGB::Red;
  FastLED.show();
  }


  

  void Arriva_I_N() {
  fill_solid(&leds[0], 3, CRGB::Black);
  fill_solid(&leds[13], 5, CRGB::Black);
  FastLED.show();
  }

  void Arriva_M_N() {
  fill_solid(&leds[30], 5, CRGB::Black);
  fill_solid(&leds[45], 3, CRGB::Black);
  FastLED.show();
  }

  void Arriva_D_N() {
  fill_solid(&leds[48], 3, CRGB::Black);
  fill_solid(&leds[61], 5, CRGB::Black);
  FastLED.show();
  }

/////////////////////////////////////////////
  void Medio_I_B() {
  leds[4] = CRGB::Blue;
  fill_solid(&leds[11], 2, CRGB::Blue);
  leds[19] = CRGB::Blue;
  FastLED.show();
  }

  void Medio_M_B() {
  leds[28] = CRGB::Blue;
  fill_solid(&leds[35], 2, CRGB::Blue);
  leds[43] = CRGB::Blue;
  FastLED.show();
  }

  void Medio_D_B() {
  leds[52] = CRGB::Blue;
  fill_solid(&leds[59], 2, CRGB::Blue);
  leds[67] = CRGB::Blue;
  FastLED.show();
  }



  void Medio_I_R() {
  leds[3] = CRGB::Red;
  leds[5] = CRGB::Red;
  leds[18] = CRGB::Red;
  leds[20] = CRGB::Red;
  FastLED.show();
  }

  void Medio_M_R() {
  leds[29] = CRGB::Red;
  leds[27] = CRGB::Red;
  leds[44] = CRGB::Red;
  leds[42] = CRGB::Red;
  FastLED.show();
  }

  void Medio_D_R() {
  leds[51] = CRGB::Red;
  leds[53] = CRGB::Red;
  leds[66] = CRGB::Red;
  leds[68] = CRGB::Red;
  FastLED.show();
  }



  void Medio_I_N() {
  fill_solid(&leds[3], 3, CRGB::Black);
  fill_solid(&leds[11], 2, CRGB::Black);
  fill_solid(&leds[18], 3, CRGB::Black);
  FastLED.show();
  }

  void Medio_M_N() {
  fill_solid(&leds[27], 3, CRGB::Black);
  fill_solid(&leds[35], 2, CRGB::Black);
  fill_solid(&leds[42], 3, CRGB::Black);
  FastLED.show();
  }

  void Medio_D_N() {
  fill_solid(&leds[51], 3, CRGB::Black);
  fill_solid(&leds[59], 2, CRGB::Black);
  fill_solid(&leds[66], 3, CRGB::Black);
  FastLED.show();
  }
//////////////////////////////////////////////////////////

  void Abajo_I_B() {
  leds[7] = CRGB::Blue;
  fill_solid(&leds[9], 2, CRGB::Blue);
  leds[22] = CRGB::Blue;
  FastLED.show();
  }

  void Abajo_M_B() {
  leds[25] = CRGB::Blue;
  fill_solid(&leds[37], 2, CRGB::Blue);
  leds[40] = CRGB::Blue;
  FastLED.show();
  }

  void Abajo_D_B() {
  leds[55] = CRGB::Blue;
  fill_solid(&leds[57], 2, CRGB::Blue);
  leds[70] = CRGB::Blue;
  FastLED.show();
  }



  void Abajo_I_R() {
  leds[6] = CRGB::Red;
  leds[8] = CRGB::Red;
  leds[21] = CRGB::Red;
  leds[23] = CRGB::Red;
  FastLED.show();
  }

  void Abajo_M_R() {
  leds[26] = CRGB::Red;
  leds[24] = CRGB::Red;
  leds[41] = CRGB::Red;
  leds[39] = CRGB::Red;
  FastLED.show();
  }

  void Abajo_D_R() {
  leds[54] = CRGB::Red;
  leds[56] = CRGB::Red;
  leds[69] = CRGB::Red;
  leds[71] = CRGB::Red;
  FastLED.show();
}





  void Abajo_I_N() {
  fill_solid(&leds[6], 5, CRGB::Black);
  fill_solid(&leds[21], 3, CRGB::Black);
  FastLED.show();
  }

  void Abajo_M_N() {
  fill_solid(&leds[24], 3, CRGB::Black);
  fill_solid(&leds[37], 5, CRGB::Black);
  FastLED.show();
  }

  void Abajo_D_N() {
  fill_solid(&leds[54], 5, CRGB::Black);
  fill_solid(&leds[69], 3, CRGB::Black);
  FastLED.show();
}

void Todo_a_0(){
  val1 = 0;
  val2 = 0;
  val3 = 0;
  val4 = 0;
  val5 = 0;
  val6 = 0;
  val7 = 0;
  val8 = 0;
  val9 = 0;
  BOT1J = 0;
  BOT2J = 0;
  BOT3J = 0;
  BOT4J = 0;
  BOT5J = 0;
  BOT6J = 0;
  BOT7J = 0;
  BOT8J = 0;
  BOT9J = 0;
}