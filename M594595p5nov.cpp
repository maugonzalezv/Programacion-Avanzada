// snake_mac.cpp  (macOS / terminal)
// WASD sin Enter, avance automático cada 1s, 100x100, comida cada 5s y expira a los 10s.
// Compila: clang++ -std=c++17 -O2 snake_mac.cpp -o snake_mac
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
using namespace std;

void cls() { cout << "\033[2J\033[H"; }

void pintar(char grid[][100], int w, int h, int* sx, int* sy, int len, int fx, int fy) {
  for (int y = 0; y < h; y++) for (int x = 0; x < w; x++) grid[y][x] = ' ';
  if (fx >= 0 && fy >= 0 && fx < w && fy < h) grid[fy][fx] = '*';
  for (int i = 1; i < len; i++) {
    int x = sx[i], y = sy[i];
    if (x >= 0 && x < w && y >= 0 && y < h) grid[y][x] = 'o';
  }
  if (sx[0] >= 0 && sx[0] < w && sy[0] >= 0 && sy[0] < h) grid[sy[0]][sx[0]] = 'O';
}

void dibujar(char grid[][100], int w, int h, int score, int seg) {
  cls();
  cout << "SNAKE " << w << "x" << h << "  Score: " << score << "  Seg: " << seg << "\n";
  for (int i = 0; i < w + 2; i++) cout << '#';
  cout << "\n";
  for (int y = 0; y < h; y++) {
    cout << '#';
    for (int x = 0; x < w; x++) cout << grid[y][x];
    cout << "#\n";
  }
  for (int i = 0; i < w + 2; i++) cout << '#';
  cout << "\nW/A/S/D para mover, Q para salir\n";
  cout.flush();
}

int libre(int* sx, int* sy, int len, int x, int y) {
  for (int i = 0; i < len; i++) if (sx[i] == x && sy[i] == y) return 0;
  return 1;
}

void comida(int w, int h, int* sx, int* sy, int len, int& fx, int& fy) {
  for (int t = 0; t < 5000; t++) {
    int rx = rand() % w, ry = rand() % h;
    if (libre(sx, sy, len, rx, ry)) { fx = rx; fy = ry; return; }
  }
}

void term_on(termios& oldt) {
  tcgetattr(0, &oldt);
  termios t = oldt;
  t.c_lflag &= ~(ICANON | ECHO);
  t.c_cc[VMIN] = 0;
  t.c_cc[VTIME] = 0;
  tcsetattr(0, TCSANOW, &t);
  int fl = fcntl(0, F_GETFL, 0);
  fcntl(0, F_SETFL, fl | O_NONBLOCK);
}

void term_off(termios& oldt) { tcsetattr(0, TCSANOW, &oldt); }

int main() {
  int w = 100, h = 100;
  if (w * h > 10000) return 0;

  int sx[10000], sy[10000], len = 3;
  int hx = w / 2, hy = h / 2;
  sx[0] = hx; sy[0] = hy;
  sx[1] = hx - 1; sy[1] = hy;
  sx[2] = hx - 2; sy[2] = hy;

  int dx = 1, dy = 0;

  int fx = -1, fy = -1, foodAlive = 0, foodBorn = -1000000;
  int spawnEvery = 5, foodLife = 10;

  char grid[100][100];
  srand((unsigned)time(0));

  int score = 0, alive = 1, seg = 0;

  pintar(grid, w, h, sx, sy, len, fx, fy);
  dibujar(grid, w, h, score, seg);

  termios oldt;
  term_on(oldt);

  while (alive) {
    fd_set r; FD_ZERO(&r); FD_SET(0, &r);
    timeval tv; tv.tv_sec = 1; tv.tv_usec = 0;
    int rv = select(1, &r, 0, 0, &tv);

    if (rv > 0 && FD_ISSET(0, &r)) {
      for (;;) {
        char c; ssize_t n = read(0, &c, 1);
        if (n <= 0) break;
        int ndx = dx, ndy = dy;
        if (c == 'q' || c == 'Q') { alive = 0; break; }
        if (c == 'w' || c == 'W') { ndx = 0; ndy = -1; }
        if (c == 's' || c == 'S') { ndx = 0; ndy =  1; }
        if (c == 'a' || c == 'A') { ndx = -1; ndy =  0; }
        if (c == 'd' || c == 'D') { ndx =  1; ndy =  0; }
        if (!(ndx == -dx && ndy == -dy)) { dx = ndx; dy = ndy; }
      }
    }
    if (!alive) break;

    seg++;

    if (!foodAlive && (seg % spawnEvery == 0)) { comida(w, h, sx, sy, len, fx, fy); foodAlive = 1; foodBorn = seg; }
    if (foodAlive && (seg - foodBorn) >= foodLife) { foodAlive = 0; fx = -1; fy = -1; }

    for (int i = len - 1; i >= 1; i--) { sx[i] = sx[i - 1]; sy[i] = sy[i - 1]; }
    sx[0] += dx; sy[0] += dy;

    if (sx[0] < 0 || sx[0] >= w || sy[0] < 0 || sy[0] >= h) alive = 0;

    if (alive) {
      for (int i = 1; i < len; i++) if (sx[0] == sx[i] && sy[0] == sy[i]) { alive = 0; break; }
    }

    if (alive && foodAlive && sx[0] == fx && sy[0] == fy) {
      score++; foodAlive = 0; fx = -1; fy = -1;
      if (len + 1 < w * h) { sx[len] = sx[len - 1]; sy[len] = sy[len - 1]; len++; }
    }

    pintar(grid, w, h, sx, sy, len, fx, fy);
    dibujar(grid, w, h, score, seg);
  }

  term_off(oldt);
  cout << "\nGAME OVER  Score: " << score << "\n";
  return 0;
}
