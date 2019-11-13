#define RX_PIN      36
#define TX_PIN      26

char last_date = 'N';

void stepmotor_init() {
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  delay(500);
  Serial2.print("ID=123\r\n");
  Serial2.print("ID123:F800\r\n");
}



void moveing_checkout() {
  while (true) {
    Serial2.printf("ID123I\r\n");
    delay(20);
    char c = Serial2.read();
    Serial.println(c);
    if (c != last_date) {
      Serial.println(c);
      last_date = c;
      if (c == 'Y') {
        Serial1.flush();
        break;
      }
    }
    if(M5.BtnB.wasPressed()){
        Serial1.flush();
        Serial2.printf("ID123:X%d\r\n", 0);                
        break;
    }
    M5.update();
  }
}


void LED_Select(uint8_t start_pixel,String direction_flag) {
  
//  fill_solid(leds+start_pixel, 10, CRGB::Blue);
//  FastLED.show(); 
  
  if(direction_flag == "forward"){
    fill_solid(leds, 55, CRGB::Black);
    for (int i = 0 ; i < start_pixel; i++) {
          leds[i] = CRGB::Blue;
          leds[i - 9] = CRGB::Black;
          FastLED.show();
          delay(20);
      }
   }
   
//   if(direction_flag == "backward"){
//    fill_solid(leds, 55, CRGB::Black);
//    for (int i = 0 ; i < start_pixel; i++) {
//          leds[i] = CRGB::Green;
//          leds[i - 9] = CRGB::Black;
//          FastLED.show();
//          delay(20);
//      }
//      }
 }



void Servo_Direction(String Direction) {
  if (Direction == "right") {
    ledcWrite(CHANNEL, 6400);
    delay(500);
    ledcWrite(CHANNEL, 4750);
    delay(200);
  } else {
    ledcWrite(CHANNEL, 3200);
    delay(500);
    ledcWrite(CHANNEL, 4750);
    delay(200);
  }
}

void stepmotor_run(uint8_t number, String Direction, uint8_t number2) {
  LED_Select(number2,"forward");
  Serial2.printf("ID123:X%d\r\n", number);
  moveing_checkout();
  Servo_Direction(Direction);
  Serial2.printf("ID123:X%d\r\n", 0);
  LED_Select(number2,"backward");
  moveing_checkout();
  Display_init();
  delay(100);
//  Serial1.begin(115200, SERIAL_8N1, 16, 17);
  Serial1.flush();
}
