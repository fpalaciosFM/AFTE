#ifndef LATEX_HPP
#define LATEX_HPP

#include <fstream>

using namespace std;

class Latex {
   private:
    string filename;
    ofstream preamble;
    ofstream modules;
    int count;

   public:
    Latex(string filename);
    ~Latex();

    void addModule(string* contents, unsigned int lines);
};

#endif /* LATEX_HPP */