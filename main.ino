#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <ArduinoJson.h>

// Configurações de Wi-Fi (Padrão do simulador Wokwi)
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Configurações do Broker MQTT (HiveMQ Público)
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "projeto/encostas/telemetria";

WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_MPU6050 mpu;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando em ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Wi-Fi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    // Cria um ID de cliente único baseado no MAC address
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("conectado ao Broker!");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);

  // Inicializa o sensor MPU6050
  if (!mpu.begin()) {
    Serial.println("Falha ao encontrar o chip MPU6050");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 encontrado e inicializado!");

  // Configurações do sensor
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Leitura dos eventos do sensor
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Cálculo simples de inclinação em graus usando o acelerômetro
  float inclinaX = atan2(a.acceleration.y, a.acceleration.z) * 180.0 / PI;
  float inclinaY = atan2(-a.acceleration.x, sqrt(a.acceleration.y * a.acceleration.y + a.acceleration.z * a.acceleration.z)) * 180.0 / PI;

  // Criação do documento JSON para envio
  StaticJsonDocument<200> doc;
  doc["id_dispositivo"] = "ESP32-ENCOSTA-01";
  doc["inclinacao_x"] = inclinaX;
  doc["inclinacao_y"] = inclinaY;
  doc["temperatura"] = temp.temperature;

  // Verifica se o ângulo ultrapassa um limite crítico (exemplo: 15 graus)
  if (abs(inclinaX) > 15.0 || abs(inclinaY) > 15.0) {
    doc["status"] = "ALERTA_RISCO";
  } else {
    doc["status"] = "NORMAL";
  }

  char buffer[200];
  serializeJson(doc, buffer);

  // Publica no tópico MQTT
  Serial.print("Enviando dados: ");
  Serial.println(buffer);
  client.publish(mqtt_topic, buffer);

  // Aguarda 5 segundos para a próxima leitura
  delay(5000);
}
