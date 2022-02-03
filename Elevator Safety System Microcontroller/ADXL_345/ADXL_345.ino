#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

float sum = 0, avg = 0, value[11];
int i, check = 0;
int in1 = 5;
int in2 = 6;

void setup(void)
{
  sensors_event_t event;
  accel.getEvent(&event);
  int temp;

  Serial.begin(9600);
  //first = sum = event.acceleration.z * 20;
  if (!accel.begin())
  {
    Serial.println("No ADXL345 sensor detected.");
    while (1);
  }
  else
  {
    for (i = 0; i < 10; i++) {
      temp = event.acceleration.z * 20;
      value[i] = temp;
      sum += temp;
    }
    value[10] = event.acceleration.z * 20;
  }
}


void loop(void)
{
  sensors_event_t event;
  accel.getEvent(&event);
  /*   Serial.print("X: "); Serial.print(event.acceleration.x * 20 ); Serial.print("  ");
     Serial.print("Y: "); Serial.print(event.acceleration.y * 20 ); Serial.print("  ");
     Serial.print("Z: "); Serial.print(event.acceleration.z * 20 ); Serial.print("  ");
     Serial.println("m/s^2 ");
    // delay(100);
  */
  // value[10] means last value[0]means first
  //  value[10] = event.acceleration.z * 20;

  sum += (value[10] - value[0]);
  avg = sum / 10;

  for (i = 0; i < 10; i++)
  {
    value[i] = value[i + 1];
  }

  value[10] = event.acceleration.z * 20;

  check = avg - value[10];
  check = abs(check);

  Serial.print("First "); Serial.print(value[0] ); Serial.print("  ");
  Serial.print("Last "); Serial.print(value[10] ); Serial.print("  ");
  Serial.print("Avg "); Serial.print(avg ); Serial.print("  ");
  Serial.print("Diff "); Serial.print(check ); Serial.println("  ");

  if ( check > 200 )
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(500);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);

  }


}
