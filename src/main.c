#include <locale.h>
#include "./tokenize/Tokenize.h"

int main() {
    setlocale(LC_ALL, "");
    const char inPath[] = "C:\\Users\\ivan\\IdeaProjects\\kalinin\\parsed-6.txt";
    const char outPath[] = "C:\\Users\\ivan\\IdeaProjects\\kalinin\\parsed-tokenized.txt";
    tokenize(inPath, outPath);
    return 0;
}
