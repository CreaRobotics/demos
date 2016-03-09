/**
 * @file line_follower.ino
 * @brief Example code for a line follower using the ProtoCREA robot.
 * @author Veronica Gonzalez
 * @copyright CREA Robotica Educativa
 */

#include <Servo.h> 
#include <QTRSensors.h>

// Motor pins.
int L_MOTOR_PIN = 9;
int R_MOTOR_PIN = 10;

Servo l_servo, r_servo;

// Speed variables.
int MAX = 120;
int MIN = 60; 
int L_STOP = 90;
int R_STOP = 95;

// Object for the infrared sensor.
// In this example we have three sensors on analog inputs 0 - 2.
unsigned char inf_sensor[] = {0, 1, 2};
QTRSensorsAnalog qtr(inf_sensor, 3);

void setup() { 

  // Calibration phase.
  // Move the sensor over both extremes.
  int i;
  for (i = 0; i < 250; i++)  // make the calibration take about 5 seconds
  {
    qtr.calibrate();
    delay(20);
  }

  // Open serial por to 9600 bps.
  Serial.begin(9600);

  // Empty serial port.
  Serial.flush();

  // Attach the Servo variable to a pin.
  l_servo.attach(L_MOTOR_PIN);
  r_servo.attach(R_MOTOR_PIN);
}


void loop() { 

  unsigned int sensors[3];

  int position = qtr.readLine(sensors);

  // Compute the "error" from the line position.
  // Error will range from -1000 to +1000.
  int error = position - 1000;

  // Monitoring of the sensor values
  Serial.println(error);

  // Move forward
  l_servo.write(MAX);
  r_servo.write(MIN);

  // Turn right (the line is on the left).
  if (error <= -500){  // the line is on the left. Turn right.
    l_servo.write(MAX);
    r_servo.write(R_STOP);
  }

  // Turn left (the line is on the right).
  if (error >= 500){ 
    l_servo.write(L_STOP);
    r_servo.write(MIN);
  }

} 

