#include<stdio.h>
#include<math.h>
#include<graphics.h>
#include<unistd.h>
#include<windows.h>

void init_graph(){
	initwindow(1360,700);
	setcolor(12);
	for(int i = 0;i<10;i++){
		line(0,400+i,1360,400+i);
	}
	for(int j = 0;j<10;j++){
		line(1000+j,400,1000+j,100);
	}
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

void lecube(double M[8][4],int h,int k,double f,double teta){
	double projectionMatrix[4][4] = {{1,0,0,0},{0,1,0,0},{f*cos(teta),f*sin(teta),0,0},{0,0,0,1}};
	double A[8][4];
	multiplication(M,projectionMatrix,A);
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
	//A-->F
	line(A[0][0]+h,k-A[0][1],h+A[5][0],k-A[5][1]);
	//D-->E
	line(A[3][0]+h,k-A[3][1],h+A[4][0],k-A[4][1]);
	//C-->H
	line(A[2][0]+h,k-A[2][1],h+A[7][0],k-A[7][1]);
	//B-->G
	line(A[1][0]+h,k-A[1][1],h+A[6][0],k-A[6][1]);
}


void cube(double A[8][4],int h,int k,double f,double teta){
	//double projectionMatrix[4][4] = {{1,0,0,0},{0,1,0,0},{f*cos(teta),f*sin(teta),0,0},{0,0,0,1}};
	double M[8][4];
	//multiplication(A,projectionMatrix,A);
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
	//A-->F
	line(A[0][0]+h,k-A[0][1],h+A[5][0],k-A[5][1]);
	//D-->E
	line(A[3][0]+h,k-A[3][1],h+A[4][0],k-A[4][1]);
	//C-->H
	line(A[2][0]+h,k-A[2][1],h+A[7][0],k-A[7][1]);
	//B-->G
	line(A[1][0]+h,k-A[1][1],h+A[6][0],k-A[6][1]);
}

void rotationX(double M[8][4],int h,int k,double f,double teta,double alpha){
	double projectionMatrix[4][4] = {{1,0,0,0},{0,1,0,0},{f*cos(teta),f*sin(teta),0,0},{0,0,0,1}};
	double A[8][4],B[8][4],C[8][4];
	multiplication(M,projectionMatrix,B);
	cube(B,h,k,1,0);
	Sleep(100);
	while(alpha<360){
		double TR[4][4] = {{1,0,0,0},{0,cos(alpha),sin(alpha),0},{0,-sin(alpha),cos(alpha),0},{0,0,0,1}};
		multiplication(M,TR,A);
		multiplication(A,projectionMatrix,C);
		cleardevice();
		line(700,400,1400,400);
		line(700,0,700,400);
		line(700,400,0,700);
		cube(C,h,k,1,0);
		Sleep(100);
		alpha++;
	}

}

void rotationY(double M[8][4],int h,int k,double f,double teta,double alpha){
	double projectionMatrix[4][4] = {{1,0,0,0},{0,1,0,0},{f*cos(teta),f*sin(teta),0,0},{0,0,0,1}};
	double A[8][4],B[8][4],C[8][4];
	multiplication(M,projectionMatrix,B);
	cube(B,h,k,1,0);
	Sleep(100);
	while(alpha<360){
		double TR[4][4] = {{cos(alpha),0,-sin(alpha),0},{0,1,0,0},{sin(alpha),0,cos(alpha),0},{0,0,0,1}};
		multiplication(M,TR,A);
		multiplication(A,projectionMatrix,C);
		cleardevice();
		line(700,400,1400,400);
		line(700,0,700,400);
		line(700,400,0,700);
		cube(C,h,k,1,0);
		Sleep(100);
		alpha++;
	}

}

void rotationZ(double M[8][4],int h,int k,double f,double teta,double alpha){
	double projectionMatrix[4][4] = {{1,0,0,0},{0,1,0,0},{f*cos(teta),f*sin(teta),0,0},{0,0,0,1}};
	double A[8][4],B[8][4],C[8][4];
	multiplication(M,projectionMatrix,B);
	cube(B,h,k,1,0);
	Sleep(100);
	while(alpha<360){
		double TR[4][4] = {{cos(alpha),sin(alpha),0,0},{-sin(alpha),cos(alpha),0,0},{0,0,1,0},{0,0,0,1}};
		multiplication(M,TR,A);
		multiplication(A,projectionMatrix,C);
		cleardevice();
		line(700,400,1400,400);
		line(700,0,700,400);
		line(700,400,0,700);
		cube(C,h,k,1,0);
		Sleep(100);
		alpha++;
	}
}

void translationX(double M[8][4],int h,int k,double f,double teta,int x){
	double projectionMatrix[4][4] = {{1,0,0,0},{0,1,0,0},{f*cos(teta),f*sin(teta),0,0},{0,0,0,1}};
	double TR[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{x,0,0,1}};
	double A[8][4],B[8][4];
	multiplication(M,projectionMatrix,B);
	multiplication(B,TR,A);
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
	//A-->F
	line(A[0][0]+h,k-A[0][1],h+A[5][0],k-A[5][1]);
	//D-->E
	line(A[3][0]+h,k-A[3][1],h+A[4][0],k-A[4][1]);
	//C-->H
	line(A[2][0]+h,k-A[2][1],h+A[7][0],k-A[7][1]);
	//B-->G
	line(A[1][0]+h,k-A[1][1],h+A[6][0],k-A[6][1]);
}

void translationY(double M[8][4],int h,int k,double f,double teta ,int y){
	double projectionMatrix[4][4] = {{1,0,0,0},{0,1,0,0},{f*cos(teta),f*sin(teta),0,0},{0,0,0,1}};
	double TR[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,y,0,1}};
	double A[8][4],B[8][4];
	multiplication(M,projectionMatrix,B);
	multiplication(B,TR,A);
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
	//A-->F
	line(A[0][0]+h,k-A[0][1],h+A[5][0],k-A[5][1]);
	//D-->E
	line(A[3][0]+h,k-A[3][1],h+A[4][0],k-A[4][1]);
	//C-->H
	line(A[2][0]+h,k-A[2][1],h+A[7][0],k-A[7][1]);
	//B-->G
	line(A[1][0]+h,k-A[1][1],h+A[6][0],k-A[6][1]);
}

void translationZ(double M[8][4],int h,int k,double f,double teta,int z){
	double projectionMatrix[4][4] = {{1,0,0,0},{0,1,0,0},{f*cos(teta),f*sin(teta),0,0},{0,0,0,1}};
	double TR[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,z,1}};
	double A[8][4],B[8][4];
	multiplication(M,projectionMatrix,B);
	multiplication(B,TR,A);
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
	//A-->F
	line(A[0][0]+h,k-A[0][1],h+A[5][0],k-A[5][1]);
	//D-->E
	line(A[3][0]+h,k-A[3][1],h+A[4][0],k-A[4][1]);
	//C-->H
	line(A[2][0]+h,k-A[2][1],h+A[7][0],k-A[7][1]);
	//B-->G
	line(A[1][0]+h,k-A[1][1],h+A[6][0],k-A[6][1]);
}



void menuCube(double M[8][4],int h,int k,double f,double teta){
	char c = 'V';
	do{
		printf("\nEntrez A pour Afficher le CUBE \n");
		printf("Entrez X pour translation sur AXE X \n");
		printf("Entrez Y pour translation sur AXE Y \n");
		printf("Entrez Z pour translation sur AXE Z \n");
		printf("Entrez M pour rotation    sur AXE X \n");
		printf("Entrez N pour rotation    sur AXE Y \n");
		printf("Entrez O pour rotation    sur AXE Z \n");
		printf("Entrez Q pour QUITTER \n");
		printf("Entrez votre choix : ");
		scanf("%c",&c);
		
		switch(c){
			case 'A':
				initwindow(1400,700);
				setcolor(12);
				line(700,400,1400,400);
				line(700,0,700,400);
				line(700,400,0,700);
				lecube(M,700,400,f,teta);
				break;
			case 'X':
				int x;
				printf("Entrez la valeur de translation autour de l axe X : ");
				scanf("%d",&x);
				initwindow(1400,700);
				setcolor(12);
				for(int i = 0;i<=x;i+=60){
					cleardevice();
					line(0,390,1400,390);
					translationX(M,h,k,f,teta,i);
					Sleep(100);
				}
				break;
			case 'Y':
				int y;
				printf("Entrez la valeur de translation autour de l axe Y : ");
				scanf("%d",&y);
				initwindow(1400,700);
				setcolor(12);
				for(int i = 0;i<=y;i+=20){
					cleardevice();
					line(700,0,700,800);
					translationY(M,700,700,f,teta,i);
					Sleep(100);
				}
				break;
			case 'Z':
				int z;
				printf("Entrez la valeur de translation autour de l axe Z : ");
				scanf("%d",&z);
				initwindow(1400,700);
				setcolor(12);
				for(int i = 0;i<=z;i+=20){
					cleardevice();
					translationZ(M,h,k,f,teta,i);
					Sleep(100);
				}
				break;
			case 'M':
				initwindow(1400,700);
				setcolor(12);
				rotationX(M,700,400,f,teta,0);
				break;
			case 'N':
				initwindow(1400,700);
				setcolor(12);
				rotationY(M,700,400,f,teta,0);
				break;
			case 'O':
				initwindow(1400,700);
				setcolor(12);
				rotationZ(M,700,400,f,teta,0);
				break;
			case 'Q' :
				break;
		}
	}while(c!='Q');
}


int main(){
	//h= 0,k=400
	//double M[8][4] = {{0,0,0,1},{1,0,0,1},{1,1,0,1},{0,1,0,1},{0,1,1,1},{0,0,1,1},{1,0,1,1},{1,1,1,1}};
	double teta = 45;
	double M[8][4] = {{0,0,0,1},{100,0,0,1},{100,100,0,1},{0,100,0,1},{0,100,100,1},{0,0,100,1},{100,0,100,1},{100,100,100,1}};
	menuCube(M,0,390,1,teta);
	getch();
	return 0;
}
