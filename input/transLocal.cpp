#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int main() {
    // 创建一个包含文件名的数组
    vector<string> filenames = {"black", "face", "ferret", "fluid", "freq", "stream", "swapt", "comm1", "comm2", "comm3", "comm4", "comm5"};

    for (const string& fname : filenames) {
        FILE* fp_in;
        fp_in = fopen(fname.c_str(), "r");  // 打开输入文件
        if (!fp_in) {
            cerr << "Cannot open " << fname << endl;
            continue;
        }

        FILE* fp_out;
        string out_filename = fname + "_Local";
        fp_out = fopen(out_filename.c_str(), "w");  // 创建输出文件

        int num1;
        char op;
        int addr, startAddr;
        int num2;
        int index = 0;

        while (fscanf(fp_in, "%d %c %x", &num1, &op, &addr) != EOF) {
            if (index == 0) {
                startAddr = addr;
            }

            if (op == 'R') {
                fscanf(fp_in, "%x", &num2);
                fprintf(fp_out, "%d %c 0x%x %x\n", num1, op, startAddr + index, num2);
            } else {
                fprintf(fp_out, "%d %c 0x%x\n", num1, op, startAddr + index);
            }
            index += 1;
        }

        fclose(fp_in);  // 关闭输入文件
        fclose(fp_out);  // 关闭输出文件
    }

    return 0;
}