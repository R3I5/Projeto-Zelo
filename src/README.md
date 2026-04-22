# Pasta `src/`

A pasta `src/` contém os arquivos de **implementação** do projeto, ou seja, os arquivos `.cpp`.

Enquanto a pasta `include/` declara as estruturas e interfaces do sistema, a pasta `src/` contém a lógica real de funcionamento de cada módulo.

Em outras palavras:
- `include/` diz **o que existe**
- `src/` mostra **como funciona**

---

## Estrutura da pasta

### `main.cpp`
É o ponto de entrada do sistema.

Esse arquivo é responsável por:
- iniciar a comunicação serial
- inicializar os barramentos de comunicação
- inicializar os módulos do sistema
- coordenar a execução principal no `setup()` e no `loop()`

Atualmente, ele:
- inicia o RTC
- inicia o sensor DHT
- inicia o display GC9A01
- lê hora e temperatura continuamente
- envia esses dados para exibição na tela e no serial

---

### `drivers/`
Contém a implementação dos módulos que interagem diretamente com o hardware.

#### `rtc_manager.cpp`
Implementa a lógica de:
- inicialização do RTC
- verificação de perda de energia
- leitura de data e hora
- ajuste automático do relógio

#### `dht_sensor.cpp`
Implementa a lógica de:
- inicialização do sensor DHT
- leitura da temperatura

#### `gc9a01_display.cpp`
Implementa a lógica de:
- inicialização do display GC9A01
- configuração de rotação
- limpeza de tela
- exibição de texto
- desenho de elementos gráficos simples

---

### `services/`
Contém a implementação da lógica de mais alto nível do sistema.

#### `display_service.cpp`
Implementa a organização da interface visual do sistema, sendo responsável por:
- montar a tela principal
- mostrar o título do projeto
- exibir a hora atual
- exibir a temperatura lida pelo sensor

Esse arquivo ajuda a separar:
- a lógica de exibição
- da lógica de comunicação com o display

---

## Papel da pasta `src/`
A pasta `src/` concentra a implementação prática dos módulos do projeto.

Essa separação ajuda a:
- manter o `main.cpp` mais limpo
- evitar código excessivamente acoplado
- facilitar manutenção
- preparar o projeto para crescer com novas funcionalidades

## Resumo
- `src/` = implementações
- `.cpp` = lógica/comportamento
- define **como o projeto funciona**