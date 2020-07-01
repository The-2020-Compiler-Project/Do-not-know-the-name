#include<iostream>
#include<string>
#include<fstream>
#pragma warning (disable:4996)
using namespace std;

typedef struct Token
{
	string type, content;
	int number;
};

Token token[10000];
static int ptr = 0;//token下标

class saomiaoqi
{
public:
	saomiaoqi() {}
	~saomiaoqi() {}
	int Change_State(int state, char ch);//识别器
	void Fenxi(int state_left);//分析器
	void kongzhi();//控制器
	int IsWord(char a);//判断是否为字母
	int IsNumber(char a);//判断是否为数字
	int IsKeyword(char *word);//判断是否为关键字
	int IsJiefu(char *mark);//判断是否为界符
protected:
	const char *KT[32] = { "auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","usigned","void","volatile" ,"while"};//关键字
	char *IT[200] = { NULL };//标识符
	char *CT[200] = { NULL };//常数
	char *CTT[200] = { NULL };//字符
	char *ST[200] = { NULL };//字符串
	const char *PT[26] = { ">=","<=","==","=","<",">","+","-","*","/","(",")","[","]","{","}",",",";",".","_","++","--","+=","-=","*=","/=" };//界符
private:
	int state_left;//自动机之前的状态
	int state;//自动机的状态
	char st[10];//识别出来的字符串
	int num;//st下标，用于判断双目运算符
};

//判断是否为字母
int saomiaoqi::IsWord(char a)
{
	if (((a >= 'a') && (a <= 'z')) || ((a >= 'A') && (a <= 'Z')))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//判断是否为数字
int saomiaoqi::IsNumber(char a)
{
	if ((a >= '0') && (a <= '9'))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//判断是否为关键字
int saomiaoqi::IsKeyword(char *word)
{
	for (int i = 0; i < 32; i++)
	{
		if (strcmp(word, KT[i]) == 0)
		{
			if (i == 0)
			{
				return 2;
			}
			return 1;
		}
	}
	return 0;
}

//判断是否为界符
int saomiaoqi::IsJiefu(char *mark)
{
	for (int i = 0; i < 26; i++)
	{
		if (strcmp(mark, PT[i]) == 0)
		{
			if (i == 0)
			{
				return 2;
			}
			return 1;
		}
	}
	return 0;
}

//识别器(有限制动机)
//自动机说明状态说明：
//1： 初始状态 2：   关键字/标识符
//3： 正整数   4->3：小数
//7： 字符     10：   字符串
//11：界符
int saomiaoqi::Change_State(int state, char ch)
{
	if ((ch == ' ') || (ch == '\t') || (ch == '\n'))
		return 0;
	else if (IsWord(ch))
	{
		if (state == 1 || state == 2)
			return 2;
		else if (state == 5)
			return 6;
		else if (state == 8 || state == 9)
			return 9;
		else if (state == 11)
		{
			st[num] = '\0';
			Fenxi(state_left);
			num = 0;
			memset(st, 0, 10);
			return 2;
		}
		else return -1;
	}
	else if (IsNumber(ch) == 1)
	{
		if (state == 1 || state == 3 || state == 4)
			return 3;
		else if (state == 2)
			return 2;
		else if (state == 11)
		{
			st[num] = '\0';
			Fenxi(state_left);
			num = 0;
			memset(st, 0, 10);
			return 3;
		}
		else return -1;
	}
	else if (ch == '_')
	{
		if (state == 1 || state == 2)
		{
			return 2;
		}
		else if (state == 11)
		{
			st[num] = '\0';
			Fenxi(state_left);
			num = 0;
			memset(st, 0, 10);
			return 2;
		}
		else return -1;
	}
	else if (ch == '.')
	{
		if (state == 2)
			return 11;
		else if (state == 3)
			return 4;
		else return -1;
	}
	else if (ch == '\'')
	{
		if (state == 1)
			return 5;
		else if (state == 6)
		{
			return 7;
		}
		else if (state == 11)
		{
			st[num] = '\0';
			Fenxi(state_left);
			num = 0;
			memset(st, 0, 10);
			return 5;
		}
		else return -1;
	}
	else if (ch == '\"')
	{
		if (state == 1)
			return 8;
		else if (state == 9)
			return 10;
		else if (state == 11)
		{
			st[num] = '\0';
			Fenxi(state_left);
			num = 0;
			memset(st, 0, 10);
			return 8;
		}
		else return -1;
	}
	else
	{
		if (state == 1)
			return 11;
		else if (state == 9)
		{
			return 9;
		}
		else if (state == 2)
		{
			st[num] = '\0';
			Fenxi(state_left);
			num = 0;
			memset(st, 0, 10);
			return 11;
		}
		else if (state == 3)
		{
			st[num] = '\0';
			Fenxi(state_left);
			num = 0;
			memset(st, 0, 10);
			return 11;
		}
		else if (state == 7)
		{
			st[num] = '\0';
			Fenxi(state_left);
			num = 0;
			memset(st, 0, 10);
			return 11;
		}
		else if (state == 10)
		{
			st[num] = '\0';
			Fenxi(state_left);
			num = 0;
			memset(st, 0, 10);
			return 11;
		}
		else if (state == 11)
		{
			if ((num == 1) && (ch == '=') && ((st[0] == '>') || (st[0] == '<') || (st[0] == '=') || (st[0] == '+') || (st[0] == '-') || (st[0] == '*') || (st[0] == '/')))
				return 11;
			else if ((num == 1) && (ch == '+') && (st[0] == '+'))
				return 11;
			else if ((num == 1) && (ch == '-') && (st[0] == '-'))
				return 11;
			else
			{
				st[1] = '\0';
				Fenxi(state_left);
				num = 0;
				memset(st, 0, 10);
				st[0] = ch;
				st[1] = '\0';
				Fenxi(state_left);
				num = 0;
				memset(st, 0, 10);
				return 0;
			}
		}
		else return -1;
	}
}

//词法分析器
void saomiaoqi::Fenxi(int state_left)
{
	int i, n, m;
	switch (state_left)
	{
	case 2://关键字（标识符）
		for (i = 0; i < 32; ++i)
		{
			n = 1;
			if (strcmp(st, KT[i]) == 0)
			{
				token[ptr].number = i;
				token[ptr].content = st;
				token[ptr].type = "KT";
				ptr++;
				n = 0;
				break;
			}
		}
		if (n == 1)
		{
			if (IT[0] == NULL)
			{
				IT[0] = (char*)malloc(sizeof(st));
				strcpy(IT[0], st);
				token[ptr].number = i;
				token[ptr].content = st;
				token[ptr].type = "IT";
				ptr++;
			}
			else
			{
				for (i = 0; i < sizeof(IT) / sizeof(*IT); ++i)
				{
					m = 1;
					if (IT[i] == NULL)
					{
						break;
					}
					if (strcmp(st, IT[i]) == 0)
					{
						token[ptr].number = i;
						token[ptr].content = st;
						token[ptr].type = "IT";
						ptr++;
						m = 0;
						break;
					}
				}
				if (m == 1)
				{
					IT[i] = (char*)malloc(sizeof(st));
					strcpy(IT[i], st);
					token[ptr].number = i;
					token[ptr].content = st;
					token[ptr].type = "IT";
					ptr++;
				}
			}
		}
		break;
	case 3://数字
		if (CT[0] == NULL)
		{
			CT[0] = (char*)malloc(sizeof(st));
			strcpy(CT[0], st);
			token[ptr].number = 0;
			token[ptr].content = st;
			token[ptr].type = "CT";
			ptr++;
		}
		else
		{
			for (i = 0; i < sizeof(CT) / sizeof(*CT); ++i)
			{
				m = 1;
				if (CT[i] == NULL)
				{
					break;
				}
				if (strcmp(st, CT[i]) == 0)
				{
					token[ptr].number = i;
					token[ptr].content = st;
					token[ptr].type = "CT";
					ptr++;
					m = 0;
					break;
				}
			}
			if (m == 1)
			{
				CT[i] = (char*)malloc(sizeof(st));
				strcpy(CT[i], st);
				token[ptr].number = i;
				token[ptr].content = st;
				token[ptr].type = "CT";
				ptr++;
			}
		}
		break;
	case 7://字符
		if (CTT[0] == NULL)
		{
			CTT[0] = (char*)malloc(sizeof(st));
			strcpy(CTT[0], st);
			token[ptr].number = 0;
			token[ptr].content = st;
			token[ptr].type = "CTT";
			ptr++;
		}
		else
		{
			for (i = 0; i < sizeof(CTT) / sizeof(*CTT); ++i)
			{
				m = 1;
				if (CTT[i] == NULL)
				{
					break;
				}
				if (strcmp(st, CTT[i]) == 0)
				{
					token[ptr].number = i;
					token[ptr].content = st;
					token[ptr].type = "CTT";
					ptr++;
					m = 0;
					break;
				}
			}
			if (m == 1)
			{
				CTT[i] = (char*)malloc(sizeof(st));
				strcpy(CTT[i], st);
				token[ptr].number = i;
				token[ptr].content = st;
				token[ptr].type = "CTT";
				ptr++;
			}
		}
		break;
	case 10://字符串
		if (ST[0] == NULL)
		{
			ST[0] = (char*)malloc(sizeof(st));
			strcpy(ST[0], st);
			token[ptr].number = 0;
			token[ptr].content = st;
			token[ptr].type = "ST";
			ptr++;
		}
		else
		{
			for (i = 0; i < sizeof(ST) / sizeof(*ST); ++i)
			{
				m = 1;
				if (ST[i] == NULL)
				{
					break;
				}
				if (strcmp(st, ST[i]) == 0)
				{
					token[ptr].number = i;
					token[ptr].content = st;
					token[ptr].type = "ST";
					ptr++;
					m = 0;
					break;
				}
			}
			if (m == 1)
			{
				ST[i] = (char*)malloc(sizeof(st));
				strcpy(ST[i], st);
				token[ptr].number = i;
				token[ptr].content = st;
				token[ptr].type = "ST";
				ptr++;
			}
		}
		break;
	case 11://界符
		for (i = 0; i < 26; ++i)
		{
			if (strcmp(st, PT[i]) == 0)
			{
				token[ptr].number = i;
				token[ptr].content = st;
				token[ptr].type = "PT";
				ptr++;
				break;
			}
		}
		break;
	default:
		printf("error");
	}
}

void saomiaoqi::kongzhi()
{
	char ch;
	state = 1;//初始状态
	num = 0;
	FILE *fp;
	if ((fp = fopen("C.txt", "r+")) == NULL)
	{
		cout << "cann't open C.txt" << endl;
		exit(1);
	}
	while ((ch = fgetc(fp)) != '#')
	{
		state_left = state;
		state = Change_State(state, ch);
		if (state == -1)
		{
			printf("error");
		}
		if (state != 0)
		{
			st[num++] = ch;
		}
		else
		{
			st[num] = '\0';
			if (state_left != 1)
				Fenxi(state_left);
			memset(st, 0, 10);
			num = 0;
			state = 1;
		}
	}
}
