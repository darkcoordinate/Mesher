#include<stdio.h>
#include<stdlib.h>

typedef struct point point;
typedef struct point2 point2;
typedef struct equator equator;
typedef int bool;

#define TRUE 		1
#define FALSE 		0

#define SENTENCE 	3
#define WORD 		4

struct equator
{
	int actual;
	int secret;
	equator* next;
	equator* prev;
};

struct point
{
//
	int a;
	int indx;
	point* next;
	point* prev;
};

struct point2 
{
//to make a generic struct so that you can 
//make linked list of any kind just by converting 
//that pointer to type void* and then referencing it to
//point 
	void* a;
	point2* next;
	point2* prev;
};


void addequator(equator* eq_list, int actual, int secret)
{
	equator* eq_pk;
	eq_pk = eq_list;
	equator* eq_p2;
	eq_p2 = (equator*)malloc(sizeof(equator));
	eq_p2->next = NULL;
	eq_p2->prev = NULL;
	eq_p2->actual = actual;
	eq_p2->secret = secret;
	while(eq_pk->next != NULL)
	{
		eq_pk = eq_pk->next;
	}
	eq_pk->next = eq_p2;
	eq_p2->prev = eq_pk;
	eq_pk = NULL;
	eq_p2 = NULL;
}


void addpoint2(point2* list, void* a)
{
//add data to the point2 linkedlist
	point2* p1;
	point2* p2;
	p1 = list;
	p2 = (point2*)malloc(sizeof(point));
	p2->a = a;
	p2->next = NULL;
	p2->prev = NULL;
	while(p1->next != NULL)
	{
		p1 = p1->next;
	}
	p1->next = p2;
	p2->prev = p1;
	p1 = NULL;
	p2 = NULL;
}

point* create_point( int a)
{
	point* poi;
	poi = (point*)malloc(sizeof(point*));
	poi->indx = 0;
	poi->a = a;
	poi->next = NULL;
	poi->prev = NULL;
	return poi;
}


void addpoint( point* list, int a)
{
	point* p1;
	point* p2;
	p1 = list;
	p2 = (point*)malloc(sizeof(point));
	p2->a = a;
	p2->next = NULL;
	p2->prev = NULL;
	while ( p1->next != NULL)
	{
		p1 = p1->next;
	}
	p1->next = p2;
	p2->indx = p1->indx + 1;
	p2->prev = p1;
	p1 = NULL;
	p2 = NULL;
}

void addpoint_to_point2(point2* list, point* list_point)
{
	list->a = (void*)list_point;
}

void makechar_word(point* list,int size, char* cha)
{
	//this function makes the linked list of the char string in the 
	list->a = (int)cha[0];
	list->next = NULL;
	list->prev = NULL;
	list->indx = 0;
	point* p1;
	p1 = list;
	int i;
	for(i = 1; i < size; i++)
	{
		while(p1->next != NULL)
		{
			p1 = p1->next;
		}
		point* p2 = (point*)malloc(sizeof(point));
		p2->a = (int)cha[i];
		p2->prev = p1;
		p2->next = NULL;
		p1->next = p2;
		p2 = NULL;
	}
	p1 = NULL;
}

	
void listtree(point* list, int a)
{
	point* p1;
	p1 = list;
	printf("*--------------------------------*\n");
	printf("--list\n");
	while(p1 != NULL)
	{
		printf("	|-----------%p\n",p1);
		printf("	|	|-- a = %d :- %c\n",p1->a, p1->a);
		printf("	|   	|-- indx = %d\n", p1->indx);
		if(a == 1)
		{
			if(p1->next == NULL)
			{
				printf("	|	|-- next = NULL\n");
			}
			else
			{
				printf("	|	|-- next = %p\n",(p1->next));
			}
			if(p1->prev == NULL)
			{
				printf("	|	|-- next = NULL\n");
			}
			else
			{
				printf("	|	|-- prev = %p\n",(p1->prev));
			}
		}
		p1 = p1->next;
	}
		
}


void printcontent(point* list)
{
	point* p1 = list;
	while(p1 != NULL)
	{
		printf("%c",p1->a);
		p1 = p1->next;
	}
}


void make_info(point* list, point2* list2, int para_element)
{
	point* p1 = list;
	point* p2 = create_point(0);
	while(p1 != NULL)
	{
		if(para_element == SENTENCE)
		{
			if(p1->a == 10)
			{
				void* n = (void*)p2;
				if(list2->a == NULL)
				{
					list2->a = n;
				}
				else
				{
					addpoint2(list2,n);
				}
				p2 = NULL;
				free(p2);
				p2 = create_point(0);
			}
			else
			{	
				if(p2->a == 0)
				{
					p2->a = p1->a;
				}
				else
				{
					addpoint(p2,p1->a);
				}
			}
			p1 = p1->next;
		}
		else if(para_element == WORD)
		{
			if((p1->a == 32)||(p1->a == 10))
			{
				void* n = (void*)p2;
				if(list2->a == NULL)
				{
					list2->a = n;
				}
				else
				{
					addpoint2(list2,n);
				}
				p2 = NULL;
				free(p2);
				p2 = create_point(0);
			}
			else
			{	
				if(p2->a == 0)
				{
					p2->a = p1->a;
				}
				else
				{
					addpoint(p2,p1->a);
				}
			}
			p1 = p1->next;
		}
	}
	void* n = (void*)p2;
	if(list2->a == NULL)
	{
		list2->a = n;
	}
	else
	{
		addpoint2(list2,n);
	}
	p2 = NULL;
	free(p2);	
}


bool match_word(point* list1, point* list2)
{
	bool t = TRUE;
	point* p1 = list1;
	point* p2 = list2;
	while(p1 != NULL)
	{
		if(p1->a == p2->a)
		{
		}
		else
		{
			t = FALSE;
			break;
		}
		if((p1->next != NULL) && (p2->next != NULL))
		{
			p1 = p1->next;
			p2 = p2->next;
		}
		else if((p1->next == NULL) && (p2->next == NULL))
		{
			p1 = p1->next;
			p2 = p2->next;
		}
		else
		{
			t = FALSE;
			break;
		}
	}
	return 	t;
}

void printequator(equator* eq_list)
{
	equator* eq = eq_list;
	while(eq != NULL)
	{
		printf("%c",eq->secret);
		eq = eq->next;
	}
	eq = eq_list;
	printf(" ");
	while(eq != NULL)
	{
		printf("%c",eq->actual);
		eq = eq->next;
	}
	printf("\n");
}


void print_words(point2* list)
{
	point2* p1 = list;
	point* p2;
	while(p1 != NULL)
	{
		p2 = (point*)(p1->a);
		printf("Word at %p\n------------------------\n",p1);
		listtree(p2, 2);
		p1 = p1->next;
	}
}


void run_intelengence(point2* list2)
{
	//if any one understand this plese let me know
	point2* p1;
	point* dict = (point*)malloc(sizeof(point));
	point* secret = (point*)malloc(sizeof(point));
	char* sec = "//secret";
	char* dic = "//dict";
	makechar_word(secret,8,sec);
	makechar_word(dict,6,dic);
	p1 = list2;
	point2* groupdict;
	point2* groupsecret;
	groupdict = (point2*)malloc(sizeof(point2*));
	groupdict->a = NULL;
	groupdict->next = NULL;
	groupdict->prev = NULL;
	groupsecret = (point2*)malloc(sizeof(point2*));
	groupsecret->a = NULL;
	groupsecret->prev = NULL;//
	groupsecret->next = NULL;
	int ldk = 1;
	while(p1 != NULL)
	{
		//printf("8\n");
		point* p2;
		p2 = (point*)(p1->a);
		if(match_word(dict, p2))
		{
			ldk = 2;	
		}
		if(match_word(secret,p2))
		{
			ldk = 3;
		}
		if(ldk == 2)
		{
			if(groupdict->a == NULL)
			{
				groupdict->a = p1->a;
			}
			else
			{
				addpoint2(groupdict, p1->a);
			}
		}
		p1 = p1->next;
	}
	p1 = list2;
	while(p1 != NULL)
	{
		point* p2;
		p2 = (point*)(p1->a);
		if(match_word(dict, p2))
		{
			ldk = 2;
		}
		if(match_word(secret,p2))
		{
			ldk = 3;
		}
		if(ldk == 3)
		{
			if(groupsecret->a == NULL)
			{
				groupsecret->a = p1->a;
			}
			else
			{
				addpoint2(groupsecret, p1->a);
			}
		}
		
		//printcontent((point*)p1->a);
		//printf("\n");
		p1 = p1->next;
	}
	p1 = list2;
	point2* psecret;
	psecret = groupsecret;
	//print_words(groupsecret);
	//print_words(groupdict);
	while(psecret != NULL)
	{
		equator* e_secret;
		
		equator* e_dict;
		point* p2;
		p2 = (point*)(psecret->a);
		point2* pse = (point2*)malloc(sizeof(point2));
		make_info(p2,pse,WORD);
		point2* dpse = pse;
		bool imesg = TRUE;
		while(dpse != NULL)
		{

			point* pmessage;
			pmessage = (point*)(dpse->a);
			point2* s_dict;
			s_dict = groupdict;
			while(s_dict != NULL)
			{
				e_secret = NULL;
				e_secret = (equator*)malloc(sizeof(equator));
				e_secret->next = NULL;
				e_secret->prev = NULL;
				e_secret->actual = 0;
				e_secret->secret = 0;
				point* p_dict;
				p_dict = (point*)(s_dict->a);
				point* k_dict = p_dict;
				point* k_message = pmessage;
				while((k_message != NULL) && (k_dict != NULL))
				{
					equator* eq = (equator*)malloc(sizeof(equator));
					eq->next = NULL;
					eq->prev = NULL;
					eq->actual = 0;
					eq->secret = 0;
					if(e_secret->actual == 0)
					{
						e_secret->actual = k_dict->a;
						e_secret->secret = k_message->a;
					}
					else
					{
						addequator(e_secret,k_dict->a,k_message->a);
					}
					eq->next = e_secret;
					while(eq->next->next != NULL)
					{
						eq->next = eq->next->next;
					}
					eq->prev = eq->next->prev;
					while(eq->prev != NULL)
					{
						if(eq->next->actual == eq->prev->actual)
						{
							if(eq->next->secret == eq->prev->secret)
							{

							}
							else
							{
								imes = FALSE;
							}
						}

						if(eq->next->secret == eq->prev->secret)
						{
							if(eq->next->actual == eq->prev->actual)
							{

							}
							else
							{
								break;
							}
						}
						eq->prev = eq->prev->prev;
					}
					k_message = k_message->next;
					k_dict = k_dict->next;
				}
				s_dict = s_dict->next;
			}
			dpse = dpse->next;
			addequator(e_secret,32,32);
		}
		printequator(e_secret);
		printf("\n");
		psecret = psecret->next;
	}			
}


int main(int argv, char** argc)
{
	FILE *fs;
	fs = fopen("/home/analyst/Documents/input000.txt","r");
	point* list;
	list = (point*)malloc(sizeof(point*));
	list->a = 0;
	list->indx = 0;
	list->next = NULL;
	list->prev = NULL;
	int i= 0;
	while( (i = getc(fs)) != EOF)
	{
		if( list->a == 0)
		{
			list->a = i;
		}
		else
		{
			addpoint(list, i);
		}
	}
	//printf("%d",**argc);
	//listtree(list, **argc);
	//printcontent(list);
	printf("j");
	point2* group = (point2*)malloc(sizeof(point2));
	group->a = NULL;
	group->next = NULL;
	group->prev = NULL;
	make_info(list, group,SENTENCE);
	run_intelengence(group);

	return 0;
}
