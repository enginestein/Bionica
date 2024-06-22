#define KP 10.4
#define KD 0.4528
#define KI 0.0

float pid(float vel, float last_vel, float pos, float last_pos, float integral);
float pd(float dt, float err_dot, float err);
