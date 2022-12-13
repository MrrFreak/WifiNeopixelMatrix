void Show_PulsatingCircle(){
  int tmp_c[3];
  int hell;
  int something_changed = 0;
  double tmp_r;
  if(fixed_farbe == 0){
    if(actual_time > farb_action_time){
      farb_action_time = farb_action_time + farbdelayval;
      something_changed = 1;
      hue_val++;
      if(hue_val>359){
        hue_val = 0;
      }
    }
  }else{
    farb_action_time = actual_time;
  }
  if(actual_time > action_time){
    action_time = action_time + delayval;
    something_changed = 1;
    r_cursor = r_cursor + r_delta;
    if(r_cursor > (max(x_m,y_m)+rbreite)*1.41){
      r_cursor = 0.0;
    }
  }
  if(something_changed == 1){
    for(int i = 0; i < NUMPIXELS_S1; i++){
      tmp_r = sqrt(sq(S1_X[i]-x_m)+sq(S1_Y[i]-y_m));
      hell = max_hell-int(abs(tmp_r-r_cursor)*float(max_hell)/rbreite);
      if(hell<0){
        hell = 0;
      }else if(hell>max_hell){
        hell=max_hell;
      }
      HSVtoRGB_GAMMA(hue_val,255,hell,tmp_c);
      pixels_S1.setPixelColor(i,pixels_S1.Color(tmp_c[0], tmp_c[1], tmp_c[2]));
    }
    pixels_S1.show();
  }
}
