#include <graphics.h>
#include <math.h>
#include <stdio.h>

// Fonction pour calculer le coefficient binomial "n choose i"
int comb(int n, int i) {
    int result = 1;
    for (int j = 1; j <= i; j++) {
        result = result * (n - j + 1) / j;
    }
    return result;
}

// Fonction pour dessiner une courbe de Bézier quadratique (degré 2)
void bezierQuadratique(int points[][2], int color) {
    double x, y, t;
    int px, py;
    
    // Parcourir t de 0 à 1 par petits incréments
    for (t = 0.0; t <= 1.0; t += 0.001) {
        x = (1 - t) * (1 - t) * points[0][0] + 2 * (1 - t) * t * points[1][0] + t * t * points[2][0];
        y = (1 - t) * (1 - t) * points[0][1] + 2 * (1 - t) * t * points[1][1] + t * t * points[2][1];

        // Arrondir les valeurs de x et y pour placer le pixel
        px = (int)(x + 0.5);
        py = (int)(y + 0.5);
        
        // Dessiner le pixel à la position (px, py)
        putpixel(px, py, color);
    }
}

void captureClick(int* res) {
    int x ,y;
    // getting click coords
    boolean init = false;
    while (!kbhit()) {  // Loop until a key is pressed
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            printf("Clicked at: (%d, %d)\n", x, y);
            putpixel(x, y, WHITE);  // Visual feedback for the click
            res[0] = x;
            res[1] = y;
            return;
        }
    }
    closegraph();
}

// Fonction principale
int main() {
    int gd = DETECT, gm; // Détection automatique du mode graphique
    initgraph(&gd, &gm, NULL);

    // allocation de memoir de table
    int* res = (int*) malloc(2 * sizeof(int));  
    if (res == NULL) {                   
        printf("Memory allocation failed\n");
        return 0;
    }

    // Points de contrôle (4 points pour une courbe cubique)
    int points[3][2];

    for (int i=0; i<3; i++){
        captureClick(res);
        points[i][0] = res[0];
        points[i][1] = res[1];
    }

    // Couleur de la courbe
    int color = WHITE;

    // Dessiner la courbe de Bézier quadratique
    bezierQuadratique(points, color);

    // dessiner la line
    setcolor(YELLOW);
    for (int i=0; i<2; i++){
        
        line(points[i][0],points[i][1],points[i+1][0],points[i+1][1]);
        
    }

    // Attendre que l'utilisateur appuie sur une touche
    getch();

    // Fermer le mode graphique
    closegraph();

    return 0;
}