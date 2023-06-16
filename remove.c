#include <sys/stat.h>
#include <sys/types.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct{
	char name[256];
	char path[1024];
	unsigned int position;
	unsigned int size;

	struct member *next;
	struct member *previous;	
} member;

unsigned int get_size(FILE *arch){
	struct stat f_data;

	fstat(fileno(arch), &f_data);
	return (unsigned int) f_data.st_size;
}

int remove_bytes(FILE *arch, const unsigned int b_init, const unsigned int b_final){
	char *buffer[1024];
	unsigned int size = get_size(arch);
	unsigned int read = b_final;
	unsigned int write = b_init - 1;
	unsigned int rt;

	if (b_init > b_final) return 1;
	if (b_final > size) return 2;

	if (read == size){
		ftruncate(fileno(arch), b_init-1);
		return 0;
	}

	while(read < size){
		fseek(arch, read, SEEK_SET);
		if (size - read > 1024) rt = fread(buffer, 1, 1024, arch);
		else rt = fread(buffer, 1, size-read, arch);
		fseek(arch, write, SEEK_SET);
		fwrite(buffer, 1, rt, arch);
		read += rt;
		write += rt;
	}
	rewind(arch);
	ftruncate(fileno(arch), size - (b_final-b_init+1));
	return 0;
}

member* search_member(char *name, member *dir){
	member *i;

	for(i = dir; i != 0; i = (member*) i->next){
		if (!strcmp(name, i->name)){
			return i;
		}
	}

	return 0;
}

//Falta atualizar a lista;
int remove_member(char *name, member* dir, FILE *arch){
	unsigned int b_init, b_final, rt;
	member *removal = search_member(name, dir);
	
	if (removal == 0) 
		return 1;
	b_init = removal->position;
	b_final = removal->position + removal->size - 1;
	rt = remove_bytes(arch, b_init, b_final);
	if (rt) 
		return 1;
}

member* create_test(){
	FILE *new = fopen("test.txt", "wb+");
	char buffer[19] = {'z', 'z', 'z', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o'};
	fwrite(buffer, 1, 19, new);

	member *members = (member*) malloc(2*sizeof(member));
	strcpy(members[0].name, "t1.txt");
	members[0].position = 5;
	members[0].size = 10;
	members[0].next = (struct member*) &members[1];
	members[0].previous = 0;

	strcpy(members[1].name, "t2.txt");
	members[1].position = 15;
	members[1].size = 5;
	members[1].next = 0;
	members[1].previous = (struct member*) &members[0];

	fwrite(members, 1, sizeof(member), new);
	fclose(new);
	return &members[0];
}

int main(int argc, char **argv){
	member *dir = create_test();

	FILE *arch = fopen("test.txt", "rb+");
	if (!arch){
		printf("ERRO: O arquivo não foi aberto!\n");
		return 1;
	}
	
	remove_member("t2.txt", dir, arch);
	return 0;
}