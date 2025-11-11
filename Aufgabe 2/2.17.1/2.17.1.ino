#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid ="";
const char *password ="";

const char *broker ="";
const char *topic ="";
const char *username ="";
const char *mqtt_password ="";
const int port = 8883;
const int Taster1 = 36;
int time1 = 0;
int time2 = 0;
int buttonState = 0;
int lastButtonState = 0;
long pressTime = 0;
long releaseTime = 0;
long duration = 0;
long Timeout = 500;
long Timer = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  client.setServer(broker, port);
  while (!client.connected())
  {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to broker \n",client_id.c_str());
    if (client.connect(client_id.c_str(),username,password))
    {
      Serial.println("broker connected");
    }
    else 
    {
      Serial.print("failed with state");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(36);
  time1 = 0;
  if (buttonState != lastButtonState)
  {
    if (buttonState == 0)
    {
      pressTime = millis();
    }
    else
    {
      releaseTime = millis();
      duration = releaseTime - pressTime;
    }
    lastButtonState = buttonState;
  }
  while (buttonState == lastButtonState)
  {
    if (pressTime <= 100)
    {
      client.publish(topic,"Hello STTS World");
    }
    else
    {
      if (millis() >= Timeout + Timer)
      {
        Timer = millis();
        client.publish(topic,"Hello STTS World");
      }
    }
    buttonState = digitalRead(36);
  }
}
