/*
 * Wonderful christmas gift for my bride to be.. Anastasia
 * Christmas 2019
*/

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// Helper functions
#define LCDWidth u8g2.getDisplayWidth()
#define LCDHeight u8g2.getDisplayHeight()
#define ALIGN_CENTER(t) ((LCDWidth - (u8g2.getUTF8Width(t))) / 2)
#define ALIGN_RIGHT(t) (LCDWidth - u8g2.getUTF8Width(t))
#define ALIGN_LEFT 0

// Initialize u8g2
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

int lidState = 0;
String currentMessage = "";

// Sweet nothing messages to rotate through on the display
const String messages[] = {
  "I love you",
  "I love you so much",
  "You the cutest",
  "boop",
  "\"Hi\"",
  "beep",
  "bop",
  "Hellooww",
  ":)",
  "Hey",
  "Hey Cutie",
  "\"Will you\nmarry me?\"\n\"Sure\"",
  "Will you marry me?",
  "Ya dork",
  "Cutie",
  "Goofball",
  "You're the prettiest girl I've ever seen",
  "Can't wait to spend the rest of my life with you",
  "Drink water",
  "You should eat something",
  "\"Whatcha doin?\"",
  "Good morning. Today is a wonderful day",
  "Coffee is life",
  "Merry Christmas\nand a happy new year",
  "Hey :)",
  ";)",
  "<3",
  "Can't wait to marry you",
  "What's up homeslice",
  "Text Me",
  "Call Me",
  "Here's my number\n512-705-3596",
  "How's your day going?",
  "Foooooooooddddddd",
  "You da bomb.com",
  "Wanna get tacos",
  "Wanna get mexican",
  "Wanna get Tex-Mex",
  "Wanna get Chuy's",
  "Wanna get Chinese?",
  "Chicken wings?",
  "Time to get off TikTok",
  "We should go to the gym lol... nah",
  "Omg lol" 

};

void setup(void){
  int messagesLength = sizeof(messages)/sizeof(messages[0]);
  // initialization
  pinMode(19, INPUT_PULLDOWN);
  u8g2.begin();
  Serial.begin(115200);
  currentMessage = messages[random(0,messagesLength)];
}

void loop(void)
{
   if (Serial.available()){
      currentMessage = Serial.readString();
   }
  int lidStateNew = digitalRead(19);

  if (lidStateNew == 0 && lidState == 1) {
    Serial.println("wake up time");
    selectNewMessage();
  }
  lidState = lidStateNew;

  u8g2.setPowerSave(lidState);

  if (lidState == 0) {
    displayMessage(currentMessage);
    delay(1000);
  }
  else {
    // Wait a shorter peroid of time for more "instant" response... Had issues with interrupts so this is Plan B
    delay(100);
  }
}

void selectNewMessage(){
  int messagesLength = sizeof(messages)/sizeof(messages[0]);
  String newMessage = messages[random(0,messagesLength)];
  while (newMessage == currentMessage){
    newMessage = messages[random(0,messagesLength)];
  }
  currentMessage = newMessage;
  Serial.println(currentMessage);
}

void displayMessage(String text){
  u8g2.clearBuffer();                 // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2_uint_t charHeight = u8g2.getMaxCharHeight();
  // Serial.println(charHeight);

  uint8_t numberOfLines = calculateNumberOfLines(text);
  String lines[numberOfLines];

  generateLines(text, lines, numberOfLines);

  // Serial.println("Generated lines");

  u8g2_uint_t height = numberOfLines * (charHeight + 6);

  uint8_t lineNum = 0;
  for (int i = 0; i <= numberOfLines - 1; i++) {
    String line = lines[i];
    // Serial.println("Start loop");
    // Serial.println(line);
    char lineBuffer[line.length() + 1];
    line.toCharArray(lineBuffer, line.length() + 1);

    u8g2.drawStr(
        ALIGN_CENTER(lineBuffer),
        (LCDHeight / 2) + 20 - (height / 2) + (lineNum * (charHeight + 3)),
        lineBuffer);
    lineNum++;
  }

  u8g2.sendBuffer(); // transfer internal memory to the display
}
