#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>

char *replace_str(char *str, char *old, char *new)
{
	char *ret, *r;
	const char *p, *q;
	size_t oldlen = strlen(old);
	size_t count, retlen, newlen = strlen(new);

	if (oldlen != newlen) {
		for (count = 0, p = str; (q = strstr(p, old)) != NULL; p = q + oldlen)
			count++;
		/* this is undefined if p - str > PTRDIFF_MAX */
		retlen = p - str + strlen(p) + count * (newlen - oldlen);
	} else
		retlen = strlen(str);

	if ((ret = malloc(retlen + 1)) == NULL)
		return NULL;

	for (r = ret, p = str; (q = strstr(p, old)) != NULL; p = q + oldlen) {
		/* this is undefined if q - p > PTRDIFF_MAX */
		ptrdiff_t l = q - p;
		memcpy(r, p, l);
		r += l;
		memcpy(r, new, newlen);
		r += newlen;
	}
	strcpy(r, p);

	return ret;
}

int main(int argc, char*argv[])
{
    FILE *fp = fopen(argv[1], "r"), ;
    int   c;
    int lines_cnt = 0;
    int  line_idx = 0;
    size_t nbytes;
    char* log_line = (char*)calloc(100, sizeof(char));
    char* start_verbose = NULL;
    char* stop_verbose = NULL;
    char* verbose = NULL;

    while ( (c=fgetc(fp)) != EOF ) {
        if ( c == '\n' )
            lines_cnt++;
    }

    fp = fopen(argv[1], "r");

      while(getline (&log_line, &nbytes, fp)!=EOF){
	   if(strstr(log_line, ": -I")!=NULL && strstr(log_line, "Status")==NULL){
                if((start_verbose = strchr(log_line, ':'))!=NULL){
                        if((stop_verbose = strrchr(log_line, ':'))!=NULL){
				int start_idx = start_verbose - log_line; 
				int stop_idx = stop_verbose - log_line;
				verbose = (char*) calloc(stop_idx - start_idx, sizeof(char));
				strncpy(verbose, log_line + start_idx, (stop_idx - start_idx)+1);
				printf("%s", replace_str(log_line, verbose, ""));
                        }
                }
	    }
	line_idx++;
    }

        return EXIT_SUCCESS;
}

