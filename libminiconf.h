/*
 * Copyright 2010  blunderer <blunderer@blunderer.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 *  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CONF_PARSER_H
#define CONF_PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CONF_DECLARE_VAR(name, type, def, id)	type name = def; conf_parser_get_var(&name, #name, #type, id);
#define CONF_DECLARE_FILE(name, id)		conf_parser_read_file(name, id);
#define CONF_UNDECLARE_FILE(id)			conf_parser_close_file(id);
#define CONF_FOREACH(k, v, id)			{ \
							conf_parser_val_t *__conf_cell = __libminiconf_head.next; \
							while(__conf_cell) { \
								if(__conf_cell->confid == id) { \
									k = __conf_cell->key; \
									v = __conf_cell->val;
#define CONF_END_FOREACH					} \
								__conf_cell = __conf_cell->next; \
							} \
						}

typedef struct _conf_parser_val
{
	int confid;
	char * key;
	char * val;
	struct _conf_parser_val * next;
} conf_parser_val_t;

int conf_parser_read_file(char * filename, int id);
void conf_parser_get_var(void * var, char * name, char * type, int id);
void conf_parser_close_file(int id);

extern conf_parser_val_t __libminiconf_head;

#endif /* CONF_PARSER_H */

