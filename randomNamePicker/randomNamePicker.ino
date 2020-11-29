/////////////////////////////////////////////////////////////////
#include "Button2.h"; //  https://github.com/LennartHennigs/Button2
#include "ESPRotary.h";
// Vajalikud teegid
#include "ssd1306.h"
#include "nano_gfx.h"
#include "sova.h"

/////////////////////////////////////////////////////////////////

// Nupu ja vibroanduri viigud
#define ROTARY_PIN1	D7
#define ROTARY_PIN2	D6
#define BUTTON_PIN  D8
#define VIBRATION_PIN D5

#define CLICKS_PER_STEP 4 // this number depends on your rotary encoder 

/////////////////////////////////////////////////////////////////
// Päevikute menüü
SAppMenu menu;

// Massiiv päevikute menüü jaoks
const char *subjects[] =
{
    "Eesti keel",
    "Matemaatika",
    "Kunstiopetus"
};

// Enkoodri ja nupu (meil enkoodri küljes) definitsioonid
ESPRotary r = ESPRotary(ROTARY_PIN1, ROTARY_PIN2, CLICKS_PER_STEP);
Button2 b = Button2(BUTTON_PIN);

// Esimese päeviku õpilaste nimekiri
char *subject0[] = {
  "Quentin Good",
  "Zakariya Ireland",
  "Amrit Allen",
  "Lina Hail",
  "Louie Lu",
  "Benedict Schofi",
  "Nathaniel Kelley",
  "Naseem Rooney",
  "Leigh Clemons",
  "Safa Ray"
};

// Teise päeviku õpilaste nimekiri
char *subject1[] = {
  "Quentin",
  "Zakariya",
  "Amrit",
  "Lina",
  "Louie",
  "Benedict",
  "Nathaniel",
  "Naseem",
  "Leigh",
  "Safa"
};

// Kolmanda päeviku õpilaste nimekiri
char *subject2[] = {
  "Good",
  "Ireland",
  "Allen",
  "Hail",
  "Lu",
  "Schofield",
  "Kelley",
  "Rooney",
  "Clemons",
  "Ray"
};

// Õpilaste nimkirjade suuruste arvutamine
int subject0Count = sizeof(subject0) / sizeof(char *) - 1;
int subject1Count = sizeof(subject1) / sizeof(char *) - 1;
int subject2Count = sizeof(subject2) / sizeof(char *) - 1;

// Päevikute menüü suuruse arvutamine
int subjectsCount = sizeof(subjects) / sizeof(char *);

// Mitu millisekundit näidatakse õpilase nime ekraanil
int showNameDelay = 3000;

/////////////////////////////////////////////////////////////////

void setup() {
  pinMode(VIBRATION_PIN, INPUT_PULLUP);
  delay(50);
  
  r.setLeftRotationHandler(updateCounter);
  r.setRightRotationHandler(updateCounter);

  b.setTapHandler(click);

  /* Select the font to use with menu and all font functions */
  ssd1306_setFixedFont(ssd1306xled_font8x16);
  sh1106_128x64_i2c_init();
  ssd1306_clearScreen( );
  ssd1306_createMenu( &menu, subjects, subjectsCount );
  ssd1306_showMenu( &menu );
}

void loop() {
  r.loop();
  b.loop();
  if(digitalRead(VIBRATION_PIN) == 0)
  {
   showName();; 
  }
}

/////////////////////////////////////////////////////////////////
// Nime kuvamise funktsioon - nime kuvatakse erinevast massiivist vastavalt menüü valikule
void showName()
{
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_clearScreen();

    switch (ssd1306_menuSelection(&menu))
    {
      case 0:
        ssd1306_printFixed(0, 16, subject0[random(0, subject0Count)] , STYLE_NORMAL);
        break;
      case 1:
        ssd1306_printFixed(0, 16, subject1[random(0, subject1Count)] , STYLE_NORMAL);
        break;
      case 2:
        ssd1306_printFixed(0, 16, subject2[random(0, subject2Count)] , STYLE_NORMAL);
        break;   
      default:
        break;
    }
    // Nime ekraanil kuvamise paus
    delay(showNameDelay);
    
    ssd1306_clearScreen();
    ssd1306_showMenu(&menu);
}

// Nupu keeramise registreerimine ja menüüs valiku muutmine
void updateCounter(ESPRotary& r) {
  if(r.getDirection() > 100)
  {
    ssd1306_menuUp(&menu);
  }
  else
  {
    ssd1306_menuDown(&menu);
  }
  ssd1306_updateMenu(&menu);
}


// Nupu vajutuse registreerimine
void click(Button2& btn) {
  showName();
}


/////////////////////////////////////////////////////////////////
