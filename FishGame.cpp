//�����С�㣬c���Դ�ʵ��
//ͼƬ�ز��������زľ��������� 
#include<stdio.h>
#include <stdlib.h>
#include<graphics.h> 
#include<time.h> 
#include <conio.h>
#include <windows.h>
//#define FishTypeNum 5
#define LevelNum 5
#define MaxHeight 600 
#define MaxWidth 900 
#define MaxFishNum 20 

typedef struct {
	int Pos[2];//λ�� x,y
	int xp;//���� 
	int dir;//���� 0�� 1�� 
	int Level;//�ȼ� 0,1,2,3,4
}MyFish;

typedef struct {
	int Pos[2];//λ��x,y 
	int isAlive;//�Ƿ���� 0������ 1���� 
	int dir;//���� 0�� 1��
	int step;//��¼�ζ����� 
	int Level;//������� 0,1,2,3,4
}Fish;
Fish fish[MaxFishNum];
MyFish myfish;
//int MaxFishNum = 20;  
int Size[LevelNum]={1,4,9,16,25};//ÿ������Ĵ�С
int Sizey[LevelNum]={1,2,3,4,5};
int Sizex[LevelNum]={1,2,3,4,5};//�����Ϊ1:1 
int Getxp[LevelNum]={1,2,3,4,5};//ÿ�������ܻ�õľ��� 
int xpNeed[LevelNum-1]={3,7,15,25};//��������ľ��� 
int Speed[LevelNum]={2,5,3,4,2};//�����ζ��ٶ� 
int sizexp[LevelNum] = {24,36,48,60,72};
void IniGame();//��ʼ��
int Click(char* c); //��鰴�� 
void Move(char c);// ���¿������λ�� 
void FishUpdate();//����������� 
void Show(int bksel);//��ʾ
int Check();// ��һ������Ƿ�����ʳ������ʧ�ܷ���0���ڶ�������Ƿ�������Ӵ���Ե��ʧ��Ĭ�Ϸ���1 
int max(int a,int b);

/*������*/ 
int main(){
	int x,y,scon=0,bgm=1,tb=0,bksel=0; 
	char op;
	srand((unsigned int)time(0));
	printf("��Ϸ���ܣ�\n");
	printf("\n1.��Ϸ�����Լ����Կ��Ƶ�С���㣬�������·��м䣬һ��ʼ�ȼ�Ϊ0��\n����Ҫ��w,a,s,d�ĸ���������С����ζ�����Ӧ���ϣ����£��ҡ�\n");
	printf("\n2.��Ϸ����ħ��BGM��������ϲ���ĵ�Ӱ�����˴���ǹ��������Ҫ��BGM��\n�ӳ��¼�ִ�һ��ʱ�����֪ʤ����\n");
	printf("\n3.������ܵĻ������ԳԵ������������Լ���������þ���ֵ����ߴ��\n���ʡ����鵽��һ���̶Ȼ��Զ���������ߵȼ�Ϊ4����\n");
	printf("\n4.��Ϸ�г����Լ����㣬������������ֱ�Ϊ���ǡ�С���㡢������\nͷ������㡣���ǵĵȼ��ֱ�Ϊ�����ǣ�0����<С���㣨1����<����2����\n<��ͷ�㣨3����<���㣨4������\n");
	printf("\n5.��Ϸ�ٶȻ����ʱ����죬Ŭ����\n");
	printf("\n6.�ý�����¼��Ĳ�����Ϸ״̬��\n");
	printf("\n7.ʤ���������涨ʱ���ڻ��350�ֻ��߼�ֲ���������Ե���\n");
	printf("\n8.ף������죡\n");
	printf("\n���������ֲ����¿ո�����Ƿ���BGM��1���ǣ���0���񣩣�\n");
	scanf("%d",&bgm); 
	printf("\n���������ֲ����¿ո��������ͼ��0����Ⱥ����1��ɺ������2��Ǳͧ����3����������\n");
	scanf("%d",&bksel); 
	printf("\n���������ֲ����¿ո������Ϸ�Ѷȣ�0���򵥣���1�����ѣ���2��ج�Σ���\n");
	scanf("%d",&tb); 
	IniGame();//��ʼ����Ϸ 
	switch(tb){
		case 0:
			printf("\n����֮ѡ\n");
			myfish.Level = 1;
			break;
		case 1:
			for(int i=0;i<LevelNum;i++)
				Speed[i]=Speed[i]+2;
			for(int j=0;j<LevelNum-1;j++)
				xpNeed[j]=xpNeed[j]*2-2;
				break;
		case 2:
			printf("\nף�����...\n");
			for(int i=0;i<LevelNum;i++)
				Speed[i]=Speed[i]*2;
			for(int j=0;j<LevelNum-1;j++)
				xpNeed[j]=xpNeed[j]*3-1;
				break;
		default:break;
		}
	printf("--------------------------------------------------------------------\n");
	MessageBox (NULL, TEXT ("��Ϸ������ʼ"), TEXT ("��ʾ"), MB_OK) ;//��ʼ���� 
	//printf("%d",map[30][40]);
	//TypeMap(map);
	initgraph(MaxWidth,MaxHeight);//����һ��ͼ�δ��� 
	Show(bksel);// ��ʾ 
	if(bgm){
		mciSendString("play bkmusic", NULL, 0, NULL);//��������
	}
	//printf("%d %d\n",myfish.Pos[0],myfish.Pos[1]);
	//MessageBox (NULL, TEXT ("Hello, bccn!"), TEXT ("HelloMsg"), MB_OK) ;
	while(1){
			scon++;
			if(scon>1500){
				Sleep(5);
			}
			else if(scon>1200){
				Sleep(10);
			}
			else if(scon>800){
				Sleep(20);
			}else if(scon>400){
				Sleep(50);
			}
			else if(scon>200){
					Sleep(100);}//if
			else 
					Sleep(200);
			//printf("%d\n",scon);
			if(scon==4000||myfish.xp>=350){
				printf("\n��ϲ��ɹ�����õķ���Ϊ:%d.\n",myfish.xp);
				printf("\n���º����֣����������\n");
				break;
			}	
			FishUpdate();  //��������������������Ϣ 
			if(Click(&op)) {
				Move(op);
			}
			//printf("successfully reach this point!\n");
			Show(bksel);
			if(!Check()) break;
	}//while
	mciSendString("stop bkmusic", NULL, 0, NULL); // ֹͣ���� 
	mciSendString("close bkmusic", NULL, 0, NULL);	//�ر����� 
	closegraph();  //�ر�ͼ�ν��� 
	MessageBox (NULL, TEXT ("��Ϸ������"), TEXT ("��ʾ"), MB_OK) ;
	system("pause");
	return 0;
}//main

/*��Ϸ��ʼ��*/ 
void IniGame(){
	int k;
	mciSendString("open .\\Resources\\Zorba_The_Greek.wav alias bkmusic", NULL, 0, NULL);
	
	/*���Ƶ����ʼ��*/
	myfish.Level = 0;
	myfish.dir = 1;
	myfish.Pos[0]=MaxWidth/2-1;
	myfish.Pos[1]=MaxHeight-25;
	myfish.xp = 0;
	/*���������ʼ��*/ 
	for(k=0;k<MaxFishNum;k++){
		fish[k].isAlive=0;
	}
}// IniGame

/*ָ�����*/  
int Click(char* c){
	if(kbhit()){
		*c = getch();
		return 1;
	}
	else
		return 0;
} //Click

/*С����ƺ���*/
void Move(char c){
	int k;
	//printf("����ָ��%c\n",c);
	switch(c){
	case 'w':
		if (myfish.Pos[1]>30){//�ж��Ƿ񵽴��ͼ���� 
			//printf("ʵ��ִ��w\n");
			myfish.Pos[1]=myfish.Pos[1]-5*myfish.Level-5;	
		}//if
		break;
	case 'a':
		if(myfish.Pos[0]>30){
			//printf("ʵ��ִ��a\n");
			myfish.dir = 1;
			myfish.Pos[0]=myfish.Pos[0] - 5*myfish.Level-5;
		}//if
		break;
	case 's':
		if(myfish.Pos[1] + Sizey[myfish.Level]<MaxHeight-30){
			//printf("ʵ��ִ��s\n");
			myfish.Pos[1] = myfish.Pos[1] + 5*myfish.Level+5;
		}//if
		break;
	case 'd':
		if(myfish.Pos[0] + Sizex[myfish.Level]<MaxWidth-30){
			//printf("ʵ��ִ��d\n");
			myfish.dir = 0;
			myfish.Pos[0] = myfish.Pos[0] + 5*myfish.Level+5;
		}//if
		break;
	default: break;	
	} //switch
}//Move

/*����������Ϣ*/ 
void FishUpdate(){
	int t,tt;
	for(t=0;t<MaxFishNum;t++){//����һ������ 
		if(fish[t].isAlive==0){
			fish[t].isAlive=rand()%5;//���ʲ���
			//printf("successfully reach this point!\n"); 
			if(fish[t].isAlive==1){//�ɹ����� 
				fish[t].Level = rand()%5;//����0-4֮����������
				fish[t].dir = rand()%2;//����Ҳ��������� 0��1
				fish[t].step = 0;
				if(fish[t].dir==1){//���� 
					fish[t].Pos[0] = MaxWidth-Sizex[fish[t].Level]-2;
					fish[t].Pos[1] = rand()%(MaxHeight-Sizey[fish[t].Level]-100)+50;
				}//if
				else {//���� 
					fish[t].Pos[0] = 2;
					fish[t].Pos[1] = rand()%(MaxHeight-Sizey[fish[t].Level]-100)+50;
					//printf("successfully reach this point!\n"); 
				}//else
		 }//if
		 else{
		 	fish[t].isAlive = 0;
		 	break;	
		 }//else	
		}//if 
	}//for
	//λ�ø��� 
	for(tt=0;tt<MaxFishNum;tt++){
		if(fish[tt].isAlive==1){//������������ 
			fish[tt].step = fish[tt].step + Speed[fish[tt].Level];
			if(fish[tt].dir){//���� 
				fish[tt].Pos[0] = MaxWidth-Sizex[fish[tt].Level]-2 - fish[tt].step;
			}//if
			else{//���� 
				fish[tt].Pos[0] = 2 + fish[tt].step;
			}//else
		}//if
	}//for
	
}//FishUpdate

/*��⺯��*/
int Check(){
	int a,b;
	int centerx1,centery1,centerx2,centery2;
	//����Ƿ�����ʳ���� 
	for(a=0;a<MaxFishNum;a++){
		if(fish[a].isAlive==1){
			centerx1 = myfish.Pos[0]+sizexp[myfish.Level]/2;
			centery1 = myfish.Pos[1]+sizexp[myfish.Level]/2;
			centerx2 = fish[a].Pos[0]+sizexp[fish[a].Level]/2;
			centery2 = fish[a].Pos[1]+sizexp[fish[a].Level]/2;
			if(2*abs(centerx1-centerx2)<=(sizexp[myfish.Level]*2/3+sizexp[fish[a].Level])*2/3&&
				2*abs(centery1-centery2)<=(sizexp[myfish.Level]*2/3+sizexp[fish[a].Level])*2/3){//��⵽��ײ 
				if(fish[a].Level<=myfish.Level){//�ɹ���ʳ 
					fish[a].isAlive=0;
					myfish.xp = myfish.xp + Getxp[fish[a].Level];//��������
					if(myfish.Level<4){//δ�����ſ������� 
						if(myfish.xp>=xpNeed[myfish.Level]){//�ж��Ƿ����� 
							myfish.Level++;
							printf("\n��ϲ��ɹ�������Ŀǰ�ȼ�%d\n",myfish.Level);
						}//if 
					}//if
					printf("\n���%d�֣�Ŀǰ�ȼ���%d������ֵ��%d\n",Getxp[fish[a].Level],myfish.Level,myfish.xp);	
				}//if
				else {
					printf("\n��Ϸ������������%d��.\n",myfish.xp);
					switch(myfish.Level){
						case 0: printf("\n�����ǵĴ���...\n");break;
						case 1: printf("\n�Ǹ���ɫ����ʲô�㣬ò�ƻ�û�Թ���\n");break;
						case 2: printf("\n����Ƭ�������ǵ�һ...�ڶ�...���ԣ�����ǿ�ߡ�\n");break;
						case 3: printf("\n���ͣ����޵оͲ�һ����\n");break;
						default: printf("\n���ᣡ������δ֪�Ĵ���\n");break;		
					}
					return 0;
					}//ʧ�� 
				break;//ÿ��ֻ���һ����ײ 
			}//if
		}//if
	}//for
	//����Ƿ������ഥ�� 
	for(b=0;b<MaxFishNum;b++){
		if(fish[b].isAlive==1){
			if(fish[b].dir){//���� 
				if(fish[b].Pos[0]<2){
					fish[b].isAlive=0;
				}//if
			}//if
			else{//���� 
				if(fish[b].Pos[0]>MaxWidth-Sizex[fish[b].Level]-2){
					fish[b].isAlive=0;
				}//if
			}//else
			
		}//if
	}
	return 1;
}//Check 

/*��ʾ����*/ 
void Show(int bksel){
	int u;
	cleardevice();//��չ�����ͼƬ����
	PIMAGE img = newimage();
	switch(bksel){
		case 0:getimage(img,".\\Resources\\background0.png");break;
		case 1:getimage(img,".\\Resources\\background1.png");break;
		case 2:getimage(img,".\\Resources\\background2.png");break;
		case 3:getimage(img,".\\Resources\\background3.png");break;
		default:getimage(img,".\\Resources\\background0.png");break;
	}
	putimage(0,0,img);//����ͼ 
	PIMAGE img1 = newimage();
	if(myfish.dir){//���ݷ���ѡ��ͼƬ 
		switch(myfish.Level){//���ݵȼ�ѡ��ͼƬ 
			case 0 :getimage(img1,".\\Resources\\myfish_level0_l.png");break;
			case 1 :getimage(img1,".\\Resources\\myfish_level1_l.png");break;
			case 2 :getimage(img1,".\\Resources\\myfish_level2_l.png");break;
			case 3 :getimage(img1,".\\Resources\\myfish_level3_l.png");break;
			case 4 :getimage(img1,".\\Resources\\myfish_level4_l.png");break;
			default:getimage(img1,".\\Resources\\myfish_level4_l.png");break;
	}//switch	
}//if
	else{
		switch(myfish.Level){
			case 0 :getimage(img1,".\\Resources\\myfish_level0_r.png");break;
			case 1 :getimage(img1,".\\Resources\\myfish_level1_r.png");break;
			case 2 :getimage(img1,".\\Resources\\myfish_level2_r.png");break;
			case 3 :getimage(img1,".\\Resources\\myfish_level3_r.png");break;
			case 4 :getimage(img1,".\\Resources\\myfish_level4_r.png");break;
			default:getimage(img1,".\\Resources\\myfish_level4_r.png");break;
		}//switch
	}//else
	putimage_withalpha(NULL,img1,myfish.Pos[0],myfish.Pos[1]);//����͸����ʾ 
	//�����������ʾ 
	PIMAGE img2 = newimage();
	for(u=0;u<MaxFishNum;u++){
		if(fish[u].isAlive==1){
			if(fish[u].dir){//���� 
				switch(fish[u].Level){
					case 0 :getimage(img2,".\\Resources\\fish_level0.png");break;
					case 1 :getimage(img2,".\\Resources\\fish_level1_l.png");break;
					case 2 :getimage(img2,".\\Resources\\fish_level2_l.png");break;
					case 3 :getimage(img2,".\\Resources\\fish_level3_l.png");break;
					case 4 :getimage(img2,".\\Resources\\fish_level4_l.png");break;
					default:break;
				}//switch
			}//if
			else{//���� 
				switch(fish[u].Level){
					case 0 :getimage(img2,".\\Resources\\fish_level0.png");break;
					case 1 :getimage(img2,".\\Resources\\fish_level1_r.png");break;
					case 2 :getimage(img2,".\\Resources\\fish_level2_r.png");break;
					case 3 :getimage(img2,".\\Resources\\fish_level3_r.png");break;
					case 4 :getimage(img2,".\\Resources\\fish_level4_r.png");break;
					default:break;
				}//switch
			}//else
			putimage_withalpha(NULL,img2,fish[u].Pos[0],fish[u].Pos[1]);
			//printf("��%d�� �ȼ�%d xλ��%d yλ��%d\n",u,fish[u].Level,fish[u].Pos[0],fish[u].Pos[1]);
		}//if
	}//for
	delimage(img);delimage(img1);delimage(img2);
}//Show

/*������ͼ�����Ժ���*/ 
void TypeMap(int map1[MaxWidth][MaxHeight]){
	int p,q;
	for(p=0;p<MaxHeight;p++){
		for(q=0;q<MaxWidth;q++){
			printf("%d ",map1[q][p]);
		}//for p
		printf("\n");
	}//for q
	printf("----------------------------------------------\n");
}//TypeMap
/*���ֵ����*/
int max(int a,int b){
	if(a>=b) return a;
	else return b;
}
 
