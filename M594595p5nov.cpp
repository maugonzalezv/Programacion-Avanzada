#include <ncurses.h>
#include <ctime>
#include <cstdlib>

void pintar(char grid[][100], int w, int h, int* sx, int* sy, int len, int fx, int fy) {
  for (int y=0;y<h;y++) for (int x=0;x<w;x++) grid[y][x]=0;
  if (fx>=0 && fy>=0 && fx<w && fy<h) grid[fy][fx]='*';
  for (int i=1;i<len;i++) { int x=sx[i], y=sy[i]; if (x>=0&&x<w&&y>=0&&y<h) grid[y][x]='o'; }
  if (sx[0]>=0&&sx[0]<w&&sy[0]>=0&&sy[0]<h) grid[sy[0]][sx[0]]='O';
}

void dibujar(WINDOW* win, char grid[][100], int w, int h, int score, int seg) {
  wclear(win);
  mvwprintw(win, 0, 0, "SNAKE %dx%d  Score: %d  Seg: %d", w, h, score, seg);
  for (int i=0;i<w+2;i++) mvwaddch(win, 1, i, '#');
  for (int y=0;y<h;y++) {
    mvwaddch(win, 2+y, 0, '#');
    for (int x=0;x<w;x++) {
      char c = grid[y][x];
      mvwaddch(win, 2+y, 1+x, c?c:' ');
    }
    mvwaddch(win, 2+y, 1+w, '#');
  }
  for (int i=0;i<w+2;i++) mvwaddch(win, 2+h, i, '#');
  mvwprintw(win, 3+h, 0, "W/A/S/D para girar. Q para salir");
  wrefresh(win);
}

int libre(int* sx,int* sy,int len,int x,int y){ for(int i=0;i<len;i++) if(sx[i]==x&&sy[i]==y) return 0; return 1; }

void comida(int w,int h,int* sx,int* sy,int len,int& fx,int& fy){
  for(int t=0;t<2000;t++){ int rx=rand()%w, ry=rand()%h; if(libre(sx,sy,len,rx,ry)){fx=rx;fy=ry;return;} }
}

int main(){
  int w=100, h=100;
  if (w*h>10000) return 0;

  initscr();
  noecho();
  curs_set(0);
  nodelay(stdscr, TRUE);   // getch() no bloquea (devuelve ERR si no hay tecla)
  keypad(stdscr, FALSE);

  int sx[10000], sy[10000], len=3;
  int hx=w/2, hy=h/2; sx[0]=hx; sy[0]=hy; sx[1]=hx-1; sy[1]=hy; sx[2]=hx-2; sy[2]=hy;
  int dx=1, dy=0;

  int foodAlive=0, fx=-1, fy=-1, foodBorn= -1000000;
  int spawnEach=5, foodLife=10;

  char grid[100][100];
  srand((unsigned)time(0));

  int score=0, alive=1, seg=0;
  pintar(grid,w,h,sx,sy,len,fx,fy);
  dibujar(stdscr,grid,w,h,score,seg);

  clock_t last = clock();

  while(alive){
    int ch = getch();
    if (ch!='\n' && ch!=ERR){
      if (ch=='q' || ch=='Q') break;
      int ndx=dx, ndy=dy;
      if (ch=='w' || ch=='W') { ndx=0; ndy=-1; }
      if (ch=='s' || ch=='S') { ndx=0; ndy= 1; }
      if (ch=='a' || ch=='A') { ndx=-1; ndy=0; }
      if (ch=='d' || ch=='D') { ndx= 1; ndy=0; }
      if (!(ndx==-dx && ndy==-dy)) { dx=ndx; dy=ndy; }
    }

    clock_t now = clock();
    if ((now - last) < CLOCKS_PER_SEC) continue;
    last = now; seg++;

    if (!foodAlive && (seg % spawnEach == 0)) { comida(w,h,sx,sy,len,fx,fy); foodAlive=1; foodBorn=seg; }
    if (foodAlive && (seg - foodBorn) >= foodLife) { foodAlive=0; fx=-1; fy=-1; }

    for(int i=len-1;i>=1;i--){ sx[i]=sx[i-1]; sy[i]=sy[i-1]; }
    sx[0]+=dx; sy[0]+=dy;

    if (sx[0]<0||sx[0]>=w||sy[0]<0||sy[0]>=h) alive=0;
    if (alive) for(int i=1;i<len;i++) if(sx[0]==sx[i]&&sy[0]==sy[i]) { alive=0; break; }

    if (alive && foodAlive && sx[0]==fx && sy[0]==fy){
      score++; foodAlive=0; fx=-1; fy=-1;
      if (len+1<w*h){ sx[len]=sx[len-1]; sy[len]=sy[len-1]; len++; }
    }

    pintar(grid,w,h,sx,sy,len,fx,fy);
    dibujar(stdscr,grid,w,h,score,seg);
  }

  endwin();
  printf("\nGAME OVER  Score: %d\n", score);
  return 0;
}
