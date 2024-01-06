#pragma once

#include "resource.h"
#include "C:\mpc-hc\src\thirdparty\ResizableLib\ResizableDialog.h"
class CKeyEncode :
	public CResizableDialog
{
private:
    CStatic m_icon;
    bool m_bMultipleFiles;
    CString m_path;
    CComboBox m_cbMRU;
    CString current_key;
    CString new_key;

    CAtlList<CString> m_fns;

public:
    CKeyEncode(CWnd* pParent = nullptr);
    virtual ~CKeyEncode();

    // Dialog Data
    enum { IDD = IDD_KEY_ENCODE_DLG };

    CString GetFileNames() { CString r = _T(""); return r; }

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
    
    afx_msg void OnBrowseFile();
    afx_msg void OnOk();
};

