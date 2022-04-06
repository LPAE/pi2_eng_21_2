# Concepção do Projeto: <h1>
  
## Requisitos <h2>
  Realizar um projeto de Domótica para uma casa, automatizando diversos processos, como ligar luzes dos cômodos atrávez da incidência solar externa, monitorar se há vazamento de gás, verificar quantidade de água na captação de água da chuva e abrir o portão da garagem de forma inteligente, e para facilitar ainda mais a vida dos moradores, eles disponibilizarão de uma interface intuitiva para interacao em seu Notebook. 
  
### Componentes que serão utilizados: <h3>
 
 - Placa MEGA 2560 R3 + Fonte + Cabo USB para Arduino
 - Sensor Fotoresistor LDR de 5mm 
 - Sensor de presença e movimento PIR
 - Sensor de gás MQ-2 inflamável e fumaça
 - Micro Servo SG92R 9g TowerPro
 - Módulo Sensor de Umidade/Nível Água Chuva
 - Buzzer passivo
 - Display LCD 16×2 I2C Backlight Azul
  
## Objetivo <h2>
  Os Objetivos são: 
  - Realizar uma maquete semelhante aos exemplos abaixo;
  - Portão inteligente: quando o carro chegar perto do portão, ele abrirá automaticamente, sem a necessidade de apertar o botão, depois que o carro passar, será nescessário fechar o portão por um comando.
  - Monitorar Luminosidade externa: Quando houver bastante luminosidade externa não é necessário a utilização de muitas luzes dentro de casa, então as luzes de casa serão desligadas. O sensor fotoresistor ficará fora de casa monitorando a luminosidade, quanto não houver luminosidade suficiente na parte externa, as luzes da casa ligarão.
  - Receber notificações caso haja vazamento de gás: quando o sensor de gas detectar gas por mais de 5 segundos soará um alarme e a porta mais proxima do gás será aberta, aparecendo uma mensagem "vazamento de gás, abra as janelas, não ligue luzes, desligue o gás".
  - Armazenamento da água da chuva: quando o nível da água da chuva estiver em um terço da capacidade, aparecerá uma mensagem no Display/Notebook "Baixo nível de água da chuva, economize água". 

### Modelo para maquete <h3>
  Abaixo temos um modelo de Casa que servirá de inspriração para maquete:
  
![Modelo Casa](https://github.com/ElisaAnes/Projeto-Domotica/blob/main/Plantas-de-Casas-de-Dois-Andares%20(1).jpg)
  <br />
  
### Modelo Planta Baixa da Maquete <h3>
  Abaixo temos a planta da maquete que será de dois andares
  
![Planta Baixa](https://github.com/ElisaAnes/Projeto-Domotica/blob/main/Plantas-de-Casas-de-Dois-Andares.jpg)
  
  #### Referências <h4>
  MUNDO DAS TRIBOS. Planta de Casas de dois andares. Disponível em: https://www.mundodastribos.com/plantas-de-casas-de-dois-andares.html . Acesso em: 6 nov. 2021.
