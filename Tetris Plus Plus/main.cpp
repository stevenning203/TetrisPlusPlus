#include <GLFW/glfw3.h>
#include <iostream>

int tilesize = 20;
int board[20][10];

class Piece
{
public:
    int shape;
};

Piece Ipiece, Lpiece, Opiece, Spiece, Tpiece;

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

int main(void)
{
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(400, 800, "Tetris Plus Plus", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT);

        drawrect(0, 0, 400, 800, 0, 0, 0);

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                if (board[j][i] != NULL)
                {
                    drawrect(j * tilesize, i * tilesize, tilesize, tilesize, 255, 255, 0);
                }
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}