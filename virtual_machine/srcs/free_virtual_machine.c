/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_virtual_machine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 13:55:52 by dhojt             #+#    #+#             */
/*   Updated: 2018/06/06 13:59:59 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void				free_virtual_machine(t_vm *vm)
{
	if (!vm)
		return ;
	if (vm->memory)
		ft_strdel(&(vm->memory));
	// free => vm->name, vm->champ, vm->process;
	free(vm);
}
