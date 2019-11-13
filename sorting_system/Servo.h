#include "esp32-hal-ledc.h"

#define TIMER_WIDTH 16   //精度
#define CHANNEL 0        //通道
#define FREQUANCE 50  //频率
#define PIN 21     //舵机引脚



void Servo_init(){
  ledcSetup(CHANNEL, FREQUANCE, TIMER_WIDTH);
  ledcAttachPin(PIN, CHANNEL);
}
