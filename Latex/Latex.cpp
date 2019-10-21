#include "Latex.hpp"
#include <string>

Latex::Latex(string fn) {
    filename = fn;
    preamble = ofstream(filename + "_Main.tex");
    modules = ofstream(filename + "_Modules.tex");
    count = 0;

    preamble << "\\documentclass{article}" << endl
             << "\\usepackage{geometry}" << endl
             << "\\usepackage[utf8]{inputenc}" << endl;
}

Latex::~Latex() {
    preamble << "\\begin{document}" << endl
             << "\\input{" << filename << "_Modules.tex}" << endl
             << "\\end{document}";
    preamble.close();
    modules.close();
}

void Latex::addModule(string* contents, unsigned int lines) {
    modules << "\\input{" << filename << "_Module" << count << ".tex}" << endl;
    ofstream ofs(filename + "_Module" + to_string(count) + ".tex");

    for (unsigned int i = 0; i < lines; i++) {
        ofs << contents[i] << endl;
    }

    ofs.close();
    count++;
}