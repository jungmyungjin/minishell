#include "minishell.h"

void redirect_output(char *filename, t_mcb *mcb)
{
    if (mcb->fd_output != STDOUT_FILENO)
        close(mcb->fd_output);
    mcb->fd_output = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
}

void redirect_append(char *filename, t_mcb *mcb)
{
    if (mcb->fd_output != STDOUT_FILENO) // fd_out이 기본이 아닐경우 이전 redirect에서 파일을 오픈했으므로 닫아줘야함
        close(mcb->fd_output); // fd_output으로 복사되었으므로 이제 닫아도 됨.
    mcb->fd_output = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
}

void redirect_input(char *filename, t_mcb *mcb)
{
    int file_open;

    file_open = open(filename, O_RDONLY);
    if (file_open < 0)
        ft_putendl_fd("FILE OPEN INPUT ERROR", STDERR_FILENO);
    else
    {
        if (mcb->fd_input != STDIN_FILENO)
            close(mcb->fd_input);
        mcb->fd_input = file_open;
    }
}

void redirect_heredoc(char *eof_keyword, t_mcb *mcb)
{
    char *line;
    int fd[2];
    int status;

    status = pipe(fd);
    if (status < 0)
        exit(0); // todo
    if (mcb->fd_input != STDIN_FILENO)
        close(mcb->fd_input);
    while (1)
    {
        line = readline("> ");
        if (!strcmp(line, eof_keyword))
        {
            free(line);
            break;
        }
        write(fd[WRITE_END], line, ft_strlen(line));
        write(fd[WRITE_END], "\n", 1);
        free(line);

    }
    close(fd[WRITE_END]);
    mcb->fd_input = fd[READ_END];
}

void execute_redirect(t_redirect *redirect, t_mcb *mcb)
{
    if (redirect->type == OUTPUT)
        redirect_output(redirect->filename, mcb);
    else if (redirect->type == INPUT)
        redirect_input(redirect->filename, mcb);
    else if (redirect->type == HERE_DOCUMENTS)
        redirect_heredoc(redirect->filename, mcb);
    else if (redirect->type == APPENDING_OUTPUT)
        redirect_append(redirect->filename, mcb);
    if (mcb->fd_output < 0) // 0 이하가 나오면 문제 가생긴것.
    {
        ft_putendl_fd("FILE OPEN OUTPUT ERROR", STDERR_FILENO);
        exit(1); // todo: return  cat < 사애 오류.
    }
}
