## Implementação

  Nos passos anteriores, foram idealizadas e em seguida planejadas todas as funcionalidades para aplicar a domótica em uma maquete e nessa etapa de implementação é o momento de colocar em prática o que foi projetado. A seguir, serão descritos os processos de fabricação da maquete, codificação, teste e validação de cada tarefa do sistema e integração do todo para obtenção dos resultados desejados.

### Construção da maquete

  Na etapa de concepção foi apresentado a planta baixa da maquete a ser implementada no projeto, baseando na planta baixa foi desenvolvido a maquete utilizando caixas de papelão para contrução das paredes e portas, e utilizando tinta spray para pintar.
  #### A imagem abaixo mostra como a maquete era antes de pintar:
  ![Maquete sem tinta](https://user-images.githubusercontent.com/72568537/156429538-3743e850-7c90-4375-ba5a-2b2e74c135a1.jpeg)
  
  #### A imagem abaixo mostra como ficou a maquete após a pintura:
![maquete pintada](https://user-images.githubusercontent.com/72568537/156429550-4a94f519-d120-4ddd-b549-db0ae4d6687f.jpeg)

  
### Testes com o sensores

  De acordo com o que foi planejado na etapa de concepção, foi realizado testes individuais com os componentes para atestar que todos estão em funcionando e realizar a integração dos mesmos.
  O código será implementado em forma de tarefas, onde cada tarefa terá um tempo, para assim ficar realizando um loop, e entregando o resultado dos sensores.
  
### Sobre o código

O código foi desenvolvido em forma de tarefas, cada uma realizada em um determinado tempo, para que tudo funcione da forma correta, as tarerefas criadas foram:

tarefa_temperatura : Essa tarefa é executada a cada 1s, fazendo a leitura da temperatura e da umidade, assim que a temperatura é igual ou superior a 25 graus, a tarefa irá ativar o relé e ligar o ventilador instalado no quarto, e irá emitir um aviso no LCD presente na sala informando que o ventilador está ligado e o valor da temperatura;

tarefa_GAS : Essa tarefa é executada a cada 2s, fazendo a leitura dos níveis de gases e fumaças presentes na cozinha, assim que o valor coletado pelo sensor ultrapassar o limite estipulado ele ativa o relé para ligar o exaustor e emite um sinal sonoro atravez do buzzer instalado na cozinha;

tarefa_AGUA : Essa tarefa é executada a cada 5s, realiza a leituras se a presença de agua, e juntamente com o valor de umidade assim que tiver a presença de agua e o valor de umidade a baixo de 90%, ela emite um aviso no LCD para regar as plantas e indica o valor de umidade;

tarefa_PIR : Essa tarefa é executada a cada 1s, onde faz a leitura se há presença ou não, se houver presença ela irá acender uma matriz de led com a letra (X), para iluminar quem tenha ativado o sensor com a presença, caso não haja presença a tarefa não irá realizar nada;

tarefa_ULTRASONIC : Essa tarefa é executada a cada 0,5s, ela irá fazer a leitura da distancia até a porta, assim que a distancia for menor que 9cm, ela irá abrir a porta, e logo após a distancia aumentar ela irá fechar a porta.


Por fim, os componentes foram dispostos nos seus devidos lugares na maquete e foram realizados diversos testes para validação do projeto. A seguir, estão listados alguns dos testes aplicados:

* Ativar os sistemas de cada sensor, individualmente e em conjunto.
* Liberar gás com um maçarico para acionar o sensor de gás.
* Modificar a temperatura de acionamento do ventilador para a temperatura do ambiente.
* Fazer o sensor pir detectar presença e ativar a matriz de led.
* Checar o display LCD e verificar se as informações estão corretas.
* Abrir e fechar o portão. 

### A imagem abaixo mostra a maquete quase pronta:
![Maquete quase pronta](https://user-images.githubusercontent.com/72568537/156430010-4cbf1cd7-67d0-41f3-9367-e6a8e78099ac.jpeg)

Por meio destas ações foi possível concluir que todo o sistema funciona corretamente, cumprindo com o que foi planejado nas etapas anteriores de concepção e design.

