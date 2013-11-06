
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int match(char *regexp,char *text);/*match the regexp in text*/
int matchhere(char *regexp,char *text);/*matchhere the regexp in the front of the text*/
int matchstar (int c,char *regexp,char *text);/*matchstar the regexp with "*" in the front of the text*/

/*match the regexp in text*/
int match(char *regexp,char *text)
{
    if(regexp[0] == '^')
    {
        return matchhere(regexp+1,text);
    }
    do{ /*scan char by char*/
        if (matchhere(regexp,text))
        {
            return 1;
        }
    }while (*text++!= '\0');
    return 0;
}

/*matchhere the regexp in the front of the text*/
int matchhere(char *regexp,char *text)
{
    if (regexp[0] == '\0')
    {
        return 1;
    }
    if (regexp[1] == '*')
    {
        return matchstar(regexp[0],regexp+2,text);
    }
    if (regexp[0] == '$' && regexp[1]=='\0')
    {
        return *text == '\0';
    }
    if (*text!='\0' && (regexp[0]=='.' || regexp[0]==*text))
    {
        return matchhere(regexp+1,text+1);
    }
    return 0;
}

/*matchstar the regexp with "*" in the front of the text*/
int matchstar (int c,char *regexp,char *text)
{
    do
    { /*"*"match the same char*/
        if (matchhere(regexp,text))
        {
            return 1;
        }
    }while (*text!='\0' && (*text++ ==c || c== '.'));
    return 0;
}

int main(int argc,char *argv[])
    {
        char line_buffer[1024];/* put the line */
        FILE *fp;             /* file pointer*/
        
        if (argc < 3)
        {
            fprintf(stderr,"Use: %s regular_expr files ..\n", argv[0]);
            return 1;
        }
    
        
        for (int i=2;i < argc;i++)
        {
            if ((fp=fopen(argv[i],"rb"))==NULL)
            {
                printf("%s: read failure.\n",argv[i]);
            }
            
            else while (fgets(line_buffer,sizeof(line_buffer),fp))
            {
                if(match(argv[1],line_buffer)==1)/*match the regular expression,if success, return 1*/
                {
                    printf("%s\n",line_buffer);/*print the results*/
                }
            }
            
            fclose(fp);
        }
        return 0;
    }

