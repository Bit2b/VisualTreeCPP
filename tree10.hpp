#pragma once

#include<iostream>
#include<sstream>
#include<iomanip>
#include<memory>

using namespace std;
template <typename T>
struct __treenode
{
    std::unique_ptr<__treenode<T>> left;
    T val;
    std::unique_ptr<__treenode<T>> right;
};

template <typename T>
static int CalculateTreeHeight(const std::unique_ptr<__treenode<T>>& root)
{
    if(!root) return 0;
    return 1+std::max(CalculateTreeHeight(root->left),CalculateTreeHeight(root->right));
}

template <typename T>
static void FillTreeVector(const std::unique_ptr<T[]>& elements,
const std::unique_ptr<__treenode<T>>& Root,const std::unique_ptr<bool[]>& elementExist,int index)
{
    if(!Root)return;
    elements[index]=Root->val;
    elementExist[index]=1;
    FillTreeVector(elements,Root->left,elementExist,2*index+1);
    FillTreeVector(elements,Root->right,elementExist,2*index+2);
}
int parent(int i)
{
    return i%2?i>>1:(i-1)>>1;
}
template <typename T>
void PrintTreeVisual(const std::unique_ptr<T[]>& elements,int height,const std::unique_ptr<bool[]>& elementExist, int n)
{
    int current_level_start_index=0;
    for(int k=0;k<=height;k++)
    {
        std::stringstream ss;
        for(int i=current_level_start_index;i<(1<<k)+current_level_start_index;i++)
        {
            int levelSpacing=(1<<(height-k))-1;
            for(int j=0;j<levelSpacing;j++)
            {
                ss<<std::setw(n) << " ";
            }
            if(elementExist[i])
                ss<<std::setw(n) << elements[i];
            else
            {
                if(elementExist[parent(i)])
                    ss<<std::setw(n) << "n";
                else
                    ss<<std::setw(n) << " ";
            }
            if(i<(1<<k)+current_level_start_index-1)
            {
                for(int j=0;j<levelSpacing;j++)
                {
                    ss<<std::setw(n) << " ";
                }
                ss<<std::setw(n) << " ";
            }
        }
        current_level_start_index+=1<<k;
        ss<<std::endl<<std::endl;
        std::cout << ss.str();
    }
}

template <typename T>
void PrintTree(void* rootNode, int width=2) {
    if(!rootNode) return;
    std::unique_ptr<__treenode<T>> root(static_cast<__treenode<T>*>(rootNode));
    int height = CalculateTreeHeight(root);
    int numElements = (1<<(height+1))-1;
    std::unique_ptr<T[]> elements(new T[numElements]());
    std::unique_ptr<bool[]> elementExists(new bool[numElements]());
    FillTreeVector(elements,root,elementExists,0);
    PrintTreeVisual(elements,height,elementExists,width);
}
