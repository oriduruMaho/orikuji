/*
    orikuji.c
    おみくじをHandyGraphicで表示させるプログラム
*/

#include <handy.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LAST_LINE_NUM 44  // fortune.txtの最後-1行目の数字

// 文字入れとくための構造体
typedef struct Script {
    char words[100];
} Script;

// レイヤ分けの変数
int layer1, layer2;
doubleLayer layers;

// おみくじの内容を描く関数
void omikujiDraw(Script *pS) {
    char *omikuji[7] = {"大吉", "中吉", "小吉", "末吉",
                        "吉",   "凶",   "大凶"};  // 運勢
    int i, j, num;  // カウンタ変数と乱数のための変数
    double x, y;    // x,y座標
    const char *days[] = {
        "日", "月", "火", "水", "木", "金", "土",
    };  // 曜日
    // 以下時刻を得るためのなんやかや
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    // 四角く線を描くための座標入り配列
    double xp[4] = {5, 5, 195, 195};
    double yp[4] = {595, 5, 5, 595};

    // 赤い箱と線を描く
    HgSetFillColor(HG_RED);
    HgSetColor(HG_RED);
    HgBoxFill(10, 510, 180, 80, 0);
    HgPolygon(4, xp, yp);
    HgLine(10, 505, 190, 505);

    // おみくじの運勢描く
    HgSetFontByName("ヒラギノ丸ゴ ProN", 40);
    HgSetColor(HG_WHITE);
    srandom(time(NULL));
    num = random() % 7;
    HgTextSize(&x, &y, "＊%s＊", omikuji[num]);
    HgText(100 - x / 2, 530, "＊%s＊", omikuji[num]);

    HgSetColor(HG_DRED);
    HgSetFillColor(HgGrayA(1, 0.8));

    //  時刻を書く
    HgSetFontByName("游教科書体", 10);
    HgTextSize(&x, &y, "%04d年%02d月%02d日（%s）%02d時%02d分%02d秒\n",
               tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
               days[tm->tm_wday], tm->tm_hour, tm->tm_min, tm->tm_sec);
    HgBoxFill(100 - x / 2, y, x, 10, 0);
    HgText(100 - x / 2, 10, "%04d年%02d月%02d日（%s）%02d時%02d分%02d秒\n",
           tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, days[tm->tm_wday],
           tm->tm_hour, tm->tm_min, tm->tm_sec);

    // おみくじの内容描く
    HgSetFontByName("游教科書体", 20);
    for (i = 0; i < 3; i++) {
        num = random() % LAST_LINE_NUM;
        HgBoxFill(45 + i * 50, 450 - 20 * ((strlen(pS[num].words) / 3) - 2), 20,
                  20 * (strlen(pS[num].words) / 3), 0);
        for (j = 0; j < strlen(pS[num].words) / 3; j++) {
            HgText(45 + i * 50, 450 - j * 20, "%c%c%c\n", pS[num].words[j * 3],
                   pS[num].words[j * 3 + 1], pS[num].words[j * 3 + 2]);
        }
    }
}

// 耳が動くうさぎさん描く関数
void rabitDraw(void) {
    hgevent *event;
    int i, j, dx, key;
    // うさぎさん描くための座標入り配列
    double x[14] = {80,  65,  71,  82,  91,  112, 120,
                    133, 140, 123, 134, 125, 88,  71};
    double y[14] = {98,  146, 165, 152, 102, 104, 148,
                    163, 146, 98,  74,  53,  49,  72};
    int face_x[4] = {90, 115, 75, 130};
    dx = 1;

    // お目々とかほっぺとか
    HgWSetFillColor(layer2, HG_BLACK);
    HgWCircle(layer2, 105, 63, 1);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            HgWOvalFill(layer2, face_x[i * 2 + j], 80 - 10 * i, 3.5 + 6.5 * i,
                        10 - 5 * i, 0, 0);
        }
        HgWSetFillColor(layer2, HG_WHITE);
        HgWCircleFill(layer2, 92 + 25 * i, 85, 2, 0);
        HgWSetFillColor(layer2, HG_PINK);
    }

    HgWSetFillColor(layer1, HG_WHITE);
    for (;;) {
        // キー入力で止まる
        event = HgEventNonBlocking();
        if (event != NULL) {
            break;
        }
        layer1 = HgLSwitch(&layers);
        HgLClear(layer1);
        HgWPolygonFill(layer1, 14, x, y, 1);  // ウサギさんの輪郭

        // 耳を動かしてる
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

// 梅の花を描く関数
void plumDraw(int cx, int cy) {
    int i, j;
    int x[5] = {1 + cx, 3 + cx, 6 + cx, 9 + cx, 11 + cx};
    int y[5] = {cy, -5 + cy, 5 + cy, -5 + cy, cy};
    HgSetColor(HG_WHITE);
    HgSetFillColor(HG_RED);
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 5; i++) {
            HgCircleFill(x[i] + 10 * j, y[i] - 10 * j, 5, 0);
            HgLine(6 + cx + 10 * j, cy - 10 * j, x[i] + 10 * j, y[i] - 10 * j);
        }
        HgSetFillColor(HG_PINK);
    }
}

// 松を描く関数
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

    // ファイル開いてデータ読み込む
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
    layers = HgWAddDoubleLayer(0);
    layer1 = HgWAddLayer(0);
    layer2 = HgWAddLayer(0);
    HgSetTitle("おりくじ");
    HgSetEventMask(HG_KEY_DOWN);

    HgSetWidth(1.5);

    // 松と梅を描く
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 3; j++) {
            if ((i + j) % 2 == 0)
                plumDraw(25 + 70 * j, 35 + 50 * i);
            else
                pineDraw(25 + 68 * j, 30 + 50 * i);
        }
    }
    omikujiDraw(scripts);  // おみくじ描く
    rabitDraw();           // うさぎさん描く

    HgGetChar();
    HgClose();
    return 0;
}
