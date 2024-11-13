/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 10:25:07 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/13 03:18:06 by cahaik           ###   ########.fr       */
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
    int		i;
    char	**splited;

    i = 0;
    splited = ft_split(p, ':');
    while (splited && splited[i])
    {
        if (ft_strcmp(*cmd, splited[i]) == 0)
            return (print_error(*cmd, 0, p_, 1), 2);
        else
        {
            if (ft_strcmp(ft_substr(*cmd, 0, ft_strlen(*cmd) 
                        - ft_strlen(ft_strrchr(*cmd, '/'))), splited[i]) == 0 
                && access(*cmd, F_OK | X_OK) == 0)
                return (0);
        }
        i++;
    }
    if (ft_strchr(*cmd, '/'))
        return (print_error(*cmd, 1, p_, 1), 1);
    if (only_cmd(cmd, splited) == 0)
        return (0);
    return (print_error(*cmd, 2, p_, 127), 2);
}

int	search(char **cmd, t_ev *ev, t_status **p)
{
    int		i;
    char	**path;
    int check;
    char *if_dir;
    

    i = 0;
    if_dir = ft_strchr(*cmd, '/');
     if (if_dir)
    {
        if (ft_strcmp(if_dir, ft_strrchr(*cmd, '/')) != 0)
        {
            if_dir = ft_substr(*cmd, 0, ft_strlen(*cmd) - ft_strlen(ft_strrchr(*cmd, '/')));
            if (ft_strcmp(ft_strrchr(*cmd, '/'), "/") == 0)
                 return (print_error(*cmd, 0, p, 1), 2);
            if (access(if_dir, F_OK | X_OK) == 0)
                        return (0);
        }
        else
        {
             if (access(if_dir, F_OK | X_OK) == 0)
                        return (print_error(*cmd, 0, p, 1), 2);
            else if (access(ft_strrchr(if_dir, '/') + 1,  F_OK | X_OK) == 0)
                    return (0);
        }     
    }
    else
    {
        if (access(*cmd, F_OK | X_OK) == 0)
                    return (0);
    }
    while (ev && ev->line)
    {
        if (ft_strncmp("PATH=", ev->line, ft_strlen("PATH=")) == 0)
        {
            path = ft_split(ev->line, '=');
            check = search_bin(cmd, path[1], p);
            if (check == 0)
                return (0);
            else if (check == 2)
                return (2);
        }
        ev = ev->next;
    }
    return (1);
}

void execute_cmd(t_status *p, t_command *root, char	*cmd)
{
    execve(cmd, root->args, &(root->ev->line));
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
    signals(0);
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
   check = search(&root->args[0], root->ev, p);
    if (check == 0)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork");
            (*p)->exit_status = 1;
            exit((*p)->exit_status);
        }
        if (pid == 0)
        {
                cmd = root->args[0];
                if (ft_strrchr(root->args[0], '/'))
                    root->args[0] = ft_strrchr(root->args[0], '/') + 1;
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
    return	;
}
