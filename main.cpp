#include <iostream>
#include "code/include/IniParser.hpp"

using namespace std;

int main() {
    string path = "..\\samples\\in\\sample1.ini";
    IniParser parser;
    auto result = parser.parse(path);

    if (result == nullptr) {
        cout << "Failure";
        return EXIT_SUCCESS;
    }


    cout << "gk2 = " << result->get("globalkey2") << endl;
    cout << "gk1 = " << result->get("globalkey1") << endl;
    cout << "sk1 = " << result->get("sectionkey1") << endl;

    auto section1 = result->getSection("section1");
    if (section1 == nullptr) {
        cout << "Failure";
        return EXIT_SUCCESS;
    }

    cout << "subsk1 = " << section1->get("sectionkey1") << endl;
    cout << "subsk2 = " << section1->get("sectionkey2") << endl;
    cout << "subgk1 = " << section1->get("globalkey1") << endl;

    auto section2 = result->getSection("section2");
    if (section2 == nullptr) {
        cout << "Failure";
        return EXIT_SUCCESS;
    }

    cout << "sub2sk1 = " << section2->get("sectionkey1") << endl;
    cout << "sub2sk3 = " << section2->get("sectionkey3") << endl;
    cout << "sub2gk1 = " << section2->get("globalkey1") << endl;


    return EXIT_SUCCESS;
}
