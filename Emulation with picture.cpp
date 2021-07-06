#include <iostream>
#include <cmath>
#include <conio.h>
#include <fstream>
#include <string>

float const gravity = -9.8f;
float const deltaTime = 0.1f;

using namespace std;

struct Image
{
	int mx;
	int my;
	int* points;
};

void createImage(Image* img, int tmx, int tmy)
{
	// Âûäåëèòü ïàìÿòü  ðàçìåðîì tmx * tmy
	img->mx = tmx;
	img->my = tmy;
	img->points = new int[tmx * tmy]{ 0 };
}

void showImage(Image* img)
{
	// Âûâåñòè êàðòèíêó íà ýêðàí ïðè ïîìîùè cout èëè 
	using namespace std;
	for (int i = 0; i < img->my; i++)
	{
		for (int j = 0; j < img->mx; j++)
		{
			cout << img->points[i * img->mx + j] << " ";
		}
		cout << endl;
	}
}

void setPointImage(Image* img, int x, int y, int color)
{
	if ((y * img->mx + x) > img->mx * img->my)
	{
		return;
	}
	img->points[(y * img->mx + x)] = color;
}

int getPointImage(Image* img, int x, int y) {
	int n;
	n = y * img->mx + x;
	int color = img->points[n];
	return color;
}

void saveToPnmFile(Image* img, string fileName) {

	fstream out;
	out.open(fileName, fstream::out);
	out << "P1" << endl;
	out << img->mx << " " << img->my << endl;
	for (int i = 0; i < img->my; i++)
	{
		for (int j = 0; j < img->mx; j++)
		{
			out << img->points[i * img->mx + j] << " ";
		}
		out << endl;
	}
	out.close();
}

struct Node
{
	float time;
	float h;
	float v;
	float const a = gravity;
	Node* next;
};

void init(Node* node, float high)
{
	node->time = 0;
	node->h = high;
	node->v = 0;
	node->next = NULL;
}
void show(Node* head)
{
	Node* print = head;
	while (print != NULL)
	{
		cout << "{" << print->time << "; " << print->h << "; " << print->v << "; " << print->a << "}" << endl;
		print = print->next;
	}
	cout << endl;
}

void pushParameters(Node* head)
{
	Node* moment = head;
	while (moment->next != NULL) moment = moment->next;
	moment->next = new Node;
	moment->next->time = moment->time + deltaTime;
	moment->next->h = moment->h + (moment->v * deltaTime) + (gravity * deltaTime * deltaTime / 2);
	moment->next->v = moment->v + gravity * deltaTime;
	moment->next->next = NULL;
}

float collision(Node* head, float high, float lossPercent, float timeOfCollision)
{
	Node* end = head;
	while (end->next != NULL)
	{
		end = end->next;
	}
	end->time = timeOfCollision;
	end->h = 0;
	end->v = sqrt(2 * (-gravity) * high) * sqrt((100 - lossPercent) / 100);
	return end->v;
}

int testEmulation()
{
	Node* head = new Node;
	float high = 100.0f;
	float saveHigh = high;
	float lossPercent = 70;
	float timeOfCollision = sqrt(2.0 * high / (-gravity));
	cout << timeOfCollision << endl;
	init(head, high);
	float time = 0;
	while (high > 0.001)
	{
		while (time < timeOfCollision - deltaTime)
		{
			pushParameters(head);
			time += deltaTime;
		}
		float v = collision(head, high, lossPercent, timeOfCollision);
		time = timeOfCollision;
		float t = v / (-gravity);
		high = v * t + gravity * t * t / 2;
		timeOfCollision += 2 * t;
	}
	show(head);
	Node* end = head;
	while (end->next != NULL)
	{
		if (end->h < 0)
		{
			cout << "Ball in earth";
			return -1;
		}
		end = end->next;
	}
	float timeOfEmulation = end->time;
	Image* img = new Image;
	createImage(img, int(timeOfEmulation) * 50, int(saveHigh)*5);
	end = head;
	while (end != NULL)
	{
		setPointImage(img, int(50*end->time), int(head->h - end->h)*5, 1);
		end = end->next;
	}
//	showImage(img);
	saveToPnmFile(img,"EmulationImage.pnm");
	return 0;
}

int main()
{
	testEmulation();
	if (testEmulation() == 0)
	{
		cout << "Test is OK";
	}
	else cout << "Test is Fail";
}
