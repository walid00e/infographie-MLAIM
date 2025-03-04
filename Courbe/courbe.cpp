#include <graphics.h>
#include <math.h>

// Fonction de base B-spline pour tout degré
float basis_function(int i, int k, float t, float knots[]) {
    if (k == 1) {
        return (knots[i] <= t && t < knots[i + 1]) ? 1.0 : 0.0;
    }
    float left = 0.0, right = 0.0;

    if (knots[i + k - 1] - knots[i] != 0) {
        left = (t - knots[i]) / (knots[i + k - 1] - knots[i]) * basis_function(i, k - 1, t, knots);
    }

    if (knots[i + k] - knots[i + 1] != 0) {
        right = (knots[i + k] - t) / (knots[i + k] - knots[i + 1]) * basis_function(i + 1, k - 1, t, knots);
    }

    return left + right;
}

// Fonction pour tracer une B-spline
void b_spline(float points[][2], int n, int degree) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // Générer les noeuds
    int knot_count = n + degree + 1;
    float knots[knot_count];
    for (int i = 0; i < knot_count; i++) {
        if (i < degree) {
            knots[i] = 0;
        } else if (i >= n + 1) {
            knots[i] = 1;
        } else {
            knots[i] = (float)(i - degree + 1) / (n - degree + 2);
        }
    }

    // Tracer la courbe B-spline
    float x, y;
    for (float t = 0; t <= 1; t += 0.001) {
        x = 0;
        y = 0;
        for (int i = 0; i <= n; i++) {
            float b = basis_function(i, degree, t, knots);
            x += b * points[i][0];
            y += b * points[i][1];
        }
        putpixel((int)x, (int)y, WHITE);
    }

    // Dessiner les lignes entre les points de contrôle
    setcolor(YELLOW); // Couleur des lignes
    for (int i = 0; i < n; i++) {
        line((int)points[i][0], (int)points[i][1], (int)points[i + 1][0], (int)points[i + 1][1]);
    }

    // Dessiner les points de contrôle
    for (int i = 0; i <= n; i++) {
        setcolor(RED);
        circle((int)points[i][0], (int)points[i][1], 5);
        floodfill((int)points[i][0], (int)points[i][1], RED);
    }

    getch();
    closegraph();
}

int main() {
    // Points de contrôle pour M=6 (6 points nécessaires)
    float points[6][2] = {
        {100, 400}, {200, 300}, {300, 200}, {400, 300}, {500, 400}, {600, 300}
    };
    int n = 5;       // Nombre de segments (n=nombre de points-1)
    int degree = 6;  // Degré de la B-spline (quintique pour M=6)

    // Tracer la courbe B-spline quintique
    b_spline(points, n, degree);

    return 0;
}