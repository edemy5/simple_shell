#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>


/* Represents read/write buffers */
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* Used for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* Used if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - Represents singly linked list
 * @num: Represents the number field
 * @str: This is a string
 * @next: Points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Contains pseudo-arguments to pass into a function,
 * allows a uniform prototype for a function pointer struct
 * @arg: This is a string generated from getline and contains arguments
 * @argv: An array of strings generated from arg
 * @path: A string path for the current command
 * @argc: The argument count
 * @linecountnw: Shows the error count
 * @err_num: Used for the error code for exits()s
 * @linecount_flag: If this is on, count this line of input
 * @fname: Represents the program filename
 * @env: Shows linked list local copy of environ
 * @environ: Shows custom modified copy of environ from LL env
 * @history: Represents the history node
 * @alias: This is the alias node
 * @env_changed: It's on if environ was changed
 * @status: Shows the return status of the last exec'd command
 * @cmd_buf: This is on if chaining, and shows the
 * address of the pointer to cmd_buf
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: The fd from which to read line input
 * @histcount: Shows the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int linecountnw;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* Pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - Contains a built-in string and related function
 * @type: Represents the built-in command flag
 * @func: Stands for the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtinc(info_t *);
void find_cmdp(info_t *);
void fork_cmde(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_charstrng(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputsa(char *);
int _eputchare(char);
int _putfdc(char c, int fd);
int my_putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmpl(char *, char *);
char *starts_withs(const char *, const char *);
char *_strcats(char *, char *);

/* toem_string1.c */
char *_strcpys(char *, char *);
char *_strdups(const char *);
void _putsa(char *);
int _putchars(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncats(char *, char *, int);
char *_strchrs(char *, char);

/* toem_tokenizer.c */
char **strtows(char *, char *);
char **strtow2w(char *, char);

/* toem_reallocb.c */
char *_memsetbyte(char *, char, unsigned int);
void ffreess(char **);
void *_reallocb(void *, unsigned int, unsigned int);

/* toem_memory.c */
int freeptr(void **);

/* toem_atoinw.c */
int myinteractive(info_t *);
int is_mydelim(char, char *);
int _myisalpha(int);
int _atoinw(char *);

/* toem_errors1.c */
int _erratoinew(char *);
void print_errorm(info_t *, char *);
int print_dn(int, int);
char *convert_number(long int, int, int);
void remove_commentsi(char *);

/* toem_builtin.c */
int _myexits(info_t *);
int _mycdd(info_t *);
int _myhelpp(info_t *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myaliase(info_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(info_t *);
void set_infoi(info_t *, char **);
void free_infof(info_t *, int);

/* toem_environ.c */
char *_getenvp(info_t *, const char *);
int _myenvp(info_t *);
int _mysetenve(info_t *);
int _myunsetenvr(info_t *);
int populate_env_listt(info_t *);

/* toem_getenvp.c */
char **get_environ(info_t *);
int _unsetenva(info_t *, char *);
int _setenvi(info_t *, char *, char *);

/* toem_history.c */
char *get_history_files(info_t *info);
int write_historycf(info_t *info);
int read_historyf(info_t *info);
int build_history_lists(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_lists.c */
list_t *add_nodes(list_t **, const char *, int);
list_t *add_nodes_end(list_t **, const char *, int);
size_t print_lists_strel(const list_t *);
int delete_node_at_indx(list_t **, unsigned int);
void free_lists(list_t **);

/* toem_lists1.c */
size_t list_lend(const list_t *);
char **list_to_strings(list_t *);
size_t print_lists(const list_t *);
list_t *node_starts_withs(list_t *, char *, char);
ssize_t get_node_indx(list_t *, list_t *);

/* toem_vars.c */
int bis_chain(info_t *, char *, size_t *);
void check_chains(info_t *, char *, size_t *, size_t, size_t);
int replace_aliast(info_t *);
int replace_varsa(info_t *);
int replace_strings(char **, char *);

#endif


