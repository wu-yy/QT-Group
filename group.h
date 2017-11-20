#ifndef GROUP_H
#define GROUP_H
#include<iostream>
#include<vector>
#include<map>
#include<fstream>
#include<stdio.h>
#include<string>
#include<set>


using namespace std;

#define N 30   //这里的N是外国人或者中国人的数量
//其中 1-N 代表中国人  N+1-2N 代表外国人
int form[N+1][N+1];
int Result[2*N+1];
vector< vector<int> > findFriends;
void insertVector(int A1,int A2)
{
    bool find=false;
    for(int i=0;i<findFriends.size();i++)
    {

        for(int j=0;j<findFriends[i].size();j++)
        {
            if(findFriends[i][j]==A1)
            {
                find=true;
                bool find2=false;
                for(int k=0;k<findFriends[i].size();k++)
                {
                    if(A2+N ==findFriends[i][k])
                    {
                        find2=true;
                        break;
                    }
                }
                if(!find2)
                {
                    findFriends[i].push_back(A2+N);
                }
                break;
            }

            else if(findFriends[i][j]==A2+N)
            {
                find=true;
                bool find2=false;
                for(int k=0;k<findFriends[i].size();k++)
                {
                    if(A1==findFriends[i][k])
                    {
                        find2=true;
                        break;
                    }
                }
                if(!find2)
                {
                    findFriends[i].push_back(A1);
                }
                break;
            }
        }

        if(find)
        {
            break;
        }

    }


    if(!find) //如果没有在这个vector里面发现
    {
        vector<int>AA;
        AA.push_back(A1);
        AA.push_back(A2+N);
        findFriends.push_back(AA);
    }
}

bool equalVector(vector<int> a,vector<int> b)
{
    for(int i=0;i<a.size();i++)
    {

        for(int j=0;j<b.size();j++)
        {
            if(a[i]==b[j])
            {
                return true;
            }
        }
    }
    return false;
}
//
vector<vector<int>> findVector;
void insertVector2(int A1,int A2)  //此处对于大规模的插入可能存在系统bug
{
    bool find=false;
    for(int i=0;i<findVector.size();i++)
    {

        for(int j=0;j<findVector[i].size();j++)
        {
            if(findVector[i][j]==A1)
            {
                find=true;
                bool find2=false;
                for(int k=0;k<findVector[i].size();k++)
                {
                    if(A2 ==findVector[i][k])
                    {
                        find2=true;
                        break;
                    }
                }
                if(!find2)
                {
                    findVector[i].push_back(A2);
                }
                break;
            }

            else if(findVector[i][j]==A2)
            {
                find=true;
                bool find2=false;
                for(int k=0;k<findVector[i].size();k++)
                {
                    if(A1==findVector[i][k])
                    {
                        find2=true;
                        break;
                    }
                }
                if(!find2)
                {
                    findVector[i].push_back(A1);
                }
                break;
            }
        }

        if(find)
        {
            break;
        }

    }


    if(!find) //如果没有在这个vector里面发现
    {
        vector<int>AA;
        AA.push_back(A1);
        AA.push_back(A2);
        findVector.push_back(AA);
    }
}

//第三次更新、修复bug
vector<set<int>>  Friends2;

struct pair_my
{
    int i;
    int j;

};

#endif // GROUP_H
