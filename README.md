# Pomodoro Arduino 
A simple Pomodoro timer built with an Arduino Uno. 

The Pomodoro technique breaks work down into 25 minute intervals with 5 minute breaks in between each interval. The Pomodoro technique helps improve focus and productivity. 

## Circuit
Circuit design: 
![Circuit Design](https://raw.githubusercontent.com/ryanarnouk/Pomodoro-Arduino/master/images/finalcircuit.png)


## Components
- Arduino Uno
- Breadboard (full size preferable)
- Jumper Wire (25x)
- Pushbutton 
- Red, Blue, Green LED (3x)
- Active or passive buzzer
- 220 Ohm Resistor (3x)
- 10K Ohm Resistor (1x) 

## Final Product
![Final Product](https://raw.githubusercontent.com/ryanarnouk/Pomodoro-Arduino/master/images/finalproduct/finalproduct.jpg)

![Final Product 2](https://raw.githubusercontent.com/ryanarnouk/Pomodoro-Arduino/master/images/finalproduct/finalproduct2.jpg)

![Final Product 3](https://raw.githubusercontent.com/ryanarnouk/Pomodoro-Arduino/master/images/finalproduct/finalproduct3.jpg)

![Final Product 4](https://raw.githubusercontent.com/ryanarnouk/Pomodoro-Arduino/master/images/finalproduct/finalproduct4.jpg)

## Code
Code can be found in `/pomodoromain` and `/pomodoromainpowermode`. Pomodoro power mode requires the user to hold the button for 3 seconds to power the rest of the components on and is the latest code written. 

Written in C++

## Future
- Implement longer breaks after 4 Pomodoro sessions. 
- Implement power off feature. 
- Design blue LED to pulse to show how many Pomodoro sessions completed. 

Ryan Arnouk

2020