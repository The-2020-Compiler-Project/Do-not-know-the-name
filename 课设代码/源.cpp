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
protected:
	const char *KT[32] = { "auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","usigned","void","volatile" ,"while"};//关键字
	char *IT[200] = { NULL };//标识符
	char *CT[200] = { NULL };//整数
	char *XT[200] = { NULL };//小数
	char *CTT[200] = { NULL };//字符
	char *ST[200] = { NULL };//字符串
	const char *PT[31] = { ">=","<=","==","=","<",">","+","-","*","/","(",")","[","]","{","}",",",";",".","_","++","--","+=","-=","*=","/=","&","&&","||","!","!=" };//界符
private:
	int state_left;//自动机之前的状态
	int state;//自动机的状态
	char st[10000];//识别出来的字符串
	int num;//st下标，用于判断双目运算符
	int key = 0;//语法出错标志
	int hangshu = 1;//行数
	int key1 = 0;//回车标志
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

//识别器(有限制动机)
//自动机说明状态说明：
//1： 初始状态    2： 关键字/标识符
//3： 正整数      4： 小数点  
//5： 单引号      6： 没遇到引号的字符
//7： 字符        10：字符串
//11：界符        12: 小数
int saomiaoqi::Change_State(int state, char ch)
{
	if ((ch == ' ') || (ch == '\t') || (ch == '\n'))
	{
		if (ch == '\n')
		{
			if (st[num - 1] == ';' || st[num - 1] == '{' || st[num - 1] == '}' || st[num - 1] == ')')
			{

			}
			else if (key1 == 1)
				key1 = 0;
			else
			{
				cout << "第" << hangshu << "行没有';'" << endl;
			}
			hangshu++;
			key1 = 1;
		}
		if (state == 5)
			return 6;
		else if (state == 8 || state == 9)
			return 9;
		else return 0;
	}
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
		else
		{
			key = 1;
			st[num] = ch;
			st[num + 1] = '\0';
			Fenxi(state_left);
			num = 0;
			memset(st, 0, 10);
			return 2;
		}
	}
	else if (IsNumber(ch))
	{
		if (state == 1 || state == 3)
			return 3;
		else if (state == 4)
			return 12;
		else if (state == 12)
			return 12;
		else if (state == 2 && st[num - 1] != '.')
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
			return 3;
		}
		else
		{
			key = 1;
			st[num] = ch;
			st[num + 1] = '\0';
			Fenxi(state_left);
			num = 0;
			memset(st, 0, 10);
			return 3;
		}
	}
	else if (ch == '_')
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
		else
		{
			key = 1;
			st[num] = ch;
			st[num + 1] = '\0';
			Fenxi(state_left);
			num = 0;
			memset(st, 0, 10);
			return 2;
		}
	}
	else if (ch == '.')
	{
		if (state == 2)
		{
			st[num] = '\0';
			Fenxi(state_left);
			num = 0;
			memset(st, 0, 10);
			return 11;
		}
		else if (state == 3)
			return 4;
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
			return 11;
		}
		else
		{
			key = 1;
			st[num] = ch;
			st[num + 1] = '\0';
			Fenxi(state_left);
			num = 0;
			memset(st, 0, 10);
			return 12;
		}
	}
	else if (ch == '\'')
	{
		if (state == 1)
			return 5;
		else if (state == 6)
			return 7;
		else if (state == 8 || state == 9)
			return 9;
		else if (state == 11)
		{
			st[num] = '\0';
			Fenxi(state_left);
			num = 0;
			memset(st, 0, 10);
			return 5;
		}
		else
		{
			key = 1;
			st[num] = ch;
			st[num + 1] = '\0';
			Fenxi(state_left);
			num = 0;
			memset(st, 0, 10);
			return 2;
		}
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
			return 5;
		}
		else
		{
			key = 1;
			st[num] = ch;
			st[num + 1] = '\0';
			Fenxi(state_left);
			num = 0;
			memset(st, 0, 10);
			return 8;
		}
	}
	else
	{
		if (state == 1)
			return 11;
		else if (state == 5)
			return 6;
		else if (state == 8 || state == 9)
			return 9;
		else if ((state == 2) || (state == 3) || (state == 7) || (state == 10) || (state == 12))
		{
			st[num] = '\0';
			Fenxi(state_left);
			num = 0;
			memset(st, 0, 10);
			return 11;
		}
		else if (state == 11)
		{
			if ((num == 1) && (ch == '=') && ((st[0] == '>') || (st[0] == '<') || (st[0] == '=') || (st[0] == '+') || (st[0] == '-') || (st[0] == '*') || (st[0] == '/') || (st[0] == '!')))
				return 11;
			else if ((num == 1) && (ch == '+') && (st[0] == '+'))
				return 11;
			else if ((num == 1) && (ch == '-') && (st[0] == '-'))
				return 11;
			else if ((num == 1) && (ch == '&') && (st[0] == '&'))
				return 11;
			else if ((num == 1) && (ch == '|') && (st[0] == '|'))
				return 11;
			else
			{
				st[num] = '\0';
				Fenxi(state_left);
				num = 0;
				memset(st, 0, 10);
				return 11;
			}
		}
		else
		{
			key = 1;
			st[num] = ch;
			st[num + 1] = '\0';
			Fenxi(state_left);
			num = 0;
			memset(st, 0, 10);
			return 11;
		}
	}
}

//词法分析器
void saomiaoqi::Fenxi(int state_left)
{
	if (key == 1)
	{
		cout << "第" << hangshu << "行  " << st << "  错误" << endl;
		key = 0;
		num = 0;
		memset(st, 0, 10);
	}
	else
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
					token[ptr].number = 0;
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
			for (i = 0; i < 31; ++i)
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
		case 12://数字
			if (XT[0] == NULL)
			{
				XT[0] = (char*)malloc(sizeof(st));
				strcpy(XT[0], st);
				token[ptr].number = 0;
				token[ptr].content = st;
				token[ptr].type = "XT";
				ptr++;
			}
			else
			{
				for (i = 0; i < sizeof(XT) / sizeof(*XT); ++i)
				{
					m = 1;
					if (XT[i] == NULL)
					{
						break;
					}
					if (strcmp(st, XT[i]) == 0)
					{
						token[ptr].number = i;
						token[ptr].content = st;
						token[ptr].type = "XT";
						ptr++;
						m = 0;
						break;
					}
				}
				if (m == 1)
				{
					XT[i] = (char*)malloc(sizeof(st));
					strcpy(XT[i], st);
					token[ptr].number = i;
					token[ptr].content = st;
					token[ptr].type = "XT";
					ptr++;
				}
			}
			break;
		default:
		{
			cout << "第" << hangshu << "行  " << st << "  错误" << endl;
			key = 0;
			num = 0;
			memset(st, 0, 10);
		}
		}
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
	while ((ch = fgetc(fp)))
	{
		state_left = state;
		state = Change_State(state, ch);
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
		if (ch == '#')
			break;
	}
}

int main()
{
	saomiaoqi C;
	C.kongzhi();
	for (int i = 0; i < ptr; i++)
	{
		cout << "<" << token[i].type << "," << token[i].number<<"," << token[i].content << ">" << " ";
	}
	system("pause");
}
