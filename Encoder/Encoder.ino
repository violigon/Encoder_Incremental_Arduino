/*
Projeto: Encoder
Autor: Vinícius Oliveira Gonçalves  
github.com/violigon
*/

int Pino1Encoder = 2;
int Pino2Encoder = 3;
int valormapeado = 0;
int ultimoMSB = 0;
int ultimoLSB = 0;
int estadoBotaoIni = 0;
int estadoBotaoFim = 0;

const int botaoIni = 4; 
const int botaoFim = 5;  

volatile int UltimoValorEncoder = 0;
volatile long ValorEncoder = 0;

long UltimoEncoder = 0;

void setup() 
{
  Serial.begin (9600);
  pinMode(Pino1Encoder, INPUT); 
  pinMode(Pino2Encoder, INPUT);
  pinMode(botaoIni,INPUT); 
  pinMode(botaoFim,INPUT);
  digitalWrite(Pino1Encoder, HIGH);
  digitalWrite(Pino2Encoder, HIGH);
  attachInterrupt(0, atualizaEncoder, CHANGE); 
  attachInterrupt(1, atualizaEncoder, CHANGE);
}

void loop()
{ 

  estadoBotaoIni = digitalRead(botaoIni);
  estadoBotaoFim = digitalRead(botaoFim);             
   
  if (estadoBotaoIni == HIGH)
  {
    valormapeado == 0;
  } else
  {
    valormapeado == valormapeado;
  }

    if (estadoBotaoFim == HIGH)
  {
    valormapeado == 1000;
  } else
  {
    valormapeado == valormapeado;
  }
  
  valormapeado = map(ValorEncoder,0,100000,0,100);
  Serial.println(valormapeado);
  //Serial.println(ValorEncoder);
  delay(120); 
}


void atualizaEncoder()
{
  int MSB = digitalRead(Pino1Encoder); 
  int LSB = digitalRead(Pino2Encoder); 

  int Encodado = (MSB << 1) |LSB; 
  int sum  = (UltimoValorEncoder << 2) | Encodado; 

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) ValorEncoder ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) ValorEncoder --;

  UltimoValorEncoder = Encodado; 
}
