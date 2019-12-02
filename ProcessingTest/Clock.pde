float t = 0;
float w2 = TWO_PI / 3600;
float w3 = TWO_PI / -450;
float w4 = TWO_PI / 60;

void setup() {
  size(300, 200);
}

void draw() {
  background(255);
  noFill();
  
  // 2番車
  ellipse(100, 100, 100, 100);
  ellipse(100, 100, 10, 10);
  line(100 + 50 * cos(t * w2), 100 + 50 * sin(t * w2), 100, 100);
  
  // 3番車
  ellipse(155, 100, 80, 80);
  ellipse(155, 100, 10, 10);
  line(155 + 40 * cos(t * w3), 100 + 40 * sin(t * w3), 155, 100);
  
  // 4番車
  ellipse(200, 100, 75, 75);
  ellipse(200, 100, 10, 10);
  line(200 + 37.5 * cos(t * w4), 100 + 37.5 * sin(t * w4), 200, 100);
  
  t += 1 / frameRate * 60;
}
