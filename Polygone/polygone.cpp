#include <stdio.h>
#include <graphics.h>
#include <math.h>

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
    int xf, yf, cont;
    initGraph();
    // allocation de memoir de table
    int* res = (int*) malloc(2 * sizeof(int));  
    if (res == NULL) {                   
        printf("Memory allocation failed\n");
        return 0;
    }
    // logic
    while(true){
        int n, x, y, xd, yd;
        printf("donner le nomber des points:\n");
        scanf("%d", &n);
        int pts[n+1][2];
        for(int i=0; i<n; i++){
            // capture de pt
            captureClick(res);
            if(i>0){
                line(x,y,res[0],res[1]);
            } else {
                xd = res[0];
                yd = res[1];
            }
            pts[i][1] = x = res[0];
            pts[i][2] = y = res[1];
            if(i==n-1){
                line(x,y,xd,yd);
            }
        }
        pts[n][1] = pts[0][1];
        pts[n][2] = pts[0][2];

        printf("point finale:\n");
        captureClick(res);
        xf = res[0];
        yf = res[1];
        
        double s = 0, alpha, prod, d1, d2;
        for (int i = 0; i <= n; i++) {
            printf("(i)-(%d)\n",i);
            printf("(x,y)-(%d,%d)\n", pts[i][1], pts[i][2]);
            line(pts[i][1], pts[i][2], xf, yf);
            if (i > 0) {
                prod = (pts[i][1] - xf) * (pts[i-1][1] - xf) + (pts[i][2] - yf) * (pts[i-1][2] - yf);
                d1 = sqrt(pow(pts[i-1][1] - xf, 2) + pow(pts[i-1][2] - yf, 2));
                d2 = sqrt(pow(pts[i][1] - xf, 2) + pow(pts[i][2] - yf, 2));

                double cosine = prod / (d1 * d2);
                if (cosine > 1.0) cosine = 1.0;
                if (cosine < -1.0) cosine = -1.0;

                alpha = acos(cosine);
                s += alpha;

                printf("prod = %f\n", prod);
                printf("d1 = %f\n", d1);
                printf("d2 = %f\n", d2);
                printf("alpha = %f\n", alpha);
                printf("s = %f\n", s);
            }
            if(i == n-1){
                
            }
        }
        if (fabs(s - 2 * M_PI) < 1e-6) {
            printf("Point a l'interieur polygon.\n");
        } else {
            printf("Point a l'exterieur polygon.\n");
        }
                    
        // redo or quit
        printf("continue? 1 for yes and 0 for no\n");
        scanf("%d", &cont);
        if (!cont) {
            break;
        } else {
            xf = yf = 0;
            cleardevice();
            setcolor(WHITE);
            continue;
        }
    }
    closegraph();

}