#ifndef __UIMARKUP_H__
#define __UIMARKUP_H__

#pragma once

namespace DuiLib {

enum
{
    XMLFILE_ENCODING_UTF8 = 0,          // xml �����ʽ utf-8
    XMLFILE_ENCODING_UNICODE = 1,       // xml �����ʽ unicode
    XMLFILE_ENCODING_ASNI = 2,          // xml �����ʽ asni
};

class CMarkup;
class CMarkupNode;

// xml������ Ŀǰ����֧�����ֱ����ʽ:UTF8��UNICODE��ASNI��Ĭ��ΪUTF8��
class DUILIB_API CMarkup
{
    friend class CMarkupNode;
public:
    CMarkup(LPCTSTR pstrXML = NULL);
    ~CMarkup();

    bool Load(LPCTSTR pstrXML);
    // ͨ�������ڴ���Դ��ʽ�������ڲ�ͨ���괦��ʱ�޿��ֽ�unicode�Ͷ��ֽڱ���ʱ���崦�����������Ҳ�Ƿ���m_pstrXML���������������ڴ��������ݣ���ͨ��_Parse����
    bool LoadFromMem(BYTE* pByte, DWORD dwSize, int encoding = XMLFILE_ENCODING_UTF8);
    // ͨ������pstrFilename�ļ�·������������xml�ļ�����ѹ���ļ�(�ڲ�Ϊxml�ļ�)������xml�ļ�����ѹ���ļ������ȡ�ڲ���������ʱ�ڴ滺������(��ѹ�����õ���ZIP_INFO)
    bool LoadFromFile(LPCTSTR pstrFilename, int encoding = XMLFILE_ENCODING_UTF8);
    void Release();                                                                     // ��Ҫ�����ͷ�m_pstrXML��m_pElements��������Դ
    bool IsValid() const;                                                               // ��ǰ�����Ƿ���Ч��ͨ��m_pElements != NULL�жϣ�

    void SetPreserveWhitespace(bool bPreserve = true);
    void GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const;
    void GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const;

    CMarkupNode GetRoot();          // ��ȡ���ڵ�CMarkupNode��CMarkupNode(this, 1)���Ե�ǰΪ��һ���ڵ�Ľڵ����

private:
    typedef struct tagXMLELEMENT
    {
        ULONG iStart;               // �ڵ�Ԫ����xml�ļ��е���ʼλ��
        ULONG iChild;               // �ڵ�Ԫ���ӽڵ�
        ULONG iNext;                // �ڵ�Ԫ�ص���һ���ڵ�(�ֵܽڵ�)
        ULONG iParent;              // �ڵ�Ԫ�صĸ��ڵ�
        ULONG iData;                // �ڵ�Ԫ�ص�����(��ʵ�ϣ���Щֵ��ΪULONG���ƣ���unsigned long;�洢��ֵΪ��ǰ�������ڴ滺����m_pstrXML��ָ���λ��)
    } XMLELEMENT;

    LPTSTR m_pstrXML;               // �Լ���xml�ļ��������ݵ�ָ�뻺����
    XMLELEMENT* m_pElements;        // ����XMLELEMENT���͵Ľڵ�Ԫ����Ϣ�Ļ���������ʵ�Ͽ����в���δԤ�ϵĴ洢�ռ�
    ULONG m_nElements;              // ʵ�ʵı���m_pElements����Ч�Ľڵ�Ԫ����
    ULONG m_nReservedElements;      // Ԥ����m_pElements�������ռ��С
    TCHAR m_szErrorMsg[100];        // ���һ�ν���ʱ�Ĵ�����Ϣ
    TCHAR m_szErrorXML[50];         // ���һ�ν���ʱ��xmlλ����Ϣ
    bool m_bPreserveWhitespace;     // �Ƿ��������Կո�Ĭ���Ǻ��ԣ�

private:
    bool _Parse();                                                      // ����Ԥ���ռ䡢��ʼ��m_szErrorMsg��m_szErrorXML�����������غ���_Parse��ִ�������Ľ�������
    bool _Parse(LPTSTR& pstrText, ULONG iParent);                       // 
    XMLELEMENT* _ReserveElement();                                      // �����㹻��Ԥ���ռ�
    inline void _SkipWhitespace(LPCTSTR& pstr) const;
    inline void _SkipWhitespace(LPTSTR& pstr) const;                    // ���ذ汾�����������ַ����ո�
    inline void _SkipIdentifier(LPCTSTR& pstr) const;                   // ���ذ汾��������������־�����磺��_���� ��:��
    inline void _SkipIdentifier(LPTSTR& pstr) const;
    bool _ParseData(LPTSTR& pstrText, LPTSTR& pstrData, char cEnd);     // ����Ԫ������������
    void _ParseMetaChar(LPTSTR& pstrText, LPTSTR& pstrDest);            // ����Ԫ�ַ����磺'&', '<','>','\"','\'','&'��'a', 'm', 'p', 't', ';'���������ַ���
    bool _ParseAttributes(LPTSTR& pstrText);                            // ����Ԫ������
    bool _Failed(LPCTSTR pstrError, LPCTSTR pstrLocation = NULL);       // ��������в������һ�εĴ�����Ϣ��λ��
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
