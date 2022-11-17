#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h> 
#include<process.h>
#define size 100000

void merge(long*a,long*b,int i,int m,int n)
{
	int j,k,t;
	j=m+1;
	k=i;
	while(i<=m && j<=n)
	{
		if(a[i]<=a[j])
			b[k++]=a[i++];
		else
			b[k++]=a[j++];
	}
	if(i>m)
		for(t=j ;t<=n;t++)
			b[t]=a[t];
	else
		for(t=i ;t<=m;t++)
			b[k+t-i]=a[t];
}
void mergepass(long*a,long*b,int n,int s)
{
	int i,j;
	for(i=0;i<=n-2*s+1;i+=2*s)
		merge(a,b,i,i+s-1,i+2*s-1);
	if(i+s-1<n)
		merge(a,b,i,i+s-1,n);
	else
		for(j=i;j<=n;j++)
			b[j]=a[j];
}
void mergesort(long *a,int n)
{
	int s=1;
	long *b=(long*)malloc(sizeof(long)*(size-1));
	while(s<n)
	{
		mergepass(a,b,n,s);
		s*=2;
		mergepass(b,a,n,s);
		s*=2;
	}
}
void main()
{
	FILE *fp;
	FILE *cfptr;
	int c=1;
	char name[10];

	printf("資料處理中. . .\n\n");
	fp=fopen("a.txt","r");
	while(!feof(fp))
	{  
		sprintf(name,"%d.txt",c);//名++
		cfptr=fopen(name,"w");

		long *a=(long*)malloc(sizeof(long)*(size-1));

		for(int i=0;i<size;i++)//讀入
			fscanf(fp,"%d",&a[i]);

		mergesort(a,size-1);

		for(int i=0;i<size;i++)//寫入
			fprintf(cfptr,"%d ",a[i]);


		fclose(cfptr);
		c++;
	} 
	fclose(fp);
	if(c>3)
	{
		system("cls");
		printf("檔案合併中. . .\n");
		FILE *file;
		char name2[10];
		int m1=0,m2=0,n=1;
		for(int i=1 ; i<c ; i++)
		{
			sprintf(name,"%d.txt",i);
			cfptr=fopen(name,"r");
			i++;
			sprintf(name2,"%d.txt",i);
			fp=fopen(name2,"r");
			file=fopen("temp.txt","w");

			if(fp==NULL)//單數最後檔
			{
				fclose(cfptr);
				fclose(file);
				i--;
				sprintf(name2,"%d.txt",i);
				sprintf(name,"%d.txt",n);
				rename(name2,name);
				n++;
				remove("temp.txt");
				if(strcmp(name,name2)==0)
					break;
			}
			else
			{
				fscanf(fp,"%d",&m1);
				fscanf(cfptr,"%d",&m2);
				while(1)
				{
					if(m1<=m2)
					{
						fprintf(file,"%d ",m1);
						fscanf(fp,"%d",&m1);
					}
					else 
					{
						fprintf(file,"%d ",m2);
						fscanf(cfptr,"%d",&m2);
					}

					if(feof(cfptr))
					{
						while(!feof(fp))
						{
							fprintf(file,"%d ",m1);
							fscanf(fp,"%d",&m1);
						}
						break;
					}
					else if(feof(fp))
					{
						while(!feof(cfptr))
						{
							fprintf(file,"%d ",m2);
							fscanf(cfptr,"%d",&m2);
						}
						break;
					}
				}
				fclose(fp);
				fclose(cfptr);
				fclose(file);
				remove(name);
				remove(name2);
				sprintf(name,"%d.txt",n);
				rename("temp.txt",name);
				n++;
			}
			if(i==c-1)
			{
				i=0;
				c=n;
				n=1;
			}
			if(c==1)
				break;
		}
	}
	system("cls");
	printf("完成!!\n");
	system("pause");
}
