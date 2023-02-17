
#include "minishell.h"

int	check_next_position(char first, char second)
{
	if (first == second)
		return (1);
	return (0);
}

int	space_checker(char input_position)
{
	if (input_position != ' ')
		return (0);
	return (1);
}


//aqui nessa função eu aloco memoria para o tamanho do input, mas ele pode variar
//por causa dos bites que vao ser adicionados, por algum motivo está sem leak, mas é bom ficar de olho

char	*input_separator(char *input) //refatorar e passou as linhas
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = ft_calloc (sizeof(char *), ft_strlen(input));
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
		{
			if (input[i - 1] && !space_checker(input[i - 1]))
			{
				str[j] = SEPARATOR;
				str[++j] = input[i];
			}
			if (input[i + 1] && check_next_position(input[i], input[i + 1]))
				str[++j] = input[++i];
			if (input[i + 1] && !space_checker(input[i + 1]))
				str[++j] = SEPARATOR;
		}
		else if (input[i] == '|')
		{
			if(!space_checker(input[i - 1]))
			{
				str[j] = SEPARATOR;
				str[++j] = input[i];
			}
			if (input[i + 1] && !space_checker(input[i + 1]))
				str[++j] = SEPARATOR;
		}
		else if (input[i] != SPACE) //e != quotes // strncmp?
			str[j] = input[i];
		else if (input[i] == SPACE) //!quotes
			str[j] = SEPARATOR;
		i++;
		j++;
	}
	return (str);
}

char	**get_input_matrix(char *input)
{
	char	**input_matrix; //nome ruim
	char	*handled_input;

	handled_input = input_separator(input);
	input_matrix = ft_split(handled_input, SEPARATOR);
	free(handled_input);
	return (input_matrix);
}
