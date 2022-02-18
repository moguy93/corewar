/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:14:20 by moguy             #+#    #+#             */
/*   Updated: 2020/02/20 01:05:01 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

/*
** =============================================================================
** 						ERROR
** =============================================================================
*/

# define BAD_ARGS "Bad arguments."
# define BAD_ID "ID is not between 1 and number of players."
# define BAD_DUMP "Dump value isn't between 1 and INT_MAX."
# define BAD_FILE "File invalid."
# define BAD_FILE_OPEN "Opening of one of the file failed."
# define BAD_FILE_READ "Reading of one of the file failed."
# define BAD_OPT "This option don't exist."
# define BAD_VERBOSE "Verbose value is incorrect."
# define LST_ERR "A process failed to be created, malloc error."
# define MALLOC_ERR "Malloc error."
# define NO_ARGS "No arguments given..."
# define SAME_ID "Some players has the same attributed ID."
# define TOO_MANY_ARGS "Too many arguments for the executable."
# define VM_ERR "Virtual machine error."
# define USAGE "usage"

/*
** =============================================================================
** 						PARSING
** =============================================================================
*/

/*
** =============================================================================
** 						LIMITS
** =============================================================================
*/

# define DUMP_LENGTH 12928
# define MAX_ARGS 32
# define MAX_CYCLE 1000000
# define NB_FUNC 16
# define PAD_LENGTH 4
# define OPT_MAX 7
# define VERB_MAX 31

/*
** =============================================================================
** 						OTHERS
** =============================================================================
*/

# define OPT_A "-a "
# define OPT_D "-d "
# define OPT_N "-n "
# define OPT_NCUR "--ncurses "
# define OPT_STEALTH "--stealth "
# define OPT_S "-s "
# define OPT_V "-v "
# define EXT ".cor"

/*
** =============================================================================
** 						BINARY_MASKS
** =============================================================================
*/

# define MASK_ENCO 0x03
# define MASK_NEG 0x80
# define MASK_FF 0xFF

#endif
