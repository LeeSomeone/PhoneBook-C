#include "phoneBook.h"

int main()
{
	char input;
	Node* beginList = NULL;
	Node* endList = NULL;
	Page *page;

	InitNode(11,&beginList,&endList);
	page = PageInfo(beginList,10);

	while(1)
	{
		printf("1.�鿴ͨѶ¼\n");
		printf("2.���ͨѶ¼\n");
		printf("3.��ѯͨѶ¼\n");
		printf("4.�޸�ͨѶ¼\n");
		printf("5.ɾ��ͨѶ¼\n");
		printf("6.�˳�ͨѶ¼\n");

		input = GetKey();
		switch (input)
		{
		case '1':
			g_menu_type = 1;
			CheckPhoneBook(beginList);
			break;
		case '2':
			AddNode(&beginList,&endList,GetNodeIn());
			break;
		case '3':
			g_menu_type = 3;
			QueryPhoneBook(beginList);
			break;
		case '4':
			g_menu_type = 4;
			UpdataPhoneBook(beginList);
			break;
		case '5':
			g_menu_type = 5;
			DeletePhoneBook(&beginList, &endList);
			break;
		case '6':
			return 0;
			break;
		default:
			printf("�������ʾ������ȷ������\n\n");
			break;
		}
	}

	return 0;
}

void AddNode(Node** beginList,Node** endList,Node* node)
{
	if(NULL == *beginList)
	{
		*beginList = node;
	}
	else
	{
		(*endList)->pNext = node;
	}
	*endList = node;
}

Node* GetNode(char* name, char* phone)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->num = GetNum();
	node->name = name;
	node->phone = phone;
	node->pNext = NULL;

	return node;
}

void InitNode(int count,Node** beginList,Node** endList)
{
	int i;
	srand((unsigned int) time(NULL));
	for (i = 0; i < count; i++)
	{
		AddNode(beginList,endList,GetNode(GetName(),GetPhone()));
	}
}

void DelNode(int num, Node** beginList,Node** endList)
{
	Node* beginList_flag = *beginList;
	Node* del = NULL;

	if (num == (*beginList)->num)
	{
		*beginList = (*beginList)->pNext;
		free(del);
		del = NULL;

		return;
	}

	while(beginList_flag->pNext != NULL)
	{
		if (num == beginList_flag->pNext->num)
		{
			del = beginList_flag->pNext;
			beginList_flag->pNext = beginList_flag->pNext->pNext;
			free(del);
			del = NULL;

			if (NULL == beginList_flag->pNext)
			{
				*endList = beginList_flag;
			}

			return;
		}
		beginList_flag = beginList_flag->pNext;
	}
}

int GetNum()
{
	static int i = 1;
	return i++;
}

char* GetName()
{
	char* name = (char*)malloc(9);
	char str[2] = {0};
	int i;
	*name = 0;

	for (i = 0; i < 8; i++)
	{
		str[0] = rand()%(122-97)+97;
		strcat_s(name,9,str);
	}

	return name;
}

char* GetPhone()
{
	char* phone = (char*)malloc(12);
	char str[2];
	int i;

	switch (rand()%5)
	{
	case 0:
		strcpy_s(phone,12,"137");
		break;
	case 1:
		strcpy_s(phone,12,"138");
		break;
	case 2:
		strcpy_s(phone,12,"139");
		break;
	case 3:
		strcpy_s(phone,12,"170");
		break;
	case 4:
		strcpy_s(phone,12,"189");
		break;
	default:
		strcpy_s(phone,12,"188");
		break;
	}

	for (i = 0; i < 8; i++)
	{
		_itoa_s(rand()%10,str,2,10);
		strcat_s(phone,12,str);
	}

	return phone;
}

char* GetString()
{
	char c;
	int size = 5;
	int count = 0;
	char* str = (char*)malloc(size);
	char* bjStr = str;
	char* newStr = NULL;

	while((c = getchar()) != '\n')
	{
		count++;
		*str++ = c;

		if ((count + 1) == size)
		{
			*str = '\0';
			size += 5;

			newStr = (char*)malloc(size);
			strcpy_s(newStr,size,bjStr);
			free(bjStr);

			bjStr = newStr;
			str = newStr + count;
		}
	}

	*str = '\0';
	return bjStr;
}

char GetKey()
{
	char c = -1;
	char v = -1;
	while((v = getchar()) != '\n' || c == -1)
	{
		c = v;
	}

	return c;
}

Node* GetNodeIn()
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->num = GetNum();

	while(1)
	{
		printf("������������ \n");
		node->name = GetString();
		printf("������绰�� \n");
		node->phone = GetString();
		node->pNext = NULL;

		printf("��ȷ����ӱ�ţ� %d ������%s �绰��%s\n\n",node->num,node->name,node->phone);
		printf("y��ȷ�ϣ���������������\n");
		if (GetKey() != 'y')
		{
			continue;
		}
		else
		{
			printf("��ӳɹ���\n");
			return node;
		}
	}
	return node;
}

Page* PageInfo(Node* beginList,int onePageItem)
{
	Page* page = (Page*)malloc(sizeof(Page));
	page->totalItem = 0;
	page->totalPage = 0;
	page->currentPage =0;
	page->onePageItem = onePageItem;

	while(beginList != NULL)
	{
		page->totalItem++;
		beginList = beginList->pNext;
	}

	page->totalPage = page->totalItem % onePageItem ? page->totalItem / onePageItem + 1 : page->totalItem / onePageItem;

	return page;
}

void showInfo(Node* beginList, Page* page)
{
	int begin = (page->currentPage - 1) * 10 + 1;
	int end = page->currentPage * 10;
	int count = 0;

	printf("���\t ����\t\t �绰\t\n");
	while(beginList != NULL)
	{
		count++;
		if (count >= begin && count <= end)
		{
			printf("%d\t %s\t %s\t\n",beginList->num,beginList->name,beginList->phone);
		}
		beginList = beginList->pNext;
	}
}
void showMenu(Page* page)
{
	switch (g_menu_type)
	{
	case 1:
		printf("��%dҳ ��%d������ ��ǰ��%dҳ w��һҳ s��һҳ b����\n",page->totalPage,page->totalItem,page->currentPage);
		break;
	case 3:
		printf("��%dҳ ��%d������ ��ǰ��%dҳ c���²�ѯ w��һҳ s��һҳ b����\n",page->totalPage,page->totalItem,page->currentPage);
		break;
	case 4:
		printf("��%dҳ ��%d������ ��ǰ��%dҳ u�޸���Ϣ w��һҳ s��һҳ b����\n",page->totalPage,page->totalItem,page->currentPage);
		break;
	case 5:
		printf("��%dҳ ��%d������ ��ǰ��%dҳ dɾ����Ϣ w��һҳ s��һҳ b����\n",page->totalPage,page->totalItem,page->currentPage);
		break;
	default:
		printf("��%dҳ ��%d������ ��ǰ��%dҳ w��һҳ s��һҳ b����\n",page->totalPage,page->totalItem,page->currentPage);
		break;
	}
}

void OpeartPage(Node* beginList,Page* page)
{
	char key = 's';
	while(key != 'b')
	{
		switch (key)
		{
		case 's':
			if (page->currentPage == page->totalPage)
			{
				printf("��ǰ�Ѿ������һҳ������\n");
			} 
			else
			{
				system("cls");
				page->currentPage++;
				showInfo(beginList,page);
				showMenu(page);
			}
			break;
		case 'w':
			if (page->currentPage == 1)
			{
				printf("��ǰ�Ѿ��ǵ�һҳ������\n");
			} 
			else
			{
				system("cls");
				page->currentPage--;
				showInfo(beginList,page);
				showMenu(page);
			}
			break;
		case 'u':
		case 'c':
		case 'd':
			return;
			break;
		default:
			printf("�������󣡣�\n");
			break;
		}
		g_key = key = GetKey();
	}
}

void CheckPhoneBook(Node* beginList)
{
	Page* page = PageInfo(beginList,10);
	OpeartPage(beginList,page);
}

void QueryPhoneBook(Node* beginList)
{
	char* keyword = NULL;
	char key = 0;
	Node* node = NULL;
	Node* beginList_flag = NULL;
	Node* newBegin = NULL;
	Node* newEnd = NULL;
	Node* del;

	while(1)
	{

		while(1)
		{
			printf("�������ѯ�Ĺؼ��֣� \n");
			keyword = GetString();
			printf("��ȷ�ϲ�ѯ�Ĺؼ��֣� %s ȷ���밴a ���������²�ѯ\n",keyword);
			key = GetKey();
			if (key == 'a')
			{
				break;
			} 
			else
			{
				free(keyword);
				keyword = NULL;
			}
		}

		beginList_flag = beginList;
		while(beginList_flag != NULL)
		{
			if (strncmp(beginList_flag->name,keyword,strlen(keyword)) == 0
				|| strncmp(beginList_flag->phone,keyword,strlen(keyword)) == 0)
			{
				node = (Node*)malloc(sizeof(Node));
				node->num = beginList_flag->num;
				node->name = beginList_flag->name;
				node->phone = beginList_flag->phone;
				node->pNext = NULL;

				AddNode(&newBegin,&newEnd,node);
			}
			beginList_flag = beginList_flag->pNext;
		}

		if (newBegin != NULL)
		{
			CheckPhoneBook(newBegin);

			while(newBegin)
			{
				del = newBegin;
				newBegin = newBegin->pNext;
				free(del);
				del = NULL;
			}
		}
		else
		{
			printf("û�иùؼ��֣���\n");
		}

		if (g_key == 'b' || g_key == 'u' || g_key == 'd')
		{
			return;
		}
	}
}

void UpdataPhoneBook(Node* beginList)
{
	int num = 0;
	Node *beginList_flag = NULL;
	QueryPhoneBook(beginList);

	if (g_key == 'b')
	{
		return;
	}

	if (g_key == 'u')
	{
		while(1)
		{
			printf("������Ҫ�޸ĵı�ţ� \n");
			num = atoi(GetString());

			beginList_flag = beginList;
			while(beginList_flag != NULL)
			{
				if (num == beginList_flag->num)
				{
					printf("������������ \n");
					beginList_flag->name = GetString();
					printf("������绰�� \n");
					beginList_flag->phone = GetString();
					printf("�޸ĳɹ���\n");
				}
				beginList_flag = beginList_flag->pNext;
			}

			printf("��y�������޸ģ�����������\n");
			if (GetKey() != 'y')
			{
				return;
			}
		}
	}
}

void DeletePhoneBook(Node** beginList, Node** endList)
{
	int num = 0;
	Node *beginList_flag = NULL;
	QueryPhoneBook(*beginList);

	if (g_key == 'b')
	{
		return;
	}

	if (g_key == 'd')
	{
		while(1)
		{
			printf("������Ҫɾ���ı�ţ� \n");
			num = atoi(GetString());
			printf("ȷ��ɾ�����%d? ȷ���밴y �������������� \n",num);
			if (GetKey() == 'y')
			{
				DelNode(num,beginList,endList);
				printf("ɾ���ɹ���\n");
			}
			else
			{
				continue;
			}

			printf("��y������ɾ��������������\n");
			if (GetKey() != 'y')
			{
				return;
			}
		}
	}
}
