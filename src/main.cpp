#include "application.h"

int main(int argc, char** argv) {
    Application application(640, 480);
    application.Loop();

    return 0;
}