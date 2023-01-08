#include<Servo.h>//import servo motor libary to run servo motor


//for automatic door open close
#define pir_motion 12 //pir motion sensor connected to digital pin 12 
int pir_value; //reserve pir sensor digital (0,1) value
Servo door_open; //defining servo motor to open and close door

//for automatic water supplly
#define tigger_water A2 //altrasonic sensor tigger
#define echo_water A3 // altrasonic sensor reseive echo

#define red_led 10 //for empty led
#define green_led 9 // for water full
#define yello_led 8 // for avaliable

#define water_pump 13 //for water pump turn OFF and ON

float time_water=0;
float distance_water=0;

//for automatic room light control
#define entry_tigger A0
#define entry_echo A1

#define exit_tigger A4
#define exit_echo A5

#define room_light 7

float entry_distance=0;
float exit_distance=0;

int entry_flag=0;
int exit_flag=0;

int person=-1;

void setup() {
  // setup pin mode for different input and out put devices:
  Serial.begin(9600);

  //for automatic dor open close
  pinMode(pir_motion, INPUT);
  door_open.attach(11);

  //for automatic water supply
  pinMode(tigger_water, OUTPUT);
  pinMode(echo_water, INPUT);
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(yello_led, OUTPUT);
  pinMode(water_pump, OUTPUT);

  //for automatic room light control
  
  // set pin mode for entry sensor:
    pinMode(entry_tigger,OUTPUT);
    pinMode(entry_echo,INPUT);

    //set pin mode for exit sensor
    pinMode(exit_tigger,OUTPUT);
    pinMode(exit_echo,INPUT);

  //set pin mode for room light
    pinMode(room_light,OUTPUT);

}
//automatic room light control
  float entry_exit_read(int sensor_tigger, int sensor_echo){

  float time;
  float distance;
  
  digitalWrite(sensor_tigger,LOW);
  delayMicroseconds(2);
  digitalWrite(sensor_tigger,HIGH);
  delayMicroseconds(10);
  time=pulseIn(sensor_echo,HIGH);

  distance=(time*0.034)/2;

  return distance;
   
}


void loop() {
  
  //value read for automatic door open close
  pir_value=digitalRead(pir_motion);

  //value read for automatic water supply
  digitalWrite(tigger_water,LOW);
  delayMicroseconds(2);
  digitalWrite(tigger_water,HIGH);
  delayMicroseconds(10);
  digitalWrite(tigger_water,LOW);
  delayMicroseconds(2);

  //claculation for automatic water supply
  time_water=pulseIn(echo_water,HIGH);
  distance_water=time_water*0.034/2;

  Serial.print("Water Distance: ");
  Serial.println(distance_water);
  delay(100);

  //Value read for room light control
  // Read entry and exit distance:
  entry_distance=entry_exit_read(entry_tigger,entry_echo);
  delay(10);
  exit_distance=entry_exit_read(exit_tigger,exit_echo);
  delay(10);
 

//condition for room light control
  Serial.println("\n");
  Serial.println("Entry Distance");
  Serial.println(entry_distance);

 Serial.println("Exit Distance");
 Serial.println(exit_distance);

  Serial.println("Persion: ");
  Serial.println(person);
     if(entry_distance<90 && entry_flag==0){
    entry_flag=1;
    
    if(exit_flag==0){
      
        person = person+1;
     }
    
     
  }else if(exit_distance<90 && exit_flag==0){
       exit_flag=1;
       
       if(entry_flag==0){
        
          person = person-1;
      }
      
      
  }else if(entry_distance>90 && exit_distance>90 && entry_flag==1 && exit_flag==1){
      entry_flag=0, exit_flag=0;
      delay(100); 
  }
  if(person>0){
       digitalWrite(room_light,HIGH); 
    }else{
        digitalWrite(room_light,LOW);
      
      }

  Serial.println("Entry Flag");
  Serial.println(entry_flag);
  
  Serial.println("Exit Flag");
  Serial.println(exit_flag);
  

   //condition for door open close system
   
   Serial.print("PIR Value: ");
   Serial.print(pir_value);
   delay(1500);
   if(pir_value==1){
    Serial.println("Door Open/Close");
    door_open.write(0);
  }else{
    door_open.write(180);
  }

  //condition for automatic water supply
  if(distance_water<4){
    digitalWrite(water_pump, HIGH);
    
    digitalWrite(green_led,HIGH);
    delay(100);
    digitalWrite(green_led,LOW);
    delay(100);
    
  }else if(distance_water>4 && distance_water<12){
       digitalWrite(yello_led,HIGH);
       delay(100);
       digitalWrite(yello_led,LOW);
       delay(100);
    }else if(distance_water>12){
         digitalWrite(water_pump, LOW);
      
       digitalWrite(red_led,HIGH);
       delay(100);
       digitalWrite(red_led,LOW);
       delay(100);
        
      }

   
}
