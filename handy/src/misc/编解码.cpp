// https://blog.csdn.net/mfcing/article/details/7529848

string U2A(const wstring& str)	//Unicode字符转Ascii字符 
{
	string strDes;
	if ( str.empty() )
		goto __end;

	int nLen=::WideCharToMultiByte(CP_ACP, 0, str.c_str(), str.size(), NULL, 0, NULL, NULL);
	if ( 0==nLen )
		goto __end;
	char* pBuffer=new char[nLen+1];
	memset(pBuffer, 0, nLen+1);
	::WideCharToMultiByte(CP_ACP, 0, str.c_str(), str.size(), pBuffer, nLen, NULL, NULL);
	pBuffer[nLen]='\0';
	strDes.append(pBuffer);
	delete[] pBuffer;

__end:
	return strDes;
}
 
wstring A2U(const string& str)	//Ascii字符转
{
	wstring strDes;
	if ( str.empty() )
		goto __end;

	int nLen=::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	if ( 0==nLen )
		goto __end;

	wchar_t* pBuffer=new wchar_t[nLen+1];
	memset(pBuffer, 0, nLen+1);
	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), pBuffer, nLen);
	pBuffer[nLen]='\0';
	strDes.append(pBuffer);
	delete[] pBuffer;

__end:
	return strDes;
}
 
string U2Utf(const wstring& wstrUnicode)	//Unicode转utf8  
{  
	string strRet;
	if( wstrUnicode.empty() )
		return strRet;

	int nLen = WideCharToMultiByte(CP_UTF8, 0, wstrUnicode.c_str(), -1, NULL, 0, NULL, NULL);  
	char* pBuffer=new char[nLen+1];
	pBuffer[nLen] = '\0';
	nLen = WideCharToMultiByte(CP_UTF8, 0, wstrUnicode.c_str(), -1, pBuffer, nLen, NULL, NULL); 
	strRet.append(pBuffer);
	delete[] pBuffer;

	return strRet;  
}
 
wstring Utf2U(const string &str)			//utf8转Unicode
{
	int u16Len = ::MultiByteToWideChar(CP_UTF8, NULL,str.c_str(),(int)str.size(), NULL, 0);
	wchar_t* wstrBuf = new wchar_t[u16Len + 1];
	::MultiByteToWideChar(CP_UTF8, NULL, str.c_str(),(int)str.size(), wstrBuf, u16Len);
	wstrBuf[u16Len] = L'\0';
	wstring wStr;
	wStr.assign(wstrBuf, u16Len);
	delete [] wstrBuf;
	return wStr;
}

//分割字符串
bool SplitString(const wstring& strSource,const wstring& strFlag, vector<wstring>& paramList)
{
	if ( strSource.empty() || strFlag.empty() )
		return false;

	paramList.clear();
	size_t nBeg = 0;
	size_t nFind = strSource.find(strFlag, nBeg);

	if ( nFind == std::wstring::npos )
		paramList.push_back(strSource);
	else
	{
		while ( true )
		{
			if ( nFind != nBeg )
				paramList.push_back(strSource.substr(nBeg, nFind-nBeg));
			nBeg = nFind + strFlag.size();
			if ( nBeg == strSource.size() )
				break;
			nFind = strSource.find(strFlag, nBeg);
			if ( nFind == std::wstring::npos )
			{
				paramList.push_back(wstring(strSource.begin()+nBeg, strSource.end()));
				break;
			}
		}
	}
	
	return true;
}

//URL编码
string UrlEncode(const string& strSrc)
{
	string strDes;
	for ( size_t i=0; i<strSrc.size(); ++i )
	{
		BYTE ch=(BYTE)strSrc[i];
		if ( isalnum(ch) || ch=='-' || ch=='_' || ch=='.' || ch=='~' )
			strDes+=ch;
		else if ( ch==' ' )
			strDes+='+';
		else
		{
			strDes+='%';
			strDes+=ToHex( (ch>>4) );
			strDes+=ToHex( ch%16 );
		}
	}
	
	return strDes;
}

//URL解码
string UrlDecode(const string& strSrc)
{
	string strDes;  
	for ( size_t i = 0; i < strSrc.size(); i++ )  
	{  
		BYTE ch=strSrc[i];
		if (ch == '+') 
			strDes+=' ';  
		else if (ch == '%')  
		{  
			BYTE h = FromHex((unsigned char)strSrc[++i]);  
			BYTE l = FromHex((unsigned char)strSrc[++i]);  
			strDes += (h<<4) + l;  
		}  
		else strDes += ch;  
	}

	return strDes; 
}

//替换字符串
wstring StrReplaceW(const wstring& strContent, const wstring& strTag, const wstring& strReplace)
{
	size_t nBegin=0, nFind=0;
	nFind = strContent.find(strTag, nBegin);
	if ( nFind == wstring::npos )
		return strContent;

	size_t nTagLen = strTag.size();
	wstring strRet;
	while ( true )
	{
		strRet.append(strContent.begin()+nBegin, strContent.begin()+nFind);
		strRet.append(strReplace);
		nBegin = nFind + nTagLen;
		nFind = strContent.find(strTag, nBegin);
		if ( nFind == wstring::npos )
		{
			strRet.append(strContent.begin()+nBegin, strContent.end());
			break;
		}
	}

	return strRet;
}
 
string StrReplaceA( const string& strContent, const string& strTag, const string& strReplace )
{
	size_t nBegin=0, nFind=0;
	nFind = strContent.find(strTag, nBegin);
	if ( nFind == string::npos )
		return strContent;

	size_t nTagLen = strTag.size();
	string strRet;
	while ( true )
	{
		strRet.append(strContent.begin()+nBegin, strContent.begin()+nFind);
		strRet.append(strReplace);
		nBegin = nFind + nTagLen;
		nFind = strContent.find(strTag, nBegin);
		if ( nFind == string::npos )
		{
			strRet.append(strContent.begin()+nBegin, strContent.end());
			break;
		}
	}

	return strRet;
}

// https://blog.csdn.net/Harry_lyc/article/details/6624960
/*
    string 转换为 wstring 
*/
std::wstring c2w(const char *pc)
{
    std::wstring val = L"";
 
    if(NULL == pc)
    {
        return val;
    }

    size_t size_of_wc;
    size_t destlen = mbstowcs(0,pc,0);
    if (destlen == (size_t)(-1))
    {
        return val;
    }

    size_of_wc = destlen + 1;
    wchar_t * pw  = new wchar_t[size_of_wc];
    mbstowcs(pw, pc, size_of_wc);
    val = pw;
    delete pw;

    return val;
}

/*
    wstring 转换为 string
*/
std::string w2c(const wchar_t * pw)
{
    std::string val = "";

    if(!pw)
    {
        return val;
    }

    size_t size= wcslen(pw) * sizeof(wchar_t);
    char *pc = NULL;
    if(!(pc = (char*)malloc(size)))
    {
        return val;
    }

    size_t destlen = wcstombs(pc, pw, size);
    /*转换不为空时，返回值为-1。如果为空，返回值0*/
    if (destlen ==(size_t)(0))
    {
        return val;
    }

    val = pc;
    delete pc;

    return val;
}