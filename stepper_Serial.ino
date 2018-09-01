
#include <math.h>

#define STEP0 9
#define DIR0 8
#define EN0 10

#define STEP1 11
#define DIR1 12
#define EN1 13

long COUNTS_PER_REV = 3200;

int posCurrent = 0;
int pos = 0; // can this be here or is it constantly being rewritten to 0?
bool initialized = false;

void setup()
{
  // initialize IO
  pinMode(STEP0, OUTPUT);
  // pinMode(STEP1, OUTPUT);
  pinMode(DIR0, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(EN0, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT); //Dave added this for troubleshooting

  // enable motors on startup
  digitalWrite(STEP0, LOW);
  // digitalWrite(STEP1, LOW);
  digitalWrite(EN0, HIGH);
  digitalWrite(EN1, HIGH);

  // initialize serial
  Serial.begin(115200);
  Serial.setTimeout(500); // Drew says this isn't important
}

void loop()
{
  while (true)
  {
    // wait for new serial data, then process
    if (Serial.available() > 0)
    {
      //Parsing the serial command coming from server.py? or is it app.js?
      // float angle0 = Serial.readStringUntil(' ').toFloat();
      String command = Serial.readStringUntil(' '); // get string command and consume the string, leaving the position number
      pos = Serial.readStringUntil('\n').toInt();   // Now with the "step part of the string consumed, read pos which is what remains
      //Serial.write("OK\n");     // write "ok" cuz Fogleman wanted me to
      // Serial.write(posCurrent);
      // Serial.write("\n");

      if (initialized = false)
      {
        posCurrent = pos;
        initialized = true;
      }

      else if (posCurrent < pos)
      {
        stepMove(1);
        posCurrent = pos + 1;
        Serial.print(pos);
        Serial.print("\n");
        Serial.print(posCurrent);
        Serial.print("\n");
      }

      else if (posCurrent > pos)
      {
        stepMove(0); // it's a bool so it can only be zero or 1 but this zero represents a backwards step
        posCurrent = pos - 1;
        Serial.print(pos);
        Serial.print("\n");
        Serial.print(posCurrent);
        Serial.print("\n");
      }

      else
      {
        Serial.print('NO CHANGE');
      }
    }
  }
}

void stepMove(bool dire)
{
  // here we are setting direction pins
  if (dire == 0)
  {
    digitalWrite(DIR0, HIGH);
  }
  else if (dire == 1)
  {
    digitalWrite(DIR0, LOW);
  }
  //here we are executing one step, then setting the step pin low again
  
  for (int i = 0; i <= 100; i++)
  {
    digitalWrite(STEP0, HIGH);
    delayMicroseconds(5);
    digitalWrite(STEP0, LOW);
    delay(10);
  }
  //              digitalWrite(LED_BUILTIN, HIGH);   // Troubleshooting
  //              delay(1000);                       // Troubleshooting
  //              digitalWrite(LED_BUILTIN, LOW);    // Troubleshooting
}

// move each motor a certain number of steps over time period (in milliseconds)
// void smoothMove(long move0, long move1, long duration_ms) {
//     // check for negative moves
//     if (move0 < 0) {
//         digitalWrite(DIR0, HIGH);
//         move0 = -move0;
//     } else {
//         digitalWrite(DIR0, LOW);
//     }
//     if (move1 < 0) {
//         digitalWrite(DIR1, HIGH);
//         move1 = -move1;
//     } else {
//         digitalWrite(DIR1, LOW);
//     }

//     // calculate time between each step for each motor
//     double step0_micros = (1000.0 * duration_ms) / move0;
//     double step1_micros = (1000.0 * duration_ms) / move1;

//     // setup time loop
//     long startTime = micros();
//     long refTime0 = startTime + step0_micros;
//     long refTime1 = startTime + step1_micros;

//     while (move0 > 0 || move1 > 0) {
//         // get current time
//         long now = micros();
//         bool step0 = false;
//         bool step1 = false;

//         // see if either stepper should take a step
//         if (move0 > 0 && now > refTime0) {
//             step0 = true;
//             move0--;
//             refTime0 += step0_micros;
//         }
//         if (move1 > 0 && now > refTime1) {
//             step1 = true;
//             move1--;
//             refTime1 += step1_micros;
//         }

//         // do the step
//         if (step0) {
//             digitalWrite(STEP0, HIGH);
//         }
//         if (step1) {
//             digitalWrite(STEP1, HIGH);
//         }
//         delayMicroseconds(5);
//         if (step0) {
//             digitalWrite(STEP0, LOW);
//         }
//         if (step1) {
//             digitalWrite(STEP1, LOW);
//         }
//     }
// }
