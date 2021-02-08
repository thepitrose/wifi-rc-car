#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
ESP8266WebServer server;


Servo name_servo;

int servo_position = 0;


uint8_t pin_led = 16;
char* ssid = "WIFI";
char* password = "PASSWORD";


static IPAddress ip(192, 168, 14, 201); // static IP used for browser access: http://IPaddress
static IPAddress gateway(192, 168, 14, 1);
static IPAddress subnet(255, 255, 255, 0);

// These are the pins used to control the motor shield

#define DRIVE_MOTOR_POWER D2 // Motor B
#define DRIVE_MOTOR_DIRECTION D4

#define STEER_MOTOR_POWER D1 // Motor A
#define STEER_MOTOR_DIRECTION D3



// drivePower sets how fast the car goes
// Can be set between 0 and 1023 (although car problaly wont move if values are too low)
int drivePower = 1023;

// driveDirection sets what direction the car drives
// If the car is moving backwards when you press the forward button, change this to LOW
uint8_t driveDirection = HIGH;

// steeringPower sets how fast the car turns
// Can be set between 0 and 1023 (again, car probably won't steer if the value is too low)
int steeringPower = 1023;

// steerDirection sets what direction the car steers
// If the car is steering right when you press the left button, change this to LOW
uint8_t steerDirection = HIGH;


const char *webpage = 
#include "web.h"
;

void setup()
{
  WiFi.config(ip, gateway, subnet); 
  name_servo.attach (D8);
  pinMode(DRIVE_MOTOR_POWER, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(DRIVE_MOTOR_DIRECTION, OUTPUT);
  pinMode(STEER_MOTOR_POWER, OUTPUT);
  pinMode(STEER_MOTOR_DIRECTION, OUTPUT);

  
  pinMode(pin_led, OUTPUT);
  WiFi.begin(ssid,password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/",[](){server.send_P(200,"text/html", webpage);});
  server.on("/ledstate",toggleLED);
  server.on("/forward",forward);
  server.on("/dback",dback);
  server.on("/dleft",dleft);
  server.on("/dright",dright);
  server.on("/stopme",stopme);
  server.on("/stopside",stopside);
  server.begin();
}

void loop()
{
  server.handleClient();
}

void toggleLED()
{
  digitalWrite(pin_led,!digitalRead(pin_led));
  server.send(0);
}

void forward()
{
  
    analogWrite(DRIVE_MOTOR_POWER, drivePower);
    digitalWrite(DRIVE_MOTOR_DIRECTION, driveDirection);
    server.send(0);

}


void dback()
{
  
    analogWrite(DRIVE_MOTOR_POWER, drivePower);
    digitalWrite(DRIVE_MOTOR_DIRECTION, !driveDirection);
    server.send(0);

}

void dleft()
{
  
    analogWrite(STEER_MOTOR_POWER, steeringPower);
    digitalWrite(STEER_MOTOR_DIRECTION, !steerDirection);
    server.send(0);

}


void dright()
{
  
    analogWrite(STEER_MOTOR_POWER, steeringPower);
    digitalWrite(STEER_MOTOR_DIRECTION, steerDirection);
    server.send(0);
}



void stopme()
{
  
    analogWrite(DRIVE_MOTOR_POWER, 0);
    analogWrite(STEER_MOTOR_POWER, 0);
    server.send(0);
}

void stopside()
{
  
    analogWrite(STEER_MOTOR_POWER, 0);
    analogWrite(STEER_MOTOR_DIRECTION, 0);
    server.send(0);
}
