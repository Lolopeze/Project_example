
#include <M5Stack.h>
#include "Display.h"
#include "LED.h"
#include "Servo.h"
#include "StepMotor.h"
#include "M5StickV.h"


void setup() {
  M5.begin();
  Display_init();
  LED_init();
  Servo_init();
  stepmotor_init();
  M5StickV_init();
  ledcWrite(CHANNEL, 4800);
  
}


void loop() {
    if(M5.BtnA.wasPressed()){                
      Serial2.printf("ID123:X%d\r\n", 55);
    }
    if(M5.BtnB.wasPressed()){                
      Serial2.printf("ID123:X%d\r\n", 55);
    }
    if(M5.BtnC.wasPressed()){                
      Serial2.print("ID123Z\r\n");
      Serial2.print("ID123:F800\r\n");
    }
    classification();
    LED_show();
    M5.update();
}
