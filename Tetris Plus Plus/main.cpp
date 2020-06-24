#include <GLFW/glfw3.h>
#include <iostream>
#include <ctime>

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

bool left_key_pressed = false;
bool up_key_pressed = false;
bool right_key_pressed = false;
bool down_key_pressed = false;

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
        bool left_move_able = false;
        for (int row = 0; row < 20; row++)
        {
            for (int col = 0; col < 10; row++)
            {
                if (board[row][col] == 'L')
                {

                }
            }
        }
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
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        right_key_pressed = true;

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
    if (new_piece_rand == 0)
    {
        board[0][4] = 'L';
        board[0][5] = 'L';
        board[1][4] = 'L';
        board[1][5] = 'L';
    }
    else if (new_piece_rand == 1)
    {
        board[0][4] = 'L';
        board[1][4] = 'L';
        board[2][4] = 'L';
        board[3][4] = 'L';
    }
    else if (new_piece_rand == 2)
    {
        board[0][4] = 'L';
        board[1][4] = 'L';
        board[1][5] = 'L';
        board[2][5] = 'L';
    }
}

double convert(double c, double d)
{
    double percentage = c / d * 2.0;
    return percentage;
}

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

int main()
{
    srand(time(NULL));
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(400, 800, "Tetris Plus Plus", NULL, NULL);

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

        for (int j = 0; j < 20; j++)
        {
            bool toggle = true;
            for (int p = 0; p < 10; p++)
            {
                if (board[j][p] == NULL || board[j][p] == 'L')
                {
                    toggle = false;
                }
            }
            if (toggle)
            {
                for (int p = 0; p < 10; p++)
                {
                    board[j][p] = NULL;
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
                        }
                        else
                        {
                            live_piece = true;
                            if (frames_since_last_moved == 60)
                            {
                                frames_since_last_moved = 0;
                                for (int row = 18; row >= 0; row--)
                                {
                                    for (int col = 0; col < 10; col++)
                                    {
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

        if (live_piece == false)
        {
            new_piece();
        }
        frames_since_last_moved += 1;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}