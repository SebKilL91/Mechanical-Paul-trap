// Include the AccelStepper library:
#include <AccelStepper.h>

// Define number of steps per revolution:
const int steps = 200;
float hz = 4;
float spd = hz * steps;

// Give the motor control pins names
#define dir 2
#define stp 3

// Define the AccelStepper interface type:
#define MotorInterfaceType 1

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(MotorInterfaceType, stp, dir);

void setup() {
  // Set the maximum steps per second:
  stepper.setMaxSpeed(hz * steps);

  // Set starting speed to 0
  hz = 0;
  spd = hz * steps;
  stepper.setSpeed(spd);

  // Initialize the Seriell monitor
  Serial.begin(9600);
  Serial.println("ready");
  Serial.println(hz);
}

void loop() {

  // Map the value from the potentiometer to a frequency between 0 - 4 Hz
  // with a stepsize of 0.1 Hz
  hz = int(map(analogRead(A0), 0, 1024, -0.1, 41));
  hz = hz/10;
  if (hz > (spd/steps + 0.09) or hz < (spd/steps - 0.11)) {
    if (hz < 0.21) { hz = 0; }
    Serial.println(hz);
    spd = hz * steps;
  }

  // Set the speed of the motor in steps per second:
  stepper.setSpeed(spd);
  // Step the motor with constant speed as set by setSpeed():
  stepper.runSpeed();
}
