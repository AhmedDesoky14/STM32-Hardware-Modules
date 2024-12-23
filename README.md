# STM32Fx Hardware Modules

This repository contains hardware modules for STM32Fx microcontrollers, based on STM32 HAL libraries.

---

### Modules Included:

1. **GY521 IMU (Accelerometer & Gyroscope)**  
   Interfaces with the GY521 IMU module using I2C to read accelerometer and gyroscope data. This is crucial for detecting motion and orientation changes.

2. **GY271 Magnetometer**  
   Interfaces with the GY271 magnetometer using I2C to measure magnetic field strength, aiding in compass-based orientation and navigation.

3. **IR Sensors**  
   Includes infrared sensor modules for proximity detection, commonly used for object avoidance and positioning.

4. **JSN-SR04T Ultrasonic Sensors**  
   Interfaces with ultrasonic distance sensors for precise measurement of distances, essential for parking space detection and collision avoidance.

5. **DC Motor**  
   Controls DC motors for movement using PWM of STM32Fx timers, enabling forward, reverse, and rotational motion.

6. **ESP8266 Wi-Fi Module**  
   Configures the ESP8266 module to iterface with it using UART-based communication, allowing the STM32Fx to operate as a Wi-Fi station or access point.  
   - **Station Mode:** Connects to a Wi-Fi network.  
   - **Access Point Mode:** Creates a Wi-Fi network for communication with clients.  
   - **Client-Server Mode:** Supports up to 4 clients, capable of asynchronous sending and receiving data.

---

### Purpose:

These modules are part of the **Secured V2X Enabled Autoparking System Graduation Project**, mentored by **Valeo**. The project focuses on leveraging hardware and communication technologies to create a secure, efficient, and autonomous parking solution with Vehicle-to-Everything (V2X) communication capabilities.

---

**Authors:**
	Ahmed Desoky,
	Esraa Fawzy,
	Dina Hamed,
	Ziad Emad
	
**Emails:**
	ahmed0201150@gmail.com,
	ef44529@gmail.com,
	dina.hamed001@gmail.com,
	ziademadh7@gmail.com
