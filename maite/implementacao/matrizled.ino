#include <EEPROM.h>

#include <MD_MAX72xx.h>

#define  DELAYTIME  120  //Controla a velocidade em que o texto se desloca
#define TIPO_DO_HARDWARE MD_MAX72XX::GENERIC_HW  // Modelo da matriz de LED
#define MAX_MODULOS  1   // Quantidade de matriz de LED que o seu projeto possui

#define DIN  48  // Pino do DIN
#define CS    46  // Pino do CS
#define CLK   44   // Pino do CLK

MD_MAX72XX matriz(TIPO_DO_HARDWARE, DIN, CLK, CS, MAX_MODULOS);

void setup() {
  matriz.begin();
  matriz.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY/2);  //Controla a intensidade dos LEDs e MAX_INTENSITY é a intensidade maxima
}

void loop() {
  escrever_texto(" Teste ");
}

void escrever_texto(const char *p)  //Função que escreve o texto
{
  byte charWidth;
  byte cBuf[8];  
  matriz.clear();  //Desliga todos os LEDs da matriz
  while (*p != '\0')
  {
    charWidth = matriz.getChar(*p++, sizeof(cBuf) / sizeof(cBuf[0]), cBuf);
    for (byte i = 0; i <= charWidth; i++)  
    {
      matriz.transform(MD_MAX72XX::TSL);  //TSL = desloca um pixel para a esquerda
      if (i < charWidth)
        matriz.setColumn(0, cBuf[i]);
        delay(DELAYTIME);
    }
  }
}
