// ket noi board voi wifi
#include <SPI.h>
#include <WiFi101.h>
//Thư viện WiFi101 giúp việc sử dụng chip Wi-Fi onboard của board MKR1000 trở nên dễ dàng, và dễ kết nối board vào Internet.
// Credentials
char ssid[] = "Happy Family";     //  your network SSID (name)// ssid: tên WiFi của điểm truy cập mà chúng ta muốn kết nối đến, có thể có tối đa lên đến 32 ký tự.
char pass[] = "02022001";  // your network password, nhập pass mạng truy cập
char server[] = "dweet.io";  // freeboard and dweet Settings
unsigned long lastConnectionTime = 0; // track the last connection time, theo dõi thời gian cuối
const unsigned long postingInterval = 10L * 1000L; // post data every 10 seconds, up data mỗi 10 s
WiFiClient client; //Initialize the wifi client
int status = WL_IDLE_STATUS;     // the Wifi radio's status //Giai đoạn WiFi đang trong quá trình thay đổi giữa các trạng thái
char rxData[40];
char rxIndex = 0;
int rpmstored = 0;
int i=0,j=0;
char text[20];
// Khởi tạo các biến lưu trữ giá trị tín hiệu 
int vSpeed = 0;
int vRPM = 0;
int vFuel = 0;
int vCool_Temp = 0;
int vOil_Temp = 0;
int vVoltage = 0;
void setup(){
      Serial.begin(9600); // prints to serial monitor
      Serial1.begin(9600); //Hardware serial connection to the obdii uart
      //Serial1.flush();
      //Reset the OBD-II-UART
      Serial1.print("ATZ\r");
      //Wait for a bit before starting to send commands after the reset.
      delay(2000);
      
      OBD_read();
      Serial.println(rxData);
      clearBuffer();
      
      
      delay(3000);
      // Kiểm tra trạng thái kết nối cho đến khi có báo cáo WL_CONNECTED
   // check the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi not ready");
    while(true);  
  }
  while ( status != WL_CONNECTED) {
    // Không kết nối được mạng   
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    
    // Connect to WPA/WPA2 network:
//Chuyển đối sang chế độ station, ta dùng hàm begin. Các tham số cần thiết sẽ là SSID và password, để module có thể kết nối đến một Access Point (AP) cụ thể    
    status = WiFi.begin(ssid, pass);

    // Wait 10 seconds for connection:
    delay(5000);
  }

  // Khi đã kết nối, in ra dòng xác nhận
  // tương đương với điều kiện if (WiFi.status() == WL_CONNECTED)
  Serial.print("You're connected to the network");
  printCurrentNet();//Hàm kiểm tra kiểm tra kết nối network
  printWifiData();
  Serial1.begin(11520);

}


void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);

  // In ra địa chỉ Mac của Arduino MKR1000 station
  // khởi tạo biến mac là một con trỏ đến vị trí bộ nhớ (một mảng uint8_t có 6 phần tử) để lưu địa chỉ mac.
  byte mac[6];
  WiFi.macAddress(mac);// Lấy địa chỉ mac
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);

}
// hàm này in ra dữ liệu về mạng Wi-Fi mà board Arduino đang kết nối tới:
void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());//Trả lại tên của mạng Wi-Fi đã kết nối.

  // print the MAC address of the router you're attached to:
  // Xuát địa chỉ MAC router mà arduino kết nối đến
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");// Trả về địa chỉ MAC router mà arduino kết nối đến
  Serial.print(bssid[5], HEX);
  Serial.print(":");
  Serial.print(bssid[4], HEX);
  Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.println(bssid[0], HEX);

  // print the received signal strength:
 // Xuất ra  cường độ tín hiệu của mạng Wi-Fi
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");// Trả về cường độ tín hiệu của mạng Wi-Fi
  Serial.println(rssi);

  // print the encryption type:
  //Xuất kiểu báo mật wifi sử dụng
  byte encryption = WiFi.encryptionType();//Hàm Wifi.encryptionType trả về kiểu bảo mật mà mạng Wifi sử dụng
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}
   
  
    
    
    void getRPM(void)
    {
      //Query the OBD-II-UART for the Vehicle rpm
      Serial1.flush();
      Serial1.print("010C\r");
      clearBuffer();
      Serial1.flush();
      OBD_read();
      //Serial.println("-");
      Serial.print("toc do dong co la(hex): ");
      xuly();
      Serial.println(text);
      Serial.print("toc do dong co la: ");
      vRPM = ((strtol(&text[6], 0, 16) * 256) + strtol(&text[9], 0, 16)) / 4;
    Serial.println(vRPM) ;     
      //Serial.println(((strtol(&text[6], 0, 16) * 256) + strtol(&text[9], 0, 16)) / 4);
      clearBuffer();
      delay(500);
    }

    int getSPEED(void)
    {

      Serial1.flush();
      Serial1.print("010D\r");
      clearBuffer();
      Serial1.flush();
      OBD_read();
      //Serial.println("-");
      Serial.print("toc do xe la(hex): ");
      xuly();
      Serial.println(text);
      Serial.print("toc do xe la: ");
      vSpeed = strtol(&text[6], 0, 16);
      Serial.println(vSpeed);
      //Serial.println(strtol(&text[6], 0, 16));
      clearBuffer();
      delay(500);
      //Query the OBD-II-UART for the vehicle speed
      
    }

    int getOILTEMP(void)
    {
      Serial1.flush();
      Serial1.print("015C\r");
      clearBuffer();
      Serial1.flush();
      OBD_read();
      //Serial.println("-");
      Serial.print("nhiet do dau la(hex): ");
      xuly();
      Serial.println(text);
      Serial.print("nhiet do dau la: ");
      vOil_Temp = strtol(&text[6], 0, 16);
      Serial.println(vOil_Temp);
     // Serial.println(strtol(&text[6], 0, 16));
      clearBuffer();
      delay(500);
      //Query the OBD-II-UART for the vehicle speed
     
      
    }

    int getFUEL(void)
    {
      Serial1.flush();
      Serial1.print("012F\r");
      clearBuffer();
      Serial1.flush();
      OBD_read();
      //Serial.println("-");
      Serial.print("luong nhien lieu la(hex): ");
      xuly();
      Serial.println(text);
      Serial.print("luong nhien lieu la: ");
      vFuel = strtol(&text[6], 0, 16);
      Serial.println( vFuel);
      //Serial.println(strtol(&text[6], 0, 16));
      clearBuffer();
      delay(500);
      //Query the OBD-II-UART for the vehicle speed
      
    }

    int getVOLT(void)
    {
      Serial1.flush();
      Serial1.print("0142\r");
      clearBuffer();
      Serial1.flush();
      OBD_read();
      //Serial.println("-");
      Serial.print("VON(hex): ");
      xuly();
      Serial.println(text);
      Serial.print("VON: ");
      vVoltage = (strtol(&text[6], 0, 16)*256+strtol(&text[9], 0, 16))/1000;
      Serial.println(vVoltage);      
      //Serial.println((strtol(&text[6], 0, 16)*256+strtol(&text[9], 0, 16))/1000);
      clearBuffer();
      delay(500);
      //Query the OBD-II-UART for the vehicle speed
      
    }

    int getWATERTEMP(void)
    {
      Serial1.flush();
      Serial1.print("0105\r");
      clearBuffer();
      Serial1.flush();
      OBD_read();
      //Serial.println("-");
      Serial.print("nhiet do nuoc(hex): ");
      xuly();
      Serial.println(text);
      Serial.print("nhiet do nuoc: ");
      vCool_Temp = strtol(&text[6], 0, 16) - 40;
      Serial.println (vCool_Temp);  
      //Serial.println(strtol(&text[6], 0, 16) - 40);
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
      char c;
      while (c != '>'){
        if (Serial1.available() > 0)
        {
          c = Serial1.read();
          if ((c != '>') && (c != '\r') && (c != '\n')) //Keep these out of our buffer
          {
            rxData[rxIndex++] = c; //Add whatever we receive to the buffer
          }
        }
      }  //The ELM327 ends its response with this char so when we get it we exit out.
      rxData[rxIndex++] = '\0';//Converts the array into a string
      rxIndex = 0; //Set this to 0 so next time we call the read we get a "clean buffer"
    
    }
void clearBuffer(){
  
  int i;
  for(int i = 0; i < 40; i++){
  rxData[i] = '';
  }
  }
void xuly(void){
  for(int i = 0; i < 20; i++){
  text[i] = '';
  }
  int len = strlen(rxData);
  i=(len/2+2);
  for(int i;i<len;i++){
    text[j] = rxData[i];
    j++;
    }
    text[j++] = '\0';
    j=0;
  
  }
  void loop() {
  while ( status != WL_CONNECTED) {
    /*lcd.clear();
    lcd.setCursor(0,0);*/
    // Connect to WPA/WPA2 Wi-Fi network
    Serial.println("Connecting to Wifi");
   /* lcd.println("Connect WiFi...");*/
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection
    delay(5000);
  }
  /*
  getSpeed();
  getRPM();
  getFuel();
  getCoolTemp();*/
  getRPM();
  getSPEED();
  getOILTEMP();
  getFUEL();
  getVOLT();
  getWATERTEMP();
//Serial1.flush();
//      Serial1.print("015C\r");
//      OBD_read();
      //Serial.print("nhiet do dau la: ");
//      Serial.println(rxData);
//Serial.print (",");
//Serial.print("W:");
//Serial.print (getWATERTEMP());
//Serial.print (",");
//Serial.print("O:");
//Serial.print (getOILTEMP());
//Serial.print (",");
//Serial.print("F:");
//Serial.print (getFUEL());
//Serial.print (",");
//Serial.print("V:");
//Serial.println (getVOLT());
delay(500);
Serial.flush();
    
  
  if (millis() - lastConnectionTime > postingInterval) {
      httpRequest(vSpeed, vRPM,  vFuel, vCool_Temp, vOil_Temp, vVoltage);// gửi yêu cầu 
      lastConnectionTime = millis();
   }
    // Kiểm tra kết nối network mỗi 5s
  
  printCurrentNet();//Hàm kiểm tra kiểm tra kết nối network
  delay(5000);
}
void httpRequest(int vSpeed, int vRPM, int vFuel,  int vCool_Temp, int vOil_Temp, int vVoltage ) {
  client.stop(); // đóng kế nối 
  // create data string to send to freeboard. tạo chuổi data gửi 
  if (client.connect(server, 80)){ // clien.connect: điều kiện kiểm tra kết nối địa chỉ khách , 80 la ổ chắm máy chủ 
    Serial.println("Connected");
    Serial.println(vRPM);
    Serial.println(vSpeed);
    Serial.println(vFuel);
    Serial.println(vCool_Temp);
     Serial.println(vOil_Temp);
        Serial.println(vVoltage);     
    
    
   String data = "GET /dweet/for/arduino?RPM="; 
   data.concat("&RPM=");
    data.concat(vRPM); // upload engine RPM
    data.concat("&Speed=");
   data.concat(vSpeed);  // upload car speed
    data.concat("&Fuel=");
    data.concat(vFuel);  // upload fuel level
    data.concat("&Cool_Temp=");
    data.concat(vCool_Temp);  // upload coolant temperature
    data.concat("&Voltage=");
    data.concat(vVoltage);  // upload coolant temperature
    data.concat("&Oil_Temp=");
    data.concat(vOil_Temp);  // upload coolant temperature
    
    
    
    
    client.println(data); //in ra thông số cho máy khách 
    
    
  
//client.println("GET/dweet/for/arduino?RPM=" + String(vSpeed) + " HTTP/1.1");//
     // Send the HTTP PUT request:
//client.println("GET /dweet/for/arduino?RPM=" +String(vSpeed) + String(vRPM)+ String(vFuel)+ String(vTemp)+ " HTTP/1.1");
client.println("Host: dweet.io");
client.println("User-Agent: ArduinoWiFi/1.1");
client.println("Connection: close");
client.println();
// Note the time that the connection was made:
lastConnectionTime = millis();
}
else {
// if you couldn't make a connection:
Serial.println("connection failed");
}
}