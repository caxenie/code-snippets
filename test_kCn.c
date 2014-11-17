#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

long num_shuffles(int n, int r)
{
    long f[n + 1];
    f[0]=1;
    for (int i=1;i<=n;i++)
        f[i]=i*f[i-1];
    return f[n]/f[r]/f[n-r];
}

unsigned int shuffle_pops_ids(unsigned int *ar, size_t n, unsigned int k)
{
    unsigned int finished = 0;
    unsigned int changed = 0;
    unsigned int i;
	
    if (k > 0) {
        for (i = k - 1; !finished && !changed; i--) {
            if (ar[i] < (n - 1) - (k - 1) + i) {
                /* Increment this element */
                ar[i]++;
                if (i < k - 1) {
                    /* Turn the elements after it into a linear sequence */
                    unsigned int j;
                    for (j = i + 1; j < k; j++) {
                        ar[j] = ar[j - 1] + 1;
                    }
                }
                changed = 1;
            }
            finished = i == 0;
        }
        if (!changed) {
            /* Reset to first combination */
            for (i = 0; i < k; i++) {
                ar[i] = i;
            }
        }
    }
    return changed;
}


int main(int argc, char**argv)
{
	unsigned int base_idx[] = {0,1,2};
        const unsigned int pre_post_pair = 2;
	int nsize = 3;
	int** sol = (int**)calloc(pre_post_pair*num_shuffles(nsize, pre_post_pair), sizeof(int*));
		for(int i = 0; i<pre_post_pair*num_shuffles(nsize, pre_post_pair);i++)
			sol[i] = (int*)calloc(pre_post_pair, sizeof(int));
        int sol_idx = 0;
	/* direct solution */
	do{
   		/* shuffle the populations ids for updating */
                int* cur_ids = base_idx;
		sol[sol_idx][0] = cur_ids[0];
		sol[sol_idx][1] = cur_ids[1];
		sol[sol_idx+num_shuffles(nsize, pre_post_pair)][0] = cur_ids[1];
		sol[sol_idx+num_shuffles(nsize, pre_post_pair)][1] = cur_ids[0];
	sol_idx ++;
        }while(shuffle_pops_ids(base_idx, nsize, pre_post_pair));

	for(int i =0;i<pre_post_pair*num_shuffles(nsize, pre_post_pair);i++){
		for(int j=0;j<pre_post_pair;j++){
			printf(" %d", sol[i][j]);
		}
		printf("\n");
	}

	return EXIT_SUCCESS;
}
