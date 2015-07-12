#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<termios.h>
#include <string.h>
#include <unistd.h>

#define maxX 25
#define maxY 12
#define N 100;
#define MOVEUP(x) printf("\033[%dA", (x))    //上移动光标
#define MOVEDOWN(x) printf("\033[%dB", (x)) //下移动光标
#define MOVELEFT(y) printf("\033[%dD", (y))  //左移动光标
#define MOVERIGHT(y) printf("\033[%dC",(y))  //右移动光标
#define MOVETO(x,y) printf("\033[%d;%dH", (x), (y))    //光标定位


struct student{
	char number[10];
	char name[20];
	int grade[3];
	double avergrade;
	char password[20];
	char classnum[10];
	struct student *next;
};

int getch(void) 
{ 
        struct termios tm, tm_old; 
        int fd = STDIN_FILENO, c; 
        if(tcgetattr(fd, &tm) < 0) 
                return -1; 
        tm_old = tm; 
        cfmakeraw(&tm); 
        if(tcsetattr(fd, TCSANOW, &tm) < 0) 
                return -1; 
        c = fgetc(stdin); 
        if(tcsetattr(fd, TCSANOW, &tm_old) < 0) 
                return -1; 
        return c; 
} 


int iCount=0;
int count;

struct student *Create()
{
	struct student *pHead;
	struct student *pNew,*pEnd;
    FILE *fp;
	fp=fopen("student.txt","rt");
	if(fp == NULL)
	{
		printf("cann't open!\n");
		getch();
		exit(1);
	}
	pHead=(struct student*)malloc(sizeof(struct student));
	pNew=(struct student*)malloc(sizeof(struct student));
	if(fread(pNew,sizeof(struct student),1,fp)==0)
	{
		pHead->next=NULL;
		return pHead;
	}
	pHead->next=pNew;
	pEnd=pNew;
	pNew->next=NULL;
	while(1){
		iCount++;
		pNew=(struct student*)malloc(sizeof(struct student));
		if(fread(pNew,sizeof(struct student),1,fp) == 0)
			break;
		pNew->next=NULL;
	    pEnd->next=pNew;
	    pEnd=pNew;
	}
	fclose(fp);
	return pHead;
}

struct student *create(struct student *p)
{
	struct student *pHead;
	struct student *pNew,*pEnd;
        struct student *p1,*p2;
	int i, a, j, x=0,y=0;
	char m[10];
	count =1;
	printf("请输入班级人数：");
	scanf("%d",&a);
	printf("请输入班级:");
	scanf("%s",m);
	while(y==0)
        { x=0;
          pHead=(struct student*)malloc(sizeof(struct student));
	  pNew=(struct student*)malloc(sizeof(struct student));
	  printf("请输入要添加学生的学号，姓名，三门课的成绩：\n");
	  strcpy(pNew->classnum,m);
	  printf("学号： ");
	  scanf("%s",pNew->number);
          p1=p->next;
          while(p1 !=NULL ){
        	   if(strcmp(pNew->number,p1->number) == 0)
        	   {
             	       x=1;
             	       break;
        	   }
        	   p1=p1->next;
       		}
          if(x == 1)
       		{
          	  j--;
          	  printf("学号重复！");
       		}
          else{
        	printf("姓名： ");
		scanf("%s",pNew->name);
		printf("成绩：（语，数，英） ");
		scanf("%d%d%d",&pNew->grade[0],&pNew->grade[1],&pNew->grade[2]);
		pNew->avergrade=(pNew->grade[0]+pNew->grade[1]+pNew->grade[2])/3.0;
		for(i=0; i<6; i++)
		     pNew->password[i]='1';
		pNew->password[i]='\0';
		pNew->next=NULL;
		pHead->next=pNew;
		pEnd=pNew;
        	y=1;
          }
        }
	for(j=1; j<a; j++){
                x=0;
		count++;
		pNew=(struct student*)malloc(sizeof(struct student));
		printf("请输入要添加学生的学号，姓名，三门课的成绩：\n");
		strcpy(pNew->classnum,m);
		printf("学号： ");
		scanf("%s",pNew->number);
                p1=p->next;
                while(p1 !=NULL ){
        	   if(strcmp(pNew->number,p1->number) == 0)
        	   {
             	       x=1;
             	       break;
        	   }
        	   p1=p1->next;
       		}
                p2=pHead->next;
                while(p2 !=NULL ){
        	   if(strcmp(pNew->number,p2->number) == 0)
        	   {
             	       x=1;
             	       break;
        	   }
        	   p2=p2->next;
       		}
       		if(x == 1)
       		{
          	  j--;
          	  printf("学号重复！");
       		}
		else{
                printf("姓名： ");
		scanf("%s",pNew->name);
		printf("成绩：（语，数，英） ");
		scanf("%d%d%d",&pNew->grade[0],&pNew->grade[1],&pNew->grade[2]);
		pNew->avergrade=(pNew->grade[0]+pNew->grade[1]+pNew->grade[2])/3.0;
		for(i=0; i<6; i++)
		     pNew->password[i]='1';
		pNew->password[i]='\0';
		pNew->next=NULL;
		pEnd->next=pNew;
		pEnd=pNew;
                }
	}
	pEnd->next=NULL;
	return pHead;
}

void Print(struct student *pHead)
{
	struct student *pTemp;
	int iTndex=1;
	pTemp=pHead->next;
	while(pTemp!=NULL)
	{
		printf("排名:%d\n",iTndex);
		printf("班级:%s\n",pTemp->classnum);
		printf("学号：%s\n",pTemp->number);
		printf("姓名：%s\n",pTemp->name);
		printf("三门成绩：%d（语文）,%d（数学）,%d（英语）\n",pTemp->grade[0],pTemp->grade[1],pTemp->grade[2]);
		printf("平均成绩：%.2f\n",pTemp->avergrade);
		printf("密码：%s\n",pTemp->password);
		pTemp=pTemp->next;
		iTndex++;
	}
}





/*void Add(struct student *pHead)
{
	struct student *pNew;
	int i;
	pNew=(struct student*)malloc(sizeof(struct student));
	printf("请输入要添加学生的学号，姓名，三门课的成绩：\n");
	printf("班级：");
	scanf("%s",pNew->classnum);
	printf("学号： ");
	scanf("%s",pNew->number);
	printf("姓名： ");
	scanf("%s",pNew->name);
	printf("成绩：（语，数，英） ");
	scanf("%d%d%d",&pNew->grade[0],&pNew->grade[1],&pNew->grade[2]);
	pNew->avergrade=(pNew->grade[0]+pNew->grade[1]+pNew->grade[2])/3.0;
	for(i=0; i<6; i++)
	     pNew->password[i]='1';
	pNew->password[i]='\0';
	pNew->next=pHead->next;
	pHead->next=pNew;
	iCount++;
}*/


void Found(struct student *pHead)
{
	struct student *p;
	char n[10];
	p=pHead->next;
	printf("请输入要查找信息的学号：");
	scanf("%s",n);
	  while(p!=NULL&&strcmp(p->number,n)){
	      p=p->next;
      }
      if(p!=NULL){
		  printf("班级:%s\n",p->classnum);
	      printf("学号：%s\n",p->number);
	      printf("姓名：%s\n",p->name);
	       printf("三门成绩：%d（语文）,%d（数学）,%d（英语）\n",p->grade[0],p->grade[1],p->grade[2]);
	      printf("平均成绩：%.2f\n",p->avergrade);
		  printf("密码：%s",p->password);
      }
      else
         printf("无此学号信息："); 
}


void Rank(struct student *pHead)
{
	struct student *p1,*p2,*p,*p3;
	int i;
	for(i=0;i<iCount;i++){
	  p=pHead;
	  p1=pHead->next;
	  p2=p1->next;
      while(p1->next!=NULL){
		  if((p2->avergrade)>(p1->avergrade)){
		  	p->next=p2;
		  	p1->next=p2->next;
		  	p2->next=p1;
		  	p3=p2;
			p2=p1;
		  	p1=p3;
		 }
		  p=p->next;
		  p1=p1->next;
		  p2=p2->next;
	  }
    }
}

/*void gotoxy(HANDLE hOut, int x, int y)
{
      COORD pos;
      pos.X = x;             //横坐标
      pos.Y = y;            //纵坐标
      SetConsoleCursorPosition(hOut, pos);
}*/

void Make()
{

    printf("\n");
    printf("\n");
    printf("\n");
	    printf("\n");
	    printf("***********************************************\n");
	    printf("    1.插入数据（班级）  2.删除数据             \n");
	    printf("\n");
	    printf("    3.查找数据          4.显示数据             \n");
	    printf("\n");
	    printf("    5.输出不及格信息    6.修改密码(教师密码)    \n"); 
	    printf("\n");
	    printf("    0.退出              7.修改成绩            \n");
	    printf("**********************************************\n");
}

void Change()
{
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("******************************************\n");
	printf("    1.教务处登录  \n");
        printf("\n");	
        printf("    2.学生登陆  \n");
	printf("\n");
	printf("    3.管理员登陆  \n");
	printf("\n");
	printf("    0.退出\n");
	printf("******************************************\n");
}

void Monitor()
{
	printf("\n\n\n\n");
        printf("******************************************\n");
	printf("    1.显示数据  \n\n");
	printf("    2.修改密码  \n\n");
	printf("    3.显示不及格 \n\n");
	printf("    0.退出  \n");
	printf("******************************************\n");
}

void Students()
{
	printf("\n\n\n\n");
        printf("******************************************\n");
	printf("    1.查找信息  \n\n");
	printf("    2.修改密码  \n\n");
	printf("    0.退出  \n");
	printf("******************************************\n");
}

int Password(char *a)
{
	 char b[20]="0",ch;
        int i=0,j;
	printf("请输入密码:");
	fflush(stdin);
	while(1)
	{
	   ch=getch();

	   if(ch == 127)
	   {
		if(i != 0){
		fflush(stdin);
		b[i-1]='\0';
	        i--;
	        }
	   }
	   else if(ch==13)
		   break;
	   else if(ch > 32 && ch < 127)
	   {
	     if(i<20){
             b[i]=ch;
	     fflush(stdin);
	     i++;
 	     }
	   }
       printf("\r请输入密码:");
	   for(j=0; j<i; j++)
		   printf("*");
	   for(j=0; j<20-i; j++)
		   printf(" ");
	}
	if(strcmp(b,a)==0)
		return 1;
	return 0;
}

struct student *Found_student(struct student *pHead)
{
	struct student *p;
	char n[10];
	int i=1;
	p=pHead->next;
	printf("请输入的学号：");
    scanf("%s",n);
	  while(p!=NULL&&strcmp(p->number,n)){
	      p=p->next;
		  i++;
      }
      if(p!=NULL){
		  if(Password(p->password)){
			  /*printf("\n排名:%d",i);
			  printf("\n班级:%s\n",p->classnum);
			  printf("\n学号：%s\n",p->number);
	          printf("姓名：%s\n",p->name);
	          printf("三门成绩：%d（语文）,%d（数学）,%d（英语）\n",p->grade[0],p->grade[1],p->grade[2]);
	          printf("平均成绩：%.2f\n",p->avergrade);*/
			  return p;
		  }
          else
			  printf("\n密码错误！");
      }
      else
         printf("无此学号信息：");
	  return NULL;
}

void Exchange_student(struct student *pHead,struct student *p)
{
	int i=0,j;
	char b[20],ch;
			  printf("\n请输入新密码：");
			  fflush(stdin);
			  while(1)
			  {
	             ch=getch();
		         if(ch==8)
				 {
			        if(i != 0){
		            fflush(stdin);
		            b[i-1]='0';
	                i--;
					}
				 }
	              else if(ch==13)
				 {
		             b[i]='\0';
					 break;
				 }
	             else
				 {
	                b[i]=ch;
	                fflush(stdin);
	                i++;
				 }
                 printf("\r请输入新密码:");
	             for(j=0; j<i; j++)
		             printf("*");
	             for(j=0; j<20; j++)
		             printf(" ");
			  }
			  strcpy(p->password,b); 
}

void Exchange_teacher(struct student *pHead2)
{
    struct student *p;
	int i=0,j;
	char b[20],ch;
	char n[10];
	p=pHead2->next;
	printf("请输入学号：");
    scanf("%s",n);
	  while(p!=NULL&&strcmp(p->number,n)){
	      p=p->next;
      }
      if(p!=NULL){
			  printf("请输入新密码：");
			  fflush(stdin);
			  while(1)
			  {
	             ch=getch();
		         if(ch==127)
				 {
			        if(i != 0){
		              fflush(stdin);
		              b[i-1]='\0';
	                  i--;
					}
				 }
	             else if(ch==13)
				 {
		             b[i]='\0';
					 break;
				 }
	             else
				 {
	                b[i]=ch;
	                fflush(stdin);
	                i++;
				 }
                 printf("\r请输入新密码:");
	             for(j=0; j<i; j++)
		             printf("*");
	             for(j=0; j<20; j++)
		             printf(" ");
			  }
			  strcpy(p->password,b);
      }
      else
         printf("无此学号信息："); 
}

void Fail(struct student *pHead)
{
	struct student *p;
	p=pHead->next;
	printf("数学不及格：\n");
	while(p != NULL)
	{
		
		if(p->grade[0] < 60)
		{
			printf("学号:%s\n",p->number);
		}
		p=p->next;
	}
	p=pHead->next;
	printf("语文不及格：\n");
	while(p != NULL)
	{
		
		if(p->grade[1] < 60)
		{
			printf("学号:%s\n",p->number);
		}
		p=p->next;
	}
	p=pHead->next;
	printf("英语不及格：\n");
	while(p != NULL)
	{
		
		if(p->grade[2] < 60)
		{
			printf("学号:%s\n",p->number);
		}
		p=p->next;
	}
}

void Write(struct student *pHead)
{
	struct student *p;
	FILE *fp;
	fp=fopen("student.txt","wt");
	if(fp == NULL)
	{
		printf("cann't open!\n");
		getch();
		exit(1);
	}
	p=pHead->next;
	while(p!=NULL)
	{
		fwrite(p,sizeof(struct student),1,fp);
		p=p->next;
	}
	fclose(fp);
}

void ExNum(struct student *pHead)
{
	struct student *p;
	char n[10];
	int i=1;
	p=pHead->next;
	printf("请输入要查找信息的学号：");
    scanf("%s",n);
	  while(p!=NULL&&strcmp(p->number,n)){
	      p=p->next;
		  i++;
      }
      if(p!=NULL){
			  printf("输入新成绩：（语，数，英）");
			  scanf("%d%d%d",&p->grade[0],&p->grade[1],&p->grade[2]);
	          p->avergrade=(p->grade[0]+p->grade[1]+p->grade[2])/3.0;
      }
      else
         printf("无此学号信息："); 
}

int Read(char *a)
{
	FILE *fp;
	char b[20]="0";
	fp=fopen("pass.txt","rt");
	if(fp == NULL)
	{
		printf("cann't open!\n");
		getch();
		exit(1);
	}
	if(fscanf(fp, "%s", b)== 0)
	{	
           return 1;
	}
        strcpy(a,b);
	fclose(fp);
	return 0;
}

void Exchange_pass(char *a)
{
	char b[20];
	int i = 0, j;
	char ch;
	if(Password(a)){
		printf("\n请输入新密码：");
	    fflush(stdin);
		while(1){
	         ch=getch();
		     if(ch==127)
			 {
			     if(i != 0){
		         fflush(stdin);
		         b[i-1]='0';
	             i--;
				}
			}
	        else if(ch==13)
			{
		         b[i]='\0';
			     break;
			}
	        else
			{
	             b[i]=ch;
	             fflush(stdin);
	             i++;
			}
            printf("\r请输入新密码:");
	        for(j=0; j<i; j++)
		          printf("*");
	        for(j=0; j<20; j++)
		          printf(" ");
		}
			strcpy(a,b);
	}
    else
		printf("\n密码错误！");
}

void WrT(char *a)
{
	FILE *fp;
	fp=fopen("pass.txt","wt");
	if(fp == NULL)
	{
		printf("cann't open!\n");
		getch();
		exit(1);
	}
	fputs(a,fp);
	fclose(fp);
}

void write_class(struct student *pHead)
{
	struct student *p;
	FILE *fp;
	char a[20];
	p=pHead->next;
    strcpy(a,p->classnum);
	strcat(a,".txt");
	fp=fopen(a,"wt");
	if(fp == NULL)
	{
		printf("cann't open!\n");
		getch();
		exit(1);
	}
	p=pHead->next;
	while(p!=NULL)
	{
		fwrite(p,sizeof(struct student),1,fp);
		p=p->next;
	}
	fclose(fp);
}

void Join(struct student *pHead,struct student *pHead2)
{
	struct student *p;
	p=pHead2->next;
	while(p->next != NULL)
	{
		p=p->next;
	}
	p->next = pHead ->next;
	pHead->next = pHead2->next;
	iCount = iCount + count;
}

struct student *change_class(char *b,char *a)
{
	struct student *pHead2;
	struct student *pNew,*pEnd;
	char c[20]="0",d[20]="0";
	FILE *fp;
	
        strcpy(c,a);
	strcat(a,".txt");
	fp=fopen(a,"rt");
	if(fp == NULL)
	{
		printf("不存在该班级！\n");
		getch();
		return NULL;
	}
	pHead2=(struct student*)malloc(sizeof(struct student));
	pNew=(struct student*)malloc(sizeof(struct student));
	if(fread(pNew,sizeof(struct student),1,fp)==0)
	{
		pHead2->next=NULL;
		return pHead2;
	}
	pHead2->next=pNew;
	pEnd=pNew;
	pNew->next=NULL;
	while(1){
		iCount++;
		pNew=(struct student*)malloc(sizeof(struct student));
		if(fread(pNew,sizeof(struct student),1,fp) == 0)
			break;
		pNew->next=NULL;
	    pEnd->next=pNew;
	    pEnd=pNew;
	}
	fclose(fp);
        strcpy(a,c);
        strcat(c,"pass.txt");
        fp=fopen(c,"rt");
	if(fp != NULL)
	{
		fscanf(fp,"%s",d);
                strcpy(b,d);
	}
	return pHead2;
}

void write_pass(char *b,char *a)
{
    FILE *fp;
    char c[10]="0";
    strcpy(c,a);
    strcat(c,"pass.txt");
    fp=fopen(c,"wt");
     fprintf(fp,"%s",b);
     fclose(fp);
}

void Delete(struct student *pHead)
{
	struct student *p,*pTemp,*p1,*pNew,*pEnd,*p3,*p2;
	char n[10];
        char a[10];
        FILE *fp;
	printf("请输入要删除信息的学号：");
	scanf("%s",n);
	p=pHead->next;
	pTemp=pHead;
        while(p!=NULL&&strcmp(p->number,n)){
	     p=p->next;
	     pTemp=pTemp->next;
        }
        if(p!=NULL){
           strcpy(a,p->classnum);
           strcat(a,".txt");
           fp=fopen(a,"rt");
           p1=(struct student*)malloc(sizeof(struct student));
	   pNew=(struct student*)malloc(sizeof(struct student));
	   if(fread(pNew,sizeof(struct student),1,fp)==0)
	   {
		p1->next=NULL;
	   }
	   p1->next=pNew;
	   pEnd=pNew;
	   pNew->next=NULL;
	   while(1){
		iCount++;
		pNew=(struct student*)malloc(sizeof(struct student));
		if(fread(pNew,sizeof(struct student),1,fp) == 0)
			break;
		pNew->next=NULL;
	    pEnd->next=pNew;
	    pEnd=pNew;
	   }
	   fclose(fp);
           p2=p1->next;
	   p3=p1;
           while(p2!=NULL&&strcmp(p2->number,n)){
	     p2=p2->next;
	     p3=p3->next;
           }
           p3->next=p2->next;
           p2->next=NULL;
           free(p2);
           write_class(p1);
           pTemp->next=p->next;
           p->next=NULL;
           free(p);
           iCount--;
        }
       else 
         printf("无此学号信息："); 
}

int main()
{
	//HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	char ch;
	char a[20]="xiyou_linux";
	char b[20]="1721267632";
        char CLASS[10];
	int x=5,y=6; 
	int c = 0;
	struct student *pHead;
	struct student *pHead2;
	struct student *p;
	pHead=Create();
	system("clear");
	Change();
//	gotoxy(hOut,x,y);
        MOVETO(y,x);
	while(1){
      while(1){
          ch=getch();
  	     if(ch==13){
  	   	     if(x==5&&y==6){
				 Read(a);
				 system("clear");
                 if(Password(a)==1){
				    x=5,y=6;
				   system("clear");
	               Make();
  	               //gotoxy(hOut,x,y);
                     MOVETO(y,x);
	               while(1){
                     while(1){
  	                   ch=getch();
  	                   if(ch==13){
  	   	                    if(x==5&&y==6){
  	   	                        system("clear");
					pHead2=create(pHead);
					Join(pHead,pHead2);
					write_class(pHead2);
                                          getch();
					break;
				    }
  	   	                    else if(x==25&&y==6){
  	   	                          system("clear");
					  Delete(pHead);
                                          getch();
  	   	                          break;
			            }
  	   	                    else if(x==5&&y==8){
  	   	                       system("clear");
				       Found(pHead);
                                       getch();
  	   	                       break;
				    }
  	   	                    else if(x==25&&y==8){
  	   	                        system("clear");
					Rank(pHead);
				        Print(pHead);
  	   	                        break;
							}
  	   	                    else if(x==5&&y==12)
							{
				                printf("\n\n\n");
							    Write(pHead);
			                    exit(0);
							}
							else if(x==25&&y==10)
							{
								system("clear");
								Exchange_pass(a);
								WrT(a);
								break;
							}
							else if(x==5&&y==10)
							{
								system("clear");
								Fail(pHead);
								break;
							}
							else if(x==25&&y==12)
							{
								system("clear");
								ExNum(pHead);
                                                                getch();
								break;
							}
					   }
  	                   else
		                 switch(ch){
  	  	                 case 'w':if(y>6&&y<=maxY){y=y-2;MOVETO(y,x);};break;
                                
  	 	                case 's':if(y>=6&&y<maxY){y=y+2;MOVETO(y,x);};break;
                                
  	 	                 case 'a':if(x>5&&x<=maxX){x=x-20;MOVETO(y,x);};break;
                                
  	 	                case 'd':if(x>=5&&x<maxX){x=x+20;MOVETO(y,x);};break;
                                
					   }
					 }
	                 printf("\n");
	                 printf("\n");
	                 printf("\n输入任意键继续.......");
	                 getch();
	                 system("clear");
	                 x=5,y=6;
                         Make();
                         // gotoxy(hOut,x,y);
                         MOVETO(y,x);
				   }
				 }
	             else{
		            printf("\n密码错误!!!!!!");
		            printf("\n输入任意键继续......");
			        getch();
		            system("clear");
			     }
		         x=5,y=6;
                 Change();
                 //gotoxy(hOut,x,y);
                 MOVETO(y,x);
			 }
  	   	     else if(x==5&&y==8){
				    x=5,y=6;
				   system("clear");
				   if((p=Found_student(pHead)) != NULL)
				   {
				     system("clear");
			         Students();
				     //gotoxy(hOut,x,y);
                     MOVETO(y,x);
                     while(1){
                       while(1){
  	                    ch=getch();
  	                    if(ch==13){
  	   	                  if(x==5&&y==6){
  	   	                    system("clear");
							Rank(pHead);
				            printf("班级:%s\n",p->classnum);
							printf("学号：%s\n",p->number);
							printf("姓名：%s\n",p->name);
							printf("三门成绩：%d（语文）,%d（数学）,%d（英语）\n",p->grade[0],p->grade[1],p->grade[2]);
							printf("平均成绩：%.2f\n",p->avergrade);
  	   	                    break;
							}
  	   	                  else if(x==5&&y==8){
  	   	                       system("clear");
					           Exchange_student(pHead,p);
  	   	                       break;
						  }
  	   	                  else if(x==5&&y==10)
							{
				               printf("\n\n\n");
							   Write(pHead);
			                   exit(0);
							}
					   }
  	                   else
		                 switch(ch){
  	  	                    case 'w':if(y>6&&y<=maxY){y=y-2;MOVETO(y,x);};break;
                                    
  	 	                    case 's':if(y>=6&&y<maxY){y=y+2;MOVETO(y,x);};break;
                                    
					   }
					 }
	                 printf("\n");
	                 printf("\n");
	                 printf("\n输入任意键继续.......");
	                 getch();
	                 system("clear");
	                 x=5,y=6;
                     Students();
                     //gotoxy(hOut,x,y);
                      MOVETO(y,x);
                    } 
				} 
	             else{
		            printf("\n密码错误!!!!!!");
		            printf("\n输入任意键继续......");
			        getch();
		            system("clear");
			     }
		         x=5,y=6;
                 Change();
                 //gotoxy(hOut,x,y);
                 MOVETO(y,x);
             }
			 else if(x==5&&y==10){
				  x=5,y=6;
			     system("clear");
                            printf("请选择班级（自行填写）:");
	                     gets(CLASS);
				 if((pHead2=change_class(b,CLASS)) != NULL){
				 if(Password(b) == 1){	
					system("clear");
					Monitor();
					//gotoxy(hOut,x,y);
                                       MOVETO(y,x);
					while(1){
						while(1){
  							ch=getch();
  							if(ch==13){
  	   						  if(x==5&&y==6){
  	   						      system("clear");
                                                                  Rank(pHead2);
								  Print(pHead2);
								  break;
							  }
							  else if(x==5&&y==8){
								system("clear");
								Exchange_pass(b);
                                                                write_pass(b,CLASS);
								break;
							  }
  	   						  else if(x==5&&y==10){
								system("clear");
  	   						    Fail(pHead);
								break;
							  }
  	   					      else if(x==5&&y==12)
							  {
							    printf("\n\n\n");
							    Write(pHead);
							    exit(0);
							  }
							}
  							else
								switch(ch){
  	  								case 'w':if(y>6&&y<=maxY){y=y-2;MOVETO(y,x);};break;
  	 								case 's':if(y>=6&&y<maxY){y=y+2;MOVETO(y,x);};break;
								}
						}
						printf("\n");
						printf("\n");
						printf("\n输入任意键继续.......");
						getch();
						system("clear");
						x=5,y=6;
						Monitor();
					//	gotoxy(hOut,x,y);
                                                MOVETO(y,x);
					}
				 }
				 else
					 printf("\n密码错误!!!!!!");
				     getch();
		             system("clear");
				 }
				 else{
		            printf("\n输入任意键继续......");
					getch();
		            system("clear");
				 }
                  x=5,y=6;
                 Change();
                // gotoxy(hOut,x,y);
                 MOVETO(y,x);
			 }
			 else if(x==5&&y==12){
				 	Write(pHead);
				    printf("\n\n\n");
  	   	            return 0;
			 }
		 }
  	      else
		     switch(ch){
  	  	         case 'w':if(y>6&&y<=maxY){y=y-2;MOVETO(y,x);};break;
                         
  	 	         case 's':if(y>=6&&y<maxY){y=y+2;MOVETO(y,x);};break;
                         
  	         }
	} 
	}
    Write(pHead);
	return 0;
}
