#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>  // REQUIRED for notifications
#include "esp_pm.h"
#include <WiFi.h>

BLEServer *pServer;//pointer to the object that represents esp32 (or the server)
BLECharacteristic *pTxCharacteristic;//used for sending data from the server
BLECharacteristic *pRxCharacteristic;//used for receiving data from the client(phone)
bool iScreech = false;//
#define SERVICE_UUID        "0000abcd-0000-1000-8000-00805f9b34fb" //unique ID used for connecting the phone to the esp32 trough bluetooth
#define CHARACTERISTIC_UUID_TX "0000deaf-0000-1000-8000-00805f9b34fb"//ID for TX,from which the data is transmitted from the esp32 to the phone
#define CHARACTERISTIC_UUID_RX "0000beef-0000-1000-8000-00805f9b34fb"//ID for RX,to which the data is transmitted from the phone to the esp32
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
const char* ssid = "qrp";
const char* password = "procoder31";
float distMedium = 0;
class MyCallbacks: public BLECharacteristicCallbacks {//inherits class and overrides onWrite functions
    void onWrite(BLECharacteristic *pCharacteristic) {//this function is called when the BLE stack task is triggered by oncoming data from the phone to the esp32
      uint8_t* data = pCharacteristic->getData();
      size_t length = pCharacteristic->getLength();
      
      if (length > 0) {//prints in serial monitor the payload from the phone
        Serial.print("Received: ");
        for (size_t i = 0; i < length; i++) {
          Serial.print((char)data[i]);
        }
        Serial.println();
      }
      if(length == 5)//toggles the buzzer,based on the 5-letter keyword "START" in the app
      {
        iScreech = !iScreech;
      }
    }
     
};
class MyReadingCallBack: public BLECharacteristicCallbacks{
  void onRead(BLECharacteristic* pCharacteristic){//sending the distance to the phone in the app
      String timeString =  String(distMedium, 2);//preparing the information,with 2 decimals
      pCharacteristic->setValue(timeString.c_str());//loading payload
  }//after the function is executed,the BLE stack sends the data 


};
int buzzerPin = 25;
void setup() {
  Serial.begin(115200);
  
  pinMode(buzzerPin, OUTPUT);
  Serial.println("Starting BLE...");

  // Initialize BLE
  BLEDevice::init("ESP32_BLE");//set the name for the esp32
  BLEDevice::setMTU(512);  // Increase MTU for better stability

  // Create Server
  pServer = BLEDevice::createServer();
  
  // Create Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create TX Characteristic (for sending data to phone)
  pTxCharacteristic = pService->createCharacteristic(//property read-constant nedded for comunication on the tx pipeline
    CHARACTERISTIC_UUID_TX,
    BLECharacteristic::PROPERTY_READ |           //property notify-constant nedded for sending the data from esp32 to the phone without permission
    BLECharacteristic::PROPERTY_NOTIFY
  );
  pTxCharacteristic->addDescriptor(new BLE2902());  // required for receiving notifications on the phone

  // Create RX Characteristic (for receiving data from phone)
  pRxCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID_RX,
    BLECharacteristic::PROPERTY_WRITE
  );
  pRxCharacteristic->setCallbacks(new MyCallbacks());//attach the callback when the phone writes data
  pTxCharacteristic->setCallbacks(new MyReadingCallBack());//attach callback when the phone reads data

  pService->start();//start Service

  WiFi.begin(ssid, password);//start wifi
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {//wait until the esp32 is connected to wifi
        delay(500);
        Serial.print(".");
    }

  // Start Advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();//init BLE comunication
  pAdvertising->addServiceUUID(SERVICE_UUID);//attach unique id
  pAdvertising->setScanResponse(true);//if true,the phone can ask fow more information
  pAdvertising->setMinPreferred(0x06);//comunication at a faster pace
  pAdvertising->setMaxPreferred(0x12);//
  BLEDevice::startAdvertising();//the esp32 can be connected to the phone via BLE

  Serial.println("BLE Ready!");
}


 float estimateDistance(int rssi, int txPower, float n) {//function used to convert RSSI in a distance
   // Log-distance path loss model
   return pow(10, (txPower - rssi) / (10 * n));
 }

float calculateMediumDistance(){

  int txPower = -47; //RSSI at 1 meter
  float n = 2.0; //Path-loss exponent (2.0 is typical for indoor)
  int rssiValue = WiFi.RSSI();//measure the strength of the signal
  float distance = estimateDistance(rssiValue, txPower, n);
  // now we make the medium value in 100 measurements
  for(int i = 0; i < 100; i++){//
    rssiValue = WiFi.RSSI();
    distance += estimateDistance(rssiValue, txPower, n);
    delay(4);
  }
  return distance / 100;//
}

//function for starting the buzzer
void playMelody() {
  int melody[] = {NOTE_C4, NOTE_G4, NOTE_A4, NOTE_F4};
  int durations[] = {500, 500, 500, 500};  // Milliseconds
  
  for (int i = 0; i < 4; i++) {
    tone(buzzerPin, melody[i], durations[i]);
    delay(durations[i] * 1.1);  // Pause between notes
    noTone(buzzerPin);
  }
}

void loop() {
  // Send heartbeat every 2 seconds to maintain connection
  BLEDevice::setPower(ESP_PWR_LVL_P9);  // Max power,at every iteration of void loop,to keep them active
  //BLE and WIFI are activating sleep mode when they are not active
  distMedium = calculateMediumDistance();
  delay(400);
  Serial.println(distMedium);
  
  esp_pm_configure(NULL);
  if(iScreech == 1){
    // Serial.println("Sunet");
    // tone(buzzerPin,2000);
    // delay(1000);
    // tone(buzzerPin,1000);
    // delay(1000);
    playMelody();
  }
  else{
    noTone(buzzerPin);
  }
  

  if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi disconnected! Reconnecting...");
        WiFi.reconnect();
        delay(2000);
    }
  





}