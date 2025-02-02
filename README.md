
---

<table>
  <tr>
    <td>
      <img src="assets/logo.jpeg" alt="Logo do Projeto" width="150">
    </td>
    <td>
      <h1>🚦 Projeto: Sistema de Temporização com Botão</h1>
    </td>
  </tr>
</table>



## 📋 Descrição Geral

Este projeto implementa um **sistema de temporização para acionamento de LEDs** utilizando o microcontrolador **Raspberry Pi Pico W** e a função `add_alarm_in_ms()` do **Pico SDK**. O sistema é acionado pelo clique em um **botão (pushbutton)**, alterando os estados dos LEDs com um atraso de **3 segundos** entre cada mudança.

O sistema também foi testado na **BitDogLab**, utilizando um **LED RGB** e o **Botão A** no **GPIO 05**.

---

## 🎯 Objetivos

- Implementar um **temporizador com alarme** usando `add_alarm_in_ms()`.
- Acionar **três LEDs individuais** após o clique no botão.
- Implementar **mudança de estado** dos LEDs com um atraso de **3 segundos**.
- Bloquear novas chamadas enquanto os LEDs ainda estão sendo desligados.
- Simular o funcionamento no **Wokwi**.
- Realizar testes na **BitDogLab** com um **LED RGB** e **Botão A (GPIO 05)**.
- Opcional: **Implementar debounce** via software para evitar acionamentos indevidos do botão.

---

## 🛠 Componentes Utilizados

- **Raspberry Pi Pico W** (Microcontrolador)
- **03 LEDs (azul, vermelho e verde)**
- **03 Resistores de 330 Ω**
- **Botão (Pushbutton)**
- **LED RGB** (BitDogLab - GPIOs 11, 12 e 13)
- **Botão A (BitDogLab - GPIO 05)**

---

## 📂 Estrutura do Projeto

```plaintext
Temporizacao/
├── assets
│   ├── logo.jpeg
│   ├── placa.gif
│   ├── wokwi.gif
├── wokwi
│   ├── diagram.json
│   ├── wokwi.toml
├── .gitignore
├── CMakeLists.txt
├── LICENSE
├── main.c
├── pico_sdk_import.cmake
└── README.md
```

---

## 🚀 Funcionalidades do Projeto

1. **Estados dos LEDs:**
   - **Clique no botão:** Todos os LEDs são acionados.
   - **Após 3 segundos:** Um LED é desligado.
   - **Após mais 3 segundos:** O segundo LED é desligado.
   - **Após mais 3 segundos:** O último LED é desligado.
   - **Novo clique no botão:** O ciclo reinicia.

2. **Temporização:**
   - Utiliza `add_alarm_in_ms()` para alternar os LEDs a cada 3 segundos.
   - Bloqueia novas chamadas enquanto os LEDs ainda estão sendo desligados.
   - Implementa debounce (opcional) para evitar acionamentos acidentais.

3. **Execução na BitDogLab:**
   - Usa o **LED RGB** nos GPIOs 11, 12 e 13.
   - Usa o **Botão A** no GPIO 05 para acionamento.

---

## 🔧 Requisitos Técnicos

- **Temporização precisa:** Uso de `add_alarm_in_ms()` para alternar os LEDs.
- **Call-back para alteração dos LEDs:** Implementação na função `turn_off_callback()`.
- **Bloqueio de acionamento:** O botão só pode ser pressionado após o desligamento do último LED.
- **Mensagens na Serial:** Impressão de status a cada mudança.
- **Código bem estruturado e comentado.**

---

## ⚙️ Instalação e Execução

### 1. Configuração do Ambiente

- Certifique-se de que o **Pico SDK** está instalado e configurado corretamente.
- Instale as dependências necessárias para compilação do código.

### 2. Clonando o Repositório

```bash
git clone https://github.com/otilianojunior/temporizador-oneshot.git
```

### 3. Compilando e Enviando o Código

```bash
mkdir build
cd build
cmake ..
make
```

### 4. Testes

- **Simulação no Wokwi:**

  - Utilize o arquivo `diagram.json` na pasta `wokwi` para testar o funcionamento.
  - Também pode ser acessado aqui [wokwi](https://wokwi.com/projects/421753405149597697)

    <p align="center">
    <img src="assets/wokwi.gif" alt="Simulação no Wokwi">
  </p>

- **Execução na placa BitDogLab:**

  - Copie o arquivo `.uf2` gerado para o Raspberry Pi Pico W.

    <p align="center">
    <img src="assets/placa.gif" alt="Execução na Placa RP2040 - BitDogLab">
  </p>

> _Observação:_ No ambiente BitDogLab, o GPIO 11 controla o LED verde, o GPIO 12 controla o LED azul e o GPIO 13 controla o LED vermelho. Como se trata de um LED RGB, ao acionar os três LEDs simultaneamente, a cor resultante é branca. Quando apenas os LEDs azul e vermelho estão acesos, a cor gerada é rosa. Por fim, com apenas o LED vermelho aceso, a cor exibida é vermelha.

- **Demonstração em Vídeo:**
  > 🎥 **[Vídeo](https://drive.google.com/file/d/171Pq9wdhYspdmimEvkkvDo3fD1gmohbS/view?usp=sharing)**

---

## ✅ Conclusão

Este projeto demonstra o uso da **função de alarme** do Pico SDK para **controlar LEDs de forma temporizada**, acionados por um **botão pushbutton**. A abordagem garante que os LEDs sigam uma sequência de desligamento sem interrupção prematura.

A implementação tanto com LEDs individuais quanto com um **LED RGB** amplia a compreensão sobre manipulação de saídas digitais.

---

_Desenvolvido por Otiliano Júnior_

