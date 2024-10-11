#include <SoftwareSerial.h> // ESP8266 헤더
#include "DHT.h"            // DHT22 헤더

#define DHTPIN A0            // DHT 데이터 핀
#define DHTTYPE DHT11       // DHT22 라이브러리
DHT dht(DHTPIN, DHTTYPE);

// ESP8266 설정
SoftwareSerial myDevice(2, 3); // RX, TX

// 서버 설정
String connWifiStr = "AT+CWJAP=\"DODO\",\"12345678\""; // SSID와 비밀번호 입력
const char* connStr = "AT+CIPSTART=\"TCP\",\"192.168.0.6\",5000"; // 모드 TCP, 서버 주소, 포트번호
const char* infoChar = "AT+CIPSEND=5"; // 보낼 데이터의 바이트 수 입력

void setup() {
  Serial.begin(9600);
  myDevice.begin(115200); // ESP8266 기본 통신 속도
  dht.begin();
  
  // 버퍼 비우기
  while (myDevice.available() > 0) {
    myDevice.read();
  }
  
  while (Serial.available() > 0) {
    Serial.read();
  }
}

void loop() {
  TryConnect();
  delay(10000); // 10초마다 루프 반복
}

void TryConnect() {
  Serial.println("Checking WiFi connection status...");
  
  // Wi-Fi 모드를 Station으로 설정
  myDevice.println("AT+CWMODE=1");
  delay(2000);

  myDevice.println("AT+CWJAP?");
  delay(5000);
  
  String res = "";
  
  // 응답 읽기
  while (myDevice.available()) {
    res += myDevice.readString();
  }
  
  Serial.println("WiFi Connection Status:");
  Serial.println(res);
  
  if (res.indexOf("No AP") != -1) {
    Serial.println("AP Connection Fail");
    myDevice.println(connWifiStr);
    delay(10000); // 10초 후 재시도
  } else if (res.indexOf("OK") != -1) {
    Serial.println("AP Connected");
    TryConnectTCP();
  } else {
    Serial.println("Command Fail");
  }
}

void TryConnectTCP() {
  Serial.println("Connecting TCP...");
  myDevice.println("AT+CIPSTART=\"TCP\",\"192.168.0.6\",5000");
  delay(5000);
  
  String res = "";
  
  // 응답 읽기
  while (myDevice.available()) {
    res += myDevice.readString();
  }
  
  Serial.println("TCP Connection Status:");
  Serial.println(res);
  
  if (res.indexOf("ALREADY CONNECTED") != -1 || res.indexOf("OK") != -1) {
    myDevice.println("AT+CIPSEND=10"); // 수정: 데이터 바이트 수를 실제 데이터 크기에 맞게 조정
    delay(5000);
  } else {
    Serial.println("AT+CIPSTART Error");
    myDevice.println("AT+CIPCLOSE");
    delay(10000); // 10초 후 재시도
    return;
  }
  
  // 보낼 데이터 모드 진입 확인
  String sendMode = "";
  while (myDevice.available()) {
    sendMode += myDevice.readString();
  }
  
  Serial.println("Send Mode Status:");
  Serial.println(sendMode);
  
  if (sendMode.indexOf(">") != -1) {
    float tempData = GetDHT22Temp(); // 온도 데이터 가져오기
    String tempStr = String(tempData);
    myDevice.println(tempStr); // 온도값 입력 후 엔터키
    delay(5000);
  } else {
    Serial.println("Failed to enter send mode");
  }
  
  // 전송 결과를 화면에 출력
  String sendResult = "";
  while (myDevice.available()) {
    sendResult += myDevice.readString();
  }
  Serial.println("Send Result:");
  Serial.println(sendResult);
  delay(5000);
}

float GetDHT22Temp() {
  return dht.readTemperature();
}
