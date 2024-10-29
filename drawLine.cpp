#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

void drawLine() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*
    )"");

    int x1, y1, x2, y2;

    // Input validation loop - crucial for robustness.
    while (1) {
        printf("Enter starting point (x1, y1): ");
        if (scanf("%d %d", &x1, &y1) == 2 && x1 >= 0 && x1 < getmaxx() && y1 >= 0 && y1 < getmaxy()) {
            break; // Valid input, exit loop
        }
        printf("Invalid input. Please enter integers within the screen dimensions.\n");
        while (getchar() != '\n'); // Clear the input buffer to avoid infinite loop on bad input
    }
    while (1) {
        printf("Enter ending point (x2, y2): ");
        if (scanf("%d %d", &x2, &y2) == 2 && x2 >= 0 && x2 < getmaxx() && y2 >= 0 && y2 < getmaxy()) {
            break;
        }
        printf("Invalid input. Please enter integers within the screen dimensions.\n");
        while (getchar() != '\n');
    }

    line(x1, y1, x2, y2);

    getch();
    closegraph();
}


int main() {
    drawLine();
    return 0;
}
