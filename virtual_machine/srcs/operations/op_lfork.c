/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 23:03:16 by dhojt             #+#    #+#             */
/*   Updated: 2018/06/06 23:03:24 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void				op_lfork(t_vm *vm, t_process *ps)
{
	t_process		*new_ps;
	int				offset;

	get_next_bytes(vm, ps, &offset, 2);
	duplicate_process(vm, ps, &new_ps);
	insert_sub_process(vm, new_ps);
	get_address(ps, offset, &new_ps->pc);
	new_ps->sleep_cycles = 0;
	new_ps->op = NULL;
	iterate_pc(ps);
}
