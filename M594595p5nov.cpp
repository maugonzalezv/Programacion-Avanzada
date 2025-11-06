#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void limpiar() {
  for (int i = 0; i < 120; i++) cout << "\n";
}

void dibujar(char grid[][100], int w, int h, int* sx, int* sy, int len, int fx, int fy, int score, int seg) {
  limpiar();
  cout << "SNAKE " << w << "x" << h << "  Score: " << score << "  Seg: " << seg << "\n";
  for (int i = 0; i < w + 2; i++) cout << '#';
  cout << "\n";
  for (int y = 0; y < h; y++) {
    cout << '#';
    for (int x = 0; x < w; x++) {
      char c = grid[y][x];
      if (c == 0) cout << ' ';
      else cout << c;
    }
    cout << "#\n";
  }
  for (int i = 0; i < w + 2; i++) cout << '#';
  cout << "\n";
  cout << "W/A/S/D para girar. Q para salir.\n";
  cout.flush();
}

void limpiarGrid(char grid[][100], int w, int h) {
  for (int y = 0; y < h; y++)
    for (int x = 0; x < w; x++)
      grid[y][x] = 0;
}

void pintar(char grid[][100], int w, int h, int* sx, int* sy, int len, int fx, int fy) {
  limpiarGrid(grid, w, h);
  if (fx >= 0 && fy >= 0 && fx < w && fy < h) grid[fy][fx] = '*';
  for (int i = 1; i < len; i++) {
    int x = sx[i], y = sy[i];
    if (x >= 0 && x < w && y >= 0 && y < h) grid[y][x] = 'o';
  }
  if (sx[0] >= 0 && sx[0] < w && sy[0] >= 0 && sy[0] < h) grid[sy[0]][sx[0]] = 'O';
}

int celdaLibreParaComida(int* sx, int* sy, int len, int x, int y) {
  for (int i = 0; i < len; i++) if (sx[i] == x && sy[i] == y) return 0;
  return 1;
}

void colocarComida(int w, int h, int* sx, int* sy, int len, int& fx, int& fy) {
  for (int t = 0; t < 2000; t++) {
    int rx = rand() % w;
    int ry = rand() % h;
    if (celdaLibreParaComida(sx, sy, len, rx, ry)) {
      fx = rx; fy = ry;
      return;
    }
  }
}

int main() {
  // Habilitar lectura instantánea en macOS/Linux (sin Enter)
  // Ignorado si no existe 'stty' (por ejemplo, en Windows).
  system("stty -icanon -echo min 0 time 0");

  try {
    int w = 100;
    int h = 100;
    int maxn = w * h;
    if (maxn > 10000) { system("stty sane"); return 0; }

    int sx[10000];
    int sy[10000];
    int len = 3;

    int hx = w / 2;
    int hy = h / 2;
    sx[0] = hx; sy[0] = hy;
    sx[1] = hx - 1; sy[1] = hy;
    sx[2] = hx - 2; sy[2] = hy;

    int dx = 1, dy = 0;

    int foodAlive = 0;
    int fx = -1, fy = -1;
    int foodBornSec = -1000000;
    int spawnEverySec = 5;
    int foodLifetimeSec = 10;

    char grid[100][100];

    srand((unsigned)time(0));

    int score = 0;
    int alive = 1;
    int seg = 0;

    pintar(grid, w, h, sx, sy, len, fx, fy);
    dibujar(grid, w, h, sx, sy, len, fx, fy, score, seg);

    time_t t0 = time(0);

    while (alive) {
      while (cin.rdbuf()->in_avail() > 0) {
        char c;
        cin.get(c);
        if (c == 'q' || c == 'Q') { alive = 0; break; }
        int ndx = dx, ndy = dy;
        if (c=='w' || c=='W') { ndx = 0; ndy = -1; }
        if (c=='s' || c=='S') { ndx = 0; ndy =  1; }
        if (c=='a' || c=='A') { ndx = -1; ndy =  0; }
        if (c=='d' || c=='D') { ndx =  1; ndy =  0; }
        if (!(ndx == -dx && ndy == -dy)) { dx = ndx; dy = ndy; }
      }
      if (!alive) break;

      time_t t1 = time(0);
      if (t1 == t0) continue;
      t0 = t1;
      seg++;

      if (!foodAlive && (seg % spawnEverySec == 0)) {
        colocarComida(w, h, sx, sy, len, fx, fy);
        foodAlive = 1;
        foodBornSec = seg;
      }
      if (foodAlive && (seg - foodBornSec) >= foodLifetimeSec) {
        foodAlive = 0; fx = -1; fy = -1;
      }

      for (int i = len - 1; i >= 1; i--) {
        sx[i] = sx[i - 1];
        sy[i] = sy[i - 1];
      }
      sx[0] += dx;
      sy[0] += dy;

      if (sx[0] < 0 || sx[0] >= w || sy[0] < 0 || sy[0] >= h) alive = 0;

      if (alive) {
        for (int i = 1; i < len; i++) {
          if (sx[0] == sx[i] && sy[0] == sy[i]) { alive = 0; break; }
        }
      }

      if (alive && foodAlive && sx[0] == fx && sy[0] == fy) {
        score++;
        foodAlive = 0; fx = -1; fy = -1;
        if (len + 1 < maxn) {
          sx[len] = sx[len - 1];
          sy[len] = sy[len - 1];
          len++;
        }
      }

      pintar(grid, w, h, sx, sy, len, fx, fy);
      dibujar(grid, w, h, sx, sy, len, fx, fy, score, seg);
    }

    system("stty sane");
    cout << "\nGAME OVER  Score: " << score << "\n";
    return 0;
  } catch (...) {
    system("stty sane");
    cerr << "[ERROR]\n";
  }
  system("stty sane");
  return 0;
}
