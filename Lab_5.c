//
// Created by Great_Society on 18.11.2020.
//
//В головном модуле объявить n матриц. Элементами матрицы
//являются строки знаков. Все строки и столбцы матрицы, в которых хотя бы
//один из ее элементов совпадают со строкой введенной из клавиатуры, удалить.
//Полученную матрицу уплотнить. Память под матрицы выделять динамически.
//Программу разбить на функции.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

/* К сожалению, сначала я стал писать всю программу в функиции main(),при этом
 * решив, что реализация n-матриц в матрице указателей - хорошая идея. Я до сих пор так считаю, однако
 * у меня есть проблема c тем как эту (или ее часть) матрицу передать в функцию поиска-замены,
 * исполнив в функции тот же алгоритм,что и сейчас.
 * Я не придумал как это сделать, не вводя агромное количество аргументов для функции,
 * и не переписывая код заново. Пока (!)
 * Поэтому пока я ограничился лишь одной функцией и прототипами тех, которые могли бы быть, не будь я таким дураком*/

// Функция оставляет только уникальные буквы в вводимой пользователем строке.
char* characterStringUnique (char *inputString, char*pOutString){

    int flag;
    int writeCounter = 0;
    for(int ctr = 0; ctr < strlen(inputString);ctr++){
        flag = 0;
        if (isalpha(inputString[ctr])){
            if (strlen(pOutString)){
                for (int dctr = 0; dctr <strlen(pOutString);dctr++){
                    if (toupper(inputString[ctr]) == toupper(pOutString[dctr])){
                        flag = 1;
                        break;
                    }
                }
            }
            if (flag == 0){
                pOutString[writeCounter]= inputString[ctr];
                writeCounter++;
            }
        }
    }

    return pOutString;
}

char functionThatCouldBe(int raws, int columns);

char functionThatCouldBe_1(char putString, int raws,int columns, char Massive[raws][columns]);

int main(){

    char *pUserString = malloc(256);
    char *pOutString = malloc(256);
    int matrix, rows, columns, x, z, i, j;
    time_t seed;

    fgets(pUserString,256,stdin);

    characterStringUnique(pUserString,pOutString);

    puts(pUserString);
    puts(pOutString);

    matrix = 5;
    puts("Please input a number of matrix:");
    scanf("%d",&matrix);


    rows = 4;
    puts("Please input a number of rows:");
    scanf("%d",&rows);


    columns = 3;
    puts("Please input a number of columns:");
    scanf("%d",&columns);


    char *arrayOfMatrix[matrix][rows];
    srand(time(&seed));

    for (z = 0; z < matrix; z++){
        for ( i = 0; i < rows; i++){
            arrayOfMatrix[z][i] = malloc(columns*sizeof(char));
            for ( j = 0; j < columns; ++j) {
                x = rand()%2;
                arrayOfMatrix[z][i][j] = x?(rand()%('Z' - 'A'+1) + 'A'):(rand()%('z' - 'a'+1) + 'a');
            }
        }
    }

    putchar('\n');
    printf ("This is random Matrix: \n"); // Печать рандомной матрицы с заданными параметрами.

    for ( z = 0; z < matrix; z++,putchar('\n')){
        for ( i = 0; i < rows; i++, putchar('\n')){
            for ( j = 0; j < columns; ++j) {
                printf(" %c ", arrayOfMatrix[z][i][j]);
            }
        }
    } // func 2

    int *dataPrint[matrix];
    for(int dP = 0; dP < matrix;dP++){
        dataPrint[dP] = (int*) malloc(2*sizeof(int));
    }
    int flagOf;
    int stringCounter;
    int cRows,cColumns;
    for (z = 0; z < matrix; z++){
        cRows = rows;
        cColumns = columns;
        for (i = 0; i < cRows; i++){
            for (j = 0; j < cColumns; ++j) {
                flagOf = 0;
                for (stringCounter=0;stringCounter < strlen(pOutString); stringCounter++){
                    if (toupper(arrayOfMatrix[z][i][j]) == toupper(pOutString[stringCounter])){
                        flagOf = 1;
                        break;
                    }
                }
                if (flagOf == 1){
                    for(int cI = 0; cI < cRows; cI++){
                        for (int cJ = j; cJ <= (cColumns-1); cJ++ ) {
                            if(cJ==(cColumns-1)){
                                arrayOfMatrix[z][cI][cJ] = 0;
                            }
                            arrayOfMatrix[z][cI][cJ] = arrayOfMatrix[z][cI][cJ+1];
                        }
                    }
                    --cColumns;
                    for (int cI = i; cI <= (cRows-1); cI++){
                        if(cI==(cRows-1)){
                            arrayOfMatrix[z][cI] = 0;
                        }
                        arrayOfMatrix[z][cI] = arrayOfMatrix[z][cI+1];
                    }
                    --cRows;
                    --i;
                }
            }
            if (i == (cRows-1)){
                dataPrint[z][0] = cRows;
                dataPrint[z][1] = cColumns;
            }
        }
    }

    putchar('\n');
    printf ("This is searched Matrix: \n");

    int printRows;
    int printColumns;

    for (z = 0; z < matrix; z++,putchar('\n')){
        printRows = dataPrint [z][0];
        for (i = 0; i < printRows; i++, putchar('\n')){
            printColumns = dataPrint[z][1];
            for (j = 0; j < printColumns; ++j) {
                printf(" %c ", arrayOfMatrix[z][i][j]);
            }
        }
    }

   /* for (z = 0; z < matrix; z++){
        for (i = 0; i < rows; i++){
            free(arrayOfMatrix[z][i]);
        }
    }

    for(int dP = 0; dP < 2;dP++){
        free(dataPrint[dP]);
    }

    free(pUserString);
    free(pOutString);*/
    return 0;
}
