#include "Application.h"
#include "Constants.h"

int main(int argc, char** argv) {
    Application application(SCREEN_WIDTH, SCREEN_HEIGHT);
    application.Loop();

    return 0;
}