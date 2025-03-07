#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <stdlib.h>
using namespace std;

COLORREF MY_RED = RGB(237, 16, 16);
COLORREF MY_YELLOW = RGB(237, 235, 74);
COLORREF MY_PURPLE = RGB(148, 8, 247);
COLORREF MY_GREEN = RGB(35, 237, 44);
COLORREF MY_BLUE = RGB(36, 100, 255);
COLORREF MY_ORANGE = RGB(255, 145, 27);
COLORREF MY_DARK_BLUE = RGB(6, 21, 150);
COLORREF MY_PINK = RGB(255, 102, 245);
COLORREF MY_YELLOW2 = RGB(255, 196, 17);
COLORREF MY_LIGHT_BLUE = RGB(2, 255, 250);
fstream file;
char username[21];
int footstep = 10;
int width = 800;
int height = 600;
int ori_len = 6;
int record = 0;
int record2 = 0;
int record3 = 0;
int count_eat = 0;

void set_color(COLORREF lineColor, COLORREF fillColor)
{
	setlinecolor(lineColor);
	setfillcolor(fillColor);
}

struct Point {
	int x;
	int y;
};

class Snake;
class Game {
public:
	int score;
	int life;
	Game();
};

Game::Game()
{
	score = 0;
	life = 5;
}

class Wall {
private:
public:
	int num;
	POINT* pos;
	bool ifexist;
	Wall() { num = 0; pos = NULL; ifexist = false; }
	~Wall() { delete pos; }
	void create(Snake snake);
	void draw();
	void draw_senior();
	void Delete(int);
};

class Fruit {
private:
	Point pos;
	COLORREF linecolor;
	COLORREF fillcolor;
public:
	char effect;
	bool exist;
	Fruit();
	void create(Fruit*, Snake, int);
	void create(Fruit*, Snake, int, Wall*);
	void draw();
	int value_x();
	int value_y();
	void Delete();
};

class Snake {
private:
	Point headPos;
	Point tailPos;
	Point body[500];
	COLORREF color1;
	COLORREF color2;
	int len;
public:
	bool ifGod;
	int type;
	char headToward;
	bool death;
	int speed;
	Snake(int);
	Snake(int, Wall *);
	void initDraw();
	void draw();
	void check_death(Wall*);
	bool check_fruit(Fruit);
	bool check_fruit_senior(Wall*);
	void move(Fruit*, int, Game&);
	void move(Fruit*, int, Game&, Wall*);
	void move_senior(Fruit*, int, Game&, Wall*);
	int value_len();
	void turn_to_God();
	void turn_to_normal();
	Point value_body(int i);
};

Snake::Snake(int T)
{
	headToward = '0'; 
	for (int i = 0; i < ori_len; i++)
		body[i] = { width / (2 * footstep) + i,height / (2 * footstep) };
	headPos = body[0];
	tailPos = body[5];
	len = ori_len;
	death = false;
	speed = 5;
	type = T;
	ifGod = false;
	switch (T) {
		case 0:
			color1 = MY_BLUE;
			color2 = WHITE;
			break;
		case 1:
			color1 = MY_PURPLE;
			color2 = MY_GREEN;
			break;
		case 2:
			color1 = MY_RED;
			color2 = MY_ORANGE;
			break;
		case 3:
			color1 = MY_DARK_BLUE;
			color2 = MY_YELLOW;
			break;
		case 4:
			color1 = MY_PINK;
			color2 = WHITE;
			break;
		default:
			color1 = 0;
			color2 = 0;
			break;
	}
}

Snake::Snake(int T, Wall *wall)
{
	headToward = '0';
	int count = 0;
	bool ifIden=false;
	while (count<=1000000) {
		body[0].x = rand() % (width / footstep-5);
		body[0].y = rand() % (height / footstep);
		for (int i = 1; i < ori_len; i++)
			body[i] = { body[0].x + i,body[0].y };
		for (int i = 0; i < ori_len; i++) {
			for (int j = 0; j < 4; j++) {
				if (wall[j].ifexist) {
					for (int k = 0; k < wall[j].num; j++) {
						if (body[i].x == wall[j].pos[k].x && body[i].y == wall[j].pos[k].y) {
							ifIden = true;
							break;
						}
					}
				}
				if (ifIden)
					break;
			}
			if (ifIden)
				break;
		}
		if (!ifIden)
			break;
	}
	
	headPos = body[0];
	tailPos = body[5];
	len = ori_len;
	death = false;
	if (ifIden)
		death = true;
	speed = 5;
	type = T;
	ifGod = false;
	switch (T) {
		case 0:
			color1 = MY_BLUE;
			color2 = WHITE;
			break;
		case 1:
			color1 = MY_PURPLE;
			color2 = MY_GREEN;
			break;
		case 2:
			color1 = MY_RED;
			color2 = MY_ORANGE;
			break;
		case 3:
			color1 = MY_DARK_BLUE;
			color2 = MY_YELLOW;
			break;
		case 4:
			color1 = MY_PINK;
			color2 = WHITE;
			break;
		default:
			color1 = 0;
			color2 = 0;
			break;
	}
}

void Snake::initDraw()
{
	BeginBatchDraw();
	set_color(color2, color1);
	for (int i = 0; i < ori_len; i++) {
		if (i == 1) {
			set_color(color2, color2);
			fillrectangle(body[i].x * footstep, body[i].y * footstep, body[i].x * footstep + footstep, body[i].y * footstep + footstep);
			set_color(color2, color1);
		}
		fillrectangle(body[i].x * footstep, body[i].y * footstep, body[i].x * footstep + footstep, body[i].y * footstep + footstep);
	}
	EndBatchDraw();
}

void Snake::draw()
{
	if (!death) {
		BeginBatchDraw();
		if (headToward != '0') {
			set_color(BLACK, BLACK);
			fillrectangle(tailPos.x * footstep, tailPos.y * footstep, tailPos.x * footstep + footstep, tailPos.y * footstep + footstep);
		}
		set_color(color2, color1);
		fillrectangle(headPos.x * footstep, headPos.y * footstep, headPos.x * footstep + footstep, headPos.y * footstep + footstep);
		fillrectangle(body[2].x * footstep, body[2].y * footstep, body[2].x * footstep + footstep, body[2].y * footstep + footstep);
		set_color(color2, color2);
		fillrectangle(body[1].x * footstep, body[1].y * footstep, body[1].x * footstep + footstep, body[1].y * footstep + footstep);
		EndBatchDraw();
	}
}

void Snake::check_death(Wall* wall=NULL)
{
	int i = 0;
	while (!i) {
		for (int i = 3; i < len; i++) {
			if (headPos.x == body[i].x && headPos.y == body[i].y) {
				death = true;
				break;
			}
		}
		if (headPos.x == -1 || headPos.y == -1 || headPos.x == width / footstep || headPos.y == height / footstep) {
			death = true;
			break;
		}
		if (wall != NULL) {
			for (int i = 0; i < 4; i++) {
				if (wall[i].ifexist) {
					for (int j = 0; j < wall[i].num; j++) {
						if (headPos.x == wall[i].pos[j].x && headPos.y == wall[i].pos[j].y) {
							death = true;
							break;
						}
					}
				}
			}
		}
		i++;
	}
}

bool Snake::check_fruit(Fruit fruit)
{
	return headPos.x == fruit.value_x() && headPos.y == fruit.value_y();
}

bool Snake::check_fruit_senior(Wall* wall)
{
	bool flag = false;
	for (int i = 0; i < 4; i++)
	{
		if (wall[i].ifexist) {
			for (int j = 0; j < wall[i].num; j++)
			{
				if (headPos.x == wall[i].pos[j].x && headPos.y == wall[i].pos[j].y) {
					flag = true;
					wall[i].Delete(j);
					break;
				}
			}
			if (flag)
				break;
		}
	}
	return flag;
}

void Snake:: move(Fruit* fruit,int num,Game &game)
{
	tailPos = body[len - 1];
	switch (headToward) {
		case 'U':
			headPos.y--;
			break;
		case 'D':
			headPos.y++;
			break;
		case 'L':
			headPos.x--;
			break;
		case 'R':
			headPos.x++;
			break;
		default:
			break;
	}
	int pts[] = { 900,42,1000,42,1000,250,900,260 };
	if (headToward != '0') {
		for (int i = len - 1; i > 0; i--) {
			body[i] = body[i - 1];
		}
		body[0] = headPos;
		check_death();
		for (int i = 0; i < num; i++) {
			if (check_fruit(fruit[i])) {
				count_eat++;
				fruit[i].exist = 0;
				game.score += 100;
				if (ifGod)
					game.score += 200;
				if(len<499)
				    len++;
				body[len] = tailPos;
				if (speed < 24)
					speed++;
				char ch_score[10], ch_speed[3], ch_len[4];
				set_color(BLACK, BLACK);
				fillpolygon((POINT*)pts, 4);
				sprintf(ch_score, "%d", game.score);
				sprintf(ch_speed, "%d", speed - 4);
				sprintf(ch_len, "%d", len);
				outtextxy(900, 42, ch_score);
				outtextxy(900, 242, ch_speed);
				outtextxy(900, 142, ch_len);
				fruit[i].Delete();
			}
		}
	}
}

void Snake::move(Fruit* fruit, int num, Game& game, Wall* wall)
{
	BeginBatchDraw();
	tailPos = body[len - 1];
	switch (headToward) {
		case 'U':
			headPos.y--;
			break;
		case 'D':
			headPos.y++;
			break;
		case 'L':
			headPos.x--;
			break;
		case 'R':
			headPos.x++;
			break;
		default:
			break;
	}
	int pts[] = { 900,42,1000,42,1000,160,900,160 };
	int pts1[] = { 900,242,1000,242,1000,260,900,260 };
	set_color(BLACK, BLACK);
	fillpolygon((POINT*)pts1, 4);
	char ch_life[2];
	sprintf(ch_life, "%d", game.life);
	outtextxy(900, 242, ch_life);
	
	if (headToward != '0') {
		for (int i = len - 1; i > 0; i--) {
			body[i] = body[i - 1];
		}
		body[0] = headPos;
		check_death(wall);
		for (int i = 0; i < num; i++) {
			if (check_fruit(fruit[i])) {
				count_eat++;
				fruit[i].exist = 0;
				game.score += 100;
				if (ifGod)
					game.score += 200;
				if(len<499)
				    len++;
				body[len] = tailPos;
				if (speed < 24)
					speed++;
				char ch_score[10], ch_len[4];
				set_color(BLACK, BLACK);
				fillpolygon((POINT*)pts, 4);
				sprintf(ch_score, "%d", game.score);
				sprintf(ch_len, "%d", len);
				outtextxy(900, 42, ch_score);
				outtextxy(900, 142, ch_len);
				fruit[i].Delete();
			}
		}
	}
	EndBatchDraw();
}

void Snake::move_senior(Fruit* fruit, int num, Game& game, Wall* wall)
{
	BeginBatchDraw();
	tailPos = body[len - 1];
	switch (headToward) {
		case 'U':
			headPos.y--;
			break;
		case 'D':
			headPos.y++;
			break;
		case 'L':
			headPos.x--;
			break;
		case 'R':
			headPos.x++;
			break;
		default:
			break;
	}
	int pts[] = { 900,42,1000,42,1000,160,900,160 };
	int pts1[] = { 900,242,1000,242,1000,260,900,260 };
	set_color(BLACK, BLACK);
	fillpolygon((POINT*)pts1, 4);
	char ch_life[2];
	sprintf(ch_life, "%d", game.life);
	outtextxy(900, 242, ch_life);

	if (headToward != '0') {
		for (int i = len - 1; i > 0; i--) {
			body[i] = body[i - 1];
		}
		body[0] = headPos;
		check_death();
		for (int i = 0; i < num; i++) {
			if (check_fruit(fruit[i])) {
				count_eat++;
				fruit[i].exist = 0;
				game.score += 100;
				if (ifGod)
					game.score += 200;
				if(len<499)
				    len++;
				body[len] = tailPos;
				if (speed < 24)
					speed++;
				char ch_score[10], ch_len[4];
				set_color(BLACK, BLACK);
				fillpolygon((POINT*)pts, 4);
				sprintf(ch_score, "%d", game.score);
				sprintf(ch_len, "%d", len);
				outtextxy(900, 42, ch_score);
				outtextxy(900, 142, ch_len);
				fruit[i].Delete();
			}
			else if (check_fruit_senior(wall)) {
				count_eat++;
				game.score += 100;
				if (ifGod)
					game.score += 200;
				len++;
				body[len] = tailPos;
				if (speed < 24)
					speed++;
				char ch_score[10], ch_len[4];
				set_color(BLACK, BLACK);
				fillpolygon((POINT*)pts, 4);
				sprintf(ch_score, "%d", game.score);
				sprintf(ch_len, "%d", len);
				outtextxy(900, 42, ch_score);
				outtextxy(900, 142, ch_len);
			}
		}
	}
	EndBatchDraw();
}

int Snake::value_len()
{
	return len;
}

Point Snake::value_body(int i)
{
	return body[i];
}

void Snake::turn_to_God()
{
	switch (type) {
		case 0:
			color1 = MY_YELLOW2;
			break;
		case 1:
			color2 = MY_RED;
			break;
		case 2:
			color2 = MY_LIGHT_BLUE;
			break;
		case 3:
			color2 = MY_RED;
			break;
		case 4:
			color2 = MY_LIGHT_BLUE;
			break;
	}
	ifGod = true;
}

void Snake::turn_to_normal()
{
	switch (type) {
		case 0:
			color1 = MY_BLUE;
			break;
		case 1:
			color2 = MY_GREEN;
			break;
		case 2:
			color2 = MY_ORANGE;
			break;
		case 3:
			color2 = MY_YELLOW;
			break;
		case 4:
			color2 = WHITE;
			break;
	}
	ifGod = false;
}

Fruit::Fruit()
{
	pos.x = 0;
	pos.y = 0;
	linecolor = MY_YELLOW;
	fillcolor = MY_RED;
	effect = 'A';
	exist = 0;
}

void Fruit::create(Fruit* fruit, Snake snake,int num)
{
	bool ifIden = false;
	while (true) {
		ifIden = false;
		pos.x = rand() % (width / footstep);
		pos.y = rand() % (height / footstep);
		int i = 0;
		while (i<num) {
			if (pos.x == fruit[i].pos.x && pos.y == fruit[i].pos.y) {
				ifIden = true;
				break;
			}
			i++;
		}
		if (ifIden)
			continue;
		for (int i = 0; i < snake.value_len(); i++) {
			if (pos.x == snake.value_body(i).x && pos.y == snake.value_body(i).y) {
				ifIden = true;
				break;
			}
		}
		if (!ifIden)
			break;
	}
	linecolor = MY_YELLOW;
	fillcolor = MY_RED;
	effect = 'A';
	exist = 1;
}
void Fruit::create(Fruit* fruit, Snake snake, int num,Wall* wall)
{
	bool ifIden = false;
	while (true) {
		ifIden = false;
		pos.x = rand() % (width / footstep);
		pos.y = rand() % (height / footstep);
		int i = 0;
		while (i < num) {
			if (pos.x == fruit[i].pos.x && pos.y == fruit[i].pos.y) {
				ifIden = true;
				break;
			}
			i++;
		}
		if (ifIden)
			continue;
		for (int i = 0; i < snake.value_len(); i++) {
			if (pos.x == snake.value_body(i).x && pos.y == snake.value_body(i).y) {
				ifIden = true;
				break;
			}
		}
		for (int i = 0; i < 4; i++)
		{
			if (wall[i].ifexist) {
				for (int j = 0; j < wall[i].num; j++) {
					if (pos.x == wall[i].pos[j].x && pos.y == wall[i].pos[j].y) {
						ifIden = true;
						break;
					}
				}
			}
			if (ifIden)
				break;
		}
		if (!ifIden)
			break;
	}
	linecolor = MY_YELLOW;
	fillcolor = MY_RED;
	effect = 'A';
	exist = 1;
}

void Fruit::draw()
{
	set_color(linecolor, fillcolor);
	fillrectangle(pos.x * footstep, pos.y * footstep, pos.x * footstep + footstep, pos.y * footstep + footstep);
}

int Fruit::value_x()
{
	return pos.x;
}

int Fruit::value_y()
{
	return pos.y;
}

void Wall::create(Snake snake)
{
	num = snake.value_len();
	pos = new POINT[num];
	for (int i = 0; i < num; i++) {
		pos[i].x = snake.value_body(i).x;
		pos[i].y = snake.value_body(i).y;
	}
	ifexist = true;
}

void Wall::draw()
{
	set_color(MY_ORANGE, MY_ORANGE);
	for (int i = 0; i < num; i++) {
		if (pos[i].x != -1)
			fillrectangle(pos[i].x * footstep, pos[i].y * footstep, pos[i].x * footstep + footstep, pos[i].y * footstep + footstep);
	}
}

void Wall::draw_senior()
{
	set_color(MY_YELLOW, MY_RED);
	for (int i = 0; i < num; i++) {
		if (pos[i].x != -1)
			fillrectangle(pos[i].x * footstep, pos[i].y * footstep, pos[i].x * footstep + footstep, pos[i].y * footstep + footstep);
	}
}

void Wall::Delete(int index)
{
	pos[index].x = -1;
	pos[index].y = -1;
}

void readKeyboard(Snake& snake, int& ifBegin)
{
	char pre_Toward = snake.headToward;
	if (_kbhit())
	{
		fflush(stdin);
		int ch;
		ch = _getch();
		ch = _getch();
		switch (ch) {
			case 72:
				snake.headToward = 'U';
				break;
			case 80:
				snake.headToward = 'D';
				break;
			case 75:
				snake.headToward = 'L';
				break;
			case 77:
				snake.headToward = 'R';
				break;
			default:
				break;
		}
	}
	
	if (pre_Toward == 'U' && snake.headToward == 'D')
		snake.headToward = 'U';
	if (pre_Toward == 'D' && snake.headToward == 'U')
		snake.headToward = 'D';
	if (pre_Toward == 'L' && snake.headToward == 'R')
		snake.headToward = 'L';
	if (pre_Toward == 'R' && snake.headToward == 'L')
		snake.headToward = 'R';
	if (pre_Toward == '0' && snake.headToward == 'R')
		snake.headToward = '0';
	if (snake.headToward != '0')
		ifBegin = 1;
}

void drawTime(int init_time)
{
	BeginBatchDraw();
	int pts[] = { 900,342,1000,342,1000,360,900,360 };
	int time = clock() - init_time;
	time = time / 1000;
	int hour = time / 3600;
	int minute = time % 3600 / 60;
	int second = time % 60;
	char ch[9];
	ch[0] = (hour / 10) + '0';
	ch[1] = (hour % 10) + '0';
	ch[2] = ':';
	ch[3] = (minute / 10) + '0';
	ch[4] = (minute % 10) + '0';
	ch[5] = ':';
	ch[6] = (second / 10) + '0';
	ch[7] = (second % 10) + '0';
	ch[8] = '\0';
	set_color(BLACK, BLACK);
	fillpolygon((POINT*)pts, 4);
	outtextxy(900, 342, ch);
	EndBatchDraw();
}

void Fruit::Delete()
{
	pos.x = -1;
	pos.y = -1;
}

void starter_mode(int type)
{
	file.open("record.txt", ios::in);
	file >> record;
	file >> record2;
	file >> record3;
	initgraph(width + 200, height);
	file.close();

	IMAGE img(width, height);
	loadimage(&img, _T("EVA蛇来袭.jpg"));
	putimage(80, 50, &img);
	LOGFONT style;
	gettextstyle(&style);
	int ifBegin = 0;
	int init_time = -1;
	int God_time = 0;
	bool chance_of_God = true;
	int pts1[] = { 840,500,960,500,960,570,840,570 };
	int pts2[] = { 845,505,955,505,955,565,845,565 };
	int pts3[] = { 0,0,800,0,800,600,0,600 };
	int pts4[] = { 900,442,1000,442,1000,460,900,460 };
	count_eat = 0;
	Game game;
	Snake snake(type);
	Fruit fruit[5];
	RECT r_score = { 800,0,900,100 };
	RECT r_len = { 810,100,900,200 };
	RECT r_speed = { 800,200,900,300 };
	RECT r_time = { 790,300,900,400 };
	RECT r_death = { 0,0,800,600 };
	RECT r_record = { 810,400,900,500 };
	RECT r_condition = { 865,520,935,550 };
	char ch_record[10];

	set_color(WHITE, WHITE);
	line(801, 0, 801, 600);
	drawtext(_T("SCORE:"), &r_score, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("SPEED:"), &r_speed, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("LENGTH:"), &r_len, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("TIME:"), &r_time, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("RECORD:"), &r_record, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	set_color(WHITE, WHITE);
	fillpolygon((POINT*)pts1, 4);
	set_color(MY_GREEN,MY_GREEN);
	fillpolygon((POINT*)pts2, 4);
	setbkmode(TRANSPARENT);
	settextstyle(30, 15, _T("黑体"));
	drawtext(_T("正常"), &r_condition, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	settextstyle(&style);
	outtextxy(900, 42, '0');
	outtextxy(900, 142, '6');
	outtextxy(900, 242, '1');
	outtextxy(900, 342, "00:00:00");
	sprintf(ch_record, "%d", record);
	outtextxy(900, 442, ch_record);
	Sleep(1500);
	set_color(BLACK, BLACK);
	fillpolygon((POINT*)pts3, 4);

	for (int i = 0; i < 5; i++) {
		fruit[i].create(fruit, snake, i);
		fruit[i].draw();
	}
	snake.initDraw();

	while (!snake.death) {
		readKeyboard(snake, ifBegin);
		bool checkFruitAll = 1;
		for (int i = 0; i < 5; i++) {
			if (fruit[i].exist == true) {
				checkFruitAll = 1;
				break;
			}
			checkFruitAll = 0;
		}
		if (!checkFruitAll) {
			for (int i = 0; i < 5; i++) {
				fruit[i].create(fruit, snake, i);
				fruit[i].draw();
			}
		}
		snake.move(fruit, 5, game);
		if (((clock() - God_time)/1000 >= 15) && God_time!=0) {
			chance_of_God = true;
			snake.turn_to_normal();
			set_color(MY_GREEN, MY_GREEN);
			fillpolygon((POINT*)pts2, 4);
			setbkmode(TRANSPARENT);
			settextstyle(30, 15, _T("黑体"));
			drawtext(_T("正常"), &r_condition, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			settextstyle(&style);
			settextcolor(WHITE);
			God_time = 0;
		}
		snake.draw();
		
		if (count_eat  == 10 && count_eat!=0&&chance_of_God) {
			set_color(MY_RED, MY_RED);
			fillpolygon((POINT*)pts2, 4);
			setbkmode(TRANSPARENT);
			settextstyle(30, 15, _T("黑体"));
			settextcolor(BLACK);
			drawtext(_T("暴走"), &r_condition, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			settextstyle(&style);
			settextcolor(WHITE);
			snake.turn_to_God();
			chance_of_God = false;
			God_time = clock();
			count_eat = 0;
		}
		if (game.score > record) {
			record = game.score;
			set_color(BLACK, BLACK);
			fillpolygon((POINT*)pts4, 4);
			sprintf(ch_record, "%d", record);
			outtextxy(900, 442, ch_record);
		}
		Sleep(1000 / snake.speed);
		if (ifBegin) {
			if (init_time == -1) {
				init_time = clock();
			}
			drawTime(init_time);
		}
	}
	Sleep(500);
	set_color(BLACK, BLACK);
	fillpolygon((POINT*)pts3, 4);
	IMAGE img_death(640, 480);
	loadimage(&img_death, _T("死亡.jpg"));
	putimage(120,100, &img_death);
	settextcolor(WHITE);
	outtextxy(0, 0, "press enter to continue...");
	outtextxy(0, 20, "press Q to quit...");
	
	file.open("record.txt", ios::out);
	file << record << endl;
	file << record2 << endl;
	file << record3 << endl;
	file.close();
	file.open("history.txt", ios::out | ios::app);
	file << "版本：入门版 用户名：" << username << " 得分：" << game.score << " 驾驶的机体：EVANGELION-0";
	if (type >= 0 && type <= 2)
		file << type << endl;
	else if (type > 2)
		file << type * 2 << endl;
	file.close();
}

void readMouse(int& mode)
{
	MOUSEMSG m{ 0 };
	bool flag = true;
	while (flag)
	{
		if (MouseHit())m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN && m.x >= 20 && m.x <= 260 && m.y >= 140 && m.y <= 210) {
			mode = 1;
			flag = false;
		}
		if (m.uMsg == WM_LBUTTONDOWN && m.x >= 20 && m.x <= 260 && m.y >= 230 && m.y <= 300) {
			mode = 2;
			flag = false;
		}
		if (m.uMsg == WM_LBUTTONDOWN && m.x >= 20 && m.x <= 260 && m.y >= 320 && m.y <= 390) {
			mode = 3;
			flag = false;
		}
		if (m.uMsg == WM_LBUTTONDOWN && m.x >= 20 && m.x <= 340 && m.y >= 410 && m.y <= 480) {
			mode = 4;
			flag = false;
		}
		if (m.uMsg == WM_LBUTTONDOWN && m.x >= 20 && m.x <= 180 && m.y >= 500 && m.y <= 590) {
			mode = 5;
			flag = false;
		}
	}
}

int menu()
{
	int mode;
	initgraph(950, 650);
	IMAGE img_menu(950, 650);
	loadimage(&img_menu, _T("menu.jpg"));
	putimage(0, 0, &img_menu);
	settextstyle(70, 40, _T("黑体"));
	outtextxy(20, 140, "入门版");
	outtextxy(20, 230, "进阶版");
	outtextxy(20, 320, "高级版");
	outtextxy(20, 410, "历史记录");
	outtextxy(20, 500, "退出");
	setbkmode(TRANSPARENT);
	settextstyle(80, 60, _T("黑体"));
	settextcolor(WHITE);
	outtextxy(20, 20, "EVA SNAKE");
	readMouse(mode);
	switch (mode) {
		case 1:
			settextcolor(MY_LIGHT_BLUE);
			settextstyle(70, 40, _T("黑体"));
			outtextxy(20, 140, "入门版");
			break;
		case 2:
			settextcolor(MY_LIGHT_BLUE);
			settextstyle(70, 40, _T("黑体"));
			outtextxy(20, 230, "进阶版");
			break;
		case 3:
			settextcolor(MY_LIGHT_BLUE);
			settextstyle(70, 40, _T("黑体"));
			outtextxy(20, 320, "高级版");
			break;
		case 4:
			settextcolor(MY_LIGHT_BLUE);
			settextstyle(70, 40, _T("黑体"));
			outtextxy(20, 410, "历史记录");
			break;
		case 5:
			settextcolor(MY_LIGHT_BLUE);
			settextstyle(70, 40, _T("黑体"));
			outtextxy(20, 500, "退出");
			break;
		default:
			break;
	}
	Sleep(200);
	closegraph();
	return mode;
}

void advanced_version(int type)
{
	file.open("record.txt", ios::in);
	file >> record;
	file >> record2;
	file >> record3;
	initgraph(width + 200, height);
	file.close();

	IMAGE img(width, height);
	loadimage(&img, _T("EVA蛇来袭.jpg"));
	putimage(80, 50, &img);
	LOGFONT style;
	gettextstyle(&style);
	Wall wall[4];
	int ifBegin = 0;
	int init_time = -1;
	int God_time = 0;
	bool chance_of_God = true;
	int pts1[] = { 840,500,960,500,960,570,840,570 };
	int pts2[] = { 845,505,955,505,955,565,845,565 };
	int pts3[] = { 0,0,800,0,800,600,0,600 };
	int pts4[] = { 900,442,1000,442,1000,460,900,460 };
	count_eat = 0;
	Game game;
	RECT r_score = { 800,0,900,100 };
	RECT r_len = { 810,100,900,200 };
	RECT r_life = { 800,200,900,300 };
	RECT r_time = { 790,300,900,400 };
	RECT r_death = { 0,0,800,600 };
	RECT r_record = { 810,400,900,500 };
	RECT r_condition = { 865,520,935,550 };
	char ch_record[10], ch;

	set_color(WHITE, WHITE);
	line(801, 0, 801, 600);
	drawtext(_T("SCORE:"), &r_score, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("LIFE:"), &r_life, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("LENGTH:"), &r_len, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("TIME:"), &r_time, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("RECORD:"), &r_record, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	set_color(WHITE, WHITE);
	fillpolygon((POINT*)pts1, 4);

	settextstyle(&style);
	outtextxy(900, 42, '0');
	outtextxy(900, 142, '6');
	outtextxy(900, 242, '5');
	outtextxy(900, 342, "00:00:00");
	sprintf(ch_record, "%d", record2);
	outtextxy(900, 442, ch_record);
	Sleep(1500);
	set_color(BLACK, BLACK);
	fillpolygon((POINT*)pts3, 4);

	while (game.life) {
		set_color(MY_GREEN, MY_GREEN);
		fillpolygon((POINT*)pts2, 4);
		setbkmode(TRANSPARENT);
		settextstyle(30, 15, _T("黑体"));
		drawtext(_T("正常"), &r_condition, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		settextstyle(&style);
		settextcolor(WHITE);
		Snake snake(type,wall);
		Snake last_snake = snake;
		Fruit fruit[5];
		count_eat = 0;
		if (snake.death)
			break;

		for (int i = 0; i < 5; i++) {
			fruit[i].create(fruit, snake, i, wall);
			fruit[i].draw();
		}
		snake.initDraw();

		while (!snake.death) {
			readKeyboard(snake, ifBegin);
			bool checkFruitAll = 1;
			for (int i = 0; i < 5; i++) {
				if (fruit[i].exist == true) {
					checkFruitAll = 1;
					break;
				}
				checkFruitAll = 0;
			}
			if (!checkFruitAll) {
				for (int i = 0; i < 5; i++) {
					fruit[i].create(fruit, snake, i, wall);
					fruit[i].draw();
				}
			}
			last_snake = snake;
			snake.move(fruit, 5, game, wall);
			if (((clock() - God_time) / 1000 >= 15) && God_time != 0) {
				chance_of_God = true;
				snake.turn_to_normal();
				set_color(MY_GREEN, MY_GREEN);
				fillpolygon((POINT*)pts2, 4);
				setbkmode(TRANSPARENT);
				settextstyle(30, 15, _T("黑体"));
				drawtext(_T("正常"), &r_condition, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				settextstyle(&style);
				settextcolor(WHITE);
				God_time = 0;
			}
			snake.draw();
			for (int i = 0; i < 4; i++) {
				if (wall[i].ifexist) {
					wall[i].draw();
				}
			}
			if (count_eat == 10 && count_eat != 0 && chance_of_God) {
				set_color(MY_RED, MY_RED);
				fillpolygon((POINT*)pts2, 4);
				setbkmode(TRANSPARENT);
				settextstyle(30, 15, _T("黑体"));
				settextcolor(BLACK);
				drawtext(_T("暴走"), &r_condition, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				settextstyle(&style);
				settextcolor(WHITE);
				snake.turn_to_God();
				chance_of_God = false;
				God_time = clock();
				count_eat = 0;
			}
			if (game.score > record2) {
				record2 = game.score;
				set_color(BLACK, BLACK);
				fillpolygon((POINT*)pts4, 4);
				sprintf(ch_record, "%d", record2);
				outtextxy(900, 442, ch_record);
			}
			Sleep(1000 / snake.speed);
			if (ifBegin) {
				if (init_time == -1) {
					init_time = clock();
				}
				drawTime(init_time);
			}
		}
		game.life--;
		Sleep(500);
		fillpolygon((POINT*)pts3, 4);
		if (game.life) {
			outtextxy(0, 0, "press enter to play...");
			while (ch = _getch()) {
				if (ch == '\r')
					break;
			}
			fillpolygon((POINT*)pts3, 4);
		}
			
		
		for (int i = 0; i < 4; i++) {
			if (!wall[i].ifexist) {
				wall[i].create(last_snake);
				break;
			}
		}
		for (int i = 0; i < 4; i++) {
			if (wall[i].ifexist) {
				wall[i].draw();
			}
		}
		
		
	}
	set_color(BLACK, BLACK);
	fillpolygon((POINT*)pts3, 4);
	IMAGE img_death(640, 480);
	loadimage(&img_death, _T("死亡.jpg"));
	putimage(120, 100, &img_death);
	settextcolor(WHITE);
	outtextxy(0, 0, "press enter to continue...");
	outtextxy(0, 20, "press Q to quit...");
	file.open("record.txt", ios::out);
	file << record << endl;
	file << record2 << endl;
	file << record3 << endl;
	file.close();
	file.open("history.txt", ios::out | ios::app);
	file << "版本：进阶版 用户名：" << username << " 得分：" << game.score << " 驾驶的机体：EVANGELION-0";
	if (type >= 0 && type <= 2)
		file << type << endl;
	else if (type > 2)
		file << type * 2 << endl;
	file.close();
}

void senior_version(int type)
{
	file.open("record.txt", ios::in);
	file >> record;
	file >> record2;
	file >> record3;
	initgraph(width + 200, height);
	file.close();

	IMAGE img(width, height);
	loadimage(&img, _T("EVA蛇来袭.jpg"));
	putimage(80, 50, &img);
	LOGFONT style;
	gettextstyle(&style);
	Wall wall[4];
	int ifBegin = 0;
	int init_time = -1;
	int God_time = 0;
	bool chance_of_God = true;
	int pts1[] = { 840,500,960,500,960,570,840,570 };
	int pts2[] = { 845,505,955,505,955,565,845,565 };
	int pts3[] = { 0,0,800,0,800,600,0,600 };
	int pts4[] = { 900,442,1000,442,1000,460,900,460 };
	count_eat = 0;
	Game game;
	RECT r_score = { 800,0,900,100 };
	RECT r_len = { 810,100,900,200 };
	RECT r_life = { 800,200,900,300 };
	RECT r_time = { 790,300,900,400 };
	RECT r_death = { 0,0,800,600 };
	RECT r_record = { 810,400,900,500 };
	RECT r_condition = { 865,520,935,550 };
	char ch_record[10], ch;

	set_color(WHITE, WHITE);
	line(801, 0, 801, 600);
	drawtext(_T("SCORE:"), &r_score, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("LIFE:"), &r_life, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("LENGTH:"), &r_len, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("TIME:"), &r_time, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("RECORD:"), &r_record, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	set_color(WHITE, WHITE);
	fillpolygon((POINT*)pts1, 4);

	settextstyle(&style);
	outtextxy(900, 42, '0');
	outtextxy(900, 142, '6');
	outtextxy(900, 242, '5');
	outtextxy(900, 342, "00:00:00");
	sprintf(ch_record, "%d", record3);
	outtextxy(900, 442, ch_record);
	Sleep(1500);
	set_color(BLACK, BLACK);
	fillpolygon((POINT*)pts3, 4);

	while (game.life) {
		set_color(MY_GREEN, MY_GREEN);
		fillpolygon((POINT*)pts2, 4);
		setbkmode(TRANSPARENT);
		settextstyle(30, 15, _T("黑体"));
		drawtext(_T("正常"), &r_condition, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		settextstyle(&style);
		settextcolor(WHITE);
		Snake snake(type, wall);
		Snake last_snake = snake;
		Fruit fruit[5];
		count_eat = 0;
		if (snake.death)
			break;

		for (int i = 0; i < 5; i++) {
			fruit[i].create(fruit, snake, i, wall);
			fruit[i].draw();
		}
		snake.initDraw();

		while (!snake.death) {
			readKeyboard(snake, ifBegin);
			bool checkFruitAll = 1;
			for (int i = 0; i < 5; i++) {
				if (fruit[i].exist == true) {
					checkFruitAll = 1;
					break;
				}
				checkFruitAll = 0;
			}
			if (!checkFruitAll) {
				for (int i = 0; i < 5; i++) {
					fruit[i].create(fruit, snake, i, wall);
					fruit[i].draw();
				}
			}
			last_snake = snake;
			snake.move_senior(fruit, 5, game, wall);
			if (((clock() - God_time) / 1000 >= 15) && God_time != 0) {
				chance_of_God = true;
				snake.turn_to_normal();
				set_color(MY_GREEN, MY_GREEN);
				fillpolygon((POINT*)pts2, 4);
				setbkmode(TRANSPARENT);
				settextstyle(30, 15, _T("黑体"));
				drawtext(_T("正常"), &r_condition, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				settextstyle(&style);
				settextcolor(WHITE);
				God_time = 0;
			}
			snake.draw();
			for (int i = 0; i < 4; i++) {
				if (wall[i].ifexist) {
					wall[i].draw_senior();
				}
			}
			if (count_eat == 10 && count_eat != 0 && chance_of_God) {
				set_color(MY_RED, MY_RED);
				fillpolygon((POINT*)pts2, 4);
				setbkmode(TRANSPARENT);
				settextstyle(30, 15, _T("黑体"));
				settextcolor(BLACK);
				drawtext(_T("暴走"), &r_condition, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				settextstyle(&style);
				settextcolor(WHITE);
				snake.turn_to_God();
				chance_of_God = false;
				God_time = clock();
				count_eat = 0;
			}
			if (game.score > record3) {
				record3 = game.score;
				set_color(BLACK, BLACK);
				fillpolygon((POINT*)pts4, 4);
				sprintf(ch_record, "%d", record3);
				outtextxy(900, 442, ch_record);
			}
			Sleep(1000 / snake.speed);
			if (ifBegin) {
				if (init_time == -1) {
					init_time = clock();
				}
				drawTime(init_time);
			}
		}
		game.life--;
		Sleep(500);
		fillpolygon((POINT*)pts3, 4);
		if (game.life) {
			outtextxy(0, 0, "press enter to play...");
			while (ch = _getch()) {
				if (ch == '\r')
					break;
			}
			fillpolygon((POINT*)pts3, 4);
		}

		for (int i = 0; i < 4; i++) {
			if (!wall[i].ifexist) {
				wall[i].create(last_snake);
				break;
			}
		}
		for (int i = 0; i < 4; i++) {
			if (wall[i].ifexist) {
				wall[i].draw_senior();
			}
		}
	}
	set_color(BLACK, BLACK);
	fillpolygon((POINT*)pts3, 4);
	IMAGE img_death(640, 480);
	loadimage(&img_death, _T("死亡.jpg"));
	putimage(120, 100, &img_death);
	settextcolor(WHITE);
	outtextxy(0, 0, "press enter to continue...");
	outtextxy(0, 20, "press Q to quit...");
	file.open("record.txt", ios::out);
	file << record << endl;
	file << record2 << endl;
	file << record3 << endl;
	file.close();
	file.open("history.txt", ios::out | ios::app);
	file << "版本：高级版 用户名：" << username << " 得分：" << game.score << " 驾驶的机体：EVANGELION-0";
	if (type >= 0 && type <= 2)
		file << type << endl;
	else if (type > 2)
		file << type * 2 << endl;
	file.close();
}

void starter_init()
{
	char ch;
	while (true) {
		system("cls");
		COLORREF color1 = 0, color2 = 0;
		int type;
		cout << "Please choose the EVA Snake you will drive: " << endl;
		cout << "0.EVANGELION-00 (blue and white)" << endl;
		cout << "1.EVANGELION-01 (green and purple)" << endl;
		cout << "2.EVANGELION-02 (red and orange)" << endl;
		cout << "3.EVANGELION-06 (dark bule and yellow)" << endl;
		cout << "4.EVANGELION-08 (pink and white)" << endl;
		while (type = _getch() - '0') {
			if (type >= 0 && type <= 4) {
				break;
			}
		}
		cout << endl;
		cout << "please enter your username(no more than 20 characters):";
		cin >> username;
		starter_mode(type);
		while (true) {
			ch = _getch();
			if (ch == '\r' || ch == 'q' || ch == 'Q')
				break;
		}
		closegraph();
		if (ch == 'q' || ch == 'Q')
			break;
	}
}

void advanced_init()
{
	char ch;
	while (true) {
		system("cls");
		COLORREF color1 = 0, color2 = 0;
		int type;
		cout << "Please choose the EVA Snake you will drive: " << endl;
		cout << "0.EVANGELION-00 (blue and white)" << endl;
		cout << "1.EVANGELION-01 (green and purple)" << endl;
		cout << "2.EVANGELION-02 (red and orange)" << endl;
		cout << "3.EVANGELION-06 (dark bule and yellow)" << endl;
		cout << "4.EVANGELION-08 (pink and white)" << endl;
		while (type = _getch() - '0') {
			if (type >= 0 && type <= 4) {
				break;
			}
		}
		cout << endl;
		cout << "please enter your username(no more than 20 characters):";
		cin >> username;
		advanced_version(type);
		while (true) {
			ch = _getch();
			if (ch == '\r' || ch == 'q' || ch == 'Q')
				break;
		}
		closegraph();
		if (ch == 'q' || ch == 'Q')
			break;
	}
}

void senior_init()
{
	char ch;
	while (true) {
		system("cls");
		COLORREF color1 = 0, color2 = 0;
		int type;
		cout << "Please choose the EVA Snake you will drive: " << endl;
		cout << "0.EVANGELION-00 (blue and white)" << endl;
		cout << "1.EVANGELION-01 (green and purple)" << endl;
		cout << "2.EVANGELION-02 (red and orange)" << endl;
		cout << "3.EVANGELION-06 (dark bule and yellow)" << endl;
		cout << "4.EVANGELION-08 (pink and white)" << endl;
		while (type = _getch() - '0') {
			if (type >= 0 && type <= 4) {
				break;
			}
		}
		cout << endl;
		cout << "please enter your username(no more than 20 characters):";
		cin >> username;
		senior_version(type);
		while (true) {
			ch = _getch();
			if (ch == '\r' || ch == 'q' || ch == 'Q')
				break;
		}
		closegraph();
		if (ch == 'q' || ch == 'Q')
			break;
	}
}

void readHistory()
{
	system("cls");
	char ch;
	file.open("history.txt", ios::in);
	while (!file.eof()) {
		ch = file.get();
		putchar(ch);
	}
	cout << "\n按enter退出" << endl;
	while (true) {
		ch = _getch();
		if (ch == '\r')
			break;
	}
}

int main()
{
	srand((unsigned int)(time(0)));
	bool flag = true;
    
	while (flag) {
		int mode;
		mode = menu();
		switch (mode)
		{
			case 1:
				starter_init();
				break;
			case 2:
				advanced_init();
				break;
			case 3:
				senior_init();
				break;
			case 4:
				readHistory();
				break;
			case 5:
				flag = false;
				break;
			default:
				break;
		}
	}
	system("cls");
	return 0;
}