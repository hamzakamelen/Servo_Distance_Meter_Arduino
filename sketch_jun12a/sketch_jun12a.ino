const int trigPin = 9;      // Trigger pin of the ultrasonic sensor
const int echoPin = 8;      // Echo pin of the ultrasonic sensor
const int LED_PIN = 10;     // External LED pin (change as per your setup)
const int BUZZER_PIN = 11;  // Buzzer pin

void setup() {
  Serial.begin(9600);  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);  // Set built-in LED pin as OUTPUT
  pinMode(BUZZER_PIN, OUTPUT);   // Set buzzer pin as OUTPUT
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the response time of the ultrasonic sensor
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;

  // Print the measured distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if an object is detected within 10 cm range
  if (distance < 10) {
    // Blink the external LED and built-in LED simultaneously
    while (distance < 10) {
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);  // Turn on the buzzer
      delay(200);
      digitalWrite(LED_PIN, LOW);
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);   // Turn off the buzzer
      delay(200);

      // Trigger the ultrasonic sensor for the updated distance
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      // Measure the response time of the ultrasonic sensor
      duration = pulseIn(echoPin, HIGH);
      distance = duration * 0.034 / 2;
    }
  } else {
    digitalWrite(LED_PIN, LOW);      // Turn off the external LED if no object detected within 10 cm
    digitalWrite(LED_BUILTIN, LOW);  // Turn off the built-in LED if no object detected within 10 cm
    digitalWrite(BUZZER_PIN, LOW);   // Turn off the buzzer if no object detected within 10 cm
  }

  delay(1000);  // Delay before taking the next measurement
}