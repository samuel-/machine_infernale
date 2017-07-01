
#include <Servo.h>

Servo porte;
#define bouton 12
#define servo 9
#define led 13
#define capteur_fin 10

int pos = 0;
static unsigned long temps_0 = millis();
static unsigned long temps_course = millis();
boolean porte_ouverte=false;
boolean bille_arrivee=false;

void setup() {
  pinMode(bouton, INPUT_PULLUP);
  pinMode(capteur_fin, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  porte.attach(servo);
  porte_ouverte=false;
  LcdInitialise();
  ecran_affiche("maCHIne","InFernALE");
  //Serial.begin(9600);
}

void loop() {
//  Serial.println(bille_arrivee);
//  Serial.println(porte_ouverte);
  int appui = digitalRead(bouton);
  int arrivee = digitalRead(capteur_fin);
  if (appui == LOW and (bille_arrivee==true or porte_ouverte==true)) {
    bille_arrivee=false;
    porte_ouverte=false;
    ecran_affiche("maCHIne","InFernALE");
  }
  else if (appui == LOW and porte_ouverte==false and bille_arrivee==false) {
    porte_ouverte=true;
    temps_0=millis();
    ecran_affiche("C'est ","PaRTI !");
    ouvre_porte();
    led_cligne(led,150);
  }
  else if (appui == HIGH) {
    digitalWrite(led, LOW);
  }
  if (arrivee == LOW and porte_ouverte==true){
    temps_course=millis()-temps_0;
    course_finie(temps_course/1000);
    }

}

void ouvre_porte(){
  porte.write(0);
  delay(1000);
  for (pos = 0; pos <= 90; pos += 1) {
    porte.write(pos);
    delay(25);
  }
  }

  void course_finie(long score){
    porte_ouverte=false;
    bille_arrivee=true;
    char buf[15];
    sprintf(buf, "%lu", score); 
    ecran_affiche("SCORE  ",buf);
    }
    
void ecran_affiche(char ligne1[15], char ligne2[15]){
    LcdClear(); 
      drawLine();
      gotoXY(4,1);
      LcdString (ligne1);
      gotoXY(4,3);
      LcdString(ligne2);
}

void led_cligne(int ledpin,int del){
    digitalWrite(ledpin, HIGH);
    delay(del);
    digitalWrite(ledpin, LOW);
    delay(del);
    digitalWrite(ledpin, HIGH);
    delay(del);
    digitalWrite(ledpin, LOW);
}

