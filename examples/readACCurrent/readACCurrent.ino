/*!
 * @file  readACCurrent.ino
 * @brief  This example reads Analog AC Current Sensor.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [bernie chen](bernie.chen@dfrobot.com)
 * @maintainer  [Henry Zhao](henry.zhao@dfrobot.com)  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2022-05-20
 * @url  https://github.com/DFRobot/DFRobot_AnalogACurrentSensor
 */

const int ACPin = A2;         // set arduino signal read pin
#define ACTectionRange 20;    // set Non-invasive AC Current Sensor tection range (5A,10A,20A)

// VREF: Analog reference
// For Arduino UNO, Leonardo and mega2560, etc. change VREF to 5
// For Arduino Zero, Due, MKR Family, ESP32, etc. 3V3 controllers, change VREF to 3.3
#define VREF 5.0

float readACCurrentValue()
{
  float ACCurrtntValue = 0;
  float peakVoltage = 0;
  float voltageVirtualValue = 0;   // Vrms
  for (int i = 0; i < 5; i++)
  {
    peakVoltage += analogRead(ACPin);   // read peak voltage
    delay(1);
  }
  peakVoltage = peakVoltage / 5;
  voltageVirtualValue = peakVoltage * 0.707;    // change the peak voltage to the Virtual Value of voltage

  /* The circuit is amplified by 2 times, so it is divided by 2. */
  voltageVirtualValue = (voltageVirtualValue / 1024 * VREF ) / 2;

  ACCurrtntValue = voltageVirtualValue * ACTectionRange;

  return ACCurrtntValue;
}

void setup() 
{
  Serial.begin(115200);
  pinMode(13, OUTPUT);

}

void loop() 
{
  float ACCurrentValue = readACCurrentValue();   // read AC Current Value
  Serial.print(ACCurrentValue);
  Serial.println(" A");
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
}
