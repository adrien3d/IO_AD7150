#include "IO_AD7150.h"

IO_AD7150 ad7150;
AD7150_Values result;

void setup()
{
  ad7150.begin();
  ad7150.setOffset(AD7150_OFFSET_DAC_5);
  ad7150.setRange(AD7150_RANGE_0_2);
  ad7150.setup();

  Serial.begin(115200);
}

void loop()
{
  ad7150.configure(AD7150_MODE_SING_CONV);
  delay(10);

  ad7150.configure(AD7150_MODE_POWER_DOWN); 

  result = ad7150.getValue();

  /*Serial.print("Status :");
  Serial.print(result.status, BIN);
  Serial.print("\t");*/
  Serial.print("Value :");
  Serial.print(result.value, DEC);
  
  delay(20);
  Serial.println();
}