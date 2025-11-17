#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <MFRC522.h>

const int RST1 = 22;
const int RST2 = 25;
const int Reader1 = 21;
const int Reader2 = 26;

int val1 = 0;
int val2 = 0;

// WLAN im SSTS Labor
const char *ssid ="LAPTOP_LUCA 7010";
const char *password ="7@gP8722";

const char *broker ="141.72.191.235";
const char *topic ="hello";
const int port = 1883;

// leer lassen fuer kein username und kein password (STTS Labor)
const char *username ="";
const char *mqtt_password ="";

WiFiClient espClient;
PubSubClient client(espClient);

MFRC522 rfid1(Reader1, RST1);
MFRC522 rfid2(Reader2, RST2);

MFRC522::MIFARE_Key key;

void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
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
  Serial.println("Hallo");
}

void loop() {
  // put your main code here, to run repeatedly:
  client.loop();
  if (! rfid1.PICC_IsNewCardPresent() && ! rfid2.PICC_IsNewCardPresent())
  {
    return;
  } 
  else if (rfid1.PICC_ReadCardSerial() != 0)
  {
    Serial.print(F("Card UID 1:"));
    dump_byte_array(rfid1.uid.uidByte, rfid1.uid.size);
    Serial.println();
  }
  else if (rfid2.PICC_ReadCardSerial() != 0)
  {
     Serial.print(F("Card UID 2:"));
    dump_byte_array(rfid2.uid.uidByte, rfid2.uid.size);
    Serial.println();
  }
  
  val1 = 0;
  val2 = 0;
}

// put function definitions here:
