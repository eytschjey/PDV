#include <WiFi.h>
#include <PubSubClient.h>

/* === CONFIG === */
const char* WIFI_SSID     = "FRITZ!Box 7590 HP";
const char* WIFI_PASSWORD = "fromage,ups!handschuh?maybe";

IPAddress MQTT_HOST_IP(192, 168, 12, 40);  // force IPv4
const uint16_t MQTT_PORT  = 1883;
const char*    MQTT_USER  = "esp32";
const char*    MQTT_PASS  = "supersicherespasswort!";   // <- your real EMQX password
const char*    CLIENT_ID  = "esp32-jan-01";             // unique per device

const char* TOPIC_STATUS  = "test/esp32/status";        // LWT + online
const char* TOPIC_UPTIME  = "test/esp32/uptime";        // heartbeat
const char* TOPIC_CMDSUB  = "test/esp32/cmd/#";         // commands
/* ============== */

WiFiClient net;
PubSubClient mqtt(net);
unsigned long lastSend = 0;

const char* mqttStateStr(int8_t s) {
  switch (s) {
    case MQTT_CONNECTION_TIMEOUT:       return "timeout";
    case MQTT_CONNECTION_LOST:          return "conn lost";
    case MQTT_CONNECT_FAILED:           return "connect failed";
    case MQTT_DISCONNECTED:             return "disconnected";
    case MQTT_CONNECTED:                return "connected";
    case MQTT_CONNECT_BAD_PROTOCOL:     return "bad protocol";
    case MQTT_CONNECT_BAD_CLIENT_ID:    return "bad client id";
    case MQTT_CONNECT_UNAVAILABLE:      return "server unavailable";
    case MQTT_CONNECT_BAD_CREDENTIALS:  return "bad credentials";
    case MQTT_CONNECT_UNAUTHORIZED:     return "unauthorized";
    default:                            return "unknown";
  }
}

void onMessage(char* topic, byte* payload, unsigned int len) {
  Serial.printf("[MQTT] %s: ", topic);
  for (unsigned int i = 0; i < len; i++) Serial.print((char)payload[i]);
  Serial.println();
}

bool connectMqtt() {
  Serial.print("[MQTT] connecting... ");
  bool ok = mqtt.connect(
    CLIENT_ID,
    MQTT_USER, MQTT_PASS,
    TOPIC_STATUS, 1, true, "offline",
    true
  );
  if (ok) {
    Serial.println("OK");
    mqtt.publish(TOPIC_STATUS, "online", true);
    mqtt.subscribe(TOPIC_CMDSUB, 1);
  } else {
    Serial.printf("FAIL (%d: %s)\n", mqtt.state(), mqttStateStr(mqtt.state()));
  }
  return ok;
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.printf("[WiFi] Connecting to %s", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) { delay(300); Serial.print("."); }
  Serial.printf("\n[WiFi] IP: %s\n", WiFi.localIP().toString().c_str());

  mqtt.setServer(MQTT_HOST_IP, MQTT_PORT);  // IPAddress => IPv4 socket
  mqtt.setCallback(onMessage);
}

void loop() {
  if (!mqtt.connected()) {
    static unsigned long nextRetry = 0;
    static uint8_t backoff = 2;
    unsigned long now = millis();
    if (now >= nextRetry) {
      connectMqtt();
      nextRetry = now + backoff * 1000UL;
      if (backoff < 30) backoff *= 2;
    }
    delay(10);
    return;
  }

  mqtt.loop();

  if (millis() - lastSend > 5000) {
    lastSend = millis();
    mqtt.publish(TOPIC_UPTIME, "tick", false);
  }
}
