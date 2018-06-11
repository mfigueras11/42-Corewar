/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffloris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 20:35:56 by ffloris           #+#    #+#             */
/*   Updated: 2018/06/10 15:32:08 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

static t_vm			*create_virtual_machine(int argc, char **argv)
{
	t_vm			*vm;

	if (!(vm = (t_vm *)malloc(sizeof(t_vm))))
		error_exit(vm, "Malloc failed, virtual machine creation");
	ft_bzero(vm, sizeof(*vm));
	vm->argv = argv;
	vm->argc = argc;
	vm->dump = -1;
	if (!(vm->memory = ft_strnew(MEM_SIZE)))
		error_exit(vm, "Malloc failed, memory space creation");
	return (vm);
}

int					main(int argc, char **argv)
{
	t_vm			*vm;

	if (argc < 2)
	{
		ft_putstr("Provide 1 or more arguments\n");
		usage(vm, 1);
	}
	vm = create_virtual_machine(argc, argv);
	parse_handler(vm);
	exec_vm(vm);
	test_print(vm); //Remove
	free_virtual_machine(vm);
	return (0);
}
