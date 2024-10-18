#include  <iostream>
#include <unistd.h>

namespace basic {
int main(int argc, char *argv[]);
}
namespace light {
int main(int argc, char *argv[]);
}
// namespace light;
// int light::main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	std::cout << "pid: " << getpid() << std::endl;
	if (argc > 1) {
		int sec = atoi(argv[1]);
		std::cout << "enter main, begin sleep for " << sec << "s\n";
		sleep(sec);
	}
    return basic::main(argc, argv);
}
