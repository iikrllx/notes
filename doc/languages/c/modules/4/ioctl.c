/*
 *  ioctl.c - the process to use ioctl's to control the kernel module
 *
 *  Until now we could have used cat for input and output. But now
 *  we need to do ioctl's, which require writing our own process.
 */

#include "chardev.h"

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

void ioctl_set_msg(int file_desc, char *message)
{
	int ret_val;

	ret_val = ioctl(file_desc, IOCTL_SET_MSG, message);

	if (ret_val < 0)
	{
		printf("ioctl_set_msg failed:%d\n", ret_val);
		exit(1);
	}
}

void ioctl_get_msg(int file_desc)
{
	int ret_val;
	char message[100];

	/*
	 * Warning - this is dangerous because we don't tell
	 * the kernel how far it's allowed to write, so it
	 * might overflow the buffer. In a real production
	 * program, we would have used two ioctls - one to tell
	 * the kernel the buffer length and another to give
	 * it the buffer to fill
	 */
	ret_val = ioctl(file_desc, IOCTL_GET_MSG, message);

	if (ret_val < 0)
	{
		printf("ioctl_get_msg failed:%d\n", ret_val);
		exit(1);
	}

	printf("get_msg message:%s\n", message);
}

void ioctl_get_nth_byte(int file_desc)
{
	int i = 0;
	char c;

	printf("get_nth_byte message:");

	do {
		c = ioctl(file_desc, IOCTL_GET_NTH_BYTE, i++);

		if (c < 0)
		{
			printf("ioctl_get_nth_byte failed at the %d'th byte:\n", i);
			exit(1);
		}

		putchar(c);
	} while (c != 0);

	putchar('\n');
}

int main(void)
{
	int file_desc, ret_val;
	char *msg = "(ioctl.c) Message passed by ioctl\n";

	file_desc = open(_DEVICE_NAME, O_RDWR);
	if (file_desc < 0)
	{
		printf("Can't open device file: %s\n", _DEVICE_NAME);
		exit(1);
	}

	// cat /dev/char_dev
	ioctl_get_nth_byte(file_desc);
	ioctl_get_msg(file_desc);

	// echo "(ioctl.c) Message passed by ioctl" > /dev/char_dev
	ioctl_set_msg(file_desc, msg);

	close(file_desc);

	return 0;
}
