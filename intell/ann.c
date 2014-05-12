#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int bool;
typedef struct weigth weigth;

struct weigth
{
	int num_of_node;
	float* item;
}num_of_node,item;


#define TRUE 	1
#define FALSE 	0
void make_training_record(float* weigth, int num_of_node, char* file)
{
	FILE *fl;
	fl = fopen(file,"w");
	fprintf(fl, "%d\n",num_of_node);
	int i;
	for(i = 0; i < num_of_node; i++)
	{
		fprintf(fl,"%f ",weigth[i]);
	}
	fclose(fl);
}

weigth* load_training(char* file)
{
	FILE *fl;
	fl = fopen(file,"rb");
	int s;
	fscanf(fl,"%d",&s);
	int i;
	weigth* wei;
	wei = (weigth*)malloc(sizeof(weigth));
	wei->item = (float*)malloc(sizeof(float*));
	for(i = 0; i < s; i++)
	{
		fscanf(fl,"%f",&(wei->item[i]));
	}
	wei->num_of_node = s;	
	return wei;
}		

int main()
{
	int dec;
	printf("if you are");
	scanf("%d",&dec);
	int **train;
	if(dec == 1)
	{
		//traning mode
		int num_of_node;
		printf("Enter number of input: ");
		scanf("%d",&num_of_node);
		float mat_for_ai[num_of_node][num_of_node];
		float mat_solu[num_of_node];
		printf("So you have enterer the number %d \nSo you have to train it for %d times\n",num_of_node, num_of_node*num_of_node);
		printf("\n Write one set of input that contains %d elements, into one line and the repeat this for %d times:\n",num_of_node,num_of_node);
		int i;
		for(i = 0; i < num_of_node; i++)
		{
			int j;
			for(j = 0; j < num_of_node; j++)
			{
				scanf("%f",&mat_for_ai[i][j]);
			}
		}
		printf("\nNow enter the for corresponding set of value: \n");
		for(i = 0; i < num_of_node; i++)
		{
			scanf("%f",&mat_solu[i]);
		}

		//checking the digonal dominance condition
		float weigth[num_of_node];
		float weigth_inst[num_of_node];
		int n;
		float inst_sol[num_of_node];
		for(n = 0; n < num_of_node; n++)
		{
			inst_sol[n] = 1;
		}
		float sol_check[3][num_of_node];
		int flip = 0;
		for(n = 0; n < 100; n++)
		{
			int j;
			
			for(j = 0; j < num_of_node; j++)
			{
				float inst = 0;
				int ji;
				for(ji = 0; ji < num_of_node; ji++)
				{
					if(ji != j)
					{
						inst = inst + inst_sol[ji] * mat_for_ai[j][ji];
					}
				}
				inst_sol[j] = (mat_solu[j] -inst)/mat_for_ai[j][j];
				printf("inst_solu[%d] after %d iteration is - %f\n",j,n,inst_sol[j]);
			}
			if(n == 50)
			{
				for(j = 0; j < num_of_node; j++)
				{
					sol_check[0][j] = inst_sol[j];
				}
			}
			if(n == 51)
			{
				for(j = 0; j < num_of_node; j++)
				{
					sol_check[1][j] = inst_sol[j];
				} 
			}
			if(n == 52)
			{
				float sol_check_d[2][num_of_node];
				int sol_i;
				for(j = 0; j < num_of_node; j++)
				{
					sol_check[2][j] = inst_sol[j];
				}
				
				for(sol_i = 0; sol_i < 2; sol_i++)
				{
					int sol_j;
					for(sol_j = 0; sol_j < num_of_node; sol_j++)
					{
						sol_check_d[sol_i][sol_j] = sol_check[sol_i][sol_j] - sol_check[sol_i + 1][sol_j];
						printf("\n\tafter 52 terms the values of sol_check_d[%d][%d] is : %f\n",sol_i, sol_j, fabs(sol_check_d[sol_i][sol_j]));
					}
					
					
				}
				for(sol_i = 0; sol_i < num_of_node; sol_i++)
				{
					if( (fabs(sol_check_d[0][sol_i]) < fabs(sol_check_d[1][sol_i])))
					{
						if(flip > num_of_node + 1)
						{
							printf("this set of input may not be solved try some other set of solution ");
							return 0;
						}
						//filp algo
						
						float inst[num_of_node];
						float inst_s = mat_solu[0];
						int k;
						for(k = 0; k < num_of_node; k++)
						{
							inst[k] = mat_for_ai[0][k];
						}
						for(k = 0; k < num_of_node -1; k++)
						{
							int m;
							for(m = 0; m < num_of_node; m++)
							{
								mat_for_ai[k][m] = mat_for_ai[k+1][m];
							}
							mat_solu[k] = mat_solu[k+1];
						}
						for(k = 0; k < num_of_node; k++)
						{
							mat_for_ai[num_of_node - 1][k] = inst[k];
						}
						mat_solu[num_of_node - 1] = inst_s;
						n = 0;
						for(k = 0; k < num_of_node; k++)
						{
							inst_sol[k] = 1;
						}
						flip += 1;
						break;
					}
				}
			}
			if(n == 99)
			{
				int m;
				for(m = 0; m < num_of_node; m++);
				{
					mat_solu[m] = inst_sol[m];
				}
			}	
		}
		
		printf("\n the solution is\n");
		for(i = 0; i < num_of_node; i++)
		{
			printf("%f ",inst_sol[i]);
		}
		make_training_record(inst_sol,num_of_node,"/home/analyst/Documents/jjjj/Mesher/intell/an");
	}
	else
	{
		printf("You are in use mode of the ai \n Enter the file name of file for training to be loaded :\n$ ");
		char* file;
		file = (char*)malloc(sizeof(char));
		scanf("%s",file);
		//printf("%s\n",file);
		weigth* weis;
		weis = load_training(file);
		printf("Now you have to enter input set.\n Your input set should consist of %d items.\n Enter the number of input set you are going to enter:\n",weis->num_of_node);
		int num_input_set;
		scanf("%d",&num_input_set);
		printf("You have to enter %d number of data.\n Enter you input: \n",weis->num_of_node * num_input_set);
		int i;
		float input_set[num_input_set][weis->num_of_node];
		for(i = 0; i < num_input_set; i++)
		{
			int j;
			for(j = 0; j < weis->num_of_node; j++)
			{
				scanf("%f",&input_set[i][j]);
			}
		}
		float output_set[num_input_set];
		for(i = 0; i < num_input_set; i++)
		{
			float inst_out = 0;
			int j;
			for(j = 0; j < weis->num_of_node; j++)
			{
				inst_out += input_set[i][j] * weis->item[j];
			}
			output_set[i] = inst_out;
		}
		for(i = 0; i < num_input_set; i++)
		{
			printf("output[%d] is %f \n",i,output_set[i]);
		}
	}		
	return 0;
}


int main()
{
	//perceptron learning algorithm
	int num_of_node;
	printf("Enter number of node:\n");
	scanf("%d",&num_of_node);
	bool input_set[num_of_node];
	printf("You have to enter %d binary numbers ;\n");
	int i;
	for(i = 0; i < num_of_node)
	
	

