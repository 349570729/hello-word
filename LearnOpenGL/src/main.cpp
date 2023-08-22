
namespace basic {
int main(int argc, char *argv[]);
}
namespace light {
int main(int argc, char *argv[]);
}

int main(int argc, char *argv[])
{
    return light::main(argc, argv);
}