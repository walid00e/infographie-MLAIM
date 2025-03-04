#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>

void repere3d(int longueur) {
 int centreX = getmaxx() / 2;
 int centreY = getmaxy() / 2;

 // Axe X
 line(centreX, centreY, centreX + longueur, centreY);
 outtextxy(centreX + longueur, centreY, (char *)"X");

 // Axe Y
 line(centreX, centreY, centreX, centreY - longueur);
 outtextxy(centreX, centreY - longueur, (char *)"Y");

 // Axe Z
 line(centreX, centreY, centreX - longueur, centreY + longueur);
 outtextxy(centreX - longueur, centreY + longueur, (char *)"Z");
}

void dessinerParallelepipede(double Parallelepipede[8][4]) {
 cleardevice();
 repere3d(300);
 int i;
 int projete[8][2];

 // Projection 2D des points 3D (projection cavaliere)
 for (i = 0; i < 8; i++) {
 projete[i][0] = getmaxx() / 2 + (int)(Parallelepipede[i][0] - Parallelepipede[i][2] * 0.5); // Projection X
 projete[i][1] = getmaxy() / 2 - (int)(Parallelepipede[i][1] - Parallelepipede[i][2] * 0.5); // Projection Y
 }

 // Relier les sommets pour dessiner les arêtes
 int aretes[12][2] = {
 {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Base (ABCD)
 {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Haut (EFGH)
 {0, 4}, {1, 5}, {2, 6}, {3, 7} // Colonnes (AE, BF, CG, DH)
 };

 // Dessiner les arêtes
 for (i = 0; i < 12; i++) {
 line(projete[aretes[i][0]][0], projete[aretes[i][0]][1],
 projete[aretes[i][1]][0], projete[aretes[i][1]][1]);
 }

 // etiqueter les points
 char etiquettes[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
 for (i = 0; i < 8; i++) {
 char str[2];
 str[0] = etiquettes[i];
 str[1] = '\0';
 outtextxy(projete[i][0], projete[i][1], str);
 }
}

void rotationAutourAxeBH(double Parallelepipede[8][4], double angle) {
 // Points B et H définissent l'axe de rotation
 double B[3] = {Parallelepipede[1][0], Parallelepipede[1][1], Parallelepipede[1][2]};
 double H[3] = {Parallelepipede[7][0], Parallelepipede[7][1], Parallelepipede[7][2]};

 // Vecteur de l'axe BH
 double axe[3] = {H[0] - B[0], H[1] - B[1], H[2] - B[2]};

 // Normalisation du vecteur de l'axe
 double norme = sqrt(axe[0] * axe[0] + axe[1] * axe[1] + axe[2] * axe[2]);
 double n1 = axe[0] / norme;
 double n2 = axe[1] / norme;
 double n3 = axe[2] / norme;

 // Matrice de rotation autour d'un axe arbitraire
 double c = cos(angle);
 double s = sin(angle);
 double t = 1 - c;

 double matriceRotation[4][4] = {
 {t * n1 * n1 + c, t * n1 * n2 - s * n3, t * n1 * n3 + s * n2, 0},
 {t * n1 * n2 + s * n3, t * n2 * n2 + c, t * n2 * n3 - s * n1, 0},
 {t * n1 * n3 - s * n2, t * n2 * n3 + s * n1, t * n3 * n3 + c, 0},
 {0, 0, 0, 1}
 };

 // Matrice de translation pour déplacer l'axe à l'origine
 double matriceTranslation[4][4] = {
 {1, 0, 0, 0},
 {0, 1, 0, 0},
 {0, 0, 1, 0},
 {-B[0], -B[1], -B[2], 1}
 };

 // Matrice de translation inverse pour ramener l'axe à sa position d'origine
 double matriceTranslationInverse[4][4] = {
 {1, 0, 0, 0},
 {0, 1, 0, 0},
 {0, 0, 1, 0},
 {B[0], B[1], B[2], 1}
 };

 // Appliquer la transformation à chaque point
 for (int i = 0; i < 8; i++) {
 double point[4] = {Parallelepipede[i][0], Parallelepipede[i][1], Parallelepipede[i][2], 1};

 // Appliquer la translation
 double pointTranslated[4] = {0, 0, 0, 0};
 for (int j = 0; j < 4; j++) {
 for (int k = 0; k < 4; k++) {
 pointTranslated[j] += point[k] * matriceTranslation[k][j];
 }
 }

 // Appliquer la rotation
 double pointRotated[4] = {0, 0, 0, 0};
 for (int j = 0; j < 4; j++) {
 for (int k = 0; k < 4; k++) {
 pointRotated[j] += pointTranslated[k] * matriceRotation[k][j];
 }
 }

 // Appliquer la translation inverse
 double pointFinal[4] = {0, 0, 0, 0};
 for (int j = 0; j < 4; j++) {
 for (int k = 0; k < 4; k++) {
 pointFinal[j] += pointRotated[k] * matriceTranslationInverse[k][j];
 }
 }

 // Mettre à jour les coordonnées du point
 Parallelepipede[i][0] = pointFinal[0];
 Parallelepipede[i][1] = pointFinal[1];
 Parallelepipede[i][2] = pointFinal[2];
 }
}

int main() {
 int gd = DETECT, gm;
 initwindow(900, 900, "Rotation Continue du Parallelepipede");

 double Parallelepipede[8][4] = {
 {0, 0, 0, 1}, // A
 {200, 0, 0, 1}, // B
 {200, 100, 0, 1},// C
 {0, 100, 0, 1}, // D
 {0, 0, 100, 1}, // E
 {200, 0, 100, 1},// F
 {200, 100, 100, 1},// G
 {0, 100, 100, 1} // H
 };

 double angle = 0.01; // Angle de rotation (petit pour une rotation lente)
 int vitesse = 50; // Delai en millisecondes pour contrôler la vitesse

 while (!kbhit()) { // Boucle infinie jusqu'à ce qu'une touche soit pressee
 // Appliquer la rotation
 rotationAutourAxeBH(Parallelepipede, angle);

 // Dessiner le parallelepipede apres rotation
 cleardevice();
 repere3d(300);
 dessinerParallelepipede(Parallelepipede);

 // Contrôler la vitesse de rotation
 delay(vitesse);
 }

 closegraph();
 return 0;
}