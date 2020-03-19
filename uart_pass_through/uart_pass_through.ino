//Reset resistance is not soldered. If necessary, weld it yourself.

#include <M5Stack.h>

#define RESET_PIN   5   


bool status_flag = true;
int UART_PIN_SELECT = 0;
int UART_BAUD_SELECT = 0;
int UART_PIN_LIST[3][2]= {{16,17},{22,21},{36,26}};
int UART_BAUD_LIST[] = {115200,961200,9600};
int RX_PIN = 16;
int TX_PIN = 17;
int BAUD = 115200;


void display_init() {
  M5.Lcd.fillRect(0, 27, 320, 190, BLACK);
  M5.Lcd.fillRect(0, 0, 320, 27, BLUE);
  M5.Lcd.setTextColor(WHITE, BLUE);
  M5.Lcd.setCursor(14, 60);
  M5.Lcd.drawTriangle(280, 100, 230, 120, 230, 80, GREEN);
  M5.Lcd.drawTriangle(160, 100, 210, 120, 210, 80, GREEN);
  M5.Lcd.drawString("Select-RX/TX",25, 220, 2);
  M5.Lcd.drawString("Select-BAUD",125, 220, 2);
  M5.Lcd.drawString("UART PASS THROUGH.",0, 0, 4);
  M5.Lcd.drawString(" RX : G"+String(RX_PIN)+" ",14, 60, 4);
  M5.Lcd.drawString(" TX : G"+String(TX_PIN)+" ",14, 110, 4);
  M5.Lcd.drawString(" BAUD RATE : "+String(BAUD)+" ",14, 160,4);
  
}

void Change_UART_status(){
  Serial.write("Reseting UART");
  Serial2.flush();
  Serial2.end();  
  display_init();
  Serial.print(String(BAUD)+String(SERIAL_8N1)+String(RX_PIN)+String(TX_PIN));
  Serial2.begin(BAUD, SERIAL_8N1, RX_PIN, TX_PIN); 
  Serial.write("UART already reseted");
}


void setup() {
  M5.begin();
  M5.Lcd.setTextFont(2);
  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  // Host serial communication
  Serial.begin(115200);   

  // SIM800L serial communication
  Serial2.begin(BAUD, SERIAL_8N1, RX_PIN, TX_PIN);   
  pinMode(RESET_PIN, OUTPUT);
  display_init();
}

void loop() {
  
  //AT instruction write
  if(Serial.available()){
    M5.Lcd.fillTriangle(280, 100, 230, 120, 230, 80, GREEN);
    Serial2.write(Serial.read());
  }else{
    M5.Lcd.fillTriangle(280, 100, 230, 120, 230, 80, BLACK);
    M5.Lcd.drawTriangle(280, 100, 230, 120, 230, 80, GREEN);
  }
  //AT instruction result
  if(Serial2.available()){
    M5.Lcd.fillTriangle(160, 100, 210, 120, 210, 80, GREEN);
    Serial.write(Serial2.read());
  }else{
    M5.Lcd.fillTriangle(160, 100, 210, 120, 210, 80, BLACK);
    M5.Lcd.drawTriangle(160, 100, 210, 120, 210, 80, GREEN);
  }
  
  if(M5.BtnA.wasPressed()){
    if(UART_PIN_SELECT<2){
      UART_PIN_SELECT++;
    }else{
      UART_PIN_SELECT = 0;
    }
    RX_PIN = UART_PIN_LIST[UART_PIN_SELECT][0];
    TX_PIN = UART_PIN_LIST[UART_PIN_SELECT][1];
    Change_UART_status();
  }

  if(M5.BtnB.wasPressed()){
    if(UART_BAUD_SELECT<2){
      UART_BAUD_SELECT++;
    }else{
      UART_BAUD_SELECT = 0;
    }
    BAUD = UART_BAUD_LIST[UART_BAUD_SELECT];
    Change_UART_status();
  }
  M5.update();
}
