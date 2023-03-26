#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define WIDTH 20
#define HEIGHT 20

typedef struct Fruit
{
  int x, y;
} Fruit;

typedef struct SnakeSegment
{
  int x, y;
  struct SnakeSegment *next;
} SnakeSegment;

enum Direction
{
  STOP = 0,
  LEFT,
  RIGHT,
  UP,
  DOWN
};

SnakeSegment *head;
Fruit fruit;
enum Direction dir;

void GoToXY(int x, int y)
{
  printf("\033[%d;%dH", y, x);
}

void Setup()
{
  dir = STOP;

  head = malloc(sizeof(SnakeSegment));
  head->x = (int)(WIDTH / 2);
  head->y = (int)(HEIGHT / 2);
  head->next = NULL;

  fruit.x = rand() % (WIDTH - 1) + 1;
  fruit.y = rand() % (HEIGHT - 1) + 1;
}

void DrawBoundaries()
{
  for (int i = 0; i < WIDTH + 2; i++)
  {
    GoToXY(i, 0);
    printf("#");
  }

  for (int i = 1; i < HEIGHT + 1; i++)
  {
    GoToXY(0, i);
    printf("#");
    GoToXY(WIDTH + 1, i);
    printf("#");
  }

  for (int i = 0; i < WIDTH + 2; i++)
  {
    GoToXY(i, HEIGHT + 1);
    printf("#");
  }
}

void Draw()
{
  system("cls"); // clear the console

  DrawBoundaries();

  GoToXY(head->x + 1, head->y + 1);
  printf("O");

  GoToXY(fruit.x + 1, fruit.y + 1);
  printf("F");

  for (SnakeSegment *current = head->next; current != NULL; current = current->next)
  {
    GoToXY(current->x + 1, current->y + 1);
    printf("o");
  }
  GoToXY(0, HEIGHT + 2);
}

void Input()
{
  if (_kbhit())
  {
    switch (_getch())
    {
    case 'a':
      dir = LEFT;
      break;
    case 'd':
      dir = RIGHT;
      break;
    case 'w':
      dir = UP;
      break;
    case 's':
      dir = DOWN;
      break;
    case 'q':
      exit(0);
    }
  }
}

void Logic()
{
  int pX = head->x;
  int pY = head->y;
  for (SnakeSegment *current = head->next; current != NULL; current = current->next)
  {
    int tempX = current->x;
    int tempY = current->y;
    current->x = pX;
    current->y = pY;
    pX = tempX;
    pY = tempY;
  }

  switch (dir)
  {
  case LEFT:
    head->x--;
    break;
  case RIGHT:
    head->x++;
    break;
  case UP:
    head->y--;
    break;
  case DOWN:
    head->y++;
    break;
  default:
    break;
  }

  if (head->x >= WIDTH || head->x <= 0 || head->y >= HEIGHT || head->y <= 0)
    exit(0);

  for (SnakeSegment *current = head->next; current != NULL; current = current->next)
    if (current->x == head->x && current->y == head->y)
      exit(0);

  if (head->x == fruit.x && head->y == fruit.y)
  {
    fruit.x = rand() % (WIDTH - 1) + 1;
    fruit.y = rand() % (HEIGHT - 1) + 1;

    SnakeSegment *newSegment = malloc(sizeof(SnakeSegment));
    newSegment->next = NULL;

    SnakeSegment *current = head;
    while (current->next != NULL)
      current = current->next;

    current->next = newSegment;
  }
}

int main()
{
  srand(time(NULL)); // Seed rand function with current time
  Setup();

  while (1)
  {
    Draw();
    Input();
    Logic();
    Sleep(100);
  }

  return 0;
}