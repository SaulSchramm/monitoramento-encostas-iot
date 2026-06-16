# monitoramento-encostas-iot
Projeto prático de IoT para monitoramento de encostas - ODS 11 - Mackenzie

# 🌍 Sistema IoT para Monitoramento Preventivo de Encostas (ODS 11)

Este repositório contém a arquitetura de software de um **sistema IoT híbrido** voltado para o monitoramento em tempo real da estabilidade estrutural de solos em encostas urbanas. O projeto foi desenvolvido como atividade prática da disciplina de Internet das Coisas da **Universidade Presbiteriana Mackenzie**, alinhando-se à meta 11.5 do ODS 11 (Cidades e Comunidades Sustentáveis).

O sistema mimetiza o comportamento de um hardware homólogo (microcontrolador **ESP32** + sensor **MPU-6050**), realizando a ingestão de telemetria angular, transmissão em nuvem via **protocolo MQTT** (porta 1883) e acionamento dinâmico de alertas visuais baseados em um algoritmo analítico de risco em JavaScript.

---

## 🛠️ Tecnologias Utilizadas

*   **Node-RED** (v5.0.0) — Orquestração de fluxos e lógica de backend.
*   **Node-RED Dashboard** (`@flowfuse/node-red-dashboard`) — Interface gráfica do usuário (UI).
*   **Protocolo MQTT** — Comunicação leve e assíncrona baseada na arquitetura Publish/Subscribe.
*   **Broker MQTT Público** (`broker.mqtt-dashboard.com`) — Servidor de mensageria em nuvem.

---

## 🚀 Como Importar e Executar o Projeto

Para rodar este fluxo no seu ambiente local do Node-RED, siga os passos abaixo:

1.  **Instale as dependências da interface:**
    No menu lateral do seu Node-RED, vá em `Gerenciar Paleta` (Manage Palette) > aba `Instalar` e pesquise por `@flowfuse/node-red-dashboard`. Instale o pacote.
2.  **Baixe o código do fluxo:**
    Faça o download do arquivo `.json` disponível neste repositório.
3.  **Importe no Node-RED:**
    Clique no menu superior direito do Node-RED, selecione `Importar` (Import), cole o conteúdo do arquivo JSON ou selecione o arquivo baixado e clique em **Importar**.
4.  **Execute o sistema:**
    Clique no botão vermelho **Deploy** no canto superior direito para ativar os fluxos.
5.  **Acesse o Dashboard:**
    Abra o seu navegador e acesse a interface gráfica através do endereço: `http://127.0.0.1:1880/dashboard`.

---

## 📊 Regras de Negócio do Algoritmo
O nó de função processa a inclinação recebida e atualiza o estado do atuador visual conforme os limites estabelecidos:
*   🟢 **Menor que 5°:** Estado NORMAL.
*   🟡 **Entre 5° e 12°:** Estado de ATENÇÃO (Mudança do painel para amarelo).
*   🔴 **Maior que 12°:** Estado de PERIGO CRÍTICO (Mudança do painel para vermelho).

---

## 📝 Autor e Orientação
*   **Aluno:** Saul Soares Schramm (RA: 10441619)
*   **Instituição:** Universidade Presbiteriana Mackenzie — Polo Santos (ADS)
*   **Orientador:** Prof. Andre Luis de Oliveira
