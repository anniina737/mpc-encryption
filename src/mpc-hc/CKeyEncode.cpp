#include "stdafx.h"
#include "CKeyEncode.h"

#include "mplayerc.h"
#include "PathUtils.h"
#include "OpenFileDlg.h"
#include "media_encrypt.h"
#include "cover_mp4.h"

//IMPLEMENT_DYNAMIC(COpenDlg, CResizableDialog)
CKeyEncode::CKeyEncode(CWnd* pParent /*=nullptr*/)
    : CResizableDialog(CKeyEncode::IDD, pParent)
    , m_bSetAsDefault(FALSE)
    , m_bMultipleFiles(false)
{
}

CKeyEncode::~CKeyEncode()
{
}


void CKeyEncode::DoDataExchange(CDataExchange* pDX)
{
    __super::DoDataExchange(pDX);
    DDX_Control(pDX, IDR_MAINFRAME, m_icon);
    DDX_Control(pDX, IDC_COMBO1, m_cbMRU);
    DDX_CBString(pDX, IDC_COMBO1, m_path);
    DDX_Text(pDX, IDC_EDIT1, current_key);
    DDX_Text(pDX, IDC_EDIT3, new_key);
}


BEGIN_MESSAGE_MAP(CKeyEncode, CResizableDialog)
    ON_BN_CLICKED(IDC_BUTTON1, OnBrowseFile)    
    ON_BN_CLICKED(IDOK, OnOk)
END_MESSAGE_MAP()


// COpenDlg message handlers

BOOL CKeyEncode::OnInitDialog()
{
    __super::OnInitDialog();

    m_icon.SetIcon((HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED));

    m_bMultipleFiles = false;
    
    m_fns.RemoveAll();
    m_path.Empty();
    m_cbMRU.SetWindowText(L"");
    current_key.Empty();
    new_key.Empty();

    //AddAnchor(IDC_BUTTON1, TOP_RIGHT);
    //AddAnchor(IDC_BUTTON2, TOP_RIGHT);
    AddAnchor(IDOK, TOP_RIGHT);
    AddAnchor(IDCANCEL, TOP_RIGHT);
    AddAnchor(IDC_STATIC1, TOP_LEFT, TOP_RIGHT);

    CRect r;
    GetWindowRect(r);
    CSize size = r.Size();
    SetMinTrackSize(size);
    size.cx = 1000;
    SetMaxTrackSize(size);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


void CKeyEncode::OnOk()
{
    UpdateData();

    //
    Cmedia_encrypt myInstance;
    GlobalEncodeInst = &myInstance;
    GlobalEncodeInst->setCoverInfo(CoverMp4Data, sizeof(CoverMp4Data));
    GlobalEncodeInst->setMaxCoverSize(MaxCoverMp4);

    const wchar_t* myWideChar = current_key.GetBuffer();
    int bufferSize = WideCharToMultiByte(CP_UTF8, 0, myWideChar, -1, NULL, 0, NULL, NULL);
    char* myChar = new char[bufferSize];
    WideCharToMultiByte(CP_UTF8, 0, myWideChar, -1, myChar, bufferSize, NULL, NULL);

    const wchar_t* myWideChar02 = new_key.GetBuffer();
    int bufferSize02 = WideCharToMultiByte(CP_UTF8, 0, myWideChar02, -1, NULL, 0, NULL, NULL);
    char* myChar02 = new char[bufferSize02];
    WideCharToMultiByte(CP_UTF8, 0, myWideChar02, -1, myChar02, bufferSize02, NULL, NULL);

    POSITION pos = m_fns.GetHeadPosition();
    while (pos) {
        CString fullpath = MakeFullPath(m_fns.GetNext(pos));        

        bool result = GlobalEncodeInst->DoEncrypt(CStringW(fullpath), myChar, myChar02);

        CString result_msg(fullpath);        

        if (result) {
            result_msg += L", Encrypt Successful";            
        }
        else {
            result_msg += L", Encrypt Failed";
        }
        AfxMessageBox(result_msg);
    }

    current_key.ReleaseBuffer();
    delete[] myChar;

    current_key.ReleaseBuffer();
    delete[] myChar02;

    OnOK();
}


void CKeyEncode::OnBrowseFile()
{
    UpdateData();

    const CAppSettings& s = AfxGetAppSettings();

    CString filter;
    CAtlArray<CString> mask;
    s.m_Formats.GetFilter(filter, mask);

    DWORD dwFlags = OFN_EXPLORER | OFN_ENABLESIZING | OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_ENABLEINCLUDENOTIFY | OFN_NOCHANGEDIR;
    if (!s.fKeepHistory) {
        dwFlags |= OFN_DONTADDTORECENT;
    }

    COpenFileDlg fd(mask, true, nullptr, m_path, dwFlags, filter, this);
    if (fd.DoModal() != IDOK) {
        return;
    }

    m_fns.RemoveAll();
    
    POSITION pos = fd.GetStartPosition();
    while (pos) {
        /*
                CString str = fd.GetNextPathName(pos);
                POSITION insertpos = m_fns.GetTailPosition();
                while (insertpos && GetFileName(str).CompareNoCase(GetFileName(m_fns.GetAt(insertpos))) <= 0)
                    m_fns.GetPrev(insertpos);
                if (!insertpos) m_fns.AddHead(str);
                else m_fns.InsertAfter(insertpos, str);
        */
        m_fns.AddTail(fd.GetNextPathName(pos));
    }

    if (m_fns.GetCount() > 1
        || m_fns.GetCount() == 1
        && (m_fns.GetHead()[m_fns.GetHead().GetLength() - 1] == '\\'
            || m_fns.GetHead()[m_fns.GetHead().GetLength() - 1] == '*')) {
        m_bMultipleFiles = true;
        m_cbMRU.SetWindowText(_T("MultiFiles"));
        return;
    }

    m_cbMRU.SetWindowText(fd.GetPathName());
}
