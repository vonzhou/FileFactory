#include "global.h"

int main(int argc, char ** argv){
	int i = 0, id = 1, result, count=0;	
	int sockfd, fd;
	char suffix[] = ".s"; // output file name = file + suffix
	char output[30] = {0};
	int outputfd;
	struct sockaddr_in servaddr;
	
	char buf[MAX_CHUNK_SIZE];
	FileInfo *fi=file_new();
	FingerChunk *p;
	
	if(argc != 2)
		err_quit("usage:client <file>");
	
	strcpy(fi->file_path, argv[1]);
	strcpy(output, argv[1]);
	strcat(output, suffix); 
	// open the output file to dump
	if((outputfd = open(output,O_RDWR | O_CREAT, 0666)) == -1)
		err_quit("Open the output file failed.");
	//FILE *fp = fdopen(outputfd, "rw");

	chunk_file(fi);
	printf("File size : %lld\n",fi->file_size);
	printf("Chunk Num : %d\n",fi->chunknum);
	p= fi->first;
	
	while(p){
		char hash[41];
        digestToHash(p->chunk_hash,hash);
        //printf("chunklen : %d ",p->chunklen);
        //printf("Fingerprint : %s \n",hash);
		result = write(outputfd, hash, 41);
		if(result != 41)
			err_quit("write error..");
		write(outputfd, "\n", 1); //every digest a line
		p = p->next;
	}
	close(outputfd);	
	close(fd);
	file_free(fi);
}
