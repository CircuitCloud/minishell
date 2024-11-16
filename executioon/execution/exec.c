/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 10:25:07 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/16 07:10:53 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	only_cmd(char **cmd, char **splited)
{
    int		i;
    char	*join;
    char	*joined;

    i = 0;
    while (splited && splited[i])
    {
        join = ft_strjoin(splited[i], "/");
        joined = ft_strjoin(join, *cmd);
        if (access(joined, F_OK | X_OK) == 0)
        {
            *cmd = ft_strdup(joined);
            return (free(join), free(joined), 0);
        }
        free(join);
        free(joined);
        i++;
    }
    return (1);
}

int	search_bin(char **cmd, char *p, t_status **p_)
{
    char	**splited;
    char *subster;

    splited = ft_split(p, ':');
    if (only_cmd(cmd, splited) == 0)
            return (0);
    if (ft_strchr(*cmd, '/'))
        return (1);
    return (print_error(*cmd, 2, p_, 127), 2);
}

char **store_env(t_ev *ev)
{
    int n;
    t_ev *enm;
    char **env;

    n = 0;
    enm = ev;
    while(ev)
    {
        n++;
        ev = ev->next;
    }
    env = malloc(sizeof(char *) * (n + 1));
    if (!env)
        return (NULL);
    ev = enm;
    n = 0;
    while(ev && ev->line)
    {
        env[n] = ft_strdup(ev->line);
        n++;
        ev = ev->next;
    }
    env[n] = NULL;
    return (env);
}

void execute_cmd(t_status *p, t_command *root, char	*cmd)
{
    execve(cmd, root->args, store_env(root->ev));
    perror(cmd);
    p->exit_status = 1;
    exit (p->exit_status);
}

int redirect_check(t_command *root, t_status **p)
{
    (*p)->newfd_out = dup(1);
    (*p)->newfd_in = dup(0);
    redirection(root, p);
    if ((*p)->check_redir == 1)
        return (1);
    return (0);
}
int status_exec_program(int status)
{
    if (WIFSIGNALED(status))
        return (WTERMSIG(status) + 128);
    else
        return (WEXITSTATUS(status));
}

int if_builtin(t_command *root, t_status **p)
{
    
    if (ft_strcmp(root->cmnd, "echo") == 0)
        echo_(root->args + 1, p);
    else if (ft_strcmp(root->cmnd, "cd") == 0)
        cd_(&(root->ev), root->args[1], p);
    else if (ft_strcmp(root->cmnd, "env") == 0)
        env_(root->ev, p);
    else if (ft_strcmp(root->cmnd, "export") == 0)
        export_(root->args + 1 , &(root->ev), p);
    else if (ft_strcmp(root->cmnd, "pwd") == 0)
        pwd_(root->ev);
    else if (ft_strcmp(root->cmnd, "unset") == 0)
        unset_(&(root->ev), (root->args + 1), p);
    else if (ft_strcmp(root->cmnd, "exit") == 0)
        exit_(root->args + 1, p);
    else
        return (1);
    return (0);
}

void	execute_program(t_command *root, t_status **p)
{
    pid_t	pid;
    char	*cmd;
    int		status;
    int check;

    cmd = NULL;
    if (!ft_strcmp(root->cmnd, "|"))
        return (execute_pipe(root, p));
    if (root->redir && (redirect_check(root, p) == 1))
    {
        last_herdoc_number((*root), 1);
        dup2((*p)->newfd_out, 1);
        dup2((*p)->newfd_in, 0);
        close((*p)->newfd_out);
        close((*p)->newfd_in);
        return ;
    }
    if (if_builtin(root, p) == 0)
    {
        if ((*p)->for_redir_check == 2)
        {
            dup2((*p)->newfd_out, 1);
            dup2((*p)->newfd_in, 0);
            close((*p)->newfd_out);
            close((*p)->newfd_in);
        }
        return ;
    }
    if (root->cmnd && !root->cmnd[0])
    {
        print_error("", 2, p, 127);
        if ((*p)->for_redir_check == 2)
        {
            dup2((*p)->newfd_out, 1);
            dup2((*p)->newfd_in, 0);
            close((*p)->newfd_out);
            close((*p)->newfd_in);
        }
        return ;
    }
   check = search(&root->cmnd, root->ev, p);
    signals(1);
    signal(SIGINT, SIG_IGN);
    if (check == 0)
    {
        pid = fork();
        signals(0);
        if (pid < 0)
        {
            write(2, "minishell : ", 12);
            perror("fork");
            (*p)->exit_status = 1;
            exit((*p)->exit_status);
        }
        if (pid == 0)
        {
                // signal(SIGINT, SIG_DFL);
                cmd = root->cmnd;
                execute_cmd(*p, root, cmd);
        }
        if ((*p)->for_redir_check == 2)
        {
            dup2((*p)->newfd_out, 1);
            dup2((*p)->newfd_in, 0);
            close((*p)->newfd_out);
            close((*p)->newfd_in);	
        }
        waitpid(pid, &status, 0);
        (*p)->exit_status = status_exec_program(status);
    }
    else if (check == 1)
        print_error(root->args[0], 1, p, 127);
}
