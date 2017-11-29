#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int main(int argc, char** argv)
{
	if(argc != 3)
		printf("Error: incorrect number of parameters\n");
	else
	{
		int n = atoi(argv[1]),m = atoi(argv[2]),k,i,j,l,toss;
		float a;
		FILE *fout = fopen("floatdata.dat","w");

		for(k = n; k <= m; k++)
		{	
			long long int num = pow(2,k);
			float array[num];
		
			time_t t;
			srand((unsigned) time(&t));

			clock_t start,stop;

			start = clock();

			for(i=0; i<num; i++)
				array[i] = rand() + (rand()%10000)/10000.0;

			for(i=0; i<10000; i++)
			{
				toss = rand()%2;

				if(toss)
				{
					a = rand() + (rand()%10000)/10000.0;
					for(l=0; l<num; l++)
					if(array[l] == a)
					break;
				}
				else
				{
					a = array[rand()%num];
					for(l=0; l<num; l++)
					if(array[l] == a)
					break;
				}
			}

			stop = clock();
			double time_taken = stop-start;
			time_taken /= (CLOCKS_PER_SEC*10000);

			printf("average time for num = %lld: %.10f \n", num,time_taken);
			fprintf(fout, "%lld %.10f\n",num,time_taken);
		}
	fclose(fout);
	}

return 0;
}