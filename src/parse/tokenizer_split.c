#include "../../minishell.h"

// 올바른 케이스: "test \" "
int find_single_quotes(const char *line, int i)
{
    while (line[i] != '\0' && line[i] != '\'')
    {
        if (line[i] == '\\' && line[i + 1] == '\'') // backslash
            i++;
        i++;
    }
    if (line[i] == '\0') // 끝이 나올경우
        return (-1); //return error
    return (i);
}

// 올바른 케이스: 'test \' '
int find_double_quotes(const char *line, int i)
{
    while (line[i] != '\0' && line[i] != '\"')
    {
        if (line[i] == '\\' && line[i + 1] == '\"') // backslash
            i++;
        i++;
    }
    if (line[i] == '\0') // 끝이 나올경우
        return (-1); //return error
    return (i);
}

int find_quotes_to_end(char *line, int i)
{
    if (line[i + 1] == '\0') // "이 1개만 나오고 line 이 끝났을 경우
        return (-1);
    if (line[i] == '\"')
    {
        i++;
        i = find_double_quotes(line, i);
        if (i == -1)
            return (-1);
    }
    else if (line[i] == '\'')
    {
        i++;
        i = find_single_quotes(line, i);
        if (i == -1)
            return (-1);
    }
    return (i);
}

int is_space(char c)
{
    if (c == ' ')
        return (1); //true
    return (0); // false
}

int counting_tokens(char *line) {
    int count;
    int i;

    count = 0;
    i = 0;
    while (line[i] != '\0')
    {
        if (is_space(line[i]))
            i++;
        else {
            while (line[i] != '\0' && !is_space(line[i]))
            {
                if (line[i] == '\"' || line[i] == '\'')
                    break;
                i++;
            }
            if (line[i] == '\"' || line[i] == '\'')
            {
                i = find_quotes_to_end(line, i);
                if (i == -1)
                    return (-1);
                i++;
            }
            count++;
        }
    }
    return (count);
}

char *create_token(const char *line, int start, int end) {
    printf("start: %c, end %c\n", line[start], line[end]);
    start++;
    while (start < end)
    {
        printf("%c", line[start]);
        start++;
    }

    return NULL;
}

char **split_line(const char *line, char **tokens, int count)
{
    int i;
    int row;
    int end;

    i = 0;
    row = 0;
    while (line[i] != '\0' && row < count)
    {
        if (line[i] == ' ')
            i++;
        else
        {
            while (line[i] != '\0' && line[i] != ' ')
            {
                if (line[i] == '\"' || line[i] == '\'')
                {
                    end = find_quotes_to_end(line, i);
                    tokens[row++] = create_token(line, i, end);
                    i = end;
                }
                i++;
            }
        }
    }
    tokens[row] = NULL;
    return tokens;
}

char **tokenizer_split(char *line)
{
    int token_count;
    char **tokens;


    if (line == NULL)
        return (NULL);
    token_count = counting_tokens(line);
    printf("token count: %d\n", token_count);
    tokens = (char **)malloc(sizeof(char *) * (token_count + 1));
    if (tokens == NULL)
        allocation_error();
    return split_line(line, tokens, token_count);
}
