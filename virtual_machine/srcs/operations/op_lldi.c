/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 23:03:38 by dhojt             #+#    #+#             */
/*   Updated: 2018/06/19 15:39:05 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

static void			load_bytes(t_vm *vm, t_process *ps, int reg, int start)
{
	int				i;

	i = 0;
	ps->r[get_r(reg)] = 0;
	while (i < REG_SIZE)
	{
		ps->r[get_r(reg)] <<= 8;
		ps->r[get_r(reg)] |= (unsigned char)vm->memory[(start + i) % MEM_SIZE];
		i++;
	}
}

void				op_lldi(t_vm *vm, t_process *ps)
{
	unsigned char	encoded;
	int				bytes;
	int				p1;
	int				p2;
	int				p3;

	ft_printf("Inside op_lldi\n");
	p1 = 0;
	p2 = 0;
	p3 = 0;
	modify_pc_tmp(ps, 1);
	encoded = vm->memory[ps->pc_tmp];
	bytes = (decode_byte(encoded, 1) == REG_CODE) ? 1 : 2;
	get_next_bytes(vm, ps, &p1, bytes);
	get_reg_value(vm, ps, decode_byte(encoded, 1), &p1);
	bytes = (decode_byte(encoded, 2) == REG_CODE) ? 1 : 2;
	get_next_bytes(vm, ps, &p2, bytes);
	get_reg_value(vm, ps, decode_byte(encoded, 2), &p2);
	get_next_bytes(vm, ps, &p3, 1);
	get_address(ps, p1 + p2, &p2);
	load_bytes(vm, ps, p3, p2);
	modify_carry(ps, ps->r[get_r(p3)]);
	iterate_pc(ps);
}
