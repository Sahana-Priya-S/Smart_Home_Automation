**HOME AUTOMATION SYSTEM**

This project demonstrates a simple home automation system using an Arduino board, various sensors, and actuators to control home appliances and monitor environmental conditions.

**Components Used:**
* Arduino Board
* Jumper Wires
* Breadboard
* LED Lights: The LEDs represent lights in different rooms that can be controlled remotely to turn on and off.
* Fan Control: A DC motor indicates the fan, which can be controlled remotely.
* Temperature Monitoring: The DHT11 sensor measures changes in temperature, enabling the user to monitor and adjust the temperature as required.
* Fire Alarm: A buzzer is used to alert in case of fire, ensuring safety.
* Smartphone Connectivity: The system uses an HC-05 module to connect lights and fans to our phone for remote control.
* User Interface: The interface is developed using MIT App Inventor to control the appliances with:
  * Buttons
  * Voice commands  
* Automatic Lighting : A LDR module to determines the amount of natural light and automatically turn on a led in dark
conditions
* Garage Monitoring: Two HC-SR04 sensors :
  * One detects the presence of vehicles inside the garage and switches the led on if occupied to indicate it
  * One to sense the outside surroundings of the garage and open the door using a servo motor
* Servo Motor: Acts as the garage door.
  
**Dependencies:**
* DHT Library
* Servo Library

**Block Diagram:**

  ![Block diagram](https://github.com/user-attachments/assets/45cafe23-a95f-4e0c-abf8-c15c86996f6e)
