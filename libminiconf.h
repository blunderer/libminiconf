
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

