#include "joystick_functions.h"

static int x_offset = 0;
static int y_offset = 0;

void joystick_init() {
  pinMode(VRX_PIN, INPUT);
  pinMode(VRY_PIN, INPUT);
  pinMode(JOYSTICK_BUTTON_PIN, INPUT_PULLUP);
  calibrate_joystick();
}

void calibrate_joystick() {
  x_offset = 0; y_offset = 0;
  int n = 500;
  long long x_sum = 0, y_sum = 0;
  int measurements[3] = {0};

  for (int i = 0; i < n; i++) {
    measure_joystick(measurements);
    x_sum += measurements[0];
    y_sum += measurements[1];
  }
  x_offset = x_sum / (n+1);
  y_offset = y_sum / (n+1);
  Serial.println(x_offset);
}

void measure_joystick(int values[3]) {
  int x = analogRead(VRX_PIN) - x_offset;
  int y = analogRead(VRY_PIN) - y_offset;
  int btn = digitalRead(JOYSTICK_BUTTON_PIN);
  values[0] = x;
  values[1] = y;
  values[2] = btn;
}
