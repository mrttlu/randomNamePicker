/////////////////////////////////////////////////////////////////
#include "Button2.h"; //  https://github.com/LennartHennigs/Button2
#include "ESPRotary.h";

#include "ssd1306.h"
#include "nano_gfx.h"
#include "sova.h"

/////////////////////////////////////////////////////////////////

#define ROTARY_PIN1	D7
#define ROTARY_PIN2	D6
#define BUTTON_PIN  D8
#define VIBRATION_PIN D5

#define CLICKS_PER_STEP   4   // this number depends on your rotary encoder 


/////////////////////////////////////////////////////////////////
SAppMenu menu;

const char *subjects[] =
{
    "Eesti keel",
    "Matemaatika",
    "Kunstiopetus"
};


ESPRotary r = ESPRotary(ROTARY_PIN1, ROTARY_PIN2, CLICKS_PER_STEP);
Button2 b = Button2(BUTTON_PIN);

char *subject0[] = {
  "Quentin Good",
  "Zakariya Ireland",
  "Amrit Allen",
  "Lina Hail",
  "Louie Lu",
  "Benedict Schofield",
  "Nathaniel Kelley",
  "Naseem Rooney",
  "Leigh Clemons",
  "Safa Ray"
};

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

int subject0Count = sizeof(subject0) / sizeof(char *) - 1;
int subject1Count = sizeof(subject1) / sizeof(char *) - 1;
int subject2Count = sizeof(subject2) / sizeof(char *) - 1;

int subjectsCount = sizeof(subjects) / sizeof(char *) - 1;

int showNameDelay = 3000;

/////////////////////////////////////////////////////////////////

void setup() {
  pinMode(VIBRATION_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  delay(50);
  
  r.setLeftRotationHandler(updateCounter);
  r.setRightRotationHandler(updateCounter);

  b.setTapHandler(click);
  b.setLongClickHandler(resetPosition);

  /* Select the font to use with menu and all font functions */
  ssd1306_setFixedFont(ssd1306xled_font6x8);
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
void showName()
{
    // Serial.println(students[random(0, studentsCount)]);
    ssd1306_setFixedFont(ssd1306xled_font6x8);
    ssd1306_clearScreen();

    switch (ssd1306_menuSelection(&menu))
    {
        case 0:
            ssd1306_printFixed(0,  8, subject0[random(0, subject0Count)] , STYLE_NORMAL);
            break;

        case 1:
            ssd1306_printFixed(0,  8, subject1[random(0, subject1Count)] , STYLE_NORMAL);
            break;

        case 2:
            ssd1306_printFixed(0,  8, subject2[random(0, subject2Count)] , STYLE_NORMAL);
            break;
            
        default:
            break;
    }
    delay(showNameDelay);
    ssd1306_clearScreen();
    ssd1306_showMenu(&menu);
}

// on left or right rotation
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


// single click
void click(Button2& btn) {
  Serial.println("Click!");
  Serial.println(ssd1306_menuSelection(&menu));
  showName();
}

// long click
void resetPosition(Button2& btn) {
  r.resetPosition();
  Serial.println("Reset!");
}


/////////////////////////////////////////////////////////////////
