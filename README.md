
   ------------------------------------------
   LESSON 02: Pulse Width Modulation (PWM)
   ------------------------------------------
   
   🎯 GOAL:
   Control the brightness of an LED using PWM to simulate analog output, 
   creating a "breathing" or "fading" effect.
   
   ---------------------------------------
   🔌 ESP32 HARDWARE CONCEPTS
   ---------------------------------------

   1. PWM (Pulse Width Modulation)
      PWM is a technique to get analog-like results with digital means. By switching 
      a pin ON and OFF very rapidly, we control the "Duty Cycle" (% of time ON).
      To the human eye, this looks like varying brightness.

   2. LED Control (LEDC) Peripheral
      The ESP32-S3 uses the "LEDC" peripheral for PWM.
      
      ledcAttach(pin, frequency, resolution);
      - Frequency:  Speed of cycles (e.g., 5000 Hz).
      - Resolution: Number of "steps" (8-bit = 256 steps, 0-255).
      
      ledcWrite(pin, dutyCycle);
      - Sets the actual duty cycle.

   3. Deep Dive: Resolution vs. Frequency
      The ESP32 timer is like a drummer who can beat a drum at a maximum fixed speed
      of 80 MHz (80 million times per second). This is your fixed budget. You must 
      "spend" these beats on two things:

      1 Resolution (Steps): How many distinct beats make up one full cycle.
        1-bit: ON or OFF (2 steps).
        8-bit: 256 steps (2^8). Standard for LEDs.
        16-bit: 65,536 steps (2^{16}). Incredibly smooth, used for precision.
      
      2 Frequency (Speed): How many times you repeat that full cycle per second.
      
      The Trade-off: You cannot have both "Infinite Steps" AND "Infinite Speed" 
      because you run out of beats.

      Max Frequency ≈ CPU Clock (80 MHz) / 2^Resolution

      ------------------------------------
      WHY CHOOSE WHICH?
      
      A. LEDs (Low Res / High Freq)
         - Human Perception: Your eyes can't see the difference between brightness 
           level 200 and 201. 8-bit (256 steps) is plenty for smooth fading.
         - Flicker: The Priority for LEDs is SPEED. If frequency is too low (<100Hz), 
           you see "flicker". We sacrifice steps to get speed (e.g. 5000Hz).
           
      B. Servos (High Res / Low Freq)
         - The "Window" Problem: Servos usually run at 50Hz (Low Speed). However, 
           they only listen to a tiny 1ms-2ms slice of that cycle.
         - If you use 8-bit (256 steps), that tiny slice only gets ~13 steps! 
           Your robot arm would move jerkily (0° -> 15° -> 30°).
         - If you use 16-bit (65536 steps), that slice gets ~3200 steps. 
           You can position the arm at exactly 10.1°.
      ------------------------------------
      
      | Resolution | Steps | Max Possible Freq | Best Use Case |
      | **8-bit** | 256 | ~312 kHz | Fast switching, Standard LEDs |
      | **10-bit** | 1024 | ~78 kHz | LED lighting (smoother) |
      | **14-bit** | 16,384 | ~4.8 kHz | Servo Motors (Precision) |
      | **16-bit** | 65,536 | ~1.2 kHz | Scientific instruments |