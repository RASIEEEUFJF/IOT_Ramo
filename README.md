# Iot do Ramo Estudantil IEEE

## Objetivo:
Esse é um projeto que mostra todas as etapas da implantação do sistema IOT no Ramo Estudantil IEEE-UFJF. O objetivo principal dele é modernizar nosso ramo, possibilitando uma acessibilidade maior da sala, além de servir de exemplo para outros grupos realizarem o mesmo.

_____________________________________________________________________________________________________________________________________

## Materiais

|        Nome          |    Especificação                           |
|----------------------|--------------------------------------------|
| ESP Node MCU         | Proporciona o controle do projeto pelo site|
| Tranca Eletrônica    | Tem a função de trancar a sala             |
| Ponte H              | Aciona a Tranca Eletrônica                 |

_____________________________________________________________________________________________________________________________________

## Príncipios de Funcionamento 

O funcionamento consiste na ativação da Tranca Eletrônica por meio de um site HTML. Essa ativação só será válida para determinados IPs pré estabelecidos no código do site.

________________________________________________________________________________________________________________________________________

## Modo de uso

O usuário deve pedir para o responsável pelo site adicionar seu IP na lista. Já adicionado, cabe ao usuário acessar o site disponibilizado a ele e clicar no botão "Abrir Porta". Ao fazer isso, a tranca será liberada e o usuário terá acesso ao ramo.

_______________________________________________________________________________________________________________________________________

## Materiais de Referência

https://embarcados.com.br/esp32-macaddress/

__________________________________________________________________________________________________________________________________________

## Testes Recentes

### Teste 6 de junho
No dia 6 de Junho de 2024 Voltamos as manutenções a respeito do código de manutenção da porta do ramo, onde estamos desenvolvendo a parte do site que será interativo com o código. Vale-se se ressaltar que como o mesmo é uma pagina armazenada no servidor local o esmo esta sendo desenvolvido em HTML, se prenda na parte onde que o processo atual temos um código que representa a interaçao entre servido e o fisico do projeto, que são lampadas, portas e sensores. 

### Teste 27 de junho
No dia 27 de junho voltamos a manutenção a respeito do processo, foi observado que o relê utilizado para o controle do projeto tem que ser alimentado com a tensão de 5 volt's. Podemos observa que o o projeto possivelmente tera que ser alimentado com carregador de celular na porta Vin do NodeMCU. onde aravés do processo iremos alimentar o resto na porta 3 Volt's do NodeMC. onde testamos o Buzze.

### Teste 18 de julho
No dia 18 de julho, foi criado o código base para acionar a fechadura. Com a fechadura em mãos, foram feitas as ligações necessárias utilizando arduino, ponte h, jumpers e a fonte de alimentação. Também se teve avanço na criação do site. Foi interessante observar que os métodos utilizados não entregou 12V a fechadura, assim, ela não acionava. Para resolver esse problema foi colocado uma fase na porta 5 do ESP (por meio da ponte H) e o terra foi conectado direto na fonte, evitando a passagem no capacitor o que aumentou a tensão obtida. No entanto não chegamos ao valor esperado de 12V, mesmo assim, a fechadura aciona, uma vez que a potência é a esperada.

### Teste 06 de setembro

No dia 6 de setembro, finalizamos os detalhes para o código "simples" da porta apenas com o sistema de segurança da senha do wifi do esp8266. Adicionamos os leds, buzzer e  botões para controle no físico da tranca e da lampada do ramo além de ajeitarmos alguns detalhes estéticos do site. Para as próximas reuniões agora só temos que instalar o circuito na porta para que ela funcione num primeiro instante dessa maneira temporária. Depois passaremos a estudar como aplicar um modelo mais eficiente de segunrança.
__________________________________________________________________________________________________________________________________________________________________________________
