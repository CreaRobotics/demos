/**
 * @file follow_me.ino
 * @brief Example code for a follow me mono-sensor using the ProtoCREA robot.
 * @author Raul Perula-Martinez (raules[at]gmail.com)
 * @copyright CREA Robotica Educativa
 */

#include <Servo.h>
#include <Ultrasonic.h>

// constants

// US sensor pins
int ECHO_PIN = 2;
int TRIG_PIN = 3;

// motor pins
int L_MOTOR_PIN = 10;
int R_MOTOR_PIN = 9;

// globals

Ultrasonic us(TRIG_PIN, ECHO_PIN);

Servo l_servo, r_servo;

int dist, last_dist = 0;

// functions

void go_straight()
{
    l_servo.write(0);
    r_servo.write(180);
}

void go_back()
{
    l_servo.write(180);
    r_servo.write(0);
}

void go_stop()
{
    l_servo.write(90);
    r_servo.write(90);
}

/**
 * @brief Initialization.
 */
void setup()
{
    // open serial port to 9600 bps
    Serial.begin(9600);

    // empty serial port
    Serial.flush();

    l_servo.attach(L_MOTOR_PIN);
    r_servo.attach(R_MOTOR_PIN);
}

/**
 * @brief Main loop of the program.
 */
void loop()
{
    // get time between pulses
    long microsec = us.timing();

    // get distances
    dist = us.CalcDistance(microsec, Ultrasonic::CM);

    // control logic
    
    // wait for a close person
    if(dist < 30) {
        // if person is nearer than before
        if(dist < last_dist) {
            // go straight
            go_straight();
        }
        // if person is further than before
        else {
            // go back
            go_back();
        }
    }
    else {
        go_stop();
    }
    
    // save last distance
    last_dist = dist;

    // wait for 1s
    delay(1000);
}




