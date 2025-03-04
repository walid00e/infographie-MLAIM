#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <unistd.h>

// Vos fonctions existantes

// Dessiner le repère 3D
void repere3D(int longueur) {
    int centreX = getmaxx() / 2;
    int centreY = getmaxy() / 2;

    // Axe X (ancien Y)
    line(centreX, centreY, centreX + longueur, centreY);
    outtextxy(centreX + longueur, centreY, (char *)"Y");

    // Axe Y (ancien Z)
    line(centreX, centreY, centreX, centreY - longueur);
    outtextxy(centreX, centreY - longueur, (char *)"Z");

    // Axe Z (ancien X)
    line(centreX, centreY, centreX - longueur, centreY + longueur);
    outtextxy(centreX - longueur, centreY + longueur, (char *)"X");
}

// Produit matriciel d'une matrice 8x4 par une matrice 4x4
void produitMatriciel8x4(double matrice[8][4], double transformation[4][4], double resulta[8][4]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            resulta[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                resulta[i][j] += matrice[i][k] * transformation[k][j];
            }
        }
    }
}

// Effectuer la projection perspective d'une matrice de points 3D en 2D
void projectionPerspective(double points[8][4], double proj[8][2]) {
    // double T[4][4] = {
    //     {1, 0, 0, 0},
    //     {0, 1, 0, 0},
    //     {0, 0, 0, -1.0/1000},
    //     {0, 0, 1000, 2}
    // };
    // Autre matrice de transformation proposée (commentée)
    double T[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, (-1.0/1000)},
        {0, 0, 0, 1}
    };

    double pointsProj[8][4];
    produitMatriciel8x4(points, T, pointsProj);
    for (int i = 0; i < 8; i++) {
        double w = pointsProj[i][3];
        proj[i][0] = pointsProj[i][0] / w;
        proj[i][1] = pointsProj[i][1] / w;
    }
}

// Dessiner la projection de l'objet (parallélépipède) en perspective
void dessinerProjection(double points[8][4]) {
    double proj[8][2];
    projectionPerspective(points, proj);
    int centreX = getmaxx() / 2;
    int centreY = getmaxy() / 2;

    // Définition des arêtes reliant les sommets
    int aretes[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    // Dessiner les arêtes
    for (int i = 0; i < 12; i++) {
        line(centreX + (int)proj[aretes[i][0]][0], centreY - (int)proj[aretes[i][0]][1],
             centreX + (int)proj[aretes[i][1]][0], centreY - (int)proj[aretes[i][1]][1]);
    }

    // Étiqueter les sommets
    char etiquettes[8] = {'A','B','C','D','E','F','G','H'};
    for (int i = 0; i < 8; i++) {
        char str[2] = {etiquettes[i], '\0'};
        outtextxy(centreX + (int)proj[i][0], centreY - (int)proj[i][1], str);
    }
}

// -------------------------------------------------------------------------
// Dessiner le plan de projection et les axes X et Y
void dessinerPlanProjection() {
    int centreX = getmaxx() / 2;
    int centreY = getmaxy() / 2;

    // Dessiner l'axe X (horizontal)
    line(centreX - 400, centreY, centreX + 400, centreY);
    outtextxy(centreX + 410, centreY, (char *)"X");

    // Dessiner l'axe Y (vertical)
    line(centreX, centreY - 400, centreX, centreY + 400);
    outtextxy(centreX, centreY - 410, (char *)"Y");
}

// -------------------------------------------------------------------------
// Programme principal
int main() {
    int gd = DETECT, gm;
    initwindow(900, 900, "Projection en perspective");

    int coef = 3;
    double x = 100 * coef, y = 50 * coef, z = 20 * coef;

    double parallelepipede[8][4] = {
        {0, 0, 0, 1},    // A
        {x, 0, 0, 1},    // B
        {x, y, 0, 1},    // C
        {0, y, 0, 1},    // D
        {0, 0, z, 1},    // E
        {x, 0, z, 1},    // F
        {x, y, z, 1},    // G
        {0, y, z, 1}     // H
    };

    dessinerPlanProjection();      // Dessiner le plan de projection
    dessinerProjection(parallelepipede); // Dessiner l'objet en perspective

    getch();
    closegraph();
    return 0;
}
