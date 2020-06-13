//大鱼吃小鱼，c语言大实验
//图片素材与音乐素材均来自网络 
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
	int Pos[2];//位置 x,y
	int xp;//经验 
	int dir;//方向 0右 1左 
	int Level;//等级 0,1,2,3,4
}MyFish;

typedef struct {
	int Pos[2];//位置x,y 
	int isAlive;//是否存在 0不存在 1存在 
	int dir;//方向 0右 1左
	int step;//记录游动距离 
	int Level;//鱼的种类 0,1,2,3,4
}Fish;
Fish fish[MaxFishNum];
MyFish myfish;
//int MaxFishNum = 20;  
int Size[LevelNum]={1,4,9,16,25};//每种鱼类的大小
int Sizey[LevelNum]={1,2,3,4,5};
int Sizex[LevelNum]={1,2,3,4,5};//长宽比为1:1 
int Getxp[LevelNum]={1,2,3,4,5};//每种鱼类能获得的经验 
int xpNeed[LevelNum-1]={3,7,15,25};//升级所需的经验 
int Speed[LevelNum]={2,5,3,4,2};//鱼类游动速度 
int sizexp[LevelNum] = {24,36,48,60,72};
void IniGame();//初始化
int Click(char* c); //检查按键 
void Move(char c);// 更新控制鱼的位置 
void FishUpdate();//其他鱼类更新 
void Show(int bksel);//显示
int Check();// 第一步检测是否有吞食产生，失败返回0，第二步检测是否有鱼类接触边缘消失，默认返回1 
int max(int a,int b);

/*主程序*/ 
int main(){
	int x,y,scon=0,bgm=1,tb=0,bksel=0; 
	char op;
	srand((unsigned int)time(0));
	printf("游戏介绍：\n");
	printf("\n1.游戏包含自己可以控制的小黄鱼，出生在下方中间，一开始等级为0，\n你需要用w,a,s,d四个键来控制小鱼的游动，对应着上，左，下，右。\n");
	printf("\n2.游戏有着魔性BGM，来自我喜欢的电影《两杆大烟枪》，你需要在BGM的\n加持下坚持存活，一定时间后会告知胜利。\n");
	printf("\n3.如果可能的话，可以吃掉其他不大于自己的鱼来获得经验值，提高存活\n几率。经验到达一定程度会自动升级，最高等级为4级。\n");
	printf("\n4.游戏中除了自己的鱼，还有五种生物，分别为海星、小蓝鱼、海马、刺\n头鱼和鲨鱼。它们的等级分别为：海星（0级）<小蓝鱼（1级）<海马（2级）\n<刺头鱼（3级）<鲨鱼（4级）。\n");
	printf("\n5.游戏速度会根据时长变快，努力存活。\n");
	printf("\n6.该界面会记录你的部分游戏状态。\n");
	printf("\n7.胜利条件：规定时间内获得350分或者坚持不被其他鱼吃掉。\n");
	printf("\n8.祝游玩愉快！\n");
	printf("\n请输入数字并按下空格决定是否开启BGM，1（是），0（否）：\n");
	scanf("%d",&bgm); 
	printf("\n请输入数字并按下空格决定背景图，0（鱼群），1（珊瑚），2（潜艇），3（沉船）：\n");
	scanf("%d",&bksel); 
	printf("\n请输入数字并按下空格决定游戏难度，0（简单），1（困难），2（噩梦）：\n");
	scanf("%d",&tb); 
	IniGame();//初始化游戏 
	switch(tb){
		case 0:
			printf("\n明智之选\n");
			myfish.Level = 1;
			break;
		case 1:
			for(int i=0;i<LevelNum;i++)
				Speed[i]=Speed[i]+2;
			for(int j=0;j<LevelNum-1;j++)
				xpNeed[j]=xpNeed[j]*2-2;
				break;
		case 2:
			printf("\n祝你好运...\n");
			for(int i=0;i<LevelNum;i++)
				Speed[i]=Speed[i]*2;
			for(int j=0;j<LevelNum-1;j++)
				xpNeed[j]=xpNeed[j]*3-1;
				break;
		default:break;
		}
	printf("--------------------------------------------------------------------\n");
	MessageBox (NULL, TEXT ("游戏即将开始"), TEXT ("提示"), MB_OK) ;//开始弹窗 
	//printf("%d",map[30][40]);
	//TypeMap(map);
	initgraph(MaxWidth,MaxHeight);//创建一个图形窗口 
	Show(bksel);// 显示 
	if(bgm){
		mciSendString("play bkmusic", NULL, 0, NULL);//播放音乐
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
				printf("\n恭喜你成功存活！获得的分数为:%d.\n",myfish.xp);
				printf("\n阁下好身手，在下佩服！\n");
				break;
			}	
			FishUpdate();  //产生并更新其他鱼类信息 
			if(Click(&op)) {
				Move(op);
			}
			//printf("successfully reach this point!\n");
			Show(bksel);
			if(!Check()) break;
	}//while
	mciSendString("stop bkmusic", NULL, 0, NULL); // 停止音乐 
	mciSendString("close bkmusic", NULL, 0, NULL);	//关闭音乐 
	closegraph();  //关闭图形界面 
	MessageBox (NULL, TEXT ("游戏结束！"), TEXT ("提示"), MB_OK) ;
	system("pause");
	return 0;
}//main

/*游戏初始化*/ 
void IniGame(){
	int k;
	mciSendString("open .\\Resources\\Zorba_The_Greek.wav alias bkmusic", NULL, 0, NULL);
	
	/*控制的鱼初始化*/
	myfish.Level = 0;
	myfish.dir = 1;
	myfish.Pos[0]=MaxWidth/2-1;
	myfish.Pos[1]=MaxHeight-25;
	myfish.xp = 0;
	/*其他鱼类初始化*/ 
	for(k=0;k<MaxFishNum;k++){
		fish[k].isAlive=0;
	}
}// IniGame

/*指令监听*/  
int Click(char* c){
	if(kbhit()){
		*c = getch();
		return 1;
	}
	else
		return 0;
} //Click

/*小鱼控制函数*/
void Move(char c){
	int k;
	//printf("输入指令%c\n",c);
	switch(c){
	case 'w':
		if (myfish.Pos[1]>30){//判断是否到达地图顶部 
			//printf("实际执行w\n");
			myfish.Pos[1]=myfish.Pos[1]-5*myfish.Level-5;	
		}//if
		break;
	case 'a':
		if(myfish.Pos[0]>30){
			//printf("实际执行a\n");
			myfish.dir = 1;
			myfish.Pos[0]=myfish.Pos[0] - 5*myfish.Level-5;
		}//if
		break;
	case 's':
		if(myfish.Pos[1] + Sizey[myfish.Level]<MaxHeight-30){
			//printf("实际执行s\n");
			myfish.Pos[1] = myfish.Pos[1] + 5*myfish.Level+5;
		}//if
		break;
	case 'd':
		if(myfish.Pos[0] + Sizex[myfish.Level]<MaxWidth-30){
			//printf("实际执行d\n");
			myfish.dir = 0;
			myfish.Pos[0] = myfish.Pos[0] + 5*myfish.Level+5;
		}//if
		break;
	default: break;	
	} //switch
}//Move

/*更新鱼类信息*/ 
void FishUpdate(){
	int t,tt;
	for(t=0;t<MaxFishNum;t++){//产生一个鱼类 
		if(fish[t].isAlive==0){
			fish[t].isAlive=rand()%5;//概率产生
			//printf("successfully reach this point!\n"); 
			if(fish[t].isAlive==1){//成功产生 
				fish[t].Level = rand()%5;//产生0-4之间的随机整数
				fish[t].dir = rand()%2;//方向也是随机产生 0，1
				fish[t].step = 0;
				if(fish[t].dir==1){//向左 
					fish[t].Pos[0] = MaxWidth-Sizex[fish[t].Level]-2;
					fish[t].Pos[1] = rand()%(MaxHeight-Sizey[fish[t].Level]-100)+50;
				}//if
				else {//向右 
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
	//位置更新 
	for(tt=0;tt<MaxFishNum;tt++){
		if(fish[tt].isAlive==1){//如果存在则更新 
			fish[tt].step = fish[tt].step + Speed[fish[tt].Level];
			if(fish[tt].dir){//向左 
				fish[tt].Pos[0] = MaxWidth-Sizex[fish[tt].Level]-2 - fish[tt].step;
			}//if
			else{//向右 
				fish[tt].Pos[0] = 2 + fish[tt].step;
			}//else
		}//if
	}//for
	
}//FishUpdate

/*检测函数*/
int Check(){
	int a,b;
	int centerx1,centery1,centerx2,centery2;
	//检测是否有吞食产生 
	for(a=0;a<MaxFishNum;a++){
		if(fish[a].isAlive==1){
			centerx1 = myfish.Pos[0]+sizexp[myfish.Level]/2;
			centery1 = myfish.Pos[1]+sizexp[myfish.Level]/2;
			centerx2 = fish[a].Pos[0]+sizexp[fish[a].Level]/2;
			centery2 = fish[a].Pos[1]+sizexp[fish[a].Level]/2;
			if(2*abs(centerx1-centerx2)<=(sizexp[myfish.Level]*2/3+sizexp[fish[a].Level])*2/3&&
				2*abs(centery1-centery2)<=(sizexp[myfish.Level]*2/3+sizexp[fish[a].Level])*2/3){//检测到碰撞 
				if(fish[a].Level<=myfish.Level){//成功吞食 
					fish[a].isAlive=0;
					myfish.xp = myfish.xp + Getxp[fish[a].Level];//经验增加
					if(myfish.Level<4){//未满级才可以升级 
						if(myfish.xp>=xpNeed[myfish.Level]){//判断是否升级 
							myfish.Level++;
							printf("\n恭喜你成功升级，目前等级%d\n",myfish.Level);
						}//if 
					}//if
					printf("\n获得%d分，目前等级：%d，经验值：%d\n",Getxp[fish[a].Level],myfish.Level,myfish.xp);	
				}//if
				else {
					printf("\n游戏结束，你获得了%d分.\n",myfish.xp);
					switch(myfish.Level){
						case 0: printf("\n吃星星的代价...\n");break;
						case 1: printf("\n那个蓝色的是什么鱼，貌似还没吃够。\n");break;
						case 2: printf("\n在这片海域你是第一...第二...不对，第三强者。\n");break;
						case 3: printf("\n加油，离无敌就差一步！\n");break;
						default: printf("\n纳尼！发生了未知的错误。\n");break;		
					}
					return 0;
					}//失败 
				break;//每轮只检测一个碰撞 
			}//if
		}//if
	}//for
	//检测是否有鱼类触边 
	for(b=0;b<MaxFishNum;b++){
		if(fish[b].isAlive==1){
			if(fish[b].dir){//向左 
				if(fish[b].Pos[0]<2){
					fish[b].isAlive=0;
				}//if
			}//if
			else{//向右 
				if(fish[b].Pos[0]>MaxWidth-Sizex[fish[b].Level]-2){
					fish[b].isAlive=0;
				}//if
			}//else
			
		}//if
	}
	return 1;
}//Check 

/*显示函数*/ 
void Show(int bksel){
	int u;
	cleardevice();//清空工作区图片缓存
	PIMAGE img = newimage();
	switch(bksel){
		case 0:getimage(img,".\\Resources\\background0.png");break;
		case 1:getimage(img,".\\Resources\\background1.png");break;
		case 2:getimage(img,".\\Resources\\background2.png");break;
		case 3:getimage(img,".\\Resources\\background3.png");break;
		default:getimage(img,".\\Resources\\background0.png");break;
	}
	putimage(0,0,img);//背景图 
	PIMAGE img1 = newimage();
	if(myfish.dir){//根据方向选择图片 
		switch(myfish.Level){//根据等级选择图片 
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
	putimage_withalpha(NULL,img1,myfish.Pos[0],myfish.Pos[1]);//背景透明显示 
	//其他鱼类的显示 
	PIMAGE img2 = newimage();
	for(u=0;u<MaxFishNum;u++){
		if(fish[u].isAlive==1){
			if(fish[u].dir){//向左 
				switch(fish[u].Level){
					case 0 :getimage(img2,".\\Resources\\fish_level0.png");break;
					case 1 :getimage(img2,".\\Resources\\fish_level1_l.png");break;
					case 2 :getimage(img2,".\\Resources\\fish_level2_l.png");break;
					case 3 :getimage(img2,".\\Resources\\fish_level3_l.png");break;
					case 4 :getimage(img2,".\\Resources\\fish_level4_l.png");break;
					default:break;
				}//switch
			}//if
			else{//向右 
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
			//printf("第%d个 等级%d x位置%d y位置%d\n",u,fish[u].Level,fish[u].Pos[0],fish[u].Pos[1]);
		}//if
	}//for
	delimage(img);delimage(img1);delimage(img2);
}//Show

/*画出地图，调试函数*/ 
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
/*最大值函数*/
int max(int a,int b){
	if(a>=b) return a;
	else return b;
}
 
