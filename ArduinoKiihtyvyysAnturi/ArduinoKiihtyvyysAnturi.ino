/*
  Tämän ohjelman pohjana oli AnalogInOutSerial,
  josta ohjelmaa muokattiin siten, että saadaan 3-kanavainen kiihtyvyysanturi GY-61 kalibroitua
  maan vetovoiman avulla sensoriarvosta kiihtyvyydeksi SI-muotoon.
  
  Kalibrointiesimerkki X-kanavalle:
  
  1) Aseta anturin X-akseli ylöspäin ja lue sensoriarvo S1
  2) Aseta anturin X-akseli vaakasuuntaan ja lue sensoriarvo S2
  3) Aseta anturin X-akseli alaspäin ja lue sensoriarvo S3
  4) Kirjaa arvot Excel-taulukkoon muodossa:
  sensori  kiihtyvyys
  S1       9,81
  S2       0
  S3       -9,81
  5) Tee XY-scatter -tyyppinen kuvaaja ja lisää trendiviiva, joka 
  antaa lineaarisen kalibrointiyhtälön sensoriarvosta kiihtyvyydeksi.
  
  Kalibrointi tehdään kullekin kanavalle erikseen.
 */

// Kiihtyvyysanturin kytkentänapojen määrittelyt:
const int analogInPinX = A0;  // X-kanavan kytkentänapa
const int analogInPinY = A1;  // Y-kanavan kytkentänapa
const int analogInPinZ = A2;  // Z-kanavan kytkentänapa

int sensorValueX = 0;        // X-kiihtyvyyttä vastaava sensoriarvo 10 bittisessä järjestelmässä (0 - 1023)
int sensorValueY = 0;        // Y-kiihtyvyyttä vastaava sensoriarvo 10 bittisessä järjestelmässä (0 - 1023)
int sensorValueZ = 0;        // Z-kiihtyvyyttä vastaava sensoriarvo 10 bittisessä järjestelmässä (0 - 1023)
unsigned long aika = 0;      // aikaleima, joka luetaan millisekunteina. Int-tyyppinen määrittely tuottaisi nopean bitti-ylivuodon.
int sisaanmeno = 0;          // testi ollaanko menossa sisään ohjelmaan ensimmäistä kertaa

float Ax = 0.0;
float Ay = 0.0;
float Az = 0.0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {
  
  if (sisaanmeno == 0)
  {
     delay(500);                   // Annetaan aikaa käynnistelylle
     Serial.print("Time(ms) " );   // Tulostetaan aluksi tiedot mitä ollaan tulostamassa
     Serial.print("\t A_x ");
     Serial.print("\t A_y ");
     Serial.print("\t A_z "); 
     Serial.println("\t A "); // Tulostus ja rivinvaihto
     sisaanmeno = 1;               // Vaihdetaan tunnistetieto niin tänne ei enää tulla
  }
  
  // Luetaan kanavien antamat sensoriarvot ja aikaleima
  sensorValueX = analogRead(analogInPinX);      
  sensorValueY = analogRead(analogInPinY);  
  sensorValueZ = analogRead(analogInPinZ);  
  aika = millis();    

 Ax = 0.1401*sensorValueX - 48.209;
 Ay = 0.1401*sensorValueY - 47.508;
 Az = 0.1422*sensorValueZ - 50.111;

  // print the results to the serial monitor:                      
  Serial.print(Ax);      
  Serial.print("\t");  
  Serial.print(Ay);      
  Serial.print("\t");  
  Serial.print(Az);      
  Serial.print("\t");  
  Serial.println();        

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(100);                         // Nyt ei vielä pyritä kovin nopeaan mittaukseen kun vasta kalibroidaan... 100ms viive.                
}
