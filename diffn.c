// this utility is used to show how many different lines 
// between two files ,maybe is slow method
// vonzhou

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	int i,count = 0;
	char digest1[41],digest2[41];
	FILE *fp1, *fp2;
	if(argc != 3){
		printf("Usage:diffn <file1> <file2>\n");
		exit(-1);
	}
	
	fp1 = fopen(argv[1],"r");
	fp2 = fopen(argv[2],"r");

	if(fp1 == NULL || fp2 == NULL){
		printf("fopen failed ..\n");
		exit(-1);
	}
	
	// one file not to the end 
	while(!feof(fp1) || !feof(fp2)){
		while(!feof(fp1) && !feof(fp2)){
			// compare the different lines
			fgets(digest1, 41, fp1);
			fgets(digest2, 41, fp2);
			if(!strcmp(digest1, digest2))
				count ++;
		}
		// enter just one loop
		while(!feof(fp1)){
			fgets(digest1, 41, fp1);
			count ++;
		}
		while(!feof(fp2)){
			fgets(digest2, 41, fp2);
			count ++;
		}
	}
	
	printf("#different lines betwn %s and %s = %d\n",argv[1], argv[2], count);
	fclose(fp1);	
	fclose(fp2);
	return 0;
}
