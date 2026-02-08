# Multi-Mode-Robotic-Vehicle
Autonomous Obstacle-Avoiding Robot with Bluetooth Control
Project Journey
This project began as a personal challenge to master Bluetooth-controlled robotics. After successfully building the initial prototype, I sought to enhance its capabilities by studying autonomous obstacle avoidance.

The real breakthrough came when I decided to merge these two distinct systems into a single, cohesive platform. To push the complexity further, I integrated an ultrasonic-based parking sensor system, mimicking real-world automotive safety features. This iterative process allowed me to explore embedded systems, sensor fusion, and multi-modal operation.

Bill of Materials (BOM)
The materials are listed according to the specific version you wish to build.

Phase 1: Bluetooth Controlled Vehicle
4WD Robot Chassis Kit (includes 4 DC motors)
Arduino Uno R3
L298N Dual H-Bridge Motor Driver
HC-06 Bluetooth Module
Breadboard (Small)
Resistors: 3x 1kΩ
Jumper Wires: 14x (Male-to-Male)
Power Supply: 4x AA Batteries (for motors) & 1x 9V Battery (for Arduino)

Phase 2: Autonomous Obstacle-Avoiding Vehicle
4WD Robot Chassis Kit
Arduino Uno R3
L298N Motor Driver
HC-SR04 Ultrasonic Sensor
Jumper Wires: 11x
Power Supply: 4x AA Batteries & 1x 9V Battery

Phase 3: Standalone Parking Sensor System
Arduino Uno or Nano
HC-SR04 Ultrasonic Sensor
Buzzer
LEDs: 4x (Red, Yellow, Green, Blue)
Resistors: 5x 220Ω
Jumper Wires: 11x
Power Supply: 1x 9V Battery

Phase 4: The Integrated "Full Package" System
All components from Phase 1 & 2
Buzzer
Resistors: 3x 1kΩ & 1x 220Ω
Jumper Wires: 20x (Total)

Technical Analysis & Challenges
While the Obstacle Avoidance and Parking Sensor modes are fully functional, the integration of multiple systems into the "Full Package" version introduced several engineering challenges.
Known Issues & Engineering Analysis
+-----------------------------+------------------------------------------------------------------------------------+-------------------------------------------------------------------------------------------------
| Issue                       | Description                                                                        | Status / Proposed Solution                                                                      
+-----------------------------+------------------------------------------------------------------------------------+-------------------------------------------------------------------------------------------------
| Bluetooth Command Latency 📶| Sending rapid, consecutive commands via Bluetooth causes system lag or buffer      | Planning to implement Software-side Command Filtering to ignore redundant inputs and optimize   
|                             | interference.                                                                      | processing speed.                                                                               
+-----------------------------+------------------------------------------------------------------------------------+-------------------------------------------------------------------------------------------------
| Power Management 🔋         | Simultaneous operation of 4 DC motors and multiple sensors leads to significant    | Investigating Power Distribution optimization and auditing the software to reduce peak         
|                             | voltage drops, causing system instability in the integrated mode.                  | current draw.                                                                                   
+-----------------------------+------------------------------------------------------------------------------------+-------------------------------------------------------------------------------------------------
| System Integration Lag 🧩   | Combining all modules increases CPU load, causing slight delays in sensor response | Considering a shift from blocking functions (like delay()) to non-blocking logic (using         
|                             | times.                                                                             | millis()) for better multitasking.                                                              
+-----------------------------+------------------------------------------------------------------------------------+-------------------------------------------------------------------------------------------------

Future Roadmap
[1] Finalize the command filtering algorithm for smoother Bluetooth control.
[2] Optimize the hardware power circuit (e.g., using separate power rails for logic and motors).
[3] Conduct a full code refactor to improve execution efficiency.
