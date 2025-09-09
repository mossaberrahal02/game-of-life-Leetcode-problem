// // ./life width height iterations
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void error(char *message, int exit_)
{
    printf("%s\n", message);
    exit(exit_);
}


char **gameOfLife(char **board, int height, int width)
{
    char **muted = malloc(sizeof(char*) * (height + 1));
    muted[height] = NULL;
    for(int i = 0; i < width; i++)
    {
        muted[i] = malloc(sizeof(char) * (width + 1));
        muted[i][width] = '\0';
    }
    int nbr_neighbours = 0;
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            nbr_neighbours = 0;
            int memo[3][3] = {0};
            if (i - 1 >= 0 && j - 1 >= 0 && board[i - 1][j - 1] == '0')
                memo[0][0] = 1;
            if (i - 1 >= 0 && board[i - 1][j] == '0')
                memo[0][1] = 1;
            if (i - 1 >= 0 && j + 1 < width && board[i - 1][j + 1] == '0')
                memo[0][2] = 1;

            if (j - 1 >= 0 && board[i][j - 1] == '0')
                memo[1][0] = 1;
            if (j + 1 < width && board[i][j + 1] == '0')
                memo[1][2] = 1;

            if (i + 1 < height && j - 1 >= 0 && board[i + 1][j - 1] == '0')
                memo[2][0] = 1;
            if (i + 1 < height && board[i + 1][j] == '0')
                memo[2][1] = 1;
            if (i + 1 < height && j + 1 < width && board[i + 1][j + 1] == '0')
                memo[2][2] = 1;

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                    nbr_neighbours += memo[i][j];
            }

            if (board[i][j] == '0')
            {
                if (nbr_neighbours < 2 || nbr_neighbours > 3)
                    muted[i][j] = ' ';
                if (nbr_neighbours == 2 || nbr_neighbours == 3)
                    muted[i][j] = '0';
            }
            else if (board[i][j] == ' ')
            {
                if (nbr_neighbours == 3)
                    muted[i][j] = '0';
                else
                    muted[i][j] = ' ';
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            board[i][j] = muted[i][j];
    }
    for (int i = 0; i < height; i++)
        free(muted[i]);
    free(muted);
    // loop over board
    // for each element count its neightbours in memo[3][3]
    // claculate num of neighbours by looping over memo
    // 2 conditions one for alive cells the other for dead ones
    return(board);
}

int main(int ac, char **av)
{
    if (ac != 4) {
        error("Bad number of arguments", 1);
    }

    int width = atoi(av[1]);
    int height = atoi(av[2]);
    int iterations = atoi(av[3]);

    char ** board = malloc(sizeof(char*) * (height + 1));
    board[height] = NULL;
    int i = 0;
    while(i < width)
    {
        board[i] = malloc(sizeof(char) * (width + 1));
        board[i][width] = '\0';
        i++;
    }
    //fill with spaces the board
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            board[i][j] = ' ';
        }
    }
    int bytes = 0;
    char c;
    bytes = read(0, &c, 1);
    bool pen = false;
    int pen_i = 0;
    int pen_j = 0;

    while(bytes > 0)
    {
        if (pen == true)
            board[pen_i][pen_j] = '0';
        if(c == 's' && pen_i < (height - 1))
            pen_i++;
        else if (c == 'w' && pen_i > 0)
            pen_i--;
        else if(c == 'a' && pen_j > 0)
            pen_j--;
        else if(c == 'd' && pen_j < (width - 1))
            pen_j++;
        else if (c == 'x')
            pen = !pen;
        bytes = read(0, &c, 1);
    }
    while(iterations--)
        gameOfLife(board, height, width);
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    return 0;
}