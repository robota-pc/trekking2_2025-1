#include <FastLED.h>

#define DATA_PIN    5
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    14

#define BRIGHTNESS  96

CRGB leds[NUM_LEDS];


const int btCH = 2;
const int btAM = 3;
const int ledcalCH = 6;
const int ledcalAM = 7;
const int ledOK = 1;
const int s0 = 9;  
const int s1 = 10;  
const int s2 = 13;
const int s3 = 12;  
const int out = 11;   
//int RedLed = 2;  
//int GreenLed = 4;  
//int BlueLed = 7;  
int colorIsRed = 1;
int colorIsBlue = 2;
int colorIsGreen = 3;
int colorIsWhite = 3;
int colorIsYellow = 4;
int estadoButtonCH = 0;//Variável responsável por armazenar o estado do botão (ligado/desligado)
int estadoButtonAM = 0;

//Contador
int CountR;
int CountB;
int CountG;
int CountY;
int ultimaCor=0;
int NoColor =0;
    
//Variaveis que armazenam o valor das cores  
int red = 0;  
int green = 0;  
int blue = 0;  

//Variaveis usadas na calibracao
int mediaR;
int mediaB;
int mediaG;

int mediaRR;
int mediaBR;
int mediaGR;

int mediaRG;
int mediaBG;
int mediaGG;

int mediaRB;
int mediaBB;
int mediaGB;

int mediaRY;
int mediaBY;
int mediaGY;

    
void setup()   
{  
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  CountR = CountG = CountB = 0;
  //configura as entradas e saidas
  pinMode(ledcalCH, OUTPUT);  
  pinMode(ledcalAM, OUTPUT);
  pinMode(ledOK, OUTPUT);
  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);  
  pinMode(out, INPUT);  
  pinMode(btCH, INPUT);
  pinMode(btAM, INPUT);
  //pinMode(RedLed, OUTPUT);  
  //pinMode(GreenLed, OUTPUT);  
  //pinMode(BlueLed, OUTPUT); 
  //Seleciona a escala de frequncia para 20% 
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, LOW);  
  //Inicializa a porta serial
  Serial.begin(9600);  
  delay(500);
  //chama funcao para calibrar o sensor
  calibraSensor();
}  
    
void loop() 
{  
  int CorIdentificada;

  //chama funçao para ler o sensor
  Readcolor();
  //imprimi valores na tela
 /* Serial.print(" Leitura do sensor por filtro: "); 
  Serial.println(); 
  Serial.print(" Azul : ");  
  Serial.print(blue, DEC); 
  Serial.print(" Vermelho :");  
  Serial.print(red, DEC);  
  Serial.print(" Verde : ");  
  Serial.print(green, DEC); 
  Serial.println();  */


    CorIdentificada = IdentificaCor();
    digitalWrite(ledOK, LOW);

  //Verifica se a cor vermelha foi detectada  
  if (CorIdentificada == colorIsRed)  
  {  
       if(ultimaCor != colorIsRed)
         CountR++;
   
       Serial.println(" Cor Identificada Vermelho: "); 
       fill_solid(leds, NUM_LEDS, CRGB::Black);
       FastLED.show();
       //Serial.println(CountR,'DEC'); 
       //digitalWrite(RedLed, HIGH); //Acende o led vermelho  
       //digitalWrite(GreenLed, LOW);  
       //digitalWrite(BlueLed, LOW);  
       delay(10);
       ultimaCor = colorIsRed;
  }  
  
  //Verifica se a cor azul foi detectada  
  else if (CorIdentificada == colorIsBlue)   
  {  
       if(ultimaCor != colorIsBlue)
         CountB++;
       Serial.println(" Cor Identificada: ama ");  
       fill_solid(leds, NUM_LEDS, CRGB(128, 0, 128));  // roxo
       FastLED.show();
       //Serial.println(CountB,'DEC');
       //digitalWrite(RedLed, LOW);  
       //digitalWrite(GreenLed, LOW);  
       //digitalWrite(BlueLed, HIGH); //Acende o led azul  
       delay(10);
       ultimaCor = colorIsBlue;
  }  
  /*
  //Verifica se a cor verde foi detectada  
  else if (CorIdentificada == colorIsGreen)  
  {         
        if(ultimaCor != colorIsGreen)
             CountG++;
             
       Serial.println(" Cor Identificada: amv ");  
       fill_solid(leds, NUM_LEDS, CRGB(128, 0, 128));  // roxo
       FastLED.show();
       //Serial.println(CountG,'DEC');
       //digitalWrite(RedLed, LOW);  
       //digitalWrite(GreenLed, HIGH); //Acende o led verde  
       //digitalWrite(BlueLed, LOW);
       delay(10);   
       ultimaCor = colorIsGreen; 
  }  
   else if (CorIdentificada == colorIsYellow)  
  {         
        if(ultimaCor != colorIsYellow)
             CountG++;
             
       Serial.println(" Cor Identificada: amarelo "); 
       fill_solid(leds, NUM_LEDS, CRGB(128, 0, 128));  // roxo
       FastLED.show(); 
       //Serial.println(CountG,'DEC');
       //digitalWrite(RedLed, LOW);  
       //digitalWrite(GreenLed, HIGH); //Acende o led verde  
       //digitalWrite(BlueLed, LOW);
       delay(10);   
       ultimaCor = colorIsYellow; 
  }  */
  else
  {
    ultimaCor = NoColor;
    Serial.println(" Cor Identificada: Nenhuma ");  
  }
  
  
  //Serial.println(); 
  //Serial.println();  
  //digitalWrite(RedLed, LOW);  
  //digitalWrite(GreenLed, LOW); 
  //digitalWrite(BlueLed, LOW); 
  //delay(10);   
  
}  
    
void Readcolor()  
{  
  //le saida com filtro vermelho
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);  
  delay(50);
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  
  
  //Le saida com filtro azul
  digitalWrite(s3, HIGH);  
  delay(50);
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  
  //le saida com filtro verde
  digitalWrite(s2, HIGH);  
  delay(50);
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  
  /*
  Serial.print(" Leitura do sensor por filtro: "); 
  Serial.println(); 
  Serial.print(" Azul : ");  
  Serial.print(blue, DEC); 
  Serial.print(" Vermelho :");  
  Serial.print(red, DEC);  
  Serial.print(" Verde : ");  
  Serial.print(green, DEC); 
  Serial.println();  */
}

void calibraSensor()
{
  int i;
  int controlLoop = true;
  int byteRead;
  int calibrouB = true;
  int calibrouR = true;
  int calibrouG = true;
  int calibrouY = true;
  
  Serial.write("Voce esta na funcao de calibracao do TCS230"); 
  Serial.println();  
  Serial.write("Digite 1 para vermelho - 2 para azul - 3 para verde - 4 para amarelo - 5 para fechar a calibracao - 6 para reinicializar a calibracao");  
  Serial.println(); 
  delay(100);
  
  
  while(controlLoop)
  {
      //LEMBRAR DE ACENDER DOIS LEDS PARA COMEÇAR CALIBRAÇÃO PROVAVELMENTE QUANDO EU CHAMAR A FUNÇÃO CALIBRAR OU ALGO ASSIM
      //AQUI DENTRO OS DOIS LEDS NAO
      //AQUI DEVO COLOCAR A LEITURA DOS  BOTOESX
      estadoButtonCH = digitalRead(btCH);//Lê o valor de buttonPin e armazena em estadoButton
      estadoButtonAM = digitalRead(btAM);

      digitalWrite(ledcalCH, HIGH);
      digitalWrite(ledcalAM, HIGH);
      if( (estadoButtonCH == HIGH) && calibrouR)
      { 
        int amostrasRe = 40;
        calibrouR = false;
        Serial.print("calibrando cor Chao");
        Serial.println();
        digitalWrite(ledcalCH, HIGH);
        digitalWrite(ledcalAM, LOW);
        
        mediaR = mediaB = mediaG = 0;
        for(i=0; i<amostrasRe; i++)
        {
          Readcolor();
          mediaR +=red;
          mediaB +=blue;
          mediaG += green;
          delay(50);
        }
       
        mediaRR = mediaR/amostrasRe;
        mediaBR = mediaB/amostrasRe;
        mediaGR = mediaG/amostrasRe;
        Serial.print("calibracao cor chao finalizada");
        Serial.println();
        Serial.print(mediaRR),DEC;
        Serial.println();
        Serial.print(mediaBR,DEC);
        Serial.println();
        Serial.print(mediaGR,DEC);
        Serial.println();
        digitalWrite(ledcalCH, LOW);
        //Serial.write("Digite 1 para vermelho - 2 para azul - 3 para verde - 4 para fechar a calibracao - 5 para reinicializar a calibracao");  
        Serial.println();
      }
      
      if( (estadoButtonAM == HIGH) && calibrouB )
      { 
        int amostrasBl = 40;
        calibrouB=false;
        Serial.print("calibrando cor objetivo");
        Serial.println();
        digitalWrite(ledcalAM, HIGH);
        digitalWrite(ledcalCH, LOW);
        
        mediaR = mediaB = mediaG = 0;
        for(i=0; i<amostrasBl; i++)
        {
          Readcolor();
          mediaR += red;
          mediaB += blue;
          mediaG += green;
          delay(50);
        }
       
        mediaRB = mediaR/amostrasBl;
        mediaBB = mediaB/amostrasBl;
        mediaGB = mediaG/amostrasBl;
        Serial.print("calibracao cor objetivo finalizada");
        Serial.println();
        Serial.print(mediaRB,DEC);
        Serial.println();
        Serial.print(mediaBB,DEC);
        Serial.println();
        Serial.print(mediaGB,DEC);
        Serial.println();
        digitalWrite(ledcalAM, LOW);
        //Serial.write("Digite 1 para vermelho - 2 para azul - 3 para verde - 4 para fechar a calibracao - 5 para reinicializar a calibracao");  
        Serial.println();
      }
      
      
      /*if( (byteRead == '3') && calibrouG )
      { 
        int amostrasGr = 40;
        calibrouG = false;
        Serial.print("calibranado a cor verde");
        Serial.println();
        mediaR = mediaB = mediaG = 0;
        for(i=0; i<amostrasGr; i++)
        {
          Readcolor();
          mediaR += red;
          mediaB += blue;
          mediaG += green;
          delay(50);
        }
       
        mediaRG = mediaR/amostrasGr;
        mediaBG = mediaB/amostrasGr;
        mediaGG = mediaG/amostrasGr;
        Serial.print("calibracao cor verde finalizada");
        Serial.print(mediaRG,DEC);
        Serial.println();
        Serial.print(mediaBG,DEC);
        Serial.println();
        Serial.print(mediaGG,DEC);
        Serial.println();
        
        Serial.write("Digite 1 para vermelho - 2 para azul - 3 para verde - 4 para amarelo - 5 para fechar a calibracao - 6 para reinicializar a calibracao");  
        Serial.println();
      }
 
      if( (byteRead == '4') && calibrouY )
      { 
        int amostrasYe = 40;
        calibrouG = false;
        Serial.print("calibranado a cor amarela");
        Serial.println();
        mediaR = mediaB = mediaG = 0;
        for(i=0; i<amostrasYe; i++)
        {
          Readcolor();
          mediaR += red;
          mediaB += blue;
          mediaG += green;
          delay(50);
        }
       
        mediaRY = mediaR/amostrasYe;
        mediaBY = mediaB/amostrasYe;
        mediaGY = mediaG/amostrasYe;
        Serial.print("calibracao cor verde finalizada");
        Serial.print(mediaRY,DEC);
        Serial.println();
        Serial.print(mediaBY,DEC);
        Serial.println();
        Serial.print(mediaGY,DEC);
        Serial.println();
        
        Serial.write("Digite 1 para vermelho - 2 para azul - 3 para verde - 4 para amarelo - 5 para fechar a calibracao - 6 para reinicializar a calibracao");  
        Serial.println();
      }*/


      
      if((estadoButtonCH == HIGH) && (estadoButtonAM == HIGH) )
      { 
        controlLoop = false;
        digitalWrite(ledcalAM, LOW);
        digitalWrite(ledcalCH, LOW);
        digitalWrite(ledOK, HIGH);
      }
      
      if(byteRead == 'g' )
      { 
        calibrouR = true;
        calibrouB = true;
        calibrouG = true;
      }
  }

}

int IdentificaCor()
{
  int margem = 10; // antes era 15
  //verifica se a cor e verde
  /*if( (blue>(mediaBG-margem) && blue<(mediaBG+margem)) && (red>(mediaRG-margem) && red<(mediaRG+margem)) && (green>(mediaGG-margem) && green<(mediaGG+margem)))
    return colorIsGreen;
    */
  //verifica se a cor e azul
  if((blue>(mediaBB-margem) && blue<(mediaBB+margem)) && (red>(mediaRB-margem) && red<(mediaRB+margem)) && (green >(mediaGB-margem) && green<(mediaGB+margem)) )
    return colorIsBlue;
  
  //Verifica se a cor e vermelha  
  else if((blue>(mediaBR-margem) && blue<(mediaBR+margem)) && (red>(mediaRR-margem) && red<(mediaRR+margem)) && (green >(mediaGR-margem) && green<(mediaGR+margem)) )
    return colorIsRed;
  /*
  //verifica se a cor e amarela
  else if((blue>(mediaBG-margem) && blue<(mediaBG+margem)) && (red>(mediaRG-margem) && red<(mediaRG+margem)) && (green>(mediaGG-margem) && green<(mediaGG+margem)))
    return colorIsYellow;
    */
  }