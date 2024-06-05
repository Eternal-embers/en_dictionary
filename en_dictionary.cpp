#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define dict_addr "data\\dictionary.txt"
#define dict_sort "data\\dictionary_sort.txt"
#define dict_backup "data\\dict_backup.txt"

struct word{
	char Eng[15];
	char meaning[20];
	struct word *next;
}dict;

void menu(void){
	printf("\n\n");
	printf("\t\t______________________________________________\n");
	printf("\t\t|                                             |\n");
	printf("\t\t|    ______________________________________   |\n");
	printf("\t\t|    |>>>>>>>>>>Ӣ��ʵ��Ű�ϵͳ<<<<<<<<<<|   |\n");
	printf("\t\t|                                             |\n");
	printf("\t\t|        �˵�:                                |\n");
	printf("\t\t|        ¼��- - - - - - - - - -N             |\n");
	printf("\t\t|                                             |\n");
	printf("\t\t|        ɾ��- - - - - - - - - -D             |\n");
	printf("\t\t|                                             |\n");
	printf("\t\t|        ���- - - - - - - - - -B             |\n");
	printf("\t\t|                                             |\n");
	printf("\t\t|        ����- - - - - - - - - -S             |\n");
	printf("\t\t|                                             |\n");
	printf("\t\t|        A-Z - - - - - - - - - -P             |\n");
	printf("\t\t|                                             |\n");
	printf("\t\t|        ����- - - - - - - - - -R             |\n");
	printf("\t\t|                                             |\n");
	printf("\t\t|        ��ϰ- - - - - - - - - -V             |\n");
	printf("\t\t|                                             |\n");
	printf("\t\t|        ����- - - - - - - - - -T             |\n");
	printf("\t\t|                                             |\n");
	printf("\t\t|        �˳�- - - - - - - - - -Q             |\n");
	printf("\t\t|_____________________________________________|\n");
	printf("\t\t >>");
}

int input(){
 	int n;
	FILE *fp;
	if((fp = fopen(dict_addr,"a"))==NULL){
		printf("\t\t----��dictionary.txtʧ��!----\n");
		return 0;
	}
 	printf("\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	while(1){
		printf("\t\t���ʣ�");
		scanf("%s",dict.Eng);
		if(dict.Eng[0]=='#') break;
		printf("\t\t���壺");
		scanf("%s",dict.meaning);
		fprintf(fp,"%15s%20s\n",dict.Eng,dict.meaning);
  		printf("\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	}
	while(getchar()!='\n')
		continue;
	fclose(fp);
	return 1;
}

void del(void){
	FILE *fp;
	int n = 0,i;
	struct word *p1,*p2,*head,*pre,*temp;
	char s1[15],s2[15];
	if((fp = fopen(dict_addr,"r"))==NULL){
	printf("\t\t----��dictionary.txtʧ��!----\n");
	return;
	}
	p1 = (struct word *)malloc(sizeof(struct word));
	fscanf(fp,"%20s%15s",p1->Eng,p1->meaning);
	while(!feof(fp)){
		n++;
		if(n==1) head = p1;
		else p2->next = p1;
		p2 = p1;
		p1 = (struct word *)malloc(sizeof(struct word));
		fscanf(fp,"%15s%20s\n",p1->Eng,p1->meaning);
	}
	p2->next = NULL;
	fclose(fp);
	p1 = head;//������ͷ��������м��
 	printf("\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	while(p1->next!=NULL){
		pre = p1;
		p2 = p1->next;
		while(p2!=NULL){
			if(strcmp(p1->Eng,p2->Eng)==0)//��������ظ��ĵ���
			{
				printf("\t\tɾ�� \"%s  %s\" �ɹ�\n",p2->Eng,p2->meaning);
				temp = p2;
				pre->next = p2->next;//ɾ�����
				p2 = p2->next;
				free(temp);//�ͷſռ�
				temp = NULL;
				continue;
			}
			p2 = p2->next;
			pre = pre->next;
		}
		p1 = p1->next;
	}
	//����������������д��
	if((fp = fopen(dict_addr,"w"))==NULL){
	printf("\t\t----��dictionary.txtʧ��!----\n");
	return;
	}
	p1 = head;
	printf("\t\tд�룺\n");
	while(p1!=NULL){
		printf("\t\t>>>%15s%20s\n",p1->Eng,p1->meaning);
		fprintf(fp,"%15s%20s\n",p1->Eng,p1->meaning);
		p1 = p1->next;
	}
	fclose(fp);
	printf("\t\t--------ɾ���ظ����ʳɹ���--------\n\t\t");
	while(head){
		p1 = head;
		head = head->next;
		free(head);
	}
	system("pause>nul");//����
}

void scan(void){
	FILE *fp;
	int count = 0;
	if((fp = fopen(dict_addr,"r"))==NULL){
	printf("\t\t--------��dictionary.txtʧ��!--------\n");
	return;
	}
	printf("\n\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	printf("\t\t���    ����                ����\n");
	while(1){
		fscanf(fp,"%15s%20s",dict.Eng,dict.meaning);
		if(feof(fp)) break;
		printf("\t\t%-8d%-20s%-s\n\n",count,dict.Eng,dict.meaning);
		count++;
	}
	fclose(fp);
	printf("\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	printf("\t\t�ܹ��洢%d��������Ϣ",count);
	system("pause>nul");
}

void sort(){
	FILE *fp;
	int n = 0;
	struct word *p1,*p2,*head,*pt,*pre,*_pre,*after;
	//_preָ��p1ǰһ����㣬preָ��ptǰһ�����
	//afterָ��p1�ĺ�һ�����
	if((fp = fopen(dict_addr,"r"))==NULL){
	printf("\t\t----��dictionary.txtʧ��!----\n");
	return;
	}
	p1 = (struct word *)malloc(sizeof(struct word));
	fscanf(fp,"%15s%20s",p1->Eng,p1->meaning);
	while(!feof(fp)){
		n++;
		if(n==1) head = p1;
		else p2->next = p1;
		p2 = p1;
		p1 = (struct word *)malloc(sizeof(struct word));
		fscanf(fp,"%15s%20s",p1->Eng,p1->meaning);
	}
	p2->next = NULL;
	fclose(fp);
	//����һ���µ�ͷ���
	pre = (struct word *)malloc(sizeof(struct word));
	strcpy(pre->Eng,"aaa");
	strcpy(pre->meaning,"ͷ");
	pre->next = head;
	head = pre;
	printf("\t\t    - - - - - - - -��A-Z��������- - - - - - - -\n");//����
	//ѡ������
	_pre = head;
	p1 = head->next;//��ͷ�����һ����ʼ
	while(p1->next != NULL){
		p2 = p1->next;
		pt = p1;
		//�������ҳ����ʵ��ֵ�����С���Ǹ����
		while(p2!=NULL){
			if(strcmp(pt->Eng,p2->Eng)>0) pt = p2;//��������ֵ���С��pt->Eng,����ַ����pt
			p2 = p2->next;
		}
		//�ҵ�����Ϊ��С�ֵ���Ľ���ǰһ�����
		if(strcmp(pt->Eng,p1->next->Eng)==0)//��������ֵ�����С�Ľ����p1��һ�����
		{
			strcpy(dict.Eng,pt->Eng);
			strcpy(dict.meaning,pt->meaning);
			strcpy(pt->Eng,p1->Eng);
			strcpy(pt->meaning,p1->meaning);
			strcpy(p1->Eng,dict.Eng);
			strcpy(p1->meaning,dict.meaning);
			_pre = _pre->next;
			p1 = pt;
			continue;
		}
		else if(strcmp(pt->Eng,p1->Eng)!=0){
			p2 = p1;
			//�ҳ�pt��ǰһ�����
			while(p2!=NULL){
				if(strcmp(p2->next->Eng,pt->Eng)==0){
					pre = p2;
					break;
				}
			p2 = p2->next;
			}
			//�������λ��
			if(p1->next==NULL) after = NULL;
				else after = &(*(*p1).next);
			//��p1�ƶ���pt��λ��
			p1->next = pt->next;
			pre->next = p1;
			//��pt�ƶ���p1��λ��
			pt->next = &(*after);
			_pre->next = pt;
		}
		_pre = _pre->next;//��¼p1ǰһ�����
		p1 = pt->next;
	}
 	printf("\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	//������õ����ݴ洢���ļ���
	if((fp = fopen(dict_sort,"w"))==NULL){
	printf("----��dictionary_sort.txtʧ��!----\n");
	return;
	}
	p1 = head->next;
	printf("\t\t>>>д��\n");
	while(p1!=NULL){
		printf("\t\t>>>%15s %20s\n",p1->Eng,p1->meaning);//����
		fprintf(fp,"%15s%20s\n",p1->Eng,p1->meaning);
		p1 = p1->next;
	}
	fclose(fp);
	printf("\t\t-------��A-Z�洢�ֵ�ɹ�!-------\n\t\t");
	system("pause>nul");
}

void print_sort(void){
	FILE *fp;
	if((fp = fopen(dict_sort,"r"))==NULL){
	printf("\t\t----��dictionary_sort.txtʧ��!----\n");
	return;
	}
	printf("\t\t����                ����\n");
	while(1){
		fscanf(fp,"%15s%20s",dict.Eng,dict.meaning);
		if(feof(fp)) break;
		printf("\t\t%15s%20s\n\n",dict.Eng,dict.meaning);
	}
	fclose(fp);
	printf("\t\t   --------��ӡ�ɹ�!--------\n");
	system("pause>nul");
}

void reserve(void){
	FILE *fp,*f;
	int option;
	printf("\n\t\t��ѡ�񱸷��ļ���Դ(ԭʼ����0/������1)��\n");
	printf("\t\t���ѡ���������Ĭ�ϱ��������ļ���\n\t\t>>");
	scanf("%d",&option);
	while(getchar()!='\n');
	if(option==0){
		if((f = fopen(dict_addr,"r"))==NULL){
			printf("\t\t----��dictionary_sort.txtʧ��!----\n");
			return;
		}
	}
	else {
		if((f = fopen(dict_sort,"r"))==NULL){
			printf("\t\t----��dictionary_sort.txtʧ��!----\n");
			return;
		}
	}
	if((fp = fopen(dict_backup,"w"))==NULL){
	printf("\t\t----��back_up.txtʧ��!----\n");
	return;
	}
	printf("\t\t>>>д��:\n");
	while(!feof(f)){
		fscanf(f,"%15s%20s",dict.Eng,dict.meaning);
		printf("\t\t>>>%15s %15s\n",dict.Eng,dict.meaning);
		fprintf(fp,"%15s%20s\n",dict.Eng,dict.meaning);
	}
	fclose(fp);
	fclose(f);
	printf("\t\t   --------���ݳɹ�--------\n\t\t");
}

void review(void){
	FILE *fp;
	char option[6];
	int i,count,add,index;
	system("cls");
	if((fp = fopen(dict_addr,"r"))==NULL){
	printf("\t\t-------��dictionary.txtʧ��!-------\n");
	return;
	}
	printf("\n\n\n\t\t��ת��(�������ʱ��Ӧ��������ߵ����)��");
	scanf("%d",&index);
	i = 0;
	while(i <= index){
		fscanf(fp,"%15s%20s",dict.Eng,dict.meaning);
		i++;
	}
	printf("\t\t>>>��ʱ��ת��%s\n",dict.Eng);
	printf("\t\t��ѡ����Ҫ��ϰ�ĵ��ʸ�����\n\t\t>>");
	scanf("%d",&count);
	printf("\n\n\n\t\t>>>�Ѹ�ϰ��0\n");
	printf("\t\t���ʣ�%s\n\t\t",dict.Eng);
	system("pause>nul");
	printf("����:%s",dict.meaning);
	system("pause>nul");
	system("cls");
	for(i = 1;i<count;i++){
		printf("\n\n\n\t\t>>>�Ѹ�ϰ��%d\n",i);
		fscanf(fp,"%15s%20s",dict.Eng,dict.meaning);
		if(feof(fp)) rewind(fp);//�����ȡ����β�Զ��ص��ļ���ͷ
		printf("\t\t���ʣ�%s\n\t\t",dict.Eng);
		system("pause>nul");
		printf("����:%s",dict.meaning);
		system("pause>nul");
		system("cls");
	}
	printf("\n\n\t\t���Ѿ���ϰ��%d������\n",count);
	while(1){
		printf("\n\n\t\t���Ƿ�Ҫ������ϰ�������ĵ����أ�(Y/N)\n\t\t�����Ҫ���¸�ϰǰ��ĵ��ʣ������˵\"�õ�\"\n\t\t>>");
		scanf("%s",option);
		while(getchar()!='\n')
			continue;
		if(option[0]=='Y') {
			printf("\n\n\t\t��ѡ����Ҫ��ϰ�ĵ��ʸ�����\n\t\t>>");
			scanf("%d",&add);
			for(i = 0;i<add;i++){
				printf("\n\n\n\t\t>>>�Ѹ�ϰ��%d\n",i);
				fscanf(fp,"%15s%20s",dict.Eng,dict.meaning);
				if(feof(fp)) rewind(fp);//�����ȡ����β�Զ��ص��ļ���ͷ
				printf("\t\t���ʣ�%s\n\t\t",dict.Eng);
				system("pause>nul");
				printf("����:%s",dict.meaning);
				system("pause>nul");
				system("cls");
			}
			count+=add;
			printf("\n\n\t\t����ϰ��%d��������\n",count);
		}
		else if(strcmp(option,"�õ�")==0){
			rewind(fp);
			printf("\n\n\n\t\t��ѡ����Ҫ��ϰ�ĵ��ʸ�����\n\t\t>>");
			scanf("%d",&count);
			for(i = 0;i<count;i++){
				printf("\n\n\t\t>>>�Ѹ�ϰ��%d\n",i);
				fscanf(fp,"%15s%20s",dict.Eng,dict.meaning);
				if(feof(fp)) rewind(fp);//�����ȡ����β�Զ��ص��ļ���ͷ
				printf("\t\t���ʣ�%s\n\t\t",dict.Eng);
				system("pause>nul");
				printf("����:%s",dict.meaning);
				system("pause>nul");
				system("cls");
			}
			printf("\n\n\n\t\t���Ѿ���ϰ��%d������\n",count);
		}
		else {
			printf("\n\n\t\t��л����ʹ�ã�\n\t\t");
			return;
		}
	}
	fclose(fp);
}

void typing(void){
	FILE *fp;
	char option[3],prac[20],_prac[20];
	int i,num;
	float t = 0.0;
	system("cls");
	if((fp = fopen(dict_addr,"r"))==NULL){
	printf("\t\t-------��dictionary.txtʧ��!-------\n");
	return;
	}
	printf("\n\n\n");
	printf("\t\t�ף���ӭ��ʹ�ô���ϵͳ����ѡ��ģʽ(Ӣ��/����/��Ӣ):\n\n");
	printf("\t\tӢ��- - - - - - - - - - - - - -En\n\n");
	printf("\t\t����- - - - - - - - - - - - - -Ch\n\n");
	printf("\t\t��Ӣ- - - - - - - - - - - - - -EC\n\n\t\t>>");
	scanf("%s",option);
	while(getchar()!='\n')
		continue;
	if(strcmp(option,"En")==0){
		printf("\t\t�ף�����������Ҫ��ϰ�ĵ�����:\n\t\t>>");
		scanf("%d",&num);
		for(i = 0;i<num;i++){
			fscanf(fp,"%15s%20s",dict.Eng,dict.meaning);
			if(feof(fp)) rewind(fp);//�����ȡ����β�Զ��ص��ļ���ͷ
			printf("\t\t%-15s\t",dict.Eng);
			scanf("%s",prac);
			while(getchar()!='\n');
			printf("\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
			if(strcmp(prac,dict.Eng)==0) t++;
		}
		printf("\t\t�ף�������ȷ����%.2f%%,��ȷƴд%.0f��������ƴд%d��\n",(100*t)/num,t,num-t);
	}
	else if(strcmp(option,"Ch")==0){
		printf("\t\t�ף�����������Ҫ��ϰ�ĵ�����:\n\t\t>>");
		scanf("%d",&num);
		for(i = 0;i<num;i++){
			fscanf(fp,"%15s%20s",dict.Eng,dict.meaning);
			if(feof(fp)) rewind(fp);//�����ȡ����β�Զ��ص��ļ���ͷ
			printf("\t\t%-20s\t",dict.meaning);
			scanf("%s",prac);
			while(getchar()!='\n');
			printf("\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
			if(strcmp(prac,dict.meaning)==0) t++;
		}
		printf("\t\t�ף�������ȷ����%.2f%%,��ȷƴд%.0f��������ƴд%d��\n",(100*t)/num,t,num-t);
	}
	else{
		printf("\t\t�ף�����������Ҫ��ϰ�ĵ�����:\n\t\t>>");
		scanf("%d",&num);
		for(i = 0;i<num;i++){
			fscanf(fp,"%15s%20s",dict.Eng,dict.meaning);
			if(feof(fp)) rewind(fp);//�����ȡ����β�Զ��ص��ļ���ͷ
			printf("\t\t%-15s %-20s\n\t\t",dict.Eng,dict.meaning);
			scanf("%s%s",prac,_prac);
			while(getchar()!='\n');
			printf("\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
			if(strcmp(prac,dict.Eng)==0 && strcmp(_prac,dict.meaning)==0) t++;
		}
		printf("\t\t�ף�������ȷ����%.2f%%,��ȷƴд%.0f��������ƴд%d��\n",(100*t/num),t,num-t);
	}
	printf("\t\t��,������ϰ��������ӭ���ٴι���\n\t\t");
	system("pause>nul");
	fclose(fp);
}

int main(){
 	char option;
	while(1){
		menu();
		scanf("%c",&option);
		getchar();
		if(option >= 'a' && option <= 'z') option -= 32;
		switch(option){
		case 'N':
		if(input()==1)printf("\t\t--------¼��ɹ�!--------\n\t\t");
			else printf("\t\t--------¼��ʧ��!--------\n\t\t");
		break;
		case 'D':del();break;
		case 'B':scan();break;
		case 'S':sort();break;
		case 'P':print_sort();break;
		case 'R':reserve();break;
		case 'V':review();break;
		case 'T':typing();break;
		case 'Q':printf("\n\t\t---------��л����ʹ��!---------\n");return 0;
		default:
		printf("\t\t----ѡ�������������������!----\n\t\t");
		while(getchar()!='\n')
			continue;
		}
	}
}
