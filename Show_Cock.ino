void Show_Cock(){
  int tmp_c[3];
  int hell;
  int something_changed = 0;
  double tmp_r;
  
  double r1 = 20;
  double x_m1 = 120;
  double y_m1 = 110;
  
  double r2 = 20;
  double x_m2 = 120;
  double y_m2 = 50;
  
  double r3 = 18;
  double x_m3 = 30;
  double y_m3 = 80;
  
  double xa = x_m3;
  double xb = x_m3;
  double xc = x_m1;
  double xd = x_m1;
  
  double ya = y_m3-r3;
  double yb = y_m3+r3;
  double yc = yb;
  double yd = ya;

  double rbreite = 10;

  double ymm = (ya+yb)/2.0;
  double mm = (max_hell/rbreite)*(yb+rbreite-ymm);

  double p_lokal[2];
  double tmp_r1;
  double tmp_r2;
  double tmp_r3;
  double hell1;
  double hell2;
  double hell3;
  double hell4;

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
    phi_glb = phi_glb + 1;
    phi_glb = int(phi_glb)%359;
  }
  if(something_changed == 1){
    for(int i = 0; i < NUMPIXELS_S1; i++){ 
      p_lokal[0] = (S1_X[i]-x_m)*cos(phi_glb/180.0*PI)+(S1_Y[i]-y_m)*sin(phi_glb/180.0*PI)+x_m;
      p_lokal[1] = (S1_Y[i]-y_m)*cos(phi_glb/180.0*PI)-(S1_X[i]-x_m)*sin(phi_glb/180.0*PI)+y_m;
      // Ball 1
      tmp_r1 = sqrt(sq(p_lokal[0]-x_m1)+sq(p_lokal[1]-y_m1));
      hell1 = max_hell-int((tmp_r1-r1)*float(max_hell)/rbreite);
      if(hell1<0){
          hell1 = 0; 
      }else if(hell1>max_hell){
          hell1 = max_hell;
      }
      // Ball 2
      tmp_r2 = sqrt(sq(p_lokal[0]-x_m2)+sq(p_lokal[1]-y_m2));
      hell2 = max_hell-int((tmp_r2-r2)*float(max_hell)/rbreite);
      if(hell2<0){
          hell2 = 0; 
      }else if(hell2>max_hell){
          hell2 = max_hell;
      }
      // Tip
      tmp_r3 = sqrt(sq(p_lokal[0]-x_m3)+sq(p_lokal[1]-y_m3));
      hell3 = max_hell-int((tmp_r3-r3)*float(max_hell)/rbreite);
      if(hell3<0){
          hell3 = 0; 
      }else if(hell3>max_hell){
          hell3 = max_hell;
      }
      // Shaft
      if(p_lokal[0]<=xd and p_lokal[0]>=xa){
          hell4 = mm-abs(ymm-p_lokal[1])*(max_hell/rbreite);
          if(hell4<0){
              hell4 = 0;
          }else if(hell4>max_hell){
              hell4 = max_hell;
          }
      }else{
          hell4 = 0;
      }
      //
      hell = max(max(hell1,hell2),max(hell3,hell4));
      HSVtoRGB_GAMMA(hue_val,255,hell,tmp_c);
      pixels_S1.setPixelColor(i,pixels_S1.Color(tmp_c[0], tmp_c[1], tmp_c[2]));
    }
    pixels_S1.show();
  }
}
