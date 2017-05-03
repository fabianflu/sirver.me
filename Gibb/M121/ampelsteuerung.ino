// GIBB: Modul 121: Steuerungsaufgaben bearbeiten, BiVo 2014
// Ampelsteuerung mit Arduino (Finite State Machines)
// 2017 by Fabian Flückiger // info@fabianflu.ch

// Variablendeklaration für Pins
#define LED_PIN_RED 12
#define LED_PIN_YELLOW 11
#define LED_PIN_GREEN 10
#define SWITCH 6
// Deklaration der für die Leuchtdauer der LEDs benötigten Variabel.
unsigned long startTime = millis();

void setup() {
  // Setzen der Pinmodes
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(LED_PIN_YELLOW, OUTPUT);
  pinMode(LED_PIN_GREEN, OUTPUT);
  pinMode(SWITCH, INPUT);
}

void loop() {
  // Rot
  trafficlight(HIGH, LOW, LOW, 10000);
  // Rot-Gelb
  trafficlight(HIGH, HIGH, LOW, 2000);
  // Grün
  trafficlight(LOW, LOW, HIGH, 10000);
  // Gelb
  trafficlight(LOW, HIGH, LOW, 2000);
}
// Nachtmodus
void nightrider() {
  // Wenn der Button gedrückt wird..
  while (digitalRead(SWITCH) == HIGH) {
    // Blinken im Sekundentakt
    nightblink(HIGH, 1000);
    nightblink(LOW, 1000);
  }
}
// Trafficlight: Universell verwendbar! ;) Akzeptiert die Argumente State1, State2 & State3 (Status der LEDs => HIGH / LOW) sowie die Dauer des Leuchtens in ms.
void trafficlight(char State1, char State2, char State3, int dauer) {
  // Startzeit-Timestamp
  startTime = millis();
  // Mit millis() holen wir den aktuellen Timestamp und vergleichen diesen mit dem Starttimestamp und der Dauer. Wird die Dauer erreicht sind wir fertig!
  while (millis() - startTime < dauer) {
    // Ansteuern der LEDs.
    digitalWrite(LED_PIN_RED, State1);
    digitalWrite(LED_PIN_YELLOW, State2);
    digitalWrite(LED_PIN_GREEN, State3);
    // Nachtmodus-Button-Check!
    nightrider();
  }
}
// Spezielle Trafficlight-Void für Nightrider, damit eine Rekursion verhindert wird...
void nightblink(char StateBlink, int dauer) {
  // Startzeit-Timestamp
  startTime = millis();
  // Mit millis() holen wir den aktuellen Timestamp und vergleichen diesen mit dem Starttimestamp und der Dauer. Wird die Dauer erreicht sind wir fertig!
   while (millis() - startTime < dauer && digitalRead(SWITCH) == HIGH) {
    digitalWrite(LED_PIN_RED, LOW);
    digitalWrite(LED_PIN_YELLOW, StateBlink);
    digitalWrite(LED_PIN_GREEN, LOW);
  }
}
