#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct{
	float x,y,z;
}vec3;

typedef struct{
	float x,y;
}vec2;

float length3(vec3 s)
{
	return sqrt(s.x*s.x + s.y+s.y + s.z+s.z);
}

float length2(vec2 s)
{
	return sqrt(s.x*s.x + s.y*s.y)
}
float sphere(vec3 p, float radius)
{
	return length3(p) - radius;
}

vec3 con_vec3(float a, float b, float c)
{
	vec3 ret;
	ret.x = a;
	ret.y = b;
	ret.z = c;
	return ret;
}

vec3 con_vec2(float a, float b)
{
	vec2 ret;
	ret.x = a;
	ret.y = b;
	return ret;
}

vec3 productf3(float a, vec3 s)
{
	return con_vec3(s.x*a,s.y*a, s.z*a);
}

vec3 product3x3(vec3 a, vec3 b)
{
	return con_vec3(a.x*b.x, a.y*b.y, a.z*b.z);
}

vec2 productf2(float a, vec2 s)
{
	return con_vec2(a*s.x, a*s.y);
}

vec2 product2x2(vec2 a, vec2 b)
{
	return con_vec2(a.x*b.x, a.y*b.y);
}

vec3 sumf3(float a, vec3 s)
{
	return con_vec2(a+s.x,a+s.y, a+s.z);
}

vec3 sum3x3(vec3 a, vec3 b)
{
	return con_vec2(a.x+b.x , a.y+b.y, a.z+b.z);
}
 	
float map(vec3 p)
{
	return sphere(p,3.0);
}
