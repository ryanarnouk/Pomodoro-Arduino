// using analog pins as digital pins 
int buttonPin = A0; 
int greenLedPin = A1; 
int redLedPin = A2; 
int blueLedPin = A3;
int buzzerPin = A4; 

// states
/*
 * pomoState: 
 * 0 --> work
 * 1 --> shortbreak
 * 2 --> longbreak 
 * 
 * cycle: # of cycles of pomodoro
 * pause: pause state of timer
 * timerRunning: state for if timer is running
 */
int pomoState = 0; // 0 --> work | 1 --> shortbreak | 2 --> longbreak
int cycle = 0; // cycle of pomos
bool pause = false; 

// timer function state to prevent keep running in loop
boolean timerRunning = false; 

// 7 segment display pins
int pinA = 2; 
int pinB = 3; 
int pinC = 4; 
int pinD = 5; 
int pinE = 6; 
int pinF = 7; 
int pinG = 8; 
int D1 = 9; 
int D2 = 10; 
int D3 = 11; 
int D4 = 12; 

// time for loops (timer and ringer)
long unsigned starttime; 
long unsigned endtime; 

void setup() {
  Serial.begin(9600); 
  pinMode(buttonPin, INPUT); 
  pinMode(greenLedPin, OUTPUT); 
  pinMode(redLedPin, OUTPUT); 
  pinMode(blueLedPin, OUTPUT); 
  pinMode(buzzerPin, OUTPUT); 

  // initialize digital pins as outputs for 7 segment display
  pinMode(pinA, OUTPUT); 
  pinMode(pinB, OUTPUT); 
  pinMode(pinC, OUTPUT); 
  pinMode(pinD, OUTPUT); 
  pinMode(pinE, OUTPUT); 
  pinMode(pinF, OUTPUT); 
  pinMode(pinG, OUTPUT);
  pinMode(D1, OUTPUT); 
  pinMode(D2, OUTPUT); 
  pinMode(D3, OUTPUT); 
  pinMode(D4, OUTPUT); 
}

// function to write number to any digit on display 
void number(int digit, int number) {
  if (digit == 1) {
    digitalWrite(D1, HIGH); 
    digitalWrite(D2, LOW); 
    digitalWrite(D3, LOW); 
    digitalWrite(D4, LOW); 
  } else if (digit == 2) {
    digitalWrite(D1, LOW); 
    digitalWrite(D2, HIGH); 
    digitalWrite(D3, LOW); 
    digitalWrite(D4, LOW); 
  } else if (digit == 3) {
    digitalWrite(D1, LOW); 
    digitalWrite(D2, LOW); 
    digitalWrite(D3, HIGH); 
    digitalWrite(D4, LOW); 
  } else if (digit == 4) {
    digitalWrite(D1, LOW); 
    digitalWrite(D2, LOW); 
    digitalWrite(D3, LOW); 
    digitalWrite(D4, HIGH); 
  }
  if (number == 0) { 
    digitalWrite(pinA, LOW); 
    digitalWrite(pinB, LOW); 
    digitalWrite(pinC, LOW); 
    digitalWrite(pinD, LOW); 
    digitalWrite(pinE, LOW); 
    digitalWrite(pinF, LOW); 
    digitalWrite(pinG, HIGH);
  } else if (number == 1) {
    digitalWrite(pinA, HIGH); 
    digitalWrite(pinB, LOW); 
    digitalWrite(pinC, LOW); 
    digitalWrite(pinD, HIGH); 
    digitalWrite(pinE, HIGH); 
    digitalWrite(pinF, HIGH); 
    digitalWrite(pinG, HIGH);
  } else if (number == 2) {
    digitalWrite(pinA, LOW); 
    digitalWrite(pinB, LOW); 
    digitalWrite(pinC, HIGH); 
    digitalWrite(pinD, LOW); 
    digitalWrite(pinE, LOW); 
    digitalWrite(pinF, HIGH); 
    digitalWrite(pinG, LOW);
  } else if (number == 3) {
    digitalWrite(pinA, LOW); 
    digitalWrite(pinB, LOW); 
    digitalWrite(pinC, LOW); 
    digitalWrite(pinD, LOW); 
    digitalWrite(pinE, HIGH); 
    digitalWrite(pinF, HIGH); 
    digitalWrite(pinG, LOW);
  } else if (number == 4) {
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, LOW);     
  } else if (number == 5) {
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, LOW);  
  } else if (number == 6) {
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, LOW);  
  } else if (number == 7) {
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, HIGH);   
  } else if (number == 8) {
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, LOW);
  } else if (number == 9) {
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, LOW);
  }
  delay(4); 
}

// timer
void timer(int minutes, int seconds) {
  timerRunning = true; // running
  int timeseconds = (minutes * 60) + seconds;
  int currentseconds; 
  int currentminutes; 
  boolean timerresolved = false; 

  while (timeseconds > 0) {
    while (pause) {
      // while paused display current time
      number(1, currentminutes/10); 
      number(2, currentminutes%10); 
      number(3, currentseconds/10); 
      number(4, currentseconds%10); 
      buttoncontrols(); 
    }
    currentseconds = timeseconds % 60; 
    currentminutes = timeseconds / 60; 
    starttime = millis(); 
    endtime = starttime; 
    while ((endtime-starttime) <= 1000) {
      // write to display for duration of one second
      number(1, currentminutes/10); 
      number(2, currentminutes%10); 
      number(3, currentseconds/10); 
      number(4, currentseconds%10); 
      endtime = millis(); 
    }

    buttoncontrols(); 
    
    timeseconds--; 
  }
  if (timeseconds == 0) {
    // done timer
    // ring
    starttime = millis(); 
    endtime = starttime; 
    while ((endtime - starttime) <= 3000) {
      tone(buzzerPin, 250, 500);
      delay(1000);  
      endtime = millis(); 
    }

    // state 
    timerRunning = false; 
    if (pomoState == 0 && cycle == 4) {
      pomoState = 2; 
    } if (pomoState == 0) {
      // switch from work to shortbreak 
      pomoState = 1; 
    } else if (pomoState == 1 || pomoState == 2) {
      // switch from break to work 
      pomoState = 0; 
    }
  } 
}

void buttoncontrols() {
  if (digitalRead(buttonPin) == HIGH) {
    if (!pause) {
      pause = true; 
    } else if (pause) {
      pause = false; 
    }
    delay(300); 
  }

  if (pause) {
    digitalWrite(blueLedPin, HIGH);  
  } else {
    digitalWrite(blueLedPin, LOW); 
  }
}

void loop() { 
  /* State: (pomo)
   * 0 --> work cycle
   * 1 --> short break
   * 2 --> long break
   * 3 --> pause
   */
   
  // todo --> fix long breaks 
  // refactor code
  // fix up remaining parts of circuit to make button accessible
  // sleep mode after button pressed for 3 seconds
  if (!timerRunning) {    
    if (pomoState == 0) {
      // work
      digitalWrite(greenLedPin, LOW); 
      digitalWrite(redLedPin, HIGH);
      
      //timer(25, 0);   
      timer(25, 0); 
    } else if (pomoState == 1) {
      // short break
      digitalWrite(greenLedPin, HIGH); 
      digitalWrite(redLedPin, LOW); 
      
      cycle++; 
      timer(5, 0); 
    } else if (pomoState == 2) {
      // long break
      digitalWrite(greenLedPin, HIGH); 
      digitalWrite(redLedPin, LOW);
      
      cycle = 0; 
      timer(20, 0);  
    } 
  }
}
