#include "encoder_functions.h"
#include "motor_functions.h"
#include "joystick_functions.h"
#include "pid_functions.h"

#define ANGLE_OFFSET 0
#define BTN_PIN 2
#define N 10 
#define ALPHA 0.25 
float angle_lim[2] = {90, 165};
void sense();
void process();
void actuate();

float iir_filter(float actual, float last_est, float alpha);
float rolling_avg_filter(float actual, float *last_ests, int n);

float setpoint = 0; 
float input = 0;
bool done = false;

unsigned long long duration = 5000;
unsigned long long start_time = 0;
unsigned long long last_time = 0;
unsigned long long time = 0;
unsigned long long refresh_time = 0;
unsigned long long refresh_period = 4000;
float dt = 0;

float raw_angle = 0;
float last_angle = 0;
float angle = 0;

float last_speeds[N] = {0};
float speed = 0;


int joystick_x = 0;
int joystick_y = 0;
bool joystick_btn = 0;


bool btn_pressed = false;


float err = 0;
float last_err = 0;
float err_dot = 0;

void setup() {
  Serial.begin(9600);
  
  motor_init();
  spi_init();
  joystick_init();

  
  pinMode(BTN_PIN, INPUT_PULLUP);


  
  for (int i = 0; i < 20; i++) {
    sense();
    process();
    delay(30);
  }
  done = false;
  Serial.printf("Current angle: %f\n", angle);
 
  Serial.println("Test Begin");
  for (int i = 0; i < 3; i++) {
    sense();
    process();
    delay(30);
  }
  done = false;

  
  enable();  
  start_time = millis();
  
}

void loop() {
  sense();
  process();
  actuate();
  Serial.print(joystick_x);
  Serial.print(' ');
  Serial.print(input);
  Serial.print(' ');
  Serial.println(get_angle());
  delay(20);
  
}

void sense() {
  
  float measurement = get_angle();
  bool btn_read = digitalRead(BTN_PIN);
  int joystick_data[3] = {0};
  measure_joystick(joystick_data);

  
  if (measurement)
    raw_angle = measurement;

  
  btn_pressed = !btn_read; 

  
  joystick_x = -joystick_data[0];
  joystick_y = joystick_data[1];
  joystick_btn = !joystick_data[2]; 

  
  last_time = time;
  time = millis();
}


void process() {
  
  last_angle = angle;
  angle = iir_filter(raw_angle - ANGLE_OFFSET, last_angle, ALPHA);

  
  long long DT = time - last_time;
  dt = (float)DT / 1000; 
  float raw_speed = (angle - last_angle) / dt;

  
  for (int i = 0; i < N - 1; i++)
    last_speeds[i] = last_speeds[i + 1];
  last_speeds[N - 1] = speed;
  
  speed = rolling_avg_filter(raw_speed, last_speeds, N);

  int max_input = 255;
  input = mapFloat(joystick_x, -515, 515, -max_input, max_input);
  input = constrain(input, -max_input, max_input);
  if (angle >= angle_lim[1] && input >= 0)
    input = 0;
  else if (angle <= angle_lim[0] && input <= 0)
    input = 0;
}

void actuate() {
  set_speed(input);
}
  
float iir_filter(float actual, float last_est, float alpha) {
  return alpha * actual + (1 - alpha) * last_est;
}
  
float rolling_avg_filter(float actual, float *last_ests, int n) {
  float est = actual;
  for (int i = 0; i < n; i++)
    est += last_ests[i];
  est /= n;
  return est;
}
