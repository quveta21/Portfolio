# **ESP32 BLE Distance Monitor with Audio Feedback**  
**Documentation**  

---

## **1. Overview**  
This firmware enables an **ESP32** to:  
- 📶 Measure distance using **WiFi RSSI** (Received Signal Strength Indicator)  
- 📱 Communicate via **Bluetooth Low Energy (BLE)**  
- 🔊 Provide **audio feedback** through a passive buzzer  
- 🔄 Reconnect to WiFi automatically if disconnected  

**Key Features:**  
- BLE Notifications for distance data  
- Melody playback when triggered (`iScreech` flag)  
- WiFi-based distance estimation  

---

## **2. Hardware Requirements**  
- **ESP32** (Tested on ESP32-WROOM-32)  
- **Passive Buzzer** (Connected to GPIO 25)  
- **WiFi Network** (For RSSI-based distance measurement)  

---

## **3. Software Architecture**  

### **3.1 Libraries Used**  
| Library | Purpose |  
|---------|---------|  
| `BLEDevice.h` | BLE Core Functions |  
| `BLEServer.h` | BLE Server Setup |  
| `BLEUtils.h` | BLE Utilities |  
| `BLE2902.h` | BLE Notifications |  
| `WiFi.h` | WiFi Connectivity |  
| `esp_pm.h` | Power Management |  

### **3.2 BLE Configuration**  
| UUID | Type | Purpose |  
|------|------|---------|  
| `0000abcd-...` | **Service** | Main BLE Service |  
| `0000deaf-...` | **TX Characteristic** | Sends distance data |  
| `0000beef-...` | **RX Characteristic** | Receives commands |  

- **TX Characteristic:**  
  - Properties: `READ` + `NOTIFY`  
  - Callback: `MyReadingCallBack` (sends distance value)  

- **RX Characteristic:**  
  - Properties: `WRITE`  
  - Callback: `MyCallbacks` (triggers buzzer on `iScreech`)  

---

## **4. Key Functions**  

### **4.1 `setup()`**  
Initializes:  
- **Serial Monitor** (115200 baud)  
- **Buzzer** (GPIO 25)  
- **BLE** (Server, Service, Characteristics)  
- **WiFi** (Connects to `ssid` and `password`)  

### **4.2 `loop()`**  
1. **Measures distance** (`calculateMediumDistance()`)  
2. **Updates BLE** (Sends distance via `pTxCharacteristic`)  
3. **Plays melody** if `iScreech == true`  
4. **Reconnects WiFi** if disconnected  

### **4.3 Distance Measurement**  
**Function:** `calculateMediumDistance()`  
- Uses **WiFi RSSI** to estimate distance  
- Applies **log-distance path loss model**:  
  ```cpp
  distance = 10^((txPower - RSSI) / (10 * n))
  ```
- **Parameters:**  
  - `txPower = -47` (RSSI at 1 meter)  
  - `n = 2.0` (Path-loss exponent)  
- **Averages 100 samples** for stability  

### **4.4 Buzzer Control**  
**Function:** `playMelody()`  
- Plays a **4-note melody** (`C4, G4, A4, F4`)  
- Uses `tone()` and `noTone()` for clean playback  

### **4.5 BLE Callbacks**  
| Callback | Trigger | Action |  
|----------|---------|--------|  
| `onWrite()` | Data received | Toggles `iScreech` if 5 bytes sent |  
| `onRead()` | Read request | Sends `distMedium` (2 decimal places) |  

---

## **5. Usage Instructions**  

### **5.1 Flashing the ESP32**  
1. **Install Arduino IDE + ESP32 Core**  
2. **Upload the code**  
3. **Monitor Serial Output** (115200 baud)  

### **5.2 BLE Interaction**  
- **Read Distance:** Read `TX Characteristic` (UUID: `0000deaf...`)  
- **Trigger Buzzer:** Write **5 bytes** to `RX Characteristic` (UUID: `0000beef...`)  

### **5.3 WiFi Setup**  
Modify in code:  
```cpp
const char* ssid = "qrp";         // Your WiFi SSID
const char* password = "procoder31";  // Your WiFi password
```

---

## **6. Troubleshooting**  
| Issue | Solution |  
|-------|----------|  
| **No BLE Connection** | Check UUIDs match in BLE client |  
| **Buzzer Not Working** | Verify GPIO 25 connection |  
| **WiFi Disconnects** | Ensure stable network |  
| **Inaccurate Distance** | Calibrate `txPower` and `n` |  

---

## **7. Customization**  
### **7.1 Change Melody**  
Modify `playMelody()`:  
```cpp
int melody[] = {NOTE_C4, NOTE_E4, NOTE_G4}; // New notes
int durations[] = {300, 300, 300};          // New durations
```

### **7.2 Improve Distance Accuracy**  
- Use **BLE RSSI** instead of WiFi (replace `WiFi.RSSI()` with BLE RSSI)  
- Implement **Kalman Filter** for smoothing  


# **ESP32 BLE Distance Monitor - Flutter Client**  

## **📱 Overview**  
This Flutter app connects to an **ESP32** over **Bluetooth Low Energy (BLE)** to:  
- 🔍 Scan and connect to an ESP32 running the companion firmware  
- 📏 Read distance measurements from the ESP32  
- 📲 Send commands to trigger audio feedback on the ESP32  

---

## **🛠️ Features**  
✅ **BLE Scanning** - Discover nearby ESP32 devices  
✅ **Distance Monitoring** - Read real-time distance values  
✅ **Command Control** - Send "blink" command to ESP32  
✅ **Auto-Reconnect** - Handles connection drops gracefully  

---

## **📋 Requirements**  
- **Flutter SDK** (v3.0+)  
- **flutter_blue_plus** (BLE plugin)  
- **ESP32 Firmware** ([See companion code](#))  
- **Android/iOS Device** (with BLE support)  

---

## **🔌 BLE Configuration**  
| UUID | Type | Purpose |  
|------|------|---------|  
| `0000abcd-...` | **Service** | Main BLE service |  
| `0000deaf-...` | **TX Characteristic** | Receives distance data |  
| `0000beef-...` | **RX Characteristic** | Accepts commands |  

---

## **🚀 Setup**  
1. **Clone the Repository**  
   ```bash
   git clone https://github.com/your-repo/esp32_ble_flutter.git
   cd esp32_ble_flutter
   ```

2. **Install Dependencies**  
   ```bash
   flutter pub get
   ```

3. **Run on Device**  
   ```bash
   flutter run
   ```

---

## **🎛️ Usage**  
### **1. Scanning for Devices**  
- Tap **"Scan for Devices"** to discover nearby ESP32s.  
- Devices appear in a list below.  

### **2. Connecting to ESP32**  
- Tap a device to connect.  
- The app will:  
  - Send a **"blink"** command (triggers buzzer on ESP32).  
  - Enable **notifications** for distance updates.  

### **3. Reading Distance**  
- Distance values appear in a **Card widget** at the bottom.  
- Updates automatically via BLE notifications.  

### **4. Debugging**  
- Connection status appears at the top.  
- Errors are logged in the status bar.  

---

## **⚙️ Key Functions**  
| Function | Purpose |  
|----------|---------|  
| `_startScan()` | Starts BLE device discovery |  
| `_connectToDevice()` | Handles BLE connection logic |  
| `_sendMamaliga()` | Sends "blink" command |  
| `_getDistData()` | Reads distance value |  

---

## **⚠️ Troubleshooting**  
| Issue | Solution |  
|-------|----------|  
| **No devices found** | Ensure ESP32 is advertising |  
| **Connection fails** | Check UUIDs match ESP32 firmware |  
| **Distance not updating** | Verify notifications are enabled |  

---


**🔗 Companion ESP32 Code:**  
[ESP32 BLE Distance Monitor Firmware](#)  




---

## **8. License**  
**MIT License** - Free for personal/commercial use.  

---

