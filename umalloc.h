#define malloc(X) umalloc((X), __FILE__, __LINE__)
#define free(X) ufree((X), __FILE__, __LINE__)
#define MEM_SIZE 10*1024*1024

static char MEM[MEM_SIZE];


typedef struct Metadata {
    unsigned int blockSize;
    char used;
} Metadata;

// char* next(char* curr);

// void combine();

// void* allocate(char* curr, size_t size);

// void* umalloc(size_t size,char *file, int line)

// void ufree(void* addressToBeFreed, char *file, int line);

// void printMetadata();