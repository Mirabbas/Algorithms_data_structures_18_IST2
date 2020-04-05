#include <iostream>
#include <fstream>
using namespace std;

int const sizeField = 10;
int const c_max = 9;
struct cell
{
    int down, right;                            //����� �� ��������� � �����������
    int val = -1;                               //������, ������� ����� ���������
    int q_down = 0, q_right = 0;                //���������� ����� � �����
    int pos_down[c_max] = {1,2,3,4,5,6,7,8,9};  //��������� �������� �� ���������
    int pos_right[c_max] = {1,2,3,4,5,6,7,8,9}; //��������� �������� �� �����������
};

cell field[sizeField][sizeField];


//=================================================================================
//�������� �������� �����
//arr1 - ��������
//arr2 - �����
void Copy(cell arr1[sizeField][sizeField], cell arr2[sizeField][sizeField]);

//=================================================================================
//������ ������ ���������� ���������
//���������� TRUE ��� ������ �����������
//a - ����
bool Rec(cell a[sizeField][sizeField]);
//=================================================================================




int main()
{
    setlocale(LC_ALL, "Rus");   //���������� ������� �����������
    int q;                      // ��� �������� ���������� ����� � �����
    int i, j;                   //��������

    //��������� ���������� �� �������� ����
    ifstream fin;
    fin.open("in.txt");
    if (fin.is_open())
    {
        for(i=0; i<sizeField; i++)
        {
            for(j=0; j<sizeField; j++)
            {
                fin>>field[i][j].down;
            }
        }
        for(i=0; i<sizeField; i++)
        {
            for(j=0; j<sizeField; j++)
            {
                fin>>field[i][j].right;
                if(field[i][j].right==0)
                {
                    field[i][j].val = 0;
                }
            }
        }
    }
    else cout<<"Not founded"<<endl;
    fin.close();

    //������� ���������� ����� � �����
    for(i=0; i<sizeField; i++)
    {
        for(j=0; j<sizeField; j++)
        {
            q=1;
            if(field[i][j].down>0)
            {
                while(field[i+q][j].val==0) q++;
                field[i][j].q_down = q-1;
            }
        }
    }
    for(i=0; i<sizeField; i++)
    {
        for(j=0; j<sizeField; j++)
        {
            q=1;
            if(field[i][j].right>0)
            {
                while(field[i][j+q].val==0) q++;
                field[i][j].q_right = q-1;
            }
        }
    }

    for(i=0; i<sizeField; i++)
    {
        cout<<endl;
        for(j=0; j<sizeField; j++)
        {
            cout.width(2);
            if(field[i][j].val!=-1) cout<<field[i][j].val;
            else cout<<'.';
        }
    }

    Rec(field);//����� �������, �������� ������ ��������

    //����� ����������
    cout<<endl;
    for(int i=0; i<sizeField; i++)
    {
        cout<<endl;
        for(int j=0; j<sizeField; j++)
        {
            cout.width(2);
            if(field[i][j].val!=-1) cout<<field[i][j].val;
            else cout<<'.';
        }
    }
}
//====================================================================================================================

void Copy(cell arr1[sizeField][sizeField], cell arr2[sizeField][sizeField])
{
    int i, j, t;//��������

    for(i=0; i<sizeField; i++)
    {
        for(j=0; j<sizeField; j++)
        {
            arr2[i][j].down = arr1[i][j].down;
            arr2[i][j].right = arr1[i][j].right;
            arr2[i][j].val = arr1[i][j].val;
            arr2[i][j].q_down = arr1[i][j].q_down;
            arr2[i][j].q_right = arr1[i][j].q_right;
            for(t=0; t<c_max; t++)
            {
                arr2[i][j].pos_down[t] = arr1[i][j].pos_down[t];
                arr2[i][j].pos_right[t] = arr1[i][j].pos_right[t];
            }
        }
    }
}

//====================================================================================================================
bool Rec(cell a[sizeField][sizeField])
{
    int   d, r;
    int   i, j, t;                  //��������
    int   sum_d, sum_r;             //����� ����������� ����� �� ��������� � �����������
    cell  a2[sizeField][sizeField]; //������ ��� ������ ���������� ��������

    for(int i=0; i<sizeField; i++)
    {
        for(int j=0; j<sizeField; j++)
        {
            if(a[i][j].val==0)//���� ����������� ������ ������
            {
                for(t=0; t<c_max; t++)
                {
                    if((a[i][j].pos_down[t]==a[i][j].pos_down[t])&&(a[i][j].pos_down[t]!=0))
                    {
                        Copy(a,a2);
                        a2[i][j].val = a2[i][j].pos_down[t];//���������� ��������� ��������
                        //������� ����� ����� � ������
                        d=0;sum_d = 0;
                        while(a2[i-d][j].val!=-1)
                        {
                            sum_d = sum_d + a2[i-d][j].val;
                            d++;
                        }
                        r=0;sum_r = 0;
                        while(a2[i][j-r].val!=-1)
                        {
                            sum_r = sum_r + a2[i][j-r].val;
                            r++;
                        }
                        //���� ��� ����� ���������
                        if(((sum_d==a2[i-d][j].down)&&((d+1)==a2[i-d][j].q_down))&&((sum_r==a2[i][j-r].right)&&((r+1)==a2[i][j-r].q_right)))
                        {
                            if(Rec(a2)==1) return 1;
                        }
                        //���� ����� �� ��������� �����������
                        else if((sum_d<=a2[i-d][j].down)&&(sum_r<=a2[i][j-r].right))
                        {
                            if(sum_d!=a2[i-d][j].down)
                            {
                                d=0;
                                while(a2[i+d][j].val!=-1)
                                {
                                    a2[i+d][j].pos_down[t] = 0;//������� ��������� �������� �� ��������� ��� ���� ����� � �����
                                    d++;
                                }
                            }
                            if(sum_r!=a2[i][j-r].right)
                            {
                                r=0;
                                while(a2[i][j+r].val!=-1)
                                {
                                    a2[i][j+r].pos_down[t] = 0;
                                    r++;
                                }
                            }

                            if((d!=1)&&(r!=1))//��������� ��������, ���� ���� ��������, � ����� �� ����������
                            {
                                if(Rec(a2)==1)
                                {
                                    field[i][j].val = a[i][j].pos_down[t];
                                    return 1;
                                }
                            }
                        }
                        else return 0;
                    }
                }
                return 0;
            }
        }
    }
}
