// Libraries
OBDII-UART-Serial version 9
* This program will talk to vehicle using the OBDII-UART board, 
* and display the results on the LCD, and upload to freeboard IoT platform
* 
* Author: zhaoshentech
* Updated: 2018-08-27
* 
* updates:
*   v3: modified the getResponse() function so that the buffer receives the correct response.
*       add the getRPM() to get the engine RPM from the vehicle.
*   v4: add the getSpeed() function to get the speed of the vehicle
*   v5: add the LCD module and display the speed and RPM on the LCD
*   v6: is the wifi version
*   v7: is the non-wifi, non-serial version. Remove serial initialization,
*       so that the board can work without a computer.
*   v8: is the non-wifi, non-serial version. Add fuel level and coolant temperature.
*       rearrange the display location.
*   v9: is the wifi, non-serial version. Upolad speed, RPM, fuel level and coolant temperture
* 
* LCD circuit connection:
* LCD RS pin to digitial pin 12
* LCD Enable pin to digital pin 11
* LCD D4 pin to digital pin 5
* LCD D5 pin to digital pin 4
* LCD D6 pin to digital pin 3 
* LCD D7 pin to digital pin 2
* LCD R/W pin to ground
* 10 K potentialmeter:
* ends to +5V and ground
* wiper to LCD VO pin (pin 3)
*/

////////////////////////////////////////////////////////
//
// WiFi related //
///////////////////////////////////////////////////////
// ket noi board voi wifi
#include <SPI.h>
#include <WiFi101.h>

// Credentials
char ssid[] = "Bao Minh Coffee";     //  your network SSID (name)// wifi ID  tạo store network 
char pass[] = "baominhcoffee";  // your network password,tao pass store network 
char server[] = "https://dweet.io";  // freeboard and dweet Settings
int status = WL_IDLE_STATUS;     // the Wifi radio's status

void setup() {
  
  // Serial 
  Serial.begin(9600);

  // Attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // Wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  printCurrentNet();
  printWifiData();

}

void loop() {

  // Check the network connection once every 10 seconds:
  delay(10000);
  printCurrentNet();
}

void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
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

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
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
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}

