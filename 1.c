#include"h.h"
typedef struct 
{
int pres;
int fra_n;
int dirty;
int ref;
int ar_time;
    }p;
    static int dirty_counter=0;
    int arr_cou=0;
    static int debug;
void reduce(p *pa,int page_count)
{
for(int i=0;i<page_count;i++)
{
if(pa[i].pres==1&&pa[i].ref>0)
    pa[i].ref--;
    }
    }
void replace(p *pa,int page_num,int vic_nu,int *fr,int d)
{
       if(debug){
       printf("\tpage %d replaced by page %d\n",vic_nu,page_num);
        printf("    ************************************\n");}
           if(debug)
           {
if(pa[vic_nu].dirty){
    printf("\tpage %d was dirty\n",vic_nu);
        printf("    ************************************\n");}
    else{
        printf("\tpage %d was not dirty\n",vic_nu);
        printf("    ************************************\n");}
}
  if(pa[vic_nu].dirty==1)
        dirty_counter++;

 int frame_ji=pa[vic_nu].fra_n;
 ///clearing
 pa[vic_nu].pres=PRESENT;
 pa[vic_nu].ref=REF_COUNT;
 pa[vic_nu].ar_time=ARR_TIME;
 pa[vic_nu].fra_n=FRAME_NO;
 pa[vic_nu].dirty=DIRTY;
//////

   pa[page_num].fra_n=frame_ji;
   pa[page_num].pres=1;
   pa[page_num].ref=3;
   pa[page_num].ar_time=arr_cou++;
   pa[page_num].dirty=d;
   fr[frame_ji]=page_num;


    }


    /////MAIN////
void main(int argc,char *argv[])
{

if(argc!=6)     
{
printf("wrong input try again....\n");
printf("progam_name , virtual_memory_bits,page_size_bits,number_of_frames,input_file_name,debug_flag(d/n)\n");
return;
    }
        printf("    ************************************\n");
int virtual =1<<atoi(argv[1]);///do the power of 2
int page=1<<atoi(argv[2]);/// do the power of 2
int frame=atoi(argv[3]);// number of frame
int page_count=virtual/page;
debug=(argv[5][0]=='d');

p pa[page_count];//page table
int fr[frame];//frame table

////////////initializing////////////
for(int i=0;i<page_count;i++)
{
pa[i].pres=PRESENT;
pa[i].fra_n=FRAME_NO;
pa[i].dirty=DIRTY;
pa[i].ref=REF_COUNT;
pa[i].ar_time=ARR_TIME;
    }
for(int i=0;i<frame;i++)
{

fr[i]=-1;

    }
//////////////////////////////////////
char a[10];
char c;
int i=0;
int total_memory_aces=0;
int global_memory_aces=0;
int page_num;
int emp_fon=0;
int page_fault=0;
char ch;
int g[page_count];
int mn=0;
FILE *fp=fopen(argv[4],"r");
if(fp==NULL)
{
printf("file error\n");
return;

    }
    if(debug)
 {      printf("       \t/////simulation starts/////\n");
        printf("    ************************************\n");}
while((ch=fgetc(fp))!=EOF)
{

    int address;
    if(ch!=' '&&ch!='r'&&ch!='w'&&ch!='\n')
 a[i++]=ch;
else if(ch=='r'||ch=='w')
    c=ch;
    if(ch=='\n'){
         total_memory_aces++;
 global_memory_aces++;
address=atoi(a);
page_num=address/page;
///////////////////////////////////////////////////////////////////////////////////
if(global_memory_aces%4==0){
   reduce(pa,page_count);
    }
    /////////////////////////////////////////////////////////////////////////////////////
        i=0;
        bzero(a,sizeof(a));


if(pa[page_num].pres==1)///page is in the ram
{ 
 if(pa[page_num].ref>=0&&pa[page_num].ref<10)
pa[page_num].ref++;
if(c=='w')
    pa[page_num].dirty=1;


    }
    else///page fault
    {
//page_fault++;
        emp_fon=0;
       
for(int j=0;j<frame;j++)
  {  
      if(fr[j]==-1)
      {
          if(debug){
              printf("\tpage NULL replaced by page %d\n",page_num);
        printf("    ************************************\n");}
      pa[page_num].pres=1;
      pa[page_num].fra_n=j;
 
      pa[page_num].dirty=0;
      pa[page_num].ref=3;
      pa[page_num].ar_time=arr_cou++;
      fr[j]=page_num;
      emp_fon=1;
      if(c=='w')
          pa[page_num].dirty=1;
      break;
      }
      }
      if(emp_fon==0)
      {
page_fault++;
          int l=0;
      bzero(g,sizeof(g));
for(int k=0;k<page_count;k++)//////////////replacemnet part here
{
if(pa[k].pres==1&&pa[k].ref==0)
{
  g[l]=k;
  l++;
}}

if(l==0)
   {
int h[page_count];
bzero(h,sizeof(h));
    int cnt=0;
for(int k=0;k<page_count;k++)
{
if(pa[k].pres==1)
{
h[cnt]=k;
cnt++;
} }
        int victim=h[0];
          int min_time=pa[h[0]].ar_time;
            for(int b=1;b<cnt;b++)
                {
             if(pa[h[b]].ar_time<min_time)
             {
                 min_time=pa[h[b]].ar_time;
                 victim=h[b];
                     
                 }

                    }
           if(c=='w'){
replace(pa,page_num,victim,fr,1);
}
            else
            {
                replace(pa,page_num,victim,fr,0);
            }
    }
else if(l==1)
{
int nu=g[0];
if(c=='w')
replace(pa,page_num,nu,fr,1);
else
replace(pa,page_num,nu,fr,0);   
    }
else if(l>1)
{
        int victim=g[0];
          int min_time=pa[g[0]].ar_time;
            for(int b=1;b<l;b++)
                {
             if(pa[g[b]].ar_time<min_time)
             {
                 min_time=pa[g[b]].ar_time;
                 victim=g[b];
    
                 }
    
                    }
           if(c=='w'){
replace(pa,page_num,victim,fr,1);
}
            else
            {
                replace(pa,page_num,victim,fr,0);
               
            }
    }}}}}
if(debug){
        printf("      \t/////simulation starts/////\n");
        printf("    ************************************\n");
}
printf("\tnumber of memory accesses = %d\n",total_memory_aces);
        printf("    ************************************\n");
printf("\tnumber of memory accesses that result in page faults = %d\n",page_fault);
        printf("    ************************************\n");
printf("\tnumber of pages written to disk = %d\n",dirty_counter);
        printf("    ************************************\n");



    }


