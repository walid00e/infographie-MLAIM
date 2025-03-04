#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

void pixel(int x, int y, int color) {
    x = x + 320;
    y = 240 - y;
    putpixel(x, y, color);
}

void ligneBresenham(int xd, int yd, int xf, int yf) {
    int x, y, s, i, dy, dx, incX, incY;

    dx = abs(xf - xd);
    dy = abs(yf - yd);

    if (xf >= xd) {
        pixel(xd, yd, WHITE);
        incX = 1;
    } else {
        pixel(xf, yf, WHITE);
        incX = -1;
    }

    if (yf >= yd) {
        incY = 1;
    } else {
        incY = -1;
    }

    if (dx > dy) {
        s = 2 * dy - dx;
        x = xd;
        y = yd;

        i = 0;
        while (i <= dx) {
            pixel(x, y, WHITE);

            if (s >= 0) {
                y += incY;
                s -= 2 * dx;
            }

            x += incX;
            s += 2 * dy;
            i++;
        }
    } else {
        s = 2 * dx - dy;
        x = xd;
        y = yd;

        i = 0;
        while (i <= dy) {
            pixel(x, y, WHITE);

            if (s >= 0) {
                x += incX;
                s -= 2 * dy;
            }

            y += incY;
            s += 2 * dx;
            i++;
        }
    }
}

void repere(){
    cleardevice();
    line(0,240,640,240);
    line(320,0,320,480);
}

void initGraph() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");
}

int main(){
    int xd, xf, yd, yf, cont;
    
    initGraph();
    
    // logic
    while(true){
        repere();
        // capture de pt depart
        printf("xd et yd: \n");
        scanf("%d%d",&xd, &yd);
        // capture de pt finale
        printf("xf et yf: \n");
        scanf("%d%d",&xf, &yf);
        // draw the line
        printf("(%d, %d) -> (%d, %d)\n", xd, yd, xf, yf);
        ligneBresenham(xd, yd, xf, yf);
        // redo or quit
        printf("continue? 1 for yes and 0 for no\n");
        scanf("%d", &cont);
        if (!cont) {
            break;
        } else {
            xd = yd = yf = yd = 0;
            cleardevice();
            continue;
        }
    }
    closegraph();
}