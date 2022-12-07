#include "CenterPoints.h"

int Checker = 0;
int Distances[] = {0,0,0,0};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //Montako kertaa looppi tehdään
  //Missä asennossa(UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4)
  // eli serial monitorille esim:
  // (Kerrottu asento)  (Algotimin mukainen asento)
  //Nappi voidaan ottaa pois
  //Tallenetaal putyllä putty logiin, jota käytetään confusion matrixissa pythonissa 
  
  if(digitalRead(4) == HIGH && Checker == 0)
  {
    Checker = 1;
    int minVal = 400;
    int X = analogRead(A0);
    int Y = analogRead(A1);
    int Z = analogRead(A2);
    
    Distances[0] = Distance(X,Y,Z,kp[0][0],kp[0][1],kp[0][2]);
    Distances[1] = Distance(X,Y,Z,kp[1][0],kp[1][1],kp[1][2]);
    Distances[2] = Distance(X,Y,Z,kp[2][0],kp[2][1],kp[2][2]);
    Distances[3] = Distance(X,Y,Z,kp[3][0],kp[3][1],kp[3][2]);

    for(int i = 0; i < 4; i++){
      if (Distances[i] < minVal) {
         minVal = Distances[i];
      }
    }
    
    if(minVal == Distances[0]){Serial.println("1");}
    if(minVal == Distances[1]){Serial.println("2");}
    if(minVal == Distances[2]){Serial.println("3");}
    if(minVal == Distances[3]){Serial.println("4");}
    
  } else if (digitalRead(4) == LOW)
  {
    Checker = 0;
  }
  
  
}

int Distance(int mX,int mY,int mZ,int cX,int cY,int cZ)
{
    int Value1 = pow(mX-cX,2);
    int Value2 = pow(mY-cY,2);
    int Value3 = pow(mZ-cZ,2);
    int dist = sqrt(Value1+Value2+Value3);
    return dist;
}
