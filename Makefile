all:
	gcc main.c arc.c unarc.c -o archivator
sanitized: 
	gcc main.c arc.c unarc.c -o archivator -fsanitize=address
