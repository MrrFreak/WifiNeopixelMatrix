void Show_RGB(){
  if(actual_time > action_time){
    action_time = action_time + delayval;
    for(int i = 0; i < NUMPIXELS_S1; i++){
      pixels_S1.setPixelColor(i,pixels_S1.Color(r*max_hell/255, g*max_hell/255, b*max_hell/255));
    }
    pixels_S1.show();
  }
}
