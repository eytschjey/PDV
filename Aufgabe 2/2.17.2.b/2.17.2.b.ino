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
const int Taster2 = 39;
const int Taster3 = 34;
const int LED1_1 = 21;
const int LED1_2 = 26;
const int LED2_1 = 32;
const int LED2_2 = 33;
const int LED3_1 = 4;
const int LED3_2 = 2;
int state1 = 0;
int state2 = 0;
int state3 = 0;
int stateLED = 0;
int val1 = 0;
int val2 = 0;
int val3 = 0;
int used1 = 0;
int used2 = 0;
int used3 = 0;
int anzahl = 0;
int failed = 0;
long Timeout = 250;
long Timer = 0;
String Taster;

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
  pinMode(Taster1,INPUT);
  pinMode(Taster2,INPUT);
  pinMode(Taster3,INPUT);
  pinMode(LED1_1,OUTPUT);
  pinMode(LED1_2,OUTPUT);
  pinMode(LED2_1,OUTPUT);
  pinMode(LED2_2,OUTPUT);
  pinMode(LED3_1,OUTPUT);
  pinMode(LED3_2,OUTPUT);
  digitalWrite(LED1_2,LOW);
  digitalWrite(LED2_2,LOW);
  digitalWrite(LED3_2,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i<3; i++)
  {
    Taster = " ";
  }
  state1 = val1;
  state2 = val2;
  state3 = val3;
  val1 = digitalRead(Taster1);
  val2 = digitalRead(Taster2);
  val3 = digitalRead(Taster3);
  anzahl = val1 + val2 +val3;
  if (state1 != val1)
  {
    if(client.publish(topic,"Gruppe K") != 1)
    {
      failed++;
    }
    used1 = 1;
  }
  if (state2 != val2)
  {
    if(client.publish(topic,String(anzahl).c_str()) != 1)
    {
      failed++;
    }
    used2 = 1;
  }
  if (state3 != val3)
  {
    if(val1 == 1)
    {
      Taster += String(" T1 ");
      if(val2 == 1)
      {
        Taster += String(" T2 ");
        if(val2 == 1)
        {
          Taster += String(" T3 ");
        }
      } 
      else if(val3 == 1)
      {
        Taster += String(" T3 ");
      }
    }
    else if(val2 == 1)
    {
      Taster += String(" T2 ");
      if(val3 == 1)
      {
        Taster += String(" T3 ");
      }
    }
    else if(val3 == 1)
    {
      Taster += String(" T3 ");
    }
    if(client.publish(topic,Taster.c_str()) != 1)
    {
      failed++;
    }
    used3 = 1;
  }
  if(used1 == 1 || used2 == 1 || used3 == 1)
  {
    delay(2000);
    if (used1 == 1)
    {
      if(client.publish(topic,"Gruppe K") != 1)
      {
        failed++;
      }
      used1 = 0;
    }
    if (used2 == 1)
    {
      if(client.publish(topic,String(anzahl).c_str()) !=1)
      {
        failed++;
      }
      used2 == 0;
    }
    if (used3 == 1)
    {
      if(client.publish(topic,Taster.c_str()) != 1)
      {
        failed++;
      }
      used3 == 0;
    }
  }
  if (failed != 0)
  {
    while(1)
    {
      if (millis() >= Timeout + Timer)
      {
        Timer = millis();
        if (stateLED = LOW) stateLED = HIGH;
        else stateLED = LOW;
        digitalWrite(LED1_1,stateLED);
        digitalWrite(LED2_1,stateLED);
        digitalWrite(LED3_1,stateLED);
      }
    }
  }
  
}
