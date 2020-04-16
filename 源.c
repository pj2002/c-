#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<process.h>

#define N 10        //评委人数
#define M 2        //歌手人数

struct Singer
{
	int number;//序号
	char name[20];//姓名
	int  score[N];//分数
	int  average;//平均数
	int  scoreAll[N];//十个评委的分数总和
};

int main()
{
	system("color B4");
	char choose;
	int flag = 1;
	void print_star();
	void print_message();
	void print_menu();//菜单函数
	void inputSingerInformation(struct Singer sin[]);//第一个功能
	void inputSingerScore(struct Singer sin[]);//第二个功能
	void caculate(struct Singer sin[]);//计算以及排序第三个功能
	void dataquery(struct Singer sin[]);
	void wdocument(struct Singer sin[]);
	void plusquery();
	struct Singer sin[M], *p = sin;
	void kongge();//空格函数
	void mistake();
	void shuchu(struct Singer sin[]);
	print_star();
	print_message();
	print_star();
	print_menu();
	do
	{
		printf("                                              请输入您想进行的功能:");
		scanf(" %s", &choose);
		switch (choose)
		{
		case  '1': inputSingerInformation(p); break;//输入选手数据函数
		case  '2': inputSingerScore(p); break;//输入评委分数
		case  '3': caculate(p); break;//排序
		case  '4': dataquery(p); break;//数据查询
		case  '5': plusquery(); break;//追加选手数据
		case  '6': wdocument(p); break;//写入文件
		case  '7': exit(0); break;
		case  '8': shuchu(p); break;
		default:mistake();
		}
	} while (1);
	return 0;
}

void print_star()//开始的*号符函数
{
	printf("                             ********************************************************\n");
}
void print_message()
{
	printf("                                              欢迎来到歌手大赛\n");
}
void print_menu()
{
	printf("                                              * 1:输入选手数据\n");
	printf("                                              * 2:评委打分\n");
	printf("                                              * 3:成绩排序\n");
	printf("                                              * 4;数据查询\n");
	printf("                                              * 5:追加选手数据\n");
	printf("                                              * 6:写入数据文件\n");
	printf("                                              * 7:退出系统\n");
}
void inputSingerInformation(struct Singer sin[])//第一个功能输入选手数据
{
	int i;
	kongge();
	printf("请输入选手的编号和名字:\n");
	for (i = 0; i < M; i++)
	{
		kongge();
		scanf("%d %s", &sin[i].number, sin[i].name);
	}
}

void inputSingerScore(struct Singer sin[])
{

	int i, j;
	for (i = 0; i < M; i++)
	{

		kongge();
		printf("请输入第%d个歌手的成绩:\n", i + 1);//提示输入歌手成绩
		for (j = 0; j < N; j++)
		{
			kongge();
			printf("请输入第%d位评委的分数", j + 1);
			scanf("%d", &sin[i].score[j]);//输入十个评委的成绩
		}
	}
}
void caculate(struct Singer sin[])
{
	int i, m, n, t, num, ave, scoreAll[M];
	char nam[20];
	for (i = 0; i < M; i++)
	{
		scoreAll[i] = sin[i].score[0] + sin[i].score[1] + sin[i].score[2] + sin[i].score[3]//求出十个评委的总评分
			+ sin[i].score[4] + sin[i].score[5] + sin[i].score[6] + sin[i].score[7]
			+ sin[i].score[8] + sin[i].score[9];
	}
	for (i = 0; i < M; i++)
	{
		for (m = 0; m < M; m++)
			for (n = 0; n < M - m; n++)
			{
				t = sin[i].score[n];
				sin[i].score[n] = sin[i + 1].score[n];
				sin[i + 1].score[n] = t;
			}  //用冒泡法将十位评委所打的成绩从小到大排序
		sin[i].average = (scoreAll[i] - sin[i].score[0] - sin[i].score[9]) / 8.0;  //用总分减去最高分与最低分算平均分
	}
	for (m = 0; m < M; m++) {
		for (n = 0; n < M - m; n++)
			if (sin[n].average > sin[n + 1].average)                              //比较平均分的大小，将所有的信息按照平均分的排序依次对照
			{
				ave = sin[n].average; sin[n].average = sin[n + 1].average; sin[n + 1].average = ave;
				strcpy(nam, sin[n].name);
				strcpy(sin[n].name, sin[n + 1].name);
				strcpy(sin[n + 1].name, nam);
				num = sin[n].number; sin[n].number = sin[n + 1].number; sin[n + 1].number = num;
			}
	}

	for (i = (M - 1); i >= 0; i--)
	{
		kongge();
		printf("第%d名%s选手的分数是%d\n", sin[i].number, sin[i].name, sin[i].average);
	}
}
void dataquery(struct Singer sin[])
{
	int t, m;
	kongge();
	printf("请输入那位选手的序号");
	scanf("%d", &t);
	; for (int m = 0; m < M; m++)
	{
		if (t == sin[m].number)
		{
			kongge();
			printf("%s选手分数为%d\n", sin[m].name, sin[m].average);
			break;
		}

	}
}
void  wdocument(struct Singer sin[])
{
	FILE *fp;
	fp = fopen("keshe.txt", "w");
	for (int i = 0; i < M; i++)
		fprintf(fp, "%d,%s,%d\n", sin[i].number, sin[i].name, sin[i].average);
	fclose(fp);
	kongge();
	printf("写入成功!\n");
}
void plusquery()
{
	char name[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int number[10], score[10], scoreaverage[10];
	int scoreall[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int m, t;
	kongge();
	printf("输入追加选手的人数");
	scanf("%d", &m);
	for (int k = 3; k < 3 + m; k++)
	{
		kongge();
		printf("请输入选手的编号和名字:\n");
		kongge();
		scanf("%d %s", &number[k], &name);
		kongge();
		printf("请输入第%d个歌手的成绩:\n", k);//提示输入歌手成绩
		for (int j = 0; j < N; j++)
		{
			kongge();
			printf("请输入第%d个评委的分数", j + 1);
			scanf("%d", &score[j]);//输入十个评委的成绩
			scoreall[k] += score[j];
		}
		for (int a = 0; a < 10; a++)
			for (int b = 0; b < 10 - a; b++)
			{
				if (score[b] < score[b + 1])
				{
					t = score[b];
					score[b] = score[b + 1];
					score[b + 1] = t;
				}
			}
		scoreaverage[k] = (scoreall[k] - score[9] - score[0]) / 8;
		FILE *FQ;
		FQ = fopen("keshe.txt", "a");
		for (int i = 3; i < m + 3; i++)
			fprintf(FQ, "%d %s,%d\n", number[k], name, scoreaverage[k]);
		fclose(FQ);
	}
}
void shuchu(struct Singer sin[])
{
	char c;
	FILE*fp = NULL;//需要注意
	fp = fopen("keshe.txt", "r");
	if (NULL == fp)
		return -1;//要返回错误代码
	while (fscanf(fp, "%c", &c) != EOF)
		printf("%c", c); //从文本中读入并在控制台打印出来
	fclose(fp);
	fp = NULL;//需要指向空，否则会指向原打开文件地址    
	return 0;

}
void mistake()
{
	printf("输入错误，请重新输入\n");
	getchar();
}
void kongge()
{
	printf("                                              ");
}
