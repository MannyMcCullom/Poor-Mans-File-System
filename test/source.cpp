#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string* pFileName;

int main()
{
    ifstream inFile;
    ofstream outFile;
    
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

    system("start temp_test.bat");

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

        int currentFile = 0;

        line1 = "";
        line2 = "";

        while (inFile)
        {
            getline(inFile, line1);

            if (line1 != line2)
            {
                if (line1 != "temp_names.txt" && line1.length() > 0)
                {
                    pFileName[currentFile] = line1;
                    currentFile++;
                }
            }

            line2 = line1;
        }

        inFile.close();
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
        bool dir = false;

        while (!exit)
        {
            dir = false;
            system("cls");

            cout
                << "w or s to navigate"
                << endl
                << "e to open file"
                << endl
                << "q to exit"
                << endl
                ;

            for (int index = 0; index < numOfFiles; index++)
            {
                if (index == selection)
                {
                    cout << "{" << pFileName[index] << "}" << endl;
                }

                else
                {
                    cout << " " << pFileName[index] << " " << endl;
                }
            }

            getline(cin, response);

            if (toupper(response[0]) == 'Q')
            {
                exit = true;
                system("del temp_openfile.bat temp_names.txt, temp_check_file.bat");
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

            else if (toupper(response[0]) == 'E')
            {
                string name = pFileName[selection];
                bool space = false;

                cout << "Selected " << name << endl;

                outFile.open("temp_check_file.bat");

                outFile
                    << "cd folder"
                    << endl
                    ;

                for (int index = 0; index < pFileName[selection].length(); index++)
                {
                    if (pFileName[selection][index] == ' ')
                    {
                        outFile << "dir " << '"' << pFileName[selection] << '"' << " > temp_check.txt" << endl;
                        space = true;
                        break;
                    }
                }
                
                if (!space)
                {
                    outFile << "dir " << pFileName[selection] << " > temp_check.txt" << endl;
                }
                
                outFile
                    << "cd.."
                    << endl
                    << "move folder\\temp_check.txt"
                    << endl
                    << "exit"
                    ;

                outFile.close();

                system("temp_check_file.bat");

                inFile.open("temp_check.txt");

                string line;
                string check = "";
                char i = ' ';

                while (inFile)
                {
                    if (dir)
                    {
                        break;
                    }

                    getline(inFile, line);

                    if (line.find(" 0 dir(s)"))
                    {
                        dir = false;
                        cout << line << endl;
                    }

                    for (int index = 0; index < line.length(); index++)
                    {
                        i = line[index];

                        if (i == '<')
                        {
                            check = line.substr(index);
                            if (check.substr(0, 5) == "<DIR>")
                            {
                                cout << "Is directory" << endl;
                                dir = true;
                                break;
                            }
                        }
                    }
                }

                inFile.close();

                outFile.open("temp_openfile.bat");

                outFile
                    << "cd folder"
                    << endl
                    << "start " << pFileName[selection]
                    << endl
                    << "exit"
                    ;

                outFile.close();

                system("start temp_openfile.bat");
            }
        }
    }

    else
    {
        cout << "No Files" << endl;
    }

    return 0;
}