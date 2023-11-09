/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:06:24 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/09 21:33:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stddef.h>
# include "libft/libft.h"

# define FILENAMELEN 4
# define BIG 999
# define ENVN 999

# define RED "\001\e[0;31m\002"
# define GREEN "\001\e[0;32m\002"
# define GREENBOLD "\001\e[1;32m\002"
# define YELLOW "\001\e[0;33m\002"
# define BLUE "\001\e[0;34m\002"
# define BLUEBOLD "\001\e[1;34m\002"
# define MAGENTA "\001\e[0;35m\002"
# define CYAN "\001\e[0;36m\002"
# define UNSET "\001\e[0m\002"
# define BOLD "\001\e[1m\002"
# define FILENAME ".tempfile"
# define FILENAME1 ".tempfile01"
# define FILENAME2 ".tempfile001"
# define ERRSTD	STDERR_FILENO

# define BLTINS 0

# define NBLOL "9223372036854775808"
# define PROMPT "minishell_by_lpollini&nizz"
# define SYNTERR "minishell: syntax error\n"
# define ERRBADASS "minishell: export: bad assignment\n"
# define LIMITERMSG "minishell: warning: heredoc reached EOF before limiter \
(expected \'"
# define PROMPTSIZEMAX 299

# define WELLDONE 0
# define NEOUGHINPT 1
# define ALLRECIEVED 2
# define ALLSENT -2
# define NOINFILE -3
# define NOOUTF 3
# define CMDNOTFOUND 4
# define PIPECREATERR -4
# define OTHRERR 5
# define TRUNCFLAGS 01101
# define APPENDFLAGS 02101

typedef struct s_loco
{
	char			*piece;
	int				and;
	int				exit;
	int				or;
	int				g_and;
	int				g_or;
	int				parentheses;
	int				n;
	int				out_to_pipe;
	int				wild;
	int				flag_no_process;
	int				counter;
	int				index;
	DIR				*dir;
	struct dirent	*entry;
	int				sigpass;
	int				count;
	int				start_flag;
	int				first_para;
	int				i;
	int				z;
	int				pasta;
	long			forkpid;
	char			redir_n_pipe;
	char			limiter_flag;
	int				fd_setafter;
	int				flagc;
	pid_t			limiter_pid;
	char			sigstop;
}	t_loco;

typedef struct s_pare
{
	int		nested;
	char	*pare_piece;
	int		index;
	char	*new_str;
	int		first;
	int		last;
	int		controll;
	int		flag;
	char	extra;
	char	*extra_2;
	int		child_fd;
}	t_pare;

typedef struct s_vector4_int
{
	int	i;
	int	j;
	int	x;
	int	y;
}	t_vector4_int;

typedef struct s_vector2_int
{
	int	a;
	int	b;
}	t_vector2_int;

typedef struct s_var_lst
{
	struct s_var_lst	*next;
	char				*value;
	char				*name;
}	t_var_lst;

typedef struct s_shell_stuff
{
	char			**cmd;
	char			*pwd;
	char			*envp[ENVN];
	int				envn;
	char			**args;
	int				argn;
	char			*usr;
	int				lststatus;
	char			haspipes;
	char			beginsquote;
	int				doexit;
	unsigned char	exit_code;
	int				tempfds[2];
}	t_shell_stuff;

typedef struct s_fds
{
	int	a_touse[2];
}	t_fds;

typedef struct s_command
{
	char	*cmd;
	char	**dquotesplit;
	char	**spacesplit;
	char	**pipelinesplit;
}	t_command;

//* ---------------------------------- nizz -------------------------------- */
t_loco	*loco(void);
char	*ft_split_bonus(char *s, int *index);
void	init_bonus_struct(void);
char	**ft_split_operators(char *s);
char	*word_dup_bonus(char const *str, int start, int finish);
int		count_words_bonus(char *str);
void	check_for_operator(char *cmd);
char	*ft_strdup_len(const char *src, int len);
char	*ft_strdup_fr_to_free(char *src, int from, int to);
char	*check_for_parentheses(char *cmd, t_shell_stuff *sh, int *pp, \
			int doset);
size_t	ft_strlen_arr(void	**loco);
char	*clean_cmd(char *str);
/* ---------------------------- wildcard/parce.c -------------------------- */
int		verify_match(char **split_wild, const char *str, int *i, int *j);
int		match(const char *str, char **split_wild, int first_char, \
			int last_char);
char	*wildcard_process(char *str, int *first, int *last, char ***split_wild);
char	*check_for_wildcard_normal(char *str);
/* ---------------------------- wildcard/utils.c -------------------------- */
char	*ft_realloc(char *pointer, int size);
void	main_command_join(char **new_str, char **split);
void	initialize_three_to_zero(int *n, int *i, int *z);
void	pr_dir(char **new_str, char **split_wild, int first_char, \
			int last_char);
char	*split_wild(char *str);
int		execution_bonus_helper(char **cmds, int *pp,
			t_shell_stuff *sh, int doset);
/* --------------------------- wildcard/utils_1.c ------------------------- */
char	*add_operator(char *new_new_str, char **str);
char	*add_command_processed(char *to_be_processed, char *new_new_str);
int		shft_isallnum(char *s);
int		split_wild_size(char *str);
char	*split_wild_fill_new_str(char *str, char *new_str);
/*! ------------------------------------------------------------------------ */

/* ----------------------------- executor_utils.c -------------------------- */
int		shft_isalnum(const int c);
char	*ft_strtab_join_free(char **s);
char	*shft_arg(t_shell_stuff *sh, char *str);
int		shft_istab1(char *str);
int		shft_redirections(char **cmd, t_shell_stuff *sh, int *doset);
/* -------------------------------- to index ------------------------------- */
int		ft_strcmp_noend(const char *s1, const char *s2);
int		shft_exit(t_shell_stuff *sh);
char	*ft_strjoin_free(char *s1, const char *s2);
char	*ft_strjoin_free_1(char const *s1, char *s2);
int		shft_rmdirone(char *s, int lim);
char	*build_put(t_shell_stuff *sh);
char	*better_pwd(char *pwd, const char *usr);
char	*shft_prompt(t_shell_stuff *sh, int dofree);
int		export_lol(t_shell_stuff *sh);
char	*ft_strdup_clean(char *s);
int		shft_execute_cmd(t_shell_stuff *sh, char *str);
char	*shft_strchr(const char *s, char c, char ig1, char ig2);
char	*shft_strchr_1(const char *s, char c, char ig1, char ig2);
char	*shft_strrchr(const char *s, char c, char ig1, char ig2);
char	**ft_split1(char const *s, char c, char iga);
char	**shft_split(char const *s, char c, char ig1, char ig2);
char	**shft_split1(char *s, char c, char ig1, char ig2);
int		count_words_1(const char *str, char c);
int		shft_pipexexec(char **cmds, int pipes, t_shell_stuff *sh);
int		shft_strcmp_noend(const char *s1, const char *s2);
int		shft_strcmp_noend2(const char *s1, const char *s2);
int		shft_isalnum(const int c);
int		shft_atoi(const char *str);
char	*shft_getenv(char *find, char *envp[], t_shell_stuff *sh);
char	*shft_env_dup(char *in[], int i, int *r);
int		shft_getenv_line(char *find, char *envp[], t_shell_stuff *sh);
void	update_env_free(char **envp, char *pwd, t_shell_stuff *sh);
int		shft_env_init_free(char *env[], char *in[], int sw);
char	*ft_strjoin_by(char const *s1, char const *s2, char sep);
char	*good_strdup(const char *src);
int		shft_istab(char c);
int		shft_split1_test(char *s, char ig1, char ig2, int test);
int		shft_rmdirone(char *s, int lim);
int		shft_pwd_better_1(char *res, char *nw, char **ori);
void	shft_init_two_vars(int *a, int va, int *b, int vb);
int		count_words(const char *str, char c);
char	*word_dup(char const *str, int start, int finish);
char	**shft_split2(char *s, char c, char ig1, char ig2);
char	*ft_strchr_1(const char *s, char c);
void	shft_after_setter(void);
char	*shft_very_lol(void);

int		shft_cmd_pwd(char *cmd, t_shell_stuff *sh);
int		shft_cmd_env(char *cmd, t_shell_stuff *sh);
int		shft_cmd_echo(char *cmd, t_shell_stuff *sh);
int		shft_cmd_exit(char *cmd, t_shell_stuff *sh);
int		shft_cmd_cd(char *cmd, t_shell_stuff *sh);
int		shft_cmd_unset(char *cmd, t_shell_stuff *sh);
int		shft_cmd_export(char *cmd, t_shell_stuff *sh);

/* ------------------------------- ft_split.c ------------------------------- */
void	surpass_q_dq(char *s, int *x);
int		execution_and_bonus_helper(char **cmds, int *pp,
			t_shell_stuff *sh, int doset);

/* ----------------------------- pipex_main.c ------------------------------- */

void	ft_free_tab(char **tb);
void	pipeft_exit(int arg);
char	*search_path(char *name, t_shell_stuff *sh);
char	**shft_dupenv(t_shell_stuff *sh);
int		shft_putter(char *s1, char *s2, char *s3, int fd);
int		command_fork(char **args, t_shell_stuff *sh, int doset);
int		command(char *cmd, t_shell_stuff *sh, int doset);
char	*shft_get_word(char *in, char end);
void	word_clean(char *str, int len);
void	clean_stuff(char *s, int l);
int		read_stdin(char *limiter, t_shell_stuff *sh);
int		shft_redir_inpt(char *cmd, t_shell_stuff *sh);
int		manage_redir_o(char *filename, int tempfd, char *p, int append);
int		shft_redir_outpt(char *cmd, t_shell_stuff *sh, int *doset);
void	shft_last_parse_1(char **s);
int		shft_redirections(char **cmd, t_shell_stuff *sh, int *doset);
void	builtin_temp_creat(char mode);
int		shft_is_builtin(char *cd);
int		builtin_cmds(char *cd, t_shell_stuff *sh, int doset);
char	*littel_better(char *s);
void	non_executable_handler(char *cmd, t_shell_stuff *sh);
int		check_for_bonus(char *cmd);
char	*clean_cmd(char *str);
int		execution_proccess_and_bonus(int *pp, t_shell_stuff *sh, int doset);
int		execution_proccess_or_bonus(int *pp, t_shell_stuff *sh, int doset);
char	*command_cleaner_and(char *tmp);
void	check_for_operator(char *cmd);
char	*cmd_cleaner(char *tmp, int index, t_shell_stuff *sh);
char	*cmd_parentheses_and_cleaner(char *cmd, int first_para,
			int last_para, t_shell_stuff *sh);
char	*cmd_parentheses_or_cleaner(char *cmd, int first_para,
			int last_para, t_shell_stuff *sh);
char	*check_for_parentheses(char *cmd, t_shell_stuff *sh,
			int *pp, int doset);
int		shft_fr_to(char *cmd, t_shell_stuff *sh, int doset);
int		shft_pipexexec(char **cmds, int pipes, t_shell_stuff *sh);
char	last_exiter(char *cmd);

/* ------------------------------- utils.c ------------------------------- */
int		execution_bonus_helper(char **cmds, int *pp, t_shell_stuff *sh,
			int doset);
void	control_and_bonus(int *fixer, int *doset, int counter);
char	**execution_and_bonus_helper_1(int doset, char **cmds,
			t_shell_stuff *sh, int *pp);
char	**execution_or_bonus_helper_1(int doset, char **cmds,
			t_shell_stuff *sh, int *pp);
char	*cmd_and_cleaner_helper(char *new_cmd, char *cmd, int *j,
			int *last_para);
char	*cmd_or_cleaner_helper(char *new_cmd, char *cmd, int *j,
			int *last_para);
void	parentheses_helper_1(char *cmd, t_shell_stuff *sh, int
			*pp, int doset);
void	parentheses_helper_2(char *cmd);
char	*parentheses_helper_3(char *cmd, t_shell_stuff *sh,
			int *pp, int doset);
char	*shft_ft_tp_helper(int *pp, t_shell_stuff *sh, int doset,
			char *tmp);
char	*shft_ft_tp_helper_1(int *pp, t_shell_stuff *sh, int doset,
			char *tmp);
char	*shft_ft_tp_helper_nizz(int *pp, t_shell_stuff *sh,
			int doset, char *tmp);
void	piperlol(int *pp);
char	shft_redir_syntax_ok(char *cmd, t_shell_stuff *sh);

/* ------------------------------- main_init.c ------------------------------ */
char	*creat_prompt(t_shell_stuff *shell, char *cmd_buff);
t_loco	*loco(void);
void	reset_loco(void);
t_pare	*pare(void);
char	limiter_ok(char **comp, char *limiter);

/* ------------------------------ main_check.c ------------------------------ */
char	fs_check(char fs, char a);
int		shft_ch_one(char **cmd, char *st, int ct);
int		shft_ch_two(char st, char lst, int ct);
int		shft_ch_checkok(char *cmd, t_shell_stuff *sh);

/* -------------------------- parenthesis_pareser.c ------------------------- */
char	*final_check_copy(char *str, int counter);
char	*final_check(char *str);
void	check_for_right_parenthesis_helper(char *s, int *double_first,
			int *open_pare, int *close_pare);
char	*check_for_right_parenthesis(char *s);
char	*better_parenthesis(char *s);

int		executed_command_last(t_shell_stuff *sh, int *pp, int doset, char *cmd);

void	shft_ft_tp_hleper_1_1(char *temp);
void	shft_ft_tp_hleper_1_0(void);

/* ---------------------------- new_parentheses_1 --------------------------- */
char	*command_parentheses_clean(char *cmd);
int		splitted_command_parentheses_clean_1(char *splitted_cmd, int *f);
char	*splitted_command_parentheses_clean(char *splitted_cmd);
char	*status_adding_cmd_cleaning(char *cmd, t_shell_stuff *sh);
void	executed_command(t_shell_stuff *sh,
			int *pp, int doset, char *splitted_cmd);

/* ---------------------------- new_parentheses_2 --------------------------- */
int		executed_command_last(t_shell_stuff *sh, int *pp, int doset, char *cmd);
void	remove_status_operator_1_1(char *cmd, int i);
char	*remove_status_operator_1(char *cmd, char *new_str, int i, int j);
char	*remove_status_operator(char *cmd);
int		shit_helper(char *cmd, int *i);

/* ---------------------------- new_parentheses_3 --------------------------- */
char	*shit(char *cmd, int *i);
int		recursive_cleanup_1(char *cmd, int *i);
void	recursive_cleanup_init(void);
int		recursive_cleanup_2(char *cmd, int *i);
int		recursive_cleanup_3(char *cmd, int *i);

/* ---------------------------- new_parentheses_4 --------------------------- */
char	*recursive_cleanup(char *cmd, int *i);
char	*remove_status_operator_cmd(char *cmd);
char	*status_check_and_clean(char *cmd);
char	*handle_exec_pare(t_shell_stuff *sh, int *pp, int doset, char *cmd);
char	*check_for_parentheses(char *cmd,
			t_shell_stuff *sh, int *pp, int doset);

/* ----------------------------- new_parentheses ---------------------------- */
char	*clean_piece(int f, int l, t_shell_stuff *sh);
void	clean_loco_piece(int first_index, int last_index);
char	*cmd_pare_clean(char *cmd);
char	*split_one_cmd(char *cmd);
void	command_parentheses_clean_1(char *cmd, int i);

/* -------------------------------- utils_1.c ------------------------------- */
void	clean_stuff(char *s, int l);
void	read_stdin_1( void );

#endif
