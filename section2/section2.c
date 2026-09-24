#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 4096

typedef struct
{
    const char *log1;
    const char *log2;
    int n;
} process_args_t;


/* TODO */
void count_in_buffer(const char *buf, int *crit, int *err, int *fail)
{
    const char *position = buf;

    while ( (position = (strstr(position ,"CRITICAL"))) != NULL  ){
        (*crit)++;
        position+=8;
    }

    position = buf;

    while ( (position = (strstr(position ,"ERROR")))  != NULL  ){
        (*err)++;
        position+=5;
    }

    position = buf;

    while ( (position = (strstr(position ,"FAILED LOGIN"))) != NULL  ){
        (*fail)++;
        position+=12;
    }
}

/* TODO */
void count_keywords_block(const char *filename, off_t start, off_t end,
                           const char *prev_tail, int prev_len,
                           int *crit, int *err, int *fail)
{
    int fd = open (filename, O_RDONLY);

    lseek (fd, start, SEEK_SET);

    int buffer_size = end - start + prev_len + 1;

    char buffer[buffer_size];

    strncpy(buffer,prev_tail,prev_len);
    
    int char_readed = read(fd, buffer + prev_len, end - start );

    buffer[char_readed + prev_len ] = '\0';

    count_in_buffer(buffer ,crit, err, fail);

    close(fd);

}

/* TODO */
void process_file(const char *filename, int n, const char *tmp_prefix)
{
    (void)filename; (void)n; (void)tmp_prefix;
}

/* TODO */
void process_task_wrapper(void *arg)
{
    (void)arg;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <log1> <log2> <N>\n", argv[0]);
        return 1;
    }

    process_args_t args;
    args.log1 = argv[1];
    args.log2 = argv[2];
    args.n = atoi(argv[3]);

    printf("Logs 1: %s\n", args.log1);
    printf("Logs 2: %s\n", args.log2);
    printf("n: %d\n", args.n);
    fflush(stdout); 

    system("mkdir -p tmp bin");

    process_task_wrapper(&args);

    return 0;
}
