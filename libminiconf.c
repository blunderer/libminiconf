/** \file libminiconf.c
 *
 * \author blunderer
 * \email blunderer@blunderer.org
 */

#include <libminiconf.h>

conf_parser_val_t __libminiconf_head = { 0, NULL, NULL, NULL };

static char * conf_parser_strip_line(char * line)
{
	int i = 0;
	char c = line[i];
	char * result = NULL;

	while((c == '\t')||(c == ' ')) c = line[++i];
	if(c == '#') { return result; }
	result = line + i;

	while((c != '\r')&&(c != '\n')&&(c != '\0')) c = line[++i];
	line[i] = '\0';

	return result;
}

static void conf_parser_add_var(char *line, int id)
{
	int i = 0;
	conf_parser_val_t *conf_cell = &__libminiconf_head;
	
	while(conf_cell->next) conf_cell = conf_cell->next;

	conf_cell->next = (conf_parser_val_t*)calloc(1, sizeof(conf_parser_val_t));
	conf_cell = conf_cell->next;
	
	while((line[i] != ' ')&&(line[i] != '\t')) i++;
	line[i++] = '\0';
	while((line[i] == ' ')||(line[i] == '\t')) i++;
	conf_cell->confid = id;
	conf_cell->key = strdup(line);
	conf_cell->val = strdup(line + i);
}

void conf_parser_get_var(void * var, char * name, char * type, int id)
{
	conf_parser_val_t *conf_cell = __libminiconf_head.next;
	while(conf_cell) {
		if(id == conf_cell->confid) {
			if(strcmp(name, conf_cell->key) == 0) {
				if(strcmp(type, "int") == 0) {
					*((int*)var) = atoi(conf_cell->val);
				} else if(strcmp(type, "char") == 0) {
					*((char*)var) = atoi(conf_cell->val);
				} else if(strcmp(type, "char*") == 0) {
					*((char**)var) = conf_cell->val;
				} else if(strcmp(type, "short") == 0) {
					*((short*)var) = atoi(conf_cell->val);
				} else if(strcmp(type, "float") == 0) {
					*((float*)var) = atof(conf_cell->val);
				} else if(strcmp(type, "double") == 0) {
					*((double*)var) = atof(conf_cell->val);
				}
			}
		}
		conf_cell = conf_cell->next;
	}
}

int conf_parser_read_file(char * filename, int id)
{
	char line_buffer[512];
	FILE *f = fopen(filename, "r");
	if(!f) { return -1; }

	while(fgets(line_buffer, 512, f)) {
		char *line = conf_parser_strip_line(line_buffer);
		if(line && strlen(line)) {
			conf_parser_add_var(line, id);
		}
	}

	fclose(f);

	return id;
}

void conf_parser_close_file(int id)
{
	conf_parser_val_t *conf_cell = &__libminiconf_head;
	while(conf_cell->next) {
		if(id == conf_cell->next->confid) {
			conf_parser_val_t *to_be_freed = conf_cell->next;
			conf_cell->next = to_be_freed->next;
			free(to_be_freed->key);
			free(to_be_freed->val);
			free(to_be_freed);
		} else {
			conf_cell = conf_cell->next;
		}
	}
}

#ifdef DEBUG

int main(int argc, char ** argv)
{
	if(argc > 1) {
		char * titi;
		CONF_DECLARE_FILE(argv[1], 1)
		CONF_DECLARE_VAR(toto, char*, "coucou", 1)
		printf("toto = '%s'\n",toto);

		CONF_FOREACH(toto, titi, 1)
			printf("%s = %s\n", toto, titi);
		CONF_END_FOREACH

		CONF_UNDECLARE_FILE(1)
	}
	return 0;
}

#endif


