const int led_pin = 26;
const int sensor_pin = 27;

const long interval = 10000;
unsigned long current_time = millis();
unsigned long last_trigger = 0;
boolean timer_on = false;
//interrupt to handle the motion detection at PIR
void IRAM_ATTR movement_detection() {
  Serial.println("Motion detected");
  digitalWrite(led_pin, HIGH);
  timer_on = true;
  last_trigger = millis();
}

void setup() {
 
  Serial.begin(115200);
 
  pinMode(sensor_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensor_pin), movement_detection, RISING);
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
}

void loop() {

  current_time = millis();
  if(timer_on && (current_time - last_trigger > interval)) {
    Serial.println("Motion stopped");
    digitalWrite(led_pin, LOW);
    timer_on = false;
  }
}
