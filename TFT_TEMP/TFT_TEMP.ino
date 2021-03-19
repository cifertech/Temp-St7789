#include <Arduino_ST7789.h>
#include <SPI.h>

#define TFT_DC   D1   // pin of your choice
#define TFT_RST  D0   // pin of your choice
#define TFT_MOSI D7   // fixed pin
#define TFT_SCLK D5   // fixed pin

#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0
#define WHITE    0xFFFF
#define VIOLET   0xAEAE8DF

#define YP A3
#define XM A2
#define YM 9
#define XP 8

#define XGRAPH 50
#define YGRAPH 75
#define HGRAPH 135
#define WGRAPH 21 

#define LM35 A0
Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST);

int newHeight;
int oldHeight = 0;
int heightDiff;


void setup(void) {

tft.init (240, 240); 
tft.fillScreen (BLACK);
tft.drawRect(10, 10, 220, 220, WHITE);
tft.fillRect(10, 10, 220, 220, BLACK);

Serial.begin(9600);
tft.fillCircle(XGRAPH, YGRAPH, (WGRAPH/2), WHITE);
tft.fillRect((XGRAPH-(WGRAPH/2)), YGRAPH, WGRAPH, HGRAPH, WHITE);
tft.fillCircle(XGRAPH, (HGRAPH+YGRAPH), ((WGRAPH/2)+10), WHITE);
tft.fillCircle(XGRAPH, YGRAPH, (WGRAPH/2)-3, WHITE);
tft.fillRect((XGRAPH-(WGRAPH/2)+3), YGRAPH, (WGRAPH-6), HGRAPH, WHITE);
tft.fillCircle(XGRAPH, (HGRAPH+YGRAPH), ((WGRAPH/2)+7), WHITE);
tft.fillCircle((XGRAPH+WGRAPH), YGRAPH, 3, WHITE);
tft.setTextColor(WHITE);
tft.setTextSize(2);
tft.setCursor(((XGRAPH+WGRAPH)+8), (YGRAPH-5));
tft.print("100");
tft.setTextSize(1);
tft.print("0");
tft.setTextSize(2);
tft.print("C");
tft.fillCircle((XGRAPH+WGRAPH), ((YGRAPH+(HGRAPH/2))-(WGRAPH/2)), 3, WHITE);
tft.setTextColor(WHITE);
tft.setTextSize(2);
tft.setCursor(((XGRAPH+WGRAPH)+8), (((YGRAPH+(HGRAPH/2))-(WGRAPH/2)))-5);
tft.print("50");
tft.setTextSize(1);
tft.print("0");
tft.setTextSize(2);
tft.print("C");
tft.fillCircle((XGRAPH+WGRAPH), ((YGRAPH+HGRAPH)-((WGRAPH/2)+7)), 3, WHITE);
tft.setTextColor(WHITE);
tft.setTextSize(2);
tft.setCursor(((XGRAPH+WGRAPH)+8), (((YGRAPH+HGRAPH)-((WGRAPH/2)+7))-5));
tft.print("0");
tft.setTextSize(1);
tft.print("0");
tft.setTextSize(2);
tft.print("C");

tft.fillRect((XGRAPH-(WGRAPH/2)+5), YGRAPH, (WGRAPH-10), HGRAPH, RED);
tft.fillCircle(XGRAPH, (HGRAPH+YGRAPH), ((WGRAPH/2)+5), RED);
}


void loop(void) {
  
int suhu=(analogRead(LM35)*5)/10;
tft.setCursor(150, 145);
tft.setTextColor(VIOLET, BLACK);
tft.setTextSize(4);
tft.print(suhu);
tft.setTextSize(2);
tft.print("0");
tft.setTextSize(4);
//tft.print("C");
tft.fillRect(130, 255, 80, 4, RED);
if(suhu <= 100){
newHeight = map(suhu,0, 100, 0, (HGRAPH-(WGRAPH/2)));
heightDiff = oldHeight-newHeight; // only draw new part of bar graph for faster display
if (oldHeight != newHeight) tft.fillRect((XGRAPH-(WGRAPH/2)+5), YGRAPH+((HGRAPH-suhu)-((WGRAPH/2)+7)), (WGRAPH-10), HGRAPH-((HGRAPH-suhu)-((WGRAPH/2)+7)), RED);
tft.fillRect((XGRAPH-(WGRAPH/2)+5), YGRAPH, (WGRAPH-10), ((HGRAPH-suhu)-((WGRAPH/2)+7)), WHITE);
if (suhu==100)tft.fillCircle(XGRAPH, YGRAPH, (WGRAPH/2)-5, RED);
oldHeight=newHeight; // remember how high bar is
}
tft.fillCircle(XGRAPH, (HGRAPH+YGRAPH), ((WGRAPH/2)+5), RED);
delay(300);
}
