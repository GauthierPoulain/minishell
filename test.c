#include <term.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>

int main(int argc, char const *argv[])
{
	char	str[2000];
	int		l;
	struct termios	term;

	tcgetattr(0, &term);
	term.c_cflag &= ~(ECHO | ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);

	tgetent(0, "xterm-256color");

	l = read(1, str, 100);
	write(1, str, l);
	write(1, "\n", 1);
	return (0);
}
