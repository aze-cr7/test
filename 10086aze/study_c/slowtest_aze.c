#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
struct T{                                              //oragindata
	int name[2];                      
	int num[11];
	char sdname[7];
}sd[21];
struct D{                                              //usefuldata    
	char diskname[7];
	int rd_ios;
	int wr_ios;
	int tot_ticks;
	int svc_t; 
}sdd[3150];
int nowread(){                                                                     // read  file /proc/diskstats and save in sd[] return disk shuliang
	FILE *in=fopen("/proc/diskstats","r");
	int n,i;
	int nu=0;
	for(n=0;!feof(in);n++){
		fscanf(in,"%d %d %s",&sd[n].name[0],&sd[n].name[1],&sd[n].sdname);
		for(i=0;i<11;i++){
			fscanf(in," %d ",&sd[n].num[i]);
		}
		nu++;
	}
	return n;
	fclose(in);
}
void display(struct T *p,int count){                                                         //show all disk name
	p=sd;
	int i;
	for(i=0;i<count;i++,p++)
	printf("%s\n",p->sdname);
}
int savedata(struct T *p,int nmanum,int cishu,int jiange){                           //save useful data in sdd[] return sdd[] jilu hangshu
	int sum=0,j,num=0,i;
	for(j=0;j<cishu;j++){
		num=nowread();
		p=sd;
		for(i=0;i<num;p++,i++){
			strcpy(sdd[sum+i].diskname,p->sdname);
			sdd[sum+i].rd_ios=p->num[0];
			sdd[sum+i].wr_ios=p->num[4];
			sdd[sum+i].tot_ticks=p->num[9];
		}
		sum=sum+num;
		sleep(jiange);
	}
	printf("Total jilu is %d tiao\n",sum);
	/*int f=0;
	  struct D *jiji=sdd;
	  for(f;f<12;jiji=jiji+11,f++){
	  printf("%d\n",jiji->rd_ios);
	  }*/
	return sum;
}
void showAll(struct T *p,int nu){                                         //show All disk chushi informations
	printf("All of disks informations:\n");
	int n;
	for(n=0;n<nu;n++,p++){
		printf("%d %d %s",p->name[0],p->name[1],p->sdname);
		int i;
		for(i=0;i<11;i++){
			printf(" %d ",p->num[i]);
		}
		printf("\n");
	} 
}
void jisuansvc_t(char diskname[7],int svc_tcount,int sdnum,int sdname,struct T *p,struct D *q,int time);  //quanzhi jisuanhanshu shengming
void Check(struct T *p,struct D *q){                                                    //zhiding disk Check hanshu
	printf("Please print check time(minute) and check jiange(miao):\n");
	int time,jiange;
	scanf("%d %d",&time,&jiange);
	int s=time*60/jiange;                                                                //checkcishu hanshu[zi ding yi]
	printf("Please print diskname need check:\n");
	char sdname[10];
	scanf("%s",sdname);
	int findsdname;
	int sdnum=nowread();
	p=sd;
	printf("Please shao deng pian ke\n");
	int jilu=savedata(p,sdnum,s,jiange);
	for(findsdname=0;findsdname<sdnum;findsdname++){
		if(strcmp(p->sdname,sdname)==0){
			printf("Now over checking disk %s thanks for wait %d minutes patience\n",p->sdname,time);
			int jiancecishu=jilu/sdnum;
			printf("mubaio disk have read %d tiao jilu\n",jiancecishu);
			int kaishi,svc_tcount=0;
			q=sdd;
			struct D *next;
			while(1)	
			{
            if(strcmp(q->diskname,sdname)==0){
					next=(q+sdnum);
					for(kaishi=0;kaishi<jiancecishu-1;kaishi++){
						q->svc_t=(next->tot_ticks-q->tot_ticks)%(next->rd_ios+next->wr_ios)-(q->rd_ios+q->wr_ios);
						printf("%d %d %d %d\n",q->rd_ios,q->wr_ios,q->tot_ticks,q->svc_t);
						svc_tcount++;
						q=q+sdnum;
						next=next+sdnum;
					}
					printf("Get %d tiao svc_t\n",svc_tcount);
					jisuansvc_t(sdname,svc_tcount,sdnum,findsdname,p,q,time);
					break;
				}
				else
					q++;
			}
			break;
		}
		else
			p++;
	}
p=sd;
q=sdd;
}
void jisuansvc_t(char diskname[7],int svc_tcount,int sdnum,int sdname,struct T *p,struct D *q,int time){              // manpan panduan hanshu
	int i;
    q=sdd;
	while(1)
	{
		if(strcmp(q->diskname,diskname)==0){
			printf("%s\n",q->diskname);
			int savesvc[sdnum][svc_tcount];
			for(i=0;i<svc_tcount;i++){                                                                          // save sdname[i]'svc_t in savesvc[sdnu][] total jiancecishuh-1 tiao
				savesvc[sdname][i]=q->svc_t;	
				q=q+sdnum;
			}
	int temp,sort_1,sort_2;
	for(sort_1=0;sort_1<svc_tcount-1;sort_1++){                                 // svc_t paixu
		for(sort_2=sort_1;sort_2<svc_tcount;sort_2++){
			if(savesvc[sdname][sort_1]<savesvc[sdname][sort_2]){
				temp=savesvc[sdname][sort_1];
				savesvc[sdname][sort_1]=savesvc[sdname][sort_2];
				savesvc[sdname][sort_2]=temp;
			}
		}
	}
	int quanzhong;                                                                                                                        // quanzhonghanshu [ zi ding yi ]
	quanzhong=(savesvc[sdname][0]+savesvc[sdname][svc_tcount-1])/2;
	printf("MAX_svc_t is %d , MIN_svc_t is %d SO quanzhong=%d\n",savesvc[sdname][0],savesvc[sdname][svc_tcount-1],quanzhong);
	int fuquan;
	int quan0num,quan1num,quan2num;
	for(fuquan=0;fuquan<svc_tcount;fuquan++){
		if((savesvc[sdname][fuquan]>quanzhong||savesvc[sdname][fuquan]==quanzhong)&&(fuquan>(svc_tcount/2-5))&&(fuquan<(svc_tcount/2+5)))   // quanzhi=1 de fan  wei yu [zi ding yi ]
			quan1num++;
		else if(savesvc[sdname][fuquan]>quanzhong&&(fuquan>(svc_tcount/2+5)))
			quan2num++;
		else
			quan0num++;
	}
	int answer=0*quan0num+1*quan1num+quan2num*2;
	if(answer>time*60)
		printf("%s is manpan!\n",p->sdname);
	else
		printf("%s is formel!\n",p->sdname);
		break;
		}
		else
			q++;
		}	
}
int main(){
	printf("***Welcome to diskcheck!***\n");
    printf("Please choose:\n");
	int chose;
	struct T *innode=sd;
	struct D *disic=sdd;
	while(1)
	{
	printf(" 1.show /proc/diskstats \n 2.show disk name \n 3.zhiding check \n 4.exit \n");
	scanf("%d",&chose);	
	if(chose==1){
			int a1=nowread();
			showAll(innode,a1);
			printf("\n***qing xuan ze: ***\n \n");
		}
	else if(chose==2){
    int a1=nowread();
	display(innode,a1);
	printf("\n***qing xuan ze: ***\n \n");
	}
	else if(chose==3){
	Check(innode,disic);
	printf("\n***qing xuan ze: ***\n \n");
	}
	else if(chose==4){
		printf("\nThanks for use!\n");
		break;
	}
	}
	return 0;
}

