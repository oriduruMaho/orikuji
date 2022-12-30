#include <handy.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LAST_LINE_NUM 44

typedef struct Script {
    char words[100];
} Script;

int layer1, layer2;

void omikujiDraw(Script *pS) {
    char *omikuji[7] = {"大吉", "中吉", "小吉", "末吉", "吉", "凶", "大凶"};
    int i, j, num;
    double x, y;
    const char *days[] = {
        "日", "月", "火", "水", "木", "金", "土",
    };
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    double xp[4] = {5, 5, 195, 195};
    double yp[4] = {595, 5, 5, 595};

    HgSetFillColor(HG_RED);
    HgSetColor(HG_RED);
    HgBoxFill(10, 510, 180, 80, 0);
    HgPolygon(4, xp, yp);
    HgLine(10, 505, 190, 505);

    HgSetFontByName("ヒラギノ丸ゴ ProN", 40);
    HgSetColor(HG_WHITE);
    srandom(time(NULL));
    num = random() % 7;
    HgTextSize(&x, &y, "＊%s＊", omikuji[num]);
    HgText(100 - x / 2, 530, "＊%s＊", omikuji[num]);

    HgSetColor(HG_DRED);
    HgSetFillColor(HgGrayA(1, 0.8));

    HgSetFontByName("游教科書体", 10);
    HgTextSize(&x, &y, "%04d年%02d月%02d日（%s）%02d時%02d分%02d秒\n",
               tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
               days[tm->tm_wday], tm->tm_hour, tm->tm_min, tm->tm_sec);
    HgBoxFill(100 - x / 2, y, x, 10, 0);
    HgText(100 - x / 2, 10, "%04d年%02d月%02d日（%s）%02d時%02d分%02d秒\n",
           tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, days[tm->tm_wday],
           tm->tm_hour, tm->tm_min, tm->tm_sec);

    HgSetFontByName("游教科書体", 20);
    for (i = 0; i < 3; i++) {
        num = random() % LAST_LINE_NUM;
        HgBoxFill(45 + i * 50, 450 - 20 * (strlen(pS[num].words) / 3) + 40, 20,
                  20 * (strlen(pS[num].words) / 3), 0);
        for (j = 0; j < strlen(pS[num].words) / 3; j++) {
            HgText(45 + i * 50, 450 - j * 20, "%c%c%c\n", pS[num].words[j * 3],
                   pS[num].words[j * 3 + 1], pS[num].words[j * 3 + 2]);
        }
    }
}

void rabitDraw(void) {
    hgevent *event;
    int i, dx, key;
    double x[14] = {80,  65,  71,  82,  91,  112, 120,
                    133, 140, 123, 134, 125, 88,  71};
    double y[14] = {98,  146, 165, 152, 102, 104, 148,
                    163, 146, 98,  74,  53,  49,  72};
    dx = 1;

    HgWSetFillColor(layer2, HG_BLACK);
    HgWCircle(layer2, 105, 63, 1);
    HgWOvalFill(layer2, 90, 80, 3.5, 10, 0, 0);
    HgWOvalFill(layer2, 115, 80, 3.5, 10, 0, 0);
    HgWSetFillColor(layer2, HG_WHITE);
    HgWCircleFill(layer2, 92.5, 85, 2, 0);
    HgWCircleFill(layer2, 117, 85, 2, 0);
    HgWSetFillColor(layer2, HG_PINK);
    HgWOvalFill(layer2, 75, 70, 10, 5, 0, 0);
    HgWOvalFill(layer2, 130, 70, 10, 5, 0, 0);
    HgWSetFillColor(layer1, HG_WHITE);
    for (;;) {
        event = HgEventNonBlocking();
        if (event != NULL) {
            break;
        }
        HgLClear(layer1);
        HgWPolygonFill(layer1, 14, x, y, 1);

        if (x[2] > 78 || x[2] < 65) {
            dx *= (-1);
        }

        for (i = 1; i < 4; i++) {
            x[i] += dx;
            x[i + 5] += dx;
        }

        HgSleep(0.2);
    }
}

void plumDraw(int cx, int cy) {
    int i, j;
    int x[5] = {1 + cx, 3 + cx, 6 + cx, 9 + cx, 11 + cx};
    int y[5] = {cy, -5 + cy, 5 + cy, -5 + cy, cy};
    HgSetColor(HG_WHITE);
    HgSetWidth(1.5);
    for (j = 0; j < 2; j++) {
        if ((cx + j) % 2 == 0) {
            HgSetFillColor(HG_PINK);
        } else {
            HgSetFillColor(HG_RED);
        }
        for (i = 0; i < 5; i++) {
            HgCircleFill(x[i] + 10 * j, y[i] - 10 * j, 5, 0);
            HgLine(6 + cx + 10 * j, cy - 10 * j, x[i] + 10 * j, y[i] - 10 * j);
        }
    }
}

void pineDraw(int x, int y) {
    int i, j;
    HgSetFillColor(HG_DGREEN);
    HgOvalFill(x + 10, y, 20, 8, 0, 0);
    HgCircleFill(x + 10, y + 5, 10, 0);
    for (i = 0; i < 3; i++) {
        HgLine(x + 5 + i * 5, y - 2, x + i * 10, y + 5 + i % 2 * 3);
    }
}

int main(void) {
    FILE *fp;
    Script scripts[LAST_LINE_NUM];
    int i, j;
    int x, y;

    fp = fopen("fortune.txt", "r");
    if (fp == NULL) {
        printf("file open error\n");
        return 1;
    }

    for (i = 0; i < LAST_LINE_NUM; i++) {
        fscanf(fp, "%s\n", scripts[i].words);
        // printf("%s\n", scripts[i].words);
    }
    fclose(fp);

    HgOpen(200, 600);
    layer1 = HgWAddLayer(0);
    layer2 = HgWAddLayer(0);
    HgSetTitle("おりくじ");
    HgSetEventMask(HG_KEY_DOWN);

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 3; j++) {
            if ((i + j) % 2 == 0)
                plumDraw(25 + 70 * j, 35 + 50 * i);
            else
                pineDraw(25 + 68 * j, 30 + 50 * i);
        }
    }
    omikujiDraw(scripts);
    rabitDraw();

    HgGetChar();
    HgClose();
    return 0;
}
