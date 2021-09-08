#include "../../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (0);
	else if (s1 == NULL)
		return (ft_strlen(s2) * -1);
	else if (s2 == NULL)
		return (ft_strlen(s1));
    while (*s1 != '\0' && *s2 != '\0')
    {
        if (*s1 != *s2)
            break ;
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}
