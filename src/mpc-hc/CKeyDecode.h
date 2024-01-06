#pragma once

#include "resource.h"
#include "ResizableLib/ResizableDialog.h"

class CKeyDecode :public CResizableDialog
{
private:
    CStatic m_icon;
    BOOL m_bSetAsDefault;
    bool m_bMultipleFiles;

public:
    static CString m_key;
    CKeyDecode(CWnd* pParent = nullptr);
    virtual ~CKeyDecode();

    // Dialog Data
    enum { IDD = IDD_KEY_DECODE_DLG };

    CString GetKey() { return this->m_key; };
    
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()

    afx_msg void OnOk();
};

