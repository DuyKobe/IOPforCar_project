// Libraries
/*OBDII-UART-Serial version 9
* This program will talk to vehicle using the OBDII-UART board, 
*and upload to freeboard IoT platform
* 
* 
* updates:
*   v3: modified the getResponse() function so that the buffer receives the correct response.
*       add the getRPM() to get the engine RPM from the vehicle.
*   v4: add the getSpeed() function to get the speed of the vehicle
*   v5: is the wifi version
*   v6: is the non-wifi, non-serial version. Remove serial initialization,
*       so that the board can work without a computer.
*   v7: is the non-wifi, non-serial version. Add fuel level and coolant temperature.
*       rearrange the display location.
*   v8: is the wifi, non-serial version. Upolad speed, RPM, fuel level and coolant temperture
* 
* 10 K potentialmeter:
* ends to +5V and ground

*/

////////////////////////////////////////////////////////
//
// WiFi related //
///////////////////////////////////////////////////////
// ket noi board voi wifi
#include <SPI.h>
#include <WiFi101.h>
//Thư viện WiFi101 giúp việc sử dụng chip Wi-Fi onboard của board MKR1000 trở nên dễ dàng, và dễ kết nối board vào Internet.
// Credentials
char ssid[] = "Phong103_2.4GHz";     //  your network SSID (name)// ssid: tên WiFi của điểm truy cập mà chúng ta muốn kết nối đến, có thể có tối đa lên đến 32 ký tự.
char pass[] = "khongthichcho";  // your network password, nhập pass mạng truy cập
char server[] = "https://dweet.io";  // freeboard and dweet Settings
int status = WL_IDLE_STATUS;     // the Wifi radio's status //Giai đoạn WiFi đang trong quá trình thay đổi giữa các trạng thái

void setup() {
  
  // Serial 
  Serial.begin(9600);

  // Kiểm tra trạng thái kết nối cho đến khi có báo cáo WL_CONNECTED
  while ( status != WL_CONNECTED) {
    // Không kết nối được mạng   
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    
    // Connect to WPA/WPA2 network:
//Chuyển đối sang chế độ station, ta dùng hàm begin. Các tham số cần thiết sẽ là SSID và password, để module có thể kết nối đến một Access Point (AP) cụ thể    
    status = WiFi.begin(ssid, pass);

    // Wait 10 seconds for connection:
    delay(10000);
  }

  // Khi đã kết nối, in ra dòng xác nhận
  // tương đương với điều kiện if (WiFi.status() == WL_CONNECTED)
  Serial.print("You're connected to the network");
  printCurrentNet();//Hàm kiểm tra kiểm tra kết nối network
  printWifiData();

}

void loop() {

  // Kiểm tra kết nối network mỗi 10s
  delay(10000);
  printCurrentNet();//Hàm kiểm tra kiểm tra kết nối network
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

