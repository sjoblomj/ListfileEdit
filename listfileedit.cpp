#include <iostream>
#include "listfile.h"
using namespace std;

// Compile with:
// g++ -pedantic -Wextra -Wall -o listfileedit listfile.cpp listfileedit.cpp

int main()
{
    bool quit = false;
    while(!quit)
    {
        int choice;
        cout << "\n== ListfileEdit 0.9 ==\nby Ojan. Written 2009-05-10\n\n";
        cout << "[0] Help\n";
        cout << "[1] Add prefix (directory) to listfile\n";
        cout << "[2] Add suffix (extension) to listfile\n";
        cout << "[3] Process patch.lst\n";
        cout << "[4] Compare two files and display differences or merge them\n";
        cout << "[5] Sort list alphabetically\n";
        cout << "[6] Remove duplicate lines\n";
        cout << "[7] Search for string in a listfile\n";
        cout << "\n[8] Quit\n\n";
        cin >> choice;

        switch(choice)
        {
        case 0:
        {
            bool subquit = false;
            while(!subquit)
            {
                cin.ignore(1);
                cout << "\n== Choose a help topic ==\n\n";
                cout << "[0] Learn more about MPQ archives and listfiles\n";
                cout << "[1] Learn more about patch.lst\n";
                cout << "[2] Learn more about this program\n";
                cout << "\n[3] Back\n\n";
                int temp;
                cin >> temp;

                switch(temp)
                {
                case 0:
                {
                    cout << "MPQ files are archive files used in all of Blizzard Entertainments games from \n";
                    cout << "Diablo I and newer. They can be compared with zip-files, in other words, one \n";
                    cout << "MPQ file contains many files with game data in it. The MPQ archives don't \n";
                    cout << "contain any names of the files inside, however. In order to see the name of the \n";
                    cout << "files inside the MPQs, a listfile is needed. These are simply a long text file \n";
                    cout << "containing the names of the files inside the MPQs. In (most?) newer games from \n";
                    cout << "Blizzard, there is a listfile inside the MPQ archive which is more or less \n";
                    cout << "complete. For older games and for those files with incomplete listfiles, \n";
                    cout << "however, external listfiles are still needed.\n\n";
                }
                break;
                case 1:
                {
                    cout << "patch.lst are files that are present in most (all?) semi-recent patches to \n";
                    cout << "Blizzard's games. The *.exe-patches themselves contain an MPQ archive with the \n";
                    cout << "updated game data, and one of the files in the MPQ is patch.lst. This file is \n";
                    cout << "basically a listfile of the files in the MPQ archive inside the patch file. This\n";
                    cout << "is relevant, because many times, a new patch introduces new file paths that are \n";
                    cout << "not present in the listfiles that have previously been used. Thus, in order to \n";
                    cout << "get a more complete listfile, the content of the patch.lst needs to be merged \n";
                    cout << "with the old listfile. The only problem is that patch.lst contains other data \n";
                    cout << "as well, appart from the file names which we want. This program has an option \n";
                    cout << "to remove this other data, thus stripping patch.lst from all rubbish and get \n";
                    cout << "only the filenames which we are interested in.\n\n";
                }
                break;
                case 2:
                {
                    cout << "This program was written to manage listfiles. It gives the user powerful \n";
                    cout << "options to manage a set of different listfiles. The program has support for \n";
                    cout << "finding differences between listfiles, merge them, finding the unique files in \n";
                    cout << "different listfiles, sorting them, etc. The program can add both suffixes and \n";
                    cout << "prefixes to each line in a listfile and can search in a listfile for a string, \n";
                    cout << "which will output all lines that match.\n";
                }
                break;
                default:
                    subquit = true;
                }
            }
        }
        break;
        case 1:
        {
            cin.ignore(1);
            char inputpath[256];
            cout << "\nYou are about to add a prefix (directory) \n";
            cout << "to each line of the listfile. Type in the \n";
            cout << "path to the listfile here:\n";
            cin.getline(inputpath, 256);

            Listfile list(inputpath);


            char prefix[256];
            cout << "\nEnter the prefix (directory) you want to add \n";
            cout << "to each line. Make sure not to forget the \\ if \n";
            cout << "you are adding a directory\n";
            cin.getline(prefix, 256);

            list.addPrefix(prefix);

            char outputpath[256];
            cout << "\nDone! Enter the name of the file to save to:\n";
            cin.getline(outputpath, 256);
            list.save(outputpath);
        }
        break;
        case 2:
        {
            cin.ignore(1);
            char inputpath[256];
            cout << "You are about to add a suffix (file-extension) \n";
            cout << "to each line of the listfile. Type in the \n";
            cout << "path to the listfile here:\n";
            cin.getline(inputpath, 256);

            Listfile list(inputpath);


            char suffix[256];
            cout << "\nEnter the suffix (extension) you want to add \n";
            cout << "to each line. Make sure not to forget the . if \n";
            cout << "you are adding a file extension.\n";
            cin.getline(suffix, 256);

            list.addSuffix(suffix);

            char outputpath[256];
            cout << "\nDone! Enter the name of the file to save to:\n";
            cin.getline(outputpath, 256);
            list.save(outputpath);
        }
        break;
        case 3:
        {
            cin.ignore(1);
            char inputpath[256];
            cout << "You are about to process patch.lst. They are  \n";
            cout << "listfiles that are present in most (all?) semi-recent \n";
            cout << "patches to Blizzard's games. This function will strip \n";
            cout << "patch.lst of unneccessary details and only keep the \n";
            cout << "file names of the patches' content, i.e. creating \n";
            cout << "a working listfile out of patch.lst. So, type in the \n";
            cout << "path to the patch.lst file you want to process:\n";
            cin.getline(inputpath, 256);

            Listfile list(inputpath);
            list.processPatchLst();

            char outputpath[256];
            cout << "\nDone! Enter the name of the file to save to:\n";
            cin.getline(outputpath, 256);
            list.save(outputpath);
        }
        break;
        case 4:
        {
            cin.ignore(1);
            char filepath1[256];
            char filepath2[256];
            cout << "\nYou can here choose to compare two listfiles and if you\n";
            cout << "wish, display a list of differences between them. If they\n";
            cout << "are different, you can also choose to merge them into one.\n";
            cout << "First type in the path to the first file and press ENTER,\n";
            cout << "then type in the path to the second file followed by ENTER\n";
            cin >> filepath1;
            cin >> filepath2;
            cin.ignore(1);

            Listfile list1(filepath1);
            Listfile list2(filepath2);
            Listfile list1uniques = list2.extractMissingLines(list1);
            Listfile list2uniques = list1.extractMissingLines(list2);

            int nr;
            bool subquit = false;
            while(!subquit)
            {
                cout << "\n\n";
                cout << "[0] Merge the files\n";
                cout << "[1] Display the lines in " << filepath1 << " that are not present in " << filepath2 << "\n";
                cout << "[2] Display the lines in " << filepath2 << " that are not present in " << filepath1 << "\n";
                cout << "[3] Quit\n";

                cin >> nr;
                cin.ignore(1);

                switch(nr)
                {
                case 0:
                {
                    Listfile list_out(list1.merge(list2uniques));

                    int nr2;
                    bool subquit2 = false;
                    while(!subquit2)
                    {
                        cout << "\n\nThe files have been merged.\n";
                        cout << "[0] Save the file without sorting or removing duplicate lines\n";
                        cout << "[1] Save the file after sorting and removing duplicate lines\n";
                        cout << "[2] Display the file\n";
                        cout << "[3] Quit - Don't save the file\n";

                        cin >> nr2;
                        cin.ignore(1);

                        switch(nr2)
                        {
                        case 0:
                        {
                            char mergedfilepath[256];
                            cout << "\nEnter path to save to:\n";
                            cin.getline(mergedfilepath, 256);

                            list_out.save(mergedfilepath);
                            subquit = true;
                            subquit2 = true;
                        }
                        break;
                        case 1:
                        {
                            char mergedfilepath[256];
                            cout << "\nEnter path to save to:\n";
                            cin.getline(mergedfilepath, 256);

                            list_out.sort();
                            list_out.unique();
                            list_out.save(mergedfilepath);
                            subquit = true;
                            subquit2 = true;
                        }
                        break;
                        case 2:
                        {
                            cout << " **\n";
                            list_out.output(cout);
                            cout << " **\n";
                        }
                        break;
                        default:
                            subquit2 = true;
                        }
                    }
                }
                break;
                case 1:
                {
                    cout << " ** Unique content in " << filepath1 << ": **\n";
                    list1uniques.output(cout);
                    cout << " **\n";
                }
                break;
                case 2:
                {
                    cout << " ** Unique content in " << filepath2 << ": **\n";
                    list2uniques.output(cout);
                    cout << " **\n";
                }
                break;
                default:
                    subquit = true;
                }
            }
        }
        break;
        case 5:
        {
            cin.ignore(1);
            char inputpath[256];
            cout << "You are about to sort a listfile alphabetically.\n";
            cout << "Enter the path to the listfile:\n";
            cin.getline(inputpath, 256);

            Listfile list(inputpath);
            list.sort();

            char outputpath[256];
            cout << "\nDone! Enter the name of the file to save to:\n";
            cin.getline(outputpath, 256);
            list.save(outputpath);
        }
        break;
        case 6:
        {
            cin.ignore(1);
            char inputpath[256];
            cout << "You are about to remove any duplicate lines from\n";
            cout << "a listfile.\n";
            cout << "Enter the path to the listfile:\n";
            cin.getline(inputpath, 256);

            Listfile list(inputpath);
            list.unique();

            char outputpath[256];
            cout << "\nDone! Enter the name of the file to save to:\n";
            cin.getline(outputpath, 256);
            list.save(outputpath);
        }
        break;
        case 7:
        {
            cin.ignore(1);
            char inputpath[256];
            cout << "\nYou are about to list all lines in a listfile\n";
            cout << "that contain a search string that you will enter.\n";
            cout << "Why you want to do this is behind my comprehension,\n";
            cout << "there are text editors that can do this as well, you know.\n";
            cout << "First, which listfile do you want to open?\n";
            cin.getline(inputpath, 256);

            Listfile list(inputpath);


            char searchstr[256];
            cout << "\nEnter the searchstring:\n";
            cin.getline(searchstr, 256);

            Listfile newlist = list.search(searchstr);


            int nr;
            bool subquit = false;
            while(!subquit)
            {
                cout << "\n\n";
                cout << "[0] List all the lines\n";
                cout << "[1] Save the file\n";
                cout << "[2] Quit\n";

                cin >> nr;
                cin.ignore(1);

                switch(nr)
                {
                case 0:
                {
                    cout << " **\n";
                    newlist.output(cout);
                    cout << " **\n";
                }
                break;
                case 1:
                {
                    char outputpath[256];
                    cout << "\nEnter the name of the file to save to:\n";
                    cin.getline(outputpath, 256);
                    newlist.save(outputpath);
                    subquit = true;
                }
                break;
                default:
                    subquit = true;
                }
            }
        }
        break;
        default:
        {
            quit = true;
        }
        }
    }
    return 0;
}

