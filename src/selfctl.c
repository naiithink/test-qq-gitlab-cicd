/**
 * \file selfctl.c
 * \author Potsawat Thinkanwatthana (potsawattkw@outlook.com)
 * \brief Monitoring and controlling the execution time of process(es), if a process reaches its limit then kill it.
 * \version 0.0.0
 * \date 2022-06-10
 * 
 */

#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <pthread.h>
#include <signal.h>
/* #include <stdarg.h> */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "selfctl.h"

#if (defined __GNU__ && __gnu_hurd__    \
     || defined __gnu_linux__           )
#include <linux/limits.h>
#else
#include <limits.h>
#endif

extern int errno;
extern char prog_hist_file[PATH_MAX];
extern char job_log_file[PATH_MAX];
static unsigned int thread_index_u;
static sighandler_table *handlers;
volatile static char uninit_job_table[MAX_JOBNAME];

int
main (int argc, char **argv)
{
    if (argc == 1)
        return 1;

    volatile clock_t ptime_start = clock ();
    volatile clock_t ptime_cur = 0;
    volatile thread_table thread_id_table[MAX_THREAD];
    const unsigned int max_longopt_name_len = 16;
    int ch = 0;
    int opt_index = 0;
    int tmp_mode = 0;
    struct stat *prog_hist_file_info;
    struct stat *job_log_file_info;

    opterr = 0;
    prog_hist_file_info = malloc (sizeof *prog_hist_file_info);
    job_log_file_info = malloc (sizeof *job_log_file_info);

    static struct option longopts[] =
    {
        { "histfile",   required_argument,  NULL,   -1  },
        { "prog",       required_argument,  NULL,   'p' },
        { 0, 0, 0, 0 }
    };

    while (ch = getopt_long (argc, argv, "l:p:",
                             longopts, &opt_index) != -1)
        switch (ch)
        {
            case 0:
                if (longopts[opt_index].flag != 0)
                    break;
                else
                {
                    TRACE("InternalError: the option must set a flag.");
                    /* fprintf (stderr, "%s:%i:\
InternalError: '%s': this option must set a flag.\n", __FILE__, __LINE__, longopts[opt_index].name); */
                    exit (1);
                }
            case 'p':
                
            case -1:
                /* TODO: Check if file exists */
                if (!strncmp("histfile", longopts[opt_index].name, max_longopt_name_len)
                    && strlen(optarg) < PATH_MAX)
                {
                    tmp_mode = checkperm (optarg, FMODE_1S);
                    /* throws error */
                    switch (tmp_mode)
                    {
                        case FMODE_DIR:
                            /*  */
                    }
                        /* checkperm (); */
                        strcpy(prog_hist_file, optarg);
                }
                else if (!strncmp("logfile", longopts[opt_index].name, max_longopt_name_len)
                         && strlen(optarg) < PATH_MAX)
                {
                    /* checkperm (); */
                }
                else if (strlen (optarg) >= PATH_MAX)
                    exit (ENAMETOOLONG);
                if ((program_log_file_ptr = fopen (optarg, "rw")) == NULL)
                {
                    switch (errno)
                    {
                        case ENOENT:
                            TRACE("Error: no such file or directory");
                            /* fprintf (stderr, "%s: Error: '%s' no such file or directory.\n", PROGRAM_NAME, longopts[opt_index].name); */
                            break;
                        default:
                            TRACE("InternalError: unknown error occurs");
                            /* fprintf (stderr, "%s:%i: InternalError: '%s': unknown error occurs.\n", __FILE__, __LINE__, longopts[opt_index].name); */
                    }
                    /* prep_exit() ? */
                    exit (errno);
                }
                break;
            case '?':
                TRACE("Error: option requires argument");
                /* fprintf (stderr, "%s: Error: '%s' requires argument.\n", PROGRAM_NAME, longopts[opt_index].name); */
                break;
            default:
                abort ();
        }

    my_default_sighandlers[0] = &prep_exit;
    my_default_sighandlers[1] = &prep_exit;
    handlers->my_default = my_default_sighandlers;

    signal (SIGINT, &sighandler);
    signal (SIGSEGV, &sighandler);

    while ((ptime_cur = clock ()) < MAX_JOBPRD_TICKS)
    {
        /* do something */
    }

    clock_t ptime_end = clock ();
    fclose (program_log_file_ptr);
    return 0;
}

void *
sighandler (int signum)
{
    /* magic (30): most default sig num */
    if (signum < 30)
        int *res = handlers->
}

/* VALID?: (void *) args */
void
prep_exit (const int exit_code, void *block)
{
    
    free(block);
}

int
auto_create_thread (thread_table *table)
{
    if (table == NULL)
    {
        TRACE("Error: NULL `thread_table *table'");
        /* fprintf (stderr, "%s:%i: Error: NULL `thread_table *table'\n", __FILE__, __LINE__); */
        prep_exit (); /*  */
    }
}

unsigned int
hash (int num)
{
    return (num * clock ()) % sizeof(unsigned int);
}

/* int checkperm (char *path, const int mode = FMODE_FULL | FMODE_DIR | FMODE_UREAD | FMODE_UWRIT | FMODE_UEXEC); */

/*
 * if (stat(optarg, &prog_hist_file_info) == 0)
 * {
 *     if (prog_hist_file_info->st_mode == FMODE_DIR)
 *     {
 *         fprintf(stderr, "%s: is a directory.\n", optarg);
 *         * prep_exit() *
 *         free(prog_hist_file_info);
 *         exit(EISDIR);
 *     }
 *     else if (!(prog_hist_file_info->st_mode & FMODE_UWRIT))
 *     {
 *         fprintf(stderr, "%s: Error: '%s' permission denied.\n", PROGRAM_NAME, longopts[opt_index].name);
 *         * prep_exit() ? *
 *         free(prog_hist_file_info);
 *         exit(EACCES);
 *     }
 *     else if (program_log_file_ptr = fopen(optarg, "rw") == NULL)
 *     {
 *         fprintf(stderr, "%s:%i: InternalError: '%s': error opening file.\n", __FILE__, __LINE__, longopts[opt_index].name);
 *         exit(1);
 *     }
 * }
 * 
 * if (stat(optarg, &prog_hist_file_info) == 0)
 * {
 *     if (prog_hist_file_info->st_mode == FMODE_DIR)
 *     {
 *         fprintf(stderr, "%s: is a directory.\n", optarg);
 *         * prep_exit() ? *
 *         free(prog_hist_file_info);
 *         exit(EISDIR);
 *     }
 *     else if (!(prog_hist_file_info->st_mode & FMODE_UWRIT))
 *     {
 *         fprintf(stderr, "%s: Error: '%s' permission denied.\n", PROGRAM_NAME, longopts[opt_index].name);
 *         * prep_exit() ? *
 *         free(prog_hist_file_info);
 *         exit(EACCES);
 *     }
 *     else if ((program_log_file_ptr = fopen(optarg, "rw")) == NULL)
 *     {
 *         fprintf(stderr, "%s:%i: InternalError: '%s': error opening file.\n", __FILE__, __LINE__, longopts[opt_index].name);
 *         exit(1);
 *     }
 * }
 */

int
checkperm (char *path, const int mode)
{
    if (path == NULL)
        return -1;
    
    int res = 0;
    struct stat tmp_stat_struct;

    if (stat (path, &tmp_stat_struct) == 0)
        return -1;

    const int file_mode = tmp_stat_struct.st_mode;

    return res = mode & file_mode;
}

int
timemgr (const clock_t ptime_start)
{}

void *
mainJob (int argc_c, char **argv_c)
{}
