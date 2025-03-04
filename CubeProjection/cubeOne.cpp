#include <graphics.h>
#include <math.h>
#include <stdio.h>

// Fonction pour dessiner le repère 3D
void repere3d(int length) {
    int centerX = getmaxx()/2;
    int centerY = getmaxy()/2;

    line(centerX, centerY, centerX + length, centerY);
    outtextxy(centerX + length, centerY, (char *)"X");

    line(centerX, centerY, centerX, centerY - length);
    outtextxy(centerX, centerY - length, (char *)"Y");

    line(centerX, centerY, centerX - length, centerY + length);
    outtextxy(centerX - length, centerY + length, (char *)"Z");
}

void methodeEquations(int xa, int ya, int xb, int yb, int xc, int yc, int xd, int yd){
    float x, y;
    float det = (xb - xa) * (yc - yd) - (yb - ya) * (xc - xd);
    if (det == 0) {
        printf("droites paralleles\n");
        return;
    }
    float t1 = ((xc - xa) * (yc - yd) - (yc - ya) * (xc - xd)) / det;
    float t2 = ((xb - xa) * (yc - ya) - (yb - ya) * (xc - xa)) / det;
    if(t1 <= 1 && t1 >= 0 && t2 <= 1 && t2 >= 0 || true){
        printf("intersection\n");
        x = xa + (xb - xa) * t1;
        y = ya + (yb - ya) * t1;
        printf("(xa, ya) : (%d, %d)\n", xa, ya);
        printf("(xb, yb) : (%d, %d)\n", xb, yb);
        //printf("(xc, yc) : (%d, %d)\n", xc, yc);
        printf("(xd, yd) : (%d, %d)\n", xd, yd);
        printf("(x, y) : (%f, %f)\n", x, y);
        line(xa,ya,x,y);
    } else {
        printf("pas d'intersection\n");
    }
}

// Function to draw axes and plot points from a 3D cube (ignoring z and w for 2D projection)
void drawAxesAndPointsFromCube(double cube[8][4]) {
    cleardevice(); // Clear the screen

    int screenWidth = getmaxx();
    int screenHeight = getmaxy();

    // Draw X-axis
    line(0, screenHeight / 2, screenWidth, screenHeight / 2);
    outtextxy(screenWidth - 20, screenHeight / 2 + 5, "X");

    // Draw Y-axis
    line(screenWidth / 2, 0, screenWidth / 2, screenHeight);
    outtextxy(screenWidth / 2 + 5, 5, "Y");

    // Project the cube points to 2D space
    int projected[8][2];
    for (int i = 0; i < 8; i++) {
        projected[i][0] = screenWidth / 2 + (int)cube[i][0]; // X-coordinate
        projected[i][1] = screenHeight / 2 - (int)cube[i][1]; // Y-coordinate
    }

    // Define the edges of the cube (pairs of points to connect)
    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Bottom face
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Top face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Vertical edges
    };

    
    // Draw the cube edges
    for (int i = 0; i < 12; i++) {
        int start = edges[i][0];
        int end = edges[i][1];
        line(projected[start][0], projected[start][1], projected[end][0], projected[end][1]);
    }


    // this is kinda working
    for(int i=8; i<12; i++){
        int start = edges[i][0];
        int end = edges[i][1];
        int start2 = edges[i+1][0];
        int end2 = edges[i+1][1];

        printf("%d\n",i);

        if(i==11){
            int start2 = edges[8][0];
            int end2 = edges[8][1];
            methodeEquations(projected[start][0], projected[start][1], projected[end][0], projected[end][1],
            projected[start2][0], projected[start2][1], projected[end2][0], projected[end2][1]);
            continue;
        }
         
        
        methodeEquations(projected[start][0], projected[start][1], projected[end][0], projected[end][1],
        projected[start2][0], projected[start2][1], projected[end2][0], projected[end2][1]);
    }

    // Label the points
    for (int i = 0; i < 8; i++) {
        char label[5];
        sprintf(label, "%d", i + 1); // Label the points as 1, 2, ..., 8
        outtextxy(projected[i][0] + 5, projected[i][1] - 5, label);
    }
    
}

void drawCube(double Cube[8][4]) {
    cleardevice();
    repere3d(300);
    int i, j;
    int projected[8][2];

    // Projection 2D des points 3D
    for (i = 0; i < 8; i++) {
        projected[i][0] = getmaxx()/2 + (int)(Cube[i][0] - Cube[i][2] * 0.5); // X projection
        projected[i][1] = getmaxy()/2 - (int)(Cube[i][1] - Cube[i][2] * 0.5); // Y projection
    }

    // Relier les sommets pour dessiner les arêtes
    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Base
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Top
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Colonnes
    };
    char* c = "A";
    for (i = 0; i < 12; i++) {
        line(projected[edges[i][0]][0], projected[edges[i][0]][1],
             projected[edges[i][1]][0], projected[edges[i][1]][1]);
        switch (i) {
            case 0:
                c = "E";
            break;
            case 1:
                c = "G";
            break;
            case 2:
                c = "F";
            break;
            case 3:
                c = "H";
            break;
            case 8:
                c = "A";
            break;
            case 9:
                c = "D";
            break;
            case 10:
                c = "C";
            break;
            case 11:
                c = "B";
            break;

        }
        outtextxy(projected[edges[i][1]][0], projected[edges[i][1]][1],c);
    }
}

void Produit_Matricielle_8x4(double matrice[8][4], double transformation[4][4], double resulta[8][4]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            resulta[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                resulta[i][j] += matrice[i][k] * transformation[k][j];
            }
        }
    }
}

void translation(double cube[8][4],double tx,double ty, double tz,double resulta[8][4]) {
    double T[4][4] = {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {tx,ty,tz,1}
    };

    Produit_Matricielle_8x4(cube,T,resulta);

}

void rotation_x(double cube[8][4], double angle,double resulta[8][4]) {
    double Rx[4][4] = {
        {1,0,0,0},
        {0,cos(angle),sin(angle),0},
        {0,-sin(angle),cos(angle),0},
        {0,0,0,1}
    };

    Produit_Matricielle_8x4(cube,Rx,resulta);

}

void rotation_y(double cube[8][4], double angle,double resulta[8][4]) {
    double Ry[4][4] = {
        {cos(angle),0,-sin(angle),0},
        {0,1,0,0},
        {sin(angle),0,cos(angle),0},
        {0,0,0,1}
    };


    Produit_Matricielle_8x4(cube,Ry,resulta);

}

void rotation_z(double cube[8][4], double angle,double resulta[8][4]) {
    double Rz[4][4] = {
        {cos(angle),sin(angle),0,0},
        {-sin(angle),cos(angle),0,0},
        {0,0,1,0},
        {0,0,0,1}
    };


    Produit_Matricielle_8x4(cube,Rz,resulta);

}

void projection_perspective(double cube[8][4], double d,double resulta[8][4]) {
    double P[4][4] = {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,0,1/d},
        {0,0,0,1}
    };

    Produit_Matricielle_8x4(cube,P,resulta);

    for(int i = 0; i < 8; i++) {
        if(resulta[i][3] != 0) {
            resulta[i][0] = resulta[i][0] / resulta[i][3];
            resulta[i][1] = resulta[i][1] / resulta[i][3];
            resulta[i][2] = resulta[i][2] / resulta[i][3];
            resulta[i][3] = 1;
        }
    }

}

void drawLinesToFuitePoint(double cube[8][4], double vpX, double vpY) {
    for (int i = 0; i < 8; i++) {
        line(vpX, vpY, cube[i][0], cube[i][1]);
    }
}

void temporaire(double temp[8][4],double resulta[8][4]) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 4; j++) {
            temp[i][j] = resulta[i][j];
        }
    }
}

int main() {
    int gd = DETECT, gm;
    // initgraph(&gd, &gm, (char *)"");
    initwindow(1300, 900, "Cube");

    double resulta[8][4];
    double temp[8][4];

    cleardevice();

    double Cube[8][4] = {
        {0,0,0,1},
        {100,0,0,1},
        {100,100,0,1},
        {0,100,0,1},
        {0,0,100,1},
        {100,0,100,1},
        {100,100,100,1},
        {0,100,100,1}
    };

    temporaire(temp,Cube);
    translation(temp,0,0,-200,resulta);
    projection_perspective(resulta, 1000,temp);
    drawAxesAndPointsFromCube(temp);

    int x;
    scanf("%d",&x);

    temporaire(temp,Cube);
    translation(temp,0,0,-200,resulta);
    temporaire(temp,resulta);
    rotation_x(temp, M_PI/4,resulta);
    temporaire(temp,resulta);
    projection_perspective(temp, 1000,resulta);
    temporaire(temp,resulta);
    rotation_x(temp, -M_PI/4,resulta);
    temporaire(temp,resulta);
    translation(temp,0,0,200,resulta);
    drawAxesAndPointsFromCube(resulta);

    // extra 
    //translation(Cube,80,80,80,resulta);
    //projection_perspective(resulta, 0.0005,temp);
    //drawAxesAndPointsFromCube(resulta);

    //double temp2[8][4];
    //translation(resulta,80,80,80,temp2);
    //projection_perspective(temp2, 0.005,temp);
    //drawAxesAndPointsFromCube(temp2);

    getch();
    closegraph();


    return 0;
}