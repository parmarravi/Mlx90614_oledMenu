#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define button1 D7 
#define button2 D1

int menuitem = 1;
int frame = 1;
int page = 1;
int lastMenuItem = 1;

String menuItem1 = "Ambient";
String menuItem2 = "Object";
String menuItem3 = "WifiMode";
String menuItem4 = "TurnOFF";

boolean navigateKey = false;
boolean selectionKey = false;

int navigateButtonState = 0;
int lastnavigateButtonState = 0;
int selectButtonState = 0;          
int lastSelectButtonState = 0;

Adafruit_SSD1306 display(4);
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); // initialize the sensor 

//display the home screen 
void firstScreen()
{
  display.clearDisplay();
  display.drawRect(0, 0, 128, 64, WHITE);
  display.setTextColor(WHITE,BLACK);
  display.setTextSize(2);
  display.setCursor(40,15);
  display.println("Smart");
  display.setCursor(35,35);
  display.println("Thermo");
  display.display();
}

void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  Wire.begin(D6,D5);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.clearDisplay(); 
  firstScreen();
  delay(2000);
  mlx.begin();
  display.clearDisplay(); 
  display.display();
  }

void loop() {
  // put your main code here, to run repeatedly:
   drawMenu();
  selectButtonState = digitalRead(button1);
  navigateButtonState = digitalRead(button2);
  checkIfnavigateButtonIsPressed();
  checkIfSelectButtonIsPressed();
  
  if(navigateKey && page ==1)
  {
    navigateKey=false;
       
    if(menuitem == 2 && lastMenuItem == 1)
    {
      frame++;
    } 
  if(menuitem == 3 && lastMenuItem == 2)
    {
      frame++;
    }
    if(menuitem == 4 && lastMenuItem == 3)
    { 
      frame++;
    }
     lastMenuItem = menuitem;
       menuitem++;
     if(menuitem ==5)
    {
      menuitem =1;
      frame = 1;
      }
  }
  
  if (selectionKey)
  {
    selectionKey = false;
    if(page ==1 && (menuitem==1 || menuitem ==2))  
    {
      page++;
    }
    else if(page ==2 && (menuitem==1 || menuitem ==2))
    {
      page++;
    }
    else if(page == 3)
    {
      page =1;
    }
  }
}
 void drawMenu()
  { 
  if (page==1) 
  {    
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(WHITE,BLACK);
    display.setCursor(34,10);
    display.print("MAIN MENU");
    display.drawFastHLine(0,25,128,WHITE);

    if(menuitem==1 && frame ==1)
    {   
      displayMenuItem(menuItem1, 30,true);
      displayMenuItem(menuItem2, 50,false);
    }
     if(menuitem == 2 && frame == 1)
    {
      displayMenuItem(menuItem1, 30,false);
      displayMenuItem(menuItem2, 50,true);
    }
     if(menuitem == 3 && frame == 2)
    {
      displayMenuItem(menuItem2, 30,false);
      displayMenuItem(menuItem3, 50,true);
    }
    if(menuitem == 4 && frame == 3)
    {
      displayMenuItem(menuItem3, 30,false);
      displayMenuItem(menuItem4, 50,true);
    }
    display.display();
  }
  else if (page==2 && menuitem == 1) 
  {    
   displaySecondSubMenuPage(menuItem1,mlx.readAmbientTempC(),"C","A Temperature C");
  }
   else if (page==3 && menuitem ==1) 
  {    
   displaySecondSubMenuPage(menuItem1,mlx.readAmbientTempF(),"F","< A Temperature F");
  }
   else if (page==2 && menuitem == 2) 
  {    
   displaySecondSubMenuPage(menuItem1,mlx.readObjectTempC(),"C","O Temperature C");
  }
   else if (page==3 && menuitem ==2) 
  {    
   displaySecondSubMenuPage(menuItem1,mlx.readObjectTempF(),"F","< O Temperature F");
  }
 
  }

void checkIfnavigateButtonIsPressed()
{
   if (navigateButtonState != lastnavigateButtonState) 
  {
    if (navigateButtonState == 0) {
      navigateKey=true;
     // Serial.println("Navigate True");
    }
    delay(50);
  }
   lastnavigateButtonState = navigateButtonState;
}

void checkIfSelectButtonIsPressed()
{
   if (selectButtonState != lastSelectButtonState) 
  {
    if (selectButtonState == 0) {
      selectionKey=true;
      //Serial.println("Selection True");
    }
    delay(50);
  }
   lastSelectButtonState = selectButtonState;
}
void displayMenuItem(String item, int position, boolean selected)
{
    if(!selected)
    {
      display.setTextColor(WHITE, BLACK);
    }else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.setTextSize(2);
    display.setCursor(0, position);
    display.print(">"+item);
 }
void displaySecondSubMenuPage(String item,float TempData,String Tempunit,String HeaderData)
{
    display.clearDisplay();
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(WHITE,BLACK);
    display.setCursor(10,5);
    display.print(HeaderData);
    display.drawFastHLine(0,18,128,WHITE);
    display.setTextSize(2);
    display.setCursor(5,35);
    display.print(TempData +Tempunit);
    display.display();
}
 
