// ============================================================
// NAUTILUS ENERGY HUB — Battery Management Firmware v1.0
// Bachelor's Thesis: Energy Harvesting System for the Venice Lagoon
// Università degli Studi di Padova — Krom Llorca Lloret
// ============================================================
//
// Monitors the Li-Ion battery voltage and activates a MOSFET-switched
// dump load when the cell reaches its maximum safe voltage (4.20 V),
// acting as a secondary, software-controlled overvoltage protection
// on top of the TP4056 CC/CV charger.

// --- Pin Definitions ---
const int GREEN_LED_PIN = 6;   // Charging OK indicator
const int RED_LED_PIN   = 7;   // Overvoltage / dump load indicator
const int MOSFET_PIN    = 8;   // Controls dump load resistor (IRFZ44N)
const int VOLTAGE_PIN   = A0;  // Battery voltage via divider

// --- Safety Threshold ---
const float V_THRESHOLD = 4.20;     // Li-Ion max safe voltage

// --- Voltage Divider Factor ---
const float DIVIDER_FACTOR = 2.0;   // 10 kOhm / 10 kOhm divider

void setup() {
  Serial.begin(9600);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN,   OUTPUT);
  pinMode(MOSFET_PIN,    OUTPUT);
  Serial.println("Nautilus Energy Hub - System Initialised");
}

void loop() {
  // 1. Read and calculate battery voltage
  int rawADC = analogRead(VOLTAGE_PIN);
  float vBatt = (rawADC / 1023.0) * 5.0 * DIVIDER_FACTOR;

  // 2. Output to Serial Monitor
  Serial.print("Battery Voltage: ");
  Serial.print(vBatt, 2);
  Serial.println(" V");

  // 3. Safety threshold comparison
  if (vBatt >= V_THRESHOLD) {
    // --- OVERVOLTAGE STATE: Battery Full ---
    digitalWrite(MOSFET_PIN,    HIGH);  // Dump load ON
    digitalWrite(RED_LED_PIN,   HIGH);  // Red LED ON
    digitalWrite(GREEN_LED_PIN, LOW);   // Green LED OFF
    Serial.println("!!! OVERVOLTAGE PROTECTION ACTIVE !!!");
  } else {
    // --- NORMAL STATE: Charging Safe ---
    digitalWrite(MOSFET_PIN,    LOW);   // Dump load OFF
    digitalWrite(RED_LED_PIN,   LOW);   // Red LED OFF
    digitalWrite(GREEN_LED_PIN, HIGH);  // Green LED ON
  }

  delay(500);  // 2 Hz loop rate
}
