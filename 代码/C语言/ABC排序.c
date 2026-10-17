#include<stdio.h>
int main(){
	int a,b,c;
	char x,y,z;
	scanf("%d %d %d",&a,&b,&c);
	scanf(" %c %c %c",&x,&y,&z);
//µÚÒ»¸ö%cÇ°ÃæÒ»¶¨ÒªÓÐ¿Õ¸ñºÅ£¬²»È»ºóÃæ»á¶ÁÈ¡²»µ½ 
	int A,B,C;
	
	if(a<=b&&a<=c){A=a;if(b<=c){B=b;C=c;}
	else{B=c;C=b;}   }
	
	else if(b<=a&&b<=c){A=b;if(a<=c){B=a;C=c;}
	else{B=c;C=a;}   }
	
	else{A=c;if(a<=b){B=a;C=b;}
	else{B=b;C=a;}   }
	
    if(x=='A'){printf("%d",A);}
	else if(x=='B'){printf("%d",B);}
	else if(x=='C'){printf("%d",C);}
	printf(" "); 
	
	if(y=='A'){printf("%d",A);}
	else if(y=='B'){printf("%d",B);}
	else if(y=='C'){printf("%d",C);}
	printf(" ");
	
    if(z=='A'){printf("%d",A);}
    else if(z=='B'){printf("%d",B);}
    else if(z=='C'){printf("%d",C);}
    printf("\n");
	return 0;
}
