String comData = "";


void M5StickV_init(){
  Serial1.begin(115200, SERIAL_8N1, 16, 17);  
 }

void classprocess(String comData){
   if(comData == "1"){
        Display_change(GbkStr2);
        stepmotor_run(55,"right",20);
     }
   if(comData == "2"){
        Display_change(GbkStr1);
        stepmotor_run(110,"left",31);   
     }
   if(comData == "3"){
        Display_change(GbkStr3);
        stepmotor_run(175,"right",41); 
     }
   if(comData == "4"){
        Display_change(GbkStr4);
        stepmotor_run(230,"left",52); 
     }
}


void classification(){
  if(Serial1.available()){
    comData = "";
    while(Serial1.available()){
    char ch = Serial1.read();
      if(ch != '\r'){
        comData += ch;
      }else{
        break;
      }
    }
//    Serial1.end();
    Serial1.flush();
    Serial.println(comData);
    classprocess(comData);
  }

}
