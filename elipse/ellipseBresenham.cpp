#include<stdio.h>
#include<math.h>
#include<graphics.h>

void init_graph() {
    int g = DETECT, m;
    initgraph(&g, &m, (char*)"C:\\TC\\BGI");
}

void repere() {
    cleardevice();
    line(0, 240, 640, 240);
    line(320, 0, 320, 480);
}

void pixel(int x, int y, int color) {
    x = x + 320;
    y = 240 - y;
    putpixel(x, y, color);
}

void ellipseBresenham(int a, int b, int xc, int yc) {
    int x = 0, y = b;
    int p;
    int px = 0, py = 2*pow(a,2) * y;

    // Partie 1
    p = round(pow(b,2) - (pow(a,2) * b) + (0.25 * pow(a,2)));
    while (px < py) {
        pixel(xc + x, yc + y, WHITE);
        pixel(xc - x, yc + y, WHITE);
        pixel(xc + x, yc - y, WHITE);
        pixel(xc - x, yc - y, WHITE);
        x++;
        px += 2*pow(b,2);
        if (p < 0) {
            p += pow(b,2) + px;
        } else {
            y--;
            py -= 2*pow(a,2);
            p += pow(b,2) + px - py;
        }
    }

    // Partie 2
    p = round(pow(b,2) * (x + 0.5) * (x + 0.5) + pow(a,2) * (y - 1) * (y - 1) - pow(a,2) * pow(b,2));
    while (y > 0) {
        pixel(xc + x, yc + y, WHITE);
        pixel(xc - x, yc + y, WHITE);
        pixel(xc + x, yc - y, WHITE);
        pixel(xc - x, yc - y, WHITE);
        y--;
        py -= 2*pow(a,2);
        if (p > 0) {
            p += pow(a,2) - py;
        } else {
            x++;
            px += 2*pow(b,2);
            p += pow(a,2) - py + px;
        }
    }
}

void drawFlower(int a, int b, int xc, int yc, int numPetals) {
    for (int i = 0; i < numPetals; i++) {
        float angle = i * 2 * M_PI / numPetals; // Divide the circle evenly
        int rotatedX = round(xc + a * cos(angle));
        int rotatedY = round(yc + b * sin(angle));
        ellipseBresenham(a, b, rotatedX, rotatedY);
    }
}

int main() {
    int h, k, a, b;
    
    init_graph();

    while(true){
        printf("Donner les coordonnes du centre (h, k):\n");
        scanf("%d %d", &h, &k);
        printf("Donner les demi-axes de l'ellipse (a, b):\n");
        scanf("%d %d", &a, &b);

        repere();
        ellipseBresenham(a, b, h, k);
    }
    

    getch();

}

