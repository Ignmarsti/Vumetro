#include <Adafruit_NeoPixel.h>

//Primer parámetro = cantidad de pixeles en la tira
//Segundo parámetro = pin de conexión a Arduino
//Tercer parámetro:
  //NEO_KHZ800  800 KHz velocidad de datos (WS2812 y nuevos)
  //NEO_KHZ400  400 KHz velocidad de datos (WS2811 y anteriores)
  //NEO_GRB     flujo de datos en el orden GRB (WS2812 y nuevos)
  //NEO_RGB     fluo de datos en el orden RGB (versiones más antiguas)

//Debido a que la señal de audio varía mucho en poco tiempo, es mejor tomar un valor promedio en
//un intervalo de tiempo. Para ello tomaremos el valor máximo y lo restaremos al mínimo en
//un intervalo de timepo determinado

#define tiempo_muestreo 50 //Definimos una ventana de 40 ms, la cual corresponde a una frecuencia de muestreo de 25 Hz
#define pin_jack 14 //Definimos el pin analógico de toma de datos
#define pin_pot 15//Definimos el pin analógico al que conectaremos el potenciómetro que controlará el nivel de amplitud 

unsigned int valor_promedio = 0;//En esta variable guardaremos la diferencia entre el valor máximo y minimo obtenido en el tiempo de muestreo
unsigned int control_amplitud = 0;//En esta variable guardaremos el valor leido del potenciómetro por puerto analógico
unsigned int valor_final = 0;//En esta variable guardaremos el valor final de amplitud de la señal

//Creamos un objeto de la tira
Adafruit_NeoPixel tira_LED = Adafruit_NeoPixel(60, 2, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  tira_LED.begin();//Iniciamos la tira LED
  tira_LED.show();//Iniciamos con valor 0 la tira de LED, es decir, iniciamos con la tira LED apagada
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long tiempo_inicial = millis();//Registramos el momento en el que entramos en el loop principal

  unsigned int maximo = 0;//Aquí guardaremos el máximo valor registrado durante el muestreo. Lo iniciamos con el valor más bajo
                          //posible para guardar el primer valor como el máximo
  unsigned int minimo = 1024;//Aquí guardaremos el mínimo valor registrado durante el muestreo. Lo iniciamos con el valor más alto
                          //posible para guardar el primer valor como el máximo

  unsigned int valor_senal = 0;//Esta variable guardará el valor analógico leido

  while(millis() - tiempo_inicial < tiempo_muestreo){
    valor_senal = analogRead(pin_jack);//guardamos el valor leido por el puerto analógico del jack
    control_amplitud = analogRead(pin_pot);//guardamos el valor leido por el puerto analógico del potenciometro
    if(valor_senal<1024){
      if(valor_senal < minimo){//si el valor actual leido es menor que el anterior
        minimo = valor_senal;//Actualizamos el valor minimo
      }
      if(valor_senal > maximo){//si el valor actual leido es mayor que el anterior
        maximo = valor_senal;//Actualizamos el valor maximo
      }
    }
  }
  //Una vez haya pasado el tiempo de muestreo, registramos el valor promedio restando el valor máximo al mínimo
  valor_promedio = maximo - minimo;
  valor_final = valor_promedio/control_amplitud;//Dividimos el valor promedio por el valor obtenido del potenciómetro. Esto es una manera de calibrar 
                                                //el vúmetro, ya que la amplitud de la señal depende del volumen. De esta manera evitamos la saturación de los LED´s debido al volumen
  vumetro();//Llamamos a la función que se encargará de enceder los LED´s correspondientes
  
}

void vumetro(){
  tira_LED.clear();//Cada 25 ms limpimaos la tira led antes de encender de nuevo los correspondientes LED´s encendidos
                   //En caso de que se percibiese visualmente el cambio tendría que aumentar la frecuencia de meustreo para evitarlo
  int i=0;
  
  if(0<valor_final<34){
    tira_LED.setPixelColor(0, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
  }
  if(34<valor_final<65){
    for(i=0;i=2; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
  }
  if(65<valor_final<102){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
  }

    
  if(102<valor_final<136){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    tira_LED.setPixelColor(4, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
  }
  
  if(136<valor_final<173){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=5; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
  }    
  if(173<valor_final<204){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
  }

  
  if(204<valor_final<240){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }

    tira_LED.setPixelColor(7, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
  }
  if(240<valor_final<280){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=8; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
  }
  if(280<valor_final<320){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
  }

  if(320<valor_final<360){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    tira_LED.setPixelColor(10, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes
  }

  if(360<valor_final<400){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    for(i=10; i=11; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes 
    }
  }
  if(400<valor_final<440){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    for(i=10; i=12; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes 
    }
  }

  if(440<valor_final<480){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    for(i=10; i=12; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes 
    }
    tira_LED.setPixelColor(13, tira_LED.Color(255, 0, 0));//Establecemos el color verde en los LED´s correspondientes
  }
  if(440<valor_final<480){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    for(i=10; i=12; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes 
    }
    for(i=13; i=14; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 0));//Establecemos el color verde en los LED´s correspondientes
    }
  }
  if(480<valor_final<520){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    for(i=10; i=12; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes 
    }
    for(i=13; i=15; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 0));//Establecemos el color verde en los LED´s correspondientes
    }
  }


  if(520<valor_final<560){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    for(i=10; i=12; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes 
    }
    for(i=13; i=14; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 0));//Establecemos el color verde en los LED´s correspondientes
    }
    tira_LED.setPixelColor(15, tira_LED.Color(255, 0, 154));//Establecemos el color verde agua en los LED´s correspondiente
  }

  if(560<valor_final<600){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    for(i=10; i=12; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes 
    }
    for(i=13; i=14; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 0));//Establecemos el color verde en los LED´s correspondientes
    }
    for(i=15; i=16; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 154));//Establecemos el color verde agua en los LED´s correspondiente
    }
  }
  if(600<valor_final<640){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    for(i=10; i=12; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes 
    }
    for(i=13; i=14; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 0));//Establecemos el color verde en los LED´s correspondientes
    }
    for(i=15; i=17; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 154));//Establecemos el color verde agua en los LED´s correspondiente
    }
  }

  if(640<valor_final<680){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    for(i=10; i=12; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes 
    }
    for(i=13; i=14; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 0));//Establecemos el color verde en los LED´s correspondientes
    }
    for(i=15; i=17; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 154));//Establecemos el color verde agua en los LED´s correspondiente
    }
    tira_LED.setPixelColor(18, tira_LED.Color(255, 0, 255));//Establecemos el color celeste en los LED´s correspondientes
  }
  if(680<valor_final<720){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    for(i=10; i=12; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes 
    }
    for(i=13; i=14; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 0));//Establecemos el color verde en los LED´s correspondientes
    }
    for(i=15; i=17; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 154));//Establecemos el color verde agua en los LED´s correspondiente
    }
    for(i=18; i=19; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 255));//Establecemos el color celeste en los LED´s correspondientes
    }
  }
  if(720<valor_final<760){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    for(i=10; i=12; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes 
    }
    for(i=13; i=14; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 0));//Establecemos el color verde en los LED´s correspondientes
    }
    for(i=15; i=17; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 154));//Establecemos el color verde agua en los LED´s correspondiente
    }
    for(i=18; i=20; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 255));//Establecemos el color celeste en los LED´s correspondientes
    }
  }

  if(760<valor_final<800){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    for(i=10; i=12; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes 
    }
    for(i=13; i=14; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 0));//Establecemos el color verde en los LED´s correspondientes
    }
    for(i=15; i=17; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 154));//Establecemos el color verde agua en los LED´s correspondiente
    }
    for(i=18; i=20; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 255));//Establecemos el color celeste en los LED´s correspondientes
    }
    tira_LED.setPixelColor(21, tira_LED.Color(0, 0, 255));//Establecemos el color azul oscuro en los LED´s correspondientes
  }
  if(800<valor_final<840){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    for(i=10; i=12; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes 
    }
    for(i=13; i=14; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 0));//Establecemos el color verde en los LED´s correspondientes
    }
    for(i=15; i=17; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 154));//Establecemos el color verde agua en los LED´s correspondiente
    }
    for(i=18; i=20; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 255));//Establecemos el color celeste en los LED´s correspondientes
    }
    for(i=21; i=22; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 0, 255));//Establecemos el color azul oscuro en los LED´s correspondientes
    }
  }
  if(840<valor_final<880){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    for(i=10; i=12; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes 
    }
    for(i=13; i=14; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 0));//Establecemos el color verde en los LED´s correspondientes
    }
    for(i=15; i=17; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 154));//Establecemos el color verde agua en los LED´s correspondiente
    }
    for(i=18; i=20; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 255));//Establecemos el color celeste en los LED´s correspondientes
    }
    for(i=21; i=23; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 0, 255));//Establecemos el color azul oscuro en los LED´s correspondientes
    }
  }

  if(880<valor_final<920){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    for(i=10; i=12; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes 
    }
    for(i=13; i=14; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 0));//Establecemos el color verde en los LED´s correspondientes
    }
    for(i=15; i=17; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 154));//Establecemos el color verde agua en los LED´s correspondiente
    }
    for(i=18; i=20; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 255));//Establecemos el color celeste en los LED´s correspondientes
    }
    for(i=21; i=22; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 0, 255));//Establecemos el color azul oscuro en los LED´s correspondientes
    }
    tira_LED.setPixelColor(23, tira_LED.Color(0, 188, 255));//Establecemos el color morado en los LED´s correspondientes
  }
  if(920<valor_final<950){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    for(i=10; i=12; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes 
    }
    for(i=13; i=14; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 0));//Establecemos el color verde en los LED´s correspondientes
    }
    for(i=15; i=17; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 154));//Establecemos el color verde agua en los LED´s correspondiente
    }
    for(i=18; i=20; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 255));//Establecemos el color celeste en los LED´s correspondientes
    }
    for(i=21; i=22; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 0, 255));//Establecemos el color azul oscuro en los LED´s correspondientes
    }
    for(i=23; i=25; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 188, 255));//Establecemos el color morado en los LED´s correspondientes
    }
  }

  if(950<valor_final<965){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    for(i=10; i=12; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes 
    }
    for(i=13; i=14; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 0));//Establecemos el color verde en los LED´s correspondientes
    }
    for(i=15; i=17; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 154));//Establecemos el color verde agua en los LED´s correspondiente
    }
    for(i=18; i=20; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 255));//Establecemos el color celeste en los LED´s correspondientes
    }
    for(i=21; i=22; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 0, 255));//Establecemos el color azul oscuro en los LED´s correspondientes
    }
    for(i=23; i=25; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 188, 255));//Establecemos el color morado en los LED´s correspondientes
    }
    tira_LED.setPixelColor(26, tira_LED.Color(0, 255, 0));//Establecemos el color rosa en los LED´s correspondientes
  }
  if(965<valor_final<980){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    for(i=10; i=12; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes 
    }
    for(i=13; i=14; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 0));//Establecemos el color verde en los LED´s correspondientes
    }
    for(i=15; i=17; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 154));//Establecemos el color verde agua en los LED´s correspondiente
    }
    for(i=18; i=20; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 255));//Establecemos el color celeste en los LED´s correspondientes
    }
    for(i=21; i=22; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 0, 255));//Establecemos el color azul oscuro en los LED´s correspondientes
    }
    for(i=23; i=25; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 188, 255));//Establecemos el color morado en los LED´s correspondientes
    }
    for(i=26; i=27; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rosa en los LED´s correspondientes
    }
  }
  if(980<valor_final<995){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    for(i=10; i=12; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes 
    }
    for(i=13; i=14; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 0));//Establecemos el color verde en los LED´s correspondientes
    }
    for(i=15; i=17; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 154));//Establecemos el color verde agua en los LED´s correspondiente
    }
    for(i=18; i=20; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 255));//Establecemos el color celeste en los LED´s correspondientes
    }
    for(i=21; i=22; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 0, 255));//Establecemos el color azul oscuro en los LED´s correspondientes
    }
    for(i=23; i=25; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 188, 255));//Establecemos el color morado en los LED´s correspondientes
    }
    for(i=26; i=28; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rosa en los LED´s correspondientes
    }
  }
  if(995<valor_final<1024){
    for(i=0;i=3; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rojo en los LED´s correspondientes
    }
    for(i=4;i=6; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(171, 255, 0));//Establecemos el color naranja en los LED´s correspondientes
    }
    for(i=7; i=9; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 247, 0));//Establecemos el color amarillo en los LED´s correspondientes
    }
    for(i=10; i=12; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 171, 0));//Establecemos el color verde pistacho en los LED´s correspondientes 
    }
    for(i=13; i=14; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 0));//Establecemos el color verde en los LED´s correspondientes
    }
    for(i=15; i=17; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 154));//Establecemos el color verde agua en los LED´s correspondiente
    }
    for(i=18; i=20; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(255, 0, 255));//Establecemos el color celeste en los LED´s correspondientes
    }
    for(i=21; i=22; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 0, 255));//Establecemos el color azul oscuro en los LED´s correspondientes
    }
    for(i=23; i=25; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 188, 255));//Establecemos el color morado en los LED´s correspondientes
    }
    for(i=26; i=29; i++){
      tira_LED.setPixelColor(i, tira_LED.Color(0, 255, 0));//Establecemos el color rosa en los LED´s correspondientes
    }
  }
}