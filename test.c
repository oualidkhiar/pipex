#include "libft/libft.h"

int my_strcpy(char *buffer, char *str, char **av, int index)
{
    int i = 0;

    while (str[i])
    {
        buffer[i] = str[i];
        i++;
    }
    if (av[index+1])
    {
        if (ft_strncmp(av[1], av[index+1], ft_strlen(av[1])) != 0)
            buffer[i] = 32;
        return (1);
    }
    else
        return (-1);
}

int count_size_doc(char **av)
{
    int i = 2;
    int  j = 0;
    int ret = 0;

    while(av[i] && ft_strncmp(av[1], av[i], ft_strlen(av[1])) != 0)
    {
        j = 0;
        while (av[i][j])
        {
            j++;
            ret++;
        }
        ret += 1;
        i++;
    }
    return (ret);
}

char *read_from_here_doc(char **av)
{
    char *buffer;
	int i;
    int len = 0;
    char *base_adress;

    buffer = malloc(count_size_doc(av));
	i = 2;
    base_adress = buffer;
	while (av[i] && ft_strncmp(av[1], av[i], ft_strlen(av[1])))
	{
		len = ft_strlen(av[i]);
        if (my_strcpy(buffer, av[i], av, i) == -1)
        {
            ft_putstr_fd("syntext Error!\n", 2);
            exit(-1);
        }
        buffer+=len+1;
		i++;
	}
    buffer = '\0';
    return (base_adress);
}

int main(int ac, char **av)
{
    if (ac < 5)
        return (1);
    char *herdoc = read_from_here_doc(av);
    printf("%s\n",herdoc);
    free(herdoc);
}







char **read_from_here_doc(char **av)
{
    char **buffer;
    int count;

    count = 0;
    buffer = malloc(sizeof(char *) * 1024);
    while (1)
    {
        buffer[count] = get_next_line(0);
        if (ft_strncmp(av[2], "DILE", 4) == 0)
            break ;
        count += ft_strlen(buffer[count]);
    }
    buffer[count] = NULL;
    return (buffer);
}

void child_procces(char **av, int *p_fd1, int *p_fd2, char **env, int i)
{
    int fd;

    if (ft_strncmp(av[1], "here_doc", 8) == 0)
    {
        int i = 0;
        fd = open("from_here_doc", O_RDWR);
		char **buffer;
        buffer = read_from_here_doc(av);
        while (buffer[i])
        {
            write (fd, buffer[i], ft_strlen(buffer[i]));
            i++;
        }
        dup2(fd, 0);
        close(p_fd1[0]);
    }
    else if (i == 0 && ft_strncmp(av[1], "here_doc", 8) != 0)
    {
        fd = ft_open_file(av[1], 0);
        dup2(fd, 0);
        close(p_fd1[0]);
    }
    else
    {
        dup2(p_fd1[0], 0);
		close(p_fd1[1]);
		close(p_fd2[0]);
    }
    dup2(p_fd2[1], 1);
    exec_cmd(av[i+2], env);
}
void parent_procces(char **av, int *p_fd, char **env, int index)
{
	int fd;
	fd  = ft_open_file(av[index], 1);
	dup2(p_fd[0], 0);
	dup2(fd, 1);
	exec_cmd(av[index - 1], env);
}


int main(int ac, char **av ,char **env)
{
    int count = ac - 3; 
    int p_fd[count-1][2];
    int pid;
    int i;

    i = 0;
    while (i < count - 1)
    {
		pipe(p_fd[i]);
        pid = fork();
        if (pid == 0)
		{
			if (i == 0)
            	child_procces(av, p_fd[i], p_fd[i],env, i);
			else
				child_procces(av, p_fd[i - 1], p_fd[i], env, i);
		}
		else
			close(p_fd[i][1]);
		i++;
    }

	waitpid(-1, NULL, 0);
	printf("END\n");
    parent_procces(av, p_fd[i-1], env, ac -1);
}
