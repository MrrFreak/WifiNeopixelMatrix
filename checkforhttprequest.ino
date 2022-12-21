void checkforhttprequest(){
    WiFiClient client = server.available();
  if (!client) {
    return;
  }
  // Der Teil unterhalb wird nur ausgeführt, wenn eine Neuer Client verbunden ist
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  
  // Rückgaben verarbeiten
  if (request.indexOf("/LED=DECREASE") != -1){
    delayval = delayval + 5;
  }
  if (request.indexOf("/LED=INCREASE") != -1){
    delayval = delayval - 5;
  }
  if (request.indexOf("/LED=FARBDECREASE") != -1){
    farbdelayval = farbdelayval + 5;
  }
  if (request.indexOf("/LED=FARBINCREASE") != -1){
    farbdelayval = farbdelayval - 5;
  }
  if (request.indexOf("/LED=PRESET01") != -1){
    fixed_farbe = 1;
    hue_val = 36;
    xbreite = 2000;
    delayval = 80;
    modus = 5;
    eeAddress = 1*sizeof(int)+0*sizeof(double);
    EEPROM.put(eeAddress,modus);
    eeAddress = 3*sizeof(int)+2*sizeof(double);
    EEPROM.put(eeAddress,delayval);
    eeAddress = 3*sizeof(int)+0*sizeof(double);
    EEPROM.put(eeAddress,xbreite);
    eeAddress = 0*sizeof(int)+0*sizeof(double);
    EEPROM.put(eeAddress,hue_val);
    eeAddress = 2*sizeof(int)+0*sizeof(double);
    EEPROM.put(eeAddress,fixed_farbe);
    EEPROM.commit(); 
  }
  if (request.indexOf("/LED=FIXCOLOR") != -1){
    if(fixed_farbe == 0){
      fixed_farbe = 1;
    }else{
      fixed_farbe = 0;
    }
    eeAddress = 2*sizeof(int)+0*sizeof(double);
    EEPROM.put(eeAddress,fixed_farbe);
    EEPROM.commit(); 
  }
  if (request.indexOf("/LED=RED") != -1){
    tmpval = request.substring(request.indexOf("/LED=RED")+8,request.indexOf("/LED=RED")+11).toInt();
    if( tmpval >= 0 and tmpval < 256){
      r = tmpval;
      eeAddress = 4*sizeof(int)+4*sizeof(double)+2*sizeof(unsigned long);
      EEPROM.put(eeAddress,r);
      EEPROM.commit(); 
    }
  }
  if (request.indexOf("/LED=GREEN") != -1){
    tmpval = request.substring(request.indexOf("/LED=GREEN")+10,request.indexOf("/LED=GREEN")+13).toInt();
    if( tmpval >= 0 and tmpval < 256){
      g = tmpval;
      eeAddress = 5*sizeof(int)+4*sizeof(double)+2*sizeof(unsigned long);
      EEPROM.put(eeAddress,g);
      EEPROM.commit(); 
    }
  }
  if (request.indexOf("/LED=BLUE") != -1){
    tmpval = request.substring(request.indexOf("/LED=BLUE")+9,request.indexOf("/LED=BLUE")+12).toInt();
    if( tmpval >= 0 and tmpval < 256){
      b = tmpval;
      eeAddress = 6*sizeof(int)+4*sizeof(double)+2*sizeof(unsigned long);
      EEPROM.put(eeAddress,b);
      EEPROM.commit(); 
    }
  }
  if (request.indexOf("/LED=WHITE") != -1){
    tmpval = request.substring(request.indexOf("/LED=WHITE")+10,request.indexOf("/LED=WHITE")+13).toInt();
    if( tmpval >= 0 and tmpval < 256){
      w = tmpval;
      eeAddress = 7*sizeof(int)+4*sizeof(double)+2*sizeof(unsigned long);
      EEPROM.put(eeAddress,w);
      EEPROM.commit(); 
    }
  }
  if (request.indexOf("/LED=MODE") != -1){
    tmpval = request.substring(request.indexOf("/LED=MODE")+9,request.indexOf("/LED=MODE")+11).toInt();
    if( tmpval >= 0 and tmpval < 100){
      modus = tmpval;
      eeAddress = 1*sizeof(int)+0*sizeof(double);
      EEPROM.put(eeAddress,modus);
      EEPROM.commit(); 
    }
  }
  if (request.indexOf("/LED=HUE") != -1){
    tmpval = request.substring(request.indexOf("/LED=HUE")+8,request.indexOf("/LED=HUE")+11).toInt();
    if( tmpval >= 0 and tmpval < 359){
      hue_val = tmpval;
      eeAddress = 0*sizeof(int)+0*sizeof(double);
      EEPROM.put(eeAddress,hue_val);
      EEPROM.commit(); 
    }
  }
  if (request.indexOf("/LED=XBREITE") != -1){
    tmpval = request.substring(request.indexOf("/LED=XBREITE")+12,request.indexOf("/LED=XBREITE")+16).toInt();
    if( tmpval >= 0 and tmpval < 9999){
      xbreite = tmpval;
      eeAddress = 3*sizeof(int)+0*sizeof(double);
      EEPROM.put(eeAddress,xbreite);
      EEPROM.commit(); 
    }
  }
  if (request.indexOf("/LED=YBREITE") != -1){
    tmpval = request.substring(request.indexOf("/LED=YBREITE")+12,request.indexOf("/LED=YBREITE")+16).toInt();
    if( tmpval >= 0 and tmpval < 9999){
      ybreite = tmpval;
      eeAddress = 3*sizeof(int)+1*sizeof(double);
      EEPROM.put(eeAddress,ybreite);
      EEPROM.commit(); 
    }
  }
  if (request.indexOf("/LED=DELAY") != -1){
    tmpval = request.substring(request.indexOf("/LED=DELAY")+10,request.indexOf("/LED=DELAY")+13).toInt();
    if( tmpval >= 0 and tmpval < 999){
      delayval = tmpval;
      eeAddress = 3*sizeof(int)+2*sizeof(double);
      EEPROM.put(eeAddress,delayval);
      EEPROM.commit();
    }
  }
  if (request.indexOf("/LED=FARBDELAY") != -1){
    tmpval = request.substring(request.indexOf("/LED=FARBDELAY")+14,request.indexOf("/LED=FARBDELAY")+17).toInt();
    if( tmpval >= 0 and tmpval < 999){
      farbdelayval = tmpval;
      eeAddress = 3*sizeof(int)+2*sizeof(double)+1*sizeof(unsigned long);
      EEPROM.put(eeAddress,farbdelayval);
      EEPROM.commit();
    }
  }
  if (request.indexOf("/LED=RBREITE") != -1){
    tmpval = request.substring(request.indexOf("/LED=RBREITE")+12,request.indexOf("/LED=RBREITE")+16).toInt();
    if( tmpval >= 0 and tmpval < 9999){
      rbreite = tmpval;
      eeAddress = 3*sizeof(int)+2*sizeof(double)+2*sizeof(unsigned long);
      EEPROM.put(eeAddress,rbreite);
      EEPROM.commit();
    }
  }
  if (request.indexOf("/LED=RDELTA") != -1){
    tmpval = request.substring(request.indexOf("/LED=RDELTA")+11,request.indexOf("/LED=RDELTA")+15).toInt();
    if( tmpval >= 0 and tmpval < 9999){
      r_delta = tmpval;
      eeAddress = 3*sizeof(int)+3*sizeof(double)+2*sizeof(unsigned long);
      EEPROM.put(eeAddress,r_delta);
      EEPROM.commit();
    }
  }
  if (request.indexOf("/LED=MAXHELL") != -1){
    tmpval = request.substring(request.indexOf("/LED=MAXHELL")+12,request.indexOf("/LED=MAXHELL")+15).toInt();
    if( tmpval >= 0 and tmpval < 256){
      max_hell = tmpval;
      eeAddress = 3*sizeof(int)+4*sizeof(double)+2*sizeof(unsigned long);
      EEPROM.put(eeAddress,max_hell);
      EEPROM.commit();
    }
  }
  if (request.indexOf("/LED=MINHELL") != -1){
    tmpval = request.substring(request.indexOf("/LED=MINHELL")+12,request.indexOf("/LED=MINHELL")+15).toInt();
    if( tmpval >= 0 and tmpval < 256){
      min_hell = tmpval;
      eeAddress = 8*sizeof(int)+4*sizeof(double)+2*sizeof(unsigned long);
      EEPROM.put(eeAddress,min_hell);
      EEPROM.commit();
    }
  }
  if (request.indexOf("/LED=DELTAHUE") != -1){
    tmpval = request.substring(request.indexOf("/LED=DELTAHUE")+13,request.indexOf("/LED=DELTAHUE")+16).toInt();
    if( tmpval >= 0 and tmpval < 359){
      delta_hue = tmpval;
      eeAddress = 9*sizeof(int)+4*sizeof(double)+2*sizeof(unsigned long);
      EEPROM.put(eeAddress,delta_hue);
      EEPROM.commit();
    }
  }
  
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  
  client.print("/LED=MODE00 is: ");
  client.print(modus);
  client.println("<br>");
  client.print("/LED=DELAY000 is: ");
  client.print(delayval);
  client.println("<br>");
  client.print("/LED=FARBDELAY000 is: ");
  client.print(farbdelayval);
  client.println("<br>");
  client.print("Fixcolor is: ");
  client.print(fixed_farbe);
  client.println("<br>");
  client.print("/LED=XBREITE0000 is: ");
  client.print(xbreite);
  client.println("<br>");
  client.print("/LED=YBREITE0000 is: ");
  client.print(ybreite);
  client.println("<br>");
  client.print("/LED=HUE000 is: ");
  client.print(hue_val);
  client.println("<br>");
  client.print("/LED=DELTAHUE000 is: ");
  client.print(delta_hue);
  client.println("<br>");
  client.print("/LED=RBREITE0000 is: ");
  client.print(rbreite);
  client.println("<br>");
  client.print("/LED=RDELTA0000 is: ");
  client.print(r_delta);
  client.println("<br>");
  client.print("/LED=MAXHELL000 is: ");
  client.print(max_hell);
  client.println("<br>");
  client.print("/LED=MINHELL000 is: ");
  client.print(min_hell);
  client.println("<br>");
  client.print("/LED=RED000 is: ");
  client.print(r);
  client.println("<br>");
  client.print("/LED=GREEN000 is: ");
  client.print(g);
  client.println("<br>");
  client.print("/LED=BLUE000 is: ");
  client.print(b);
  client.println("<br>");
  client.print("/LED=WHITE000 is: ");
  client.print(w);
  

  client.println("<br><br>");
  client.println("Click <a href=\"/LED=INCREASE\">here</a> increase runlite speed<br>");
  client.println("Click <a href=\"/LED=DECREASE\">here</a> decrease runlite speed<br>");
  client.println("Click <a href=\"/LED=FARBINCREASE\">here</a> increase farb speed<br>");
  client.println("Click <a href=\"/LED=FARBDECREASE\">here</a> decrease farb speed<br>");
  client.println("Click <a href=\"/LED=FIXCOLOR\">here</a> fix or unfix color<br>");
  client.println("<br>");
  client.println("Click <a href=\"/LED=MODE00\">here</a> RGB Farbe<br>");
  client.println("Click <a href=\"/LED=MODE01\">here</a> HUE Farbe<br>");
  client.println("Click <a href=\"/LED=MODE02\">here</a> Rainbow Run<br>");
  client.println("Click <a href=\"/LED=MODE03\">here</a> Moving Dot<br>");
  client.println("Click <a href=\"/LED=MODE04\">here</a> Pulsating Circle<br>");
  client.println("Click <a href=\"/LED=MODE05\">here</a> Rotating Cock<br>");
  client.println("</html>");
  
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
