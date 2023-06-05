char rxData[4];
char c;
int z = 0;
void setup() {
Serial.begin(9600);
}

void loop() {
  if(Serial.available()>0){
    Serial.readBytes(rxData,4);
    rxData[4] = '\0';
  if(strcmp(rxData,"010C")==0){
    switch(random(1,5))
    {
      case 1:
        Serial.println("41 OC 0D 50 41 OC 0D 50 >010C");
        clearbuffer();
        break;
      case 2:
        Serial.println("41 OC 0D 58 41 OC 0D 58 >010C");
        clearbuffer();
        break;
      case 3:
        Serial.println("41 OC 0D 3E 41 OC 0D 3E >010C");
        clearbuffer();
        break;
      case 4:
        Serial.println("41 OC 0D 4E 41 OC 0D 4E >010C");
        clearbuffer();
        break;
      case 5:
        Serial.println("41 OC 0D 54 41 OC 0D 54 >010C");
        clearbuffer();
        break;
    }
  }
    if(strcmp(rxData,"010D")==0){  // toc do xe 010D
    switch(random(1,2))
    {
      case 1:
        Serial.println(">010D41 0D 00 41 0D 00");
        clearbuffer();
        break;
      case 2:
        Serial.println(">010D41 0D 00 41 0D 00");
        clearbuffer();
        break;
    }
  }
    if(strcmp(rxData,"0142")==0){  // volt 0142
    switch(random(1,6))
    {
      case 1:
        Serial.println(">014241 42 38 93 41 42 38 93");
        clearbuffer();
        break;
      case 2:
        Serial.println(">014241 42 38 F1 41 42 38 F1");
        clearbuffer();
        break;
      case 3:
        Serial.println(">014241 42 38 64 41 42 38 64");
        clearbuffer();
        break;
      case 4:
        Serial.println(">014241 42 38 C2 41 42 38 C2");
        clearbuffer();
        break;
      case 5:
        Serial.println(">014241 42 39 09 41 42 39 09");
        clearbuffer();
        break;
      case 6:
        Serial.println(">014241 42 38 D9 41 42 38 D9");
        clearbuffer();
        break;
    }
  }
    if(strcmp(rxData,"010F")==0){  // nhiet do khi nap
    switch(random(1,6))
    {
      case 1:
        Serial.println("41 0F 48 41 0F 48 >010F");
        clearbuffer();
        break;
      case 2:
        Serial.println("41 0F 48 41 0F 48 >010F");
        clearbuffer();
        break;
      case 3:
        Serial.println("41 0F 48 41 0F 48 >010F");
        clearbuffer();
        break;
      case 4:
        Serial.println("41 0F 48 41 0F 48 >010F");
        clearbuffer();
        break;
      case 5:
        Serial.println("41 0F 48 41 0F 48 >010F");
        clearbuffer();
        break;
      case 6:
        Serial.println("41 0F 48 41 0F 48 >010F");
        clearbuffer();
        break;
    }
  }
    if(strcmp(rxData,"0111")==0){  // nhiet do khi nap
    switch(random(1,6))
    {
      case 1:
        Serial.println("41 11 22 41 11 22 >0111");
        clearbuffer();
        break;
      case 2:
        Serial.println("41 11 22 41 11 22 >0111");
        clearbuffer();
        break;
      case 3:
        Serial.println("41 11 22 41 11 22 >0111");
        clearbuffer();
        break;
      case 4:
        Serial.println("41 11 22 41 11 22 >0111");
        clearbuffer();
        break;
      case 5:
        Serial.println("41 11 22 41 11 22 >0111");
        clearbuffer();
        break;
      case 6:
        Serial.println("41 11 22 41 11 22 >0111");
        clearbuffer();
        break;
    }
  }
    if(strcmp(rxData,"0115")==0){  // nhiet do khi nap
    switch(random(1,6))
    {
      case 1:
        Serial.println("41 15 83 FF 41 15 81 FF >0115");
        clearbuffer();
        break;
      case 2:
        Serial.println("41 15 83 FF 41 15 82 FF >0115");
        clearbuffer();
        break;
      case 3:
        Serial.println("41 15 83 FF 41 15 83 FF >0115");
        clearbuffer();
        break;
      case 4:
        Serial.println("41 15 83 FF 41 15 84 FF >0115");
        clearbuffer();
        break;
      case 5:
        Serial.println("41 15 83 FF 41 15 85 FF >0115");
        clearbuffer();
        break;
      case 6:
        Serial.println("41 15 83 FF 41 15 87 FF >0115");
        clearbuffer();
        break;
    }
  }
    if(strcmp(rxData,"010F")==0){  // nhiet do khi nap
    switch(random(1,6))
    {
      case 1:
        Serial.println("41 0F 51 41 0F 51 >010F");
        clearbuffer();
        break;
      case 2:
        Serial.println("41 0F 51 41 0F 51 >010F");
        clearbuffer();
        break;
      case 3:
        Serial.println("41 0F 51 41 0F 51 >010F");
        clearbuffer();
        break;
      case 4:
        Serial.println("41 0F 51 41 0F 51 >010F");
        clearbuffer();
        break;
      case 5:
        Serial.println("41 0F 51 41 0F 51 >010F");
        clearbuffer();
        break;
      case 6:
        Serial.println("41 0F 51 41 0F 51 >010F");
        clearbuffer();
        break;
    }
  }
    if(strcmp(rxData,"0149")==0){  // nhiet do khi nap
    switch(random(1,6))
    {
      case 1:
        Serial.println("41 49 25 41 49 25 >0149");
        clearbuffer();
        break;
      case 2:
        Serial.println("41 49 25 41 49 25 >0149");
        clearbuffer();
        break;
      case 3:
        Serial.println("41 49 25 41 49 25 >0149");
        clearbuffer();
        break;
      case 4:
        Serial.println("41 49 25 41 49 25 >0149");
        clearbuffer();
        break;
      case 5:
        Serial.println("41 49 25 41 49 25 >0149");
        clearbuffer();
        break;
      case 6:
        Serial.println("41 49 25 41 49 25 >0149");
        clearbuffer();
        break;
    }
  }
    if(strcmp(rxData,"014A")==0){  // nhiet do khi nap
    switch(random(1,6))
    {
      case 1:
        Serial.println("41 4A 13 41 4A 13 >014A");
        clearbuffer();
        break;
      case 2:
        Serial.println("41 4A 13 41 4A 13 >014A");
        clearbuffer();
        break;
      case 3:
        Serial.println("41 4A 13 41 4A 13 >014A");
        clearbuffer();
        break;
      case 4:
        Serial.println("41 4A 13 41 4A 13 >014A");
        clearbuffer();
        break;
      case 5:
        Serial.println("41 4A 13 41 4A 13 >014A");
        clearbuffer();
        break;
      case 6:
        Serial.println("41 4A 13 41 4A 13 >014A");
        clearbuffer();
        break;
    }
  }
    if(strcmp(rxData,"0105")==0){
    switch(random(1,5))
    {
      case 1:
        Serial.println("41 05 81 41 05 81 >0105");
        clearbuffer();
        break;
      case 2:
        Serial.println("41 05 80 41 05 80 >0105");
        clearbuffer();
        break;
      case 3:
        Serial.println("41 05 81 41 05 81 >0105");
        clearbuffer();
        break;
      case 4:
        Serial.println("41 05 81 41 05 81 >0105");
        clearbuffer();
        break;
      case 5:
        Serial.println("41 05 81 41 05 81 >0105");
        clearbuffer();
        break;
    }
  }
    if(strcmp(rxData,"0147")==0){  // nhiet do khi nap
    switch(random(1,6))
    {
      case 1:
        Serial.println("41 47 21 41 47 21 >0147");
        clearbuffer();
        break;
      case 2:
        Serial.println("41 47 21 41 47 21 >0147");
        clearbuffer();
        break;
      case 3:
        Serial.println("41 47 21 41 47 21 >0147");
        clearbuffer();
        break;
      case 4:
        Serial.println("41 47 21 41 47 21 >0147");
        clearbuffer();
        break;
      case 5:
        Serial.println("41 47 21 41 47 21 >0147");
        clearbuffer();
        break;
      case 6:
        Serial.println("41 47 21 41 47 21 >0147");
        clearbuffer();
        break;
    }
  }
    }
    
  






  
//  if(Serial.available()>0){
//  
//  while(Serial.available()>0){
//    c = Serial.read();
//    rxData[z++] = c;
//    rxData[z] = '\0';
//  
//  }
//  Serial.println(rxData[2]);
//  z = 0;
//  //Serial.println(strcmp(rxData,"010C"));
//  if(strcmp(rxData,"010C")==0){
//    Serial.println("khai");
//    switch(random(1,5))
//    {
//      case 1:
//        Serial.println(">41 OC 0D 50 41 OC 0D 50 010C");
//        clearbuffer();
//        break;
//      case 2:
//        Serial.println(">41 OC 0D 58 41 OC 0D 58 010C");
//        clearbuffer();
//        break;
//      case 3:
//        Serial.println(">41 OC 0D 3E 41 OC 0D 3E 010C");
//        clearbuffer();
//        break;
//      case 4:
//        Serial.println(">41 OC 0D 4E 41 OC 0D 4E 010C");
//        clearbuffer();
//        break;
//      case 5:
//        Serial.println(">41 OC 0D 54 41 OC 0D 54 010C");
//        clearbuffer();
//        break;
//    }
//  }  
////  else if(strcmp(rxData,"010D")==0){  // toc do xe 010D
////    switch(random(1,2))
////    {
////      case 1:
////        Serial.println(">41 0D 00 41 0D 00 010D");
////        clearbuffer();
////        break;
////      case 2:
////        Serial.println(">41 0D 00 41 0D 00 010D");
////        clearbuffer();
////        break;
////    }
////  }else if(strcmp(rxData,"0142")==0){  // volt 0142
////    switch(random(1,6))
////    {
////      case 1:
////        Serial.println(">41 42 35 36 41 42 35 36 0142");
////        clearbuffer();
////        break;
////      case 2:
////        Serial.println(">41 42 35 47 41 42 35 47 0142");
////        clearbuffer();
////        break;
////      case 3:
////        Serial.println(">41 42 35 02 41 42 35 02 0142");
////        clearbuffer();
////        break;
////      case 4:
////        Serial.println(">41 42 34 E2 41 42 34 E2 0142");
////        clearbuffer();
////        break;
////      case 5:
////        Serial.println(">41 42 35 28 41 42 35 28 0142");
////        clearbuffer();
////        break;
////      case 6:
////        Serial.println(">41 42 35 74 41 42 35 74 0142");
////        clearbuffer();
////        break;
////    }
////  }else if(strcmp(rxData,"0105")==0){
////     switch(random(1,6))
////    {
////      case 1:
////        Serial.println(">41 05 80 41 05 80 0105");
////        clearbuffer();
////        break;
////      case 2:
////        Serial.println(">41 05 80 41 05 80 0105");
////        clearbuffer();
////        break;
////      case 3:
////        Serial.println(">41 05 80 41 05 80 0105");
////        clearbuffer();
////        break;
////      case 4:
////        Serial.println(">41 05 80 41 05 80 0105");
////        clearbuffer();
////        break;
////      case 5:
////        Serial.println(">41 05 80 41 05 80 0105");
////        clearbuffer();
////        break;
////      case 6:
////        Serial.println(">41 05 80 41 05 80 0105");
////        clearbuffer();
////        break;
////    }
//  
//  }
//  

}
void clearbuffer(void){
  for(int i = 0;i<=3;i++){
    rxData[i] = NULL;
  }
}
