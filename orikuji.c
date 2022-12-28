#include <handy.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LAST_LINE_NUM 44

typedef struct Script {
    char words[100];
} Script;

typedef struct Rabit {
    double x;
    double y;
} Rabit;

int main(void) {
    FILE *fp;
    Script scripts[LAST_LINE_NUM];
    char *omikuji[7] = {"大吉", "中吉", "小吉", "末吉", "吉", "凶", "大凶"};
    int i, j, num;
    double x, y;

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
    HgSetTitle("おりくじ");
    HgSetFillColor(HG_RED);
    HgSetColor(HG_RED);
    HgBoxFill(5, 510, 190, 85, 0);
    HgMoveTo(5, 595);
    HgLineTo(5, 5);
    HgLineTo(195, 5);
    HgLineTo(195, 595);

    HgSetFont(HG_MB, 40);
    HgSetColor(HG_WHITE);
    srandom(time(NULL));
    num = random() % 7;
    HgTextSize(&x, &y, "＊%s＊", omikuji[num]);
    HgText(100 - x / 2, 530, "＊%s＊", omikuji[num]);

    HgSetColor(HG_DRED);
    HgSetFont(HG_C, 20);

    for (i = 0; i < 3; i++) {
        num = random() % LAST_LINE_NUM;
        for (j = 0; j < strlen(scripts[num].words) / 3; j++) {
            HgText(45 + i * 50, 450 - j * 20, "%c%c%c\n",
                   scripts[num].words[j * 3], scripts[num].words[j * 3 + 1],
                   scripts[num].words[j * 3 + 2]);
        }
    }

    HgGetChar();
    HgClose();
    return 0;
}
