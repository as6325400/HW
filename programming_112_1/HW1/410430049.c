#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <ncurses.h>
#include <conio.h>

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

  return map;
  
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

  sleep(3213213);
}

int main(){
  while(1){
    int row, column;
    char **map, name[20];

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

    displayMap(map, row, column);


  }
}