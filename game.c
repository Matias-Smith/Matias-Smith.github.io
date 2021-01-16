#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>
#include<limits.h>


void movePlayer(int* nextXCharCoord, int* nextYCharCoord, int* xCharCoord, int* yCharCoord, char movingChar , int firstDim, int secondDim, char board[firstDim][secondDim])
{
        board[*yCharCoord][*xCharCoord] = ' ';
        *xCharCoord = *nextXCharCoord;
        *yCharCoord = *nextYCharCoord;
        board[*yCharCoord][*xCharCoord] = movingChar;
}


void printBoard(int firstDim, int secondDim, char board[firstDim][secondDim])
{
for (int i = 0; i < firstDim; ++i)
{
        for (int j = 0; j < secondDim; ++j)
        {
                printf("%c", board[i][j]);
                if (j == (secondDim - 1)) printf("\n");
        }
}
}


int playGame(const char* filename)
{


char* sleft;
char* sright;
char* sup;
char* sdown;
char* squit;
char left;
char right;
char up;
char down;
char quit;
int itemCounter = 0;
int itemsRemaining;
int score = 0;
char input;
int xCharCoord;
int yCharCoord;
int nextXCharCoord;
int nextYCharCoord;
int xItemCoord;
int yItemCoord;
char* scharacter;
char* spowerUp;
char* sitem;
char character;
char movingChar;
char powerUp;
char item;
int powerMovesLeft;


if (filename == NULL) return(0);
FILE* fp = fopen(filename, "r");   //Input File
char buf[100];
int lineCounter = 2;
fgets(buf, 100, fp);


int firstDim = atoi(strtok(buf, " ")) + 2;
int secondDim = atoi(strtok(NULL, "\n")) + 2;
char board[firstDim][secondDim];


for (int i = 0; i < firstDim; ++i)
{
        for (int j = 0; j < secondDim; ++j)
        {
                if ((i == 0) || (i == (firstDim -1)) || (j == 0) || (j == (secondDim -1)))
                {
                        board[i][j] = '*';
                }
                else board[i][j] = ' ';
        }
}


while (fgets(buf, 100, fp))
{
if (lineCounter == 2)
{
        sleft = strtok(buf, " ");
        if(strcmp(sleft, "\n") == 0)
        {
                left = 'a';
                right = 'd';
                up = 'w';
                down = 's';
                quit = 'q';
        }
        else
        {
                left = sleft[0];
                sright = strtok(NULL, " ");
                right = sright[0];
                sup = strtok(NULL, " ");
                up = sup[0];
                sdown = strtok(NULL, " ");
                down = sdown[0];
                squit = strtok(NULL, "\n");
                quit = squit[0];
        }


        ++lineCounter;
}
else if(lineCounter == 3)
{
        scharacter = strtok(buf, " ");
        character = scharacter[0];
        movingChar = character;
        spowerUp = strtok(NULL, " ");
        powerUp = spowerUp[0];
        yCharCoord = atoi(strtok(NULL, " ")) + 1;
        xCharCoord = atoi(strtok(NULL, "\n")) + 1;
        ++lineCounter;
        board[yCharCoord][xCharCoord] = movingChar;




}
else
{
        sitem = strtok(buf, " ");
        item = sitem[0];
        yItemCoord = atoi(strtok(NULL, " ")) + 1;
        xItemCoord = atoi(strtok(NULL, "\n")) + 1;
        if (item == 'B')
        {
                for (int i = 0;i < 6; ++i)
                {
                        for (int j = 0; j < 4; ++j)
                        {
                                if (((i==2) || (i==3)) && ((j==2) || (j==3))) board[yItemCoord+j][xItemCoord+i] = '&';
                                else board[yItemCoord+j][xItemCoord+i] = '-';
                        }
                }
        }
        else
        {
        if (item == 'E') item = 'X';
        else if (item == 'I')
        {
                item = '$';
                ++itemCounter;
        }
        else if (item == 'P') item = '*';
        board[yItemCoord][xItemCoord] = item;
        }
}
}
fclose(fp);
itemsRemaining = itemCounter;


while (movingChar != '@')
{
printf("Score: %d\nItems remaining: %d\n", score, itemsRemaining);
printBoard(firstDim, secondDim, board);
printf("Enter input: ");
scanf(" %c", &input);


while ((input != left) && (input != right) && (input != up) && (input != down) && (input !=quit))
{
        printf("Invalid input.\nEnter input: ");
        scanf(" %c", &input);
}
nextXCharCoord = xCharCoord;
nextYCharCoord = yCharCoord;


if (input == left) nextXCharCoord = xCharCoord - 1;
else if (input == right) nextXCharCoord = xCharCoord + 1;
else if (input == up) nextYCharCoord = yCharCoord - 1;
else if (input == down) nextYCharCoord = yCharCoord + 1;
else if (input == quit)
{
        printf("You have quit.\nFinal score: %d\n", score);
        return (1);
}


if (movingChar == powerUp)
{
        --powerMovesLeft;
        if (powerMovesLeft == 0) movingChar = character;
}


if ((nextXCharCoord != 0) && (nextXCharCoord != (secondDim -1)) && (nextYCharCoord != 0) && (nextYCharCoord != (firstDim - 1)) && (board[nextYCharCoord][nextXCharCoord] != '-') && (board[nextYCharCoord][nextXCharCoord] != '&'))
{


if (board[nextYCharCoord][nextXCharCoord] == '*')
{
        movingChar = powerUp;
        powerMovesLeft = 7;
}


else if (board[nextYCharCoord][nextXCharCoord] == '$')
{
        ++score;
        --itemsRemaining;
}
else if (board[nextYCharCoord][nextXCharCoord] == 'X')
{
        if (movingChar == character) movingChar = '@';
        else ++score;
}


movePlayer(&nextXCharCoord, &nextYCharCoord, &xCharCoord, &yCharCoord, movingChar, firstDim, secondDim, board);
}
else    
{
        nextXCharCoord = xCharCoord;
        nextYCharCoord = yCharCoord;
        movePlayer(&nextXCharCoord, &nextYCharCoord, &xCharCoord, &yCharCoord, movingChar, firstDim, secondDim, board);
} 


if (itemsRemaining == 0)
{
        printf("Congratulations! You have won.\nFinal score: %d\n", score);
        return (1);
}
}
printf("Score: %d\nItems remaining: %d\n", score, itemsRemaining);
printBoard(firstDim, secondDim, board);
printf("You have died.\nFinal score: %d\n", score);
return(1);
}