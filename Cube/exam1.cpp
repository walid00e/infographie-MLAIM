#include <stdio.h>
#include <graphics.h>
#include <math.h>

int centerX, centerY;

int comb(int n, int i) {
    int result = 1;
    for (int j = 1; j <= i; j++) {
        result = result * (n - j + 1) / j;
    }
    return result;
}

// Fonction pour dessiner une courbe de Bézier cubique
void bezierCubic(int points[][2], int color) {

    int n = 3; // Degré de la courbe (cubic)
    double x, y, t;
    int px, py;

    // Parcourir t de 0 à 1 par petits incréments
    for (t = 0.0; t <= 1.0; t += 0.001) {
        x = 0;
        y = 0;

        // Calcul de x et y à l'aide de la formule de Bézier cubique
        for (int i = 0; i <= n; i++) {
            double binomial = comb(n, i) * pow(1 - t, n - i) * pow(t, i);
            x += binomial * points[i][0];
            y += binomial * points[i][1];
        }

        // Dessiner le point calculé
        px = (int)(x + 0.5); // Arrondir la valeur de x
        py = (int)(y + 0.5); // Arrondir la valeur de y
        putpixel(px, py, color);
    }
}

void repere3d(int length) {
    centerX = getmaxx()/2;
    centerY = getmaxy()/2;
    line(centerX, centerY, centerX + length, centerY);
    outtextxy(centerX + length, centerY, (char *)"X");

    line(centerX, centerY, centerX, centerY - length);
    outtextxy(centerX, centerY - length, (char *)"Y");

    line(centerX, centerY, centerX - length * cos(35 * M_PI / 180), centerY + length* sin(35 * M_PI / 180));
    outtextxy(centerX - length * cos(35 * M_PI / 180), centerY + length* sin(35 * M_PI / 180), (char *)"Z");
}

void multiplication(double M1[8][4],double M2[4][4],double P[8][4]){
	for(int i = 0;i<8;i++){
		for(int j=0;j<4;j++){
			P[i][j] = 0;
			for(int k=0;k<4;k++){
				P[i][j] += M1[i][k] * M2[k][j]; 
			}
		}
	}
}

void projectionCavalier(double cube[8][4], double A[8][4], int h, int k, int teta = 45){
    int i,j;
    double projectionMatrix[4][4] = {{1,0,0,0},{0,1,0,0},{cos(teta* M_PI / 180),sin(teta* M_PI / 180),0,0},{0,0,0,1}};
    multiplication(cube,projectionMatrix,A);
    //LES SOMMETS
	outtextxy(h+A[0][0],k-A[0][1],(char*)"A");
	outtextxy(h+A[1][0],k-A[1][1],(char*)"B");
	outtextxy(h+A[2][0],k-A[2][1],(char*)"C");
	outtextxy(h+A[3][0],k-A[3][1],(char*)"D");
	outtextxy(h+A[4][0],k-A[4][1],(char*)"E");
	outtextxy(h+A[5][0],k-A[5][1],(char*)"F");
	outtextxy(h+A[6][0],k-A[6][1],(char*)"G");
	outtextxy(h+A[7][0],k-A[7][1],(char*)"H");
	//A-->B
	line(A[0][0]+h,k-A[0][1],h+A[1][0],k-A[1][1]);
	//B-->C
	line(A[1][0]+h,k-A[1][1],h+A[2][0],k-A[2][1]);
	//C-->D
	line(A[2][0]+h,k-A[2][1],h+A[3][0],k-A[3][1]);
	//D-->A
	line(A[3][0]+h,k-A[3][1],h+A[0][0],k-A[0][1]);
	//E-->F
	line(A[4][0]+h,k-A[4][1],h+A[5][0],k-A[5][1]);
	//F-->G
	line(A[5][0]+h,k-A[5][1],h+A[6][0],k-A[6][1]);
	//G-->H
	line(A[6][0]+h,k-A[6][1],h+A[7][0],k-A[7][1]);
	//H-->E
	line(A[7][0]+h,k-A[7][1],h+A[4][0],k-A[4][1]);
	//A-->E
	line(A[0][0]+h,k-A[0][1],h+A[4][0],k-A[4][1]);
	//D-->H
	line(A[3][0]+h,k-A[3][1],h+A[7][0],k-A[7][1]);
	//C-->G
	line(A[2][0]+h,k-A[2][1],h+A[6][0],k-A[6][1]);
	//B-->F
	line(A[1][0]+h,k-A[1][1],h+A[5][0],k-A[5][1]);

	int points[4][2] = {{(int)(A[1][0]+h),(int)(k-A[1][1])},{(int)(h+A[5][0]),(int)(k-A[5][1])},{(int)(h+A[7][0]),(int)(k-A[7][1])},{(int)(h+A[3][0]),(int)(k-A[3][1])}};
	
	bezierCubic(points, YELLOW);

    
}

// Fonction pour calculer le coefficient binomial "n choose i"

int main(){
    double cube[8][4] = {
        {0,0,0,1},
        {200,0,0,1},
        {200,100,0,1},
        {0,100,0,1},
        {0,0,100,1},
        {200,0,100,1},
        {200,100,100,1},
        {0,100,100,1}
    };
    double res[8][4];

    int gd = DETECT, gm;
    initwindow(1300, 700, "Cube");

    repere3d(300);

    projectionCavalier(cube,res, centerX, centerY, 35);

    getch();
}

