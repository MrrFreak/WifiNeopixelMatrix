void Show_RainbowRun(){
  int tmp_hue;
  int tmp_c[3];
  if(actual_time > action_time){
    action_time = action_time + delayval;
    for(int i = 0; i < NUMPIXELS_S1; i++){
      tmp_hue = i + tmpval;
      tmp_hue = tmp_hue%359;
      HSVtoRGB_GAMMA(tmp_hue,255,max_hell,tmp_c);
      pixels_S1.setPixelColor(i,pixels_S1.Color(tmp_c[0], tmp_c[1], tmp_c[2]));
    }
    pixels_S1.show();
    tmpval = tmpval+1;
  }
}
