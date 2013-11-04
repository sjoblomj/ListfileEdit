#include "listfile.h"

////////////////////////////////////////////////////////////////////////////////
// Constructor. Reads the content of filepath and adds each line to the filelist
////////////////////////////////////////////////////////////////////////////////
Listfile::Listfile(string filepath)
{
    char temp[1024];
    string strtemp;
    ifstream is(filepath.c_str());
    is.getline(temp, 1024);
    while(!is.eof())
    {
        strtemp = temp;
        for(string::iterator i = strtemp.begin(); i != strtemp.end(); ++i)
            *i = tolower(*i);
        filelist.push_back(strtemp);
        is.getline(temp, 1024);
    }
    is.close();
}



////////////////////////////////////////////////////////////////////////////////
// Adds the suffix string after each line in the filelist
////////////////////////////////////////////////////////////////////////////////
void Listfile::addSuffix(string suffix)
{
    for(list<string>::iterator i = filelist.begin(); i != filelist.end(); i++)
        *i = *i + suffix;
}



////////////////////////////////////////////////////////////////////////////////
// Adds the prefix string before each line in the filelist
////////////////////////////////////////////////////////////////////////////////
void Listfile::addPrefix(string prefix)
{
    for(list<string>::iterator i = filelist.begin(); i != filelist.end(); i++)
        *i = prefix + *i;
}



////////////////////////////////////////////////////////////////////////////////
// Saves the filelist by creating an ofstream and calling the output() function
////////////////////////////////////////////////////////////////////////////////
void Listfile::save(string filepath)
{
    ofstream out(filepath.c_str());
    output(out);
    out.close();
}



////////////////////////////////////////////////////////////////////////////////
// Writes the content of filelist to the ostream we get as input. We return out
// since it could be cout, and we need to return it to have the operator <<
// function normal.
////////////////////////////////////////////////////////////////////////////////
ostream & Listfile::output(ostream &out)
{
    ostream_iterator<string> strosi(out, "\n"); // Add newline after each line
    copy(filelist.begin(), filelist.end(), strosi);
    return out;
}



////////////////////////////////////////////////////////////////////////////////
// This function will add the lines of newlistclass after the lines in this
////////////////////////////////////////////////////////////////////////////////
void Listfile::append(Listfile &newlistclass)
{
    list<string> newlist = newlistclass.getList();
    list<string> temp;
    newlist.sort();
    filelist.sort();

    // Make list large enough to hold all values
    temp.resize(filelist.size() + newlist.size());
    std::merge(filelist.begin(), filelist.end(), newlist.begin(), newlist.end(), temp.begin());
    filelist = temp;
}



////////////////////////////////////////////////////////////////////////////////
// This function will output a list which is the combination of newlistclass
// and the listfile of this object.
////////////////////////////////////////////////////////////////////////////////
list<string> Listfile::merge(Listfile &newlistclass)
{
    list<string> newlist = newlistclass.getList();
    list<string> output;
    list<string> temp = filelist;
    newlist.sort();
    temp.sort();

    // Make list large enough to hold all values
    output.resize(temp.size() + newlist.size());
    set_union(temp.begin(), temp.end(), newlist.begin(), newlist.end(), output.begin());

    return output;
}



////////////////////////////////////////////////////////////////////////////////
// This function will output a list of all the lines in newlistclass that are
// not in this objects filelist.
////////////////////////////////////////////////////////////////////////////////
list<string> Listfile::extractMissingLines(Listfile &newlistclass)
{
    list<string> newlist = newlistclass.getList();
    list<string> output;
    list<string> temp = filelist;
    newlist.sort();
    temp.sort();

    // Make the list way too big to not run out of items
    output.resize(newlist.size());
    set_difference(newlist.begin(), newlist.end(), temp.begin(), temp.end(), output.begin());
    // output is now the elements in newlist that are not in filelist.

    output.unique();
    return output;
}

list<string> Listfile::search(string searchstr)
{
    for(string::iterator i = searchstr.begin(); i != searchstr.end(); ++i)
        *i = tolower(*i);

    list<string> output;
    for(list<string>::iterator i = filelist.begin(); i != filelist.end(); i++)
        if(string(*i).find(searchstr) != string::npos)
            output.push_back(*i);

    return output;
}

void Listfile::processPatchLst()
{
    size_t FirstColon, SecondColon;
    for(list<string>::iterator i = filelist.begin(); i != filelist.end(); i++)
    {
        FirstColon = (*i).find(";", 0);                    // (*i) is the current line, FirstColon is the first ; in that line
        if(FirstColon != string::npos)                     // If there are no ;'s in the line, do nothing. Keep the line as it is
        {
            SecondColon = (*i).find(";", FirstColon + 1);  // Find the second ; in the line

            if(SecondColon == string::npos)                // We are to remove everything before the ; in the line
                *i = (*i).substr(FirstColon + 1);
            else                                           // We are to remove everything before the first ; and after the second ;
                *i = (*i).substr(FirstColon + 1, SecondColon - FirstColon - 1);
        }
    }
}
