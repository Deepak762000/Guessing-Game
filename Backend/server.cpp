#include "crow.h"
#include "webview.h"
#include <cstdlib>
#include <ctime>
#include <thread>
#include <filesystem>
namespace fs = std::filesystem;

int main(){
    srand(time(0));
    int secret = rand() % 100 + 1;

    std::thread serverThread([&secret](){
        crow::SimpleApp app;

        CROW_ROUTE(app, "/")([](){
            return "C++ Guessing Game API is running"; 
        });

        CROW_ROUTE(app, "/check/<int>")([&secret](int guess){
            crow::response res;
            if (guess < secret){
                res = crow::response(200, R"({"result":"low"})");
            }else if (guess > secret){
                res = crow::response(200, R"({"result":"high"})");
            }else{
                int oldSecret = secret;
                secret = rand() % 100 + 1;
                res = crow::response(200, "{\"result\":\"correct\",\"number\":" + std::to_string(oldSecret) + "}");
            }
            res.set_header("Content-Type", "application/json");
            res.set_header("Access-Control-Allow-Origin", "*");
            return res;
        });

        app.port(8080).multithreaded().run();
    });

    webview::webview w(true,nullptr);
    w.set_title("Guessing Game - Desktop");
    w.set_size(500,400,WEBVIEW_HINT_NONE);

    std::string htmlPath = fs::absolute("C:/Users/pc/Desktop/Programming/App/Guessing_Game/Frontend/index.html").string();
    w.navigate("file:///" + htmlPath);

    w.run();

    serverThread.join();
    return 0;
}