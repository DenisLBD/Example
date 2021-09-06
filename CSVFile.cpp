#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

typedef std::vector<std::vector<std::string>> stringTable;

void VectorString(std::string& fileContent, std::vector<std::string>& stringVector); // создает вектор типа string из csv формы

void readFile(std::string& filename, stringTable& myTable); // читает csv файл

void makeAlphaMap(stringTable& myTable, std::map<std::string, int>& alphaIndex); //создает пару ключ-значение, ключ - название столбца, значение - его индекс

void makeDigitMap(stringTable& myTable, std::map<std::string, int>& digitIndex); //создает пару ключ-значение, ключ - номер строки, значение - его индекс

void modTable(stringTable& myTable, std::map<std::string, int> alphaIndex, std::map<std::string, int> digitIndex); // производит необходимые вычисления в таблице 

void numsOperatoin(std::string& stringToCalculate); // вычисляет результат если в выражении нет адресов ячеек 

int getNumAlpha(std::string stringToConvert, std::string::size_type& i, std::map<std::string, int> alphaIndex); // создает пару ключ-значение для названия столбца

int getNumDigit(std::string stringToConvert, std::string::size_type& i, std::map<std::string, int> digitIndex); // создает пару ключ-значение для номера строки

int main()
{ 
    stringTable myTable; // таблица, в которую будут заноситься данные из csv файла
    std::string filename; // имя файла csv

    std::cout << "Enter file name:" << std::endl;

    std::getline(std::cin, filename);

    readFile(filename, myTable);

    std::map<std::string, int> alphaIndex, digitIndex;

    makeAlphaMap(myTable, alphaIndex); 
    makeDigitMap(myTable, digitIndex);

    modTable(myTable, alphaIndex, digitIndex);

    std::cout << ',' << '\t';

    for (int i = 0; i < myTable.size(); i++)
    {
        for (int j = 0; j < myTable[i].size(); j++)
        {
            std::cout << myTable[i][j];
            if (j != myTable[i].size() - 1)
                std::cout << ',' << '\t';
        }
        std::cout << std::endl;
    }

    return 0;
}

void readFile(std::string& filename, stringTable& myTable)
{
    std::ifstream myFile;
    std::string fileContent;
    std::vector<std::string> stringVector;

    myFile.open(filename, std::ios_base::in);

    if (myFile.is_open())
    {
        while (myFile.good())
        {
            std::getline(myFile, fileContent);

            VectorString(fileContent, stringVector);
            myTable.push_back(stringVector);

            stringVector.clear();
            std::cout << fileContent << std::endl;
        }

        myFile.close();
    }
    else
    {
        std::cerr << "Can't open file" << std::endl;
        return;
    }
}

void VectorString(std::string& fileContent, std::vector<std::string>& stringVector)
{

    std::string::size_type pos = fileContent.find_first_not_of(",", 0);
    std::string::size_type delPos = fileContent.find_first_of(",", pos); // номер позиции ","

    while ((std::string::npos != delPos) || (std::string::npos != pos))
    {

        stringVector.push_back(fileContent.substr(pos, delPos - pos));

        pos = fileContent.find_first_not_of(",", delPos);
        delPos = fileContent.find_first_of(",", pos);
    }
}

void makeAlphaMap(stringTable& myTable, std::map<std::string, int>& alphaIndex)
{
    for (int j = 0; j < myTable[0].size(); j++) //create map
    {
        alphaIndex.insert(std::make_pair(myTable[0][j], j + 1));
    }
}

void makeDigitMap(stringTable& myTable, std::map<std::string, int>& digitIndex)
{
    for (int i = 1; i < myTable.size() - 1; i++) //create map 
    {
        digitIndex.insert(std::make_pair(myTable[i][0], i));
    }
}

void modTable(stringTable& myTable, std::map<std::string, int> alphaIndex, std::map<std::string, int> digitIndex)
{
    std::string::size_type findEq;
    for (int i = 0; i < myTable.size(); i++)
    {
        for (int j = 0; j < myTable[i].size(); j++)
        {
            findEq = myTable[i][j].find("=");
            if (findEq != std::string::npos) // если в ячейке есть "="
            {
                if (isdigit((myTable[i][j])[1]))
                {
                    numsOperatoin(myTable[i][j]);
                    continue;
                }

                std::string::size_type pos = 1;

                std::string::size_type j1 = getNumAlpha(myTable[i][j], pos, alphaIndex);
                std::string::size_type i1 = getNumDigit(myTable[i][j], pos, digitIndex);

                char operat = (myTable[i][j])[pos]; // находим оператор
                pos++;

                std::string::size_type j2 = getNumAlpha(myTable[i][j], pos, alphaIndex);
                std::string::size_type i2 = getNumDigit(myTable[i][j], pos, digitIndex);

                if (myTable[i][j] == myTable[i1][j1] || myTable[i][j] == myTable[i2][j2]) // если рекурсивный случай, записываем в ячейку "Recur"
                {
                    myTable[i][j] = "Recur";
                    continue;
                }
                
                double result = 0; // результат вычисления выражения

                std::stringstream convertTo1;
                double oper1, oper2;

                convertTo1 << myTable[i1][j1];
                convertTo1 >> oper1; // первый аргумент

                std::stringstream convertTo2;
                convertTo2 << myTable[i2][j2];
                convertTo2 >> oper2; // второй аргумент

                switch (operat)
                {
                case '+':
                    result = oper1 + oper2;
                    break;
                case '-':
                    result = oper1 - oper2;
                    break;
                case '*':
                    result = oper1 * oper2;
                    break;
                case '/':
                    if (oper2 == 0)
                    {
                        myTable[i][j] = "Err"; // если деление на 0, записываем в ячейку "Err"
                        continue;
                    } else
                        result = (oper1 * 1.0) / oper2;
                    break;
                default:
                    myTable[i][j] = "Err";
                    continue;
                }

                std::stringstream convertTo3;
                convertTo3 << result;
                std::string stringResult;
                convertTo3 >> stringResult; // преобразуем результат в строку

                myTable[i][j] = stringResult;
            }

        }

    }
}

void numsOperatoin(std::string& stringToCalculate)
{
    std::string::size_type i = 1;
    std::string::size_type initPos = i; // Начальная позиция
    std::string subStr;

    while (isdigit(stringToCalculate[i]))
        i++;

    subStr = stringToCalculate.substr(initPos, i - initPos);

    std::stringstream convertArg1;
    double oper1, oper2, result;

    convertArg1 << subStr;
    convertArg1 >> oper1; // первый аргумент

    char operat = stringToCalculate[i]; // находим оператор

    i++;
    initPos = i;

    while (isdigit(stringToCalculate[i]))
        i++;

    subStr = stringToCalculate.substr(initPos, i - initPos);

    std::stringstream convertArg2;

    convertArg2 << subStr;
    convertArg2 >> oper2; // второй аргумент

    switch (operat)
    {
    case '+':
        result = oper1 + oper2;
        break;
    case '-':
        result = oper1 - oper2;
        break;
    case '*':
        result = oper1 * oper2;
        break;
    case '/':
        if (oper2 == 0)
        {
            stringToCalculate = "Err"; // если деление на 0, записываем в ячейку "Err"
        }
        else
            result = (oper1 * 1.0) / oper2;
        break;
    default:
        stringToCalculate = "Err";
    }

    if (stringToCalculate != "Err")
    {
        std::stringstream convertResult;
        convertResult << result;
        convertResult >> stringToCalculate;
    }
}

int getNumAlpha(std::string stringToConvert, std::string::size_type& i, std::map<std::string, int> alphaIndex)
{
    std::string::size_type initPos = i;
    std::string subStr;
    while (isalpha(stringToConvert[i]))
        i++;

    subStr = stringToConvert.substr(initPos, i - initPos); // находим название столбца

    auto search = alphaIndex.find(subStr);

    int num = 0;

    if (search != alphaIndex.end())
    {
        num = search->second;
    }
    else
    {
        std::cerr << "Invalid column name" << std::endl;
        return 1;
    }
    return num;
}

int getNumDigit(std::string stringToConvert, std::string::size_type& i, std::map<std::string, int> digitIndex)
{
    std::string::size_type initPos = i; // Начальная позиция
    std::string subStr;
    while (isdigit(stringToConvert[i]))
        i++;

    subStr = stringToConvert.substr(initPos, i - initPos); // находим номер строки

    auto search = digitIndex.find(subStr);

    int num = 0;

    if (search != digitIndex.end())
    {
        num = search->second;
    }
    else
    {
        std::cerr << "Invalid line number" << std::endl;
        return 1;
    }
    return num;
}

