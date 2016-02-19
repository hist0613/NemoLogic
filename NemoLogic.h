#ifndef NEMOLOGIC_H
#define NEMOLOGIC_H

class NemoLogic {
public:
    bool solve();
    int check_row(int ri);
    int check_col(int ci);
    void input(istream &input);
    void output(ostream &output);

private:
    int row_size, col_size;
    vector< vector<int> > row_hints;
    vector< vector<int> > col_hints;
    vector< vector<int> > board;
};

#endif NEMOLOGIC_H