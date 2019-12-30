#include <Arduino.h>
void generateLines(String text, String lines[], uint8_t numberOfLines){
    uint8_t startingPoint = 0;

    if (text.indexOf("\n") > 0){
        for (int i = 0; i < numberOfLines; i++){
            uint8_t newLineIndex = text.indexOf("\n", startingPoint);
            lines[i] = text.substring(startingPoint, newLineIndex);
            Serial.println("Prepared line" + lines[i]);
            startingPoint = newLineIndex + 1;

        }
        return;
    }

    Serial.println(text);
    
    for (int i = 0; i < numberOfLines; i++)   {
        Serial.println("Preparing line: " + String(i));

        uint8_t lineLength = text.length() / (numberOfLines - i);
        Serial.println("line length: " + String(lineLength));
        uint8_t spaceIndex = text.lastIndexOf(' ', startingPoint + lineLength);
        Serial.println("Space Index: " + String(spaceIndex));

        Serial.println(String(startingPoint) + " - " + String(spaceIndex));
        Serial.println(text.substring(startingPoint, spaceIndex));

        lines[i] = text.substring(startingPoint, spaceIndex);
        Serial.println(lines[i]);
        startingPoint = spaceIndex;
    }
}

uint8_t calculateNumberOfLines(String text){
    if (text.indexOf("\n") > 0){
        int count = 1;
        int startingPoint = 0;
        while((startingPoint = text.indexOf("\n", startingPoint)) > 0){
            count++;
            startingPoint++;
        }
            Serial.println("Calculated lines (inside): " + String(count));

        return count;
    }
    uint8_t lcd_width = LCDWidth;
    uint8_t numberOfLines = 0;
    char textArray[text.length()];
    text.toCharArray(textArray, text.length() + 1);

    Serial.print("text array ");
    Serial.println(textArray);
    uint16_t width = strlen(textArray) * 8;
    Serial.println("Width: " + String(width) + "\t" + String(lcd_width));

    Serial.println((float)width / (float)lcd_width);

    numberOfLines = ceil((float)width / (float)lcd_width);
    Serial.println("Calculated lines (inside): " + String(numberOfLines));
    return numberOfLines;
}