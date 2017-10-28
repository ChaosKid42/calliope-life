#define _GNU_SOURCE

#include "MicroBit.h" 
#include <array>
#include <stdlib.h>
MicroBit uBit;

int lebendig(int x, int y);
int nachbarnLebendig(int x, int y);
int neuLebendig(int x, int y);
void schritt();

int helligkeit;
int wartez;
array<int, 25> tempListe;
int main() 
{
    uBit.init();
    
    helligkeit = 9;
    wartez = 100;
    tempListe = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uBit.display.setDisplayMode(DISPLAY_MODE_GREYSCALE);
    for (int y = 0; y < 5; y += 1) {
        for (int x = 0; x < 5; x += 1) {
            uBit.display.image.setPixelValue(x, y, uBit.random(2) * 255.0);
        }
    }
    while ( true ) {
        while ( true ) {
            if ( uBit.buttonA.isPressed() ) {
                break;
            }
        }
        schritt();
        uBit.sleep(200);
    }
    release_fiber();
}

int lebendig(int x, int y) {
        if (( x > 4 ) || ( x < 0 ) || ( y > 4 ) || ( y < 0 )) return 0;
        if (uBit.display.image.getPixelValue(x, y) > 0) return 1;
        return 0;
}

int nachbarnLebendig(int x, int y) {
        int nachbarn;
        nachbarn = 0;
        nachbarn += lebendig(x + -1, y + 0);
        nachbarn += lebendig(x + 1, y + 0);
        nachbarn += lebendig(x + 0, y + -1);
        nachbarn += lebendig(x + 0, y + 1);
        nachbarn += lebendig(x + -1, y + -1);
        nachbarn += lebendig(x + 1, y + 1);
        nachbarn += lebendig(x + -1, y + 1);
        nachbarn += lebendig(x + 1, y + -1);
        return nachbarn;
}

int neuLebendig(int x, int y) {
        int nachbarn = nachbarnLebendig(x, y);
        if ( lebendig(x, y) == 0 ) {
            if (nachbarn == 3) return helligkeit;
        } else {
            if (( nachbarn == 2 ) || ( nachbarn == 3 )) return helligkeit;
        }
        return 0;
}

void schritt() {
        for (int y = 0; y < 5; y += 1) {
            for (int x = 0; x < 5; x += 1) {
                tempListe[( y * 5 ) + x] = neuLebendig(x, y);;
            }
        }
        for (int y = 0; y < 5; y += 1) {
            for (int x = 0; x < 5; x += 1) {
                uBit.display.image.setPixelValue(x, y, tempListe[( y * 5 ) + x] * 255.0 / 9.0);
            }
        }
}
