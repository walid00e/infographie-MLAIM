#include <stdio.h>
#include <graphics.h>

void pixel(int x, int y, int color) {
    x = x + 320;
    y = 240 - y;
    putpixel(x, y, color);
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

void cercleBres(int h, int k, int r){
    if(r>0){
        int x = 0;
        int y = r;
        int d = 3 - 2*r;
        int i = 0;
        while(x <= y){
            pixel(x+h, y+k, WHITE);
            pixel(-x+h, -y+k, WHITE);

            pixel(y+h, x+k, WHITE);
            pixel(-y+h, -x+k ,WHITE);

            pixel(-y+h, x+k, WHITE);
            pixel(y+h, -x+k ,WHITE);

            pixel(-x+h, y+k, WHITE);
            pixel(x+h, -y+k, WHITE);

            if(d > 0){
                d += 4*(x-y) + 10;
                x++;
                y--;
            } else {
                d += 4*x + 6;
                x++;
            }
        }
    }
}

int main(){
    int h, k, r, cont;
    
    initGraph();
    
    // logic
    while(true){
        repere();
        // capture de centre
        printf("centre de cercle (h,k): \n");
        scanf("%d%d",&h, &k);
        // capture rayon
        printf("rayon de cercle: \n");
        scanf("%d",&r);
        // draw the cercle
        cercleBres(h, k, r);
        // redo or quit
        printf("continue? 1 for yes and 0 for no\n");
        scanf("%d", &cont);
        if (!cont) {
            break;
        } else {
            h = k = r = 0;
            cleardevice();
            continue;
        }
    }
    closegraph();
}