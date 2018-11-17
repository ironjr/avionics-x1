# Avionics-X1
SNU Rocket Team Hanaro rocket avionics experimental project #1

### Main Purpose
Current Arduino-based model rocket control system has done its job pretty well in the past year. However, this system suffers from three major limitation:
1. Processing capability of Arduino boards are too low to introduce real-time Kalman filtering of sensors, or in-flight attitude evaluation.
1. Although Arduino board "may" be able to communicate via XBee module, its serial capability constrains rapid signal transmission.
1. Accessing and writing to data storages such as microSD card, which is currently used, takes serious amount of time, causing several tens of milliseconds of gaps between data points.

These problems didn't seem so easy to solve at first. After introducing raspberry pi video recording system, it became clear that integration of higher computation and interfacing capability of RPi board would solve much of the problems. Before redesign of avionics system of our model rocket [Identity-II](https://github.com/SNURocketTeamHanaro), I suggest investigating system-level configuration of MCU with sensors would be of help. In this experimental project, migration from Arduino to PIC18F based model rocket control system is tested.

### Works To Do
- Write I2C driver of BMP280 pressure/temperature sensor --> done!
- Write I2C driver of MPU9250 9-axis gyro/accel/magnetometer --> done!
- Establish communication channel between raspberry pi and MPU board --> on progress
- XBee test on RPi module with its capability of throughput and reliable transmission distance
- Integrate the system on a single or multiple PCB boards

### Credit
Jaerin Lee
