#include <Adafruit_NeoPixel.h>

const byte pin_LED = 6; 
const byte pinJack = A0;
const byte numero_led = 30; 
const byte BRILLO = 10;

int valorADC = 0;
int valorActual = 0;
int valorAnterior = 0;

int valorPico = 0;
int valorPicoAnterior = 0;

unsigned long tiempoPico = 0;
unsigned long tiempoCaida = 0;

bool cayendo = false;


Adafruit_NeoPixel tira_LED(numero_led, pin_LED, NEO_GRB + NEO_KHZ800);


void setup() {
  tira_LED.begin();///INICIALIZAMOS LA TIRA LED
}

void loop() {
  valorADC = 20*log(analogRead(pinJack) + 1);//Leemos el valor del puerto analógico y lo convertimos a escala logaritmica
  valorActual = map(valorADC, 0, 81, 0, numero_led);//El valor máximo de valorADC es 60, que corresponde al valor 1000 de lectura del pinJack

  ///-------Si el valor actual leido por el puerto ADC es mayor que el últimao valorPico 
  if(valorActual >= valorPico){
    valorPico = valorActual;//Actualizamos la variable valorPico con el nuevo pico
    tiempoPico = millis();//Tomamos el momento en el que se actualizó el nuevo LED pico
    cayendo = false;//bajamos la bandera de que  está cayendo porque estamos subiendo
  }
  ////---Siempre el led pico sea mayor que cero lo tendremos encendido ----////
  if(valorPico>=0){
    if(valorPicoAnterior<valorActual){//si el valor pico anterior es menor que el valor leido actualmente por el ADC, tendremos que devolver ese LED al color que le corresponde
      if(valorPicoAnterior<10) tira_LED.setPixelColor(valorPicoAnterior, tira_LED.Color(0,BRILLO, 0));
      else if(valorPicoAnterior<20) tira_LED.setPixelColor(valorPicoAnterior, tira_LED.Color(BRILLO,BRILLO, 0));
      else tira_LED.setPixelColor(valorPicoAnterior, tira_LED.Color(BRILLO,0, 0));
    }
    else tira_LED.setPixelColor(valorPicoAnterior, tira_LED.Color(0, 0, 0));//Si el valor pico anterior es mayor o igual que el valor actual leido por el ADC, apagaremos el pico anterior porque habrá un pico nuevo
    tira_LED.setPixelColor(valorPico, tira_LED.Color(0, 0, BRILLO));
  }
  //---Si el led pico es menor a 0, lo tendremos apagado----////
  else tira_LED.setPixelColor(valorPico, tira_LED.Color(0, 0, 0));

  ///---Si el valor actual leido del puerto analógico es mayor que el anterior, tendremos que encender los LED´s que faltan por encender---//
  if(valorActual>valorAnterior){
    for(int i=valorAnterior; i<valorActual; i++){
      if(i<10) tira_LED.setPixelColor(i, tira_LED.Color(0,BRILLO, 0));
      else if(i<20) tira_LED.setPixelColor(i, tira_LED.Color(BRILLO,BRILLO, 0));
      else tira_LED.setPixelColor(i, tira_LED.Color(BRILLO,0, 0));   
    }
  }
  ///---Si el valor actual leido del puerto analógico es menor que el anterior, tendremos que apagar los LED´s que sobren----////
  else{
    for(int i=valorAnterior; i>=valorActual; i--){
      tira_LED.setPixelColor(i, tira_LED.Color(0,0,0));
    }
  }


  
  //--VAMOS AHORA CON EL TIEMPO QUE VA A ESTAR CAYENDO EL LED PICO---///
  if(!cayendo){//Si no está cayendo el LED
    if(millis() - tiempoPico >= 300){///Si han pasado 500 ms desde que se encendió el nuevo LED
      tiempoCaida = millis();//Guardamos el tiempo en el que ha empezado a caer el LED
      cayendo = true;//Levantamos la bandera de que esta cayendo
    }
  }
  else{// Si sí está cayendo el LED
    if(millis() - tiempoCaida >= 100){//Si han pasado 100 ms
      valorPicoAnterior = valorPico;
      tiempoCaida = millis();//Guardamos el instante de tiempo en el que sigue decrementamos el valorPico 
      valorPico--;//Decrementamos el valor pico
      if(valorPico<0) cayendo = false;
    }
  }
  tira_LED.show();
  valorAnterior = valorActual;//Guardamos el último valor leido en una variable antes de guardar el nuevo valor leido por el puerto analógico
  //valorPicoAnterior = valorPico;
}