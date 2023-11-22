#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <conio.h>

char name[20];

void clearTerminal(){
  printf("\x1B[2J\x1B[H");
}

void DisplayMenu(){
  printf("****Welcome to Sokoban Game****\n");
  printf("You can move the character up, down, left, and right through the direction keys\n");
  printf("\n");
  printf("Press any key to continue...");
  _getch();
  clearTerminal();
}

void DisplayNoSuchFile(){
  clearTerminal();
  printf("No such level found\n");
  printf("Press any key to continue...");
  _getch();
}

void displaySelectUI(){
  clearTerminal();
  printf("Select a play level:");
}

char **readGraph(char name[], int *row, int *column){
  char filename[20] = "map";
  strcat(filename, name);
  strcat(filename, ".txt");
  FILE *fp = fopen(filename, "r");
  if(fp == NULL){
    printf("%s\n", filename);
    return NULL;
  }

  fscanf(fp, "%d %d", row, column);
  char **map = (char**)malloc(sizeof(char*) * (*row));
  for(int i = 0; i < *row; i++){
    map[i] = malloc(sizeof(char) * (*column));
  }
  
  for(int i = 0; i < *row; i++){
    for(int j = 0; j < *column; j++){
      int num;
      fscanf(fp, "%d", &num);
      if(num == 0) map[i][j] = ' ';
      else if(num == 1) map[i][j] = 'W';
      else if(num == 2) map[i][j] = 'D';
      else if(num == 3) map[i][j] = 'o';
      else map[i][j] = 'P';
    }
  }

  fclose(fp);
  return map;
  
}

// up 0, left 1, right 2, down 3
bool changeMap(char **map, int row, int column, int mode){
  int direci[4] = {-1, 0, 0, 1};
  int direcj[4] = {0, -1, 1, 0};

  int pi, pj, newi, newj;
  for(int i = 0; i < row; i++){
    for(int j = 0; j < column; j++){
      if(map[i][j] == 'P'){
        pi = i;
        pj = j;
        break;
      }
      if(map[i][j] == 'p'){
        pi = i;
        pj = j;
        break;
      }
    }
  }

  newi = pi + direci[mode];
  newj = pj + direcj[mode];
  if(newi >= row || newi < 0 || newj >= column || newj < 0) return false;
  if(map[newi][newj] == ' ' || map[newi][newj] == 'o' || map[newi][newj] == 'D'){
    char origin = map[pi][pj];
    if(map[newi][newj] == ' '){
      map[newi][newj] = 'P';
      map[pi][pj] = ' ';
    }
    else if(map[newi][newj] == 'D'){
      map[pi][pj] = ' ';
      map[newi][newj] = 'p';
    }
    else{
      int newBoxi = newi + direci[mode], newBoxj = newj + direcj[mode];
      if(map[newBoxi][newBoxj] == ' ' || map[newBoxi][newBoxj] == 'D'){
        map[newi][newj] = 'P';
        map[pi][pj] = ' ';
        if(map[newBoxi][newBoxj] == 'D'){
          map[newBoxi][newBoxj] = 'X';
        }
        else{
          map[newBoxi][newBoxj] = 'o';
        }
      }
      else return false;
    }
    if(origin == 'p') map[pi][pj] = 'D';
  }
  else true;
}

bool newMap(char **map, int *row, int *column){
  char **newmap = readGraph(name, row, column);
  for(int i = 0; i < *row; i++){
    for(int j = 0; j < *column; j++){
      map[i][j] = newmap[i][j];
    }
  }
  return true;
}

void displayMap(char **map, int row, int column){
  clearTerminal();
  printf("Use the arrow keys to control the character\n");
  printf("Use the R button to restart this game\n");
  printf("\n");

  for(int i = 0; i < row; i++){
    for(int j = 0; j < column; j++){
      printf("%c", map[i][j]);
    }
    printf("\n");
  }
  char direction = _getch();

  if(direction == 72) changeMap(map, row, column, 0);
  if(direction == 80) changeMap(map, row, column, 3);
  if(direction == 75) changeMap(map, row, column, 1);
  if(direction == 77) changeMap(map, row, column, 2);
  if(direction == 'R') newMap(map, &row, &column);
}

bool judgeGame(char **map, int row, int column){
  for(int i = 0; i < row; i++){
    for(int j = 0; j < column; j++){
      if(map[i][j] == 'o') return false;
    }
  }
  return true;
}

void winGame(){
  printf("Congratulations on passing the level~\n");
}

bool replay(){
  while(1){
    printf("Do you want to continue playing?(Y/n)");
    char ch = _getch();
    if(ch == 'Y') return true;
    else if(ch == 'n') return false;
    printf("\n");
  }
  return false;
}

int main(){
  while(1){
    int row, column;
    char **map;

    DisplayMenu();

    while(1){


      displaySelectUI();
      scanf("%s", name);

      map = readGraph(name, &row, &column);

      if(map == NULL){
        DisplayNoSuchFile();
      }
      else{
        break;
      }
    }

    while(!judgeGame(map, row, column)){
      displayMap(map, row, column);
    }

    winGame();
    if(replay()){
      clearTerminal();
      continue;
    }
    else break;
  }
}