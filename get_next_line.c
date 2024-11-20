/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badal-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:04:01 by badal-la          #+#    #+#             */
/*   Updated: 2024/11/20 14:14:22 by badal-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	
}

#include <stdio.h>

int main(void)
{
	int fd1 = open("fd.txt", O_RDONLY);
	printf("%s", get_next_line(fd1));
}