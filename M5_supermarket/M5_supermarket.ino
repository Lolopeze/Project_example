#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <M5Stack.h> 
#include <ArduinoJson.h>




#include "SPIFFS.h"
#include "AudioFileSourceSPIFFS.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include "hx711.h"

AudioGeneratorMP3 *mp3;
AudioFileSourceSPIFFS *file;
AudioOutputI2S *out;
AudioFileSourceID3 *id3;


#include <FastLED.h>
#define NUM_LEDS 10
#define DATA_PIN 15

HX711 scale(36, 26);
CRGB leds[NUM_LEDS];

int weight;

#define FRONT 4

#define X_LOCAL 40
#define Y_LOCAL 40
#define X_F 30
#define Y_F 30

StaticJsonDocument<500> doc;

int  temp1,temp2,temp3,temp4,temp5,temp6,temp7 = 0;

#include "index_test.h"  //Web page header file

//===============================================================
// Initialize every attribut we need
//===============================================================
WebServer server(80);
 
//Enter your SSID and PASSWORD
const char* ssid = "M5Pay";
const char* password = "";

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================


void header(const char *string, uint16_t color){
    M5.Lcd.fillScreen(color);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLUE);
    M5.Lcd.fillRect(0, 0, 320, 30, TFT_BLUE);
    M5.Lcd.setTextDatum(TC_DATUM);
    M5.Lcd.drawString(string, 160, 3, 4);  
}






void homepage() {
 String s = MAIN_page; //Read HTML contents
 Serial.println("hello");
 server.send(200, "text/html", s); //Send web page
}
 
void get_list() {
  String S = "";
  serializeJson(doc, S);
  server.send(200, "text/html", S);
  fill_solid(leds, 10, CRGB::Green);
  delay(50);
  FastLED.show();
}

//"{\"banana(200g)\":200,\"apple(4￥)\":2,\"peach(1￥)\":4}"
void paid() {
  server.send(200, "text/html", "ok");
  fill_solid(leds, 10, CRGB::Blue); 
  FastLED.show();
  delay(500);
  fill_solid(leds, 10, CRGB::Black); 
  FastLED.show();
  M5.Speaker.beep();
  M5.Lcd.clear(BLACK);

  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(55, 100);
  M5.Lcd.print("Paid Successful"); 
  doc.clear();
  temp1,temp2,temp3,temp4,temp5,temp6,temp7 = 0;
}
//===============================================================
// Setup
//===============================================================
 



void Prodcut_info(){
   while(true){
    String comData = "1234";
    if(Serial1.available()){
      comData = "";
      while(Serial1.available()){
        char ch = Serial1.read();
        if(ch != '\r'){
          comData += ch;
        }else{
           fill_solid(leds, 10, CRGB::White); 
           FastLED.show();
           M5.Speaker.beep();
           M5.update();
           break;
        }
      }
//    delay(400);
    Serial.println(comData);
    M5.Lcd.fillRect(0,90, 320, 50, TFT_BLACK);
    weight =scale.getGram();
    Prodcut_info_handle(comData,weight);
    fill_solid(leds, 10, CRGB::Black); 
    FastLED.show(); 
    break;
    }
   }
   
}

void Prodcut_info_handle(String comData, int weight){
   Serial.print("helloworld");
   if(comData == "1"){
      M5.Lcd.setCursor(0, Y_LOCAL+Y_F*1,FRONT);
      M5.Lcd.println("Product Name: watchband");
      M5.Lcd.printf("Weight: %d g", weight);
      M5.Lcd.println();
      M5.Lcd.printf("Price: %d", weight * 2);
      temp1 += weight;
      doc["watchband"] = temp1;


     }
   if(comData == "2"){
      M5.Lcd.setCursor(0, Y_LOCAL+Y_F*1,FRONT);
      M5.Lcd.println("Product Name: big-orange-wheel");
      M5.Lcd.printf("Weight: %d g", weight);
      M5.Lcd.println();
      M5.Lcd.printf("Price: %d", weight * 4);
      temp2 += weight;
      doc["big-orange-wheel"] = temp2;
      Serial.println(temp2);

     }
   if(comData == "3"){
      M5.Lcd.setCursor(0, Y_LOCAL+Y_F*1,FRONT);
      M5.Lcd.println("Product Name: orange-wheel");
      M5.Lcd.printf("Weight: %d g", weight);
      M5.Lcd.println();
      M5.Lcd.printf("Price: %d", weight * 6);
      temp3 += weight;
      doc["orange-wheel"] = temp3;
      Serial.println(temp3);
     }
   if(comData == "4"){
      M5.Lcd.setCursor(0, Y_LOCAL+Y_F*1,FRONT);
      M5.Lcd.println("Product Name: mecanum-wheel");
      M5.Lcd.printf("Weight: %d g", weight);
      M5.Lcd.println();
      M5.Lcd.printf("Price: %d", weight * 8);    
      temp4 += weight;
      doc["mecanum-wheel"] = temp4;
      Serial.println(temp4);
     }
   if(comData == "5"){
      int weight = scale.getGram();
      M5.Lcd.setCursor(0, Y_LOCAL+Y_F*1,FRONT);
      M5.Lcd.println("Product Name: big-blue-wheel");
      M5.Lcd.printf("Weight: %d g", weight);
      M5.Lcd.println();
      M5.Lcd.printf("Price: %d", weight * 5);
      temp5 += weight;
      doc["big-blue-wheel"] = temp5;
      Serial.println(temp5);
     }
   if(comData == "6"){
//      int weight = scale.getGram();
      M5.Lcd.setCursor(0, Y_LOCAL+Y_F*1,FRONT);
      M5.Lcd.println("Product Name: servo");
      M5.Lcd.printf("Weight: %d g", weight);
      M5.Lcd.println();
      M5.Lcd.printf("Price: %d", weight * 1);
      temp6 += weight;
      doc["servo"] = temp6;
      Serial.println(temp6);
     }
   if(comData == "7"){
//      int weight = scale.getGram();
      M5.Lcd.setCursor(0, Y_LOCAL+Y_F*1,FRONT);
      M5.Lcd.println("Product Name: white-wheel");
      M5.Lcd.printf("Weight: %d g", weight);
      M5.Lcd.println();
      M5.Lcd.printf("Price: %d", weight * 7);
      temp7 += weight;
      doc["white-wheel"] = temp7;
      Serial.println(temp7);
     }
     Serial.print("************");
}

void setup(void){
  M5.begin();
  SPIFFS.begin();
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  header("M5 Pay", TFT_BLACK);
  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  M5.Lcd.setCursor(X_LOCAL, Y_LOCAL,FRONT);

  Serial1.begin(115200, SERIAL_8N1, 16, 17);
  scale.setOffset(scale.averageValue());


//ESP32 connects to your wifi -----------------------------------
  WiFi.softAP(ssid, password); //Connect to your wifi    
  Serial.println("Connecting to ");
  Serial.print(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());  //IP address assigned to your ESP
//----------------------------------------------------------------
  server.on("/", homepage); 
  server.on("/get_list", get_list);
  server.on("/paid", paid);

  server.begin();                  //Start server
  Serial.println("HTTP server started");
  fill_solid(leds, 10, CRGB::Black);
  FastLED.show();
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(95, 100);
  M5.Lcd.print("SCANNING"); 
 
}


//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void loop(void){
//  Serial.println(scale.getGram(););
  server.handleClient();
   M5.update();
  if (M5.BtnA.wasPressed()) {
    
    Serial1.flush();
    
    delay(20);
    M5.Lcd.clear(BLACK);
    header("M5 Pay", TFT_BLACK);
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(95, 100);
    M5.Lcd.print("SCANNING");
    fill_solid(leds, 10, CRGB::Black);
    FastLED.show();
    Prodcut_info();
    
  } else if (M5.BtnB.wasPressed()) {
    M5.Lcd.clear(BLACK);
    
    fill_solid(leds, 10, CRGB::Yellow);
    FastLED.show();
    M5.Lcd.setCursor(5,10,4);
    M5.Lcd.println("Please scan QR to checkout");
    M5.Lcd.qrcode("192.168.4.1", 70, 50, 180, 6);
  } else if (M5.BtnC.wasPressed()) {
    M5.Lcd.clear(BLACK);
    scale.setOffset(scale.averageValue());
    fill_solid(leds, 10, CRGB::Black);
    FastLED.show(); 
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(25, 100);
    M5.Lcd.print("Calibration Completed"); 
  } 
  
}




//          CRGB::Black,
//          CRGB::Black,
//          CRGB::Red,
//          CRGB::Yellow,
//          CRGB::Green,
//          CRGB::Blue,
//          CRGB::Purple,
//          CRGB::Black,
