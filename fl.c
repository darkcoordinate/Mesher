#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef int bool;
#define true 1
#define false 0

struct point
{
	int pos_x; int pos_y; int pos_z;
};


struct vector
{
	double vec_x;
	double vec_y;
	double vec_z;
};

struct object
{
	struct vector object_point;
	struct vector velocity;
	struct vector accleration;
}object_point,velocity,accleration;

typedef struct object pl_object;
typedef struct vector pl_vector;


void vec_normalize(pl_vector *vec)    //mormalizing the vector 
{
	double vector_magnitude = sqrt(vec->vec_x * vec->vec_x + vec->vec_y * vec->vec_y + vec->vec_z * vec->vec_z);
	vec->vec_x = vec->vec_x / vector_magnitude;
	vec->vec_y = vec->vec_y / vector_magnitude;
	vec->vec_z = vec->vec_z / vector_magnitude;
}

double calculate_distance(pl_vector * pos1, pl_vector* pos2, bool i)
{
//calculate distance between two vector points
	
	double ret = sqrt( (pos1->vec_x - pos2->vec_x)*(pos1->vec_x - pos2->vec_x) + (pos1->vec_y - pos2->vec_y)*(pos1->vec_y = pos2->vec_y) + (pos1->vec_z - pos2->vec_z)*(pos1->vec_z - pos2->vec_z));
	if(i)
	{
		printf("\n distance between point %f",ret);
	}
	return ret;
}

double ob_calculate_distance(pl_object *ob1, pl_object* ob2, bool flag)
{
	return calculate_distance(&(ob1->object_point), &(ob2->object_point), flag);
}
	

void calculate_point(pl_vector * object, pl_vector* velocity, pl_vector* accleration,bool debug)
{ //calculating the velocity of the body
	velocity->vec_x = velocity->vec_x + accleration->vec_x;
	velocity->vec_y = velocity->vec_y + accleration->vec_y;
	velocity->vec_z = velocity->vec_z + accleration->vec_z;
//calculating the position of the body
	object->vec_x += velocity->vec_x;
	object->vec_y += velocity->vec_y;
	object->vec_z += velocity->vec_z;

//to print on the terminal when debuging is on
	if(debug)
	{
	printf("\n%f %f %f |%f %f %f",object->vec_x, object->vec_y, object->vec_z, velocity->vec_x, velocity->vec_y, velocity->vec_z);
	}
}

void ob_calculate_point(pl_object * inst_object, bool flag)
{
//for the object
	calculate_point(&(inst_object->object_point), &(inst_object->velocity), &(inst_object->accleration),flag);
}	

 

int main()
{
	int time_of_simul = 100;    //time of simulation is set to 100
	pl_object* object1 = (pl_object*)malloc(sizeof(pl_object*));
	pl_object* object2 = (pl_object*)malloc(sizeof(pl_object*));
	
//defining the vector
	object1->object_point.vec_x = 0;
	object1->object_point.vec_y = 0;
	object1->object_point.vec_z = 0;

	object1->accleration.vec_x = 3;
	object1->accleration.vec_y = 2;
	object1->accleration.vec_z = 1;

	object1->velocity.vec_x = 0;
	object1->velocity.vec_y = 0;
	object1->velocity.vec_z = 0;
	int i;
	printf("Position           velocity\n");
	printf("---------------------------\n");
	for(i = 0; i < time_of_simul ; i++)
	{
		ob_calculate_point(object1, false);
		ob_calculate_point(object2, false);
		ob_calculate_distance(object1, object2, true);		
	}
	return 0;
}
