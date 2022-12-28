#include <handy.h>
#include <stdio.h>

typedef struct Rabit {
    double x;
    double y;
} Rabit;

int main(void) {
    Rabit head[14];
    int i, j, dx, dy;
    double x[14] = {80,  65,  71,  82,  91,  112, 120,
                    133, 140, 123, 134, 125, 88,  71};
    double y[14] = {98,  146, 165, 152, 102, 104, 148,
                    163, 146, 98,  74,  53,  49,  72};
    int w, h;

    HgOpen(200, 600);
    dx = 1;
    w = 5;
    h = 15;
    for (;;) {
        HgClear();
        HgPolygon(14, x, y);
        HgSetFillColor(HG_DGRAY);

        if (x[2] > 78 || x[2] < 65) {
            dx *= (-1);
        }

        for (i = 1; i < 4; i++) {
            x[i] += dx;
            x[i + 5] += dx;
        }

        HgSleep(0.2);
    }

    HgGetChar();
    HgClose();

    return 0;
}
