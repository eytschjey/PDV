#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <MFRC522.h>

const int RST1 = 22;
const int RST2 = 25;
const int Reader1 = 21;
const int Reader2 = 26;

const int LED2_1 = 32;
const int LED2_2 = 33;
const int LED3_1 = 4;
const int LED3_2 = 2;

long Timeout = 500;
long Timer = 0;
int state = 0;

String r1;
String r2;


String topic1 = "";
String topic2 = "";

// WLAN im SSTS Labor
const char *ssid ="LAPTOP_LUCA 7010";
const char *password ="7@gP8722";

const char *broker ="141.72.191.235";
const int port = 1883;

// leer lassen fuer kein username und kein password (STTS Labor)
const char *username ="";
const char *mqtt_password ="";

WiFiClient espClient;
PubSubClient client(espClient);

MFRC522 rfid1(Reader1, RST1);
MFRC522 rfid2(Reader2, RST2);

MFRC522::MIFARE_Key key;


String write_byte_array(byte *buffer, byte bufferSize)
{
  String r = "";
  for (byte i = 0; i < bufferSize; i++)
  {

    r += String(buffer[i] < 0x10 ? " 0" : " ");
    r += String(buffer[i], HEX);
  }
  return r;
}

void connection_loss()
{
  while(WiFi.status() != WL_CONNECTED || !client.connected())
  {
    if (millis() >= Timeout + Timer)
    {
      Timer = millis();
      if (state == 0) state = 1;
      else if (state == 1) state = 0;
      if (state == 0)
      {
        digitalWrite(LED2_1,HIGH);
        digitalWrite(LED3_1,HIGH);
        digitalWrite(LED2_2,LOW);
        digitalWrite(LED3_2,LOW);
      }
      else
      {
        digitalWrite(LED2_2,HIGH);
        digitalWrite(LED3_2,HIGH);
        digitalWrite(LED2_1,LOW);
        digitalWrite(LED3_1,LOW);
      }
    }
    Serial.println("Reconnecting...");
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    client.connect(client_id.c_str(),username,password,"ESP32_[K]/Online",0,true,"Offline");
  }
  digitalWrite(LED2_2,HIGH);
  digitalWrite(LED3_2,HIGH);
  digitalWrite(LED2_1,LOW);
  digitalWrite(LED3_1,LOW);
}
// put function declarations here:

void setup() {
  // put your setup code here, to run once:
  // WLAN Verbindung aufbauen
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  SPI.begin();
  rfid1.PCD_Init();
  rfid2.PCD_Init();

  pinMode(LED2_1,OUTPUT);
  pinMode(LED2_2,OUTPUT);
  pinMode(LED3_1,OUTPUT);
  pinMode(LED3_2,OUTPUT);

  digitalWrite(LED2_1,HIGH);
  digitalWrite(LED3_1,HIGH);
  digitalWrite(LED2_2,LOW);
  digitalWrite(LED3_2,LOW);

  int stat = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
    stat ++;
    if (stat == 20) connection_loss();
  }
  Serial.println("Connected to the WiFi network");

  // MQTT Verbindung aufbauen
  client.setServer(broker, port);
  int brok = 0;
  while (!client.connected())
  {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to broker \n",client_id.c_str());
    if (client.connect(client_id.c_str(),username,password,"ESP32_[K]/Online",0,true,"Offline"))
    {
      Serial.println("broker connected");
    }
    else 
    {
      Serial.print("failed with state");
      Serial.print(client.state());
      delay(2000);
    }
    brok ++;
    if (brok == 10) connection_loss();
  }
  client.publish("ESP32_[K]/Online", "Online");
  digitalWrite(LED2_2,HIGH);
  digitalWrite(LED3_2,HIGH);
  digitalWrite(LED2_1,LOW);
  digitalWrite(LED3_1,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  client.loop();
  if (WiFi.status() != WL_CONNECTED || !client.connected()) connection_loss();
  if (! rfid1.PICC_IsNewCardPresent() && ! rfid2.PICC_IsNewCardPresent())
  {
    return;
  } 
  else if (rfid1.PICC_ReadCardSerial() != 0)
  {
    r1 = write_byte_array(rfid1.uid.uidByte, rfid1.uid.size);
    Serial.print(F("Card UID 1:"));
    Serial.println(r1);
    topic1 = "ESP32_[K]/RFID[1]/";
    topic1 += r1;
    client.publish(topic1.c_str(), r1.c_str());
    rfid1.PICC_HaltA();
    rfid1.PCD_StopCrypto1();
  }
  else if (rfid2.PICC_ReadCardSerial() != 0)
  {
    r2 = write_byte_array(rfid2.uid.uidByte, rfid2.uid.size);
    Serial.print(F("Card UID 2:"));
    Serial.println(r2);
    topic2 = "ESP32_[K]/RFID[2]/";
    topic2 += r2;
    client.publish(topic2.c_str(), r2.c_str());
    rfid1.PICC_HaltA();
    rfid1.PCD_StopCrypto1();
  }

}
