#include <GLFW/glfw3.h>
#include <iostream>
#include <ctime>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int tilesize = 40;
int frames_since_last_moved = 0;
char board[20][10];
int red[3] = { 255, 0, 0 };
int blue[3] = { 255, 0, 0 };
int cyan[3] = { 0, 255, 255 };
int orange[3] = { 255, 153, 51 };
int yellow[3] = { 255, 255, 0 };
int green[3] = { 0, 255, 0 };
int purple[3] = { 153, 0, 255 };
bool live_piece = false;
int color_array[7] = { 'r', 'b', 'c', 'o', 'y', 'g', 'p' };
int score = 0;
int frame_count = 0;
int temp_frame = NULL;
int row_pushdown_limit = NULL;
static const int MAX_SCORE = 250;

bool left_key_pressed = false;
bool up_key_pressed = false;
bool right_key_pressed = false;
bool down_key_pressed = false;
bool solidify_next_frame = false;
bool live_piece_is_stable = false;
bool remove_layer = false;

void WriteLivePiecePosition(int* pointerToX, int* pointerToY)
{
    int* x = pointerToX;
    int* y = pointerToY;
    char compiledRow[20];
    char compiledColumn[10];
    for (int r = 0; r < 20; r++)
    {
        for (int c = 0; c < 10; c++)
        {
            if (board[r][c] == 'L')
            {

            }
        }
    }
}

bool is_static_piece(char piece)
{
    if (piece == NULL)
    {
        return false;
    }
    if (piece == 'L')
    {
        return false;
    }
    return true;
}

void keycallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    left_key_pressed = false;
    up_key_pressed = false;
    right_key_pressed = false;
    down_key_pressed = false;

    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    { 
        left_key_pressed = true;
        bool left_move_able = true;
        for (int row = 0; row < 20; row++)
        {
            for (int col = 1; col < 10; col++)
            {
                if (board[row][col] == 'L')
                {
                    if (board[row][col - 1] != NULL && board[row][col - 1] != 'L')
                    {
                        left_move_able = false;
                    }
                    
                }
                if (board[row][0] == 'L')
                {
                    left_move_able = false;
                }
            }
        }
        if (left_move_able)
        {
            for (int row = 19; row >= 0; row--)
            {
                for (int col = 1; col < 10; col++)
                {
                    if (board[row][col] == 'L')
                    {
                        board[row][col] = NULL;
                        board[row][col - 1] = 'L';
                    }
                }
            }
        }
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        right_key_pressed = true;
        bool right_move_able = true;
        for (int row = 0; row < 20; row++)
        {
            for (int col = 0; col < 9; col++)
            {
                if (board[row][col] == 'L')
                {
                    if (board[row][col + 1] != NULL && board[row][col + 1] != 'L')
                    {
                        right_move_able = false;
                    }

                }
                if (board[row][9] == 'L')
                {
                    right_move_able = false;
                }
            }
        }

        if (right_move_able)
        {
            for (int row = 19; row >= 0; row--)
            {
                for (int col = 8; col >= 0; col--)
                {
                    if (board[row][col] == 'L')
                    {
                        board[row][col] = NULL;
                        board[row][col + 1] = 'L';
                    }
                }
            }
        }
    }
    if (key == GLFW_KEY_UP)
    {
        up_key_pressed = true;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
        down_key_pressed = true;
        frames_since_last_moved = 60;
    }
}

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

double convert(double c, double d)
{
    double percentage = c / d * 2.0;
    return percentage;
}

void drawrect(int x, int y, int w, int h, int r, int g, int b)
{
    double realx = convert(x, 440) - 1;
    double realy = -convert(y, 800) + 1;
    double realw = convert(w, 440);
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

void drawProgressBar(int x, int y, int w, int h, double percentage, bool outline = true)
{
    drawrect(x, y, w, h, 255, 255, 255);
    drawrect(x + 1, y + 1, w - 2, h - 2, 0, 0, 0);
    drawrect(x + 1, y + h - 1, w - 2, -(h * percentage - 2), 255, 255, 255);
}

int main()
{
    srand(time(NULL));
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(440, 800, "Tetris Plus Plus", NULL, NULL);

    glfwSetKeyCallback(window, keycallback);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        live_piece = false;
        glClear(GL_COLOR_BUFFER_BIT);

        drawrect(0, 0, 400, 800, 0, 0, 0);
        drawProgressBar(400, 0, 40, 800, (double)((double)score/(double)MAX_SCORE));

        live_piece_is_stable = false;
        for (int j = 0; j < 20; j++)
        {
            row_pushdown_limit = j;
            remove_layer = true;
            for (int p = 0; p < 10; p++)
            {
                if (board[j][p] == NULL || board[j][p] == 'L')
                {
                    remove_layer = false;
                }
            }
            if (remove_layer)
            {
                if (score <= MAX_SCORE - 10)
                    score += 10;
                for (int p = 0; p < 10; p++)
                {
                    board[j][p] = NULL;

                }
                for (int k = j - 1; k >= 0; k--)
                {
                    for (int m = 0; m < 10; m++)
                    {
                        board[k + 1][m] = board[k][m];
                        board[k][m] = NULL;
                    }
                }
            }
            for (int i = 0; i < 10; i++)
            {
                if (board[j][i] != NULL)
                {
                    if (board[j][i] != 'L')
                    {
                        if (board[j][i] == 'r')
                        {
                            drawrect(i * tilesize, j * tilesize, tilesize, tilesize, red[0], red[1], red[2]);
                        }
                        if (board[j][i] == 'b')
                        {
                            drawrect(i * tilesize, j * tilesize, tilesize, tilesize, blue[0], blue[1], blue[2]);
                        }
                        if (board[j][i] == 'c')
                        {
                            drawrect(i * tilesize, j * tilesize, tilesize, tilesize, cyan[0], cyan[1], cyan[2]);
                        }
                        if (board[j][i] == 'o')
                        {
                            drawrect(i * tilesize, j * tilesize, tilesize, tilesize, orange[0], orange[1], orange[2]);
                        }
                        if (board[j][i] == 'y')
                        {
                            drawrect(i * tilesize, j * tilesize, tilesize, tilesize, yellow[0], yellow[1], yellow[2]);
                        }
                        if (board[j][i] == 'g')
                        {
                            drawrect(i * tilesize, j * tilesize, tilesize, tilesize, green[0], green[1], green[2]);
                        }
                        if (board[j][i] == 'p')
                        {
                            drawrect(i * tilesize, j * tilesize, tilesize, tilesize, purple[0], purple[1], purple[2]);
                        }
                    }
                    else
                    {
                        if (j == 19 || (board[j + 1][i] != 'L' && board[j+1][i] != NULL))
                        {
                            live_piece_is_stable = true;
                            solidify_next_frame = true;
                            if (temp_frame == NULL)
                            {
                                temp_frame = frame_count;
                            }
                            if (solidify_next_frame == true && frame_count - temp_frame >= 60)
                            {
                                live_piece = false;
                                int index = rand() % 7;
                                char choice = color_array[index];
                                for (int row = 19; row >= 0; row--)
                                {
                                    for (int col = 0; col < 10; col++)
                                    {
                                        if (board[row][col] == 'L')
                                        {
                                            board[row][col] = choice;
                                        }
                                    }
                                }
                                solidify_next_frame = false;
                                temp_frame = NULL;
                            }
                        }
                        else
                        {
                            live_piece = true;
                            if (frames_since_last_moved >= 60 && solidify_next_frame == false && !live_piece_is_stable)
                            {
                                frames_since_last_moved = 0;
                                for (int col = 0; col < 10; col++)
                                {
                                    for (int row = 19; row >= 0; row--)
                                    {
                                        if (row == 19)
                                        {
                                            continue;
                                        }
                                        if (board[row][col] == 'L')
                                        {
                                            board[row][col] = NULL;
                                            board[row + 1][col] = 'L';
                                        }
                                    }
                                }
                            }
                        }
                        drawrect(i * tilesize, j * tilesize, tilesize, tilesize, 255, 255, 255);
                    }
                }
            }
        }
        if (live_piece_is_stable == false)
        {
            solidify_next_frame = false;
            temp_frame = NULL;
        }

        if (live_piece == false)
        {
            frames_since_last_moved = 0;
            new_piece();
        }
        frames_since_last_moved += 1;
        frame_count += 1;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}