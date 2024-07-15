/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:21:27 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:17 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>

# define CMD 1
# define PIPE 2
# define AND 3
# define OR 4
# define REDIR 5
# define ACCOL 6
# define APPEND 7
# define HERE_DOC 8
# define OPTION 9
# define CH_MD 10

# define IN_CHILD 1
# define NOT_IN_CHILD 0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 24
# endif

typedef struct s_env
{
	char			*name;
	char			*value;
	int				assg_opr;
	int				i_in_ou;
	int				flag;
	struct s_env	*next;
}			t_env;

typedef struct s_strt
{
	struct s_strt	*prev;
	char			*str;
	char			*command;
	int				*pr_exec;
	int				pr_exec_size;
	int				type;
	int				here_doc_fd;
	char			**option;
	char			**redirect;
	char			**here_doc;
	char			**delemiter;
	char			**append;
	char			**in_file;
	char			**ou_file;
	int				cmd_flag;
	int				*ofile_flag;
	int				ofile_flag_size;
	int				*ifile_flag;
	int				ifile_flag_size;
	int				*var_qts;
	int				var_qts_size;
	int				var_qts_dejavu;
	int				opt_flag;
	int				exit_cmd_flag;
	struct s_strt	*chil_cmd;
	char			*delem_1[7];
	char			*delem_2[7];
	int				expandable;
	struct s_strt	*next;
}			t_strt;

typedef struct s_mini
{
	int				exit_s;
	t_strt			*stack;
	t_env			*env;
	char			*secure_pwd;
	int				sec_fd[2];
	int				pipe_fd[3];
	int				here_doc_fd[2];
	struct s_mini	*next;
}			t_mini;

typedef struct s_vars
{
	int		i_dice_1;
	int		i_dice_ou;
	int		i_dice_in;
	int		i_dice_redr;
	int		fd_in;
	int		fd_out;
	int		sec_in;
	int		sec_out;
	int		exit_status;
	int		pid;
	int		f;
}	t_vars;

typedef struct s_vars2
{
	int		i;
	int		j;
	char	**tmp;
	int		sp_cnt;
	char	*str;
	char	*var;
	int		size;
	int		x;
	int		ss;
	int		echo_flag;
	char	*exp_var;
}	t_vars2;

typedef struct s_vars3
{
	int		start;
	char	*expanded_var;
	int		end;
	int		n;
	int		f;
	t_env	**env;
	char	*str;
	int		var_size;
	int		new_line;
}	t_vars3;

typedef struct s_vars4
{
	t_mini	*shell;
	t_strt	*p_stack;
	int		fd[2];
}	t_vars4;

// Builtins
	// builtins_1.c
int		builtin_echo(t_strt *stack);
int		build_env(t_env **env, t_mini *shell);
char	*ft_rm_quotes(char *s, t_strt *p_tr, int flag);
	// builtins_2.c
int		build_unset(t_env **env, char **p__splt);
int		build_export(t_env **env, char **p__splt, t_mini *shell);
void	*ft_value_changer(t_env *env, char *str, int i_dice, int flag);
	// builtins_3.c
int		builtin_cd(t_strt *stack, t_env *env, t_mini *shell);
	// builtins_4.c
char	**env_to_char(t_env **env);
char	*get_path(t_env **env, char *cmd);
void	*cmd_extend(t_strt *stack, int *j, char ***tmp);
	// builtins_5.c
int		exec_cmd(t_strt *stack, t_mini *shell, int fd_in, int fd_out);
	// builtins_6.c
int		builtin_exit(t_mini *shell, char **p__tr, int exit_cmd_f);
	// builtins_7.c
int		builtin_pwd(char *secure_pwd);
int		is_build_in(t_strt *node, t_mini *shell);
void	*ft_change_old_pwd(t_env **env, char *npwd);
void	build_error(char *command_build, char *identifier);
	// builtins_8.c
void	ext_err(char *str);
void	ft_putstr_fd(char *s, int fd);
void	*malloc_failure(t_mini *shell, char **str);
int		check_empty(t_mini *shell, t_strt *node, char **str, int i);
char	**ft_get_options(t_strt *stack, t_mini *shell, char **tmp, int j);
	// here_doc.c
int		execute_here_doc(t_strt *stack, int *ex_stat, int i, t_mini *shell);
void	vars_init4(t_vars4 *v, int *exit_status, t_mini *shell);
	// here_doc_utils.c
int		find(char *s, char *c);
int		close2(int fd_in, int fd_out);
void	custom_error(char *cmd, char *err_msg, char *err_cmd);
void	vars_init4(t_vars4 *v, int *exit_status, t_mini *shell);
	// wild_card.c
int		ft_is_wild(char *str, t_strt *node);
char	**get_options(t_strt *stack, t_mini *shell);
int		ft_in_arr(int n, t_strt *p_tr, int *arr, int size);
char	**wild_card(char *str, t_strt *p_tr, int *wild_card, char *old_str);

// env
	// env_1.c
t_env	*env_init(char **env);
void	*env_add(t_env **lst, t_env *new);
	// env_2.c
char	*ft_strdup(char *s1);
int		env_find(t_env *env, char *name);
t_env	*env_new(char *content, int assg_opr);
void	env_add_front(t_env **lst, t_env *new, t_mini *shell);
	// env_3.c
int		env_shlvl_warning(int shlvl);
void	*env_oldpwd_exit_status(t_env **p__env);
void	*env_value_modifie(t_env *env, char *str);
int		here_doc_file(t_strt *node, t_mini *shell);

// executer
	// executer_.c
int		len_2d(char **array);
void	*ft_sort_env(t_env *env);
void	unset_var(t_env **env, char *var);
int		executer_phase(t_mini *shell, t_strt *node, int in_child);
	// executer_1.c
void	ft_sort_2d(char **p__tr);
int		ft_stack_len(t_env *p_env);
char	*ft_char_check(char *str, char c);
int		env_name_check(t_env *env, char *name);
void	exct_affch_export(t_env *env, char **p__tr);
	// executer_2.c
int		check_varname(char *str);
int		ft_strcmp(char *str_1, char *str_2);
int		ft_strcmp_value(char *str_1, char *str_2);
void	*env_handle___soon(t_strt *node, t_env *env, void *p_tmp);

// Execution
	// global_exec_1.c
void	vars_init(t_vars *v);
int		file_with_cmd(t_strt *node, t_vars *v, t_mini *shell, int hdrc_dice);
	// global_exec_2.c
int		file_without_cmd(t_strt *node, t_vars *v);
int		buitins_dup(t_strt *node, t_vars *v, int f, t_mini *shell);
	// global_exec_3.c
t_strt	*accol_checker(t_strt *stack, int *accol_count);
int		builtin_execve(t_mini *shell, t_strt *node, int in_child);
	// global_exec_4.c
t_strt	*cp_node(t_strt *node);
t_strt	*ft_lstlast(t_strt *lst);
void	executer_start(t_mini *shell);
	// global_exec_5.c
t_strt	*executer_convert(t_mini *shell, t_strt *stack);
int		cmd_ignore(t_strt **p_stack, int *lst_cmd_exec, int exit_status);
int		redir_after(t_strt **p_stack, t_vars *v, int *exit_status,
			t_mini *shell);
	// global_exec_6.c
int		recursion_func(t_mini *shell, t_strt *p_stack, int lst_cmd_exec,
			t_strt **lst_cmd);
	// global_exec_7.c
void	close_red_fd(t_vars *v);
int		*pipe_b_or_a(t_mini *shell, t_strt *p_stack,
			int fd[], int sec_in_out[]);
void	set_exit_cmd_flag(t_strt *p_stack, int flag);
void	*env_handle__(t_strt *node, t_env *env, char **p__tr, void *p_tmp);
	// global_exec_8.c
void	cmd_w_pipe_wait(struct termios *attr, int *exit_status, int *flag);
void	sec_in_out_init(t_mini *shell, int sec_in_out[3], int lst_cmd_exec);
void	cmd_with_pipe_bef_soon(t_vars4 *v, int sec_in_out[], int *lst_cmd_exec,
			int *exit_status);
void	exp_caller(t_mini *shell, t_strt *p_stack);
char	*init_vars(t_strt **node, int *wild_flag, t_mini *shell, char *str);

// Expanding
	// expander.c
void	sec_close(t_mini *shell, int sec_in_out[]);
int		*ft_alloc_int_arr(t_strt *stack, int type);
char	*ft_expander(char *s, t_env **env, t_strt *p_tr, char *expanded_var);
	// expander_utils.c
int		aln(int c);
int		ft_isdigit(int c);
int		ft_between_sqts(char *s, int idx);
int		ft_between_dqts(char *s, int idx);
char	*ft_get_from_env(t_env **env, char *var);
	// expander_utils_2.c
char	*calc_words(char *s, t_vars2 *v);
void	*bind_vars(t_strt *p_tr, t_vars2 *v, t_vars3 *v3);
int		check_ambig(char *s, t_vars2 *v, t_vars3 *v3, t_strt *p_tr);
void	exp_echo_flag(t_strt *p_tr, t_vars2 *v2, t_vars3 *v3, char *s);
	// expander_var.c
void	var_end(char *p, t_vars3 *v3, int *i);
void	*vars_init_2(t_vars2 *v, t_vars3 *v3, char *s);
void	vars_init_3(t_vars3 *v3, t_env **env, char *expanded_var, char *s);
int		hrd_ex(t_mini *shell, t_strt *p_stack, int ex_st);
int		check_pipe(t_strt *p_stack);

//	fill
	// fill_space.c
int		fill_space(t_strt *stack);
int		fill_compare(t_mini *shell, t_strt *node, char **dels, char **str);
	// fill_.c
int		fill_phase(t_mini *shell);
char	*ft_realloc_with_space(char *str, int i_dice_space);
	// fill_utils_1.c
int		*ft_realloc_arr(t_strt *stack, int type);
char	**ft_realloc_2d(char **o__pt, char *new_opt);
int		*ft_ralloc_ifile_flag(t_strt *stack, int type);
int		*ft_ralloc_ofile_flag(t_strt *stack, int type);
	// fill_utils_2.c
int		ft_check_qts(char *str, int i_dice);
int		ft_check_delm(char *cmd, char *d_lemiter[]);
void	ft_decal_value(int *array, int size, int value);
void	*ft_type_special(t_strt *stack, char *str, int del_dice);
	// fill_inou_file.c
void	*fill_opt(t_strt **node, char *str, t_mini *shell, int i);
void	*fill_in_file(t_strt **node, char *str, t_mini *shell, char *s_str);
void	*fill_ou_file(t_strt **node, char *str, t_mini *shell, char *s_str);
void	*fill_cmd_type(t_strt **node, char *str, t_mini *shell, int i);

//	parser
	// parser_.c
int		parser_phase(t_mini *shell, int hrdc_flag);
int		parser_here_doc(t_strt *node, t_env *env, t_mini *shell);
	// parser_accol.c
int		parser_accol(t_mini *shell, t_strt *stack, int flag, int hrdc_flag);
	// parser_sq_dq_red_app_herd.c
int		parser_error_after_accol(t_mini *shell, t_strt *node, char **p__tr,
			int hrdc_flag);
int		parser_sq_dq_red_app_herd(t_strt *stack, char **p__tr, int hrdc_flag,
			t_mini *shell);
	// parser_error.c
int		parser_spc_err_2(t_mini *shell);
void	*parser_err_synt(char *str, int hrdc_flag);
int		parser_spc_err_1(t_mini *shell, t_strt *node, char **p__tr,
			int p__dice);
int		parser_spc_err(t_mini *shell, t_strt *node, char **p__tr, int p__dice);

// token
	// token_.c
t_strt	*token_phase(char *cmd);
char	*get_name(t_mini *shell);
	// token_utils_1.c
int		ft_strlen(char *str);
char	**free_echoue(char **p, int i_final);
int		ft_strcmp_delm(char *str, char *delem);
void	ft_strncpy(char *dst, char *src, int size);
int		ft_strncmp(char *str_1, char *str_2, int size);
	// token_utils_2.c
int		ft_is_delm(char *str, char *c[]);
int		ft_check_qts(char *str, int i_dice);
t_strt	*ft_lstnew(char *content, int size);
int		ft_lstadd_back(t_strt **lst, t_strt *new);
int		ft_is_there(char *cmd, char *delem[], int btw_quotes);

// utils
	// ft_.c
char	*ft_strrchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
char	*ft_strnstr(const char *haystack, char *needle, int len);
	// ft_2.c
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
int		ft_calc(int n);
	// ft_3.c
void	free_env(t_env *env);
void	free_shell(t_mini *shell);
void	ft_dup_sec(t_mini *shell);
void	free_stack(t_strt *stack, t_strt *p_stack);
void	*check_for_space(t_vars2 *v, t_vars3 *v3, char *s);
	// ft_split.c
int		is_space_(int a, int c);
char	**ft_split(char *s, char c);
char	**ft_split1(char *s, char c);
char	**ft_split3(char *s, char c, t_strt *node);
	// ft_split2.c
char	**ft_split2(char *s, char *c[]);
void	main_sigint(int signal);

//get_line

size_t	ft_strlenn(const char *c);
char	*get_next_line(int fd);
char	*ft_strchrr(const char *s, int c);
char	*ft_strjoinn(char *s1, char *s2);
char	*ft_getstrr(char *s);
char	*ft_getsecondd(char *s);
char	*ft_allocat2(int size, char **s1, char **s2);
char	*ft_allocat(char **str, int s);
int		f(char **str, char **buffer, int size);

#endif
