#ifndef _CBREAK_H
#define _CBREAK_H

#include <termios.h>
#include <stdio.h>

int set_cbreak (struct termios *save_termios)
{
  struct termios buf;
  /* Remove line buffering from stdin */
  if (setvbuf (stdin, NULL, _IONBF, 0) != 0)
    return -1;
  /* Store previous terminal settins */
  if (tcgetattr (0, save_termios))
    return -1;
  /* Modify terminal settings. */
  buf = *save_termios;
  buf.c_lflag &= ~(ECHO|ICANON);
  buf.c_cc[VMIN] = 1;
  buf.c_cc[VTIME] = 0;
  /* Set new terminal settings. */
  if (tcsetattr (0, TCSAFLUSH, &buf) < 0)
    return -1;
  return 0;
}

int unset_cbreak (struct termios *save_termios)
{
  /* Return line buffering to stdin. */
  if (setvbuf (stdin, NULL, _IOLBF, 0) != 0)
    return -1;
  /* Return original terminal settings. */
  if (tcsetattr (0, TCSAFLUSH, save_termios) < 0)
    return -1;
  return 0;
}


#endif