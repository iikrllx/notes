/*
 *  chardev.h - the header file with the ioctl definitions.
 *
 *  The declarations here have to be in a header file, because
 *  they need to be known both to the kernel module
 *  (in chardev.c) and the process calling ioctl (ioctl.c)
 */

#ifndef CHARDEV_H
#define CHARDEV_H

#ifndef DEBUG
#define DEBUG
#endif

#include <linux/ioctl.h>

/*
 * The major device number. We can't rely on dynamic
 * registration any more, because ioctls need to know
 * it.
 */
#define MAJOR_NUM 100

/*
#define IOCTL_SET_MSG _IOR(MAJOR_NUM, 0, char *)
Создается макрос IOCTL_SET_MSG чтобы использовать его в userspace и kernelspace
передача данных между этими пространствами

_IOR это макрос, используется для создания кода команды IOCTL
Принимает 3 аргумента: номер устройства, номер команды и тип данных,
который будет передан ioctl

_IOR передача информации из userspace к kernelspace
*/

/*
 * Set the message of the device driver
 */
#define IOCTL_SET_MSG _IOR(MAJOR_NUM, 0, char *)

/*
 * Get the message of the device driver
 */
#define IOCTL_GET_MSG _IOR(MAJOR_NUM, 1, char *)
/*
 * This IOCTL is used for output, to get the message
 * of the device driver. However, we still need the
 * buffer to place the message in to be input,
 * as it is allocated by the process.
 */

/*
 * Get the n'th byte of the message
 */
#define IOCTL_GET_NTH_BYTE _IOWR(MAJOR_NUM, 2, int)
/*
 * The IOCTL is used for both input and output. It
 * receives from the user a number, n, and returns
 * Message[n].
 */

#define DEVICE_NAME "char_dev"
#define _DEVICE_NAME "/dev/char_dev"

#endif
