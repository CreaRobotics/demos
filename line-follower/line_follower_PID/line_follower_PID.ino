
/**
 * @file line_follower_PID.ino
 * @brief Example code for a line follower with PID using the ProtoCREA robot.
 * @author Veronica Gonzalez
 * @copyright CREA Robotica Educativa
 */

#include <Servo.h> 
#include <QTRSensors.h>

// Motor pins.
int L_MOTOR_PIN = 9;
int R_MOTOR_PIN = 10;

Servo l_servo, r_servo;

// Speed variables
int MAX = 120; //120
int MIN = 60; //60

// PID variables
// A PD controller is enough to control the robot.
float KP = 0.1; 
float KD = 0.1;
int lastError = 0;

// Object for the infrared sensor.
// In this example we have three sensors on analog inputs 0 - 2.
unsigned char inf_sensor[] = {
  0, 1, 2};
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
  
  //Monitoring of the error value
  Serial.println(error);
  
  // Set the motor speed according to the KP and KD variables.
  int m_speed = KP*error + KD*(error - lastError);
  lastError = error;

  int lm_Speed = (MAX - m_speed);
  int rm_Speed = (MIN - m_speed);

  l_servo.write(lm_Speed);
  r_servo.write(rm_Speed);

} 
