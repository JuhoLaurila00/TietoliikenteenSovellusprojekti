#include "accelerator.h"
#include <arduino.h>

const int analogInPinX = A0;  // X-kanavan kytkentänapa
const int analogInPinY = A1;  // Y-kanavan kytkentänapa
const int analogInPinZ = A2;  // Z-kanavan kytkentänapa
Measurement M;

Accelerator::Accelerator()
{
   Serial.println("Accelerator created!");
}


Accelerator::~Accelerator()
{
   Serial.println("Accelerator deleted!");
}


void Accelerator::makeMeasurement()
{
    M = {analogRead(analogInPinX), analogRead(analogInPinY), analogRead(analogInPinZ)};
    printStruct();
}
Measurement Accelerator::getMeasurement()
{

    return M;
}

void Accelerator::printStruct()
{
  Serial.println(M.x);
  Serial.println(M.y);
  Serial.println(M.z);
}
