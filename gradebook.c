#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gradebook.h"

// This is the (somewhat famous) djb2 hash
unsigned hash(const char *str) {
    unsigned hash_val = 5381;
    int i = 0;
    while (str[i] != '\0') {
        hash_val = ((hash_val << 5) + hash_val) + str[i];
        i++;
    }

    return hash_val % NUM_BUCKETS;
}

gradebook_t *create_gradebook(const char *class_name) {
    gradebook_t *new_book = malloc(sizeof(gradebook_t));
    if (new_book == NULL) {
        return NULL;
    }

    strcpy(new_book->class_name, class_name);
    for (int i = 0; i < NUM_BUCKETS; i++) {
        new_book->buckets[i] = NULL;
    }
    new_book->size = 0;

    return new_book;
}

const char *get_gradebook_name(const gradebook_t *book) {
    return book->class_name; //Returning class name by accessing it with pointers
}

int add_score(gradebook_t *book, const char *name, int score) {
    int place = hash(name); //Hash to find location of name in buckets
    node_t *current = book->buckets[place];
    node_t* student;
    //Check for valid score is in gradebook_main
    
    if (current == NULL) { //when initial current is null
        student = malloc(sizeof(node_t));
        strcpy(student->name,name);
        student->score = score;
        student->next = NULL;
        book->size++;
        book->buckets[place] = student;
        return 0;
    }

    while(current!=NULL){
        if(strcmp(current->name,name) == 0) {
            current->score = score;
            return 0;
        } else if(current->next == NULL) {
	      student = malloc(sizeof(node_t));
          strcpy(student->name,name);
          student->score = score;
          student->next = NULL;
          current->next = student;
          book->size++;
          return 0;
        }

        current = current->next;     
    }

    return -1;
}

int find_score(const gradebook_t *book, const char *name) {
    int place = hash(name);
    node_t *current = book->buckets[place];  

    while (current != NULL) {
        if(strcmp(current->name,name) == 0) {
            return current->score;
        } else {
            current = current->next;
        }
    }

    return -1;
}

void print_gradebook(const gradebook_t *book) {
   for (int i = 0; i < NUM_BUCKETS; i++) {
        node_t *current = book->buckets[i];
        while (current != NULL) {
            printf("%s: %d\n", current->name, current->score);
            current = current->next;
        }    
    }
}

void free_gradebook(gradebook_t *book){
    for (int i = 0; i < NUM_BUCKETS; i++) {
        node_t *current = book->buckets[i];
        while (current != NULL) {
            node_t *after = current->next;
            free(current); //Freeing gradebook contents
            current = after;
        }    
    }

    free(book); //Freeing gradebook structure
}

int write_gradebook_to_text(const gradebook_t *book) {
    char file_name[MAX_NAME_LEN + strlen(".txt")];
    strcpy(file_name, book->class_name);
    strcat(file_name, ".txt");
    FILE *f = fopen(file_name, "w");
    if (f == NULL) {
        return -1;
    }

    fprintf(f, "%u\n", book->size);
    for (int i = 0; i < NUM_BUCKETS; i++) {
        node_t *current = book->buckets[i];
        while (current != NULL) {
            fprintf(f, "%s %d\n", current->name, current->score);
            current = current->next;
        }
    }

    fclose(f);
    return 0;
}

gradebook_t *read_gradebook_from_text(const char *file_name) {
    FILE *f = fopen(file_name, "r");
    char class_newname[128] = {};
    strcpy(class_newname,file_name);
    class_newname[strlen(class_newname)-strlen(".txt")] = '\0';
    gradebook_t *new_book = create_gradebook(class_newname);
    if (f == NULL) {
        free_gradebook(new_book);
        return NULL;
    }

    int score = 0;
    unsigned booksize = 0;
    char name[128] = {};
    fscanf(f, "%u\n", &booksize);
    int end = 0;
    while(end != EOF){
        fscanf(f, "%s %d", name, &score);
        add_score(new_book,name,score);
        end = getc(f);
    }
       
    fclose(f);
    return new_book;
}

int write_gradebook_to_binary(const gradebook_t *book) {
   char file_name[MAX_NAME_LEN + strlen(".bin")];
    strcpy(file_name, book->class_name);
    strcat(file_name, ".bin");
    FILE *f = fopen(file_name, "wb");
    if (f == NULL) {
        return -1;
    }

    fwrite(&book->size,sizeof(int),1,f);
    for (int i = 0; i < NUM_BUCKETS; i++) {
        node_t *current = book->buckets[i];
        while (current != NULL) {
                unsigned studentlen = strlen(current->name);
            fwrite(&studentlen,sizeof(studentlen),1,f);
            fwrite(current->name,sizeof(char),studentlen,f);
            fwrite(&current->score,sizeof(int),1,f);
            current = current->next;
        }
    }

    fclose(f);
    return 0;
}

gradebook_t *read_gradebook_from_binary(const char *file_name) {
    FILE *f = fopen(file_name, "rb");
    char class_newname[MAX_NAME_LEN] = {};
    strcpy(class_newname,file_name);
    class_newname[strlen(class_newname)-strlen(".bin")] = '\0';
    gradebook_t *new_book = create_gradebook(class_newname);
    if (f == NULL) {
        free_gradebook(new_book);
        return NULL;
    }

    int booksize = 0;
    new_book->size = 0;
    fread(&booksize,sizeof(int),1,f);
    for (int i = 0; i < booksize; i++) {
        int score = 0;
        char name[MAX_NAME_LEN] = {};
        unsigned namelen = 0;
        fread(&namelen,sizeof(namelen),1,f);
        name[namelen]='\0';
    	fread(name,sizeof(char),namelen,f);
    	fread(&score,sizeof(int),1,f);
    	add_score(new_book,name,score);
    }

    fclose(f);
    return new_book;
}
