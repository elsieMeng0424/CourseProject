#include <iostream>  
#include <iomanip>     
#include <graphics.h>  
#include <math.h>  
#include <conio.h>  
#include <time.h>  
using namespace std;
#define PI 3.1415926  
#define MY_RED RGB(255,32,21)
#define MY_ORANGE RGB(240, 157, 27)
#define MY_BLUE RGB(115, 251, 253)
#define MY_YELLOW RGB(253, 255, 45)
#define MY_GREY RGB(70,70,70)
#define MY_DARKRED RGB(179,0,0)

const int height = 480;
const int width = 640;
const int FPS = 30;
struct Point
{
    int x;
    int y;
};

double length(Point a, Point b)/*��������֮��ĳ���*/
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double multiplication(Point a, Point b)/*�����������ĳ˻�*/
{
    return a.x * b.x + a.y * b.y;
}

int sdf_color(int bg, int color, double alpha)/*����alpha blending�㷨�������ص����ɫ*/
{
    return RGB(GetRValue(bg) * (1 - alpha) + GetRValue(color) * alpha, GetGValue(bg) * (1 - alpha) + GetGValue(color) * alpha, GetBValue(bg) * (1 - alpha) + GetBValue(color) * alpha);
}

double sdf_of_circle(Point o, Point p, int r)/*����Բ�ε�SDF*/
{
    return length(o, p) - r;
}

void SDF_Circle(Point o, int color, int r)/*Բ�ε�SDF+alpha blending�㷨�����*/
{
    Point p;
    double d, alpha;
    int X, Y;
    for (X = o.x - r - 5; X < o.x + r + 5; X++) {
        for (Y = o.y - r - 5; Y < o.y + r + 5; Y++) {
            p = { X,Y };
            d = sdf_of_circle(o, p, r);
            alpha = 1 - d / 3;/*d/3ʱ�Ӿ�Ч������Ƿ�������ת��ԲȦ�����Ч�����ѣ�d/4ʱ��תԲȦ������Ժõ���Ȼ���ѣ������廭���Եú�����*/
            if (alpha >= 0 && alpha <= 1)
                putpixel(X, Y, sdf_color(getpixel(X, Y), color, alpha));
            else if (d < 0)
                continue;/*�ڲ�ֱ��ͨ��fillcircle()���������Լ��ټ���ʱ��*/
        }
    }
    setfillcolor(color);
    setlinecolor(color);
    fillcircle(o.x, o.y, r);
}

double sdf_of_line(Point p, Point a, Point b)/*����ֱ�ߵ�SDF*/
{
    Point ap = { p.x - a.x,p.y - a.y };
    Point ab = { b.x - a.x,b.y - a.y };
    double h = (multiplication(ap, ab) / multiplication(ab, ab));
    if (h < 0)/*�����˵�֮��������ȡֱ��ʹ�ö˵��������֮��ľ�����ΪSDF*/
        h = 0;
    else if (h > 1)
        h = 1;
    double X = a.x + h * (b.x - a.x), Y = a.y + h * (b.y - a.y);
    return length({ int(X),int(Y) }, p);
}

void SDF_Line(Point a, Point b, int color)/*Բ�ε�SDF+alpha blending�㷨�����*/
{
    Point p;
    double d, alpha;
    int X, Y;
    for (X = min(a.x, b.x) - 10; X <= max(a.x, b.x) + 10; X++) {
        for (Y = min(a.y, b.y) - 10; Y <= max(a.y, b.y) + 10; Y++) {
            p = { X,Y };
            d = sdf_of_line(p, a, b);
            alpha = 1 - d / 3;
            if (alpha >= 0 && alpha <= 1)
                putpixel(X, Y, sdf_color(getpixel(X, Y), color, alpha));
        }
    }
    setlinecolor(color);
    line(a.x, a.y, b.x, b.y);
}

void background()/*����Ч���ı���*/
{
    double x, y;

    for (x = width / 2, y = -height / 2; x >= -width / 2 && y <= height / 2; x -= (width / height), y += 1) {
        setlinecolor(RGB(int(150 - (-height / 2 - y) * 105 / height),
            int(150 - (-height / 2 - y) * 105 / height), int(150 - (-height / 2 - y) * 105 / height)));
        line(-width / 2, int(y), int(x), height / 2);
    }
    for (x = -width / 2, y = height / 2; x <= width / 2 && y >= -height; x += (width / height), y -= 1) {
        setlinecolor(RGB(int(150 - (height / 2 - y) * 105 / height),
            int(150 - (height / 2 - y) * 105 / height), int(150 - (height / 2 - y) * 105 / height)));
        line(int(x), -height / 2, width / 2, int(y));
    }
    /*���ɫ����ɫ�Ľ���*/
}

void DrawCircle(int x, int y, int r, int color)/*��Բ*/
{
    SDF_Circle({ x,y }, color, r);
}

void DrawPointer(int x1, int x2, int color)/*����ָ��*/
{
    for (double theta = 0; theta < 2 * PI; theta += (PI / 6)) {
        SDF_Line({ int(x1 * sin(theta)), int(x1 * cos(theta)) }, { int(x2 * sin(theta)), int(x2 * cos(theta)) }, color);
    }/*ÿPI/6һ��ָ��*/
}

void DrawLittlePointer(int x1, int x2, int color)
{
    setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 1);
    setlinecolor(color);
    for (double theta = 0; theta < 2 * PI; theta += (PI / 30)) {
        line(int(x1 * sin(theta)), int(x1 * cos(theta)), int(x2 * sin(theta)), int(x2 * cos(theta)));
    }
    setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 3);
}

void Rotating_Ring(int x, int y, int r1, int r2, int color1, double angle)/*������ת������Բ��*/
{
    DrawCircle(x, y, r1, color1);
    fillpie(r2, r2, -r2, -r2, angle, angle + PI / 2);
    fillpie(r2, r2, -r2, -r2, angle + PI, angle + PI * 3 / 2);
}

void Ball_Tail(double theta)/*���н���ɫ��С��β��*/
{
    double angle = theta - PI / 6;
    for (; angle <= theta; angle += PI / 60000) {
        setlinecolor(RGB(int(255 - 15 * (angle - theta + PI / 6) / (PI / 6)), int(32 + 125 * (angle - theta + PI / 6) / (PI / 6)),
            int(21 + 6 * (angle - theta + PI / 6) / (PI / 6))));
        line(0, 0, int(50 * sin(angle)), int(50 * cos(angle)));
    }
}

void Minute_Pointer(int x, int y, int r, double angle, int color)
{
    SDF_Line({ 0, 0 }, { int(r * sin(angle)), int(r * cos(angle)) }, color);
}

// ��ȷ��ʱ����(���Ծ�ȷ�� 1ms������ ��1ms)
void HpSleep(int ms)
{
    static clock_t oldclock = clock();   // ��̬��������¼��һ�� tick
    oldclock += ms * CLOCKS_PER_SEC / 1000;  // ���� tick
    if (clock() > oldclock)      // ����Ѿ���ʱ��������ʱ
        oldclock = clock();
    else
        while (clock() < oldclock)     // ��ʱ
            Sleep(1);        // �ͷ� CPU ����Ȩ������ CPU ռ����
}
int getTime()
{
    return clock() / CLOCKS_PER_SEC;
}
int main()
{
    struct tm t;
    time_t now;
    time(&now);
    localtime_s(&t, &now);
    int lastTime = 0;
    float x = 0, y = 0, * p_x = &x, * p_y = &y;
    double angle_blue = -PI / 2, angle_red = 0;
    double angle_yellow = ((t.tm_sec + t.tm_min * 60 + (t.tm_hour % 12) * 3600) * 2 * PI / (12 * 3600)),
        angle_orange = (t.tm_sec) * 2 * PI / 60, angle_pointer = (t.tm_sec + t.tm_min * 60) * 2 * PI / 3600;
    initgraph(width, height);
    setorigin(width / 2, height / 2);
    getaspectratio(p_x, p_y);
    setaspectratio(*p_x, -(*p_y));
    BeginBatchDraw();
    background();
    DrawCircle(0, 0, 220, MY_GREY);
    DrawCircle(0, 0, 200, MY_RED);
    DrawCircle(0, 0, 193, BLACK);
    setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 3);
    DrawPointer(170, 197, MY_RED);
    EndBatchDraw();
    while (!_kbhit())
    {
        int now = getTime();
        BeginBatchDraw();
        DrawCircle(0, 0, 160, BLACK);
        Rotating_Ring(0, 0, 150, 160, MY_BLUE, angle_blue);
        angle_blue += (PI / 300);
        DrawCircle(0, 0, 145, BLACK);
        DrawCircle(int(130 * sin(angle_yellow)), int(130 * cos(angle_yellow)), 15, MY_YELLOW);
        if (now - lastTime > 0) {
            angle_yellow += 2 * PI / (60 * 60 * 12);
        }
        Rotating_Ring(0, 0, 110, 115, MY_RED, angle_red);
        angle_red -= (PI / 300);
        DrawCircle(0, 0, 105, BLACK);
        for (int r = 78; r >= 70; r--) {
            DrawCircle(0, 0, r, (78 - r) * 179 / 8);
        }
        DrawCircle(0, 0, 70, MY_DARKRED);
        DrawCircle(0, 0, 50, MY_RED);
        DrawPointer(50, 70, MY_RED);
        DrawLittlePointer(65, 70, MY_RED);
        DrawCircle(int(45 * sin(angle_orange)), int(45 * cos(angle_orange)), 5, MY_ORANGE);
        Ball_Tail(angle_orange);
        if (now - lastTime > 0) {
            angle_orange += 2 * PI / (60);
        }
        DrawCircle(0, 0, 36, MY_RED);
        Minute_Pointer(0, 0, 50, angle_pointer, BLACK);
        if (now - lastTime > 0) {
            angle_pointer += 2 * PI / (60 * 60);
            lastTime = now;
        }
        EndBatchDraw();
        HpSleep(int(1000 / 30));
    }
    _getch();
    closegraph();
    return 0;
}