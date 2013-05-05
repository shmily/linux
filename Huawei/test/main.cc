#include <iostream>
#include <cctype>
#include <cstring>
#include <string>
#include <vector>
#include <iterator>
using namespace std;
 
struct Relation
{
public:
    Relation(char *str, int i) : name(str), id(i) {}
    Relation(string &str, int i) : name(str), id(i) {}
    string name;
    int id;
};
 
vector<Relation> relations;
int id;
 
int CheckeParams(char *str, int len, int ex)
{
    int i=0, j=-1;
    while (i<len)
    {
        while (i<len&&!isalnum(str[i])) i++;
        if (i>=len)
            break;
        while(isalnum(str[i])) i++;
        j++;
    }
 
    if (j>ex){
        cout << "error:参数过多" <<endl;
        return 0;
    }
    if (j<ex)
    {
        cout << "error:参数过少" <<endl;
        return 0;
    }
 
    return 1;
}
 
void parseParams(char *str, int *p, int n)
{
    int i=0;
    while (!isalnum(str[i])) i++;
    while (isalnum(str[i])) i++;
 
    for (int j=0; j<n; j++)
    {
        while (!isalnum(str[i])) i++;
        p[j]=i;
        while (isalnum(str[i])) i++;
    }
}
 
int SearchId(string &str)
{
    if (relations.empty())
        return -1;
 
    vector<Relation>::iterator iter = relations.begin(),
        end = relations.end();
 
    for (; iter!=end; ++iter)
    {
        if (iter->name==str)
            return iter->id;
    }
 
    return -1;
}
 
void UpdateRelations(int id1, int id2)
{
    int mid = id1>id2 ? id1 : id2;
    int tid = id1>id2 ? id2 : id1;
 
    vector<Relation>::iterator iter = relations.begin(),
        end = relations.end();
 
    for (; iter!=end; ++iter)
    {
        if (iter->id==mid)
            iter->id=tid;
    }
}
 
void HandleSet(char *str, int len)
{
    if (!CheckeParams(str, len, 2))
        return;
 
    int paras[2];
    parseParams(str, paras, 2);
 
    if (strcmp(str+paras[0], str+paras[1])==0){
        cout << "false" <<endl;
        return;
    }
 
    string str1(str+paras[0]), str2(str+paras[1]);
    int id1 = SearchId(str1);
    int id2 = SearchId(str2);
    if (id1==id2&&id1!=-1)
    {
        cout << "false" <<endl;
        return;
    }
 
    if (id1==id2&&id1==-1)
    {
        relations.push_back(Relation(str1, id));
        relations.push_back(Relation(str2, id));
        id++;
        return;
    }
 
    if (id1==-1)
    {
        relations.push_back(Relation(str1, id2));
        return;
    }
    if (id2==-1)
    {
        relations.push_back(Relation(str2, id1));
        return;
    }
 
    UpdateRelations(id1, id2);
}
 
void HandleIs(char *str, int len)
{
    if (!CheckeParams(str, len, 2))
        return;
 
    int paras[2];
    parseParams(str, paras, 2);
 
    if (strcmp(str+paras[0], str+paras[1])==0){
        cout << "false" <<endl;
        return;
    }
 
    string str1(str+paras[0]), str2(str+paras[1]);
    int id1 = SearchId(str1);
    int id2 = SearchId(str2);
    if (id1!=id2 || (id1==id2&&id1==-1))
    {
        cout << "false" <<endl;
        return;
    }
 
    cout << "true" <<endl;
}
 
void HandleClear(char *str, int len)
{
    if (!CheckeParams(str, len, 0))
        return;
    id = 0;
    relations.clear();
}
 
int main()
{
    char str[1024];
    id = 0;
    while (cin.getline(str, 1024))
    {
        int i,len = strlen(str);
        for (i=0; i<len; i++)
            if (!isalnum(str[i]))
                str[i] = 0;
 
        char *pcmd = str;
        while (*pcmd==0) pcmd++;
 
        if (strcmp(pcmd, "SetSynonyms")==0)
            HandleSet(str, len);
        else if (strcmp(pcmd, "IsSynonyms")==0)
            HandleIs(str, len);
        else if (strcmp(pcmd, "ClearRelations")==0)
            HandleClear(str, len);
        else
            cout <<"error:系统不支持该命令"<<endl;
    }
 
    return 0;
}