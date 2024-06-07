# Automatização-o-Ramo-estudantil-IEEE-UFJF

  Este repositório tem como objetivo armazenar informações para auxiliar no desenvolvimento do projeto de automação do ramo Estudantil IEEE UFJF. Com foco na saúde dos colaboradores, o projeto destaca-se pelo uso da comunicação Wi-Fi entre os membros e as saídas do ramo. Após uma extensa pesquisa, foram analisadas as possibilidades de utilização do motor 17HS16-2004S1. Abaixo, apresentamos a sequência de acionamento.

|Step | N1| N2| N3| N4|
|-----|---|---|---|---|
|   1 |  1|  0|  1|  0|
|   2 |  0|  1|  1|  0|
|   3 |  0|  1|  0|  1|
|   4 |  1|  0|  0|  1|


  Para a alteração de cada passo, a tabela é modificada pelo tempo determinado pelo Step. Cada step possui 4 variáveis, que representam os polos do motor de passo bifásico. Portanto, em cada estado, é necessário enviar obrigatoriamente dois polos positivos e dois neutros para o motor, sendo crucial evitar a energização simultânea da mesma bobina.

Para identificar as bobinas, inicialmente, encontramos duas bobinas com os polos em série. Com base nelas, definimos a sequência de acionamento, seguindo as orientações do Datasheet do 17HS16. Em todo o projeto que envolve motores e tensões de saída, a tensão operacional é de 12 volts.
  
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

Vale ressaltar que a orientação é o Flat Vermelho. A partir dele, o primeiro fio da bobina deve ser orientado para a esquerda. Vermelho:
1 A+
2 B+
3 A-
4 B-

  Para a conexão do projeto, está sendo utilizada uma Ponte H para controlar o sentido de rotação do motor. O código utilizado baseia-se nas linguagens HTML e C++, e a comunicação será realizada por meio de um site criado pelos próprios programadores do IEEE.

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

Através de medições realizadas no dia 16 de novembro de 2023, utilizando 480W a 127V, encontramos um consumo de 3.17A e 9.08V, totalizando 28,78W com o motor ligado. Foi observado um aumento na temperatura na Ponte H.

Já com o Motor EM-257, aplicamos uma tensão de 12V, que ao acionar o motor, ela cai para 10,72V e entrega 1,40A. Mostrando uma rotação contínua interessante, porém com um comportamento anormal de aumento de temperatura, tanto na carcaça do motor quanto no dissipador de temperatura da Ponte H. Para tentar reduzir a temperatura, foi utilizado o método de desenvolvimento do motor, listado abaixo:

Para o desenvolvimento no motor EM-257, foram testados 3 tempos de passos e observados os seguintes valores
|Tempo em Mile Segundos| Corrente (A)| Tensão(V)|
|------------|---------|----------|
|16 mS | 1,57A |10,58V|
|8  mS | 1,40A |10,72V|
|4 mS  | 1,16A |10,98V|

Onde foi notado que no desenvolvimento de passo 4mS foi obtido os melhores resultados. 

Para o conhecimento de controle de acesso da porta, está sendo discutida a possibilidade de cadastrar o IP armazenado em vetores.

Para o desenvolvimento do código, vamos definir as variáveis.

O sensor de refletância está operando pela saída de pull-up do ESP no pino D8, utilizando o fio de cor preta conectado no pino D8. A alimentação do sensor é feita pelo fio marrom no +3V, e o fio azul é conectado ao GND.
_____________________________________________________________________________________
A partir dos testes realizados com o motor EM-257, avançamos para a montagem da condição, na qual utilizamos botões para controlar o sentido de rotação de acordo com o ângulo padronizado. Estipulamos um ângulo de 180º de rotação, equivalente a 200 passos.
_____________________________________________________________________________________

Código.
Para o desenvolvimento do código, foi escolhida a utilização do microcontrolador ESP-8266, onde nos deparamos com as limitações das portas. É um tanto peculiar mencionar isso quando poderíamos trabalhar com Arduino Mega e ESP32 como shield. O projeto está bastante evoluído, e a pinagem atual é a seguinte:

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


Uma coisa muito interessante é o trabalho com memória de dados. Vamos usar o tipo de dado 'bool', que carrega o nome 'PecaStatus' com a primeira letra maiúscula e 'Status' com 's' minúsculo. Temos 3 variáveis 'bool'. Devemos ter muita atenção ao mudar o status das variáveis. É importante destacar que estamos utilizando os valores 'true' e 'false'. Muita atenção a esta parte, pois erros podem resultar em má interpretação do código.

|Tipo de dados| Nome Variável| NIVEL(V)|
|------------|---------|----------|
|bool | Lampadastatus|LOW|
|bool | Portastatus |LOW|

_____________________________________________________________________________________
Observação realizada no dia 8 de dezembro foi que o interruptor não funciona no código, possivelmente seja alguma questão dentro do código. Talvez a razão esteja nos 'if's, pois não há um 'else' e talvez falte a condição para a ação. É estranho, mas demandará tempo de estudo.
_________________________________________________________________________________________

#Continuidade.
No dia 6 de Junho de 2024 Voltamos as manutenções a respeito do código de manutenção da porta do ramo, ond estamos desenvolvvendo a parte do site que será interativo com o código. Vale-se se ressaltar que como o mesmo é uma pagina armazenada no servidor local o esmo esta sendo desenvolvido em HTML, se prenda na parte onde que o processo atual temos um código que representa a interaçao entre servido e o fisico do projeto, que são lampadas, portas e sensores. 


