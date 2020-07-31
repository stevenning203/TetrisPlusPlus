# TetrisPlusPlus
Tetris made in C++ with OpenGL

## Workings
This version of "Tetris" uses a 2d array with each tile being a char. The renderer draws each letter as their corresponding colour as 4 verticies to produce a quadrilateral. 

```C++
char board[20][10];
```

To add a new "live" piece, 1 of 7 pieces are chosen and the corresponding tiles are changed into "L" tiles, which are "live" and fall every 60 frames.

```C++
void new_piece()
{
    int new_piece_rand = rand() % 7;
    if (new_piece_rand == 0) //square
    {
        board[0][4] = 'L';
        board[0][5] = 'L';
        board[1][4] = 'L';
        board[1][5] = 'L';
    }
    else if (new_piece_rand == 1) // I piece
    {
        board[0][4] = 'L';
        board[1][4] = 'L';
        board[2][4] = 'L';
        board[3][4] = 'L';
    }
    else if (new_piece_rand == 2) // S piece
    {
        board[0][4] = 'L';
        board[1][4] = 'L';
        board[1][5] = 'L';
        board[2][5] = 'L';
    }
    else if (new_piece_rand == 3) // Z piece
    {
        board[0][5] = 'L';
        board[1][5] = 'L';
        board[1][4] = 'L';
        board[2][4] = 'L';
    }
    else if (new_piece_rand == 4) // T piece
    {
        board[0][4] = 'L';
        board[1][4] = 'L';
        board[2][4] = 'L';
        board[1][5] = 'L';
    }
    else if (new_piece_rand == 5) // L reverse piece
    {
        board[0][4] = 'L';
        board[1][4] = 'L';
        board[2][4] = 'L';
        board[2][5] = 'L';
    }
    else if (new_piece_rand == 6) // L piece
    {
        board[0][5] = 'L';
        board[1][5] = 'L';
        board[2][5] = 'L';
        board[2][4] = 'L';
    }
}
```

Since OpenGL takes x and y arguments as a range of -1 to 1 instead of width/height, you have to convert x and y coordinates into the OpenGL format.

```C++
double convert(double c, double d)
{
    double percentage = c / d * 2.0;
    return percentage;
}
```

This allows us to draw rectangles with x and y coordinates.

```C++
void drawrect(int x, int y, int w, int h, int r, int g, int b)
{
    double realx = convert(x, 400) - 1;
    double realy = -convert(y, 800) + 1;
    double realw = convert(w, 400);
    double realh = convert(h, 800);

    double realr = r / 255;
    double realg = g / 255;
    double realb = b / 255;

    glBegin(GL_POLYGON);
    glColor3d(realr, realg, realb);
    glVertex2d(realx, realy);
    glVertex2d(realx + realw, realy);
    glVertex2d(realx + realw, realy - realh);
    glVertex2d(realx, realy - realh);
    glEnd();
}
```
