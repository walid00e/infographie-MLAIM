#include <stdio.h>
#include <graphics.h>
#include <math.h>

int centerX, centerY;

void repere3d(int length) {
    centerX = getmaxx()/2;
    centerY = getmaxy()/2;
    line(centerX, centerY, centerX + length, centerY);
    outtextxy(centerX + length, centerY, (char *)"X");

    line(centerX, centerY, centerX, centerY - length);
    outtextxy(centerX, centerY - length, (char *)"Y");

    line(centerX, centerY, centerX - length, centerY + length);
    outtextxy(centerX - length, centerY + length, (char *)"Z");
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
    cleardevice();
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
    

    // line de rotation B-->H
    setcolor(YELLOW);
    line(A[1][0]+h,k-A[1][1],h+A[7][0],k-A[7][1]);
    setcolor(WHITE);
}


void rotationX(double M[8][4],double teta){
	double rotationMatrix[4][4] = {{1,0,0,0},{0,cos(teta),sin(teta),0},{0,-sin(teta),cos(teta),0},{0,0,0,1}};
	double A[8][4],B[8][4],C[8][4];
	multiplication(M,rotationMatrix,B);
	projectionCavalier(B,C,centerX,centerY);
}

void rotationY(double M[8][4],double teta){
	double rotationMatrix[4][4] = {{cos(teta),0,-sin(teta),0},{0,1,0,0},{sin(teta),0,cos(teta),0},{0,0,0,1}};
	double A[8][4],B[8][4],C[8][4];
	multiplication(M,rotationMatrix,B);
	projectionCavalier(B,C,centerX,centerY);
}

void rotationZ(double M[8][4],double teta){
	double rotationMatrix[4][4] = {{cos(teta),sin(teta),0,0},{-sin(teta),cos(teta),0,0},{0,0,1,0},{0,0,0,1}};
	double A[8][4],B[8][4],C[8][4];
	multiplication(M,rotationMatrix,B);
	projectionCavalier(B,C,centerX,centerY);
}

void rotationAxe(double M[8][4],double ax, double ay, double az){
    double rotationMatrixX[4][4] = {{1,0,0,0},{0,cos(ax),sin(ax),0},{0,-sin(ax),cos(ax),0},{0,0,0,1}};
    double rotationMatrixY[4][4] = {{cos(ay),0,-sin(ay),0},{0,1,0,0},{sin(ay),0,cos(ay),0},{0,0,0,1}};
    double rotationMatrixZ[4][4] = {{cos(az),sin(az),0,0},{-sin(az),cos(az),0,0},{0,0,1,0},{0,0,0,1}};
    double A1[8][4],rotationAxe[8][4],A3[8][4],B[8][4],C[8][4];
    multiplication(rotationMatrixX,rotationMatrixY,A1);
    multiplication(A1,rotationMatrixZ,rotationAxe);
    multiplication(M,rotationAxe,B);
    projectionCavalier(B,C,centerX,centerY);
}

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

    //projectionCavalier(cube,res, centerX, centerY);
    //rotationX(cube, 45 * M_PI / 180);
    
    double i = 0;
    while(true){
        repere3d(300);
        rotationX(cube, i * M_PI / 180);
        i += 0.1;
    }

    getch();
}

