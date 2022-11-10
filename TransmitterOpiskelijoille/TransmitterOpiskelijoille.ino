#include "messaging.h"
#include "accelerator.h"

void setup() 
{
  Serial.begin(9600);
}

void loop()
{
  Accelerator Aobject;
  Messaging Mobject;
  Serial.println("Give number how many measurements");
  int NumberOfMeasurements = 0;
  while(NumberOfMeasurements==0)
  {
    if(Serial.available()>0)
    {
       NumberOfMeasurements = Serial.parseInt();
    }
  }

  uint8_t flags = 0xff;
  
  //Kysytään missä asennossa arduino on
  Serial.println("Give position of arduino (left=1, right=2, up=3, down=4)");
  int pos = 0;
  while(pos==0)
  {
    if(Serial.available()>0)
    {
      pos = Serial.parseInt();
    }
  }
   //Määritetään hexa arvo flagiin asennon mukaan
   switch (pos){
    case 1:
      flags = 0x01;
      break;
    case 2:
      flags = 0x02;
      break;
    case 3:
      flags = 0x03;
      break;
    case 4:
      flags = 0x04;
      break;
   }

  
  for(int M = 0;M<NumberOfMeasurements;M++)
  {
     Aobject.makeMeasurement();
     Measurement m = Aobject.getMeasurement();
     
     uint8_t id = M;
      
     Mobject.createMessage(m);
     if(Mobject.sendMessage(id,flags))
     {
       Serial.println("Successfull transmission");
     }
     else
     {
       Serial.println("Transmission fails");
     }
     if(Mobject.receiveACK())
     {
       Serial.println("Receiver got message, going to next measurement");
     }
     else
     {
       Serial.println("Reciver did not get the message. Need to resend it");
       M--;  // Let's just revind for loop 
     }
  } // end of for
}   // end of loop
