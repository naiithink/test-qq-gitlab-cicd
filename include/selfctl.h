#ifndef SELFCTL_H
#define SELFCTL_H

#ifdef _cplusplus
extern "C" {
#endif

#define PROGRAM_NAME "selfctl"

#if (defined __GNU__ && __gnu_hurd__    \
     || defined __gnu_linux__           )
#define TRUE_PTIME 1
#else
#define TRUE_PTIME 0
#endif

#include <pthread.h>
#include <stdio.h>

#define FMODE_FULL      0000700
#define FMODE_DIR       0040000
#define FMODE_UREAD     0000400
#define FMODE_UWRIT     0000200
#define FMODE_UEXEC     0000100
#define MAX_THREAD 2
#define MAX_JOBNAME 2
#define N_SUPPORTED_DFT_SIG_HANDLING 2
#define N_SUPPORTED_CUS_SIG_HANDLING 0
#define PTHREAD_INIT (pthread_t)(MAX_THREAD + 1)

/* >>> tmp */
#define MAX_JOBPRD_INMIN 12
#define MAX_JOBPRD_INSEC (MAX_JOBPRD_INMIN * 60)
#define MAX_JOBPRD_TICKS (MAX_JOBPRD_INSEC * CLOCKS_PER_SEC)
/* <<< tmp */

typedef void (*V_PF_VS)(void *);
typedef void *(*VS_PF_VS)(void *);

typedef struct
{
    const V_PF_VS (*my_default)[];
    VS_PF_VS (*my_custom)[];
}
sighandler_table;

typedef struct
{
    char name[MAX_JOBNAME];
    unsigned int id;
    volatile VS_PF_VS callbacks[]; /*  */
}
job_table;

typedef struct thread_table
{
    int creation_return;
    pthread_t id;
    struct thread_table *prev;
    struct thread_table *next;
}
thread_table;

/* Diag */
extern FILE *program_log_file_ptr;

/* Files */
int checkperm(char *path, const int perm);

/* Jobs */
/* int gen_args_table(void *arg, ...); */
void init_job_table(pthread_t *);
int auto_create_thread(thread_table *);
unsigned int hash(int);
int timemgr(const clock_t p_start);
void *main_job(int argc_c, char **argv_c);
void prep_exit(void) __attribute__((noreturn));

/* Signals */
void *sighandler(int);
extern V_PF_VS my_default_sighandlers[N_SUPPORTED_DFT_SIG_HANDLING];

#ifdef _cplusplus
}
#endif

#endif /* SELFCTL_H */
