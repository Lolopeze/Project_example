#include <Wire.h>
#include <M5Stack.h>
#include "Adafruit_TCS34725.h"
#include "BaseX.h"

// set to false if using a common cathode LED
#define commonAnode true

// our RGB -> eye-recognized gamma color
byte gammatable[256];

//#define deviation_clear 300
//#define deviation_rgb 35

#define deviation_rgb 0.033


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

BASE_X base_x = BASE_X();

bool play_flag = false;
int speed_vaule = -7;
int time_count = 70;
int speed_level = 1;
int wait_time = 60;

bool direction_flag = true;

//int C[]={225,116,49,61};
//int D[]={314,165,80,60};
//int E[]={630,207,262,134};
//int F[]={375,70,175,120};
//int G[]={550,47,167,310}; 
//int A[]={530,127,121,290};
//int B[]={446,200,121,150};
//int HC[]={176,60,60,60};


float C[] = {0.54, 0.26, 0.21};
float D[] = {0.52, 0.19, 0.26};
float E[] = {0.35, 0.22, 0.42};
float F[] = {0.20, 0.30, 0.47};
float G[] = {0.09, 0.60, 0.31};
float A[] = {0.23, 0.55, 0.23};
float B[] = {0.40, 0.30, 0.25};
float HC[] = {0.36,0.33, 0.30};


bool color_value_judge (uint16_t clear , uint16_t red , uint16_t green , uint16_t blue, float* color_stande_value) {
  //  if ((clear<=(color_stande_value[0]+deviation_clear))&&
  //  (clear>=(color_stande_value[0]-deviation_clear))&&
  //  (red<=(color_stande_value[1]+deviation_rgb))&&
  //  (red>=(color_stande_value[1]-deviation_rgb))&&
  //  (green<=(color_stande_value[2]+deviation_rgb))&&
  //  (green>=(color_stande_value[2]-deviation_rgb))&&
  //  (blue<=(color_stande_value[3]+deviation_rgb))&&
  //  (blue>=(color_stande_value[3]-deviation_rgb))){
  //    return true;
  //  }
  //  else{
  //    return false;
  //  }

  float RC = float(red) / float(clear);
  float GC = float(blue) / float(clear);
  float BC = float(green) / float(clear);
 
  Serial.println(RC);
  Serial.println(GC);
  Serial.println(BC);
  if ((RC <= (color_stande_value[0] + deviation_rgb)) &&
      (RC >= (color_stande_value[0] - deviation_rgb)) &&
      (GC <= (color_stande_value[1] + deviation_rgb)) &&
      (GC >= (color_stande_value[1] - deviation_rgb)) &&
      (BC <= (color_stande_value[2] + deviation_rgb)) &&
      (BC >= (color_stande_value[2] - deviation_rgb))) {
    return true;
  }
  else {
    return false;
  }
}
//  if ((red<=(color_stande_value[1]+deviation_rgb))&&
//  (red>=(color_stande_value[1]-deviation_rgb))&&
//  (blue<=(color_stande_value[3]+deviation_rgb))&&
//  (blue>=(color_stande_value[3]-deviation_rgb))){
//    return true;
//  }
//  else{
//    return false;
//  }




void color_value_display(uint16_t clear , uint16_t red , uint16_t green , uint16_t blue , uint16_t color = BLUE ) {

  M5.Lcd.fillRect(0, 30, 110, 100, BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE, color);
  M5.Lcd.setCursor(14, 60);
  M5.Lcd.printf("C:%d", clear);
  M5.Lcd.setCursor(14, 80);
  M5.Lcd.printf("R:%d",red);
  M5.Lcd.setCursor(14, 100);
  M5.Lcd.printf("G:%d",green);
  M5.Lcd.setCursor(14, 120);
  M5.Lcd.printf("B:%d", blue);
}



void color_index(uint16_t clear , uint16_t red , uint16_t green , uint16_t blue) {

  color_value_display(clear , red , green , blue , BLACK);
  if (play_flag) {
    if (color_value_judge(clear , red , green , blue, C)) {
      speaker_tone("C");
      color_value_display(clear , red , green , blue , 0xF800);
    }
    else if (color_value_judge(clear , red , green , blue, D)) {
      speaker_tone("D");
      color_value_display(clear , red , green , blue, 0xF200);
    }
    else if (color_value_judge(clear , red , green , blue, E)) {
      speaker_tone("E");
      color_value_display(clear , red , green , blue , 0xFFE0);
    }
    else if (color_value_judge(clear , red , green , blue, F)) {
      speaker_tone("F");
      color_value_display(clear , red , green , blue , 0x07E0);
    }
    else if (color_value_judge(clear , red , green , blue, G)) {
      speaker_tone("G");
      color_value_display(clear , red , green , blue , 0x001F);
    }
    else if (color_value_judge(clear , red , green , blue, A)) {
      speaker_tone("A");
      color_value_display( clear , red , green , blue, 0x780F );
    }
    else if (color_value_judge(clear , red , green , blue, B)) {
      speaker_tone("B");
      color_value_display(clear , red , green , blue , 0xFC9F);
    }
    else if (color_value_judge(clear , red , green , blue, HC)) {
      speaker_tone("HC");
      color_value_display(clear , red , green , blue , 0x7800 );
    }
    else {
      speaker_tone("nothing");
    }
  }
}

void speaker_tone(String tone_name) {
  //      time_count--;

  if (tone_name == "C") {
    M5.Speaker.tone(262, 125);
    Serial.print("C");
  }
  else if (tone_name == "D") {
    M5.Speaker.tone(294, 125);
    Serial.print("D");
  }
  else if (tone_name == "E") {
    M5.Speaker.tone(330, 125);
    Serial.print("E");
  }
  else if (tone_name == "F") {
    M5.Speaker.tone(349, 125);
    Serial.print("F");
  }
  else if (tone_name == "G") {
    M5.Speaker.tone(392, 125);
    Serial.print("G");
  }
  else if (tone_name == "A") {
    M5.Speaker.tone(440, 125);
    Serial.print("A");
  }
  else if (tone_name == "B") {
    M5.Speaker.tone(494, 125);
    Serial.print("B");
  }
  else if (tone_name == "HC") {
    M5.Speaker.tone(532, 125);
    Serial.print("HC");
  }
  delay(wait_time);
  M5.Speaker.mute();
}


void display_init() {

  M5.Lcd.fillRect(0, 0, 320, 30, BLUE);
  M5.Lcd.fillRect(0, 210, 320, 30, BLUE);
  M5.Lcd.setCursor(14, 5);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE, BLUE);
  M5.Lcd.print("M5Stack Color Music Box");
//  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(14, 220);
  M5.Lcd.print("F/R");
  M5.Lcd.setCursor(115, 220);
  M5.Lcd.print("Run/Stop");
  M5.Lcd.setCursor(250, 220);
  M5.Lcd.print("Speed");
  M5.Lcd.fillRect(240, 60, 65, 18, BLUE);
  M5.Lcd.fillRect(240, 90, 65, 18, BLUE);
  M5.Lcd.fillRect(240, 120,65, 18, GREEN);
  M5.Lcd.setCursor(14, 190);
  M5.Lcd.print("Forward");
  M5.Lcd.setCursor(220, 190);
  M5.Lcd.setTextColor(WHITE, BLUE);
  M5.Lcd.printf("Speed:%d",speed_level);
      
}



void display_change(String play_status) {

  if (play_status == "stop") {
    M5.Lcd.fillRect(110, 30, 110, 180, BLACK);
    M5.Lcd.fillTriangle(140, 80, 140, 160, 200, 120, GREEN);
    M5.Lcd.drawCircle(160, 120, 50, GREEN);
    M5.Lcd.drawCircle(160, 120, 51, GREEN);
  }
  else {
    M5.Lcd.fillRect(110, 30, 110, 180, BLACK);
    M5.Lcd.fillRect(140, 85, 15, 75, BLUE);
    M5.Lcd.fillRect(170, 85, 15, 75, BLUE);
    M5.Lcd.drawCircle(160, 120, 50, BLUE);
    M5.Lcd.drawCircle(160, 120, 51, BLUE);
  }
}

void display_tone(String tone_name, uint8_t tone_color) {

  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.setCursor(10, 100);
  M5.Lcd.print(tone_name);

}




void setup() {
  // put your setup code here, to run once:
  delay(100);
  M5.begin(true, false, false);
  M5.Power.begin();
  display_init();
  M5.Speaker.setVolume(5);
  Serial.begin(115200);
  while (!tcs.begin()) {
    Serial.println("No TCS34725 found ... check your connections");
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.drawString("No Found sensor.", 50, 100, 4);
    delay(1000);
  }
  tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_50MS);
  tcs.setGain(TCS34725_GAIN_4X);
  display_change("stop");

}

void loop() {

  uint16_t clear, red, green, blue;
  tcs.getRawData(&red, &green, &blue, &clear);
  Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);
  Serial.println();

  if (M5.BtnA.wasPressed())
  {
    direction_flag = !direction_flag;
    if(direction_flag){
       M5.Lcd.setCursor(14, 190);
       M5.Lcd.setTextColor(WHITE, BLUE);
       M5.Lcd.print("Forward");
    }else{
       M5.Lcd.setCursor(14, 190);
       M5.Lcd.setTextColor(WHITE, BLUE);
       M5.Lcd.print("Reverse");
    }
    if (play_flag) {
        if(direction_flag){
           base_x.SetMotorSpeed(1, speed_vaule);
        }else{
           base_x.SetMotorSpeed(1, -speed_vaule);
        }
    }
  }
  
  if (M5.BtnC.wasPressed())
  {

    speed_level++;
    if (speed_level>3){ 
      speed_level = 1;
      wait_time = 60;
      M5.Lcd.fillRect(240, 60, 65, 18, BLUE);
      M5.Lcd.fillRect(240, 90, 65, 18, BLUE);
      M5.Lcd.fillRect(240, 120,65, 18, GREEN);
     }
    else{
      if(speed_level == 2){
        speed_vaule = 9;
        wait_time = 50;
        M5.Lcd.fillRect(240, 60, 65, 18, BLUE);
        M5.Lcd.fillRect(240, 90, 65, 18, GREEN);
        M5.Lcd.fillRect(240, 120,65, 18, GREEN);
       }
       else{
        speed_vaule = 11;
        wait_time = 40;
        M5.Lcd.fillRect(240, 60, 65, 18, GREEN);
        M5.Lcd.fillRect(240, 90, 65, 18, GREEN);
        M5.Lcd.fillRect(240, 120,65, 18, GREEN);
       }
    }
    if (play_flag) {
        if(direction_flag){
            base_x.SetMotorSpeed(1, speed_vaule);
          }else{
            base_x.SetMotorSpeed(1, -speed_vaule);
          }
    }
    M5.Lcd.setCursor(220, 190);
    M5.Lcd.setTextColor(WHITE, BLUE);
    M5.Lcd.printf("Speed:%d",speed_level);
  }
  if (M5.BtnB.wasPressed())
  {
    play_flag = !play_flag;
    Serial.print(play_flag);
    if (play_flag) {
      if(direction_flag){
        base_x.SetMotorSpeed(1, speed_vaule);
      }else{
        base_x.SetMotorSpeed(1, -speed_vaule);
      }
      display_change("play");
    }
    else {
      base_x.SetMotorSpeed(1, 0);
      display_change("stop");
    }
  }
  color_index(clear, red, green, blue);
  M5.update();
}
