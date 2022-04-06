# Concepção

Acesso rápido:
  - [Início](https://github.com/JoaoMario109/projeto-integrador-2)
  - [Design/Projeto](./design.md)
  - [Implementação](./implement.md)
  - [Operação](./operate.md)

<p>
O projeto visa o desenvolvimento de um sistema de automação de tarefas residenciais que atendam aos requisítos do cliente, implementando todas as necessidades e estabelecendo um sistema final de baixo custo, fácil utilização e manutenção bem como visando o conforto e praticidade gerada pelo sistema final.
</p>
<p>
Cada participante da disciplina irá desenvolver o projteto em torno de uma maquete que terá por objetivo apresentar de maneira simplificada o funcionamento do sistema simulando sua operação em um ambiente de produção.
</p>
<hr>

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
      <li>Ultrasônico HC-SR04</li>
    </ul>
  </li>
  <li>Módulos:
    <ul>
      <li>Sensor de Umidade/Nível Água Chuva</li>
      <li>Relé 5 V e um Canal</li>
      <li>Matriz de LED 8×8 com MAX7219</li>
    </ul>
  </li>
  <li>Micro Servo SG92R 9g TowerPro</li>
  <li>Display LCD 16×2 I2C Backlight Azul</li>
  <li>Buzzer Passivo</li>
</ul>

<hr>

## Descrição geral de tarefas
<ul>
  <li>Monitoramento:
    <ul>
      <li>Umidade e temperatura de um jardim</li>
      <li>Vazamentos de gás no ambiente residencial</li>
      <li>Disparo de alarme em situação de risco</li>
      <li>Permitir que o usuário configure os parâmetros do sistema</li>
    </ul>
  </li>
  <li>Controle:
    <ul>
      <li>Abertura e fechamento de janela para ventilação</li>
      <li>Monitoramento da temperatura e umidade de algum jardim</li>
      <li>Monitoramento de vazamento de gás em ambiente residencial</li>
    </ul>
  </li>
  <li>Ações:
    <ul>
      <li>Disparo de alarme utilizando o buzzer em situações consideradas de risco</li>
      <li>Caso identificado foco de fumaça verifica se há pessoa no ambiente para fechar ou abrir a janela</li>
      <li>No caso de alguém se aproximar de um ambiente monitorado com risco dispara o buzzer</li>
      <li>No caso de vazamento de gás detectado utiliza o servo para para abrir a janela do ambiente</li>
      <li>Aciona o relé para iniciar a rega automática de algum jardim</li>
    </ul>
  </li>
  <li>Visualização:
    <ul>
      <li>Informar situação interna do sistema através de um display LCD</li>
      <li>Fornecer uma interface rápida utilizando a matriz de LEDs 8x8</li>
      <li>Fornecer padrões sonoros utilizando o buzzer para informar possíveis perigos</li>
      <li>Utiliza o sensor ultrasônico para ligar ou desligar as interfaces do sistema</li>
    </ul>
  </li>
</ul>

<hr>

### Objetivação Prévia do Projeto

<li>Sistema para monitoramento do jardim</li>
<p>
  Séra desenvolvido um sistema responsável por realizar o controle da rega e dos parâmetros de um jardim
  para isso será utilizado os sensores de temperatura e umidade para realizar as medições dos parâmetros
  do solo onde o jardim se encontra, utilizando as informações obtidas no solo será realizado o controle
  da rega do jardim, evidenciando o fato de que o sistema utilizará os dados de temperatura também para
  auxiliar a decidir a quantidade correta de água a ser utilizada durante a rega, dessa maneira será 
  possível manter o jardim saudável e economizar na utilização de água.
</p>

<li>Sistema para controle de vazamento de gás</li>
<p>
  Será desenvolvido um sistema para controle de vazamentos de gás no ambiente residencial, assim será utilizado 
  o sensor de gás em conjunto com o sensor de presença e o buzzer para gerar alertas sonoros e para realizar a
  abertura das janelas do ambiente no caso de um vazamento de gás detectado.
</p>

<li>Sistema para controle de incêndios</li>
<p>
  No caso de algum incêndio detectado um sistema trabalhará em conjunto com o sensor de fumaça e presença para
  decidir se as janelas do ambiente devem ser abertas para ventilação ou se devem serem fechadas para evitar maior
  fluxo de ar.
</p>

<li>Sistema de alarmes</li>
<p>
  Quando o sistema de alarme estiver acionado se alguma pessoa for detectada como um invasor um alarme sonoro será disparado indicando
  o proprietário de alguma invasão no ambiente residencial.
</p>

<li>Interface</li>
<p>
  Será desenvolvida uma interface para permitir que o usuário visualize os parâmetros internos do sistema e que
  este possa ter uma visão rápida do funcionamento deste, o sistema também contará com um sensor ultrassônico para
  saber quando ligar ou desligar as interfaces, economizando assim o consumo de energia.
</p>
