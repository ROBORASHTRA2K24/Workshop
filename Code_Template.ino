#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

WiFiClient client;
Servo myservo;
ESP8266WebServer server(80);

const char* ssid = "__";
const char* password = "__";

const int gripperOpenAngle = __;
const int gripperClosedAngle = __;
int robospeed = __; // Defining speed limit min 400 to max 1023

String direction = "";
String servo_clamp = "";

int RMotor_1 = __; 
int RMotor_2 = __; 
int LMotor_1 = __; 
int LMotor_2 = __; 

int REnable = __; 
int LEnable = __; 

int grabPin = __; 

// Function prototypes
void openGripper();
void handleRoot();
void handleClose();
void connectingToWiFi();
void move_forward();
void open_grabbing_arm();
//Add the necessary functions


void connectingToWiFi()
{
  delay(3000);
  WiFi.disconnect();
  delay(1000);
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (!(WiFi.status() == WL_CONNECTED))
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.println("Local IP is : ");
  Serial.print((WiFi.localIP().toString()));
  delay(5000);
  }

void handleRoot() {
  server.send(200, "text/html", "<h1>ESP8266 Gripper Control</h1>");
}

void handleOpen() {
  openGripper();
  server.send(200, "text/html", "Gripper opened");
}

void handleClose() {
 //Complete the function
}
void setup() {
  Serial.begin(__); //Choose appropriate baud rate
  pinMode(RMotor_1, OUTPUT);
 //Configure the other pins

  myservo.attach(2);
  myservo.write(gripperClosedAngle);

  connectingToWiFi();

  server.on("/", HTTP_GET, handleRoot);
  server.on("/O", HTTP_GET, handleOpen);
  server.on("/C", HTTP_GET, handleClose);

  server.begin();
  analogWrite(REnable, 800);
  analogWrite(LEnable, 800);
}

void loop() {
  server.handleClient();
  String direction = server.arg("direction");
  String servo_clamp = server.arg("servo_clamp");

  if (!direction.isEmpty()) {
    if (direction.equals("F")) move_forward();
   //Complete the code for other movements accordingly 
  }

  if (!servo_clamp.isEmpty()) {
    if (servo_clamp.equals("/O")) open_grabbing_arm();
    else if (servo_clamp.equals("/C")) close_grabbing_arm();
    else Serial.println("Unknown gripper command");
  }
}

void move_forward() {
  digitalWrite(RMotor_1, LOW);
  digitalWrite(RMotor_2, HIGH);
  digitalWrite(LMotor_1, HIGH);
  digitalWrite(LMotor_2, LOW);
}

void move_backward() {
 //Complete the function
}

void turn_right() {
  //Complete the function
}

void turn_left() {
  //Complete the function
}

void move_stop() {
 //Complete the function
}

void open_grabbing_arm() {
  
  int pos;

  for (pos = 0; pos <= 180; pos += 1) {  // goes from 0 degrees to 180 degrees
                                    // in steps of 1 degree
    myservo.write(pos);  // tell servo to go to position in variable 'pos'
    delay(15);           // waits 15ms for the servo to reach the position
  }
  delay(1000);
}

void close_grabbing_arm() {
//Complete the function
  }
}

void openGripper()
{
  myservo.write(gripperOpenAngle);
  digitalWrite(grabPin, HIGH);
	delay(1000);
}

void closeGripper()
{
  //Write the code for closing the gripper
}
