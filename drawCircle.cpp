#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void drawCircle() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *)"");

    int x, y, radius;

    // Input validation loop - crucial for robustness.
    while (1) {
        printf("Enter center coordinates (x, y): ");
        if (scanf("%d %d", &x, &y) == 2 && x >= 0 && x < getmaxx() && y >= 0 && y < getmaxy()) {
            break;
        }
        printf("Invalid input. Please enter integers within the screen dimensions.\n");
        while (getchar() != '\n'); // Clear input buffer.
    }

    while(1){
        printf("Enter radius: ");
        if (scanf("%d", &radius) == 1 && radius > 0) {
            break;
        }
        printf("Invalid input. Please enter a positive integer for the radius.\n");
        while (getchar() != '\n');
    }

    circle(x, y, radius);

    getch(); // Pause before closing
    closegraph();
}


int main() {
    drawCircle();
    return 0;
}