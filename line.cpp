#include <graphics.h>
#include <stdio.h>

void drawLine(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;  // Step for x
    int sy = (y0 < y1) ? 1 : -1;  // Step for y
    int err = dx - dy;  // Error term

    while (1) {
        putpixel(x0, y0, WHITE);  // Draw the pixel at (x0, y0)
        if (x0 == x1 && y0 == y1) break;  // Exit when the end point is reached

        int e2 = 2 * err;
        if (e2 > -dy) {  // Adjust error term for x direction
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {  // Adjust error term for y direction
            err += dx;
            y0 += sy;
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    int x0 = 100, y0 = 100, x1 = 200, y1 = 300;  // Define start and end points
    drawLine(x0, y0, x1, y1);

    getch();  // Wait for a key press
    closegraph();  // Close the graphics mode
    return 0;
}
