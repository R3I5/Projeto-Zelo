# 🏥 Projeto Zelo
> Sistema Ciberfísico para Gestão Terapêutica e Monitoramento de Idosos.

---

## 📝 Descrição do Projeto
O **Projeto Zelo** é um dispositivo inteligente baseado no ESP32 projetado para mitigar os riscos de esquecimento ou dosagem incorreta de medicamentos em populações idosas. O sistema funciona como um assistente físico e digital, emitindo alertas sonoros e visuais personalizados para cada paciente.

A solução integra hardware de baixo custo com uma interface web robusta, permitindo que familiares e profissionais de saúde gerenciem prescrições e monitorem a aderência ao tratamento em tempo real.

## 🚀 Justificativa de Performance e Concorrência
Diferente de sistemas de automação simples, este projeto exige:
**Baixa Latência:** Prioridade absoluta no processamento do botão de emergência para notificações instantâneas.
**Multitarefa (RTOS):** Gerenciamento paralelo entre a contagem de tempo real (RTC), interface de usuário (OLED/Botões) e comunicação de rede (Wi-Fi).
**Confiabilidade:** Persistência de dados em memória flash para operação em casos de queda de conectividade.
**Eficiência Energética:** Otimização do consumo para garantir a continuidade em situações críticas de saúde.

## 🛠️ Tecnologias Utilizadas
* **Hardware:** ESP32 (Dual-Core).
* **Firmware:** Framework Arduino / FreeRTOS.
* **Back-end:** C++.
* **Front-end:** HTML e CSS.
* **Protocolos:** HTTP / MQTT.

## 🔌 Componentes de Hardware
| Componente | Função |
| :--- | :--- |
| **ESP32** | Microcontrolador central com Wi-Fi/Bluetooth integrados. |
| **DS3231 (RTC)** | Sensor de Tempo Real para precisão cronométrica. |
| **Display OLED** | Interface visual para horários e dosagens. |
| **DFPlayer Mini** | Módulo de áudio para alertas sonoros e voz. |
| **Push-Buttons** | Interação do usuário (Confirmar, Soneca e Emergência). |



## 🏗️ Arquitetura do Sistema
1. **Input:** Cadastro de medicamentos e horários via Interface Web.
2. **Processamento:** O ESP32 sincroniza os dados, monitora o RTC e aguarda eventos de entrada.
3. **Output:** Alerta visual/sonoro no horário programado e logs de confirmação enviados para a nuvem.

## ⚠️ Riscos Técnicos
* Conflito de acesso a recursos compartilhados entre tarefas de rede e interface.
* Gerenciamento de memória RAM durante instabilidades no Wi-Fi.
* Desgaste da memória Flash por escritas excessivas de logs.

## 👥 Integrantes
* **[Nome do Integrante 1]** 
* **João Victor dos Reis** 
* **[Nome do Integrante 3]**
  
---
*Projeto desenvolvido para a disciplina de Performance em Sistemas Ciberfísicos  - PUCPR.*
