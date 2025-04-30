#define ENC1_A 2
#define ENC1_B 9
#define ENC2_A 3
#define ENC2_B 10

volatile int position_a = 0;
volatile int position_b = 0;

void isr1() {
  if(digitalRead(ENC1_B) == HIGH)
    position_a++;
  else
    position_a--;
}

void isr2() {
  if(digitalRead(ENC2_B) == HIGH)
    position_b++;
  else
    position_b--;
}

void setup() {
  pinMode(ENC1_A, INPUT_PULLUP);
  pinMode(ENC2_A, INPUT_PULLUP);

  pinMode(ENC1_B, INPUT);
  pinMode(ENC2_B, INPUT);

  digitalWrite(ENC1_B, HIGH);
  digitalWrite(ENC1_A, HIGH);

  Serial.begin(115200);

  attachInterrupt(digitalPinToInterrupt(ENC1_A), &isr1, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC2_A), &isr2, RISING);
}

void loop() {
  Serial.print(position_a);
  Serial.print(" ");
  Serial.println(position_b);

  delay(49);
}
