

void aurora() {

  //Creat a sin wave with period of 2 seconds (30bpm) to change the brightness of the strip
  //uint8_t sinBeat = beatsin8(5, 150, 240, 0, 0);
  uint8_t sinBeat = beatsin8(5, 150, 240, 0, 0);
  // Color each pixel from the palette using the index from colorIndex[]
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(greenblue, colorIndex[i], sinBeat);
    //leds[i + 1] = ColorFromPalette(greenblue, colorIndex[i], sinBeat);
    //leds[i + 2] = ColorFromPalette(greenblue, colorIndex[i], sinBeat);
  }

  EVERY_N_MILLISECONDS(15) {//////////////////////////was 15
    for (int i = 0; i < NUM_LEDS; i++) {
      colorIndex[i]++;
    }
  }

    // for (int j = 0; j <8; j++) {
    //     //leds[j] = CRGB(181,0,255);        //pink
    //     //leds[j] = CRGB(20,  232,  30);    // dark green
    //     leds[j] = CRGB(0,   234,  101);     // light green
    //     //leds[j] = CRGB(1,   126,  213);     // blue
    //   }
//        for (int j = 0; j <5; j++) {
//        //leds[j] = CRGB(181,0,255);        //pink
//        leds[j] = CRGB(20,  232,  30);    // dark green
//        //leds[j] = CRGB(0,   234,  101);     // light green
//        //leds[j] = CRGB(1,   126,  213);     // blue
//      }

      // leds[0] = CRGB(181,0,255); 
      // leds[1] = CRGB(181,0,255); 
      // leds[2] = CRGB(181,0,255); 

//  leds[0] = CRGB(20,  232,  30);    // dark green
//  leds[1] = CRGB(0,   234,  101);     // light green
//  leds[2] = CRGB(0,   234,  101);     // light green
//  leds[3] = CRGB(1,   126,  213);   //blue
//  leds[4] = CRGB(1,   126,  213);   //blue
//  leds[5] = CRGB(181, 0, 255);      //pink
//  leds[6] = CRGB(141, 1,    196);     // pruple


  FastLED.show();
}
