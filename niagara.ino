/*
  State change detection (edge detection)
*/

// this constant won't change:
const int buttonPin = 2;  // the pin that the pushbutton is attached to
const int ledPin = 6;    // the pin that the LED is attached to
const int relayPin = 5;    // the pin that the Relat Module is attached to
unsigned long previousMillis = 0; //time that the LED state was last changed
unsigned long previousMillis_check = 0; //time that the LED state was last changed

// Variables will change:
int buttonPushCounter = 0;  // counter for the number of button presses
int buttonState = 0;        // current state of the button
int lastButtonState = 0;    // previous state of the button
int state = 0;    // previous state of the button
int state_inicial_pump = 0;    // state of the function initial_pump
int disable_inicial = 0;
int state_pump = 0;    // state of the function initial_pump
int flag_millis = 0;
int flag_check = 0;
unsigned long cont = 10000;    // previous state of the button


void initial_pump(){
  flag_millis = 1;
    if (millis() - previousMillis > 5000) { //3000ms or 3 seconds since last event
    digitalWrite(relayPin, LOW);
  }
    if (millis() - previousMillis > 10000) { //3000ms or 3 seconds since last event
    digitalWrite(relayPin, HIGH);
  }
    if (millis() - previousMillis > 15000) { //3000ms or 3 seconds since last event
    digitalWrite(relayPin, LOW);
    previousMillis = millis(); // save time that event last occurred
    state_inicial_pump = 0;
    state_pump = 1;
    disable_inicial = 1;
  }
}

void pump(){
  if (state != 0) {
    digitalWrite(relayPin, LOW);
    cont = ((millis() - previousMillis) + 10000);
  }

    if (millis() - previousMillis > cont) { //3000ms or 3 seconds since last event
    digitalWrite(relayPin, HIGH);
    previousMillis = millis(); // save time that event last occurred
    cont = 10000;
    state_pump = 0;
    state_inicial_pump = 0;
    flag_millis = 0;
    disable_inicial = 0;
  }
}

void check_pump(){
    if (millis() - previousMillis_check > 300000) { //3000ms or 3 seconds since last event
    disable_inicial = 1;
    digitalWrite(relayPin, LOW);
    if (buttonState == HIGH) {
      flag_check++;
    }
    if (millis() - previousMillis_check > 303000) { //3000ms or 3 seconds since last event
    if (flag_check > 10) {
      state_pump = 1;
    } else {
      digitalWrite(relayPin, HIGH);
    }
    previousMillis_check = millis();
    state_inicial_pump = 0;
    disable_inicial = 0;
    flag_check = 0;
  }
  }
}

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the Relay as an output:
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      state = 1;
    } else {
      // if the current state is LOW then the button went from on to off:
      state = 0;
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;


  // turns on the LED every four button pushes by checking the modulo of the
  // button push counter. the modulo function gives you the remainder of the
  // division of two numbers:
  if (state == 1) {
    digitalWrite(ledPin, HIGH);
    state_inicial_pump = 1;
  } else {
    digitalWrite(ledPin, LOW);
  }
  if (state_inicial_pump == 1 && disable_inicial == 0) {
    initial_pump();
    previousMillis_check = millis();
  }
  if (state_pump == 1) {
    pump();
    previousMillis_check = millis();
  }

  if ((millis() - previousMillis_check) > 300000) {
    check_pump();
  }

  if (flag_millis == 0) {
        previousMillis = millis(); // save time that event last occurred
  }

    Serial.print("millis: ");
    Serial.print(millis());
    Serial.print(" || previousMillis: ");
    Serial.print(previousMillis);
    Serial.print(" || Value: ");
    Serial.print(millis() - previousMillis);
    Serial.print(" || flag_millis: ");
    Serial.print(flag_millis);
    Serial.print(" || cont: ");
    Serial.print(cont);
    Serial.print(" || previousMillis_check: ");
    Serial.print(previousMillis_check);
    Serial.print(" || Value2: ");
    Serial.print(millis() - previousMillis_check);
    Serial.print(" || Check: ");
    Serial.println(flag_check);


}
