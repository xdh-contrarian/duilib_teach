#ifndef __UIMARKUP_H__
#define __UIMARKUP_H__

#pragma once

namespace DuiLib {

enum
{
    XMLFILE_ENCODING_UTF8 = 0,          // xml 编码格式 utf-8
    XMLFILE_ENCODING_UNICODE = 1,       // xml 编码格式 unicode
    XMLFILE_ENCODING_ASNI = 2,          // xml 编码格式 asni
};

class CMarkup;
class CMarkupNode;

// xml解析器 目前内置支持三种编码格式:UTF8、UNICODE、ASNI，默认为UTF8；
class DUILIB_API CMarkup
{
    friend class CMarkupNode;
public:
    CMarkup(LPCTSTR pstrXML = NULL);
    ~CMarkup();

    bool Load(LPCTSTR pstrXML);
    // 通过加载内存资源方式解析，内部通过宏处理时限宽字节unicode和多字节编译时定义处理解析，最终也是分配m_pstrXML缓冲区并拷贝该内存数据内容，后通过_Parse解析
    bool LoadFromMem(BYTE* pByte, DWORD dwSize, int encoding = XMLFILE_ENCODING_UTF8);
    // 通过参数pstrFilename文件路径名，可以是xml文件或是压缩文件(内部为xml文件)，对于xml文件或是压缩文件处理读取内部数据至临时内存缓冲区中(解压缩采用的是ZIP_INFO)
    bool LoadFromFile(LPCTSTR pstrFilename, int encoding = XMLFILE_ENCODING_UTF8);
    void Release();                                                                     // 主要用以释放m_pstrXML和m_pElements缓冲区资源
    bool IsValid() const;                                                               // 当前解析是否有效，通过m_pElements != NULL判断；

    void SetPreserveWhitespace(bool bPreserve = true);
    void GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const;
    void GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const;

    CMarkupNode GetRoot();          // 获取根节点CMarkupNode，CMarkupNode(this, 1)，以当前为第一个节点的节点对象

private:
    typedef struct tagXMLELEMENT
    {
        ULONG iStart;               // 节点元素在xml文件中的起始位置
        ULONG iChild;               // 节点元素子节点
        ULONG iNext;                // 节点元素的下一个节点(兄弟节点)
        ULONG iParent;              // 节点元素的父节点
        ULONG iData;                // 节点元素的数据(事实上，这些值均为ULONG类似，即unsigned long;存储的值为当前数据在内存缓冲区m_pstrXML中指向的位置)
    } XMLELEMENT;

    LPTSTR m_pstrXML;               // 以加载xml文件数据内容的指针缓冲区
    XMLELEMENT* m_pElements;        // 保存XMLELEMENT类型的节点元素信息的缓冲区，事实上可能有部分未预料的存储空间
    ULONG m_nElements;              // 实际的保存m_pElements中有效的节点元素数
    ULONG m_nReservedElements;      // 预留的m_pElements缓冲区空间大小
    TCHAR m_szErrorMsg[100];        // 最近一次解析时的错误信息
    TCHAR m_szErrorXML[50];         // 最近一次解析时的xml位置信息
    bool m_bPreserveWhitespace;     // 是否跳过忽略空格，默认是忽略；

private:
    bool _Parse();                                                      // 分配预留空间、初始化m_szErrorMsg、m_szErrorXML，并调用重载函数_Parse，执行真正的解析过程
    bool _Parse(LPTSTR& pstrText, ULONG iParent);                       // 
    XMLELEMENT* _ReserveElement();                                      // 分配足够的预留空间
    inline void _SkipWhitespace(LPCTSTR& pstr) const;
    inline void _SkipWhitespace(LPTSTR& pstr) const;                    // 重载版本均处理、跳过字符串空格
    inline void _SkipIdentifier(LPCTSTR& pstr) const;                   // 重载版本均均处理、跳过标志符号如：‘_’， ‘:’
    inline void _SkipIdentifier(LPTSTR& pstr) const;
    bool _ParseData(LPTSTR& pstrText, LPTSTR& pstrData, char cEnd);     // 解析元素属性中数据
    void _ParseMetaChar(LPTSTR& pstrText, LPTSTR& pstrDest);            // 解析元字符，如：'&', '<','>','\"','\'','&'与'a', 'm', 'p', 't', ';'等相关组合字符串
    bool _ParseAttributes(LPTSTR& pstrText);                            // 解析元素属性
    bool _Failed(LPCTSTR pstrError, LPCTSTR pstrLocation = NULL);       // 保存解析中产生最近一次的错误信息、位置
};


class DUILIB_API CMarkupNode
{
    friend class CMarkup;
private:
    CMarkupNode();
    CMarkupNode(CMarkup* pOwner, int iPos);

public:
    bool IsValid() const;

    CMarkupNode GetParent();
    CMarkupNode GetSibling();
    CMarkupNode GetChild();
    CMarkupNode GetChild(LPCTSTR pstrName);

    bool HasSiblings() const;
    bool HasChildren() const;
    LPCTSTR GetName() const;
    LPCTSTR GetValue() const;

    bool HasAttributes();
    bool HasAttribute(LPCTSTR pstrName);
    int GetAttributeCount();
    LPCTSTR GetAttributeName(int iIndex);
    LPCTSTR GetAttributeValue(int iIndex);
    LPCTSTR GetAttributeValue(LPCTSTR pstrName);
    bool GetAttributeValue(int iIndex, LPTSTR pstrValue, SIZE_T cchMax);
    bool GetAttributeValue(LPCTSTR pstrName, LPTSTR pstrValue, SIZE_T cchMax);

private:
    void _MapAttributes();

    enum { MAX_XML_ATTRIBUTES = 64 };

    typedef struct
    {
        ULONG iName;
        ULONG iValue;
    } XMLATTRIBUTE;

    int m_iPos;
    int m_nAttributes;
    XMLATTRIBUTE m_aAttributes[MAX_XML_ATTRIBUTES];
    CMarkup* m_pOwner;
};

} // namespace DuiLib

#endif // __UIMARKUP_H__
