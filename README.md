 #Arduino Smart House#

Summary
A multi-sensor smart home prototype designed as a second-year Electrical Engineering final project. It integrates automated window controls, a fire warning system, environment-aware lighting, corridor path tracking, and doorway occupancy detection onto a single microcontroller.
A Project Overview:
This project was built using sensors and actuators from a standard starter kit to demonstrate integrated home automation concepts. 

While pin constraints were a major challenge during design and using a single overhead Ultrasonic sensor for doorway counting has practical limitations compared to an IR break-beam—the goal was to showcase system integration, state logic, and sensor-actuator feedback loops in C++.


# Features:
Potentiometer-Controlled Servo Window: Translates analog input into smooth 0–180° window positioning.
Fire System Fan & Alarm: Triggers an L298N DC motor driver fan, buzzer tone, and flashing LED upon IR flame detection.
LDR Smart Lighting: Adjusts ambient room light brightness using PWM based on surrounding light levels.
Corridor Motion Lighting: Sequentially illuminates path LEDs based on ultrasonic distance thresholds.
Doorway Occupancy Counter: Tracks entry detection using an overhead ultrasonic proximity state machine.



# Components Used:
Microcontroller: Arduino 
Sensors: 2x HC-SR04 Ultrasonic Sensors, LDR Light Sensor, IR Flame Sensor
Actuators: 2x Micro Servos, DC Motor (Ventilation Fan), Buzzer
Drivers and Interface: L298N DC Motor Driver, Potentiometer, 3x Push Buttons
Outputs:LEDs (Fire, Room, and Corridor Lighting)

