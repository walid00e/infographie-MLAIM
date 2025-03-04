#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>

// Dessiner une pétale (ellipse tournante) en utilisant des segments de ligne.
void dessinerPetale(int centreX, int centreY, int a, int b, float angle) {
    const int numSegments = 100; // Définit le nombre de segments
    const float stepAngleDeg = 360.0 / numSegments; // Calcule l'angle par segment

    for (int i = 0; i <= numSegments; i++) {
        float t = i * stepAngleDeg * M_PI / 180.0f; // Conversion en radians
        // Calcul du point de l'ellipse tournante
        int x = centreX + a * cos(t) * cos(angle) - b * sin(t) * sin(angle);
        int y = centreY + a * cos(t) * sin(angle) + b * sin(t) * cos(angle);
        if (i == 0)
            moveto(x, y);
        else
            lineto(x, y);
    }
}

// Dessiner une fleur avec un nombre dynamique de pétales.
// Seuls les coordonnées du centre et le nombre de pétales sont passés en paramètres.
void dessinerFleur(int centreX, int centreY, int nbPetales, int rayonCentre, int petaleA, int petaleB) {
    int distancePetale = rayonCentre + petaleA / 2;  // Distance du centre au centre de la pétale

    // Dessiner le cercle central
    circle(centreX, centreY, rayonCentre);

    // Dessiner chaque pétale, réparties uniformément autour du centre
    for (int i = 0; i < nbPetales; i++) {
        // Calculer l'angle pour la pétale courante (en radians)
        float angle = i * 2 * M_PI / nbPetales;
        // Déterminer le centre de la pétale pour qu'elle soit à distancePetale du centre de la fleur
        int px = centreX + distancePetale * cos(angle);
        int py = centreY + distancePetale * sin(angle);
        // Dessiner la pétale avec sa rotation réglée sur l'angle courant
        dessinerPetale(px, py, petaleA / 2, petaleB / 2, angle);
    }
}

void Ellipse(int xc, int yc, int a, int b, float angle) {
    int i;
    float theta, x, y, xr, yr;

    // Convertir l'angle en radians
    float radian = angle * M_PI / 180;

    for (i = 0; i < 360; i++) {
        theta = i * M_PI / 180; // Conversion de l'angle en radians

        // Coordonnées paramétriques de l'ellipse
        x = a * cos(theta);
        y = b * sin(theta);

        // Rotation de l'ellipse
        xr = xc + x * cos(radian) - y * sin(radian);
        yr = yc + x * sin(radian) + y * cos(radian);

        putpixel(xr, yr, YELLOW);
    }
}

void fleur(){
    setcolor(YELLOW);
    circle(getmaxx()/2,getmaxy()/2,50);
    int a = 50;
    int b = 100;
    Ellipse(getmaxx()/2,150 + getmaxy()/2,  a, b, 0);
    Ellipse(getmaxx()/2 - 125,getmaxy()/2 + 80,  a,  b, 60);
    Ellipse(getmaxx()/2 - 125,getmaxy()/2 - 75,  a,  b, 120);
    Ellipse(getmaxx()/2,getmaxy()/2 - 150,  a,  b, 180);
    Ellipse(getmaxx()/2 +125,getmaxy()/2 -75,  a,  b, 240);
    Ellipse(getmaxx()/2 + 125,getmaxy()/2 + 75,  a,  b, 300);
    getch(); // Attendre une touche pour fermer
    closegraph();
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    // Dessiner la fleur au centre de la fenêtre (320,240)
    dessinerFleur(320, 240, 6, 50, 100, 50);
    getch();
    closegraph();
    return 0;
}
