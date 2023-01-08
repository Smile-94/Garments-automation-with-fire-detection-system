//Fire Detection And Alarm System
#define GASA0  A0
#define FIREA1 A1
#define buzzer  10

//Solar System
#define dayNight 9
#define nightCurrent 13
#define daySolar 12


void setup() {
  // Fire and Smoke System:
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(GASA0, INPUT);
  pinMode(FIREA1, INPUT);

  //solar system
  pinMode(dayNight, INPUT);
  pinMode(nightCurrent, OUTPUT);
  pinMode(daySolar, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int somekSensor=analogRead(GASA0);
  int fireSensor=analogRead(FIREA1);
  int day_night=digitalRead(dayNight);
  

  
  Serial.println("Gas sensor value");
  Serial.println(somekSensor);
  Serial.println("Fire Sensor");
  Serial.println(fireSensor);
  Serial.print("\n");
  Serial.print("Day Night: ");
  Serial.println(day_night);
  delay(1000);

  
  //fire and smoke condition
  if(somekSensor>240 || fireSensor<500){
    Serial.println("Fire");
    tone(buzzer, 1000, 10000);
    delay(2000);
    noTone(buzzer);
    delay(100);
    }else{
      noTone(buzzer);
     }

    //solar System
    if(day_night==1){
      Serial.println("NIGHT");
      digitalWrite(nightCurrent, HIGH);
      digitalWrite(daySolar, LOW);
    }else{
      Serial.println("DAY");
      digitalWrite(nightCurrent, LOW);
      digitalWrite(daySolar, HIGH);
    }
 
}
