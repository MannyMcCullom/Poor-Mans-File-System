#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

string* pFileName;
string* pBatchFile;

int main()
{
    ifstream inFile;
    ofstream outFile;
    int currentFile;

    int numOfFiles = 0;

    outFile.open("temp_test.bat");

    outFile
        << "cd folder"
        << endl
        << "dir /b > temp_names.txt"
        << endl
        << "cd.."
        << endl
        << "move folder\\temp_names.txt"
        << endl
        << "exit"
        << endl
        ;

    outFile.close();

    system("temp_test.bat");

    inFile.open("temp_names.txt");

    if (inFile)
    {
        string line1 = "";
        string line2 = "";

        while (inFile)
        {
            getline(inFile, line1);

            if (line1 != line2)
            {
                if (line1 != "temp_names.txt" && line1.length() > 0)
                {
                    numOfFiles++;
                }
            }

            line2 = line1;
        }

        inFile.close();

        inFile.open("temp_names.txt");

        pFileName = new string[numOfFiles];
        pBatchFile = new string[numOfFiles];
        ifstream inFile2;

        currentFile = 0;

        line1 = "";
        line2 = "";

        while (inFile)
        {
            bool file = true;

            getline(inFile, line1);

            if (line1 != line2)
            {
                if (line1 != "temp_names.txt" && line1.length() > 0)
                {
                    pFileName[currentFile] = line1;
                    pBatchFile[currentFile] = "batch" + to_string(currentFile) + ".bat";

                    pFileName[currentFile] = '"' + line1 + '"';

                    outFile.open(pBatchFile[currentFile]);

                    outFile
                        << "cd folder"
                        << endl
                        << pFileName[currentFile]
                        << endl
                        << "exit"
                        ;

                    outFile.close();

                    outFile.open("temp_checkDir.bat");

                    outFile
                        << "cd folder"
                        << endl
                        << "dir " << pFileName[currentFile] << " > temp_CheckDir.txt"
                        << endl
                        << "cd .."
                        << endl
                        << "move folder\\temp_CheckDir.txt"
                        << endl
                        << "exit"
                        ;

                    outFile.close();

                    system("temp_checkDir.bat");

                    inFile2.open("temp_CheckDir.txt");

                    string line;
                    string word;

                    while (inFile2)
                    {
                        if (!file)
                        {
                            break;
                        }

                        getline(inFile2, line);

                        for (int index = 0; index < line.length(); index++)
                        {
                            if (line[index] == '<')
                            {
                                word = line.substr(index);

                                if (word.substr(0, 5) == "<DIR>")
                                {
                                    outFile.open(pBatchFile[currentFile]);

                                    outFile
                                        << "cd folder"
                                        << endl
                                        << "cd " << pFileName[currentFile]
                                        << endl
                                        << "start ."
                                        << endl
                                        << "exit"
                                        ;

                                    outFile.close();

                                    file = false;
                                    break;
                                }
                            }
                        }
                    }

                    inFile2.close();

                    currentFile++;
                }
            }

            line2 = line1;
        }

        inFile.close();

        string tempFileName;
        string tempBatchFile;

        for (int index = 0; index < numOfFiles - 1;index++)
        {
            if (pFileName[index] > pFileName[index + 1])
            {
                tempFileName = pFileName[index];
                tempBatchFile = pBatchFile[index];

                pFileName[index] = pFileName[index + 1];
                pBatchFile[index] = pBatchFile[index + 1];

                pFileName[index + 1] = tempFileName;
                pBatchFile[index + 1] = tempBatchFile;

                index = -1;
            }
        }
    }

    else
    {
        cout << "No File" << endl;
    }

    // Select file menu
    if (numOfFiles > 0)
    {
        int selection = 0;
        string response = "";
        bool exit = false;

        while (!exit)
        {
            response = "";

            system("cls");

            cout
                << "         w or s to navigate"
                << endl
                << "         e to open file"
                << endl
                << "         o to open explorer"
                << endl
                << "         q to exit"
                << endl
                << endl
                ;

            int dot;

            for (int index = 0; index < numOfFiles; index++)
            {
                dot = 0;

                for (int index2 = 0; index2 < pFileName[index].length(); index2++)
                {
                    if (pFileName[index][index2] == '.')
                        dot = index2;
                }

                if (index == selection)
                {
                    if (dot > 0)
                    {
                        cout << "-+-+-+-{ " << pFileName[index].substr(1, pFileName[index].length() - (pFileName[index].length() - dot) - 1) << " }-+-+-+-" << endl;
                    }

                    else
                    {
                        cout << "-+-+-+-{ " << pFileName[index].substr(1, pFileName[index].length() - 2) << " }-+-+-+-" << endl;
                    }
                }

                else
                {
                    if (dot > 0)
                    {
                        cout << "         " << pFileName[index].substr(1, pFileName[index].length() - (pFileName[index].length() - dot) - 1) << "         " << endl;
                    }

                    else
                    {
                        cout << "         " << pFileName[index].substr(1, pFileName[index].length() - 2) << "         " << endl;
                    }
                }
            }

            getline(cin, response);

            if (toupper(response[0]) == 'Q')
            {
                exit = true;
            }

            else if (toupper(response[0]) == 'W')
            {
                selection--;

                if (selection < 0)
                {
                    selection = numOfFiles - 1;
                }
            }

            else if (toupper(response[0]) == 'S')
            {
                selection++;

                if (selection >= numOfFiles)
                {
                    selection = 0;
                }
            }

            else if (toupper(response[0]) == 'O')
            {
                outFile.open("temp_openexplorer.bat");

                outFile
                    << "cd folder"
                    << endl
                    << "start ."
                    << endl
                    << "exit"
                    ;

                outFile.close();

                system("call temp_openexplorer.bat");
            }

            else if (toupper(response[0]) == 'E')
            {
                system(("call " + pBatchFile[selection]).c_str());
                //exit = true;
            }
        }
    }

    else
    {
        cout << "No Files" << endl;
    }

    system("cls");

    for (int index = 0; index < numOfFiles; index++)
    {
        system(("del " + pBatchFile[index]).c_str());
    }

    ///*
    system("del temp_openexplorer.bat");
    system("del temp_checkDir.txt");
    system("del temp_checkDir.bat");
    system("del temp_names.txt");
    system("del temp_test.bat");
    //*/

    return 0;
}