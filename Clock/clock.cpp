#include <graphics.h>
#include <math.h>
#include <time.h>

void dessinerCadran(int centreX, int centreY, int rayon) {
    circle(centreX, centreY, rayon);
    for (int i = 0; i < 60; i++) {
        int h = (i % 5) ? 10 : 20;
        int x = centreX + (rayon - 5) * sin(i * M_PI / 30);
        int y = centreY - (rayon - 5) * cos(i * M_PI / 30);
        line(centreX + (rayon - h) * sin(i * M_PI / 30),
            centreY - (rayon - h) * cos(i * M_PI / 30),
            x, y);
        if (i % 5 == 0){
            int x = centreX + (rayon + 25) * sin(i * M_PI / 30);
            int y = centreY - (rayon + 25) * cos(i * M_PI / 30) - 5;
            char txt[3];
            x -= (i / 5 >= 10) ? 8 : 4;
            itoa(i/5 ,txt, 10);
            outtextxy(x, y, txt);
        }
    }
}

void dessinerAiguille(int centreX, int centreY, int longueur, float angle) {
    int x = centreX + longueur * sin(angle);
    int y = centreY - longueur * cos(angle);
    line(centreX, centreY, x, y);
}

void dessinerHorloge(int centreX, int centreY, int rayon) {
    time_t maintenant = time(NULL);
    struct tm *local = localtime(&maintenant);

    int heure = local->tm_hour % 12;
    int minute = local->tm_min;
    int seconde = local->tm_sec;

    cleardevice();
    dessinerCadran(centreX, centreY, rayon);

    float angleHeure = (M_PI / 6) * (heure + minute / 60.0);
    dessinerAiguille(centreX, centreY, rayon * 0.5, angleHeure);

    float angleMinute = (M_PI / 30) * (minute + seconde / 60.0);
    dessinerAiguille(centreX, centreY, rayon * 0.75, angleMinute);

    float angleSeconde = (M_PI / 30) * seconde;
    dessinerAiguille(centreX, centreY, rayon * 0.9, angleSeconde);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int centreX = getmaxx() / 2;
    int centreY = getmaxy() / 2;
    int rayon = 180;

    while (1) {
        dessinerHorloge(centreX, centreY, rayon);
        delay(1000);
    }

    closegraph();
    return 0;
}