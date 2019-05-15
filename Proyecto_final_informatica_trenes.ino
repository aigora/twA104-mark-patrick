#include <Servo.h> 

//inicialización del servo motor 
Servo servo;

//Variables de pines arduino 
int Yellow1 = 12;
int Yellow2 = 13;
int red = 11;
int green = 10;
int trigPin_1 = 9;
int echoPin_1 = 4;
int trigPin_2 = 6;
int echoPin_2 = 7;


//Variables numericas 
int pos=45;   
long duracion_1;
int distancia_1;
long duracion_2;
int distancia_2;
const int grados_velocidad=4;

//funciones prototipos

void subir_barra(int);
void bajar_barra(int);
void Distancia(int,int*);
int sensor_ultra(int,int);
int a=0;

void setup()
{
  //output
 pinMode(Yellow1, OUTPUT);
 pinMode(Yellow2, OUTPUT);
 pinMode(green, OUTPUT);
 pinMode(red, OUTPUT);
 pinMode(trigPin_1, OUTPUT);
 pinMode(trigPin_2, OUTPUT);

 //input
 pinMode(echoPin_1, INPUT);
 pinMode(echoPin_2, INPUT);

 //Servo
 servo.attach(5);   

 //Monitor de computador
 Serial.begin(9600);
} 

void loop()
{ 
 digitalWrite(green, HIGH);//Conectado junto a una resistencia de 220ohms
 duracion_1=sensor_ultra(trigPin_1,echoPin_1);
 Distancia(duracion_1,&distancia_1);
 Serial.print("Distancia del sensor de movimiento 1 : ");
 Serial.println(distancia_1);
 if (distancia_1 <= 8)
  {
 digitalWrite(green, LOW);
 duracion_1 = pulseIn(echoPin_1, LOW);
 bajar_barra(grados_velocidad);
 digitalWrite(red, HIGH);
  do 
 {
duracion_2=sensor_ultra(trigPin_2,echoPin_2);
Distancia(duracion_2,&distancia_2);
Serial.print("Distancia del sensor de movimiento 2 : ");
Serial.println(distancia_2);//cm
 }
while(distancia_2>=9);
 do 
 {
duracion_2=sensor_ultra(trigPin_2,echoPin_2);
Distancia(duracion_2,&distancia_2);
Serial.print("Distancia del sensor de movimiento 2 : ");
Serial.println(distancia_2);//cm
 }
while(distancia_2<=8);

digitalWrite(red, LOW);
subir_barra(grados_velocidad);
  }
  }


void subir_barra(int velocidad)
{
   for(pos = 45; pos <= 135; pos += velocidad)  
  {                                  
    servo.write(pos);               
    delay(60);                       
    digitalWrite(Yellow1, HIGH);
    delay(250);
    digitalWrite(Yellow1, LOW);
    digitalWrite(Yellow2, HIGH);
    delay(250);
    digitalWrite(Yellow2, LOW);
  } 
}
void bajar_barra(int velocidad)
{
for(pos = 135; pos>=45; pos-=velocidad)     
  {                                
    servo.write(pos);             
    delay(30);    
    digitalWrite(Yellow1, HIGH);
    delay(275);
    digitalWrite(Yellow1, LOW);
    digitalWrite(Yellow2, HIGH);
    delay(275);
    digitalWrite(Yellow2, LOW);                   
  } 
 
}

void Distancia(int duracion,int *distancia)
 {
*distancia=duracion*0.034/2;
 }

int sensor_ultra(int trigger,int echo)
{
  int tiempo;
 digitalWrite(trigger, LOW);
 delay(10);
 digitalWrite(trigger, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigger, LOW);
 tiempo = pulseIn(echo, HIGH);
 return(tiempo);
}
