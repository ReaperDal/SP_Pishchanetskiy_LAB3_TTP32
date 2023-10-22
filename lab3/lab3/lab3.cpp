#include <iostream>
#include <regex>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;


const string CLASS_NUMBER = "Number";
const string CLASS_STRING = "String const";
const string CLASS_CHAR = "Char const";
const string CLASS_PREPROCESSOR_DIRECTIVE = "Preprocessor Directive";
const string CLASS_COMMENT = "Comment";
const string CLASS_KEYWORD = "KeyWord";
const string CLASS_OPERATOR = "Operator";
const string CLASS_PUNCTUATION = "Punctuation sign";
const string CLASS_IDENTIFIER = "Identifier";
const string CLASS_ERROR = "Error";


struct Lexeme {
    string value;
    string lexemeClass;
};


vector<Lexeme> analyzeLexemes(const string& text) {
    vector<Lexeme> lexemes;
    unordered_map<string, string> regexPatterns = {
        {CLASS_NUMBER, R"(\b\d+(\.\d+)?\b)"},
        {CLASS_STRING, R"(@?\"([^\"\n]*)\")"},
        {CLASS_PREPROCESSOR_DIRECTIVE, R"(\s*using\s+[a-zA-Z_][a-zA-Z0-9_]*(\s*,\s*[a-zA-Z_][a-zA-Z0-9_]*)*\s*)"},
        {CLASS_COMMENT, R"(\/\/[^\n]*|\/\*[\s\S]*?\*\/)"},
        {CLASS_KEYWORD, R"(\b(abstract|as|args|base|bool|break|byte|case|catch|char|checked|class|const|continue|decimal|default|delegate|do|double|else|enum|event|explicit|extern|false|finally|fixed|float|for|foreach|goto|if|implicit|in|int|interface|internal|is|lock|long|namespace|new|null|object|operator|out|override|params|private|protected|public|readonly|ref|return|sbyte|sealed|short|sizeof|stackalloc|static|string|struct|switch|this|throw|true|try|typeof|uint|ulong|unchecked|unsafe|ushort|using|using static|virtual|void|volatile|while|WriteLine|Write|Console)\b)"},
        {CLASS_OPERATOR, R"(\+|\-|\*|\/|\=|\==|\<|\>)"},
        {CLASS_PUNCTUATION, R"(\(|\)|\{|\}|\[|\]|\;|\,)"},
        {CLASS_IDENTIFIER, R"((?!\b(abstract|as|args|base|bool|break|byte|case|catch|char|checked|class|const|continue|decimal|default|delegate|do|double|else|enum|event|explicit|extern|false|finally|fixed|float|for|foreach|goto|if|implicit|in|int|interface|internal|is|lock|long|namespace|new|null|object|operator|out|override|params|private|protected|public|readonly|ref|return|sbyte|sealed|short|sizeof|stackalloc|static|string|struct|switch|this|throw|true|try|typeof|uint|ulong|unchecked|unsafe|ushort|using|using static|virtual|void|volatile|while|WriteLine|Write|Console)\b)(?!(\/\/[^\n]*|\/\*[\s\S]*?\*\/)(?!(@?\"([^\"\n]*)\")))\b[a-zA-Z_][a-zA-Z0-9_]*\b)"}
    };//string m = text;
    for (const auto& entry : regexPatterns) {
        regex pattern(entry.second);
        auto words_begin = sregex_iterator(text.begin(), text.end(), pattern);
        auto words_end = sregex_iterator();
        for (auto i = words_begin; i != words_end; ++i) {
            Lexeme lexeme;
            lexeme.value = i->str();
            lexeme.lexemeClass = entry.first;
            lexemes.push_back(lexeme);
            
            //m.erase(i->position(), i->position() + i->length()-1);
            //text.erase(i->position(), i->position() + i->length());
            //text.replace(i->position(), i->position() + i->length(), "");
        }
    }

    return lexemes;
}


void printLexemeClasses(const vector<Lexeme>& lexemes) {
    for (const auto& lexeme : lexemes) {
        cout << "<" << lexeme.value << ", " << lexeme.lexemeClass << ">\n";
    }
}

int main() {

    string inputProgramText = R"(
using System;
//comment
public class HelloWorld
{
    public static void Main(string[] args)
    {
        int n = 0;
        double pi = 3.14;
        Console.WriteLine("Hello, world!");
    }
}
)";

    vector<Lexeme> lexemes = analyzeLexemes(inputProgramText);
    

    printLexemeClasses(lexemes);

    return 0;
}