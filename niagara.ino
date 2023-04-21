/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground through 220 ohm resistor
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
*/

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;  // the number of the pushbutton pin
const int ledPin = 5;    // the number of the LED pin
const int tempo_on = 10000; //TEMPO LIGADA DURANTE CADA CICLO, EM MILLISSECONDS
const int intervalo_reciclo = 10; //TEMPO ENTRE CADA CICLO, EM SEGUNDOS
const int quant_replays = 3; //QUANTIDADE DE VEZES QUE ELE FARÁ O RECLICLO

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status

int cont = 0;

int replays = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {

  buttonState = digitalRead(buttonPin);

  Serial.println("Iniciando o sistema..."); // Imprime na tela
    Serial.print("cont = "); // Imprime na tela
  Serial.println(cont); // Imprime na tela
  Serial.print("replays = "); // Imprime na tela
  Serial.println(replays); // Imprime na tela
  Serial.print("buttonState = "); // Imprime na tela
  Serial.println(buttonState); // Imprime na tela
  Serial.println(""); // Imprime na tela
  // read the state of the pushbutton value:
  cont = cont++;
  delay(10000);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, LOW);
    //cont = 0;
    //replays = 0;
    delay(tempo_on); /////// VALOR DEFINIDO PARA TEMPO LIGADA A MÁQUINA
  } else {
      if (replays < quant_replays){
        if (cont > intervalo_reciclo){
        digitalWrite(ledPin, LOW);
        cont = 0;
        replays = replays++;
        delay(tempo_on);
        digitalWrite(ledPin, HIGH);
      }
    }
        // turn LED off:
    digitalWrite(ledPin, HIGH);
  }
  Serial.print("cont = "); // Imprime na tela
  Serial.println(cont); // Imprime na tela
  Serial.print("replays = "); // Imprime na tela
  Serial.println(replays); // Imprime na tela
  Serial.print("buttonState = "); // Imprime na tela
  Serial.println(buttonState); // Imprime na tela
  Serial.println(""); // Imprime na tela
}
