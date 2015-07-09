
char* encodeConv::GB2UTF_8(char *p_srcStr)
{
         char* p_desStr = NULL;
         assert(NULL != p_srcStr);
 
         int isrcLen = strlen(p_srcStr);
         int idesLen = isrcLen*2;
         int x = 0;
         int y = 0;
         short s_Temp = 0;
         p_desStr = new char[idesLen];
         memset(p_desStr,0,idesLen*sizeof(char));
         char chighChar = 0;
         char clowChar = 0;
         char *p_TempStr = p_desStr;
         for(int k = 0;k < idesLen;k++)
         {
                   printf("%x ",*(p_srcStr+k));
         }
         printf("/n");
         while ('/0' != *p_srcStr)
         {
                   if(((unsigned char)*(p_srcStr))>=0xA0)
                   {
                            printf("%s %d %x %x/n",__FILE__,__LINE__,*(p_srcStr+1),*p_srcStr);
                            //gb2312转unicdoe
chighChar = *p_srcStr-0xB0;//大端序
                            clowChar = *(p_srcStr+1)-0xA0;//
                            x = (int)chighChar;
                            y = (int)clowChar;
                            s_Temp = Unicode[x][y];//取unicode编码
                            printf("%s %d %d %d %d/n",__FILE__,__LINE__,x,y,s_Temp);
                            //unicdoe转utf-8
                            chighChar= (0xff00&s_Temp)>>8;
                            clowChar= (0x00ff&s_Temp);
                            char cTemp[3];
                            printf("%s %d %x %x/n",__FILE__,__LINE__,chighChar,clowChar);
                            cTemp[0] = 0xE0 | ((0xF0 & chighChar)>>4);
                            cTemp[1] = 0x80 | (((0x0F & chighChar)<<2) | ((0xC0 & clowChar)>>6));
                            cTemp[2] = 0x80 | (0x3F & clowChar);
                            printf("%s %d %x %x %x/n",__FILE__,__LINE__,cTemp[0],cTemp[1],cTemp[2]);
                            memcpy(p_desStr,cTemp,sizeof(cTemp));
                           
                            p_desStr += 3;                   
                            p_srcStr += 2;
                   }
                   else
                   {
                            memcpy(p_desStr,p_srcStr,1*sizeof(char));
                            p_srcStr +=1;  
                            p_desStr += 1;
                   }
         }
         idesLen = strlen(p_TempStr);
         for(int j = 0;j < idesLen;j++)
         {
                   printf("%x ",*(p_TempStr+j));
         }
         return p_TempStr;//记得外面要delete []p_TempStr;
        
}
