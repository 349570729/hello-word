
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
    return basic::main(argc, argv);
}