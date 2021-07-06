#include <iostream>
#include <fstream>
#include <string>

struct Image {
  int mx;
  int my;
  int* points;  //картинка размером mx * my
};

using namespace std;

// Создание изображения
void createImage(Image* img,int tmx, int tmy) {
  // Выделить память  размером tmx * tmy
	img->mx = tmx;
	img->my = tmy;
	img->points = new int[tmx * tmy]{ 0 };

}


// Отображения изображения на экран в pnm формате
//  0 0 0 0 1 0
//  0 0 0 0 1 0
//  0 0 0 0 1 0
//  0 0 0 0 1 0
//  0 0 0 0 1 0
//  0 0 0 0 1 0
//  1 0 0 0 1 0
//  0 1 1 1 0 0
//  0 0 0 0 0 0
//  0 0 0 0 0 0


void showImage(Image* img) {
  // Вывести картинку на экран при помощи cout или 
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


// Изменения точки на изображения
//  Необходимо изменить в массиве points - точку с координатами mx*y+x в цвето color
//  0 0 0 0 1 0  0 0 0 0 1 0  0 0 0 0 1 0  0 0 0 0 1 0  0 0 0 0 1 0  0 0 0 0 1 0  1 0 0 0 1 0  0 1 1 1 0 0  0 0 0 0 0 0  0 0 0 0 0 0
   

void setPointImage(Image* img,int x, int y,int color) {
	if ((y * img->mx + x) > img->mx * img->my)
	{
		return;
	}
	img->points[(y * img->mx + x)] = color;
}


// Получение точки на изображение
int getPointImage(Image* img,int x, int y) {
	int n;
	n = y * img->mx + x;
	int color = img->points[n];
	return color;
}


// Отображения изображения на экран в pnm формате - P1
// https://en.wikipedia.org/wiki/Netpbm#File_formats
//
//  P1
//  6 10
//  0 0 0 0 1 0
//  0 0 0 0 1 0
//  0 0 0 0 1 0
//  0 0 0 0 1 0
//  0 0 0 0 1 0
//  0 0 0 0 1 0
//  1 0 0 0 1 0
//  0 1 1 1 0 0
//  0 0 0 0 0 0
//  0 0 0 0 0 0
//  Файл можно открыть в gimp

void saveToPnmFile(Image* img, string fileName) {

	fstream out;
	out.open(fstream::out,fileName);
	out << "P1"<< endl;
	out << img->mx << " " << img->my << endl;
	for (int i=0; i<img->my;i++)
	{
		for (int j=0; j<img->mx;j++)
		{
			out << img->points[i * img->mx + j]<<" ";
		}
		out<<endl;
	}
	out.close();
}

int testCreateImage();
{
	Image *img = new Image;
	tmx = 10;
	tmy = 10;
	createImage(img, tmx, tmy);
	if (img->mx == 10 && img->my == 10) return 0;
	return -1;
}
int testGetImage()
{
	Image* img = new Image;
	tmx = 10;
	tmy = 10;
	createImage(img, tmx, tmy);
	img->points[1] = 1;
	if (getPointImage(img, 1, 0) == 1 && getPointImage(im, 1, 2) == 0)
	{
		return 0;
	}
	return -1;

}

int testSetImage();
{
	Image* img = new Image;
	tmx = 10;
	tmy = 10;
	createImage(img, tmx, tmy);
	setPointImage(img,1,0,1);
	if (getPointImage(img, 1, 0) == 1)
	{
		return 0;
	}
	return -1;
}

void runTest(testFunction(), const string testName)
{
	if (testFunction() == 0)
	{
		cout << testName << " Test is OK" <<endl;
	}
	else
	{
		cout << testName << " Test if FAIL"<<endl;
	}
}

int main() {
	runTest(testCreateImage(), "testCreateImage");
	runTest(testGetImage(), "testCreateImage");
	runTest(testSetImage(), "testCreateImage");
	Image* img_out = new Image;
	createImage(img_out, 3, 3);
	setPointImage(img_out, 0, 0, 1);
	setPointImage(img_out, 1, 1, 1);
	setPointImage(img_out, 2, 2, 1);
	showImage(img_out);
	saveToPnmFile(img, "imgutils.pnm");
	return 0;
}
