#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "group.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include<QAxObject>
//#include<QtGui>
#include<QString>
#include<QDir>
#include<QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->Button1->setIcon();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_MainWindow_iconSizeChanged(const QSize &iconSize)
{

}

void MainWindow::on_Edit_cursorPositionChanged(int arg1, int arg2)
{

}

void check3()
{
    int finddata[10000];
    //memset(finddata,1,sizeof(finddata));

    int len=findFriends.size();
    int dd[1000];
    pair_my pai[1000];
    int incre=0;
    //memset(dd,0,sizeof(dd));
    for(int i=0;i<1000;i++)
    {
        finddata[i]=1;
        dd[i]=0;
    }

    for(int i=0;i<len-1;i++)
    {
        for(int j=i+1; j<len;j++)
        {
            if(i!=j && equalVector(findFriends[i],findFriends[j])) //发现相同的元素
            {
                //cout<<"发现重复的元素组号："<<i<<" "<<j<<endl;
                //insertVector2(i,j); //这里是插入的index的数值
                pai[incre].i=i;
                pai[incre].j=j;
                incre++;
                dd[i]++;
                dd[j]++;
                finddata[i]=0;
                finddata[j]=0;
            }

        }

    }


    int max=-1;
    int max_index=-1;
    int dow=0;
    int dowe[1000];
    int dota[1000];
    memset(dota,0,sizeof(dota));
    memset(dowe,0,sizeof(dowe));
    while(dow<incre)  //采用的穿插的算法,出现最多的组号首先插入vector
    {
        max=-1;
        for(int i=0;i<len;i++)
        {
            if(dd[i]>=max&&dowe[i]==0)
            {
                max=dd[i];
                max_index=i;
            }

        }
        for(int k=0;k<incre;k++)
        {
            if(dota[k]==0)
            {
                if(pai[k].i==max_index||pai[k].j==max_index)
                {
                    insertVector2(pai[k].i,pai[k].j);
                    dota[k]=1;
                }

            }
        }
        dow++;
    }

    //

    for(int i=0;i<findVector.size();i++)
    {
        //cout<<"队员有重复的组号：";
        set<int> temp;
        for(int j=0;j<findVector[i].size();j++)
        {
            //cout<<findVector[i][j]<<" ";   //输出重复的组号
            for(int h=0;h<findFriends[findVector[i][j]].size();h++)
                temp.insert(findFriends[findVector[i][j]][h]);

        }
        Friends2.push_back(temp);
        temp.clear();
    }

    //没有重复元素的组号
    for(int i=0;i<findFriends.size();i++)
    {
        if(finddata[i]==1)
        {
            set<int>temp;
            for(int h=0;h<findFriends[i].size();h++)
            {
                temp.insert(findFriends[i][h]);
            }
            Friends2.push_back(temp);
        }
    }
    for(int i=0;i<2*N+1;i++)
        Result[i]=0;

    ofstream outfile("result.txt");

    outfile.close();

}

void Group()
{
    //cout<< "这里设置的中国人为"<<N<<"，外国人最大数目为"<<N<<"。 如果想要更换最大数目，请重新编译执行\n\n";
    memset(form,0,sizeof(form));


    ifstream infile;
    infile.open("input.txt");
    string s;
    while(getline(infile,s))
    {
        char sa[1000];
        for( int i=0;i<s.length();i++)
            sa[i] = s[i];
        sa[s.length()]='\0';
        const char *d = " :：,，";
        char *p;
        p = strtok(sa,d);
        int input1=0;
        int input2=0;
        while(p)
        {
            if(atoi(p)==0)
            {
                input2=((char)toupper(p[0])-64);
            }else
            {
                input1=atoi(p);
            }
            form[input1][input2]++;
            p=strtok(NULL,d);
        }

    }

    infile.close();
    for(int i=1;i<=N;i++)
    {
        for(int jj=1;jj<=N;jj++)
        {
            if(form[i][jj]>1)
            insertVector(i,jj);
        }
    }

    check3();

}

void setNumber(set<int> g1,set<int>g2,int &desk,int &cf,Ui::MainWindow *ui)
{
        int c=1,f=1;
        for(set<int>::iterator it=g1.begin();it!=g1.end();it++) //中国人在label上面写数字
        {
             QString str=QString::number(2*(c+desk),10);
             QLabel *la=ui->centralWidget->findChild<QLabel*>("label_"+str);
             la->setText(QString::number(*it,10));
             cout<<*it<<"  ";
             c++;
             QString str2=QString::number(max(c,f)-1+desk,10);
             QPushButton *da=ui->centralWidget->findChild<QPushButton*>("Button"+str2);
             da->setText(QString::number(cf,10));

        }
        for(set<int>::iterator it=g2.begin();it!=g2.end();it++)
        {
            QString str=QString::number(2*(f+desk)+1,10);
            QLabel *la=ui->centralWidget->findChild<QLabel*>("label_"+str);
            la->setText(QString("")+char(*it-N+64));
            cout<<char(*it-N+64)<<"  ";
            f++;
            QString str2=QString::number(max(c,f)-1+desk,10);
            QPushButton *da=ui->centralWidget->findChild<QPushButton*>("Button"+str2);
            da->setText(QString::number(cf,10));
        }
       desk=desk+max(c,f);// 桌子编号整体上升

       //多余的一张桌子隐去
       QString str=QString::number(desk,10);
       QPushButton *da=ui->centralWidget->findChild<QPushButton*>("Button"+str);
       da->hide();

       cf=cf+1;
       cout<<endl;
}

void MainWindow::on_Start_clicked()
{
    int gz=0; //每组最多的人数
    QString gzstr=ui->Edit3->text();
    if(!gzstr.isEmpty())
        gz=gzstr.toInt();

    //如果gz 是奇数则变为偶数
    if(gz%2!=0)
        gz++;

    Group();  //分组
    int cf=1;
    int desk=0;
    for(int i=0;i<Friends2.size();i++)
    {
        cout<<"Group:"<<cf<<":"<<endl;
        set<int>g_1; //存储中国人编号
        set<int>g_2;  //存储外国人编号
        for(set<int>::iterator it=Friends2[i].begin();it!=Friends2[i].end();it++)
        {
            Result[*it]=1;
            if(*it<=N)
            {
               g_1.insert(*it);
            }else
            {
                g_2.insert(*it);
            }
        }
        if(gz==0) //没有限制每组的最多人数
        {
            setNumber(g_1,g_2,desk,cf,ui);
        }else   //限制了每组的最多人数
        {
            //将set 数据存储到数组中
            int gg1[100];
            int gg2[100];
            int countgg=0;
            for(set<int>::iterator it=g_1.begin();it!=g_1.end();it++)
            {
                gg1[countgg]=*it;
                countgg++;
            }
            countgg=0;
            for(set<int>::iterator it=g_2.begin();it!=g_2.end();it++)
            {
                gg2[countgg]=*it;
                countgg++;
            }
            set<int>g1[10]; //定义存储每个小组的最大的人数
            set<int>g2[10];
            int iter1=0;
            int nums=0;
            int numsmin=g_1.size()>g_2.size()?g_2.size():g_1.size(); //找到最小的组的人数
            int zushu=ceil(numsmin/(double)(gz/2));//向上取整的组数
            for(int zs=1;zs<zushu;zs++)
            {

                g1[nums].insert(gg1+iter1,gg1+iter1+gz/2);
                g2[nums].insert(gg2+iter1,gg2+iter1+gz/2);
                iter1=iter1+gz/2;
                nums++;
            }
            //剩余的划分为一组
            g1[nums].insert(gg1+iter1,gg1+g_1.size());
            g2[nums].insert(gg2+iter1,gg2+g_2.size());

            //分组完毕，在桌子上写上编号
            for(int ni=0;ni<=nums;ni++)
            {
                 setNumber(g1[ni],g2[ni],desk,cf,ui);
            }

        }
        //setNumber(g1,g2,desk,cf,ui);

    }
    cout<<"no Group: \n";
    int max1=26,max2=26;
    QString te=ui->Edit1->text(); //中国人数量
    if(!te.isEmpty())
        max1=te.toInt();
    QString te2=ui->Edit2->text(); //外国人数量
    if(!te2.isEmpty())
        max2=te2.toInt();

    int c=1,f=1;
    for(int i=1;i<=2*N;i++)
    {
        if(Result[i]==0)
        {
            if(i<=N&&i<=max1)
            {
                QString str=QString::number(2*(c+desk),10);
                QLabel *la=QMainWindow::centralWidget()->findChild<QLabel*>("label_"+str);
                la->setText(QString::number(i,10));
                cout<<i<<"  ";
                c++;
            }else if(i>N&&i<=N+max2)
            {
                QString str=QString::number(2*(f+desk)+1,10);
                QLabel *la=QMainWindow::centralWidget()->findChild<QLabel*>("label_"+str);
                la->setText(QString("")+char(i-N+64));
                cout<<char(i-N+64)<<"  ";
                f++;
            }

        }

    }
    cout<<endl;
    ui->Start->hide();

}

void MainWindow::on_actionPriori_2_triggered()
{

}

struct name_Count
{
    int name;
    int count;
};

//将数据保存到Excel主程序
void toExcel(QString te,QString te2,name_Count*all_result,int &size)
{
    ifstream infile;
    infile.open("input.txt");
    string s;
    int vote[2*N+1]={0};//这里是投票的统计

    while(getline(infile,s))
    {
        //将每一行的数据进行统计
        char sa[1000];
        for( int i=0;i<s.length();i++)
            sa[i] = s[i];
        sa[s.length()]='\0';
        const char *d = " :：,，";
        char *p;
        p = strtok(sa,d);
        while(p)
        {
            p=strtok(NULL,d);//被投票的人
            if(p!=NULL)
            {
                if(atoi(p)==0) //外国人
                {
                    vote[((char)toupper(p[0])-64)+N]++;
                }else
                {
                    vote[atoi(p)]++; //中国人
                }
            }
        }

    }

    infile.close();

    int max1=26,max2=26;

    if(!te.isEmpty())
       max1=te.toInt();
    if(!te2.isEmpty())
        max2=te2.toInt();

    name_Count all[2*N+1];
    for(int i=0;i<=max1;i++)
    {
        all[i].name=i;
        all[i].count=vote[i];
    }
    for(int i=N+1;i<=N+max2;i++)
    {
        all[max1+i-N].name=i;
        all[max1+i-N].count=vote[i];
    }
    //冒泡排序对所有人进行排序
    for (int i = 1; i < max1+max2; i++)
       {
           for (int j = i + 1; j < max1+max2; j++)
           {
               if (all[i].count < all[j].count)
               {
                   name_Count temp;
                   temp.name=all[i].name;
                   temp.count=all[i].count;

                   all[i].name=all[j].name;
                   all[i].count=all[j].count;

                   all[j].name=temp.name;
                   all[j].count=temp.count;
               }
           }
       }

    for(int i=1;i<=max1+max2;i++)
    {
        all_result[i].name=all[i].name;
        all_result[i].count=all[i].count;
    }
    size=max1+max2;


}
void MainWindow::on_SaveButton_clicked()
{
    QString te=ui->Edit1->text(); //中国人数量
    QString te2=ui->Edit2->text(); //外国人数量
    int size;
    name_Count all[2*N+1];
    toExcel(te,te2,all,size);
    for(int i=1;i<=size;i++)
    {

        cout<<"Name: "<<all[i].name <<"  count:" <<all[i].count<<endl;

    }

    QString filepath=QFileDialog::getSaveFileName(this,tr("Save orbit"),".",tr("Microsoft Office 2007 (*.xlsx)"));
    if(!filepath.isEmpty()){
     QAxObject *excel = new QAxObject(this);
    excel->setControl("Excel.Application");//连接Excel控件
    excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
    excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示

    QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
    workbooks->dynamicCall("Add");//新建一个工作簿
    QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
    QAxObject *worksheets = workbook->querySubObject("Sheets");//获取工作表集合
    QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);//获取工作表集合的工作表1，即sheet1

    QAxObject *cellA,*cellB,*cellC,*cellD;

    //设置标题
    int cellrow=1;
    QString A="A"+QString::number(cellrow);//设置要操作的单元格，如A1
    QString B="B"+QString::number(cellrow);
    QString C="C"+QString::number(cellrow);
    QString D="D"+QString::number(cellrow);
    cellA = worksheet->querySubObject("Range(QVariant, QVariant)",A);//获取单元格
    cellB = worksheet->querySubObject("Range(QVariant, QVariant)",B);
    cellC=worksheet->querySubObject("Range(QVariant, QVariant)",C);
    cellD=worksheet->querySubObject("Range(QVariant, QVariant)",D);
    cellA->dynamicCall("SetValue(const QVariant&)",QVariant("姓名"));//设置单元格的值
    cellB->dynamicCall("SetValue(const QVariant&)",QVariant("投票数"));
    //设置A列的第二个单元格
   // cellrow++;
  //  A="A"+QString::number(cellrow);
 //   cellA = worksheet->querySubObject("Range(QVariant, QVariant)",A);//获取单元格
 //   cellA->dynamicCall("SetValue(const QVariant&)",QVariant("流水号2"));//设置单元格的值

  //  cellC->dynamicCall("SetValue(const QVariant&)",QVariant("金额"));
   // cellD->dynamicCall("SetValue(const QVariant&)",QVariant("日期"));
    cellrow++;
    for(int i=1;i<=size;i++)
    {
        A="A"+QString::number(cellrow);
        cellA = worksheet->querySubObject("Range(QVariant, QVariant)",A);//获取单元格
        if(all[i].name>N)
        {
            QString x=(QChar)(all[i].name-N+64);
            cellA->dynamicCall("SetValue(const QVariant&)",QVariant(x));//设置单元格的值
        }else
        {
              cellA->dynamicCall("SetValue(const QVariant&)",QVariant(QString::number(all[i].name)));//设置单元格的值
        }
        B="B"+QString::number(cellrow);
        cellB = worksheet->querySubObject("Range(QVariant, QVariant)",B);
        cellB->dynamicCall("SetValue(const QVariant&)",QVariant(all[i].count));
        cellrow++;

    }
    workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(filepath));//保存至filepath，注意一定要用QDir::toNativeSeparators将路径中的"/"转换为"\"，不然一定保存不了。
    workbook->dynamicCall("Close()");//关闭工作簿
    excel->dynamicCall("Quit()");//关闭excel
    delete excel;
    excel=NULL;
    }

}
