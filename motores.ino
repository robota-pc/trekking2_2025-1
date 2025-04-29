#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
byte command;

// Motor A
int motor1Pin1 = 22; 
int motor1Pin2 = 23; 

// Motor B
int motor2Pin1=19;
int motor2Pin2=21;

/* Check if Bluetooth configurations are enabled in the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

void setup()
{
  //Motor1 Pins
  pinMode(motor1Pin1,OUTPUT);
  pinMode(motor1Pin2,OUTPUT);

  //Motor2 Pins
  pinMode(motor2Pin1,OUTPUT);
  pinMode(motor2Pin2,OUTPUT);
  
  Serial.begin(115200);
  SerialBT.begin("ESP32");
  Serial.println("Bluetooth Started! Ready to pair...");
  Serial.print("Testing DC Motor...");
}

void loop()
{
  if(SerialBT.available())
  {
    command = SerialBT.read();
    Serial.write(command);
  }
// Going Forward
  if(command=='F')
  {
    Serial.println(" frente");
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);

  }
//Going Backward
  if(command=='B')
  {
    Serial.println(" tras");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);

  }
//Turning Left
  if(command=='L')
  {
    Serial.println(" curva 1");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);

  }
//Turning Left
  if(command=='R')
  {
    Serial.println(" curva 2");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);

  }
//Stopping
  if(command=='P')
  {
    Serial.println(" para");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);

  }

  delay(20);
  
}
