int main(int argc, char **argv)
{
  /*
    Заменить stdin на pipe fd[1] с помощью dup2
    Затем закрыть stdin с помощью close
    И проверить это */

  int pipe_fds[2];
  int read_fd;
  int write_fd;

  /* создается pipe */
  pipe(pipe_fds);

  /* pipe_fds[0] -> 3 */
  /* pipe_fds[1] -> 4 */
  read_fd = pipe_fds[0];
  write_fd = pipe_fds[1];

  /* на место 0 (stdin) ставится write_fd (замена) */
  dup2(write_fd, 0);

  /* и закрывается лишний fd -> 4
     ибо на месте 0 уже стоит 4 */
  close(write_fd);
  sleep(200);

  /* dup просто возвращает копию дескриптора 3 = dup(3)
     а dup2 осуществляет замену */

  return 0;
}
