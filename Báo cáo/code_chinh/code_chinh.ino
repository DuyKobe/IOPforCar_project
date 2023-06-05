char rxData[40];
char rxIndex = 0;
int rpmstored = 0;
int i=0,j=0,x=1;
char text[20];
int RPM;
int k= 1;
char RPM_hex[20];
    void setup()
    {
      Serial.begin(9600); // prints to serial monitor
      Serial1.begin(9600); //Hardware serial connection to the obdii uart
//      //Serial1.flush();
//      //Reset the OBD-II-UART
//      Serial1.print("ATZ\r");
//      //Wait for a bit before starting to send commands after the reset.
//      delay(2000);
//      
//      OBD_read();
//      Serial.println(rxData);
//      clearBuffer();
//      
//      
//      delay(1000);
    }
    
    void loop()
{    
//        Serial1.print("010C\r");
//        Serial.println("dong co"); 
//        if(Serial1.available()<=0){
//          
//        }
//        OBD_read();
//      
//        Serial.println(rxData);
//       delay(2000);
//        Serial1.print("010D\r");
//       Serial.println("xe"); 
//        if(Serial1.available()<=0){
//          
//         }
//        OBD_read();
//       
//    Serial.println(rxData);
//    delay(2000);





    //getRPM(); //1
    //getSPEED(); //1 
    //Intake_air_temperature(); //1
    //Throttle_position(); //1
    // getVOLT(); //1
    //Oxygen_Sensor_2(); //1
   //Accelerator_pedal_position_D(); //1
  //Accelerator_pedal_position_E(); //1




  
   // getWATERTEMP();   // ko dung dduoc tren KIA'Quang

  //getFUEL();  // ko dc
  //getOILTEMP(); 
 
 
 
 

delay(500);
//Serial.flush();
    }
    
    
    void getRPM(void)
    {
      Serial1.print("010C\r");
      //Serial1.flush();
      OBD_read();
      Serial.print("toc do dong co la(hex): ");
      xuly();
      Serial.println(rxData);
      Serial.print("toc do dong co la: ");
      Serial.print(((strtol(&text[6], 0, 16) * 256) + strtol(&text[9], 0, 16)) / 4);
      Serial.println(" rpm");
      clearBuffer();
      delay(500);

    }

    void getSPEED(void)
    {
      Serial1.print("010D\r");
      //Serial1.flush();
      OBD_read();
      Serial.print("toc do xe la(hex): ");
      xuly();
      Serial.println(rxData);
      Serial.print("toc do xe la: ");
      Serial.print(strtol(&text[6], 0, 16));
      Serial.println(" Km/h");
      clearBuffer();
      delay(500);
    }
    void  Accelerator_pedal_position_D()
    {
      Serial1.print("0149\r");
      //Serial1.flush();
      OBD_read();
      Serial.print("vi tri ban dap D(hex): ");
      xuly();
      Serial.println(rxData);
      Serial.print("vi tri ban dap D: ");
      Serial.print((strtol(&text[6], 0, 16)*100)/255);
      Serial.println(" %");
      clearBuffer();
      delay(500);
    }  
    void  Accelerator_pedal_position_E()
    {
      Serial1.print("014A\r");
      //Serial1.flush();
      OBD_read();
      Serial.print("vi tri ban dap E(hex): ");
      xuly();
      Serial.println(rxData);
      Serial.print("vi tri ban dap E: ");
      Serial.print((strtol(&text[6], 0, 16)*100)/255);
      Serial.println(" %");
      clearBuffer();
      delay(500);
    }  
      void Oxygen_Sensor_2(void)
    {
      Serial1.print("0115\r");
      //Serial1.flush();
      OBD_read();
      Serial.print("tin hieu cam bien oxy la(hex): ");
      xuly();
      Serial.println(rxData);
      Serial.print("tin hieu cam bien oxy la: ");
      Serial.print((float)strtol(&text[6], 0, 16)/200);
      Serial.println(" V");
      clearBuffer();
      delay(500);
    }
    void getOILTEMP(void)
    {
      Serial1.print("015C\r");
      Serial1.flush();
      OBD_read();
      Serial.print("nhiet do dau la(hex): ");
      xuly();
      Serial.println(rxData);
      Serial.print("nhiet do dau la: ");
      Serial.println(strtol(&text[6], 0, 16));
      clearBuffer();
      delay(500);      
    }
    void Intake_air_temperature(){
             Serial1.print("010F\r");
      Serial1.flush();
      OBD_read();
      Serial.print("nhiet do khi nap la(hex): ");
      xuly();
      Serial.println(rxData);
      Serial.print("nhiet do khi nap la: ");
      Serial.print(strtol(&text[6], 0, 16)-40);
      Serial.println(" do C");
      clearBuffer();
      delay(500);  
    }
    void Throttle_position(){
      Serial1.print("0111\r");
      Serial1.flush();
      OBD_read();
      Serial.print("vi tri buom ga la(hex): ");
      xuly();
      Serial.println(rxData);
      Serial.print("vi tri buom ga la: ");
      Serial.print((strtol(&text[6], 0, 16)*100)/255);
      Serial.println(" %");
      clearBuffer();
      delay(500);  
    }
        
    void getFUEL(void)
    {
      Serial1.print("012F\r");
      Serial1.flush();
      OBD_read();
      Serial.print("luong nhien lieu la(hex): ");
      xuly();
      Serial.println(rxData);
      Serial.print("luong nhien lieu la: ");
      Serial.println(strtol(&text[6], 0, 16));
      clearBuffer();
      delay(500);    
    }

    void getVOLT(void)
    {
      Serial1.print("0142\r");
      //Serial1.flush();
      OBD_read();
      Serial.print("VON(hex): ");
      xuly();
      Serial.println(rxData);
      Serial.print("VON: ");
      Serial.print((strtol(&text[6], 0, 16)*256+strtol(&text[9], 0, 16))/1000);
      Serial.println(" V");
      clearBuffer();
      delay(500);
    }

    void getWATERTEMP(void)
    {
      Serial1.print("0105\r");
      //Serial1.flush();
      OBD_read();
      Serial.print("nhiet do nuoc(hex): ");
      xuly();
      Serial.println(rxData);
      Serial.print("nhiet do nuoc: ");
      Serial.println(strtol(&text[6], 0, 16) - 40);
      clearBuffer();
      delay(500);
      //Query the OBD-II-UART for the Engine Coolant Temp
      Serial1.flush();
      Serial1.print("0105\r");
      OBD_read();

      return strtol(&rxData[6], 0, 16) - 40;
    }
    
    
    void OBD_read(void)
    {
      char inChar;
       while(Serial1.available() > 0) {
     // Start by checking if we've received the end of message character ('\r').
     if(Serial1.peek() == '\r'){
       // reach the end of the message, clear the Serial buffer
       inChar = Serial1.read();
       rxData[rxIndex] = '\0';
       // Reset the buffer index so that the next character goes back at the beginning of the string
       rxIndex = 0;  
     }
     // If we didnt get the end of the message character, just add the new character to the string
     else{
       // Get the new character from the Serial port:
       inChar = Serial1.read();
       if(inChar != '\n'){
       // add the new character to the string, and increase the index variable:
       rxData[rxIndex++] = inChar;
       }
     }  
 }
      
    }
void clearBuffer(){
  
  int i;
  for(i = 0; i < 40; i++){
  rxData[i] = NULL;
  }
  for(i = 0; i < 20; i++){
  text[i] = "";
  }
  }
void xuly(void){

  int len = strlen(rxData);

  if(rxData[0] == '>'){
    for(i=4;i<(len/2+2);i++){
      text[j] = rxData[i];
      j++;
    }
    text[j++] = '\0';
    j=0;    
  }else{
    for(i=0;i<(len/2-2);i++){
      text[j] = rxData[i];
      j++;
    }
    text[j++] = '\0';
    j=0;
    }    
  }
  
//  for(i=0;i<(len/2-2);i++){
//    text[j] = rxData[i];
//    j++;
//    }
//    text[j++] = '\0';
//    j=0;
//  
  //}
  
