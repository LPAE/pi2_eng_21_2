# Operação

Tanto nesta etapa do projeto quanto na etapa de implementação, percebeu-se que alguns objetivos do projeto não eram realizáveis. Desta maneira, algumas alterações foram realizadas:

- O sistema de irrigação não foi realizado pois o sensor DHT11 não é próprio para isso. O sensor YL-69 foi adquirido para realizar esta função em projetos futuros.

# Funções Implementadas

- Sistema de Detecção de Gás: O sensor MQ-2 foi utilizado para medir o gás, exibe-se "A" (alto), "M" (médio) e "B" (baixo) na matriz de LEDs conforme a medida do sensor. Quando chega-se no nível alto, o exaustor é acionado, sendo desligado somente quando o nível de gás descer para "M" (médio).

- Controle de Acesso: Quando detectado um carro/pessoa a uma distância de x cm, a campainha (buzzer) é acionada e espera-se um comando para abrir ou não o portão. Caso deseja-se que o portão seja aberto, depois que ele abre, espera-se um comando para fecha-lo.

- Leitura da umidade e temperatura do ambiente, mostrando os dados no LCD.

- Quando detectada presença na porta da frente, a campainha é acionada (buzzer).

# Maquete

![Maquete](https://github.com/maiteluisaa/projeto_pi2/blob/main/figuras/maquete.png)

![Maquete e servomotor](https://github.com/maiteluisaa/projeto_pi2/blob/main/figuras/maquetee.png)

# Funções Futuras

Para o sistema de irrigação, planeja-se medir o nível do reservatório da bomba d'água com o sensor de nível de água. A regra de irrigação será baseada na umidade do solo, que será medida através do sensor YL-69, quando a umidade do solo estiver menor que 30%, o relé da bomba d'água será acionado e só será desligado quando a umidade passar de 30%.

![Sistema de Irrigação](https://github.com/maiteluisaa/projeto_pi2/blob/main/figuras/regar.png)

# Vídeo

Acesse os links abaixo para checar o funcionamento do projeto:

https://www.youtube.com/watch?v=k62mpUQfJKQ

https://youtu.be/ZnO91Lebzdc

# Sketch Atualizada

Acessar em: [Sketch](https://github.com/maiteluisaa/projeto_pi2/blob/main/sketch/novasketch_bb.pdf).
