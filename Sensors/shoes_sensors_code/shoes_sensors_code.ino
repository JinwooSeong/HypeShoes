#include <Adafruit_ADS1X15.h>
#include <Wire.h>

#define I2C_SDA 17
#define I2C_SCL 21

const int fsrPin0 = 35;
const int fsrPin1 = 34;

TwoWire I2CADS = TwoWire(0);
Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
// Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */

void setup(void)
{
  Serial.begin(115200);
  Serial.println("Hello!");
  pinMode(fsrPin0, INPUT);
  pinMode(fsrPin1, INPUT);


  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  I2CADS.begin(I2C_SDA, I2C_SCL, 100000);

  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

  if (!ads.begin(0x48, &I2CADS)) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
}

void loop(void)
{
  int16_t adc0, adc1, adc2, adc3;
  float volts0, volts1, volts2, volts3;

  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

  // volts0 = ads.computeVolts(adc0);
  // volts1 = ads.computeVolts(adc1);
  // volts2 = ads.computeVolts(adc2);
  // volts3 = ads.computeVolts(adc3);

  Serial.println("-----------------------------------------------------------");
  // Serial.print("AIN0: "); Serial.print(adc0); Serial.print("  "); Serial.print(volts0); Serial.println("V");
  // Serial.print("AIN1: "); Serial.print(adc1); Serial.print("  "); Serial.print(volts1); Serial.println("V");
  // Serial.print("AIN2: "); Serial.print(adc2); Serial.print("  "); Serial.print(volts2); Serial.println("V");
  // Serial.print("AIN3: "); Serial.print(adc3); Serial.print("  "); Serial.print(volts3); Serial.println("V");

  int fsrRead0 = analogRead(fsrPin0);
  int fsrRead1 = analogRead(fsrPin1);
  // // if(analogRead(fsrPin) >= 10){
  // float voltage0 = fsrRead0 * (3.3 / 1023.0);
  // Serial.print(voltage0);
  // Serial.print("kg");
  // Serial.print(" => ");
  // Serial.println(fsrRead0);

  Serial.print("0: "); Serial.print(adc0); Serial.print("  "); Serial.print(adc0 * (3.3 / 1023.0)); Serial.println("V(kg)");
  // Serial.print("0: "); Serial.print(fsrRead0); Serial.print("  "); Serial.print(fsrRead0 * (3.3 / 1023.0)); Serial.println("V(kg)");
  Serial.print("1: "); Serial.print(adc1); Serial.print("  "); Serial.print(adc1 * (3.3 / 1023.0)); Serial.println("V(kg)");
  Serial.print("2: "); Serial.print(adc2); Serial.print("  "); Serial.print(adc2 * (3.3 / 1023.0)); Serial.println("V(kg)");
  Serial.print("3: "); Serial.print(adc3); Serial.print("  "); Serial.print(adc3 * (3.3 / 1023.0)); Serial.println("V(kg)");
  Serial.print("4: "); Serial.print(fsrRead1); Serial.print("  "); Serial.print(fsrRead1 * (3.3 / 1023.0)); Serial.println("V(kg)");
  Serial.println();

  delay(1000);
}