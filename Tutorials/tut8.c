/*/////////////////////////////////////
Q3

man open
man fopen

open (filePath, O_RDONLY)
open (filePath, O_APPEND | O_CREAT)
open (filePath, O_WRONLY)
open (filePath, O_RDWR)

*//////////////////////////////////////



/*/////////////////////////////////////
Q4

typedef struct _graphics {
   int   x;  // x coordinate
   int   y;  // y coordinate
   char  r;  // red level
   char  g;  // green level
   char  b;  // blue level
} Graphics;


int main (void) {
	int picture = open("Picture", O_RDONLY);

	if (picture < 0) error(errno, errno, "No picture");

	int dev = open("/dev/display", O_WRONLY);

	if (dev < 0) error(errno, errno, "No display");

	Graphics point;

	size_t gsize = sizeof(Graphics);
	while(read(picture, &point, gsize) == gsize) {
		display(dev, point);
	}
	close(picture);
	close(dev);
	return 0;
}

*/////////////////////////////////////


/*/////////////////////////////////////
Q5

int addStruct(char *fileName, struct X data) {
	int fd = open(fileName, O_APPEND | O_CREAT);
	if (fd < 0) return -1;
	int nw = write(fd, &data, sizeof(struct));
	close (fd);
	return (nw != sizeof(struct X)) ? -1: 1;
}

*//////////////////////////////////////