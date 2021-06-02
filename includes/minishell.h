#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <termios.h>
# include <term.h>
# include <unistd.h>

# ifdef		RELEASE
#  define		DEBUG			0
#  define		P_ARRAY			0
#  define		PRINT_TERMCAP	0
# else
#  define		DEBUG			1
#  define		P_ARRAY			0
#  define		PRINT_TERMCAP	0
# endif

# define	KEY_BUFFER_SIZE		4096
# define	GNL_BUFFER_SIZE		1024

# define	KEY_UP				"[A"
# define	KEY_DOWN			"[B"
# define	KEY_RIGHT			"[C"
# define	KEY_LEFT			"[D"

# define	CURSOR_RIGHT		"\033[1C"
# define	CURSOR_LEFT			"\033[1D"
# define	CURSOR_SAVE			"\033[s"
# define	CURSOR_RECOVER		"\033[u"
# define	CURSOR_DEL			"\033[K"

# ifndef O_DIRECTORY
#  define	O_DIRECTORY			__O_DIRECTORY
# endif

# ifndef PATH_MAX
#  define PATH_MAX	4096
# endif

# define	_END				"\033[1;0m"

# define	_DEFAULT			"\033[1;39m"
# define	_RED				"\033[1;31m"
# define	_GREEN				"\033[1;32m"
# define	_YELLOW				"\033[1;33m"
# define	_BLUE				"\033[1;34m"
# define	_MAGENTA			"\033[1;35m"
# define	_CYAN				"\033[1;36m"
# define	_LIGHTGRAY			"\033[1;37m"
# define	_DARKGRAY			"\033[1;90m"
# define	_LIGHTRED			"\033[1;91m"
# define	_LIGHTGREEN			"\033[1;92m"
# define	_LIGHTYELLOW		"\033[1;93m"
# define	_LIGHTBLUE			"\033[1;94m"
# define	_LIGHTMAGENTA		"\033[1;95m"
# define	_LIGHTCYAN			"\033[1;96m"
# define	_WHITE				"\033[1;97m"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_buffer
{
	char	*ptr;
	size_t	size;
}				t_buffer;

typedef struct s_env
{
	char	*key;
	char	*value;
}				t_env;

typedef struct s_reader
{
	int		size;
	int		pos;
}				t_reader;

typedef struct s_parse
{
	bool	s_quotes;
	bool	quotes;
	char	*new_line;
}				t_parser;

typedef struct s_lexer
{
	int		i;
	int		j;
	int		id;
	bool	had_quotes;
}				t_lexer;

typedef struct s_token
{
	char	*str;
	bool	sp;
	int		type;
	int		id;
}				t_token;

typedef struct s_history
{
	t_list	*lst;
	int		act_pos;
}				t_history;

typedef struct s_pipes
{
	int		to_father[2];
	int		to_son[2];
}				t_pipes;

typedef struct s_infos
{
	int	len;
	int	was_quotes;
}				t_infos;

typedef struct s_command
{
	char	*prog;
	char	*path;
	char	**argv;
	bool	need_pipe;
	bool	need_redirect;
	char	*redirect_path;
	bool	listen_stderr;
	bool	listen_stdout;
	bool	redirect_append;
	char	*operator;
	bool	skip_exec;
	bool	file_input;
}				t_command;

typedef struct s_minishell
{
	t_list			*gc;
	char			*workdir;
	int				last_return;
	t_list			*env;
	t_list			*tokens;
	struct termios	term;
	struct termios	save;
	char			termbuffer[2048];
	t_history		history;
	char			**actual_str;
	bool			use_termcaps;
	t_pipes			pipes;
	pid_t			child;
	pid_t			outputmngr;
	int				saved_stdout;
	int				saved_stderr;
	int				saved_stdin;
	t_reader		reader;
	bool			error;
	t_buffer		pipe_output;
	bool			need_pipe;
	bool			keep_reading;
	bool			is_in_quotes;
	bool			is_in_s_quotes;
	bool			had_bslash;
	bool			is_running;
}				t_minishell;

extern t_minishell	g_shell;

// LIB ------------------------------------------------------------------------

int			ft_atoi(const char *str);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstadd_front(t_list **alst, t_list *new);
void		ft_lstclear(t_list **lst);
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
size_t		ft_lstsize(t_list *alist);
size_t		ft_envlstsize(t_list *alist);
void		ft_putcolor(char *str, char *color);
void		ft_putstr_fd(int fd, char *str);
void		ft_putstr(char *str);
int			ft_putchar(int c);
int			ft_putchar_fd(int fd, int c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(char *s1);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strjoinf1(char *s1, char *s2);
char		*ft_strjoinf2(char *s1, char *s2);
char		*ft_strjoinall(char *s1, char *s2);
char		*ft_strjoinc(char *s1, char c);
size_t		ft_strlen(char *str);
void		gc_clean(void);
void		gc_free(void *ptr);
void		*gc_malloc(size_t size);
size_t		ft_nblen(long long nb);
size_t		ft_strlen_charset(char *str, char *charset);
char		*ft_itoa(int n);
void		ft_bzero(void *s, size_t n);
char		*ft_strchr(const char *s, int c);
char		**ft_split(char const *s, char c);
void		*ft_calloc(size_t size);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		*ft_strcat(char *dest, char *src);
char		**ft_split_spaces(char const *s);
char		*ft_strstr(char *str, char *to_find);
char		*ft_strreplace(char *str, char *substr, char *replace);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		gc_free_tab(char **arr);
size_t		ft_tab_len(char **car);
void		*ft_calloc_char(size_t size, int c);
int			ft_memcmp(const char *s1, const char *s2, size_t size);
char		*ft_memchr(const char *s, int c, int pos, size_t size);

char		*ft_strndup(char *s1, size_t n);
char		*ft_strtrim_spaces(char *str);

bool		ft_isalpha(char c);
bool		ft_isdigit(char c);
bool		ft_isalnum(char c);
bool		ft_isascii(char c);
bool		ft_isprint(char c);
bool		ft_isspace(char c);
bool		ft_ischarset(char c, char *charset);
bool		ft_isinrange(long long value, long long min, long long max);

// MINISHELL ------------------------------------------------------------------

int			close_shell(char *msg);
void		process_input(char *line);
int			builtin_cd(char **argv);
int			builtin_pwd(void);
char		*get_pwd(void);
int			builtin_env(bool print_export);
int			builtin_echo(char **str);
char		**get_envp(void);
int			builtin_which(char **argv);
int			builtin_export(char **argv);
int			builtin_unset(char **argv);
void		set_env(char *key, char *value);
void		unset_env(char *key);
char		*get_env(char *key);
void		init_env(char **envp);
int			run_line(char **argv);
int			check_type_at(int i);
void		get_lexer(char *line);
void		init_lexer(t_lexer *lexer);
void		display_tokens(void);
char		*parse_env_var(char *word);
size_t		get_word_len(char *word, int i);
void		join_last_token(t_token *token);
int			set_dollar_type(t_token *token, char *line, int start);
char		*treat_backslash(char *word, int *i, int *trans);
char		**parse_line(char *line);
void		display_array(char **array);
int			check_occurence(char *str, char c);
int			quotes_token_len(char *line, t_lexer *lexer);
char		**array_from_list(void);
void		display_array(char **array);
void		set_input_mode(void);
void		reset_input_mode(void);
char		*read_term(void);
bool		process_key(char *c, t_reader *reader, char ***str);
void		unprint_char(char ***str, t_reader *reader);
void		print_char(char ***str, char *c, t_reader *reader);
char		*get_str_rterm(char **str);
int			get_next_line(int fd, char **line);
void		history_add(char **line);
char		*history_before(char ***str, t_reader *reader);
char		*history_after(char ***str, t_reader *reader);
void		print_debug_termcap(char *c);
void		remove_line(char ***line, t_reader *reader);
void		put_in_term(char **line, char ***str, t_reader *reader);
char		*which(char *prog);
void		pre_prompt(void);
int			get_this_char(char **c, char **retour);
void		cursor_op(char *op);
void		add_signals_listeners(void);
void		signals_listeners_to_child(void);
void		SIGQUIT_catcher_subprocess(int code);
void		redir_sig_to_child(int signal);
int			builtin_exit(char **argv);
void		close_subprocess(int code);
void		set_output(t_command cmd);
void		reset_output(void);
void		manage_output(t_command cmd);
void		process_pipe(t_command cmd, char *buffer, int len);
int			exec_builtin(char *prog, char **argv);
void		wait_outputmanager(t_command cmd);
int			bslash_token_len(char *line, t_lexer *lexer);
int			quotes_token_len(char *line, t_lexer *lexer);
char		*parse_tokens(char *word);
char		*parse_d_quotes(char *word);
int			get_token_len(char *line, t_lexer *lexer);
int			bslash_token_len(char *line, t_lexer *lexer);
void		token_l_error(char *line, t_lexer *lexer);
int			else_token_l(char *line, t_lexer *lexer);
int			write_redirect(char *path, char *buffer, bool erease, int len);
void		close_pipe(void);
char		*treat_doll_slash(char *word, int i, int back);
char		*replace_dolls(char *word, int i);
char		*treat_doll(char *word, int *i, int *trans);
char		*error_bslash(int *i);
char		*bslash_filled(char *word, int *i, int *trans, int back);
char		*bslash_nquotes(char *word, int i, int r_back);
int			check_slash(char *word, int i);
void		reset_pipe_output(void);
t_list		*get_commands(char **argv);
bool		fill_cmd_structs(t_list *lst);
int			commant_not_found(char *cmd);
int			syntax_error(void);
bool		is_a_file(char *path);
char		*parse_s_quotes(char *word);
void		*ft_memjoin(void *s1, size_t l1, void *s2, size_t l2);
void		get_input_part2(t_command cmd, t_buffer *res);
void		print_buffer_in_file(t_command *cmd, bool print);
void		print_buffer_in_fd(t_buffer buff, int fd);
int			file_not_found(char *file);
t_buffer	*get_multiple_input(t_command cmd);
bool		is_operator(char *c);
void		check_write_redirect(t_command *cmd, t_list *cmds);

#endif
