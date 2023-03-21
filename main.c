#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>

const int ROWS = 10;
const int COLS = 10;
const char BOUNDARY_SYMBOL[] = "##";
const char SNAKE_SYMBOL[] = "%%";

struct SnakeTile
{
  int x;
  int y;
};

void clear()
{
  printf("\033[H\033[J");
}

void goToXY(int x, int y)
{
  printf("\033[%d;%dH", y, x);
}

void drawBoundaries()
{
  for (int x = 1; x <= (COLS + 2) * 2; x += 2)
  {
    goToXY(x, 1);
    printf("%s", BOUNDARY_SYMBOL);
    goToXY(x, ROWS + 2);
    printf("%s", BOUNDARY_SYMBOL);
  }
  for (int y = 1; y <= ROWS + 2; y++)
  {
    goToXY(1, y);
    printf("%s", BOUNDARY_SYMBOL);
    goToXY((COLS + 2) * 2 - 1, y);
    printf("%s", BOUNDARY_SYMBOL);
  }
}

void draw(struct SnakeTile snake[])
{
  clear();
  drawBoundaries();

  for (int i = 0; i <= sizeof(snake) / sizeof(snake[0]); i++)
  {
    goToXY(snake[i].x * 2, snake[i].y);
    printf("%s", SNAKE_SYMBOL);
  }

  goToXY(0, ROWS + 3);
}

int main()
{
  setlocale(LC_ALL, "en_US.UTF-8");

  int run = 1;
  struct SnakeTile snake[] = {
      {.x = (int)(ROWS / 2), .y = (int)(COLS / 2)},
      {.x = (int)(ROWS / 2), .y = (int)(COLS / 2 + 1)},
      {.x = (int)(ROWS / 2), .y = (int)(COLS / 2 + 2)},
      {.x = (int)(ROWS / 2), .y = (int)(COLS / 2 + 3)},
  };
  int xVel = 0;
  int yVel = 0;

  draw(snake);
  while (run)
  {
    if (kbhit())
    {
      int c = getch();
      if ((c) == 27)
        run = 0;

      switch (c)
      {
      case 72: // up arrow
      case 'w':
        xVel = 0;
        yVel = -1;
        break;
      case 80: // down arrow
      case 's':
        xVel = 0;
        yVel = 1;
        break;
      case 75: // left arrow
      case 'a':
        xVel = -1;
        yVel = 0;
        break;
      case 77: // right arrow
      case 'd':
        xVel = 1;
        yVel = 0;
        break;
      }
    }

    for (int i = sizeof(snake) / sizeof(snake[0]) - 1; i > 0; i--)
    {
      snake[i].x = snake[i - 1].x;
      snake[i].y = snake[i - 1].y;
    }

    snake[0].x += xVel;
    snake[0].y += yVel;

    if (COLS + 1 < snake[0].x || snake[0].x < 1 || ROWS + 1 < snake[0].y || snake[0].y < 2)
    {
      printf("YOU LOSE! %d", snake[0].x);
      run = 0;
      break;
    }

    draw(snake);

    Sleep(150);
  }
  return 0;
}