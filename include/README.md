# Pasta `include/`

A pasta `include/` contém os arquivos de **declaração** do projeto, ou seja, os arquivos de cabeçalho (`.h`).

Esses arquivos definem:
- classes
- métodos
- interfaces públicas
- constantes
- configurações globais

Em outras palavras, esta pasta descreve **o que existe no sistema**, enquanto a pasta `src/` descreve **como isso funciona internamente**.

---

## Estrutura da pasta

### `config/`
Contém arquivos de configuração geral do sistema.

#### `pins.h`
Responsável por centralizar os pinos utilizados pelos módulos do projeto, como:
- barramento I2C do RTC
- pino do DHT
- pinos SPI do display GC9A01

Esse arquivo evita que os pinos fiquem espalhados pelo código.

---

### `drivers/`
Contém os módulos que fazem a comunicação direta com os componentes físicos do hardware.

#### `rtc_manager.h`
Define a interface do módulo responsável por:
- inicializar o RTC
- consultar hora e data atuais
- ajustar o relógio quando necessário

#### `dht_sensor.h`
Define a interface do módulo responsável por:
- inicializar o sensor DHT
- ler a temperatura

#### `gc9a01_display.h`
Define a interface do módulo responsável por:
- inicializar o display GC9A01
- limpar a tela
- exibir textos
- desenhar elementos simples de interface

---

### `services/`
Contém arquivos voltados à lógica de organização do sistema, sem falar diretamente com o hardware bruto.

#### `display_service.h`
Define a interface do serviço responsável por:
- organizar o conteúdo visual mostrado na tela
- montar a tela principal do sistema
- posicionar textos como hora e temperatura

---

## Papel da pasta `include/`
A pasta `include/` existe para deixar o projeto mais organizado e modular.

Com isso:
- outros arquivos podem reutilizar módulos com clareza
- a manutenção fica mais simples
- o sistema ganha melhor separação de responsabilidades
- a estrutura fica mais profissional e escalável

## Resumo
- `include/` = declarações
- `.h` = contratos/interfaces
- define **o que o projeto possui**