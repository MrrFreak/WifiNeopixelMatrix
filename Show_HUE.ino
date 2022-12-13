void Show_HUE(){
  int tmp_c[3];
  if(actual_time > action_time){
    action_time = action_time + delayval;
    HSVtoRGB_GAMMA(hue_val,255,max_hell,tmp_c);
    for(int i = 0; i < NUMPIXELS_S1; i++){
      pixels_S1.setPixelColor(i,pixels_S1.Color(tmp_c[0], tmp_c[1], tmp_c[2]));
    }
    pixels_S1.show();
  }
}
