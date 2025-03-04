#include <stdio.h>
#include <graphics.h>

void canvas(int xmin, int ymin, int xmax, int ymax){
    line(0,ymin,640,ymin);
    line(xmin,0,xmin,480);
    line(0,ymax,640,ymax);
    line(xmax,0,xmax,480);
}

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

void algoCohen(int x, int y, int xmin, int ymin, int xmax, int ymax, int* res){
    res[0] = (y-ymax) >= 0 ? 1 : 0;
    res[1] = (ymin-y) >= 0 ? 1 : 0;
    res[2] = (x-xmax) >= 0 ? 1 : 0;
    res[3] = (xmin-x) >= 0 ? 1 : 0;
    printf("res=%i%i%i%i\n", res[0],res[1],res[2],res[3]);
}

int statusDeSegement(int *resD, int *resF){
    boolean visible = true;
    boolean candidat = true;
    int res[4];
    printf("status: ");
    for(int i=0; i<4; i++){
        res[i] = (resD[i] && resF[i]);
        if (resD[i] != 0 || resF[i] != 0) {
            visible = false; 
        }
        if(res[i] != 0){
            candidat = false;
        }
    }
    if(visible){
        printf("visible\n");
        return 1;
    } else {
        if(candidat){
            printf("candidat\n");
            return 2;
        } else {
            printf("invisible\n");
            return 3;
        }
    }
    
}

int checkPoints(int *resD, int *resF){
    boolean firstPoint = true;
    boolean secondPoint = true;
    for(int i=0; i<4; i++){
        if(resD[i])
            firstPoint = false;
    }
    for(int i=0; i<4; i++){
        if(resF[i])
            secondPoint = false;
    }
    if(firstPoint && secondPoint){
        return 3;
    }else{
        if(firstPoint)
            return 1;
        else 
            return 2;
    }
}

void methodeDichotomique(int xd, int yd, int xf, int yf, int xmin, int ymin, int xmax, int ymax){
    int resD[4], resF[4];
    int x,y;
    algoCohen(xd, yd, xmin, ymin, xmax, ymax, resD);
    algoCohen(xf, yf, xmin, ymin, xmax, ymax, resF);
    int check = checkPoints(resD, resF);
    if(check == 1){
        x = xd;
        y = yd;
    } else {
        if(check == 2){
            x = xf;
            y = yf;
        } else{
            // calcule de deux point
        }
    }
    int xm, ym, i=0;
    while(i<100){
        xm = (xd + xf) / 2;
        ym = (yd + yf) / 2;
        algoCohen(xd, yd, xmin, ymin, xmax, ymax, resD);
        algoCohen(xm, ym, xmin, ymin, xmax, ymax, resF);
        if(statusDeSegement(resD, resF)==2){
            xf = xm;
            yf = ym;
        } else {
            algoCohen(xm, ym, xmin, ymin, xmax, ymax, resD);
            algoCohen(xf, yf, xmin, ymin, xmax, ymax, resF);
            if(statusDeSegement(resD, resF)==2){
                xd = xm;
                yd = ym;
            } else {
                printf("found\n");
                break;
            }
        }
        printf("(%d, %d) -> (%d, %d)\n", xd, yd, xf, yf);
        i++;
    }
    cleardevice();
    canvas(xmin, ymin, xmax, ymax);
    line(x, y, xm, ym);

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
        // draw the canvas
        printf("(%d, %d) -> (%d, %d)\n", xmin, ymin, xmax, ymax);
        canvas(xmin, ymin, xmax, ymax);
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
        // check for cohen
        int resD[4], resF[4];
        algoCohen(xd, yd, xmin, ymin, xmax, ymax, resD);
        algoCohen(xf, yf, xmin, ymin, xmax, ymax, resF);
        int status = statusDeSegement(resD, resF);
        if(status == 2){
            methodeDichotomique(xd, yd, xf, yf, xmin, ymin, xmax, ymax);
        }
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