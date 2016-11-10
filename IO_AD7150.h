#include <Arduino.h>
#include <Wire.h>

#define AD7150_I2C_ADDRESS                  0x48

#define AD7150_REG_STATUS                   0x00
#define AD7150_REG_CH1_DATA_HIGH            0x01
#define AD7150_REG_CH1_DATA_LOW             0x02
#define AD7150_REG_CH2_DATA_HIGH            0x03
#define AD7150_REG_CH2_DATA_LOW             0x04
#define AD7150_REG_CH1_AVERAGE_HIGH         0x05
#define AD7150_REG_CH1_AVERAGE_LOW          0x06
#define AD7150_REG_CH2_AVERAGE_HIGH         0x07
#define AD7150_REG_CH2_AVERAGE_LOW          0x08
#define AD7150_REG_CH1_SENSITIVITY          0x09
#define AD7150_REG_CH1_TIMEOUT              0x0A
#define AD7150_REG_CH1_SETUP                0x0B
#define AD7150_REG_CH2_SENSITIVITY          0x0C
#define AD7150_REG_CH2_TIMEOUT              0x0D
#define AD7150_REG_CH2_SETUP                0x0E
#define AD7150_REG_CONFIGURATION            0x0F
#define AD7150_REG_POWER_DOWN_TIMER         0x10
#define AD7150_REG_CH1_CAPDAC               0x11
#define AD7150_REG_CH2_CAPDAC               0x12
#define AD7150_REG_SERIAL_NUMBER_3          0x13
#define AD7150_REG_SERIAL_NUMBER_2          0x14
#define AD7150_REG_SERIAL_NUMBER_1          0x15
#define AD7150_REG_SERIAL_NUMBER_0          0x16
#define AD7150_REG_CHIP_ID                  0x17

//Values for the Capdac Register (0x11)
#define AD7150_OFFSET_DAC_EN_AUTO           0x80
#define AD7150_OFFSET_DAC_EN_MANU_0         0x81  //1
#define AD7150_OFFSET_DAC_EN_MANU_1         0x88  //8
#define AD7150_OFFSET_DAC_EN_MANU_2         0x8F  //15
#define AD7150_OFFSET_DAC_EN_MANU_3         0x97  //23
#define AD7150_OFFSET_DAC_EN_MANU_4         0x9E  //30
#define AD7150_OFFSET_DAC_EN_MANU_5         0xA7  //39
#define AD7150_OFFSET_DAC_EN_MANU_6         0xAE  //46
#define AD7150_OFFSET_DAC_EN_MANU_7         0xB6  //54
#define AD7150_OFFSET_DAC_EN_MANU_8         0xBF  //63

//Values for the Setup Register (0x0B)
#define AD7150_CAPACTIVE_INPUT_RANGE_2      0x0B
#define AD7150_CAPACTIVE_INPUT_RANGE_0_5    0x4B
#define AD7150_CAPACTIVE_INPUT_RANGE_1      0x8B
#define AD7150_CAPACTIVE_INPUT_RANGE_4      0xCB

typedef enum
{
  AD7150_OFFSET_AUTO        = AD7150_OFFSET_DAC_EN_AUTO,
  AD7150_OFFSET_DAC_0       = AD7150_OFFSET_DAC_EN_MANU_0,
  AD7150_OFFSET_DAC_1       = AD7150_OFFSET_DAC_EN_MANU_1,
  AD7150_OFFSET_DAC_2       = AD7150_OFFSET_DAC_EN_MANU_2,
  AD7150_OFFSET_DAC_3       = AD7150_OFFSET_DAC_EN_MANU_3,
  AD7150_OFFSET_DAC_4       = AD7150_OFFSET_DAC_EN_MANU_4,
  AD7150_OFFSET_DAC_5       = AD7150_OFFSET_DAC_EN_MANU_5,
  AD7150_OFFSET_DAC_6       = AD7150_OFFSET_DAC_EN_MANU_6,
  AD7150_OFFSET_DAC_7       = AD7150_OFFSET_DAC_EN_MANU_7,
  AD7150_OFFSET_DAC_8       = AD7150_OFFSET_DAC_EN_MANU_8,
} AD7150_adOffset_t;

typedef enum
{
  AD7150_RANGE_0_5          = AD7150_CAPACTIVE_INPUT_RANGE_0_5,
  AD7150_RANGE_0_1          = AD7150_CAPACTIVE_INPUT_RANGE_1,
  AD7150_RANGE_0_2          = AD7150_CAPACTIVE_INPUT_RANGE_2,
  AD7150_RANGE_0_4          = AD7150_CAPACTIVE_INPUT_RANGE_4,
} AD7150_adRange_t;

typedef enum
{
  AD7150_MODE_IDLE          = 0x10,
  AD7150_MODE_CONT_CONV     = 0x11,
  AD7150_MODE_SING_CONV     = 0x12,
  AD7150_MODE_POWER_DOWN    = 0x13,
} AD7150_adMode_t;

struct AD7150_Values {
  uint8_t status;
  uint16_t value;
};

class IO_AD7150
{
protected:
   // Instance-specific properties
   uint8_t              m_i2cAddress;
   AD7150_adOffset_t    m_offset;
   AD7150_adRange_t    m_range;

 public:
  IO_AD7150(uint8_t i2cAddress = AD7150_I2C_ADDRESS);
  void begin();
  void writeRegister(uint8_t reg, uint16_t value);
  void setup();
  void configure(AD7150_adMode_t mode);
  void setOffset(AD7150_adOffset_t offset);
  void setRange(AD7150_adRange_t range);
  AD7150_Values getValue(void);

 private:
};