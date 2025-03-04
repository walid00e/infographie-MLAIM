#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

// Définition d'un type pour représenter un point 2D
typedef struct {
    double x, y;
} Point2D;

// Fonction qui calcule la factorielle d'un entier n
unsigned long factorielle(int n) {
    unsigned long f = 1;
    for (int i = 2; i <= n; i++)
        f *= i;
    return f;
}

// Fonction qui calcule le coefficient binomial C(n, i)
unsigned long coefficientBinomial(int n, int i) {
    return factorielle(n) / (factorielle(i) * factorielle(n - i));
}

// Fonction qui calcule le polynôme de Bernstein Φ_i^n(t)
double Bernstein(int i, int n, double t) {
    return coefficientBinomial(n, i) * pow(t, i) * pow(1 - t, n - i);
}

// Fonction pour récupérer les points de contrôle de la courbe de Bézier
// On définit ici les 6 points de contrôle : B0, B1, B2, B3, B4 et B5.
void recupererPointsControle(Point2D points[6]) {
    points[0].x = 0;    points[0].y = 0;
    points[1].x = 200;  points[1].y = 100;
    points[2].x = 300;  points[2].y = 0;
    points[3].x = 350;  points[3].y = 75;
    points[4].x = 450;  points[4].y = 120;
    points[5].x = 600;  points[5].y = 0;
}

// Fonction qui calcule le point P(t) de la courbe de Bézier d'ordre 5
Point2D calculerPointBezier(Point2D points[6], double t) {
    int n = 5; // degré = 5
    Point2D P = {0, 0};
    for (int i = 0; i <= n; i++) {
        double phi = Bernstein(i, n, t);
        P.x += points[i].x * phi;
        P.y += points[i].y * phi;
    }
    return P;
}

// Fonction pour dessiner le repère (axes horizontaux et verticaux avec graduations)
// On considère que l'origine du repère est placée en (origineX, origineY)
void dessinerRepere(int origineX, int origineY) {
    int maxX = getmaxx();
    int maxY = getmaxy();
    setcolor(WHITE);

    // Axe horizontal (X)
    line(0, origineY, maxX, origineY);
    outtextxy(maxX - 20, origineY + 5, "X");

    // Axe vertical (Y)
    line(origineX, 0, origineX, maxY);
    outtextxy(origineX - 20, 20, "Y");

    // Graduations horizontales (tous les 50 pixels)
    char tampon[10];
    for (int x = origineX; x <= maxX; x += 50) {
        line(x, origineY - 3, x, origineY + 3);
        sprintf(tampon, "%d", x - origineX);
        outtextxy(x - 10, origineY + 5, tampon);
    }

    // Graduations verticales (tous les 50 pixels)
    // On incrémente en descendant (l'axe Y est inversé dans notre affichage)
    for (int y = origineY; y >= 0; y -= 50) {
        line(origineX - 3, y, origineX + 3, y);
        sprintf(tampon, "%d", origineY - y);
        outtextxy(origineX + 5, y - 5, tampon);
    }
}

// Fonction principale
int main() {
    int gd = DETECT, gm;
    initwindow(900, 500, "Bezier");

    // Définir l'origine pour le repère et pour le tracé (translation)
    // On choisit (50, 400) comme origine de notre repère
    int origineX = 50, origineY = 400;

    // Dessiner le repère (axes et graduations)
    dessinerRepere(origineX, origineY);

    // Récupérer les points de contrôle
    Point2D points[6];
    recupererPointsControle(points);

    // Afficher dans la console P(0), P(0.5) et P(1)
    Point2D P0   = calculerPointBezier(points, 0.0);
    Point2D P05  = calculerPointBezier(points, 0.5);
    Point2D P1   = calculerPointBezier(points, 1.0);
    printf("P(0)   = (%.2f, %.2f)\n", P0.x, P0.y);
    printf("P(0.5) = (%.2f, %.2f)\n", P05.x, P05.y);
    printf("P(1)   = (%.2f, %.2f)\n", P1.x, P1.y);

    // Tracer le polygone de contrôle (en rouge)
    setcolor(RED);
    for (int i = 0; i < 5; i++) {
        line((int)(points[i].x + origineX), origineY - (int)points[i].y,
             (int)(points[i+1].x + origineX), origineY - (int)points[i+1].y);
    }

    // Tracer les points de contrôle et leurs étiquettes (B0, B1, ..., B5)
    char etiquette[3];
    for (int i = 0; i < 6; i++) {
        int px = (int)(points[i].x + origineX);
        int py = origineY - (int)points[i].y;
        circle(px, py, 3);
        sprintf(etiquette, "B%d", i);
        outtextxy(px + 5, py - 5, etiquette);
    }

    // Tracer la courbe de Bézier (en jaune)
    setcolor(YELLOW);
    Point2D precedent = calculerPointBezier(points, 0.0);
    int precX = (int)(precedent.x + origineX);
    int precY = origineY - (int)precedent.y;
    for (double t = 0.01; t <= 1.0; t += 0.01) {
        Point2D courant = calculerPointBezier(points, t);
        int courX = (int)(courant.x + origineX);
        int courY = origineY - (int)courant.y;
        line(precX, precY, courX, courY);
        precX = courX;
        precY = courY;
    }

    getch();
    closegraph();
    return 0;
}
