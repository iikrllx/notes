#include <sys/vfs.h>
#include <linux/magic.h>

int main(int argc, char **argv, char **envp)
{
	struct statfs s;
	if (statfs("/fff", &s))
		abort();

	switch (s.f_type)
	{
		case EXT4_SUPER_MAGIC:
			puts("good");
	}

	return 0;
}
