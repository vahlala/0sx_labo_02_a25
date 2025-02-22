//Nom : NUEKUMO SIMO ARHTUR DURAND
//DA: 2412876



const int BUTTON = 2;
const int LEDS[] = {8, 9, 10, 11}; 
const int potentiometerPin = A1; 
const int nbreLed = 4;
const int baud = 9600;
const int max = 20;
const int diviseur = 5;

void setup() {
  Serial.begin(baud);
  for (int i = 0; i < nbreLed; i++) { 
    pinMode(LEDS[i], OUTPUT); 
  }
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  lirePotentiometre();
  lireButton();
}

int lirePotentiometre() {
  int potentiometerValue = analogRead(potentiometerPin);
  int PotentiometerV2 = map(potentiometerValue, 0, 1023, 0, 20); 
  controlLed(PotentiometerV2);
  return potentiometerValue;
}

void controlLed(int PotentiometerV2) {
  for (int i = 0; i < nbreLed; i++) { 
    if ((i * diviseur) < PotentiometerV2) {
      digitalWrite(LEDS[i], HIGH); 
    } else {
      digitalWrite(LEDS[i], LOW);
    }
  }
}

void afficher() {
  int potsVal = map(lirePotentiometre(), 0, 1023, 0, 100); 
  Serial.print("[");
  
  for (int i = 0; i < max; i++) {
    if (i < (potsVal / diviseur)) { 
      Serial.print("#");
    } else {
      Serial.print(".");
    }
  }
  
  Serial.print("] "); 
  Serial.print(potsVal);
  Serial.println("%"); 
}

void lireButton() {
  static int etatPrecedent = HIGH;
  int interval = 80; 
  int etatPresent = digitalRead(BUTTON);
  static unsigned long previousMillis = 0; 
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (etatPresent == LOW && etatPrecedent == HIGH) { 
      afficher();
    }
    
    etatPrecedent = etatPresent; 
  }
}