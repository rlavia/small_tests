
/**************************************************************************************
Parser
**************************************************************************************/
int parse(char* xml,void (*eventHandler)(char*, char*))
{
  customEventHandler = eventHandler;
  if(parse_document(&amp;amp;amp;amp;xml))
  {
    return 1;
  }
  return 0;
}
/**************************************************************************************
document           ::=           prolog  element  Misc*
**************************************************************************************/
int parse_document(char** xml)
{
  raiseEvent(&amp;amp;amp;quot;startDocument&amp;amp;amp;quot;,&amp;amp;amp;quot;&amp;amp;amp;quot;);
  if(parse_prolog(xml))    return 1;
  if(parse_element(xml))   return 1;
  parse_misc(xml);
  raiseEvent(&amp;amp;amp;quot;endDocument&amp;amp;amp;quot;,&amp;amp;amp;quot;&amp;amp;amp;quot;);
  return 0;
}

/**************************************************************************************
prolog     ::=           XMLDecl? Misc* (doctypedecl  Misc*)?
**************************************************************************************/
int parse_prolog(char** xml)
{
  if(parse_XMLDecl(xml))      return 1;
  parse_misc(xml);
  if(parse_doctypedecl(xml))  return 1;
  parse_misc(xml);
  return 0;
}
/**************************************************************************************
        XMLDecl    ::=          '&amp;amp;amp;lt;?xml' VersionInfo  EncodingDecl? SDDecl? S? '?&amp;amp;amp;gt;'
**************************************************************************************/
int parse_XMLDecl(char** xml)
{
  if(parse_literal(xml,'&amp;amp;amp;lt;')!=0)    return 1;
  if(parse_literal(xml,'?')!=0)    return 1;
  if(parse_literal(xml,'x')!=0)    return 1;
  if(parse_literal(xml,'m')!=0)    return 1;
  if(parse_literal(xml,'l')!=0)    return 1;
  if(parse_S(xml))         return 1;
  while (getCharacter(xml)!='?') {};
  if(parse_literal(xml,'&amp;amp;amp;gt;')==1)       return 1;
  return 0;
}
/**************************************************************************************
doctypedecl        ::=          '&amp;amp;amp;lt;!DOCTYPE' S  Name (S  ExternalID)? S? ('[' intSubset ']' S?)? '&amp;amp;amp;gt;'
**************************************************************************************/
int parse_doctypedecl(char** xml)
{
  char szName[ELEMENT_NAME_MAX_SIZE];
  if(parse_literal(xml,'&amp;amp;amp;lt;')==1) return 1;
  if(parse_literal(xml,'!')==1) return 1;
  if(parse_literal(xml,'D')==1) return 1;
  if(parse_literal(xml,'O')==1) return 1;
  if(parse_literal(xml,'C')==1) return 1;
  if(parse_literal(xml,'T')==1) return 1;
  if(parse_literal(xml,'Y')==1) return 1;
  if(parse_literal(xml,'P')==1) return 1;
  if(parse_literal(xml,'E')==1) return 1;
  if(parse_S(xml))         return 1;
  if(parse_Name(xml,szName)) return 1;
  parse_S(xml);
  while (getCharacter(xml)!='&amp;amp;amp;gt;')  {};
  raiseEvent(&amp;amp;amp;quot;doctypedecl&amp;amp;amp;quot;,szName);
  return 0;
}
/**************************************************************************************
        element    ::=           EmptyElemTag | STag content ETag
**************************************************************************************/
int parse_element(char** xml)
{
  char szSTagName[ELEMENT_NAME_MAX_SIZE];
  char szETagName[ELEMENT_NAME_MAX_SIZE];
  parse_S(xml);
  if(!parse_EmptyElemTag(xml))
  {
    return 0;
  }
  else
  {
    if(!parse_STag(xml,szSTagName))
    {
      if(!parse_Content(xml))
      {
        if(!parse_ETag(xml,szETagName))
        {
          if(strcmp(szSTagName,szETagName)!=0) 
            {
              return 1;
            }
          return 0;
        }
      else
        {
          return 1;
        }
      }
      else
      {
        return 1;
      }
    }
    else
    {
      return 1;
    }
  }
}
/**************************************************************************************
STag       ::=          '&amp;amp;amp;lt;' Name (S  Attribute)* S? '&amp;amp;amp;gt;'
**************************************************************************************/
int parse_STag(char** xml,char *szSTagName)
{
  char c;
  char szName[ELEMENT_NAME_MAX_SIZE]=&amp;amp;amp;quot;&amp;amp;amp;quot;;
  char* pos1;
  /*strini(szName,ELEMENT_NAME_MAX_SIZE);*/
  pos1=*xml;
  c = getCharacter(xml);
  if(c!='&amp;amp;amp;lt;')
  {
    *xml=pos1;
    return 1;
  }
  if(parse_Name(xml,szName))
  {
    *xml=pos1;
    return 1;
  }
  c = getCharacter(xml);
  if(c!='&amp;amp;amp;gt;') {
    return 1;
  }
  strcpy(szSTagName,szName);
  raiseEvent(&amp;amp;amp;quot;startElement&amp;amp;amp;quot;,szName);
  return 0;
}
/**************************************************************************************
ETag       ::=          '&amp;amp;amp;lt;/' Name  S? '&amp;amp;amp;gt;'
**************************************************************************************/
int parse_ETag(char** xml,char *szETagName)
{
    char c;
    char szName[ELEMENT_NAME_MAX_SIZE]=&amp;amp;amp;quot;&amp;amp;amp;quot;;
    char szNameTemp[ELEMENT_NAME_MAX_SIZE];
    char* pos1;
    pos1=*xml;
    /*strini(szName,ELEMENT_NAME_MAX_SIZE);*/
    c = getCharacter(xml);
    if(c!='&amp;amp;amp;lt;')
    {
      *xml=pos1;
      return 1;
    }
    c = getCharacter(xml);
    if(c!='/')
    {
      *xml=pos1;
      return 1;
    }
    if(parse_Name(xml,szName))
    {
      *xml=pos1;
      return 1;
    }
    c = getCharacter(xml);
    if(c!='&amp;amp;amp;gt;')
    {
      *xml=pos1;
      return 1;
    }
    strcpy(szETagName,szName);
    raiseEvent(&amp;amp;amp;quot;endElement&amp;amp;amp;quot;,szName);    
    return 0;
}
/**************************************************************************************
        EmptyElemTag       ::=          '&amp;amp;amp;lt;' Name (S  Attribute)* S? '/&amp;amp;amp;gt;'
**************************************************************************************/
int parse_EmptyElemTag(char** xml)
{
    char c;
    char szName[ELEMENT_NAME_MAX_SIZE]=&amp;amp;amp;quot;&amp;amp;amp;quot;;
    char* pos1;
    pos1 = *xml;
    /*strini(szName,ELEMENT_NAME_MAX_SIZE);*/
    if(parse_literal(xml,'&amp;amp;amp;lt;')==1)
    {
      *xml=pos1;
      return 1;
    }
    if(parse_Name(xml,szName))
    {
      *xml=pos1;
      return 1;
    }
    if(parse_literal(xml,'/')==1)
    {
      *xml=pos1;
      return 1;
    }
    if(parse_literal(xml,'/')==1) return 1;
    raiseEvent(&amp;amp;amp;quot;EmptyElemTag&amp;amp;amp;quot;,szName);
    return 0;
}
/**************************************************************************************
content    ::=           CharData? ((element | Reference | CDSect | PI | Comment) CharData?)*
**************************************************************************************/
int parse_Content(char** xml)
{
  char c;
  char* pos1;
  char szText[CONTENT_TEXT_MAX_SIZE]=&amp;amp;amp;quot;&amp;amp;amp;quot;;
  int i;

  /*strini(szText,CONTENT_TEXT_MAX_SIZE);*/
  
  i=0;
  pos1 = *xml;
  parse_S(xml);
  c = getCharacter(xml);
  if(c=='&amp;amp;amp;lt;')
  {
    (*xml)--;
    while(!parse_element(xml))
    {

    }
    return 0;
  }
  else
  {
    *xml = pos1;
    c=getCharacter(xml);
    szText[i] = c;
    i++;
    while(c!='&amp;amp;amp;lt;' &amp;amp;amp;amp;&amp;amp;amp;amp; c!='&amp;amp;amp;gt;')
    {
      c = getCharacter(xml);
      szText[i] = c;
      i++;
    }
    i--;
    szText[i] = '&#092;&#048;';
    (*xml)--;
    if (pos1==*xml)
    {
      return 1;
    }
    raiseEvent(&amp;amp;amp;quot;characters&amp;amp;amp;quot;, szText);
    return 0;
  }
}
/**************************************************************************************
Name       ::=          (Letter | '_' | ':') (NameChar)*
**************************************************************************************/
int parse_Name(char** xml,char* szName)
{
  char* pos1;
  char c;
  char szTemp[ELEMENT_NAME_MAX_SIZE];
  strini(szTemp,ELEMENT_NAME_MAX_SIZE);
  pos1 = *xml;
  if (parse_Letter(xml,&amp;amp;amp;amp;c))
  {
    c=getCharacter(xml);
    if( (c!='_') &amp;amp;amp;amp;&amp;amp;amp;amp; (c!=':') )
    {
      *xml = pos1;
      return 1;
    }
  }
  szName[0] = c;
  szName[1] = '&#092;&#048;';
  if (parse_NameChar(xml,szTemp))
  {
    *xml = pos1;
    return 1;
  }
  strcat(szName,szTemp);
  return 0;
}
/**************************************************************************************
Letter     ::=           BaseChar | Ideographic
**************************************************************************************/
int parse_Letter(char** xml,char* letter)
{
  char* pos1;
  char c='&#092;&#048;';
  pos1 = *xml;
  c = getCharacter(xml);
  *letter=c;
  if ( !( (c&amp;amp;amp;gt;='A' &amp;amp;amp;amp;&amp;amp;amp;amp; c&amp;amp;amp;lt;='Z') || (c&amp;amp;amp;gt;='a' &amp;amp;amp;amp;&amp;amp;amp;amp; c&amp;amp;amp;lt;='z') ) )
  {
    *xml = pos1;
    return 1;
  }
  return 0;
}
/**************************************************************************************
NameChar           ::=           Letter | Digit | '.' | '-' | '_' | ':' | CombiningChar | Extender
**************************************************************************************/
int parse_NameChar(char** xml,char* szName)
{
  char c='&#092;&#048;';
  int i=0;
  c = getCharacter(xml);
  szName[0]=c;
  i++;
  while(
          (c&amp;amp;amp;gt;='1' &amp;amp;amp;amp;&amp;amp;amp;amp; c&amp;amp;amp;lt;='0') || (c&amp;amp;amp;gt;='A' &amp;amp;amp;amp;&amp;amp;amp;amp; c&amp;amp;amp;lt;='Z') || (c&amp;amp;amp;gt;='a' &amp;amp;amp;amp;&amp;amp;amp;amp; c&amp;amp;amp;lt;='z') ||
          (c=='.') || (c=='_') || (c==':') || (c=='-')
       )
  {
    c = getCharacter(xml);
    szName[i] = c;
    i++;
  }
  i--;
  szName[i] = '&#092;&#048;';
  (*xml)--;
  return 0;
}
/**************************************************************************************
Misc       ::=           Comment | PI | S
**************************************************************************************/
int parse_misc(char** xml)
{
  if(parse_S(xml)) return 1;
  /*raiseEvent(&amp;amp;amp;quot;Misc&amp;amp;amp;quot;,&amp;amp;amp;quot;&amp;amp;amp;quot;);*/
  return 0;
}
/**************************************************************************************

**************************************************************************************/
int parse_literal(char** xml,char cLiteral)
{
  char c;
  char* pos1;
  pos1 = *xml;
  c = getCharacter(xml);
  if(c!=cLiteral)
  {
    *xml = pos1;
    return 1;
  }
  else
  {
    return 0;
  }
}
/**************************************************************************************

**************************************************************************************/
char getCharacter(char** xml)
{
  char c='&#092;&#048;';
  c = **xml;
  (*xml)++;
  return c;
}
/**************************************************************************************
S          ::=          (#x20 | #x9 | #xD | #xA)+
**************************************************************************************/
int parse_S(char** xml)
{
  if( !(((**xml)==' ') || ((**xml)==0x09) || ((**xml)==0x0A) || ((**xml)==0x0D)) )
  {
    return 1;
  }
  (*xml)++;
  while( ((**xml)==' ') || ((**xml)==0x09) || ((**xml)==0x0A) || ((**xml)==0x0D) )
  {
    (*xml)++;
  }
  return 0;
}
/**************************************************************************************

**************************************************************************************/
void raiseEvent(char* szEventName, char* szText)
{
  customEventHandler(szEventName,szText);
}
/**************************************************************************************

**************************************************************************************/
void strini(char* s,long l)
{
  long i=0;
  for(i=0;i&amp;amp;amp;lt;l;i++) s[i] = '&#092;&#048;';
}


