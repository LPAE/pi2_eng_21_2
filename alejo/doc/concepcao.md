# Concepção do projeto

Acesso rápido:
  - [Introdução](../README.md)
  - [Design/Projeto](./design.md)
  - [Implementação](./implementacao.md)
  - [Operação](./operacao.md)


Este projeto visa a implementação de um sistema de automação residencial, que facilite e automatize tarefas que o cliente requisite, visando a praticidade e baixo custo. Por fins didáticos, uma maquete que será desenvolvida por cada aluno será implementada. 

---

### Materiais Utilizados 
<ul>
  <li>Controlador:
    <ul>
      <li>Placa MEGA 2560 R3 + Fonte + Cabo USB para Arduino</li>
    </ul>
  </li>
  <li>Sensores:
    <ul>
      <li>Umidade e Temperatura DHT11</li>
      <li>Presença e Movimento PIR</li>
      <li>Gás MQ-2 Inflamável e Fumaça</li>
      <li>Ultrassônico HC-SR04</li>
    </ul>
  </li>
  <li>Módulos:
    <ul>
      <li>Sensor de Umidade/Nível Água Chuva</li>
      <li>Relé 5V e um Canal</li>
    </ul>
  </li>
  <li>Micro Servo SG92R 9g TowerPro</li>
  <li>Display LCD 16×2 I2C Backlight Azul</li>
  <li>Buzzer Passivo</li>
</ul>

---

### Objetivação Prévia do Projeto

<ul>
  <li>Monitoramento:
    <ul>
      <li>Umidade do solo, ambiente e temperatura no jardim</li>
      <li>Sensoriamento de vazamento de gás e fumaça</li>
      <li>Detecção de indivíduos em locais de risco (área com vazamento de gás ou incêndio)</li>
    </ul>
  </li>
  <li>Controle:
    <ul>
      <li>Automatização de janelas</li>
      <li>Automatização de bomba de água, para regamento de jardim</li>
      <li>Automatização da interface para economia de energia</li>
    </ul>
  </li>
  <li>Ações:
    <ul>
      <li>Abrir ou fechar as janelas dependendo da presença de indivíduos quando detectar um foco de incêndio</li>
      <li>Acionar bomba de regamento por meio de um relé</li>
      <li>Se algum individuo se aproximar de uma zona de perigo, acionar ou mudar o som emitido pelo buzzer</li>
      <li>Se houver vazamento de gás, abrir a janela e emitir um aviso sonoro pelo buzzer</li>
    </ul>
  </li>
  <li>Visualização:
    <ul>
      <li>Interface visual a partir do LCD, onde serão mostrados dados de interesse e se houver alguma situação de risco será informado</li>
      <li>Interface sonora a partir do buzzer, onde serão criados padrões dependendo da situação de risco</li>
      <li>Utilizar o sensor ultrassônico para detectar a presença de indivíduos para ligar ou desligar a inteface, assim economizando energia</li>
    </ul>
  </li>
</ul>


## Referências


ADMIN. **Casa inteligente: a tecnologia de Black Mirror já está o seu alcance!** Disponível em: <https://www.delmak.com.br/casa-inteligente-a-tecnologia-de-black-mirror-ja-esta-ao-seu-alcance/>. Acesso em: 23 mai. 2021.
