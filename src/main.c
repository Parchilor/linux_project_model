#include <string.h>
#include <stdio.h>

#define MAX_CB_LENGTH 256
#define MAX_CB_ITEM 16

struct cbline {
	int count;
//	char *params[MAX_CB_ITEM];
	char **params;
};

static void cb_welcome(struct cbline *cb)
{
	printf("I'm Welcome!\n");
	printf("Hello World!\n");
}

static void cb_reboot(struct cbline *cb)
{
	printf("I'm reboot!\n");
}

static void cb_poweroff(struct cbline *cb)
{
	printf("I'm poweroff!\n");
}

static void cb_help(struct cbline *cb);

const static struct _cb_def{
	char *name;
	void (*proc)(struct cbline*);
	char *help_msg;
}cbs[] = {
	{"help", cb_help, "show all callbacks"},
	{"welcome", cb_welcome, "show \"hello world\""},
	{"reboot", cb_reboot, "reboot the system"},
	{"poweroff", cb_poweroff, "poweroff the PC"},
};

static void cb_help(struct cbline *cb)
{
	int i;
	for(i = 0; i < sizeof(cbs)/sizeof(*cbs); i++)
	{
		printf("%s : %s\n", cbs[i].name, cbs[i].help_msg);
	}
}

static void dispatch(struct cbline *cb)
{
	int i;
	printf("struct .count = [%d], ", cb->count);
	for(i = 0; i < cb->count; i++)
	{
		printf(".params[%d] = %s ", i, cb->params[i]);
	}
	putchar('\n');
	putchar('\n');
	if((!cb->count) || cb->count == 1)
		return;
	for(i = 0; i < sizeof(cbs)/sizeof(*cbs); i++)
	{
		if(!strcmp(cbs[i].name, cb->params[1]))
		{
			cbs[i].proc(cb);
			return;
		}
	}
}

int main(int argc, char *argv[])
{
	struct cbline _cb = {.count = argc, .params = argv};
	printf ("Testing!\n");
	dispatch(&_cb);
	return 0;
}
