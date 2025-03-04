#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

void ligneBresenham(int xd, int yd, int xf, int yf) {
    int x, y, s, i, dy, dx, incX, incY;

    dx = abs(xf - xd);
    dy = abs(yf - yd);

    if (xf >= xd) {
        putpixel(xd, yd, WHITE);
        incX = 1;
    } else {
        putpixel(xf, yf, WHITE);
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
            putpixel(x, y, WHITE);

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
            putpixel(x, y, WHITE);

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

void captureClick(int* res) {
    int x ,y;
    // getting click coords
    boolean init = false;
    while (!kbhit()) {  // Loop until a key is pressed
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            printf("Clicked at: (%d, %d)\n", x, y);
            putpixel(x, y, WHITE);  // Visual feedback for the click
            res[0] = x;
            res[1] = y;
            return;
        }
    }
    closegraph();
}

void initGraph() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");
}

int main(){
    int xd, xf, yd, yf, cont;
    
    initGraph();
    // allocation de memoir de table
    int* res = (int*) malloc(2 * sizeof(int));  
    if (res == NULL) {                   
        printf("Memory allocation failed\n");
        return 0;
    }
    // logic
    while(true){
        // capture de pt depart
        captureClick(res);
        xd = res[0];
        yd = res[1];
        // capture de pt finale
        captureClick(res);
        xf = res[0];
        yf = res[1];
        // draw the line
        printf("(%d, %d) -> (%d, %d)\n", xd, yd, xf, yf);
        ligneBresenham(xd, yd, xf, yf);
        // redo or quit
        printf("continue? 1 for yes and 0 for no\n");
        scanf("%d", &cont);
        if (!cont) {
            break;
        } else {
            xd = yd = xf = yf = 0;
            cleardevice();
            continue;
        }
    }
    closegraph();
}