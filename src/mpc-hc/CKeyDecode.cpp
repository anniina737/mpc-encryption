#include "stdafx.h"
#include "CKeyDecode.h"


// COpenDlg dialog
CString CKeyDecode::m_key = _T("");

//IMPLEMENT_DYNAMIC(COpenDlg, CResizableDialog)
CKeyDecode::CKeyDecode(CWnd* pParent /*=nullptr*/)
    : CResizableDialog(CKeyDecode::IDD, pParent)
    , m_bSetAsDefault(true)
    , m_bMultipleFiles(false)
{
}

CKeyDecode::~CKeyDecode()
{
}


void CKeyDecode::DoDataExchange(CDataExchange* pDX)
{
    __super::DoDataExchange(pDX);
    DDX_Control(pDX, IDR_MAINFRAME, m_icon);
    DDX_Text(pDX, IDC_EDIT1, m_key);
    DDX_Check(pDX, IDC_CHECK1, m_bSetAsDefault);
}


BEGIN_MESSAGE_MAP(CKeyDecode, CResizableDialog)
    ON_BN_CLICKED(IDOK, OnOk)
END_MESSAGE_MAP()


// COpenDlg message handlers

BOOL CKeyDecode::OnInitDialog()
{
    __super::OnInitDialog();

    m_icon.SetIcon((HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
    
    m_bMultipleFiles = false;
    
    AddAnchor(IDC_BUTTON1, TOP_RIGHT);
    AddAnchor(IDC_BUTTON2, TOP_RIGHT);
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

void CKeyDecode::OnOk()
{
    UpdateData();
    
    OnOK();
}
