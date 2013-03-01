#include <stdio.h>
#include <stdlib.h>

int main(void)
{
srand(time(NULL));
int  rand_map;
int i = 0;

while(i<30){
rand_map = (rand()%(2)+1);
printf("RND[%d]: %d\n", i, rand_map);
i++;
}

return 0;
}


