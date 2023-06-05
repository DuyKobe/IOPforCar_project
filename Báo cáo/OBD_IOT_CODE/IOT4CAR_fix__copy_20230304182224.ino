// ket noi board voi wifi
#include <SPI.h>
#include <WiFi101.h>
//Thư viện WiFi101 giúp việc sử dụng chip Wi-Fi onboard của board MKR1000 trở nên dễ dàng, và dễ kết nối board vào Internet.
// Credentials
char ssid[] = "tên WiFi ";     //  your network SSID (name)// ssid: tên WiFi của điểm truy cập mà chúng ta muốn kết nối đến, có thể có tối đa lên đến 32 ký tự.
char pass[] = "password";  // your network password, nhập pass mạng truy cập
char server[] = "dweet.io";  // freeboard and dweet Settings
unsigned long lastConnectionTime = 0; // track the last connection time, theo dõi thời gian cuối
const unsigned long postingInterval = 10L * 1000L; // post data every 10 seconds, up data mỗi 10 s
WiFiClient client; //Initialize the wifi client
int status = WL_IDLE_STATUS;     // the Wifi radio's status //Giai đoạn WiFi đang trong quá trình thay đổi giữa các trạng thái
char rxData[40];
char rxIndex = 0;
int i=0,j=0;
char text[20];
// Khởi tạo các biến lưu trữ giá trị tín hiệu 
int vSpeed = 0;
int vRPM = 0;
int vEngine_Coolant_Temp = 0;
int vPedal_Position = 0;
float vOxygen_Sensor = 0;
int vIntake_Air_Temp = 0;
int vVoltage = 0;
int vThrottle_Position= 0;
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
       //Serial1.flush();
      Serial1.print("010C\r");
      //Serial1.flush();
      OBD_read();
      Serial.print("toc do dong co la(hex): ");
      xuly();
      Serial.println(rxData);
      Serial.print("toc do dong co la: ");
      vRPM =((strtol(&text[6], 0, 16) * 256) + strtol(&text[9], 0, 16)) / 4;
      Serial.println(" rpm");
      clearBuffer();
      delay(500);
    }
    int getSPEED(void)
    {
      Serial1.print("010D\r");
      //Serial1.flush();
      OBD_read();
      Serial.print("toc do xe la(hex): ");
      xuly();
      Serial.println(rxData);
      Serial.print("toc do xe la: ");
      vSpeed =strtol(&text[6], 0, 16);
      Serial.println(" Km/h");
      clearBuffer();
      delay(500);
    }
    void  getAccelerator_pedal_position_D()
    {
      Serial1.print("0149\r");
      //Serial1.flush();
      OBD_read();
      Serial.print("vi tri ban dap D(hex): ");
      xuly();
      Serial.println(rxData);
      Serial.print("vi tri ban dap D: ");
      vPedal_Position = (strtol(&text[6], 0, 16)*100)/255;
      Serial.println(" %");
      clearBuffer();
      delay(500);
    }  
    
      void getOxygen_Sensor_2(void)
    {
      Serial1.print("0115\r");
      //Serial1.flush();
      OBD_read();
      Serial.print("tin hieu cam bien oxy la(hex): ");
      xuly();
      Serial.println(rxData);
      Serial.print("tin hieu cam bien oxy la: ");
      vOxygen_Sensor = strtol(&text[6], 0, 16)/200;
      Serial.println(" V");
      clearBuffer();
      delay(500);
    }
    
    void getIntake_air_temperature(){
             Serial1.print("010F\r");
      Serial1.flush();
      OBD_read();
      Serial.print("nhiet do khi nap la(hex): ");
      xuly();
      Serial.println(rxData);
      Serial.print("nhiet do khi nap la: ");
      vIntake_Air_Temp = strtol(&text[6], 0, 16)-40;
      Serial.println(" do C");
      clearBuffer();
      delay(500);  
    }
    void getThrottle_position(){
      Serial1.print("0111\r");
      Serial1.flush();
      OBD_read();
      Serial.print("vi tri buom ga la(hex): ");
      xuly();
      Serial.println(rxData);
      Serial.print("vi tri buom ga la: ");
      vThrottle_Position = (strtol(&text[6], 0, 16)*100)/255;
      Serial.println(" %");
      clearBuffer();
      delay(500);  
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
       // Get the new character from the Serial port: thực hiện nhận kí tự từ cổng serial
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
  text[i] = NULL;
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
    
  void loop() {
  while ( status != WL_CONNECTED) {
    // Connect to WPA/WPA2 Wi-Fi network
    Serial.println("Connecting to Wifi");
   /* lcd.println("Connect WiFi...");*/
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection
    delay(5000);
  }

  getRPM();
  getSPEED();
  getVOLT();
  getIntake_air_temperature();
  getThrottle_position();
  getOxygen_Sensor_2();
  getAccelerator_pedal_position_D();
delay(500);
Serial.flush();
    
  if (millis() - lastConnectionTime > postingInterval) {
      httpRequest(vSpeed, vRPM, vEngine_Coolant_Temp, vPedal_Position, vOxygen_Sensor, vIntake_Air_Temp, vVoltage ,vThrottle_Position);// gửi yêu cầu 
      lastConnectionTime = millis();
   }
    // Kiểm tra kết nối network mỗi 5s
    
  printCurrentNet();//Hàm kiểm tra kiểm tra kết nối network
  delay(5000);
}
void httpRequest(int vSpeed, int vRPM, int vEngine_Coolant_Temp, int vPedal_Position,  float vOxygen_Sensor, int vIntake_Air_Temp, int vVoltage, int vThrottle_Position ) {
  client.stop(); // khôi phục client sau khi được gọi 
  // create data string to send to freeboard. tạo chuổi data gửi 
  if (client.connect(server, 80)){ // clien.connect: điều kiện kiểm tra kết nối địa chỉ khách , 80 la ổ chắm máy chủ 
    Serial.println("Connected");
    Serial.println(vRPM);
    Serial.println(vSpeed);
    Serial.println(vPedal_Position);
    Serial.println(vOxygen_Sensor);
    Serial.println(vIntake_Air_Temp);
    Serial.println(vVoltage); 
    Serial.println(vThrottle_Position);      
    String data = "GET /dweet/for/arduinoMRK1000"; 
    data.concat("&RPM=");
    data.concat(vRPM); // upload engine RPM
    data.concat("&Speed=");
    data.concat(vSpeed);  // upload car speed
    data.concat("&Engine_Coolant_Temp=");
    data.concat(vEngine_Coolant_Temp);  // upload intake air temperature
    data.concat("&Pedal_Position=");
    data.concat(vPedal_Position);  // upload pedal position
    data.concat("&Oxygen_Sensor=");
    data.concat(vOxygen_Sensor);  // upload Oxygen Sensor
    data.concat("&Voltage=");
    data.concat(vVoltage);  // upload battery voltage
    data.concat("&Intake_Air_Temp=");
    data.concat(vIntake_Air_Temp);  // upload intake air temperature
    data.concat("&Throttle_Position=");
    data.concat(vThrottle_Position);  // upload throttle position
    client.println(data); //in ra thông số cho máy khách 
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