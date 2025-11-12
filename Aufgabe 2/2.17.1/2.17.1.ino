// Aufgabe 2.17.1: MQTT Nachricht bei Tastendruck senden
#include <WiFi.h>
#include <PubSubClient.h>

// WLAN im SSTS Labor
const char *ssid ="ITBahn";
const char *password ="geheim007";

const char *broker ="141.72.191.235";
const char *topic ="hello";
const int port = 1883;

// leer lassen fuer kein username und kein password (STTS Labor)
const char *username ="";
const char *mqtt_password ="";

// Initialisierung von Variablen
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
  // WLAN Verbindung aufbauen
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  // MQTT Verbindung aufbauen
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
  // Taster 1 als Input
  pinMode(Taster1,INPUT);
}

void loop() {
  // Messung des Tasterzustands an Pin 36
  buttonState = digitalRead(36);
  time1 = 0;

  // Messung von Druckdauer und Intervall
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

  // Sende MQTT Nachricht bei Tastendruck
  while (buttonState == lastButtonState)
  {
    // Kurz- und gedrückt unterscheiden
    if (pressTime <= 100)
    {
      client.publish(topic,"Hello STTS World");
    }
    // Bei gedrücktem Taster alle 500ms Nachricht senden
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
