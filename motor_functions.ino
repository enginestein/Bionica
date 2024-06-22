#include "motor_functions.h"

static bool reverse = false;

void motor_init() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(PINK_PIN, OUTPUT);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  digitalWrite(PINK_PIN, LOW);
  analogWriteResolution(ANALOG_RES); 
}

void set_voltage(float volt) {
  if (volt >= 2.5)
    volt = 2.5;
  else if (volt <= 0)
    volt = 0;
  uint16_t set_point = (volt / 2.27) * 2827;
  analogWrite(GREY_PIN, set_point);
}

void set_direction(bool dir) {
  if (dir)
    digitalWrite(BLUE_PIN, HIGH);
  else
    digitalWrite(BLUE_PIN, LOW);
}

void set_speed(float speed) {
  speed = constrain(speed, -100, 100);
  float voltage;

  if (speed <= 0) {
    if (reverse == false) {
      set_voltage(3.24);
      delay(DEAD_TIME_MS);
    }
    else {
      speed = -speed;
      voltage = speed_to_voltage(speed);
      set_voltage(voltage);

    }
    reverse = true;
    set_direction(HIGH);
  }
  else {
    if (reverse == true) {
      set_voltage(3.24);
      delay(DEAD_TIME_MS);
    }
    else {
      voltage = speed_to_voltage(speed);
      set_voltage(voltage);
      set_direction(LOW);
    }
    reverse = false;
    set_direction(LOW);
  }
}

float speed_to_voltage(float speed) {
  float zero_speed_voltage = 2.27;
  if (fabs(speed) <= DEAD_ZONE)
    return 3.1;
  else
    return zero_speed_voltage - zero_speed_voltage / 255 * speed;
}


void enable() {
  enable_speed();
  set_direction(true);
  digitalWrite(PINK_PIN, HIGH);
  delay(100);
  digitalWrite(RED_PIN, HIGH);
}

void disable() {
  disable_speed();
  digitalWrite(RED_PIN, LOW);
  digitalWrite(PINK_PIN, LOW);
}

void enable_speed() {
  analogWrite(GREY_PIN, 255);
}

void disable_speed() {
  analogWrite(GREY_PIN, 0);
}

void btn_wait() {
  bool active = false;
  bool btn_state = !active;
  bool last_state = !active;
  while (true) {
    btn_state = digitalRead(BTN_PIN);
    if ((btn_state == last_state) && (btn_state == active))
      break;
    last_state = btn_state;
  }
  Serial.println("A button was pressed");
}
