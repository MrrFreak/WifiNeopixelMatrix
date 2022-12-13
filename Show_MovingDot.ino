void Show_MovingDot(){
  int tmp_hue;
  int tmp_c[3];
  if(actual_time > action_time){
    action_time = action_time + delayval;
    tmpval = tmpval%NUMPIXELS_S1;
    for(int i = 0; i < NUMPIXELS_S1; i++){
      if (tmpval == i) {
        HSVtoRGB_GAMMA(hue_val,255,max_hell,tmp_c);  
      }else{
        tmp_c[0] = 0;
        tmp_c[1] = 0;
        tmp_c[2] = 0;
      }
      pixels_S1.setPixelColor(i,pixels_S1.Color(tmp_c[0], tmp_c[1], tmp_c[2]));
    }
    pixels_S1.show();
    tmpval = tmpval+1;
  }
}
