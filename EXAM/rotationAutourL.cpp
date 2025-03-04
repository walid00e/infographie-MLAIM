#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <unistd.h>

// Variables globales pour stocker les dimensions d'origine
double orig_x, orig_y, orig_z;

// Dessiner le repère 3D
void repere3D(int longueur) {
    int centreX = getmaxx() / 2;
    int centreY = getmaxy() / 2;

    // Axe X (ancien Y)
    line(centreX, centreY, centreX + longueur, centreY);
    outtextxy(centreX + longueur, centreY, (char*)"Y");

    // Axe Y (ancien Z)
    line(centreX, centreY, centreX, centreY - longueur);
    outtextxy(centreX, centreY - longueur, (char*)"Z");

    // Axe Z (ancien X)
    line(centreX, centreY, centreX - longueur, centreY + longueur);
    outtextxy(centreX - longueur, centreY + longueur, (char*)"X");
}

// Dessiner le parallélépipède à partir d'une matrice 8x4
void dessinerParallelepipede(double parallelepipede[8][4]) {
    cleardevice();
    repere3D(300);
    int i;
    int projete[8][2];

    // Projection 2D des points 3D (projection cavalière)
    for (i = 0; i < 8; i++) {
        projete[i][0] = getmaxx() / 2 + (int)(parallelepipede[i][1] - parallelepipede[i][0] * 0.5); // Projection sur X (ancien Y)
        projete[i][1] = getmaxy() / 2 - (int)(parallelepipede[i][2] - parallelepipede[i][0] * 0.5); // Projection sur Y (ancien Z)
    }

    // Relier les sommets pour dessiner les arêtes
    int aretes[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Base (ABCD)
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Haut (EFGH)
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Colonnes (AE, BF, CG, DH)
    };

    // Dessiner les arêtes
    for (i = 0; i < 12; i++) {
        line(projete[aretes[i][0]][0], projete[aretes[i][0]][1],
             projete[aretes[i][1]][0], projete[aretes[i][1]][1]);
    }

    // Étiqueter les points
    char etiquettes[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    for (i = 0; i < 8; i++) {
        char str[2];
        str[0] = etiquettes[i];
        str[1] = '\0';
        outtextxy(projete[i][0], projete[i][1], str);
    }

    // Tracer la ligne AG
    line(projete[0][0], projete[0][1], projete[6][0], projete[6][1]);

    // Calculer le milieu de AG
    int milieuAG_x = (projete[0][0] + projete[6][0]) / 2;
    int milieuAG_y = (projete[0][1] + projete[6][1]) / 2;

    // La ligne L doit être verticale (variation uniquement sur Y)
    int longueurL = 100; // Longueur arbitraire pour la ligne L
    line(milieuAG_x, milieuAG_y - longueurL,
         milieuAG_x, milieuAG_y);
}

// Effectuer le produit matriciel d'une matrice 8x4 par une matrice 4x4
void produitMatriciel8x4(double matrice[8][4], double transformation[4][4], double resultat[8][4]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            resultat[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                resultat[i][j] += matrice[i][k] * transformation[k][j];
            }
        }
    }
}

// Copier une matrice 8x4 dans une autre
void copierMatrice(double dest[8][4], double src[8][4]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

// Rotation autour de l'axe Y
void rotationY(double cube[8][4], double angle, double resultat[8][4]) {
    double Ry[4][4] = {
        { cos(angle), 0, -sin(angle), 0 },
        { 0, 1, 0, 0 },
        { sin(angle), 0, cos(angle), 0 },
        { 0, 0, 0, 1 }
    };

    produitMatriciel8x4(cube, Ry, resultat);
}

// Rotation autour de l'axe Z
void rotationZ(double cube[8][4], double angle, double resultat[8][4]) {
    double Rz[4][4] = {
        { cos(angle), sin(angle), 0, 0 },
        { -sin(angle), cos(angle), 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 }
    };

    produitMatriciel8x4(cube, Rz, resultat);
}

// Translation
void translationMatrice(double cube[8][4], double tx, double ty, double tz, double resultat[8][4]) {
    double T[4][4] = {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { tx, ty, tz, 1 }
    };

    produitMatriciel8x4(cube, T, resultat);
}

// Afficher la matrice représentant la forme (pour le débogage)
void afficherForme(double cube[8][4]) {
    printf("Cube:\n{\n");
    for (int i = 0; i < 8; i++) {
        printf("\t{");
        for (int j = 0; j < 4; j++) {
            printf("%.2f, ", cube[i][j]);
        }
        printf("}\n");
    }
    printf("}\n");
}

// Rotation du cube autour de la ligne L
void rotationAutourL(double cube[8][4], double angle_deg, double resultat[8][4]) {
    double temp1[8][4], temp2[8][4], temp3[8][4], temp4[8][4];

    // Utilisation des dimensions d'origine
    double x = orig_x;  // par exemple : 100 * coef
    double y = orig_y;  // par exemple : 50 * coef
    double z = orig_z;  // par exemple : 20 * coef

    // Calcul des angles alpha et beta en radians
    double alpha = atan2(z, x);             // Rotation autour de Y pour aligner AG sur le plan XOY
    double beta = atan2(y, sqrt(x*x + z*z));    // Rotation autour de Z pour aligner AG sur X

    // 1. Rotation autour de Y par alpha
    rotationY(cube, alpha, temp1);
    // 2. Rotation autour de Z par beta (beta est déjà négatif)
    rotationZ(temp1, -beta, temp2);
    // 3. Translation le long de X pour amener le milieu de AG à l'origine
    //    tx est constant et calculé à partir des dimensions d'origine
    double tx = -(sqrt(x * x + z * z + y * y) / 2.0);
    translationMatrice(temp2, tx, 0, 0, temp3);
    // 4. Rotation incrémentale autour de Z par angle_deg (converti en radians)
    rotationZ(temp3, angle_deg * M_PI / 180.0, temp4);
    // 5. Inversion des transformations
    translationMatrice(temp4, -tx, 0, 0, temp3);    // Inversion de la translation
    rotationZ(temp3, beta, temp2);                  // Inversion de la rotation autour de Z
    rotationY(temp2, -alpha, resultat);              // Inversion de la rotation autour de Y
}

int main() {
    int gd = DETECT, gm;
    initwindow(900, 900, "Rotation autour de l'axe L");

    int coef = 3;
    double x = 100 * coef, y = 50 * coef, z = 20 * coef;
    // Initialiser les dimensions d'origine dans les variables globales
    orig_x = x;
    orig_y = y;
    orig_z = z;

    double resultat[8][4];
    double temp[8][4];

    // Définition du parallélépipède (cube déformé) par ses 8 sommets
    double parallelepipede[8][4] = {
        {0, 0, 0, 1},     // A
        {x, 0, 0, 1},     // B
        {x, y, 0, 1},     // C
        {0, y, 0, 1},     // D
        {0, 0, z, 1},     // E
        {x, 0, z, 1},     // F
        {x, y, z, 1},     // G
        {0, y, z, 1}      // H
    };

    dessinerParallelepipede(parallelepipede);

    copierMatrice(resultat, parallelepipede);

    double angle_deg = 5; // Angle de rotation à chaque itération (en degrés)

    // Boucle infinie pour la rotation
    while (!kbhit()) {
        delay(500); // Délai de 100 ms (ajuster pour la vitesse de rotation)
        cleardevice();              // Effacer l'écran à chaque itération
        copierMatrice(temp, resultat);
        rotationAutourL(temp, angle_deg, resultat); // Appliquer la rotation
        dessinerParallelepipede(resultat);          // Dessiner le parallélépipède
    }

    getch();
    closegraph();
    return 0;
}
