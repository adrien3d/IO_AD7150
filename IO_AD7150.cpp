#include "IO_AD7150.h"

IO_AD7150::IO_AD7150(uint8_t i2cAddress)
{
   m_i2cAddress = i2cAddress;
   m_offset = AD7150_OFFSET_DAC_4;
   m_range = AD7150_CAPACTIVE_INPUT_RANGE_2;
}

/**************************************************************************/
/*!
    @brief  Sets up the HW (reads coefficients values, etc.)
*/
/**************************************************************************/
void IO_AD7150::begin()
{
  Wire.begin();
}

void IO_AD7150::writeRegister(uint8_t reg, uint16_t value)
{
  Wire.begin();
  Wire.beginTransmission(m_i2cAddress);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
  delay(4); //Wait a little bit that the change is effective
}

void IO_AD7150::setup()
{
  writeRegister(AD7150_REG_CH1_SENSITIVITY, 0x08);
  writeRegister(AD7150_REG_CH1_SETUP, m_range);
  writeRegister(AD7150_REG_CONFIGURATION, 0x12);    //Conversion enabled on ch1 and ch2, Single Conversion mode
  writeRegister(AD7150_REG_POWER_DOWN_TIMER, 0x00);
  writeRegister(AD7150_REG_CH1_CAPDAC, m_offset);
}

void IO_AD7150::configure(AD7150_adMode_t mode)
{
  writeRegister(AD7150_REG_CONFIGURATION, mode);
}

void IO_AD7150::setOffset(AD7150_adOffset_t offset)
{
  m_offset = offset;
}
void IO_AD7150::setRange(AD7150_adRange_t range)
{
  m_range = range;
}

AD7150_Values IO_AD7150::getValue(void)
{
  uint8_t data[3];
  Wire.requestFrom(AD7150_I2C_ADDRESS, 3, true);  
  for (int i = 0; Wire.available(); i++)
  {
    data[i] = Wire.read();
  }

  uint16_t val = data[1] << 4 | data[2] >> 4;
  uint8_t status = data[0];

  AD7150_Values result;
  result.status = status;
  result.value = val;

  return result;
}
