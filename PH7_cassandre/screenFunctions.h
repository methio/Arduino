void clear_screen(){
  screen.fillScreen(0x0);
}


void welcome_screen(){
  // logo
  screen.drawBitmap(40, 0, image_logo_bits, 240, 240, 0x55E);
}

void drawloading(int posX) {
  // text
  screen.setTextColor(0x55E);
  screen.setTextSize(2);
  screen.setTextWrap(false);
  screen.setCursor(20, 23);
  screen.print("Veuillez patientez");
  screen.setCursor(20, 58);
  screen.print("Nous testons votre eau");
  // image
  screen.fillRect(0, 120, 320, 50, 0x0); // black overlay on wave top 
  screen.drawBitmap(posX, 3, image_vague_bits, 500, 240, 0x55E);
}


void drawresult_fail() {
  // result
  screen.setTextColor(0xF206);
  screen.setTextSize(3);
  screen.setTextWrap(false);
  screen.setCursor(99, 177);
  screen.print("Eau non");
  screen.setCursor(63, 206);
  screen.print("recommandee");

  // graph
  screen.setTextColor(0xFFFF);
  screen.setTextSize(2);
  screen.setCursor(29, 150);
  screen.print("Conductivite");

  screen.drawLine(20, 141, 289, 141, 0xFFFF);

  screen.setCursor(30, 119);
  screen.print("Temperature");

  screen.drawLine(20, 110, 289, 110, 0xFFFF);

  screen.setCursor(30, 88);
  screen.print("Turbidite");

  screen.drawLine(20, 78, 289, 78, 0xFFFF);

  screen.setCursor(30, 54);
  screen.print("PH");

  screen.fillCircle(276, 61, 12, 0xF206);
  screen.fillCircle(276, 94, 12, 0xF206);
  screen.fillCircle(276, 126, 12, 0xFE00);
  screen.fillCircle(276, 156, 12, 0xFE00);

  // title
  screen.setCursor(20, 20);
  screen.print("Vos resultats :");
}


void drawresult_ok() {
  screen.setTextColor(0x4D6A);
  screen.setTextSize(3);
  screen.setTextWrap(false);
  screen.setCursor(63, 188);
  screen.print("Eau potable");

  screen.setTextColor(0xFFFF);
  screen.setTextSize(2);
  screen.setCursor(29, 150);
  screen.print("Conductivite");

  screen.drawLine(20, 141, 289, 141, 0xFFFF);

  screen.setCursor(30, 119);
  screen.print("Temperature");

  screen.drawLine(20, 110, 289, 110, 0xFFFF);

  screen.setCursor(30, 88);
  screen.print("Turbidite");

  screen.drawLine(20, 78, 289, 78, 0xFFFF);

  screen.setCursor(30, 54);
  screen.print("PH");
  
  screen.fillCircle(276, 61, 12, 0x4D6A);
  screen.fillCircle(276, 94, 12, 0x4D6A);
  screen.fillCircle(276, 126, 12, 0x4D6A);
  screen.fillCircle(276, 156, 12, 0x4D6A);

  screen.setCursor(20, 20);
  screen.print("Vos resultats :");    
}