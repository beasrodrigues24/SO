#define FILENAME "file_pessoas.bin"

typedef struct person {
    char name[200];
    int age;
} Person;

// API
int new_person (char * name, int age);
int person_change_age(char * name, int age);
int person_change_age_v2(long pos, int age);