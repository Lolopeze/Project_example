#include "display_ch.h"
#include "str.h"

DisplayCh displaych;

void Display_init(){

    displaych.fillScreen(BLACK);
    displaych.loadHzk16();
    displaych.setTextColor(WHITE, BLACK);
    displaych.setTextSize(2);
    displaych.highlight(false);
    displaych.setCursor(50,100);
    displaych.writeHzk(GbkStr5);

    
    M5.Lcd.fillRect(0, 0, 122, 10, BLUE); 
    M5.Lcd.fillRect(0, 0, 10, 50, BLUE);  
    M5.Lcd.fillRect(0, 225, 122, 10, BLUE); 
    M5.Lcd.fillRect(0, 185, 10, 50, BLUE); 
    M5.Lcd.fillRect(198, 0, 122, 10, BLUE); 
    M5.Lcd.fillRect(310, 0, 10, 50, BLUE); 
    M5.Lcd.fillRect(198, 225, 122, 10, BLUE); 
    M5.Lcd.fillRect(310, 185, 10, 50, BLUE); 

}



void Display_change(char*test){

    displaych.fillScreen(BLACK);
    displaych.loadHzk16();
    displaych.setTextColor(WHITE, BLACK);
    displaych.setTextSize(2);
    displaych.highlight(false);
    displaych.setCursor(60,100);
    displaych.writeHzk(test);

    
    M5.Lcd.fillRect(0, 0, 122, 10, GREEN); 
    M5.Lcd.fillRect(0, 0, 10, 50, GREEN);  
    M5.Lcd.fillRect(0, 225, 122, 10, GREEN); 
    M5.Lcd.fillRect(0, 185, 10, 50, GREEN); 
    M5.Lcd.fillRect(198, 0, 122, 10, GREEN); 
    M5.Lcd.fillRect(310, 0, 10, 50, GREEN); 
    M5.Lcd.fillRect(198, 225, 122, 10, GREEN); 
    M5.Lcd.fillRect(310, 185, 10, 50, GREEN); 

}
