#include "CenterPoints.h"

int Distances[] = {0,0,0,0};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4, INPUT);
  
}

void loop() {
  //Missä asennossa(UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4)
  
   int LoopAmount = 0;
   int GivenPos = 0;
   Serial.println("Give loop amount");
   while(LoopAmount==0)
   {
      if(Serial.available()>0)
      {
        LoopAmount = Serial.parseInt();
      }
   }
   Serial.println("Give position (UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4)");
   while(GivenPos==0)
   {
      if(Serial.available()>0)
      {
        GivenPos = Serial.parseInt();
      }
   }
   
   
   for(int i = 0; i < LoopAmount; i++){
    int minVal = 400;
    int X = analogRead(A0);
    int Y = analogRead(A1);
    int Z = analogRead(A2);
    
    Distances[0] = Distance(X,Y,Z,kp[0][0],kp[0][1],kp[0][2]);
    Distances[1] = Distance(X,Y,Z,kp[1][0],kp[1][1],kp[1][2]);
    Distances[2] = Distance(X,Y,Z,kp[2][0],kp[2][1],kp[2][2]);
    Distances[3] = Distance(X,Y,Z,kp[3][0],kp[3][1],kp[3][2]);

    for(int a = 0; a < 4; a++){
      if (Distances[a] < minVal) {
         minVal = Distances[a];
      }
    }
    Serial.print(GivenPos);
    Serial.print("  ");
    if(minVal == Distances[0]){Serial.print("1");}
    if(minVal == Distances[1]){Serial.print("2");}
    if(minVal == Distances[2]){Serial.print("3");}
    if(minVal == Distances[3]){Serial.print("4");}
    Serial.println();
    delay(100);
    
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
