
## Design

Aqui na parte do design será estabelecido como serão montados os componentes de onde será distribuído cada função definida anteriormente de acordo com o que foi estabelecido na concepção do projeto sendo assim será apresentado o diagrama de montagem, a planta baixa e quais componentes serão utilizados.

## Diagrama de montagem

O diagrama de montagem mostra um exemplo de como será realizada as ligações de cada tenologia utilizda para realizar o projeto, certas alterações podem ocorrer no projeto final.


![qweqwe](https://user-images.githubusercontent.com/92868328/145195751-9b7ff73f-a25e-4022-8b52-78c6e2cc6838.png)

>- ![image](https://user-images.githubusercontent.com/92868328/145211898-ef771913-f139-4e91-a114-6cbf8816e615.png) Sensor Ultrassônico, será utilizado para detectar a presença de visitas na porta de entrada da casa
>- ![image](https://user-images.githubusercontent.com/92868328/145211965-e3976a8e-f432-4ff5-a563-8a72019d141b.png) Sensor de Gás, será utilizado na cozinha para fazer a detectação de gás
>- ![image](https://user-images.githubusercontent.com/92868328/145212008-5bd0b31d-8e2d-452c-a189-2ae751b328ef.png) Sensor de Umidade, será utilizado junto com o sensor de nível de água para determinar se é necessário regar o jardim
>- ![image](https://user-images.githubusercontent.com/92868328/145212033-bd324862-caa6-4b71-b354-89d745dc228a.png) Buzzer, será utilizado como alarme tanto no sensor de gás quanto no sistema de segurança
>- ![image](https://user-images.githubusercontent.com/92868328/145212089-698ed181-e128-4981-8f93-6cd38e48ed17.png) Sensor de Presença, será utilizado para detectar a presença de um intruso na residência no sistema de segurança
>- ![image](https://user-images.githubusercontent.com/92868328/145212101-177c838d-af45-47b9-973c-a8757aac88a2.png) Servo Motor, será utilizado como "tranca" da porta de entrada
>- ![image](https://user-images.githubusercontent.com/92868328/145212164-fa3d7380-fc7e-4158-8b4d-278ca17a3643.png) Matriz de Led, será utilizado como luz da cozinha
>- ![image](https://user-images.githubusercontent.com/92868328/145212272-00f48574-cc6e-40ed-9864-83e7d4937c1e.png) Módulo Relé, será utilizado para controlar o ar condicionado
>- ![image](https://user-images.githubusercontent.com/92868328/145212302-49d8e0d8-57bf-4dcb-9f54-4fb8e938dea7.png) Fan, será utilizado para representar o ar condicionado
>- ![image](https://user-images.githubusercontent.com/92868328/145212339-92a87640-bd51-425d-952c-4cdcaac849bf.png) Sensor de Nível de Água, será utilizado com o sensor de umidade para determinar se será necessário regar o jardim
>- ![image](https://user-images.githubusercontent.com/92868328/145212354-41536d21-a369-45d0-8109-ab4b25c78703.png) LCD, será utilizado como painel de controle das função anteriormente descritas



## Planta baixa:

A imagem a seguir é planta baixa da casa que será montada e mostra como será distribuidas cada função exemplificada no projeto e onde será montada cada tecnologia

![planta baixa design pi2](https://user-images.githubusercontent.com/92868328/145198906-9bcd7558-f908-4047-88ef-d52aedd6a81d.png)


## Lista de Componentes:
Quantidade  | Tecnologias
:---------:   | ------
1           | Placa Arduino MEGA 2560 R3
1           | Sensor de Umidade e Temperatura DHT11
1           | Sensor de gás MQ-2 inflamável e fumaça
1           | Micro Servo SG92R 9g TowerPro
1           | Módulo Sensor de Umidade/Nível Água Chuva
1           | Módulo Relé 5 V e um Canal
1           | Sensor ultrasônico HC-SR04
1           | Módulo Matriz de LED 8×8 com MAX7219
1           | Display LCD 16×2 I2C 
1           | Seensor de Presença PIR 
1           | Buzzer
1           | Toggle Switch (Interruptor da Cozinha)
