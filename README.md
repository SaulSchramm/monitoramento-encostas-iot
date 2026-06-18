# Sistema IoT para Monitoramento de Estabilidade de Encostas (ODS 11)

Este projeto consiste em um protótipo de sistema IoT desenvolvido para monitorar a inclinação e estabilidade de encostas em áreas de vulnerabilidade social e geológica, alinhado à meta 11.5 dos Objetivos de Desenvolvimento Sustentável da ONU (Cidades e Comunidades Sustentáveis). O sistema detecta variações angulares críticas que precedem deslizamentos de terra e envia alertas em tempo real.

## 🛠️ Hardware e Componentes Utilizados
* **Microcontrolador:** ESP32 (módulo Wi-Fi integrado para transmissão de dados).
* **Sensor Principal:** MPU-6050 (Acelerômetro e Giroscópio de 3 eixos para medição de inclinação).
* **Protoboard e Jumpers:** Para interconexão dos componentes.

## 🔌 Diagrama de Montagem (Pinagem I2C)
As conexões físicas (ou no simulador) entre o ESP32 e o MPU-6050 seguem o padrão de comunicação I2C:

| MPU-6050 | ESP32 | Descrição |
|----------|-------|-----------|
| VCC      | 3V3   | Alimentação 3.3V |
| GND      | GND   | Terra / Comum |
| SCL      | GPIO 22 | Clock da comunicação I2C |
| SDA      | GPIO 21 | Dados da comunicação I2C |

## 🌐 Protocolo de Comunicação e Broker MQTT
Os dados de telemetria coletados são estruturados em formato **JSON** e publicados via protocolo **MQTT**, garantindo leveza e agilidade no envio das informações.
* **Broker Utilizado:** HiveMQ Public Broker (`broker.hivemq.com`)
* **Porta:** 1883 (TCP padrão)
* **Tópico de Publicação:** `projeto/encostas/telemetria`

### Exemplo de Payload JSON Enviado:
```json
{
  "id_dispositivo": "ESP32-ENCOSTA-01",
  "inclinacao_x": 2.45,
  "inclinacao_y": -1.12,
  "temperatura": 26.50,
  "status": "NORMAL"
}
