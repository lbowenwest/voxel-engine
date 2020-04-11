#pragma once


int main(int argc, char* argv[]) {
    auto app = engine::create_application();
    app->run();
    delete app;

    return 0;
}