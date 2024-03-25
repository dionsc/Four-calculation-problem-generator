#define  _CRT_SECURE_NO_WARNINGS

#include <string>
#include <urlmon.h>
#include <iostream>
#include <fstream>
#include <ExDisp.h>
#include <ShlObj.h>
#include <vector>
#include <Windows.h>
#include <Commdlg.h> 
#include <map>
#include <algorithm>
#include <cmath>
#include <tchar.h>



/*** �������ݴ��� ***/

//�������������LaTeX��ʽ��ʾ����ʽ
std::string Operator[7] = { "+","-","\\times","\\div","=","(",")" };

//����������������Ŀ
std::vector<std::vector<int> >  naturalNumber(int n, int l, int r)
{
    //��ʼ�������������
    srand(static_cast<unsigned int>(time(nullptr)));
    if (l > r) std::swap(l, r);
    //��map���������ÿһ���ù�����Ŀ���Դﵽ���ظ���Ч��
    std::map<int, std::map<int, std::map<int, std::map<int, std::map<int, int> > > > >vis;
    //��ÿһ��ʽ����һ��vector����洢
    std::vector<std::vector<int> > res;
    while (n)
    {
        int x = rand() % (r - l + 1) + l;
        int y = rand() % (r - l + 1) + l;
        int z = rand() % (r - l + 1) + l;
        int i = rand() % 4;
        int j = rand() % 4;
        if (vis[x][y][z][i][j]) continue;
        vis[x][y][z][i][j] = true;
        n--;
        //��������Ƿ������ź����ŵ�λ��
        if (rand() % 2)
        {
            res.push_back({ x,-i - 1,y,-j - 1,z,-5 });
        }
        else
        {
            if (rand() % 2)
            {
                res.push_back({ -6,x,-i - 1,y,-7,-j - 1,z,-5 });
            }
            else
            {
                res.push_back({ x,-i - 1,-6,y,-j - 1,z,-7,-5 });
            }
        }
    }
    return res;
}

std::vector<std::vector<int> > Fraction(int n, int Numerator, int denominator)
{
    //��ʼ�������������
    srand(static_cast<unsigned int>(time(nullptr)));


    //��ÿһ��ʽ����һ��vector����洢
    std::vector<std::vector<int> > res;

    //��map���������ÿһ���ù�����Ŀ���Դﵽ���ظ���Ч��
    std::map<int, std::map<int, std::map<int, std::map<int, std::map<int, std::map<int, std::map<int, std::map<int, int> > > > > > > >vis;
    while (n)
    {
        int x1 = rand() % Numerator + 1, x2 = rand() % denominator + 1;
        int y1 = rand() % Numerator + 1, y2 = rand() % denominator + 1;
        int z1 = rand() % Numerator + 1, z2 = rand() % denominator + 1;
        int i = rand() % 4;
        int j = rand() % 4;

        if (vis[x1][x2][y1][y2][z1][z2][i][j]) continue;
        n--;
        vis[x1][x2][y1][y2][z1][z2][i][j] = true;


        //��������Ƿ������ź����ŵ�λ��
        if (rand() % 2)
        {
            res.push_back({ x1,x2,-i - 1,y1,y2,-j - 1,z1,z2,-5 });
        }
        else
        {
            if (rand() % 2)
            {
                res.push_back({ -6,x1,x2,-i - 1,y1,y2,-7,-j - 1,z1,z2,-5 });
            }
            else
            {
                res.push_back({ x1,x2,-i - 1,-6,y1,y2,-j - 1,z1,z2,-7,-5 });
            }
        }

    }
    return res;
}

//������ת��Ϊ�ַ���
std::string NumToString(long long num)
{
    std::string res;
    if (num < 0)
    {
        res += '-';
        num *= -1;
    }
    do {
        res += (char)(num % 10 + '0');
        num /= 10;
    } while (num > 0);
    std::reverse(res.begin(), res.end());
    return res;
}

//��շת������������Լ������������������
int gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

//���������ݲ�ͬ����������м���
void calculate(long long &fz, long long &fm, long long x, long long y, long long op)
{
    if (op == -1)
    {
        x *= fm;
        fz *= y;
        fm *= y;
        fz += x;
    }
    else if (op == -2)
    {
        x *= fm;
        fz *= y;
        fm *= y;
        fz -= x;
    }
    else if (op == -3)
    {
        fz *= x;
        fm *= y;
    }
    else
    {
        fz *= y;
        fm *= x;
    }
    long long u = gcd(fz, fm);
    fz /= u;
    fm /= u;
    return;
}

//����ʽ�ӵĽ������תΪ�ַ�������
std::string GetAns(const std::vector<int> &Data)
{
    std::string res = {};
    std::vector<long long> tmp;
    int len = (int)Data.size();
    for (int i = 0; i < len; i++)
    {
        tmp.push_back(Data[i]);
        //������תΪ����
        if (Data[i] >= 0 && ((i == 0 && Data[i + 1] < 0) || (i != 0 && i + 1 != len && Data[i - 1] < 0 && Data[i + 1] < 0)))
        {
            tmp.push_back(1);
        }
    }
    tmp.pop_back();
    len = (int)tmp.size();
        
    long long fz = 1, fm = 1;
    //�����������ڵĲ�ͬλ�ý��м���
    if (tmp[len - 1] == -6)
    {
        //11/(11/11)
        fz = tmp[4];
        fm = tmp[5];
        calculate(fz, fm, tmp[7], tmp[8], tmp[6]);
        calculate(fz, fm, tmp[0], tmp[1], tmp[2]);
    }
    else if (tmp[0] == -6)
    {
        //(11/11)/11
        fz = tmp[1];
        fm = tmp[2];
        calculate(fz, fm, tmp[4], tmp[5], tmp[3]);
        calculate(fz, fm, tmp[8], tmp[9], tmp[7]);
    }
    else
    {
        // 11/11/11
        fz = tmp[0];
        fm = tmp[1];
        calculate(fz, fm, tmp[3], tmp[4], tmp[2]);
        calculate(fz, fm, tmp[6], tmp[7], tmp[5]);
    }
    if (fz == 0 || fm == 0)
    {
        res += "0";
        return res;
    }
    if (fz < 0 && fm < 0)
    {
        fz *= -1;
        fm *= -1;
    }
    if (fz < 0)
    {
        fz *= -1;
        res += '-';
    }
    if (fm < 0)
    {
        fm *= -1;
        res += '-';
    }
    //������ת��Ϊ������
    if (fz / fm)
    {
        res += NumToString(fz / fm);
    }
    if (fz % fm)
    {
        if (fz / fm)
        {
            res += "\\'";
        }
        fz %= fm;
        res += NumToString(fz);
        res += "/";
        res += NumToString(fm);
    }
    if (!res.size()) res = "0";
    return res;
}

//����ʽ�ӵĴ𰸣�����ʽ�Ӻʹ𰸴����һ���������û�ʹ�õ�ǰ�˽��棬��html���������ָ��.html�ļ�
std::string Pack(const std::vector<std::vector<int> >& Data, const std::string& Title, std::ofstream &outputFile)
{
    std::string res;

    outputFile <<"<!DOCTYPE html>  \n"
        "<html lang=\"en\">  \n"
        "<head>  \n"
        "    <meta charset=\"ANSI\">  \n"
        "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">  ";
    outputFile <<"     <title>"; outputFile <<Title; outputFile <<"</title>\n";
    outputFile <<"<style>  \n"
        "        .answer-container {  \n"
        "            margin-bottom: 20px;  \n"
        "        }  \n"
        "        .feedback {  \n"
        "            display: none;  \n"
        "            margin-left: 10px;  \n"
        "            font-size: 14px;  \n"
        "            color: #666;  \n"
        "        }  \n"
        "        .feedback.correct {  \n"
        "            color: green;  \n"
        "        }  \n"
        "        .feedback.incorrect {  \n"
        "            color: red;  \n"
        "        }  \n"
        "        .show-correct-btn {  \n"
        "            margin-left: 10px;  \n"
        "            cursor: pointer;  \n"
        "            color: blue;  \n"
        "            text-decoration: underline;  \n"
        "        }  \n"
        "    </style>  ";
    outputFile <<"     <script src=\"https://polyfill.io/v3/polyfill.min.js?features=es6\"></script>\n";
    outputFile <<"     <script id=\"MathJax-script\" async src=\"https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-mml-chtml.js\"></script>\n";
    outputFile <<"</head>\n";
    outputFile <<"<body>\n";
    outputFile <<"     <h3>"; outputFile <<Title; outputFile <<"</h3>\n";

    int index = 0;
    for (auto& arr : Data)
    {
        index++;
        outputFile <<"<div class=\"answer-container\">  \n"
            "        <p>\\(";
        int len = (int)arr.size();
        for (int i = 0; i < len; i++)
        {
            //��ʽ��ת����LaTex��ʽ
            if (arr[i] >= 0)
            {
                if (i != len - 1 && arr[i + 1] >= 0)
                {
                    outputFile <<"\\frac{";
                    outputFile <<NumToString(arr[i]);
                    outputFile <<"}{";
                    outputFile <<NumToString(arr[i + 1]);
                    outputFile <<"}";
                    i++;
                }
                else
                {
                    outputFile <<NumToString(arr[i]);
                }
            }
            else
            {
                outputFile <<Operator[-arr[i] - 1];
            }
        }

        outputFile <<"\\)</p>\n"
            "        <input type=\"text\" id=\"answer";
        outputFile <<NumToString(index);
        outputFile <<"\" class=\"answer-input\" placeholder=\"�������\">  \n"
            "        <span class=\"feedback\" id=\"feedback";
        outputFile <<NumToString(index);
        outputFile <<"\"></span>  \n"
            "        <span class=\"show-correct-btn\" id=\"showCorrect";
        outputFile <<NumToString(index);
        outputFile <<"\">�鿴��ȷѡ��</span>  \n"
            "    </div>  ";

    }


    outputFile <<"<script>  \n";
    outputFile <<"var correctAnswers = [";
    for (int i = 1; i <= index; i++)
    {
        outputFile <<"'";
        outputFile << GetAns(Data[i - 1]);
        outputFile <<"',";
    }
    outputFile <<"];\n";
    outputFile <<
        "        document.querySelectorAll('.answer-input').forEach(function(input) {  \n"
        "            input.addEventListener('input', function() {  \n"
        "                checkAnswer(input);  \n"
        "            });  \n"
        "        });  \n"
        "  \n"
        "        // �����鿴��ȷѡ��ĵ���¼�  \n"
        "        document.querySelectorAll('.show-correct-btn').forEach(function(btn) {  \n"
        "            btn.addEventListener('click', function() {  \n"
        "                showCorrectAnswer(btn);  \n"
        "            });  \n"
        "        });  \n"
        "  \n"
        "        // �����Ƿ���ȷ  \n"
        "        function checkAnswer(input) {  \n"
        "            var index = parseInt(input.id.replace('answer', ''), 10) - 1; // ��ȡ����������������±꣩  \n"
        "            var feedbackElement = document.getElementById(input.id.replace('answer', 'feedback'));  \n"
        "  \n"
        "            // ���֮ǰ�ķ���  \n"
        "            feedbackElement.textContent = '';  \n"
        "            feedbackElement.classList.remove('correct', 'incorrect');  \n"
        "  \n"
        "            // ��������Ƿ������鷶Χ��  \n"
        "            if (index >= 0 && index < correctAnswers.length) {  \n"
        "                // �Ƚ��û��������ȷ�𰸣�ȷ�������ַ������ͣ�  \n"
        "                if (input.value.trim().toLowerCase() === correctAnswers[index].toLowerCase()) {  \n"
        "                    feedbackElement.textContent = '��ȷ��';  \n"
        "                    feedbackElement.classList.add('correct');  \n"
        "                    feedbackElement.style.display = 'inline'; // ��ʾ����  \n"
        "                } else {  \n"
        "                    feedbackElement.textContent = '����';  \n"
        "                    feedbackElement.classList.add('incorrect');  \n"
        "                    feedbackElement.style.display = 'inline'; // ��ʾ����  \n"
        "                }  \n"
        "            } else {  \n"
        "                console.error('����������Χ');  \n"
        "            }  \n"
        "        }  \n"
        "  \n"
        "        // ��ʾ��ȷ��  \n"
        "        function showCorrectAnswer(btn) {  \n"
        "            var index = parseInt(btn.id.replace('showCorrect', ''), 10) - 1; // ��ȡ����������������±꣩  \n"
        "  \n"
        "            // ��������Ƿ������鷶Χ��  \n"
        "            if (index >= 0 && index < correctAnswers.length) {  \n"
        "                alert('���� ' + (index + 1) + ' ����ȷ���ǣ�' + correctAnswers[index]);  \n"
        "            } else {  \n"
        "                console.error('����������Χ');  \n"
        "            }  \n"
        "        }  \n"
        "    </script>  \n"
        "</body>  \n"
        "</html>";


    return res;
}



// ��ȡ�ļ���ַĿ¼
TCHAR* GetFile()
{
    // ��ʼ��COM���
    if (CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE) == S_FALSE)
    {
        return NULL;
    }

    // ��ʼ��OPENFILENAME�ṹ��
    OPENFILENAME ofn;
    TCHAR szFile[MAX_PATH] = { 0 };

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"HTML Files\0*.html\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    TCHAR* res = NULL;
    // ��ʾSave As�Ի���
    if (GetSaveFileName(&ofn) == TRUE)
    {
        res = (TCHAR*)malloc(sizeof(TCHAR) * _tcslen(ofn.lpstrFile));
        if (res)
        {
            _tcscpy(res, ofn.lpstrFile);
        }
    }

    // �ͷ�COM���
    CoUninitialize();
    return res;
}



int main()
{
    while (true)
    {
        int option = -1; 
        do
        {
            system("cls");
            std::cout << "������ѡ��\n[1]������Ȼ����Ŀ\n[2]���ɷ�����Ŀ\n���ѡ��";
            std::cin >> option;
        } while (option != 1 && option != 2);


        if (option == 1)
        {
            //��ȡ����
            int n = -1, l = -1, r = -1;
            do
            {
                system("cls");
                std::cout << "������3���������ֱ��ʾ����Ŀ������ ��Ȼ����Χ����Сֵ ��Ȼ����Χ�����ֵ\nÿ����֮���ÿո����\n";
                std::cin >> n >> l >> r;
            } while (n < 0 || l < 0 || r < 0);
            
            TCHAR* file = GetFile();
            if (file == NULL)
            {
                continue;
            }
            std::ofstream outputFile(file);

            //������Ŀ�ʹ�
            Pack(naturalNumber(n, l, r), "��Ȼ����Ŀ", outputFile);
            outputFile.close();

            //��������ļ�
            ShellExecute(NULL, L"open", file, NULL, NULL, SW_SHOWNORMAL);

        }
        else
        {

            //��ȡ����
            int n = -1, l = -1, r = -1;
            do
            {
                system("cls");
                std::cout << "������3���������ֱ��ʾ����Ŀ������ ���ӵ����ֵ ��ĸ�����ֵ\nÿ����֮���ÿո����\n";
                std::cin >> n >> l >> r;
            } while (n < 0 || l < 0 || r < 0);
            TCHAR* file = GetFile();
            if (file == NULL)
            {
                continue;
            }

            //������Ŀ�ʹ�
            std::ofstream outputFile(file);
            Pack(Fraction(n, l, r), "������Ŀ", outputFile);
            outputFile.close();

            //��������ļ�
            ShellExecute(NULL, L"open", file, NULL, NULL, SW_SHOWNORMAL);
        }
    }

    

}