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
static int ptr = 0;//token�±�

class saomiaoqi
{
public:
	saomiaoqi() {}
	~saomiaoqi() {}
	int Change_State(int state, char ch);//ʶ����
	void Fenxi(int state_left);//������
	void kongzhi();//������
	int IsWord(char a);//�ж��Ƿ�Ϊ��ĸ
	int IsNumber(char a);//�ж��Ƿ�Ϊ����
protected:
	const char *KT[32] = { "auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","usigned","void","volatile" ,"while"};//�ؼ���
	char *IT[200] = { NULL };//��ʶ��
	char *CT[200] = { NULL };//����
	char *XT[200] = { NULL };//С��
	char *CTT[200] = { NULL };//�ַ�
	char *ST[200] = { NULL };//�ַ���
	const char *PT[31] = { ">=","<=","==","=","<",">","+","-","*","/","(",")","[","]","{","}",",",";",".","_","++","--","+=","-=","*=","/=","&","&&","||","!","!=" };//���
private:
	int state_left;//�Զ���֮ǰ��״̬
	int state;//�Զ�����״̬
	char st[10000];//ʶ��������ַ���
	int num;//st�±꣬�����ж�˫Ŀ�����
	int key = 0;//�﷨�����־
	int hangshu = 1;//����
};

//�ж��Ƿ�Ϊ��ĸ
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

//�ж��Ƿ�Ϊ����
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

//ʶ����(�����ƶ���)
//�Զ���˵��״̬˵����
//1�� ��ʼ״̬ 2��   �ؼ���/��ʶ��
//3�� ������   4��   С����  12:С��
//5�� ������   6��   û�������ŵ��ַ�
//7�� �ַ�     10��   �ַ���
//11�����
int saomiaoqi::Change_State(int state, char ch)
{
	if ((ch == ' ') || (ch == '\t') || (ch == '\n'))
	{
		if (ch == '\n')
		{
			if (st[num - 1] == ';' || st[num - 1] == '{' || st[num - 1] == '}' || st[num - 1] == ')')
			{
				
			}
			else
			{
				cout << "��" << hangshu << "��û��';'" << endl;
			}
			hangshu++;
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
		if (state == 1 || state == 3 || state == 4)
			return 3;
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
			return 5;
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
		else if ((state == 2) || (state == 3) || (state == 7) || (state == 10))
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

//�ʷ�������
void saomiaoqi::Fenxi(int state_left)
{
	if (key == 1)
	{
		cout << "��" << hangshu << "��" << st << "������" << endl;
		key = 0;
		num = 0;
		memset(st, 0, 10);
	}
	else
	{
		int i, n, m;
		switch (state_left)
		{
		case 2://�ؼ��֣���ʶ����
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
		case 3://����
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
		case 7://�ַ�
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
		case 10://�ַ���
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
		case 11://���
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
		default:
		{
			cout << "��" << hangshu << "��" << st << "������" << endl;
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
	state = 1;//��ʼ״̬
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
