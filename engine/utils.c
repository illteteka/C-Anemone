#include "../include.h"

int CheckCollision(float x1,float y1,float w1,float h1, float x2,float y2,float w2,float h2)
{
	return (x1 < x2+w2 && x2 < x1+w1 && y1 < y2+h2 && y2 < y1+h1);
}

int getSquare(int n)
{
	int p = 1;
	while (p < n)
	{
		p *= 2;
	}
	return p;
}

void reverseString(char* str)
{
	int length = strlen(str);
	int i, j;
	for (i = 0, j = length - 1; i < j; i++, j--)
	{
		char temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
}

float lengthdir_x(float length, float dir)
{
	return length * cos(dir);
}

float lengthdir_y(float length, float dir)
{
	return -length * sin(dir);
}

float point_direction(float x1, float y1, float x2, float y2)
{
	return atan2(y2 - y1, x2 - x1);
}

int sign(int x)
{
	return (x < 0) ? -1 : 1;
}

float clamp(float x, float min, float max)
{
	if (x < min)
		return min;
	else if (x > max)
		return max;
	else
		return x;
}

float lerp(float a, float b, float amount)
{
	return a + (b - a) * clamp(amount, 0, 1);
}

void hsl(int h, int s, int l)
{
	if (s <= 0)
	{
		gfxSetColor(255, 255, 255);
		return;
	}

	float H = h / 256.0f * 6.0f;
	float S = s / 255.0f;
	float L = l / 255.0f;

	float C = (1 - fabsf(2 * L - 1)) * S;
	float X = C * (1 - fabsf(fmodf(H, 2) - 1));
	float m = L - C / 2.0f;

	float r, g, b;

	switch ((int)H) {
		case 0:
			r = C;
			g = X;
			b = 0;
			break;
		case 1:
			r = X;
			g = C;
			b = 0;
			break;
		case 2:
			r = 0;
			g = C;
			b = X;
			break;
		case 3:
			r = 0;
			g = X;
			b = C;
			break;
		case 4:
			r = X;
			g = 0;
			b = C;
			break;
		default:
			r = C;
			g = 0;
			b = X;
			break;
	}

	gfxSetColor((int)((r + m) * 255), (int)((g + m) * 255), (int)((b + m) * 255));
}