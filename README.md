# Automatização-o-Ramo-estudantil-IEEE-UFJF

  Este repositório tem como objetivo armazenar a fim de auxiliar no desenvolvimento do projeto da automatização do ramo Estudantil IEEE UFJF.
Visando a saúde dos colaboradores o projeto tem como principal ponto forte a comunicação WIFI entre membro e saidas do ramo.
Após uma grande pesquisa, foi estudado sobre a utilização do motor 17hs16-2004s1, abaixo podemos ver a sequência de ligamento.

|Step | N1| N2| N3| N4|
|-----|---|---|---|---|
|   1 |  1|  0|  1|  0|
|   2 |  0|  1|  1|  0|
|   3 |  0|  1|  0|  1|
|   4 |  1|  0|  0|  1|


  Para a alteração de cada passo, a tabela é alterada pelo tempo determinado pelo Step, cada step tem 4 váriaveis que são os polos do motor de passo bifásico, logo a cada status obrigatóriamente enviáremos dois polos positivos no motor e dois neutros, onde devemos tomar cuidado para não energizarmos a mesma bobina. Para o reconhecimento da mesma foi encontrado primeiramente duas bobinas onde os polos estão em série, a partir dela definimos a sequência de acionamento nos baseando do Datasheat do 17hs16. Todo o projeto que envolve motores e tensôes de saída,a tensão operada é de 12 Volt's.
  
|Saida Ponte H |Cores referência |
|-------------|------------|
|N1 | PRETO |
|N2 | VERDE |
|N3 | VERMELHO| 
|N4 | AZUL|

|Ligação das bobinas do motor 17HS16:|
|---------------------------|
|A+ Preto | A- Verde|
|B+ vermelho| B- Azul|

|Bobinas motor EM-257| Cores na Ponte H|
|---------------------------------|----------|
|VERMELHO FLAT| Preto   | 
|SEGUNDO FLAT | Vermelho| 
|TERCEIRO FLAT | Verde|
|QUARTO FLAT| Azul|

Vale ressaltar que á orientação é o Flat Vermelho. E a partir dele,o primeiro fio da bobina ser orientado para a Esquerda. 
Vermelho:
1 A+
2 B+
3 A-
4 B-

  Para  a ligação do projeto está sendo utilizada a Ponte H para o controle do sentido do giro do motor. O código utilizado basea-se nas linguagens HTML e C+ e a comunicação vai ser feita através de comunicação de uma site criado pelos próprios programadores do IEEE. 

Modelo de ponte H usado no projeto:
L298N

Através da seguinte função calculamos o delay de passo:

200 stcps = 360 graus.
1 rpm = 360/60s

Fazendo uma regra de três para obter quantos passos por segundo:
(400/60) * stecs/s = 0,15 ms

 -> 20*(360/60) = 60 stcps/s (refazer)
tsecps= (1/120) -> 8,333s

Podemos determinar esse delay através da equação:
tspecs = 1/N*6 [s]

17HS16

Através de medições realizadas no dia 16 de Novembro de 2023 utilizando 480W, 127V encontramos 3.17A e e 9.08V 28,78W de consumo com o motor ligado.
foi observado o aumento  da temperatura na Ponte H

Já com o Motor EM-257, aplicamos uma tensão de 12V, que ao acionar o motor ela cai para 10,72V e entrega 1,40A. 
Mostrando uma rotação continua interresante mas com um comportamento anormal de aumento temperatura, tanto na carcaça do motor quanto no dissipador de temperatura da Ponte H.
Para tentar reduzir a temperatura foi utilizado o método de desenvolvimento do motor; listado abaixo:

Para o desenvolvimento no motor EM-257, foram testados 3 tempos de passos e observados os seguintes valores
|Tempo em Mile Segundos| Corrente (A)| Tensão(V)|
|------------|---------|----------|
|16 mS | 1,57A |10,58V|
|8  mS | 1,40A |10,72V|
|4 mS  | 1,16A |10,98V|

Onde foi notado que no desenvolvimento de passo 4mS foi obtido os melhores resultantes. 

Para o Cochecimento de controle de acesso da porta, esta sendo discutindo a possibilidade de cadastro de IP armazenado em vetores do 

para o Desenvolvimento do Código vamos definir as varáveis 

O sensor de refletância está funcionando pela saída de pull-up do ESP no pino D8, utilizando o fio de cor preta conectado no pino D8 e a alimentação do sensor é feita pelo fio marrom no +3V e o fio azul no GND.
_____________________________________________________________________________________
A partir dos teste realizados pelo motor EM-257, partimos para a montagem da condicional onde usamos botões para o controle de sentido de giro de acordo com o angulo que nós temos padronizados. estipulamos um angulo de 180º de rotação que da 200' Passos.
_____________________________________________________________________________________

Código. 
Para o desenvolvimento do Código foi escolhiodo a utilização do microcontrolador ESP-8266. onde batemos de frente com as limitações das portas, é muito estranho se falar nisso quando podemos trabalhar com arduino Mega com o esp32 como shield, o projeto ta bem evuluido e pinagem atual é a seguinte. 


|PORTA NODE MCU|LIGAÇÃO|MOTOR|
|-------------|------------|---------|
|D0 | PONTE H |PRETO|
|D1 | PONTEH |VERDE|
|D2 | PONTE H|VERMELHO| 
|D3 | PONTE H|AZUL|
|D4 |InterruptorLampada | |
|D5 |ReleLampada | |
|D6 |InterruptorPorta | |
|D7 |LedVerde | |
|D8 |LedSinal | |


um coisa muito interessante é o trabalho com memória de dados, vamos usar o tipo de dado bool, que carregam o nome Peçastatus com oa primeira letra maiscula e Status com s minusculo. temos 3 variaveis bool. Temos que ter muita atenção onde mudar a status das variáveis. muito pica tambem é entender que estamos mudando as variáveis com o tipo true e false. muitatenção a esta parte, o erro pode acarretar na má interpretação do código.

|Tipo de dados| Nome Variável| NIVEL(V)|
|------------|---------|----------|
|bool | Lampadastatus|LOW|
|bool | Portastatus |LOW|

_____________________________________________________________________________________
obeservação realizada no dia 8 de dezembro foi que o interruptor não funciona no código, possivelmente seja alguma questão dentro do código. Possivelmente seja a questão de estamos errando seja nos if's, pois ele não tem um else e talvez não tenha a condição da ação, é estranhos mas vai demandar tempode estudo


