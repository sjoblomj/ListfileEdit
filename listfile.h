
#ifndef LISTFILE_H
#define LISTFILE_H

#include <cctype>
#include <fstream>
#include <string>
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;


class Listfile
{
private:
    list<string> filelist;

public:
    Listfile()                          { }
    Listfile(list<string> lst)          { filelist = lst; }
    Listfile(string filepath);
    ~Listfile()                         { }
    void setFileList(list<string> &lst) { filelist = lst; }
    void setFileList(Listfile &lst)     { filelist = lst.getList(); }
    void save(string filepath);
    ostream & output(ostream &out);
    void append(Listfile &newlist);
    void addSuffix(string suffix);
    void addPrefix(string prefix);
    void processPatchLst();
    int size()                          { return filelist.size(); }
    bool empty()                        { return filelist.empty(); }
    void resize(int size)               { filelist.resize(size); }
    void unique()                       { filelist.unique(); }
    void sort()                         { filelist.sort(); }
    list<string> getList()              { return filelist; }
    list<string> search(string searchstr);
    list<string> merge(Listfile &newlist);
    list<string> extractMissingLines(Listfile &newlist);
};

#endif
