# ESP32-Based Secure Multi-Layer Access Control System using Keypad Authentication

## 📌 Project Overview
This project is a secure embedded access control system built using **ESP32 and a 4×4 matrix keypad**. It performs password-based authentication with LED status indication and supports password update functionality with validation and history checking.

The system demonstrates core embedded systems concepts such as GPIO interfacing, keypad scanning, state machine design, and basic security implementation.

---

## ⚙️ Features

- 4×4 Matrix Keypad input system  
- 4-digit password authentication  
- Multi-state operation (Login & Password Change mode)  
- Password update functionality using `*` key  
- Password confirmation system  
- Password history check to prevent reuse  
- LED-based status indication:
  - 🟢 Green LED → Access Granted  
  - 🔴 Red LED → Access Denied  
  - 🔵 Blue LED → Password Updated Successfully  
  - ⚪ White LED → Password already used  

---

## 🧰 Hardware Requirements

- ESP32 Development Board  
- 4×4 Matrix Keypad  
- LEDs (Green, Red, Blue, White)  
- 220Ω Resistors  
- Breadboard  
- Jumper Wires  

---

## 🔌 Pin Configuration

| Component   | GPIO |
|-------------|------|
| R1          | 14   |
| R2          | 27   |
| R3          | 26   |
| R4          | 25   |
| C1          | 33   |
| C2          | 32   |
| C3          | 22   |
| C4          | 23   |
| Green LED   | 21   |
| Red LED     | 19   |
| Blue LED    | 18   |
| White LED   | 5    |

---

## 🧠 Working Principle

1. User enters a 4-digit password using keypad  
2. System compares input with stored password  
3. If correct → Green LED ON (Access Granted)  
4. If incorrect → Red LED ON (Access Denied)  
5. Press `*` to enter password change mode  
6. System verifies old password  
7. User enters and confirms new password  
8. New password is checked against password history  
9. If valid → Blue LED ON (Password Updated)  
10. If already used → White LED blinks (Rejected)  

---

## 🧩 Concepts Used

- ESP32 GPIO programming  
- 4×4 Matrix keypad scanning  
- String handling in C (`strcmp`, `strcpy`)  
- State machine design  
- Embedded security logic  
- Event-driven firmware design  

---

## 🚀 Future Improvements

- Multiple user authentication system  
- EEPROM/NVS password storage (non-volatile memory)  
- RFID integration  
- Fingerprint sensor support  
- OLED/LCD display UI  
- Wi-Fi based logging system  
- Wrong attempt lockout system  

---

## 📷 Project Images

_Add hardware setup and circuit images here_

---

## 🎥 Demo Video

_Add demo video link or GIF here_

---

## 👨‍💻 Author

Shaik Rizwan Basha
ESP32 Embedded Systems Project  
Focused on firmware development, IoT fundamentals, and real-world embedded applications.

---

## ⭐ Conclusion

This project demonstrates a real-world embedded security system using ESP32 with keypad-based authentication, password management, and LED status feedback. It is designed to simulate industrial-level access control logic using state machine architecture.
