#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;


void init(vector<int>& num)
{
    string s;
    cin>>s;
    int len=s.length()-1;
    for(int i=len;i>=0;i--)
    {
        num.push_back(s[i]-'0');
    }
}

void display(const vector<int>& num)
{
    bool leading_zero=true;

    if(num.empty())
    {
        cout<<"0.0\n";
        return;
    }

    // 检查并输出负号（无需变量）
    if(num.back()<0&&num.back()!=-1) cout<<"-";

    // 从最高位开始显示
    for(auto iter=num.rbegin();iter!=num.rend();iter++)
    {
        if(*iter==10)
        {
            if(leading_zero) cout<<"0";
            cout<<".";
            leading_zero=false; // 遇到小数点后，允许显示前导零
        }
        else
        {
            if(leading_zero&&*iter==0) continue;
            cout<<abs(*iter); // 输出绝对值（符号已处理）
            leading_zero = false;
        }
    }
    cout<<endl;
}

vector<int> add(vector<int> num1, vector<int> num2)
{
    int temp=0;
    if(num1.size()<num2.size()) swap(num1,num2);
    for(size_t i=0;i<num1.size();i++)
    {
        if(i<num2.size()) temp+=num1[i]+num2[i];
        else temp+=num1[i];
        
        if(temp<10)
        {
            num1[i]=temp;
            temp=0;
        }
        else
        {
            num1[i]=temp-10;
            temp=1;
        }
    }
    if(temp) num1.push_back(temp);
    while(num1.size()>1 && num1.back()==0)
    {
        num1.pop_back();
    }
    return num1;
}

vector<int> subtract(vector<int> num1, vector<int> num2)
{
    bool isNegative=false;
    int temp=0;
    if(num1.size()<num2.size())
    {
        swap(num1,num2);
        isNegative=true;
    }
    else if(num1.size()==num2.size())
    {
        if(num1.back()<num2.back())
        {
            swap(num1,num2);
            isNegative=true;
        }
    }
    for(size_t i=0;i<num1.size();i++)
    {
        if(i<num2.size()) temp+=num1[i]-num2[i];
        else temp+=num1[i];
        if(temp>=0)
        {
            num1[i]=temp;
            temp=0;
        }
        else
        {
            num1[i]=temp+10;
            temp=-1;
        }
    }
    while(num1.size()>1 && num1.back()==0)
    {
        num1.pop_back();
    }
    if(isNegative) num1.back()=-num1.back();
    return num1;
}

vector<int> multiply(vector<int> num1, vector<int> num2)
{
    vector<int> res(num1.size()+num2.size(),0);
    for(size_t i=0;i<num1.size();i++)
    {
        for(size_t j=0;j<num2.size();j++)
        {
            res[i+j]+=num1[i]*num2[j];
            if(res[i+j]>=10)
            {
                res[i+j+1]+=res[i+j]/10;
                res[i+j]%=10;
            }
        }
    }
    while(res.size()>1 && res.back()==0)
    {
        res.pop_back();
    }
    return res;
}

// 高精度除法，返回商和小数部分
vector<int> divide(vector<int> num1,vector<int> num2,int decimal_places)
{
    vector<int> quotient;
    vector<int> current_remainder;

    if(num2.size()==1&&num2[0]==0) return vector<int>();
    // 处理整数部分
    for(int i=num1.size()-1;i>=0;i--)
    {
        current_remainder.insert(current_remainder.begin(),num1[i]);
        // 去除前导零（逆序后的末尾零）
        while(current_remainder.size()>1&&current_remainder.back()==0)
        {
            current_remainder.pop_back();
        }

        int q=0;
        while(true)
        {
            vector<int> sub_result=subtract(current_remainder,num2);
            if(sub_result.back()>=0)
            {
                q++;
                current_remainder=sub_result;
            }
            else break;
        }
        quotient.push_back(q);
    }

    // 去除整数部分的前导零（正序的高位零）
    reverse(quotient.begin(),quotient.end());
    while(quotient.size()>1&&quotient.back()==0)
    {
        quotient.pop_back();
    }
    reverse(quotient.begin(),quotient.end());

    // 处理小数部分
    vector<int> decimal;
    for(int i=0;i<decimal_places;i++)
    {
        current_remainder.insert(current_remainder.begin(),0);
        // 去除前导零
        while(current_remainder.size()>1&&current_remainder.back()==0)
        {
            current_remainder.pop_back();
        }

        int q=0;
        while(true)
        {
            vector<int> sub_result=subtract(current_remainder,num2);
            if(sub_result.back()>=0)
            {
                q++;
                current_remainder=sub_result;
            }
            else break;
        }
        decimal.push_back(q);
    }
    vector<int> res=quotient;
    if(!decimal.empty()||decimal_places>0)
    {
        res.push_back(10); // 添加小数点
        res.insert(res.end(),decimal.begin(),decimal.end());
    }
    reverse(res.begin(), res.end());
    //if(res[0]==10) res.insert(res.begin(),0);
    return res;
}

int main()
{
    vector<int> num1;
    vector<int> num2;
    cout<<"Enter two numbers:\n";
    init(num1);
    init(num2);
    cout<<"\nAdd:\n";
    display(add(num1,num2));
    cout<<"\nSubtract:\n";
    display(subtract(num1,num2));
    cout<<"\nMultiply:\n";
    display(multiply(num1,num2));
    cout<<"\nDivide:\n";
    display(divide(num1,num2,20)); // 保留20位小数
    return 0;
}

