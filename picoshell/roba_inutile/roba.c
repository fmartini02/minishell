/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roba.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:04:21 by fmartini          #+#    #+#             */
/*   Updated: 2024/03/26 17:04:40 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_get_cont_var(char *env_var_line, int j)
{
	int		index;
	char	*ret_str;

	index = 0;
	while (env_var_line[j] != '=' && env_var_line[j] != '\0')//skipping var name
		j++;
	if (env_var_line[j] == '=')//skipping '='
		j++;
	ret_str = malloc(sizeof(char) * (ft_word_len(env_var_line, j) + 1));
	if (!ret_str)
		return NULL;
	while (env_var_line[j] != '\0')
		ret_str[index++] = env_var_line[j++];//copying var value
	ret_str[index] = '\0';//ending string
	return (ret_str);
}
