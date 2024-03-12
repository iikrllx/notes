/*

- бесконечный цикл
- в цикле происходит ввод символов
- данные символы записываются в буфер
- буфер работает с динамическим выделением памяти
- дальше данный буфер разбивается на лексемы и записывается в указатель на указатель
- далее производится рождение потомка, который выполняет данные лексемы
- есть команды, которые не ищутся в PATH окружения, такие как cd, они встроены

Здесь есть утечки памяти, если играться с ENTER и EOF
а так же SIGINT - джампы

*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <setjmp.h>
#include <assert.h>

#define PROGRAM_NAME "shell"
sigjmp_buf env_buf;

void signal_handler()
{
  siglongjmp(env_buf, 5);
}

void execute_cmd(char **command)
{
  pid_t child;

  switch (child = fork()) {
    case -1:
      fprintf(stderr, "%s: fork error\n", PROGRAM_NAME);
      exit(EXIT_FAILURE);
    case 0:
      if (execvp(*command, command) == -1) {
        fprintf(stderr, "%s: %s: Command not found\n", PROGRAM_NAME, *command);
        exit(EXIT_FAILURE);
      }
    default:
      wait(NULL);
  }
}

char **split_input(char *input)
{
  int buffsize, index;
  char *token, **tokens;
  char *separator;

  index = 0;
  buffsize = 1024;
  separator = " \n\t\r";
  tokens = calloc(buffsize, sizeof(char *));

  if (tokens == NULL) {
    fprintf(stderr, "%s: calloc error\n", PROGRAM_NAME);
    exit(EXIT_FAILURE);
  }

  token = strtok(input, separator);
  while (token != NULL) {
    tokens[index] = token;
    index++;

    if (index >= buffsize) {
      buffsize += 1024;
      tokens = realloc(tokens, buffsize * sizeof(char *));

      if (tokens == NULL) {
        fprintf(stderr, "%s: realloc error\n", PROGRAM_NAME);
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, separator);
  }

  tokens[index] = NULL;
  return tokens;
}

void read_input(char **input_buffer, int bufsize)
{
  int c;

  for (int i = 0; (c = getchar()) != EOF; i++) {

    if (c == '\n') {
      (*input_buffer)[i] = '\0';
      break;
    } else
      (*input_buffer)[i] = c;

    if ((i + 1) >= bufsize) {
      *input_buffer = realloc(*input_buffer, bufsize += 1024);
      assert(*input_buffer != NULL);
    }
  }

  if (c == EOF) {
    printf("\n");
    exit(EXIT_SUCCESS);
  }
}

int main(void)
{
  char *input;
  char **command;
  int bufsize = 1024;

  signal(SIGINT, signal_handler);

  while (1) {
    if (sigsetjmp(env_buf, 1) == 5)
      printf("\n");

    char *current_dir = get_current_dir_name();
    printf("unixsh: %s: ", current_dir);
    free(current_dir);

    input = calloc(bufsize, sizeof(char));
    assert(input != NULL);

    read_input(&input, bufsize);
    command = split_input(input);

    if (*command == NULL)
      continue;

    if (strcmp(*command, "exit") == 0)
      exit(EXIT_SUCCESS);

    execute_cmd(command);

    free(input);
    free(command);
  }

  return 0;
}
