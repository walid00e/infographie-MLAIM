#include <graphics.h>
#include <math.h>

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
        {0,0,0,d},
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
    initwindow(1300, 700, "Cube");

    double resulta[8][4];
    double temp[8][4];

    cleardevice();

    double Cube[8][4] = {
        {0,0,0,1},
        {200,0,0,1},
        {200,200,0,1},
        {0,200,0,1},
        {0,0,200,1},
        {200,0,200,1},
        {200,200,200,1},
        {0,200,200,1}
    };

    projection_perspective(Cube, 0.0005,resulta);
    drawCube(resulta);

    int x;
    scanf("%d",&x);

    temporaire(resulta,Cube);
    translation(Cube,0,0,-200,resulta);
    temporaire(temp,resulta);
    rotation_x(temp, M_PI/4,resulta);
    temporaire(temp,resulta);
    projection_perspective(temp, 0.00005,resulta);
    temporaire(temp,resulta);
    rotation_x(temp, -M_PI/4,resulta);
    temporaire(temp,resulta);
    translation(temp,0,0,200,resulta);
    
    drawCube(resulta);

    getch();
    closegraph();

    return 0;
}