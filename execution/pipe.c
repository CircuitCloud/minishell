/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:22:35 by cahaik            #+#    #+#             */
/*   Updated: 2024/09/07 09:40:31 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>

// // ex 01 and ex02
// int main()
// {
// 	int fd[2][2];
// 	pid_t pid[2];
// 	char buffer[100];   // Buffer to store the message read by the child
// 	if (pipe(fd[0]) == -1 || pipe(fd[1]) == -1)
// 	{
// 		write(2 , "Error Creating pipe\n", 20);
// 		return (1);
// 	}
// 	pid[0] = fork();
// 	if (pid[0] < 0)
// 	{
// 		write(2, "Fork failed\n", 12);
//         return 1;
// 	}
// 	else if (pid[0] == 0)
// 	{
// 		// Child process
// 		close(fd[0][1]);// Close the write end of the pipe
// 		read (fd[0][0], buffer, sizeof(buffer));// Read from the pipe
// 		printf("child received : %s\n", buffer);
// 		close (fd[1][0]);
// 		write(fd[1][1], "edited\n", 7);
// 		close(fd[1][1]);// Close the write end of the pipe
// 		close(fd[0][0]);// Close the read end of the pipe
// 		return (0);
// 	}
// 	pid[1] = fork();
// 	if (pid[1] < 0)
// 	{
// 		write(2, "Fork failed\n", 12);
//         return 1;
// 	}
// 	else if (pid[1] == 0)
// 	{
// 		return (0);
// 	}
// 		// parent process

// 		// close(fd[0]);
// 		close(fd[0][0]);
// 		write(fd[0][1], "hello , I'm working on pipe\n", 28);// Write to the pipe
// 		close(fd[0][1]);
// 		close(fd[1][1]);
// 		read (fd[1][0], buffer, sizeof(buffer));
// 		printf("Parent received : %s\n", buffer);
// 		close(fd[1][0]);
// 		wait (NULL);
// 		wait(NULL);
// 	return (0);
// }

int main()
{
	int fd[2][2];
	int pid[3];

	if (pipe(fd[0] == -1 || pipe(fd[1]) == -1))
	{
		write(2, "Error creating pipes\n", 21);
		return (1);
	}
	if ((pid[0] = forks()) == -1)
	{
		write(2, "failed to fork\n", 15);
		return (1);
	}
	if (pid[0] == 0)
	{
		close(fd[0][1]);
		read(fd[0][0], )
	}
	 
}