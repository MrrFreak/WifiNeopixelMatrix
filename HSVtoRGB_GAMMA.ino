void HSVtoRGB_GAMMA(int hue, int sat, int hell, int colors[3]){
  // hue: 0-359, sat: 0-255, val (lightness): 0-255
  HSVtoRGB(hue, sat, hell, colors);
  colors[0] = g8[colors[0]];
  colors[1] = g8[colors[1]];
  colors[2] = g8[colors[2]];
}
