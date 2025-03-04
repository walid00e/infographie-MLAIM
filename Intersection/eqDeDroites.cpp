#include <stdio.h>
#include <graphics.h>

void initGraph() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");
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

void methodeEquations(int xa, int ya, int xb, int yb, int xc, int yc, int xd, int yd){
    float x, y;
    float det = (xb - xa) * (yc - yd) - (yb - ya) * (xc - xd);
    if (det == 0) {
        printf("droites paralleles\n");
        return;
    }
    float t1 = ((xc - xa) * (yc - yd) - (yc - ya) * (xc - xd)) / det;
    float t2 = ((xb - xa) * (yc - ya) - (yb - ya) * (xc - xa)) / det;
    if(t1 <= 1 && t1 >= 0 && t2 <= 1 && t2 >= 0){
        printf("intersection\n");
        x = xa + (xb - xa) * t1;
        y = ya + (yb - ya) * t1;
        printf("(x, y) : (%f, %f)\n", x, y);
        line(0,0,x,y);
    }
}

int main(){
    int xmin, ymin, xmax, ymax, xd, yd, xf, yf, cont;
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
        xmin = res[0];
        ymin = res[1];
        // capture de pt finale
        captureClick(res);
        xmax = res[0];
        ymax = res[1];
        // draw the Line
        printf("(%d, %d) -> (%d, %d)\n", xmin, ymin, xmax, ymax);
        line(xmin, ymin, xmax, ymax);
        // capture the point de depart de segement
        captureClick(res);
        xd = res[0];
        yd = res[1];
        // capture the point finale de segement
        captureClick(res);
        xf = res[0];
        yf = res[1];
        // draw the segement
        line(xd, yd, xf, yf);
        // find the intersection
        methodeEquations(xd, yd, xf, yf, xmin, ymin, xmax, ymax);
        // redo or quit
        printf("continue? 1 for yes and 0 for no\n");
        scanf("%d", &cont);
        if (!cont) {
            break;
        } else {
            xmin = ymin = xmax = ymax = 0;
            cleardevice();
            setcolor(WHITE);
            continue;
        }
    }
    closegraph();

}