#include <syslog.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char **argv) {
	openlog(NULL, 0, LOG_USER);

	if (argc < 3) {
		syslog(LOG_ERR, "Invalid number of arguments: %d.", argc - 1);
		return 1;
	} else if (argc > 3) {
		syslog(LOG_WARNING, "More than 2 arguments provided, ignoring arguments given after %s.", argv[2]);
	}

	const char* path_to_file = argv[1];
	const char* text_to_write = argv[2];
	
	int fd = open(path_to_file, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR |S_IWGRP | S_IRGRP | S_IROTH);

	if (fd == -1) {
		syslog(LOG_ERR, "Error opening file: %s", strerror(errno));
		return 1;
	}
	
	ssize_t nr = write(fd, text_to_write, strlen(text_to_write));

	if (nr == -1) {
		syslog(LOG_ERR, "Error writing to file: %s", strerror(errno));
		return 1;
	} else {
		syslog(LOG_DEBUG, "Writing %s to %s", text_to_write, path_to_file);
	}
	
	if (close(fd) == -1) {
		syslog(LOG_ERR, "Error closing file: %s", strerror(errno));
		return 1;
	}

	return 0;
}
