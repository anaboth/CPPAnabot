#include <cpr/cpr.h>
#include <iostream>
#include "json.hpp"
#include <string>

using namespace nlohmann;
using namespace std;

string getText(json j){
    return j["result"].at(0)["message"]["text"];
}

int getChatID(json j){
    return j["result"].at(0)["message"]["chat"]["id"];
}

int main(int argc, char** argv) {

    std::string token = "MY TOKEN";
    std::string url = "https://api.telegram.org/bot" + token + "/";

    auto updates = cpr::Get(cpr::Url{url + "getUpdates"});
    json j;
	std::cout << updates.text;
    try {
        std::cout << std::endl << std::endl << std::endl << getText(json::parse(updates.text)) << std::endl << std::endl << getChatID(json::parse(updates.text)) << std::endl;
        auto send = cpr::Get(cpr::Url{url + "sendMessage?chat_id=" + to_string(getChatID(json::parse(updates.text))) + "&text=" + getText(json::parse(updates.text))});
        cout << send.text;
    } catch (int e) {
        std::cout << "deu ruim";
    }
}
