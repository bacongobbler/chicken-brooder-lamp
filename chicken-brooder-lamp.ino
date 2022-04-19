// which analog pin is the thermistor connected to?
#define THERMISTORPIN A0
// resistance of the thermistor at 25 C
#define THERMISTORNOMINAL 30000
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3754
// the resistance value of the fixed value resistor
#define RESISTORVALUE 10000
// how many samples to take and average out. More takes longer but is 'smoother'
#define NUMSAMPLES 5

// which digital pin is the relay connected to?
#define RELAYPIN 8
// what is the maximum temperature we want the brooder lamp to be? (in C)
#define MAX_TEMPERATURE 36.5
// what is the minimum temperature we want the brooder lamp to be? (in C)
#define MIN_TEMPERATURE 33.5

int samples[NUMSAMPLES];

void setup() {
	Serial.begin(9600);
	analogReference(EXTERNAL);
	pinMode(RELAYPIN, OUTPUT);
}

void loop() {
	uint8_t i;
	float reading;
	float resistance;
	float temperature;

	for (i = 0; i < NUMSAMPLES; i++) {
		samples[i] = analogRead(THERMISTORPIN);
		delay(10);
	}

	// average all the samples out
	reading = 0;
	for (i = 0; i < NUMSAMPLES; i++) {
		reading += samples[i];
	}
	reading /= NUMSAMPLES;

	// convert from a voltage to a resistance
	resistance = (1023 / reading) - 1;    // (1023 / ADC) - 1
	resistance = RESISTORVALUE / resistance; // 100K / (1023 / ADC) - 1

	// convert resistance to temperature using the Steinhart-Hart equation
	//
	// (simplified B parameter equation)
	temperature = resistance / THERMISTORNOMINAL;       // (R/Ro)
	temperature = log(temperature);                     // ln(R/Ro)
	temperature /= BCOEFFICIENT;                        // 1/B * ln(R/Ro)
	temperature += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
	temperature = 1.0 / temperature;                    // Invert
	temperature -= 273.15;                              // convert absolute temp to C

	Serial.print("Temperature: ");
	Serial.print(temperature);
	Serial.println(" C");

	// shut off if the brooder lamp goes over the max temperature
	if (temperature > MAX_TEMPERATURE) {
		digitalWrite(RELAYPIN, HIGH);
	}

	// turn it back on if the lamp drops below the min temperature
	if (temperature < MIN_TEMPERATURE) {
		digitalWrite(RELAYPIN, LOW);
	}

	delay(10000);
}
