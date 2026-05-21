#include <GL/glut.h>
#include <cmath>
using namespace std;
int width = 1440;
int height = 1024;

int currentScenario = 1;
float planeX = 600;
float planeY = 900;
float planeSpeed = 2.0;
bool isNight = false;

// height from bottom
int grass = 120;
int roadBorder = 20;
int road = 400;
int ground = 80;

// for moving object
float cloudX = 0;

// Car movement
float carX = 60;
float carSpeed = 10;

// Bus movement
float busX = 400;
float busSpeed = 2;
// scene 2
// Large ship
float largeShipX = -400;
float cruiseShipSpeed = 0.8;

// Small fishing boat
float smallBoatX = 1440;
float fishingBoatSpeed = 0.5;

// Cargo boat
float cargoBoatX = 1600;
float cargoBoatSpeed = 1;

// Clouds
float cloud1X = 0;
float cloud2X = 500;
float cloud3X = 1000;
float cloudSpeed = 1;


void drawBackground()
{
    glClear(GL_COLOR_BUFFER_BIT);

    int y = 0;

    // sky
    glBegin(GL_QUADS);
    if (isNight)
        glColor3f(0.05, 0.05, 0.15);
    else
        glColor3f(0.7, 0.9, 1.0);

    glVertex2f(0, y);
    glVertex2f(width, y);
    glVertex2f(width, height);
    glVertex2f(0, height);
    glEnd();

    //int y = 0;

    // grass
    glBegin(GL_QUADS);
    if (isNight)
        glColor3f(0.0, 0.2, 0.0);
    else
        glColor3f(0.2, 0.8, 0.2);
    glVertex2f(0, y);
    glVertex2f(width, y);
    glVertex2f(width, y + grass);
    glVertex2f(0, y + grass);
    glEnd();

    y = y + grass;

    // bottom border
    int tile = 250;
    for(int i = 0; i < 1440; i += tile)
    {

        // yellow block
        glBegin(GL_QUADS);
        glColor3f(1,1,0);
        glVertex2f(i, y);
        glVertex2f(i + tile/2, y);
        glVertex2f(i + tile/2, y + 20);
        glVertex2f(i, y + 20);
        glEnd();

        // white block
        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex2f(i + tile/2, y);
        glVertex2f(i + tile, y);
        glVertex2f(i + tile, y + 20);
        glVertex2f(i + tile/2, y + 20);
        glEnd();
    }

    y = y + roadBorder;

    // road
    glBegin(GL_QUADS);
    glColor3f(0.27, 0.28, 0.29);
    glVertex2f(0, y);
    glVertex2f(width, y);
    glVertex2f(width, y + road);
    glVertex2f(0, y + road);
    glEnd();

    // middle line
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    for(int i = 20; i < width; i += 100)
    {
        glVertex2f(i, y + road/2);
        glVertex2f(i + 40, y + road/2);
    }
    glEnd();

    y = y + road;

    // top border
    tile = 250;
    for(int i = 0; i < 1440; i += tile)
    {

        // yellow block
        glBegin(GL_QUADS);
        glColor3f(1,1,0);
        glVertex2f(i, y);
        glVertex2f(i + tile/2, y);
        glVertex2f(i + tile/2, y + 20);
        glVertex2f(i, y + 20);
        glEnd();

        // white block
        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex2f(i + tile/2, y);
        glVertex2f(i + tile, y);
        glVertex2f(i + tile, y + 20);
        glVertex2f(i + tile/2, y + 20);
        glEnd();
    }

    y = y + roadBorder;

    // upper ground
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.6, 0.2);
    glVertex2f(0, y);
    glVertex2f(width, y);
    glVertex2f(width, y + ground);
    glVertex2f(0, y + ground);
    glEnd();

    y = y + ground;

    glBegin(GL_QUADS);
    glColor3f(0.8, 0.6, 0.6);
    glVertex2f(0, y);
    glVertex2f(width, y);
    glVertex2f(width, y + 40);
    glVertex2f(0, y + 40);
    glEnd();
}

void drawCircle(float cx, float cy, float r)
{
    glBegin(GL_POLYGON);
    for(int i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416 * i / 100;
        float x = r * cos(angle);
        float y = r * sin(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawEllipse(float cx, float cy, float rx, float ry)
{
    glBegin(GL_POLYGON);
    for(int i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416 * i / 100;

        float x = rx * cos(angle);
        float y = ry * sin(angle);

        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawCloud(float x, float y)
{
    glColor3f(1,1,1);

    drawCircle(x, y, 30);           // left
    drawCircle(x+30, y+15, 30);     // upper-left
    drawCircle(x+60, y+10, 30);     // top-middle
    drawCircle(x+90, y, 30);        // right
    drawCircle(x+60, y-15, 30);     // lower-right
    drawCircle(x+30, y-10, 30);     // lower-left
}

void drawBuilding(float x, float y)
{
    float w = 97;
    float h = 184;

    // body
    glBegin(GL_QUADS);
    glVertex2f(x,y);
    glVertex2f(x+w,y);
    glVertex2f(x+w,y-h);
    glVertex2f(x,y-h);
    glEnd();

    // top
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.8, 0.8);
    glVertex2f(x-2, y);
    glVertex2f(x-2, y+6);
    glVertex2f(x+w+2, y+6);
    glVertex2f(x+w+2, y);
    glEnd();

    float wy = y - 25;

    // windows
    for(int i = 0; i < 5; i++)
    {
        float wx = x + 7;

        for (int j = 0; j < 2; j++)
        {
            glBegin(GL_POLYGON);
            if (!isNight)
                glColor3f(0.8,0.8,0.8);
            else
                glColor3f(1, 1, 0);
            glVertex2f(wx, wy);
            glVertex2f(wx+11, wy);
            glVertex2f(wx+11, wy+15);
            glVertex2f(wx, wy+15);
            glEnd();

            wx += 21;
        }
        wy -= 27;
    }

    wy = y - 25;
    for(int i = 0; i < 5; i++)
    {
        float wx = x + 59;

        for (int j = 0; j < 2; j++)
        {
            glBegin(GL_POLYGON);
            if (!isNight)
                glColor3f(0.8,0.8,0.8);
            else
                glColor3f(1, 1, 0);
            glVertex2f(wx, wy);
            glVertex2f(wx+11, wy);
            glVertex2f(wx+11, wy+15);
            glVertex2f(wx, wy+15);
            glEnd();

            wx += 21;
        }
        wy -= 27;
    }

    // door
    glBegin(GL_QUADS);
    if (!isNight)
        glColor3f(0.8,0.8,0.8);
    else
        glColor3f(1, 1, 0);
    glVertex2f(x+36 , y-h);
    glVertex2f(x+36, y-h+35);
    glVertex2f(x+61, y-h+35);
    glVertex2f(x+61, y-h);
    glEnd();

    //middle line
    glBegin(GL_LINES);
    glLineWidth(4);
    if (!isNight)
        glColor3f(0.8,0.8,0.8);
    else
        glColor3f(1, 1, 0);
    glVertex2f(x+48.5, y-160);
    glVertex2f(x+48.5, y-7);
    glEnd();
}

void drawPlane(float x, float y)
{
    // head
    glColor3f(0.9, 0.9, 0.9);
    drawEllipse(x-10, y-5, 20, 15);
    drawCircle(x, y, 20);


    // back circle
    glColor3f(0.9, 0.9, 0.9);
    drawCircle(x+152, y, 20);

    // main body
    glColor3f(0.9, 0.9, 0.9);
    glBegin(GL_QUADS);
    glVertex2f(x, y-20);
    glVertex2f(x+150, y-20);
    glVertex2f(x+150, y+20);
    glVertex2f(x, y+20);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(x+15, y+20);
    glVertex2f(x+15, y-20);
    glEnd();

    // door
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(x+20, y+15);
    glVertex2f(x+30, y+15);
    glVertex2f(x+30, y-15);
    glVertex2f(x+20, y-15);
    glEnd();

    // windows
    glColor3f(0,0,0);
    for(int i = 0; i < 3; i++)
    {
        drawCircle(x + 45 + i*30, y+5, 6);
    }
    drawCircle(x, y+5, 6);

    // upper tail
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(x+120, y+20);
    glVertex2f(x+150, y+45);
    glVertex2f(x+180, y+45);
    glVertex2f(x+150, y+20);
    glEnd();

    // wing
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(x+50, y-5);
    glVertex2f(x+100, y-5);
    glVertex2f(x+100, y-40);
    glVertex2f(x+80, y-40);
    glEnd();
}

void drawShop(float x, float y)
{
    /*
    // shop base
    glBegin(GL_QUADS);
    glColor3f(0.305, 0.496, 0.617);
    glVertex2f(x, y);
    glVertex2f(x + 324, y);
    glVertex2f(x + 324, y + 200);
    glVertex2f(x, y + 200);
    glEnd();
    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2f(x, y);
    glVertex2f(x + 324, y);
    glVertex2f(x + 324, y + 200);
    glVertex2f(x, y + 200);
    glEnd();

    // door
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2f(x + 5.4, y);
    glVertex2f(x + 90.4, y);
    glVertex2f(x + 90.4, y + 200);
    glVertex2f(x + 5.4, y + 200);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.734, 0.703, 0.66);
    glVertex2f(x + 5.4 + 10.6, y + 65);
    glVertex2f(x + 90.4 - 10.6, y + 65);
    glVertex2f(x + 90.4 - 10.6, y + 200);
    glVertex2f(x + 5.4 + 10.6, y + 200);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2f(x + 5.4 + 10.6, y + 65);
    glVertex2f(x + 90.4 - 10.6, y + 65);
    glVertex2f(x + 90.4 - 10.6, y + 200);
    glVertex2f(x + 5.4 + 10.6, y + 200);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2f(x + 5.4 + 10.6, y + 15);
    glVertex2f(x + 90.4 - 10.6, y + 15);
    glVertex2f(x + 90.4 - 10.6, y + 50);
    glVertex2f(x + 5.4 + 10.6, y + 50);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2f(x + 5.4 + 10.6 + 3, y + 15 + 3);
    glVertex2f(x + 90.4 - 10.6 - 3, y + 15 + 3);
    glVertex2f(x + 90.4 - 10.6 - 3, y + 50 - 3);
    glVertex2f(x + 5.4 + 10.6 + 3, y + 50 - 3);
    glEnd();

    // devider
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(x + 90.4, y);
    glVertex2f(x + 90.4, y + 200);
    glEnd();

    // window
    glLineWidth(1);
    glBegin(GL_POLYGON);
    glColor3f(0.734, 0.703, 0.66);
    glVertex2f(x + 105, y + 65);
    glVertex2f(x + 105 + 205, y + 65);
    glVertex2f(x + 105 + 205, y + 200);
    glVertex2f(x + 105, y + 200);
    glEnd();
    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2f(x + 105, y + 65);
    glVertex2f(x + 105 + 205, y + 65);
    glVertex2f(x + 105 + 205, y + 200);
    glVertex2f(x + 105, y + 200);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2f(x + 105, y + 15);
    glVertex2f(x + 105 + 205, y + 15);
    glVertex2f(x + 105 + 205, y + 50);
    glVertex2f(x + 105, y + 50);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2f(x + 105 + 3, y + 15 + 3);
    glVertex2f(x + 105 + 205 - 3, y + 15 + 3);
    glVertex2f(x + 105 + 205 - 3, y + 50 - 3);
    glVertex2f(x + 105 + 3, y + 50 - 3);
    glEnd();

    // side piller
    glBegin(GL_POLYGON);
    glColor3f(0.977, 0.859, 0.609);
    glVertex2f(x, y);
    glVertex2f(x - 12.6, y - 12);
    glVertex2f(x - 12.6 - 37, y - 12);
    glVertex2f(x - 12.6 - 37, y +190);
    glVertex2f(x - 12.6, y + 190);
    glVertex2f(x, y + 190);
    glEnd();
    // another side
    glBegin(GL_POLYGON);
    glColor3f(0.977, 0.859, 0.609);
    glVertex2f(x + 324, y);
    glVertex2f(x + 324 + 12.6, y - 12);
    glVertex2f(x + 324 + 12.6 + 37, y - 12);
    glVertex2f(x + 324 + 12.6 + 37, y +190);
    glVertex2f(x + 324 + 12.6, y + 190);
    glVertex2f(x + 324, y + 190);
    glEnd();

    // top
    glColor3f(0.917, 0.394, 0.246);
    int r = 20;
    int cy = y + 190;
    int cx = x - 47;
    int cx2 = x - 47;
    for (int i = 0; i < 13; i++)
    {
        drawCircle(cx2, cy, r);
        cx2 += 35;
    }

    glBegin(GL_POLYGON);
    glVertex2f(cx - 20, cy);
    glVertex2f(cx - 20, cy + 20);
    glVertex2f(cx + 20, cy + 75);
    glVertex2f(cx2 - 35 - 20, cy + 75);
    glVertex2f(cx2 - 35 + 20, cy + 20);
    glVertex2f(cx2 - 35 + 20, cy);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.734, 0.703, 0.66);
    glVertex2f(cx + 20, cy + 75);
    glVertex2f(cx + 20, cy + 100);
    glVertex2f(cx2 - 35 - 20, cy + 100);
    glVertex2f(cx2 - 35 - 20, cy + 75);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.977, 0.859, 0.609);
    glVertex2f(cx + 17, cy + 75);
    glVertex2f(cx + 17, cy + 80);
    glVertex2f(cx2 - 35 - 17, cy + 80);
    glVertex2f(cx2 - 35 - 17, cy + 75);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.977, 0.859, 0.609);
    glVertex2f(cx + 17, cy + 100);
    glVertex2f(cx + 17, cy + 105);
    glVertex2f(cx2 - 35 - 17, cy + 105);
    glVertex2f(cx2 - 35 - 17, cy + 100);
    glEnd();
    */
/*
    // roof (triangle)
    glBegin(GL_TRIANGLES);
    glColor3f(0.8, 0.1, 0.1); // red
    glVertex2f(480, 600);
    glVertex2f(720, 600);
    glVertex2f(600, 700);
    glEnd();

    // door
    glBegin(GL_QUADS);
    glColor3f(0.4, 0.2, 0.0); // brown
    glVertex2f(580, 450);
    glVertex2f(620, 450);
    glVertex2f(620, 520);
    glVertex2f(580, 520);
    glEnd();

    // left window
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.9, 1.0); // light blue
    glVertex2f(520, 520);
    glVertex2f(560, 520);
    glVertex2f(560, 560);
    glVertex2f(520, 560);
    glEnd();

    // right window
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.9, 1.0);
    glVertex2f(640, 520);
    glVertex2f(680, 520);
    glVertex2f(680, 560);
    glVertex2f(640, 560);
    glEnd();
    */

    // shop base
    glBegin(GL_QUADS);
    glColor3f(0.305, 0.496, 0.617);
    glVertex2f(x, y);
    glVertex2f(x + 194.4, y);
    glVertex2f(x + 194.4, y + 120);
    glVertex2f(x, y + 120);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2f(x, y);
    glVertex2f(x + 194.4, y);
    glVertex2f(x + 194.4, y + 120);
    glVertex2f(x, y + 120);
    glEnd();

    // door
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2f(x + 3.24, y);
    glVertex2f(x + 54.24, y);
    glVertex2f(x + 54.24, y + 120);
    glVertex2f(x + 3.24, y + 120);
    glEnd();

    glBegin(GL_POLYGON);
    if (isNight)
        glColor3f(1, 1, 0);
    else
        glColor3f(0.734, 0.703, 0.66);
    glVertex2f(x + 9.6, y + 39);
    glVertex2f(x + 47.88, y + 39);
    glVertex2f(x + 47.88, y + 120);
    glVertex2f(x + 9.6, y + 120);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2f(x + 9.6, y + 39);
    glVertex2f(x + 47.88, y + 39);
    glVertex2f(x + 47.88, y + 120);
    glVertex2f(x + 9.6, y + 120);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2f(x + 9.6, y + 9);
    glVertex2f(x + 47.88, y + 9);
    glVertex2f(x + 47.88, y + 30);
    glVertex2f(x + 9.6, y + 30);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2f(x + 11.4, y + 10.8);
    glVertex2f(x + 46.08, y + 10.8);
    glVertex2f(x + 46.08, y + 28.2);
    glVertex2f(x + 11.4, y + 28.2);
    glEnd();

    // divider
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(x + 54.24, y);
    glVertex2f(x + 54.24, y + 120);
    glEnd();

    // window
    glLineWidth(1);
    glBegin(GL_POLYGON);
    if (isNight)
        glColor3f(1, 1, 0);
    else
        glColor3f(0.734, 0.703, 0.66);
    glVertex2f(x + 63, y + 39);
    glVertex2f(x + 186, y + 39);
    glVertex2f(x + 186, y + 120);
    glVertex2f(x + 63, y + 120);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2f(x + 63, y + 39);
    glVertex2f(x + 186, y + 39);
    glVertex2f(x + 186, y + 120);
    glVertex2f(x + 63, y + 120);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2f(x + 63, y + 9);
    glVertex2f(x + 186, y + 9);
    glVertex2f(x + 186, y + 30);
    glVertex2f(x + 63, y + 30);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2f(x + 64.8, y + 10.8);
    glVertex2f(x + 184.2, y + 10.8);
    glVertex2f(x + 184.2, y + 28.2);
    glVertex2f(x + 64.8, y + 28.2);
    glEnd();

    // side pillar
    glBegin(GL_POLYGON);
    glColor3f(0.977, 0.859, 0.609);
    glVertex2f(x, y);
    glVertex2f(x - 7.56, y - 7.2);
    glVertex2f(x - 29.76, y - 7.2);
    glVertex2f(x - 29.76, y + 114);
    glVertex2f(x - 7.56, y + 114);
    glVertex2f(x, y + 114);
    glEnd();

    // another side
    glBegin(GL_POLYGON);
    glColor3f(0.977, 0.859, 0.609);
    glVertex2f(x + 194.4, y);
    glVertex2f(x + 201.96, y - 7.2);
    glVertex2f(x + 224.16, y - 7.2);
    glVertex2f(x + 224.16, y + 114);
    glVertex2f(x + 201.96, y + 114);
    glVertex2f(x + 194.4, y + 114);
    glEnd();

    // top
    glColor3f(0.917, 0.394, 0.246);
    int r = 12;
    int cy = y + 114;
    int cx = x - 28.2;
    int cx2 = x - 28.2;

    for (int i = 0; i < 13; i++)
    {
        drawCircle(cx2, cy, r);
        cx2 += 21;
    }

    glBegin(GL_POLYGON);
    glVertex2f(cx - 12, cy);
    glVertex2f(cx - 12, cy + 12);
    glVertex2f(cx + 12, cy + 45);
    glVertex2f(cx2 - 21 - 12, cy + 45);
    glVertex2f(cx2 - 21 + 12, cy + 12);
    glVertex2f(cx2 - 21 + 12, cy);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.734, 0.703, 0.66);
    glVertex2f(cx + 12, cy + 45);
    glVertex2f(cx + 12, cy + 60);
    glVertex2f(cx2 - 21 - 12, cy + 60);
    glVertex2f(cx2 - 21 - 12, cy + 45);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.977, 0.859, 0.609);
    glVertex2f(cx + 10.2, cy + 45);
    glVertex2f(cx + 10.2, cy + 48);
    glVertex2f(cx2 - 21 - 10.2, cy + 48);
    glVertex2f(cx2 - 21 - 10.2, cy + 45);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.977, 0.859, 0.609);
    glVertex2f(cx + 10.2, cy + 60);
    glVertex2f(cx + 10.2, cy + 63);
    glVertex2f(cx2 - 21 - 10.2, cy + 63);
    glVertex2f(cx2 - 21 - 10.2, cy + 60);
    glEnd();

}

void drawCar(float x, float y)
{
    glColor3f(0, 0, 0);
    // body
    drawCircle(x+28, y+64, 28);
    glBegin(GL_QUADS);
    glVertex2f(x+28, y+36);
    glVertex2f(x+28, y+92);
    glVertex2f(x+234.4, y+92);
    glVertex2f(x+234.4, y+36);
    glEnd();
    drawCircle(x+234.4, y+64, 28);

    // tires
    glColor3f(0.27, 0.28, 0.29);
    drawCircle(x+76.8, y+32, 32);
    drawCircle(x+194.4, y+32, 32);

    glColor3f(0, 0, 0);
    drawCircle(x+76.8, y+32, 26);
    drawCircle(x+194.4, y+32, 26);

    glColor3f(0.27, 0.28, 0.29);
    drawCircle(x+76.8, y+32, 14);
    drawCircle(x+194.4, y+32, 14);

    // top
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(x+56, y+92);
    glVertex2f(x+56.8, y+93.6);
    glVertex2f(x+58.4, y+96);
    glVertex2f(x+60.08, y+98.4);
    glVertex2f(x+61.6, y+100.8);
    glVertex2f(x+63.2, y+103.2);
    glVertex2f(x+64.8, y+105.6);
    glVertex2f(x+66.4, y+108);
    glVertex2f(x+68, y+110.4);
    glVertex2f(x+69.6, y+112.8);
    glVertex2f(x+71.2, y+115.2);
    glVertex2f(x+72.8, y+117.6);
    glVertex2f(x+75.2, y+120.8);
    glVertex2f(x+78.4, y+124.8);
    glVertex2f(x+80.24, y+127.2);
    glVertex2f(x+82.4, y+129.6);
    glVertex2f(x+83.92, y+135.2);
    glVertex2f(x+87.92, y+136);
    glVertex2f(x+88.8, y+136.8);
    glVertex2f(x+89.68, y+137.6);
    glVertex2f(x+90.72, y+138.4);
    glVertex2f(x+92, y+139.2);
    glVertex2f(x+93.44, y+140);
    glVertex2f(x+94.4, y+140.4);
    glVertex2f(x+95.2, y+140.72);
    glVertex2f(x+96, y+140.8);
    glVertex2f(x+228.8, y+140.8);
    glVertex2f(x+229.6, y+140.72);
    glVertex2f(x+230.4, y+140.4);
    glVertex2f(x+231.2, y+140.08);
    glVertex2f(x+232, y+139.6);
    glVertex2f(x+232.8, y+138.88);
    glVertex2f(x+233.6, y+138.08);
    glVertex2f(x+234.4, y+135.2);
    glVertex2f(x+235.2, y+134.4);
    glVertex2f(x+236, y+133.6);
    glVertex2f(x+236.8, y+132.8);
    glVertex2f(x+237.6, y+132);
    glVertex2f(x+238.4, y+131.2);
    glVertex2f(x+237.6, y+92);
    glEnd();

    // window 1
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(x+56+7, y+92);
    glVertex2f(x+56.8+7, y+93.6);
    glVertex2f(x+58.4+7, y+96);
    glVertex2f(x+60.08+7, y+98.4);
    glVertex2f(x+61.6+7, y+100.8);
    glVertex2f(x+63.2+7, y+103.2);
    glVertex2f(x+64.8+7, y+105.6);
    glVertex2f(x+66.4+7, y+108);
    glVertex2f(x+68+7, y+110.4);
    glVertex2f(x+69.6+7, y+112.8);
    glVertex2f(x+71.2+7, y+115.2);
    glVertex2f(x+72.8+7, y+117.6);
    glVertex2f(x+75.2+7, y+120.8);
    glVertex2f(x+78.4+7, y+124.8);
    glVertex2f(x+80.24+7, y+127.2);
    glVertex2f(x+82.4+7, y+129.6);
    glVertex2f(x+83.92+7, y+135.2-7);
    glVertex2f(x+87.92+7, y+136-6);
    glVertex2f(x+88.8+7, y+136.8-6);
    glVertex2f(x+89.68+7, y+137.6-6);
    glVertex2f(x+90.72+7, y+138.4-6);
    glVertex2f(x+92+7, y+139.2-7);
    glVertex2f(x+93.44+7, y+140-7);
    glVertex2f(x+94.4+7, y+140.4-7);
    glVertex2f(x+95.2+7, y+140.72-7);
    glVertex2f(x+96+7, y+140.8-7);
    glVertex2f(x+96+40, y+140.8-7);
    glVertex2f(x+96+40, y+92);
    glEnd();

    //window 2
    glBegin(GL_POLYGON);
    glVertex2f(x+140, y+92);
    glVertex2f(x+140, y+133.8);
    glVertex2f(x+190, y+133.7);
    glVertex2f(x+190, y+92);
    glEnd();
    //window 3
    glBegin(GL_POLYGON);
    glVertex2f(x+194, y+92);
    glVertex2f(x+194, y+133.8);
    glVertex2f(x+230, y+133.7);
    glVertex2f(x+230, y+92);
    glEnd();
}

void drawBus(float x, float y)
{
    // ===== BODY =====
    glColor3f(0.85, 0.1, 0.1); // red bus
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + 420, y);
    glVertex2f(x + 420, y + 120);
    glVertex2f(x + 360, y + 160);
    glVertex2f(x + 80, y + 160);
    glVertex2f(x, y + 120);
    glEnd();

    // ===== WINDOW STRIP =====
    glColor3f(0.2, 0.2, 0.25);
    glBegin(GL_POLYGON);
    glVertex2f(x + 40, y + 110);
    glVertex2f(x + 380, y + 110);
    glVertex2f(x + 340, y + 150);
    glVertex2f(x + 80, y + 150);
    glEnd();

    // ===== WINDOWS (individual) =====
    glColor3f(0.6, 0.8, 1.0);
    for(int i = 0; i < 6; i++)
    {
        float wx = x + 55 + i * 55;
        glBegin(GL_POLYGON);
        glVertex2f(wx, y + 115);
        glVertex2f(wx + 40, y + 115);
        glVertex2f(wx + 30, y + 145);
        glVertex2f(wx - 5, y + 145);
        glEnd();
    }

    // ===== DOOR =====
    glColor3f(0.15, 0.15, 0.15);
    glBegin(GL_POLYGON);
    glVertex2f(x + 300, y);
    glVertex2f(x + 350, y);
    glVertex2f(x + 350, y + 100);
    glVertex2f(x + 300, y + 100);
    glEnd();

    // ===== STRIPE =====
    glColor3f(1.0, 0.8, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(x + 10, y + 40);
    glVertex2f(x + 410, y + 40);
    glVertex2f(x + 410, y + 55);
    glVertex2f(x + 10, y + 55);
    glEnd();

    // ===== WHEELS =====
    glColor3f(0.1, 0.1, 0.1);
    drawCircle(x + 100, y, 40);
    drawCircle(x + 320, y, 40);

    glColor3f(0.5, 0.5, 0.5);
    drawCircle(x + 100, y, 20);
    drawCircle(x + 320, y, 20);

    // ===== HEADLIGHT =====
    glColor3f(1.0, 1.0, 0.6);
    drawCircle(x + 400, y + 30, 8);

    // ===== BACK LIGHT =====
    glColor3f(1.0, 0.2, 0.2);
    drawCircle(x + 20, y + 30, 6);
}

void drawSun(float x, float y)
{
    if (!isNight)
        glColor3f(1, 0.9, 0);
    else if (isNight)
        glColor3f(1, 1, 1);
    drawCircle(x, y, 80);
}

void drawTree(float x, float y)
{
    // ===== trunk (short height, same width) =====
    glBegin(GL_POLYGON);
    glColor3f(0.55, 0.27, 0.07);
    glVertex2f(x + 18, y);
    glVertex2f(x + 32, y);
    glVertex2f(x + 32, y + 25);
    glVertex2f(x + 18, y + 25);
    glEnd();
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x+22, y+5);
    glVertex2f(x+22, y+20);
    glEnd();

    // ===== bottom triangle (wide) =====
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.6, 0.0);
    glVertex2f(x - 30, y + 25);
    glVertex2f(x + 80, y + 25);
    glVertex2f(x + 25, y + 150);
    glEnd();

    // ===== top triangle (same width, less gap) =====
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.5, 0.0);
    glVertex2f(x - 30, y + 70);
    glVertex2f(x + 80, y + 70);
    glVertex2f(x + 25, y + 180);
    glEnd();

    // grass
    glColor3f(0.0, 0.7, 0.0);
    glLineWidth(2);

    for(int i = -30; i <= 80; i += 6)
    {
        glBegin(GL_LINES);
        glVertex2f(x + i, y);
        glVertex2f(x + i + 2, y + 8);   // right tilt
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(x + i, y);
        glVertex2f(x + i - 2, y + 7);   // left tilt
        glEnd();
    }

    glLineWidth(1);
}

// scene 2
// Background
void drawBackground2()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Sky
    glBegin(GL_QUADS);
     if (isNight)
        glColor3f(0.05, 0.05, 0.15); // dark blue
    else
        glColor3f(0.30, 0.78, 0.99); // day sky

    glVertex2f(0, 722);
    glVertex2f(1440, 722);
    glVertex2f(1440, 1024);
    glVertex2f(0, 1024);
    glEnd();

    // Water
    glBegin(GL_QUADS);
    glColor3f(0.082, 0.4f, 0.682);
    glVertex2f(0, 0);
    glVertex2f(1440, 0);
    glVertex2f(1440, 722);
    glVertex2f(0, 722);
    glEnd();

    // Left land
    glBegin(GL_POLYGON);
    glColor3f(0.698, 0.537, 0.4);
    glVertex2f(0, 0);
    glVertex2f(0, 617);
    glVertex2f(654, 617);
    glVertex2f(781, 459);
    glVertex2f(709, 444);
    glVertex2f(830, 269);
    glVertex2f(744, 234);
    glVertex2f(905, 0);
    glEnd();

    // Right land
    glBegin(GL_POLYGON);
    glColor3f(0.698, 0.537, 0.4);
    glVertex2f(1440, 0);
    glVertex2f(1440, 617);
    glVertex2f(1020, 617);
    glVertex2f(1148, 459);
    glVertex2f(1076, 444);
    glVertex2f(1197, 269);
    glVertex2f(1111, 234);
    glVertex2f(1288, 0);
    glEnd();

}

// Mountains
void drawMountain2(float x, float y)
{
    float my = y;
    glColor3f(0.29, 0.27, 0.27);
    glBegin(GL_POLYGON);
    glVertex2f(x - 36, my);
    glVertex2f(x + 6, my + 81);
    glVertex2f(x + 86, my + 132);
    glVertex2f(x + 171, my + 99);
    glVertex2f(x + 234, my);
    glEnd();

    // Snow cap
    glColor3f(0.85, 0.85, 0.85);
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 45, my + 104);
    glVertex2f(x + 86, my + 132);
    glVertex2f(x + 155, my + 104);
    glEnd();

    // White lines
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(x + 0, my + 45);
    glVertex2f(x + 68, my + 82);

    glVertex2f(x + 0, my + 35);
    glVertex2f(x + 78, my + 82);
    glEnd();

    // border
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x - 36, my);
    glVertex2f(x + 6, my + 81);
    glVertex2f(x + 86, my + 132);
    glVertex2f(x + 171, my + 99);
    glVertex2f(x + 234, my);
    glEnd();
}

// Big Ship
void drawLargeShip2(float x, float y)
{

    // 1st floor
    glColor3f(0.92, 0.4, 0.25);
    glBegin(GL_QUADS);
    glVertex2f(x + 44, y - 18);
    glVertex2f(x + 289, y - 18);
    glVertex2f(x + 289, y + 16);
    glVertex2f(x + 44, y + 16);
    glEnd();
    // border
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x + 44, y - 18);
    glVertex2f(x + 289, y - 18);
    glVertex2f(x + 289, y + 16);
    glVertex2f(x + 44, y + 16);
    glEnd();

    // Windows
    for (int row = 0; row < 2; row++)
    {
        for (int i = 0; i < 5; i++)
        {
            float wx = x + 68 + i * 35;
            float wy = y - 5;
            // blue
            if (!isNight)
                glColor3f(0.21, 0.67, 0.95);
            else if (isNight)
                glColor3f(1, 1, 0);

            glBegin(GL_QUADS);
            glVertex2f(wx, wy);
            glVertex2f(wx + 14, wy);
            glVertex2f(wx + 14, wy + 14);
            glVertex2f(wx, wy + 14);
            glEnd();

            // black
            glColor3f(0, 0, 0);
            glBegin(GL_LINE_LOOP);
            glVertex2f(wx, wy);
            glVertex2f(wx + 14, wy);
            glVertex2f(wx + 14, wy + 14);
            glVertex2f(wx, wy + 14);
            glEnd();
        }
    }

    // Front windows
    glBegin(GL_QUADS);
    if (!isNight)
        glColor3f(0.21, 0.67, 0.95);
    else if (isNight)
        glColor3f(1, 1, 0);

    glVertex2f(x + 236, y - 10);
    glVertex2f(x + 289, y - 10);
    glVertex2f(x + 289, y + 12);
    glVertex2f(x + 236, y + 12);
    glEnd();

    // 2nd floor
    glBegin(GL_POLYGON);
    glColor3f(0.92, 0.4, 0.25);
    glVertex2f(x + 44, y + 16);
    glVertex2f(x + 289, y + 16);
    glVertex2f(x + 286, y + 33);
    glVertex2f(x + 271, y + 51);
    glVertex2f(x + 51, y + 51);
    glEnd();

    // border
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2f(x + 44, y + 16);
    glVertex2f(x + 289, y + 16);
    glVertex2f(x + 286, y + 33);
    glVertex2f(x + 271, y + 51);
    glVertex2f(x + 51, y + 51);
    glEnd();

    // Windows
    for (int row = 0; row < 2; row++)
    {
        for (int i = 0; i < 5; i++)
        {
            float wx = x + 68 + i * 35;
            float wy = y + 30;
            if (!isNight)
                glColor3f(0.21, 0.67, 0.95);
            else if (isNight)
                glColor3f(1, 1, 0);

            glBegin(GL_QUADS);
            glVertex2f(wx, wy);
            glVertex2f(wx + 14, wy);
            glVertex2f(wx + 14, wy + 14);
            glVertex2f(wx, wy + 14);
            glEnd();

            // black
            glColor3f(0, 0, 0);
            glBegin(GL_LINE_LOOP);
            glVertex2f(wx, wy);
            glVertex2f(wx + 14, wy);
            glVertex2f(wx + 14, wy + 14);
            glVertex2f(wx, wy + 14);
            glEnd();
        }
    }

    // Front windows
    glBegin(GL_POLYGON);
    if (!isNight)
        glColor3f(0.21, 0.67, 0.95);
    else if (isNight)
        glColor3f(1, 1, 0);

    glVertex2f(x + 238, y + 25);
    glVertex2f(x + 238, y + 50);
    glVertex2f(x + 270, y + 50);
    glVertex2f(x + 285, y + 32);
    glVertex2f(x + 285, y + 25);
    glEnd();

    // Chimneys
    for (int i = 0; i < 3; i++)
    {
        float cx = x + 100 + i * 59;
        float cy = y + 52;
        glColor3f(0.87, 1, 0);
        glBegin(GL_QUADS);
        glVertex2f(cx, cy);
        glVertex2f(cx, cy + 26);
        glVertex2f(cx + 13, cy + 26);
        glVertex2f(cx + 13, cy);
        glEnd();

        glColor3f(0, 0, 0);
        glBegin(GL_QUADS);
        glVertex2f(cx, cy + 20);
        glVertex2f(cx, cy + 26);
        glVertex2f(cx + 13, cy + 26);
        glVertex2f(cx + 13, cy + 20);
        glEnd();
    }

    // Hull
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + 337, y);
    glVertex2f(x + 289, y - 32);
    glVertex2f(x + 20, y - 32);
    glEnd();

    // Bottom red line
    glColor3f(0.97f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x + 20, y - 29);
    glVertex2f(x + 290, y - 29);
    glVertex2f(x + 290, y - 36);
    glVertex2f(x + 20, y - 36);
    glEnd();
}

// Small Boat
void drawSmallBoat2(float x, float y)
{
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + 90, y);
    glVertex2f(x + 82, y - 6);
    glVertex2f(x + 8, y - 6);
    glEnd();

    glColor3f(0.698f, 0.537f, 0.400f);
    glBegin(GL_QUADS);
    glVertex2f(x + 18, y);
    glVertex2f(x + 72, y);
    glVertex2f(x + 72, y + 8);
    glVertex2f(x + 18, y + 8);
    glEnd();

    glColor3f(0, 0, 0);
    drawCircle(x + 83, y + 3, 1.5f);

    glBegin(GL_QUADS);
    glVertex2f(x + 82, y - 1);
    glVertex2f(x + 84, y - 1);
    glVertex2f(x + 84, y + 3);
    glVertex2f(x + 82, y + 3);
    glEnd();

    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(x + 81, y + 2);
    glVertex2f(x + 81, y - 10);
    glEnd();
}

// Cargo Boat
void drawCargoBoat2(float x, float y)
{
    // Driver
    glColor3f(0, 0, 0);
    drawEllipse(x + 187.5, y + 24, 2.5, 3);

    glBegin(GL_QUADS);
    glVertex2f(x + 185, y + 14);
    glVertex2f(x + 190, y + 14);
    glVertex2f(x + 190, y + 24);
    glVertex2f(x + 185, y + 24);
    glEnd();

    // Hull
    glColor3f(0.12f, 0.12f, 0.12f);
    glBegin(GL_POLYGON);
    glVertex2f(x + 19, y);
    glVertex2f(x + 19, y + 14);
    glVertex2f(x + 19 + 173, y + 14);
    glVertex2f(x + 19 + 173, y);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(x, y + 22);
    glVertex2f(x, y + 11);
    glVertex2f(x + 10, y);
    glVertex2f(x + 19, y);
    glVertex2f(x + 19, y + 14);
    glVertex2f(x + 10, y + 22);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(x + 192, y);
    glVertex2f(x + 192, y + 22);
    glVertex2f(x + 202, y + 22);
    glVertex2f(x + 202, y + 11);
    glVertex2f(x + 198, y);
    glEnd();

    // control handle
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex2f(x + 175, y + 18);
    glVertex2f(x + 175 + 17, y + 18);
    glEnd();

    // driver hand
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(x + 180, y + 19);
    glVertex2f(x + 187, y + 22);
    glEnd();

    // Blue cargo
    glColor3f(0.16f, 0.0f, 0.81f);
    glBegin(GL_QUADS);
    glVertex2f(x + 38, y + 14);
    glVertex2f(x + 38, y + 19);
    glVertex2f(x + 161, y + 19);
    glVertex2f(x + 161, y + 14);
    glEnd();

    // Bottom yellow line
    glColor3f(0.78f, 0.56f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(x + 9, y - 1);
    glVertex2f(x + 199, y - 1);
    glEnd();
}

// House
void drawHouse2(float x, float y)
{
    // Foundation
    glColor3f(0.85f, 0.85f, 0.85f);
    glBegin(GL_POLYGON);
    glVertex2f(x + 17, y + 22);
    glVertex2f(x + 17, y + 31);
    glVertex2f(x + 210, y + 17);
    glVertex2f(x + 210, y + 3);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(x + 322, y + 22);
    glVertex2f(x + 322, y + 31);
    glVertex2f(x + 210, y + 17);
    glVertex2f(x + 210, y + 3);
    glEnd();

    // Left wall
    glColor3f(0.92, 0.40, 0.25);
    glBegin(GL_QUADS);
    glVertex2f(x + 21, y + 31);
    glVertex2f(x + 21, y + 105);
    glVertex2f(x + 211, y + 105);
    glVertex2f(x + 211, y + 17);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x + 21, y + 31);
    glVertex2f(x + 21, y + 105);
    glVertex2f(x + 211, y + 105);
    glVertex2f(x + 211, y + 17);
    glEnd();

    // Right wall
    glColor3f(0.92, 0.40, 0.25);
    glBegin(GL_QUADS);
    glVertex2f(x + 211, y + 17);
    glVertex2f(x + 211, y + 105);
    glVertex2f(x + 319, y + 105);
    glVertex2f(x + 319, y + 31);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x + 211, y + 17);
    glVertex2f(x + 211, y + 105);
    glVertex2f(x + 319, y + 105);
    glVertex2f(x + 319, y + 31);
    glEnd();

    // Windows
    if (!isNight)
        glColor3f(0.85, 0.85, 0.85);
    else if (isNight)
        glColor3f(1, 1, 0);

    glBegin(GL_QUADS);
    glVertex2f(x + 43, y + 66);
    glVertex2f(x + 43, y + 66 + 25);
    glVertex2f(x + 83, y + 66 + 25);
    glVertex2f(x + 83, y + 66);
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x + 43, y + 66);
    glVertex2f(x + 43, y + 66 + 25);
    glVertex2f(x + 83, y + 66 + 25);
    glVertex2f(x + 83, y + 66);
    glEnd();

    if (!isNight)
        glColor3f(0.85, 0.85, 0.85);
    else if (isNight)
        glColor3f(1, 1, 0);
    glBegin(GL_QUADS);
    glVertex2f(x + 140, y + 66);
    glVertex2f(x + 140, y + 66+25);
    glVertex2f(x + 180, y + 66+25);
    glVertex2f(x + 180, y + 66);
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x + 140, y + 66);
    glVertex2f(x + 140, y + 66+25);
    glVertex2f(x + 180, y + 66+25);
    glVertex2f(x + 180, y + 66);
    glEnd();

    // Door
    if (!isNight)
        glColor3f(0.85, 0.85, 0.85);
    else if (isNight)
        glColor3f(1, 1, 0);
    glBegin(GL_QUADS);
    glVertex2f(x + 258, y + 23.8);
    glVertex2f(x + 258, y + 77);
    glVertex2f(x + 286, y + 77);
    glVertex2f(x + 286, y + 27);
    glEnd();

    // Roof right
    glColor3f(0.92, 0.40, 0.25);
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 211, y + 105);
    glVertex2f(x + 320, y + 105);
    glVertex2f(x + 265, y + 146);
    glEnd();

    // Roof left
    glColor3f(0.40, 0.29, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(x, y + 83);
    glVertex2f(x + 55, y + 83+63);
    glVertex2f(x + 264, y + 146);
    glVertex2f(x + 209, y + 83);
    glEnd();
    glColor3f(0.445, 0.172, 0);
    glBegin(GL_POLYGON);
    glVertex2f(x, y + 83);
    glVertex2f(x + 55, y + 83+63);
    glVertex2f(x + 264, y + 146);
    glVertex2f(x + 209, y + 83);
    glEnd();

    // Roof right top line
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(0.445, 0.172, 0);
    glVertex2f(x + 265, y + 148);
    glVertex2f(x + 329, y + 98);
    glEnd();

    // roof top line
    glColor3f(0.445, 0.172, 0);
    glBegin(GL_LINES);
    glVertex2f(x + 55, y + 148);
    glVertex2f(x + 55 + 210, y + 148);
    glEnd();

    // Roof vent
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(x + 261, y + 114);
    glVertex2f(x + 261, y + 129);
    glVertex2f(x + 273, y + 129);
    glVertex2f(x + 273, y + 114);
    glEnd();
}

// Tree
void drawTree2(float x, float y)
{
    // Ground
    glColor3f(0.40, 0.74, 0.27);
    drawEllipse(x + 88, y +17.5, 43, 17.5);

    // Trunk
    glColor3f(0.47f, 0.17f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x + 76, y + 19);
    glVertex2f(x + 76, y + 209);
    glVertex2f(x + 104, y + 209);
    glVertex2f(x + 104, y + 19);
    glEnd();

    // Leaves
    glColor3f(0.19f, 0.62f, 0.36f);
    drawEllipse(x + 50, y + 206, 50, 49);
    drawEllipse(x + 119, y + 205, 50, 50);
    drawEllipse(x + 50.5, y + 253, 50.5, 39);
    drawEllipse(x + 89, y + 276, 39, 41);
    drawEllipse(x + 134.5, y + 241.5, 38.5, 34.5);
}

// night overlay
void drawNightOverlay()
{
    if (!isNight) return;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Semi-transparent black overlay
    glColor4f(0.0, 0.0, 0.0, 0.6);

    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(1440, 0);
    glVertex2f(1440, 1024);
    glVertex2f(0, 1024);
    glEnd();

    glDisable(GL_BLEND);
}

void update1()
{
    // cloud movement
    cloudX -= 1;
    if (cloudX < -1500) cloudX = 1446;

    // Bus auto movement
    busX += busSpeed;
    if (busX > 1440) busX = -420;

    // Plane auto movement
    planeX -= planeSpeed;
    if (planeX <-1500) planeX -= 200;
}

void update2()
{
    // Cruise Ship
    largeShipX += cruiseShipSpeed;

    if (largeShipX > 1600)
        largeShipX = -450;

    // Fishing Boat
    smallBoatX -= fishingBoatSpeed;

    if (smallBoatX < -250)
        smallBoatX = 1500;

    // Cargo Boat
    cargoBoatX -= cargoBoatSpeed;

    if (cargoBoatX < -300)
        cargoBoatX = 1600;

    // Clouds
    if (!isNight)
    {
        cloud1X += cloudSpeed;
        cloud2X += cloudSpeed;
        cloud3X += cloudSpeed;

        if (cloud1X > 1500) cloud1X = -200;
        if (cloud2X > 1500) cloud2X = -200;
        if (cloud3X > 1500) cloud3X = -200;
    }
}

void update(int value)
{
    if (currentScenario == 1)
    {
        update1();
    }
    else if (currentScenario == 2)
    {
        update2();
    }

    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case '1':
            currentScenario = 1;
            break;

        case '2':
            currentScenario = 2;
            break;

        case 'a':
        case 'A':
            if (currentScenario == 1)
                carX -= carSpeed;
            break;

        case 'd':
        case 'D':
            if (currentScenario == 1)
                carX += carSpeed;
            break;

        case 'm':
        case 'M':
            if (currentScenario == 1)
                isNight = !isNight;
            break;

        case 's':
        case 'S':
            if (currentScenario == 2)
            {
                cruiseShipSpeed += 0.2;
                if (cruiseShipSpeed > 5.0)
                    cruiseShipSpeed = 0;
            }
            break;

        case 'n':
        case 'N':
            if (currentScenario == 2)
                isNight = !isNight;
            break;

        case 'r':
        case 'R':
            if (planeX <= -200)
                planeX = 1500;
            break;

        case 27:
            exit(0);
            break;
    }

    glutPostRedisplay();
}

void mouse(int button, int state, int mx, int my)
{
    if (currentScenario == 1)
    {
        if (button == 3 && state == GLUT_DOWN)  // scroll up
        {
            planeSpeed += 0.5;
            if (planeSpeed > 40.0) planeSpeed = 40.0;
        }
        if (button == 4 && state == GLUT_DOWN)  // scroll down
        {
            planeSpeed -= 0.5;
            if (planeSpeed < -15.0) planeSpeed = -15.0;
        }
    }
    glutPostRedisplay();
}

void display1()
{
    // background
    drawBackground();

    drawSun(1340, 924);

    // cloud
    drawCloud(200 + cloudX, 850);
    drawCloud(500 + cloudX, 900);
    drawCloud(850 + cloudX, 820);
    drawCloud(1250 + cloudX, 880);

    // mountains
    drawMountain2(356, 680);
    drawMountain2(561, 680);
    drawMountain2(760, 680);
    drawMountain2(973, 680);
    drawMountain2(1182, 680);
    drawMountain2(1350, 680);

    // buildings
    glColor3f(0.239, 0.141, 0.141);
    drawBuilding(-10, 850);
    glColor3f(0.074, 0.242, 0.261);
    drawBuilding(100, 850);
    glColor3f(0.074, 0.242, 0.261);
    drawBuilding(310, 860);
    glColor3f(0.758, 0.75, 0.258);
    drawBuilding(220, 850);


    drawPlane(planeX, planeY);
    drawShop(1000, 610);

    drawCar(carX, 350);
    drawBus(busX, 300);
    drawTree(1300, 600);
    drawTree(850, 600);

    if (isNight)
        drawNightOverlay();

    glFlush();
}

void display2()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw background
    drawBackground2();

    // draw sun and clouds
    drawSun(1340, 924);

    drawCloud(cloud1X, 950);
    drawCloud(cloud2X, 880);
    drawCloud(cloud3X, 900);

    // Mountains
    drawMountain2(0, 722);
    drawMountain2(172, 722);
    drawMountain2(356, 722);
    drawMountain2(561, 722);
    drawMountain2(760, 722);
    drawMountain2(973, 722);
    drawMountain2(1182, 722);
    drawMountain2(1350, 722);

    // Ships
    drawSmallBoat2(smallBoatX, 702);
    drawLargeShip2(largeShipX, 685);
    drawCargoBoat2(cargoBoatX, 650);

    drawTree2(120, 278);
    drawHouse2(233, 296);

    drawNightOverlay();

    glFlush();
}

void display()
{
    if (currentScenario == 1)
        display1();
    else if (currentScenario == 2)
        display2();
}

void init()
{
    glClearColor(1, 1, 1, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1440, 0, 1024);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(1440, 1024);
    glutCreateWindow("Merged Scene");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
