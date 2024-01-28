#include <iostream>
#include <string>
#include <vector>

void devolveme_gil(std::string str) {
    std::string * ret;
    unsigned * prev;
    unsigned i;
    unsigned j;
    unsigned last;
    unsigned curr;
    unsigned top = 1;
    char let;
    
    for (i = 0; i < str.size(); i++) {
        if(str[i] == '(') {
            top++;
        }
    }
    ret = new std::string[top];
    prev = new unsigned[top];
    curr = 0;
    last = 0;
    j = 0;
    for (i = 0; i < str.size(); i++) {
        let = str[i];
        if (let != ' '){
            if(let == '(') {
                ret[curr] += '#';
                j++;
                prev[j] = curr;
                last++;
                curr = last;
            } else if (let == ')') {
                curr = prev[j];
                j--;
            } else {
                ret[curr] += let;
            }
        }
    }

    for(i = 0; i < top; i++) {
        std::cout << ret[i] << std::endl;
    }

    delete [] ret;
    delete [] prev;
}

int main() {
    std::string str = "1 + T*((4*R + cos(qh)) * ((h%r))) + R*Q - N";
    devolveme_gil(str);
}
