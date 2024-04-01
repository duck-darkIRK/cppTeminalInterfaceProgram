#ifndef INTERFACE_H
#define INTERFACE_H

#include<functional>
#include<string>
#include<regex>
#include<iostream>
#include<regex>
#include <cstdlib>
using namespace std;

namespace Program {
    namespace Internal {
        static vector<int> findLeavesOfTree(const vector<int>& tree) {
            vector<int> leaves;

            for (size_t i = 0; i < tree.size(); ++i) {
                // Nếu đỉnh hiện tại không có con sau đó trong cây, nó là lá
                bool isLeaf = true;
                for (size_t j = i + 1; j < tree.size(); ++j) {
                    if (tree[j] > tree[i] * 10 && tree[j] < (tree[i] + 1) * 10) {
                        // Nếu tìm thấy một đỉnh con của đỉnh hiện tại, không phải lá
                        isLeaf = false;
                        break;
                    }
                }
                if (isLeaf) {
                    leaves.push_back(tree[i]);
                }
            }
            return leaves;
        }

        static int vectorToInt(const vector<int>& nums) {
            int result = 0;
            for (int num : nums) {
                result = result * 10 + num;
            }
            return result;
        }

        vector<int> intToVector(int num) {
            vector<int> result;
            
            // Đặc biệt xử lý cho trường hợp số 0
            if (num == 0) {
                result.push_back(0);
                return result;
            }
            
            // Chuyển số nguyên thành vector
            while (num > 0) {
                int digit = num % 10;  // Lấy chữ số cuối cùng
                result.insert(result.begin(), digit);  // Chèn chữ số vào đầu vector
                num /= 10;  // Loại bỏ chữ số cuối cùng đã xử lý
            }
            
            return result;
        }

        static int removeTrailingZeros(int num) {
            while (num % 10 == 0 && num != 0) {
                num /= 10;
            }
            return num;
        }

        static string toUpperCase(const string& str) {
            string result = str;

            // Chuyển đổi chuỗi thành uppercase
            transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
                return toupper(c);
            });

            return result;
        }
    }

    class Script{
        private:
            vector<string> script;
            vector<int> waysToken;
            vector<int> endWaysToken;
            vector<int> depthsToken;
            string title;

            int countDivisions (int number) const {
                int count = 0;
                while (number >= 10) {
                    number /= 10;
                    count++;
                }
                return count;
            }

            string findSpecialString(string input, string regexPattern) const {
                regex pattern(regexPattern);
                smatch match; // Sử dụng smatch để lưu các match groups
                // Tìm kiếm mẫu regex trong chuỗi
                if (regex_search(input, match, pattern)) {
                    return match.str(); // In ra phần được tìm thấy
                } else {
                    return input;
                }
            }

            string removeSpecialCharacters(string input, string regexPattern) const {
                regex pattern(regexPattern);
                string result = regex_replace(input, pattern, "");
                return result;
            }

        public:
            Script() {}
            Script(string input){
                // Structure input like this:
                // Number always < 10;
                //////////////////////////////
                // 1. Path 1\n              //
                // 2. Path 2\n              //
                // 2.1. Path 2.1\n          //
                // 2.1.1. Path 2.1.1\n      //
                // 2.2. Path 2.2\n          //
                // 2.2.1. Path 2.2.1\n      //
                // 2.2.2. Path 2.2.2\n      //
                //////////////////////////////
                istringstream iss(input);
                getline(iss, title);
                cout << title << endl;
                string line;
                int endWaysSave = 0;
                // split input line to array
                while (getline(iss, line)) {
                    script.push_back(line);
                }
                // get ways token
                for (string command : script) {
                    waysToken.push_back(
                        stoi(
                        removeSpecialCharacters(
                        findSpecialString(command, "(\\d+\\.)+"), "\\.")
                        ));
                }
                // get end ways
                endWaysToken = Internal::findLeavesOfTree(waysToken);
                // get depth per token
                for (int token : waysToken) {
                    depthsToken.push_back(countDivisions(token));
                }
            }

            string getTitle() {
                return title;
            }

            int getDepthPath() const {
                int depth = 0;
                for (int ways : endWaysToken) {
                    if (depth < countDivisions(ways)) {
                        depth = countDivisions(ways);
                    }
                }
                return depth + 1;
            }

            string getScriptByToken(int token) const {
                for (int i; i < waysToken.size(); i++) {
                    if (waysToken[i] == token) {
                        return script[i];
                    }
                }
                return "No script data at this Route";
            }

            bool isEndWay(int dir) const {
                for (int i = 0; i < endWaysToken.size(); ++i) {
                    if (endWaysToken[i] == dir) {
                        return true; // Nếu số được tìm thấy trong vector, trả về true
                    }
                }
                return false; // Nếu số không được tìm thấy trong vector, trả về false
            }

            string getScriptByCurrentPath(int path) const {
                string result = "";
                for (int way = 0; way < waysToken.size(); ++way) {
                    if (path == (int) waysToken[way] / 10) {
                        result += script[way] + "\n";
                    }
                }
                return result;
            }


            bool isWay(int dir) const {
                for (int i = 0; i < waysToken.size(); ++i) {
                    if (waysToken[i] == dir) {
                        return true; // Nếu số được tìm thấy trong vector, trả về true
                    }
                }
                return false; // Nếu số không được tìm thấy trong vector, trả về false
            }

            void checkAll() {
                for (int i : waysToken) {
                    cout << "ways token: " << i << endl;
                }

                for (int i : endWaysToken) {
                    cout << "end ways token: " << i << endl;
                }

                for (string i : script) {
                    cout << "script: " << i << endl;
                }

                for (int i : depthsToken) {
                    cout << "depth tokens: " << i << endl;
                }
            }
    };

    class Interface{
        private:
            vector<int> dir;
            Script* mainScript;

            bool checkDepth(int depth){
                if (depth > 3 && depth < 0) {return false;}
                return true;
            }

        public:
            Interface() {}
            Interface(Script &script) : mainScript(&script) {
                // set initial dir state
                for (int i = 0; i < mainScript->getDepthPath(); i++) {
                    dir.push_back(0);
                }
            }

            void resetDirectory() {
                for (int &curentPath : dir) {
                    curentPath = 0;
                }
            }

            void display() const {
                system("cls");
                cout << mainScript->getTitle() << endl;
                cout << mainScript->getScriptByCurrentPath(Internal::removeTrailingZeros(Internal::vectorToInt(dir)));
            }

            bool moveInto(int path) {
                if (mainScript->isWay(Internal::removeTrailingZeros(Internal::vectorToInt(dir))*10 + path)) {
                    for (int &way : dir) {
                        if (!way) {way = path; break;};
                    }
                    return true;
                } else { return false; }
            }

            bool moveBack() {
                if (!dir[0]) { return false; }
                for (int way = dir.size() - 1; way >= 0; way--) {
                    if (dir[way] != 0) {dir[way] = 0; break;};
                }
                return true;
            }

            bool moveTo(int dir) {
                if (mainScript->isWay(Internal::removeTrailingZeros(dir))) {
                    vector<int> newDir = Internal::intToVector(dir);
                    resetDirectory();
                    for (int i = 0; i < newDir.size(); i++) {
                        this->dir[i] = newDir[i];
                    }
                    return true;
                } else { return false; }
            }

            int getDirectory() const {
                return Internal::removeTrailingZeros(Internal::vectorToInt(dir));
            }

            void checkScript() const {
                mainScript->checkAll();
            }
    };

    class InputArgument {
        private:
            Interface *dir;
        public:
            InputArgument() {}
            InputArgument(Interface &dir):dir(&dir) {}
            void inputPath() {
                try {
                    string input;
                    cout << "[C to back][M go to main]" << endl;
                    cout << "Direct to: ";
                    getline(cin, input);
                    if (Internal::toUpperCase(input) == "C") {
                        dir->moveBack();
                    } else if (Internal::toUpperCase(input) == "M") {
                        dir->resetDirectory();
                    } else {
                        dir->moveInto(stoi(input));
                    }
                } catch (...) {cout << "Error" << endl;}
            }

            string inputData(string require) {
                try {
                    string input;
                    cout << "Information is entered in this form: " << endl;
                    cout << "\t" << require << endl;
                    getline(cin, input);
                    return input;
                } catch (...) {cout << "Error" << endl; return "";}
            }
    };

    // global namespace data
    namespace {
        //define user rule function controller
        Script *script;
        Interface *program;
        InputArgument *input;
        bool runningProgram = true;

        bool isRunningProgram() { return runningProgram; }
        void stopProgram() {
            string input;
            getline(cin, input);
            if (input == "C" || input == "c") {
                program->moveBack();
            } else {}
        }
        string getInput(string require) {
            string i = input->inputData(require);
            cout << "[C to back][ENTER to continue]" << endl;
            return i;
        }
        void quitProgram() { 
            runningProgram = false;
            program->resetDirectory();
            system("cls");
        }
        void setDataControl(Script &s, Interface &i, InputArgument &in) {
            script = &s;
            program = &i;
            input = &in;
        }

        int process() {
            return program->getDirectory();
        }
        void goForward(int way) { program->moveInto(way); }
        void goBack() { program->moveBack(); }
        void goTo(int path) { program->moveTo(path); }
    }


    void start(string script, function<void()> action) {
        Script actionScript(script);
        Interface mainProgram(actionScript);
        InputArgument input(mainProgram);
        setDataControl(actionScript, mainProgram, input);
        // mainProgram.checkScript();
        do {
            mainProgram.display();
            if (actionScript.isEndWay(mainProgram.getDirectory())) {
                action();
            } else {
                input.inputPath();
            }
        } while (isRunningProgram());
    }
}


#endif