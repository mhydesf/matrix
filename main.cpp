#include <cstddef>
#include <locale>

#include <application.h>

int main(int argc, const char** argv) {
    using namespace Matrix::Application;

    // std::locale::global(std::locale("en_US.UTF-8"));
   
    Application app{std::chrono::milliseconds(50)};
    app.Run();

    return 0;
}

