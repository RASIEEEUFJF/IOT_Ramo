/*
Código Desenvolvido para realizar teste Com status de variáveis de armazenamento de memória no formato bool
código simples e fácil e funcionando de maneira correta
o circuito tem dois botoes um na porta D1 e Outro na porta D2 e um LED na Porta D0
D4----------RESITOR------------LED--------GND
RELÉ É 5 VOLTS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1

*/

//defindo Ledstatus para LOW, para sempre que ele reiniciar ir para zero
bool Ledstatus = LOW;
void setup() {
  // Definindo a porta D0 do ESP 8266 como Saida, porta que tem um LED conectada
  pinMode(D8, OUTPUT);
  //Definindo as Porta D1 e D2 como porta de leituras.
  pinMode(D4, INPUT_PULLUP);
  pinMode(D6, INPUT_PULLUP);
}

// Loop do projeto que vai ler e escrever nas portas, enquanto o programa rodar no esp
void loop() {
 // Ledstatus = LOW;
  if(digitalRead(D6) == 0){
   Ledstatus = HIGH;
   acendeLed(Ledstatus);
  }
  if  (digitalRead(D6) == 1) {               
    Ledstatus = LOW;
   acendeLed(Ledstatus);    
  }
  } 
 // Void que escreve na porta D0 do esp, porta essa que esta conecata o LED
void acendeLed(bool Ledstatus){
  digitalWrite(D5,Ledstatus);
  }
