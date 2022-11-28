const int analogInPinX = A0;  // X-kanavan kytkentänapa
const int analogInPinY = A1;  // Y-kanavan kytkentänapa
const int analogInPinZ = A2;  // Z-kanavan kytkentänapa

int X = 0;        
int Y = 0;        
int Z = 0;                

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {

  
  X = analogRead(analogInPinX);      
  Y = analogRead(analogInPinY);  
  Z = analogRead(analogInPinZ);   
                    
  Serial.print(X);      
  Serial.print("\t");  
  Serial.print(Y);      
  Serial.print("\t");  
  Serial.print(Z);      
  Serial.print("\t");  
  Serial.println();        

  delay(100);                                   
}
