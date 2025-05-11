# 💧 ESP32 EC (Electrical Conductivity) and Temperature Monitoring System

This project uses an **ESP32**, **DFRobot EC sensor**, and **DS18B20 temperature sensor** to measure the **nutrient concentration (EC)** in hydroponic or aquaponic systems with **temperature compensation**.

---

## 📦 Components Required

| Component                  | Quantity |
|----------------------------|----------|
| ESP32 Dev Board            | 1        |
| DFRobot Analog EC Sensor   | 1        |
| DS18B20 Temperature Sensor | 1        |
| 4.7kΩ Resistor (for DS18B20) | 1     |
| Breadboard + Jumper Wires  | as needed |

---

## ⚙️ Circuit Connections

| Sensor       | ESP32 Pin |
|--------------|-----------|
| EC Sensor    | A0 (GPIO 34) |
| DS18B20      | GPIO 23   |
| DS18B20 VCC  | 3.3V      |
| DS18B20 GND  | GND       |
| 4.7kΩ Resistor | Between DS18B20 Data & VCC |

---

## 🧠 Required Libraries

Install these via Arduino Library Manager:

- [DFRobot_ESP_EC](https://github.com/DFRobot/DFRobot_ESP_EC)
- OneWire by Paul Stoffregen
- DallasTemperature

---

## 🚀 Getting Started

### 1. Wiring

Connect the EC sensor and DS18B20 as shown above.

### 2. Upload the Code

- Open the Arduino IDE.
- Install the required libraries.
- Upload `main.ino` to your ESP32.

### 3. Serial Monitor

- Set **baud rate to 115200**.
- Every ~4 seconds, it will print:
  - EC voltage (raw + mV)
  - Temperature (°C)
  - EC in mS/cm

---

## 🔧 Calibration

### Step-by-Step:

1. Open Serial Monitor.
2. Submerge the EC probe in a standard solution (e.g., 1.413 mS/cm).
3. Type the value into Serial Monitor (e.g., `enterec,1.413`) and hit Enter.
4. The library will calibrate and store values in EEPROM.

You only need to calibrate once unless the sensor environment changes.

---

## 🧪 Sample Output

EC Raw Voltage (V): 1.3652
Temperature: 24.8 °C
EC Raw (ADC): 1680
EC Voltage (mV): 1365.2000
EC (mS/cm): 1.4512

---

## 📝 Notes

- Ensure the EC sensor is fully submerged for accurate readings.
- Voltage conversion uses a 3.3V reference and 12-bit ADC (0–4095).
- Calibration is stored in EEPROM at address 10 by default.

---

## 📁 File Structure

📦 esp32-ec-temp-monitor
┣ 📜 main.ino
┣ 📜 README.md

---

## 📚 References

- [DFRobot EC Sensor Wiki](https://wiki.dfrobot.com/Analog_EC_Meter_SKU__SEN0244)
- [DS18B20 Datasheet](https://datasheets.maximintegrated.com/en/ds/DS18B20.pdf)

---

## 💡 License

MIT License – Feel free to modify and use it for any personal or educational projects.
