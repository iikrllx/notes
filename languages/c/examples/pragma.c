/* preprocessors #pragma (examples) */
/* --- compiler directive --- */

/* print message while gcc */
#pragma message "Compiling " __FILE__ "..."

/* ON warnings, same $ gcc -Wextra -Wall file.c */
#pragma GCC diagnostic warning "-Wextra"
#pragma GCC diagnostic warning "-Wall"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wextra"
#pragma GCC diagnostic ignored "-Wuse-after-free"
/* code with -Wextra warning here */
#pragma GCC diagnostic pop

/* include this source once (linking) */
#pragma once

#include <stdio.h>
#include <stdlib.h>

int main(void)
{


	return 0;
}
