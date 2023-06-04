#include <stdio.h>
#define M 50
void main() {
    int r, c;
    int array[M][M];
    for(r = 0; r < M; r++) {
	for(c = 0; c < M; c++) {
	    if(r==1 || r==M-2)
		if(c==0 || c==M-1)
		    array[r][c] = 0;
		else
		    array[r][c] = 1;
	    else if(c==1 || c==M-2)
		if(r==0 || r==M-1)
		    array[r][c] = 0;
		else
		    array[r][c] = 1;
	    else
		array[r][c] = 0;
	    printf("%d", array[r][c]);
	}
	printf("\n");
    }

}   
